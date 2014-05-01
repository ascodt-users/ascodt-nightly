#include "LBNSCommunicator.h"
#include "CouplingDefinitions.h"
#include <sstream>

LBNSCommunicator::LBNSCommunicator(
		const Parameters & parameters,
		int index,int* start,int* end,std::string mi,
		std::vector<int>& maxSizeCommunicators,
		std::vector<int>& sizeCommunicators):
		_parameters(parameters),
		_mid(mi),
		_maxSizeCommunicators(maxSizeCommunicators),
		_sizeCommunicators(sizeCommunicators)

{

	_startIndex[0]=start[index*3];
	_startIndex[1]=start[index*3+1];
	_startIndex[2]=start[index*3+2];

	_endIndex[0]=end[index*3];
	_endIndex[1]=end[index*3+1];
	_endIndex[2]=end[index*3+2];
	_lbnsPeer2Peer=NULL;
	_open=false;
	_velocity_keys_count_sum=0;
	_velocity_offset_count_sum=0;
	_velocity_flips_count_sum=0;
	_velocity_count_sum=0;
	_index=index;
	std::cout<<"creating com:"<<_index<<std::endl;
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
//	if(!_open){
//		std::stringstream fileName;
//		fileName<<"log_lbns_sender."<<_parameters.parallel.rank<<".txt";
//		_logComm.open(fileName.str().c_str());
//	}
//	_open=true;
}

void LBNSCommunicator::convertVelocity(
		std::vector<int>& keysVelocity,
		std::vector<int>& velocityOffsets,
		std::vector<int>& velocityFlips,
		std::vector<double>& velocityValues

){
	__gnu_cxx::hash_map<int,std::vector<LBNSData> >::iterator it;
	for(it=_velocities.begin();it!=_velocities.end();it++){
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
}

void LBNSCommunicator::flush(){
	//_logComm.flush();
	int rank=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(_maxSizeCommunicators[_index*2+1]==rank){
		connect();
		int ack;
		//convert(keys,values,offsets,flips,componentSize);
		_lbnsPeer2Peer->forwardVelocities(
				&_velocityKeys[0],
				_velocityKeys.size(),
				&_velocityOffsets[0],
				_velocityOffsets.size(),
				&_velocityFlips[0],
				_velocityFlips.size(),
				&_velocityValues[0],
				_velocityValues.size(),
				ack
		);
	}
	_velocities.clear();

}

void LBNSCommunicator::gatherVelocity(
		std::vector<int>& keys,
		std::vector<int>& offset,
		std::vector<int>& flips,
		std::vector<double>& velocities)
{
	//_logComm<<"start gather com:"<<_index<<",on rank:"<<_parameters.parallel.rank<<" keys:"<<keys.size()<<std::endl;
	gatherArray(_velocity_keys_count_sum,_velocity_keys_count,_velocity_keys_displ,keys);
	//_logComm<<"start gather com:"<<_index<<",on rank:"<<_parameters.parallel.rank<<" flips:"<<flips.size()<<std::endl;

	gatherArray(_velocity_flips_count_sum,_velocity_flips_count,_velocity_flips_displ,flips);
	//_logComm<<"start gather com:"<<_index<<",on rank:"<<_parameters.parallel.rank<<" offset:"<<offset.size()<<std::endl;

	gatherArray(_velocity_offset_count_sum,_velocity_offset_count,_velocity_offset_displ,offset);
	//_logComm<<"start gather com:"<<_index<<",on rank:"<<_parameters.parallel.rank<<" data:"<<velocities.size()<<std::endl;

	gatherArray(_velocity_count_sum,_velocity_count,_velocity_displ,velocities);
	//_logComm<<"end gather com:"<<_index<<",on rank:"<<_parameters.parallel.rank<<" data:"<<_velocities.size()<<std::endl;
}

void LBNSCommunicator::gatherArray(
		int& count,
		std::vector<int>& data_size,
		std::vector<int>& data_displ,
		std::vector<int>& data){
	int rank=0;
	int com_size=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	MPI_Comm_size(MPI_COMM_WORLD,&com_size);
	if(data_size.size()==0){

		count=data.size();
		data_size.resize(1);
		if(rank==_maxSizeCommunicators[_index*2+1])
			data_size.resize(com_size);
		MPI_Gather(&count,1, MPI_INT, &data_size[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
		if(rank==_maxSizeCommunicators[_index*2+1]){
			data_displ.resize(com_size);

			data_displ[rank]=0;

			for(int i=0;i<com_size;i++){
				if(i!=rank){
					data_displ[i]=count;
					count+=data_size[i];
				}
			}
		}
	}
	data.resize(count);
	if(rank==_maxSizeCommunicators[_index*2+1])
		MPI_Gatherv(MPI_IN_PLACE,0, MPI_INT,&data[0], &data_size[0],&data_displ[0], MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
	else
		MPI_Gatherv(&data[0],count, MPI_INT,&data[0], &data_size[0],&data_displ[0], MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);



}


void LBNSCommunicator::gatherArray(
		int& count,
		std::vector<int>& data_size,
		std::vector<int>& data_displ,
		std::vector<double>& data){
	int rank=0;
	int com_size=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);

	MPI_Comm_size(MPI_COMM_WORLD,&com_size);
	if(data_size.size()==0){
		count=data.size();
		data_size.resize(1);
		if(rank==_maxSizeCommunicators[_index*2+1])
			data_size.resize(com_size);
		MPI_Gather(&count,1, MPI_INT, &data_size[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
		if(rank==_maxSizeCommunicators[_index*2+1]){
			data_displ.resize(com_size);

			data_displ[rank]=0;

			for(int i=0;i<com_size;i++){
				if(i!=rank){
					data_displ[i]=count;
					count+=data_size[i];
				}
			}
		}
	}
	data.resize(count);
	if(rank==_maxSizeCommunicators[_index*2+1])
		MPI_Gatherv(MPI_IN_PLACE,0, MPI_DOUBLE,&data[0], &data_size[0],&data_displ[0], MPI_DOUBLE,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
	else
		MPI_Gatherv(&data[0],count, MPI_DOUBLE,&data[0], &data_size[0],&data_displ[0], MPI_DOUBLE,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);



}

void LBNSCommunicator::gather(){
//	_logComm<<"gather:"<<_index<<std::endl;

	_velocityValues.clear();
	_velocityOffsets.clear();
	_velocityFlips.clear();
	_velocityKeys.clear();


	convertVelocity(_velocityKeys,_velocityOffsets,_velocityFlips,_velocityValues);

	gatherVelocity(_velocityKeys,_velocityOffsets,_velocityFlips,_velocityValues);
}
void LBNSCommunicator::gather_init(){
	int rank=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	_sizeCommunicators[_index*2]=_velocities.size();
	_sizeCommunicators[_index*2+1]=rank;

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

	//open();
	//	_logComm<<"i_j_k_index:"<<i
	//			<<" "<<j<<" "<<k
	//			<<" stencil:"<<stencilIndex
	//			<<" component:"<<component
	//			<<" index:"<<index
	//			<<" value:"<<velocity
	//			<<" mid:"<<_mid<<std::endl;

	LBNSData data;
	data.value=velocity;
	data.offset[0]=offset[0];
	data.offset[1]=offset[1];
	data.offset[2]=offset[2];
	data.flip[0]=flip[0];
	data.flip[1]=flip[1];
	data.flip[2]=flip[2];
	_velocities[index].push_back(data);
}
