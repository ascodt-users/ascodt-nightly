#include "NSLBCommunicator.h"
#include "CouplingDefinitions.h"
#include <sstream>
NSLBCommunicator::NSLBCommunicator(
		const Parameters & parameters,
		int index,int* start,int* end,std::string mi):
		_parameters(parameters),
		_mid(mi)

{

	_startIndex[0]=start[index*3];
	_startIndex[1]=start[index*3+1];
	_startIndex[2]=start[index*3+2];

	_endIndex[0]=end[index*3];
	_endIndex[1]=end[index*3+1];
	_endIndex[2]=end[index*3+2];
	_nslbPeer2Peer=NULL;

//	_iter=0;
//	_open=false;
}
NSLBCommunicator::~NSLBCommunicator(){
	if(_nslbPeer2Peer){
		//_lbnsPeer2Peer->disconnect();
		delete _nslbPeer2Peer;
		_nslbPeer2Peer=NULL;
	}

}
//void NSLBCommunicator::open(){
//	if(!_open){
//		std::stringstream fileName;
//		fileName<<"log_nslb_sender."<<_parameters.parallel.rank<<".txt";
//		_logComm.open(fileName.str().c_str());
//	}
//	_open=true;
//}
void NSLBCommunicator::connect(){
	if(_nslbPeer2Peer==NULL){
		std::string hostname = _mid.substr(0,_mid.find(":"));
		std::string port = _mid.substr(_mid.find(":")+1,_mid.size()-_mid.find(":"));
		const char* buffer_size = getenv("CCA_CFD_NS_BUFFER_SIZE");
		_nslbPeer2Peer= new cca::cfd::LBSolverCxx2SocketPlainPort(
				(char*)hostname.c_str(),atoi(port.c_str()),atoi(buffer_size)
		);
		std::cout<<"connecting rank:"<<_parameters.parallel.rank<<" host:"<<hostname<<"port:"<<port<<std::endl;
	}
}

void NSLBCommunicator::convert(
		std::vector<int>& keysVelocity,
		std::vector<int> &velocityOffsets,
		std::vector<int> &velocityFlips,
		std::vector<double>& velocityValues,
		std::vector<int>& componentSize,
		std::vector<int>& keysPressure,
		std::vector<int> &pressureOffsets,
		std::vector<int> &pressureFlips,
		std::vector<double>& pressureValues

){
	std::unordered_map<int,std::vector<NSLBData>>::iterator it;

	for(it=_velocities[0].begin();it!=_velocities[0].end();it++){
		for(unsigned int i=0;i<(*it).second.size();i++){
			keysVelocity.push_back((*it).first);
			velocityValues.push_back((*it).second[i].value);
			velocityOffsets.push_back((*it).second[i].offset[0]);
			velocityOffsets.push_back((*it).second[i].offset[1]);
			velocityOffsets.push_back((*it).second[i].offset[2]);
			velocityFlips.push_back((*it).second[i].flip[0]);
			velocityFlips.push_back((*it).second[i].flip[1]);
			velocityFlips.push_back((*it).second[i].flip[2]);
		}
	}
	componentSize[0]=velocityValues.size();

	for(it=_velocities[1].begin();it!=_velocities[1].end();it++){
		for(unsigned int i=0;i<(*it).second.size();i++){
			keysVelocity.push_back((*it).first);
			velocityValues.push_back((*it).second[i].value);
			velocityOffsets.push_back((*it).second[i].offset[0]);
			velocityOffsets.push_back((*it).second[i].offset[1]);
			velocityOffsets.push_back((*it).second[i].offset[2]);
			velocityFlips.push_back((*it).second[i].flip[0]);
			velocityFlips.push_back((*it).second[i].flip[1]);
			velocityFlips.push_back((*it).second[i].flip[2]);
		}
	}
	componentSize[1]=velocityValues.size()-componentSize[0];
	for(it=_velocities[2].begin();it!=_velocities[2].end();it++){

		for(unsigned int i=0;i<(*it).second.size();i++){
			keysVelocity.push_back((*it).first);
			velocityValues.push_back((*it).second[i].value);
			velocityOffsets.push_back((*it).second[i].offset[0]);
			velocityOffsets.push_back((*it).second[i].offset[1]);
			velocityOffsets.push_back((*it).second[i].offset[2]);
			velocityFlips.push_back((*it).second[i].flip[0]);
			velocityFlips.push_back((*it).second[i].flip[1]);
			velocityFlips.push_back((*it).second[i].flip[2]);
		}
	}
	componentSize[2]=velocityValues.size()-componentSize[1]-componentSize[0];
	for(it=_pressure.begin();it!=_pressure.end();it++){

		for(unsigned int i=0;i<(*it).second.size();i++){
			keysPressure.push_back((*it).first);
			pressureValues.push_back((*it).second[i].value);
			pressureOffsets.push_back((*it).second[i].offset[0]);
			pressureOffsets.push_back((*it).second[i].offset[1]);
			pressureOffsets.push_back((*it).second[i].offset[2]);
			pressureFlips.push_back((*it).second[i].flip[0]);
			pressureFlips.push_back((*it).second[i].flip[1]);
			pressureFlips.push_back((*it).second[i].flip[2]);

		}
	}
	if(componentSize[0]<=0||componentSize[1]<=0||
			componentSize[2]<=0||pressureValues.size()<=0)
		std::cout<<"alarm :"<<componentSize[0]<<","<<componentSize[1]<<","<<componentSize[2]<<std::endl;
	_velocities[0].clear();
	_velocities[1].clear();
	_velocities[2].clear();
	_pressure.clear();
}
void NSLBCommunicator::flush(){
	//_logComm.flush();
	std::vector<double> velocityValues;
	std::vector<int> velocityOffsets;
	std::vector<int> velocityFlips;
	std::vector<int> pressureOffsets;
	std::vector<int> pressureFlips;


	std::vector<double> pressureValues;
	std::vector<int> keysVelocity;
	std::vector<int> keysPressure;

	std::vector<int> componentSize;
	componentSize.resize(3);
	if(_velocities[0].size()>0||_velocities[1].size()>0||_velocities[2].size()>0){
		connect();
		convert(keysVelocity,velocityOffsets,velocityFlips,velocityValues,componentSize,keysPressure,pressureOffsets,pressureFlips,pressureValues);
		int ack=0;
		_nslbPeer2Peer->forwardVelocities(
				&keysVelocity[0],
				keysVelocity.size(),
				&velocityOffsets[0],
				velocityOffsets.size(),
				&velocityFlips[0],
				velocityFlips.size(),
				&velocityValues[0],
				velocityValues.size(),
				&componentSize[0],
				componentSize.size(),
				ack
		);

		_nslbPeer2Peer->forwardPressure(
				&keysPressure[0],
				keysPressure.size(),
				&pressureOffsets[0],
				pressureOffsets.size(),
				&pressureFlips[0],
				pressureFlips.size(),
				&pressureValues[0],
				pressureValues.size(),
				ack
		);
	}

}
int NSLBCommunicator::index2Varray ( int i, int j, int k, int component, int stencil ) const {

	// Check that the indexes are within bounds
	int sizeX=_parameters.geometry.sizeX+3;
	int sizeY=_parameters.geometry.sizeY+3;
	int sizeZ=_parameters.geometry.sizeZ+3;
	assertion ( ( i < sizeX ) && ( j < sizeY ) && ( k < sizeZ ) );
	assertion ( ( i >= 0 ) && ( j >= 0 ) && ( k >= 0 )  );

	return  (3*stencilSize * ( i + ( j * sizeX ) + ( k * sizeY * sizeX) ))+component*stencilSize+stencil;
}
int NSLBCommunicator::index2Parray ( int i, int j, int k, int stencil ) const {

	// Check that the indexes are within bounds
	int sizeX=_parameters.geometry.sizeX+3;
	int sizeY=_parameters.geometry.sizeY+3;
	int sizeZ=_parameters.geometry.sizeZ+3;
	assertion ( ( i < sizeX ) && ( j < sizeY ) && ( k < sizeZ ) );
	assertion ( ( i >= 0 ) && ( j >= 0 ) && ( k >= 0 )  );

	return  (stencilSize * ( i + ( j * sizeX ) + ( k * sizeY * sizeX ) ))+stencil;
}
const bool NSLBCommunicator::isInside(
		const int i,const int j , const int k) const{
	return
			(i>=_startIndex[0]&&i<=_endIndex[0])&&
			(j>=_startIndex[1]&&j<=_endIndex[1])&&
			(k>=_startIndex[2]&&k<=_endIndex[2]);
}
void NSLBCommunicator::setPressure(
		int i,
		int j,
		int k,
		int stencilIndex,
		const int *  const offset, const int * const flip,
		double value){
	//open();
	int index=index2Parray(i,j,k,stencilIndex);
	NSLBData data;
	data.value=value;
	data.offset[0]=offset[0];
	data.offset[1]=offset[1];
	data.offset[2]=offset[2];
	data.flip[0]=flip[0];
	data.flip[1]=flip[1];
	data.flip[2]=flip[2];
	_pressure[index].push_back(data);
	//	_logComm<<"i_j_k_index:"<<i
	//			<<" "<<j<<" "<<k
	//			<<" stencil:"<<stencilIndex
	//			<<" iter:"<<_iter
	//			<<" index:"<<index
	//			<<" value:"<<value<<std::endl;
}
void NSLBCommunicator::setVelocityComponent(
		const int i,
		const int j,
		const int k,
		const int stencilIndex,
		const int component,
		const int *  const offset, const int * const flip,
		const double velocity){
	int index=index2Varray(i,j,k,component,stencilIndex);
	//std::unordered_map<int,double>::iterator it;
	//it=_velocities[component].find(index);
	//if(it==_velocities[component].end()){
	NSLBData data;
	data.value=velocity;
	data.offset[0]=offset[0];
	data.offset[1]=offset[1];
	data.offset[2]=offset[2];
	data.flip[0]=flip[0];
	data.flip[1]=flip[1];
	data.flip[2]=flip[2];
	//open();
	_velocities[component][index].push_back(data);


//		_logComm<<"i_j_k_index:"<<i
//				<<" "<<j<<" "<<k
//				<<" stencil:"<<stencilIndex
//				<<" component:"<<component
//				<<" index:"<<index
//				<<" value:"<<velocity
//				<<" mid:"<<_mid<<std::endl;


}
