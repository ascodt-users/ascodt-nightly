#include "LBNSCommunicator.h"
#include "CouplingDefinitions.h"
#include <sstream>

LBNSCommunicator::LBNSCommunicator(
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
	_lbnsPeer2Peer=NULL;
	_open=false;

}
LBNSCommunicator::~LBNSCommunicator(){
	if(_lbnsPeer2Peer){
		//_lbnsPeer2Peer->disconnect();
		delete _lbnsPeer2Peer;
		_lbnsPeer2Peer=NULL;
	}

}
void LBNSCommunicator::connect(){
	if(_lbnsPeer2Peer==NULL){
		std::string hostname = _mid.substr(0,_mid.find(":"));
		std::string port = _mid.substr(_mid.find(":")+1,_mid.size()-_mid.find(":"));
		const char* buffer_size = getenv("CCA_CFD_LB_BUFFER_SIZE");
		_lbnsPeer2Peer= new cca::cfd::NSSolverCxx2SocketPlainPort(
				(char*)hostname.c_str(),atoi(port.c_str()),atoi(buffer_size)
		);
		std::cout<<"lbns comm host:"<<hostname<<"port:"<<port<<std::endl;
	}
}
void LBNSCommunicator::open(){
	if(!_open){
		std::stringstream fileName;
		fileName<<"log_lbns_sender."<<_parameters.parallel.rank<<".txt";
		_logComm.open(fileName.str().c_str());
	}
	_open=true;
}

void LBNSCommunicator::convert(
		std::vector<int>& keys,
		std::vector<double>& values,
		std::vector<int>& offsets,
		std::vector<int>& flips,
		std::vector<int>& componentSize){
	__gnu_cxx::hash_map<int,std::vector<LBNSData> >::iterator it;

	for(it=_velocities[0].begin();it!=_velocities[0].end();it++){
		for(unsigned int i=0;i<(*it).second.size();i++){
			keys.push_back((*it).first);
			values.push_back((*it).second[i].value);
			offsets.push_back((*it).second[i].offset[0]);
			offsets.push_back((*it).second[i].offset[1]);
			offsets.push_back((*it).second[i].offset[2]);
			flips.push_back((*it).second[i].flip[0]);
			flips.push_back((*it).second[i].flip[1]);
			flips.push_back((*it).second[i].flip[2]);
		}
	}
	componentSize[0]=values.size();
	for(it=_velocities[1].begin();it!=_velocities[1].end();it++){
		for(unsigned int i=0;i<(*it).second.size();i++){
			keys.push_back((*it).first);
			values.push_back((*it).second[i].value);
			offsets.push_back((*it).second[i].offset[0]);
			offsets.push_back((*it).second[i].offset[1]);
			offsets.push_back((*it).second[i].offset[2]);
			flips.push_back((*it).second[i].flip[0]);
			flips.push_back((*it).second[i].flip[1]);
			flips.push_back((*it).second[i].flip[2]);
		}
	}
	componentSize[1]=values.size()-componentSize[0];
	for(it=_velocities[2].begin();it!=_velocities[2].end();it++){

		for(unsigned int i=0;i<(*it).second.size();i++){
			keys.push_back((*it).first);
			values.push_back((*it).second[i].value);
			offsets.push_back((*it).second[i].offset[0]);
			offsets.push_back((*it).second[i].offset[1]);
			offsets.push_back((*it).second[i].offset[2]);
			flips.push_back((*it).second[i].flip[0]);
			flips.push_back((*it).second[i].flip[1]);
			flips.push_back((*it).second[i].flip[2]);
		}
	}
	componentSize[2]=values.size()-componentSize[1]-componentSize[0];

	_velocities[0].clear();
	_velocities[1].clear();
	_velocities[2].clear();
}
void LBNSCommunicator::flush(){
	std::vector<double> values;
	std::vector<int> keys;
	std::vector<int> componentSize;
	std::vector<int> offsets;
	std::vector<int> flips;
	componentSize.resize(3);
	_logComm.flush();
	if(_velocities[0].size()>0||_velocities[1].size()>0||_velocities[2].size()>0){
		connect();
		int ack;
		convert(keys,values,offsets,flips,componentSize);
		_lbnsPeer2Peer->forwardVelocities(
				&keys[0],
				keys.size(),
				&offsets[0],
				offsets.size(),
				&flips[0],
				flips.size(),
				&values[0],
				values.size(),
				&componentSize[0],
				componentSize.size(),
				ack
		);
	}

}
int LBNSCommunicator::index2array ( int i, int j, int k, int component, int stencil ) const {

	// Check that the indexes are within bounds
	int sizeX=_parameters.geometry.sizeX+3;
	int sizeY=_parameters.geometry.sizeY+3;
	int sizeZ=_parameters.geometry.sizeZ+3;
	assertion ( ( i < sizeX ) && ( j < sizeY ) && ( k < sizeZ ) );
	assertion ( ( i >= 0 ) && ( j >= 0 ) && ( k >= 0 )  );

	return  (3*stencilSize * ( i + ( j * sizeX ) + ( k * sizeY * sizeX ) ))+component*stencilSize+stencil;
}
const bool LBNSCommunicator::isInside(int i, int j ,int k) const{
	return
			(i>=_startIndex[0]&&i<=_endIndex[0])&&
			(j>=_startIndex[1]&&j<=_endIndex[1])&&
			(k>=_startIndex[2]&&k<=_endIndex[2]);
}
void LBNSCommunicator::setDensity(
		int i,
		int j,
		int k,
		int stencilIndex,
		double value){

}
void LBNSCommunicator::setVelocityComponent(
		int i,
		int j,
		int k,
		int stencilIndex,
		int component,
		const int *offset,
		const int *flip,
		double velocity){
	int index=index2array(i,j,k,component,stencilIndex);

	open();
	_logComm<<"i_j_k_index:"<<i
			<<" "<<j<<" "<<k
			<<" stencil:"<<stencilIndex
			<<" component:"<<component
			<<" index:"<<index
			<<" value:"<<velocity
			<<" mid:"<<_mid<<std::endl;

	LBNSData data;
	data.value=velocity;
	data.offset[0]=offset[0];
	data.offset[1]=offset[1];
	data.offset[2]=offset[2];
	data.flip[0]=flip[0];
	data.flip[1]=flip[1];
	data.flip[2]=flip[2];
	_velocities[component][index].push_back(data);
}
