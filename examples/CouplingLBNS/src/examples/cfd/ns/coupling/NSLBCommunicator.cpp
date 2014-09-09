#include "NSLBCommunicator.h"
#include "CouplingDefinitions.h"
#include <sstream>
NSLBCommunicator::NSLBCommunicator(
		const Parameters & parameters,
		int index,
		int* start,
		int* end,
		std::string mid,
		std::vector<int>& maxSizeCommunicators,
		std::vector<int>& sizeCommunicators
):
_mid(mid),
_parameters(parameters),
_maxSizeCommunicators(maxSizeCommunicators),
_sizeCommunicators(sizeCommunicators)
{

	_startIndex[0]=start[index*3];
	_startIndex[1]=start[index*3+1];
	_startIndex[2]=start[index*3+2];

	_endIndex[0]=end[index*3];
	_endIndex[1]=end[index*3+1];
	_endIndex[2]=end[index*3+2];
	_nslbPeer2Peer=NULL;
	_index=index;
	_pressure_keys_count_sum =0;
	_pressure_offset_count_sum=0;
	_pressure_flips_count_sum=0;
	_pressure_count_sum = 0;
	_velocity_keys_count_sum=0;
	_velocity_offset_count_sum=0;
	_velocity_flips_count_sum=0;
	_velocity_count_sum=0;
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

void NSLBCommunicator::gather_init(
){
	int rank=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	_sizeCommunicators[_index*2]=_pressure.size();
	_sizeCommunicators[_index*2+1]=rank;

}
//
//void NSLBCommunicator::greedy_gather_init_v(
//		int* maxSizeCommunicators,
//		int* sizeCommunicators
//){
//	if(maxSizeCommunicators[1]==_parameters.parallel.rank){
//		_data_cout.resize(_parameters.parallel.numberOfRanks);
//	}else
//		_data_cout.resize(1);
//	_data_cout[0]=sizeCommunicators[0];
//	_sum=data_cout[0];
//	MPI_Gather(&_data_cout[0], 1, MPI_INT, &_data_cout[0], 1, MPI_INT,maxSizeCommunicators[1], MPI_COMM_WORLD);
//	if(maxSizeCommunicators[index].rank=_parameters.parallel.rank){
//
//		data_displ[0]=0;
//		for(int i=1;i<_parameters.parallel.numberOfRanks;i++){
//			_data_displ[i]=_sum;
//			_sum+=_data_cout[i];
//		}
//	}
//}



void NSLBCommunicator::gatherVelocityInit(){
	if(_velocity_count.size()==0){
		std::vector<int> sendBuffer_count(1);
		std::vector<int> sendBuffer_offset_count(1);
		std::vector<int> sendBuffer_flips_count(1);
		std::vector<int> sendBuffer_keys_count(1);
		_velocity_keys_count.resize(1);
		_velocity_offset_count.resize(1);
		_velocity_flips_count.resize(1);
		_velocity_count.resize(1);
		int rank=0;
		MPI_Comm_rank(MPI_COMM_WORLD,&rank);
		int com_size=0;
		MPI_Comm_size(MPI_COMM_WORLD,&com_size);
		if(_maxSizeCommunicators[_index*2+1]==rank){
			_velocity_keys_count.resize(com_size);
			_velocity_offset_count.resize(com_size);
			_velocity_flips_count.resize(com_size);
			_velocity_count.resize(com_size);

			_velocity_displ.resize(com_size);
			_velocity_keys_displ.resize(com_size);
			_velocity_offset_displ.resize(com_size);
			_velocity_flips_displ.resize(com_size);

		}
		_velocity_count[0]=_velocities.size();
		_velocity_offset_count[0]=_velocities.size()*3;
		_velocity_flips_count[0]=_velocities.size()*3;
		_velocity_keys_count[0]=_velocities.size();

		sendBuffer_count[0]=_velocities.size();
		sendBuffer_offset_count[0]=_velocities.size()*3;
		sendBuffer_flips_count[0]=_velocities.size()*3;
		sendBuffer_keys_count[0]=_velocities.size();
		MPI_Gather(&sendBuffer_count[0],1, MPI_INT, &_velocity_count[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
		MPI_Gather(&sendBuffer_keys_count[0], 1, MPI_INT, &_velocity_keys_count[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
		MPI_Gather(&sendBuffer_flips_count[0], 1, MPI_INT, &_velocity_flips_count[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
		MPI_Gather(&sendBuffer_offset_count[0], 1, MPI_INT, &_velocity_offset_count[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);

		_velocity_keys_count_sum+=_velocities.size();
		_velocity_offset_count_sum+=_velocities.size()*3;
		_velocity_flips_count_sum+=_velocities.size()*3;
		_velocity_count_sum+=_velocities.size();

		if(_maxSizeCommunicators[_index*2+1]==rank){

			_velocity_displ[rank]=0;
			_velocity_keys_displ[rank]=0;
			_velocity_offset_displ[rank]=0;
			_velocity_flips_displ[rank]=0;
			//			_velocity_count[rank]=0;
			//			_velocity_offset_count[rank]=0;
			//			_velocity_flips_count[rank]=0;
			//			_velocity_keys_count[rank]=0;
			for(int i=0;i<com_size;i++){
				if(i!=rank){
					_velocity_displ[i]=_velocity_count_sum;
					_velocity_keys_displ[i]=_velocity_keys_count_sum;
					_velocity_offset_displ[i]=_velocity_offset_count_sum;
					_velocity_flips_displ[i]=_velocity_flips_count_sum;
					_velocity_keys_count_sum+=_velocity_keys_count[i];
					_velocity_offset_count_sum+=_velocity_offset_count[i];
					_velocity_flips_count_sum+=_velocity_flips_count[i];
					_velocity_count_sum+=_velocity_count[i];
				}

			}
			//			_velocity_keys_count[rank]=0;
			//			_velocity_offset_count[rank]=0;
			//			_velocity_flips_count[rank]=0;
			//			_velocity_count[rank]=0;
		}

	}
	//	_sum=data_cout[0];


}
void NSLBCommunicator::gatherPressureInit(){
	if(_pressure_count.size()==0){
		std::vector<int> sendBuffer_count(1);
		std::vector<int> sendBuffer_offset_count(1);
		std::vector<int> sendBuffer_flips_count(1);
		std::vector<int> sendBuffer_keys_count(1);
		_pressure_keys_count.resize(1);
		_pressure_offset_count.resize(1);
		_pressure_flips_count.resize(1);
		_pressure_count.resize(1);
		int rank=0;
		MPI_Comm_rank(MPI_COMM_WORLD,&rank);
		int com_size=0;
		MPI_Comm_size(MPI_COMM_WORLD,&com_size);
		if(_maxSizeCommunicators[_index*2+1]==rank){
			_pressure_keys_count.resize(com_size);
			_pressure_offset_count.resize(com_size);
			_pressure_flips_count.resize(com_size);
			_pressure_count.resize(com_size);

			_pressure_displ.resize(com_size);
			_pressure_keys_displ.resize(com_size);
			_pressure_offset_displ.resize(com_size);
			_pressure_flips_displ.resize(com_size);

		}


		sendBuffer_count[0]=_pressure.size();
		sendBuffer_offset_count[0]=_pressure.size()*3;
		sendBuffer_flips_count[0]=_pressure.size()*3;
		sendBuffer_keys_count[0]=_pressure.size();
		_pressure_keys_count[0]=_pressure.size();
		_pressure_offset_count[0]=_pressure.size()*3;
		_pressure_flips_count[0]=_pressure.size()*3;
		_pressure_count[0]=_pressure.size();

		MPI_Gather(&sendBuffer_count[0], 1, MPI_INT, &_pressure_count[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
		MPI_Gather(&sendBuffer_keys_count[0], 1, MPI_INT, &_pressure_keys_count[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
		MPI_Gather(&sendBuffer_flips_count[0],1, MPI_INT, &_pressure_flips_count[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);
		MPI_Gather(&sendBuffer_offset_count[0], 1, MPI_INT, &_pressure_offset_count[0], 1, MPI_INT,_maxSizeCommunicators[_index*2+1], MPI_COMM_WORLD);

		_pressure_keys_count_sum+=_pressure.size();
		_pressure_offset_count_sum+=_pressure.size()*3;
		_pressure_flips_count_sum+=_pressure.size()*3;
		_pressure_count_sum+=_pressure.size();

		if(_maxSizeCommunicators[_index*2+1]==rank){
			_pressure_displ[rank]=0;
			_pressure_keys_displ[rank]=0;
			_pressure_offset_displ[rank]=0;
			_pressure_flips_displ[rank]=0;
			//			_pressure_count[rank]=0;
			//			_pressure_keys_count[rank]=0;
			//			_pressure_offset_count[rank]=0;
			//			_pressure_flips_count[rank]=0;
			std::cout<<"disp pressure on com:"<<_index<<"[["<<_pressure_displ[0]<<","<<_pressure_count[0]<<"]";
			for(int i=0;i<com_size;i++){
				if(i!=rank){
					_pressure_displ[i]=_pressure_count_sum;
					_pressure_keys_displ[i]=_pressure_keys_count_sum;
					_pressure_offset_displ[i]=_pressure_offset_count_sum;
					_pressure_flips_displ[i]=_pressure_flips_count_sum;
					_pressure_keys_count_sum+=_pressure_keys_count[i];
					_pressure_offset_count_sum+=_pressure_offset_count[i];
					_pressure_flips_count_sum+=_pressure_flips_count[i];
					_pressure_count_sum+=_pressure_count[i];
				}
				std::cout<<",["<<_pressure_displ[i]<<","<<_pressure_count[i]<<"]";
			}

			std::cout<<"]"<<std::endl;
		}
	}
	//	_sum=data_cout[0];


}
void NSLBCommunicator::gatherVelocity(
		std::vector<int>& keys,
		std::vector<int>& offset,
		std::vector<int>& flips,
		std::vector<double>& velocities)
{

	gatherArray(_velocity_keys_count_sum,_velocity_keys_count,_velocity_keys_displ,keys);
	gatherArray(_velocity_flips_count_sum,_velocity_flips_count,_velocity_flips_displ,flips);
	gatherArray(_velocity_offset_count_sum,_velocity_offset_count,_velocity_offset_displ,offset);
	gatherArray(_velocity_count_sum,_velocity_count,_velocity_displ,velocities);

}

void NSLBCommunicator::gatherArray(
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


void NSLBCommunicator::gatherArray(
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

void NSLBCommunicator::gatherPressure(
		std::vector<int>& keys,
		std::vector<int>& offset,
		std::vector<int>& flips,
		std::vector<double>& pressure){
	gatherArray(_pressure_keys_count_sum,_pressure_keys_count,_pressure_keys_displ,keys);
	gatherArray(_pressure_flips_count_sum,_pressure_flips_count,_pressure_flips_displ,flips);
	gatherArray(_pressure_offset_count_sum,_pressure_offset_count,_pressure_offset_displ,offset);
	gatherArray(_pressure_count_sum,_pressure_count,_pressure_displ,pressure);

	std::cout<<"end gathering pressure:"<<_pressure_count_sum<<std::endl;

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
	std::cout<<"mid"<<_mid<<std::endl;
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


void NSLBCommunicator::convertVelocity(
		std::vector<int>& keysVelocity,
		std::vector<int>& velocityOffsets,
		std::vector<int>& velocityFlips,
		std::vector<double>& velocityValues

){
	__gnu_cxx::hash_map<int,std::vector<NSLBData> >::iterator it;
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
			_couplingData.push_back((*it).second[i].value);
		}
	}

}

void NSLBCommunicator::convertPressure(
		std::vector<int>& keysPressure,
		std::vector<int>& pressureOffsets,
		std::vector<int>& pressureFlips,
		std::vector<double>& pressureValues
){
	__gnu_cxx::hash_map<int,std::vector<NSLBData> >::iterator it;
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
			_couplingDataSecondary.push_back((*it).second[i].value);
		}
	}

}
void NSLBCommunicator::gather(){

	_velocityValues.clear();
	_velocityOffsets.clear();
	_velocityFlips.clear();
	_keysVelocity.clear();

	_pressureValues.clear();
	_keysPressure.clear();
	_pressureOffsets.clear();
	_pressureFlips.clear();

	convertPressure(_keysPressure,_pressureOffsets,_pressureFlips,_pressureValues);
	gatherPressure(_keysPressure,_pressureOffsets,_pressureFlips,_pressureValues);
	convertVelocity(_keysVelocity,_velocityOffsets,_velocityFlips,_velocityValues);
	gatherVelocity(_keysVelocity,_velocityOffsets,_velocityFlips,_velocityValues);
}
void NSLBCommunicator::flush(){
	//_logComm.flush();




	std::cout<<"converted"<<std::endl;
	int rank=0;
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	if(_maxSizeCommunicators[_index*2+1]==rank){
		connect();

		int ack=0;
		_nslbPeer2Peer->forwardVelocities(
				&_keysVelocity[0],
				_keysVelocity.size(),
				&_velocityOffsets[0],
				_velocityOffsets.size(),
				&_velocityFlips[0],
				_velocityFlips.size(),
				&_velocityValues[0],
				_velocityValues.size(),
				ack
		);
		std::cout<<"forw pressure"<<std::endl;
		_nslbPeer2Peer->forwardPressure(
				&_keysPressure[0],
				_keysPressure.size(),
				&_pressureOffsets[0],
				_pressureOffsets.size(),
				&_pressureFlips[0],
				_pressureFlips.size(),
				&_pressureValues[0],
				_pressureValues.size(),
				ack
		);

	}
	_velocities.clear();
	_pressure.clear();
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
	_velocities[index].push_back(data);


	//		_logComm<<"i_j_k_index:"<<i
	//				<<" "<<j<<" "<<k
	//				<<" stencil:"<<stencilIndex
	//				<<" component:"<<component
	//				<<" index:"<<index
	//				<<" value:"<<velocity
	//				<<" mid:"<<_mid<<std::endl;


}
