#ifndef NS_LB_COMMUNICATOR
#define NS_LB_COMMUNICATOR
#include <string>
#include <hash_map>
#include "Parameters.h"
#include "cca/cfd/LBSolverCxx2SocketPlainPort.h"
#include <vector>
#include <fstream>
struct NSLBData{
	int offset[3];
	int flip[3];
	double value;
};
class NSLBCommunicator{
private:

	const Parameters & _parameters;
	std::string _mid;
	int _startIndex[3];
	int _endIndex[3];
	int _index;
	std::vector<double> _couplingData;
	std::vector<double> _couplingDataSecondary;
	__gnu_cxx::hash_map<int,std::vector<NSLBData> > _velocities;
	__gnu_cxx::hash_map<int,std::vector<NSLBData> > _pressure;

	cca::cfd::LBSolverCxx2SocketPlainPort *_nslbPeer2Peer;
	std::vector<int>& _maxSizeCommunicators;
	std::vector<int>& _sizeCommunicators;

	std::vector<int> _velocity_keys_count;
	std::vector<int> _velocity_keys_displ;
	int _velocity_keys_count_sum;

	std::vector<int> _velocity_flips_count;
	std::vector<int> _velocity_flips_displ;
	int _velocity_flips_count_sum;

	std::vector<int> _velocity_offset_count;
	std::vector<int> _velocity_offset_displ;
	int _velocity_offset_count_sum;

	std::vector<int> _velocity_count;
	std::vector<int> _velocity_displ;
	int _velocity_count_sum;

	std::vector<int> _pressure_keys_count;
	std::vector<int> _pressure_keys_displ;
	int _pressure_keys_count_sum;

	std::vector<int> _pressure_flips_count;
	std::vector<int> _pressure_flips_displ;
	int _pressure_flips_count_sum;

	std::vector<int> _pressure_offset_count;
	std::vector<int> _pressure_offset_displ;
	int _pressure_offset_count_sum;

	std::vector<int> _pressure_count;
	std::vector<int> _pressure_displ;
	int _pressure_count_sum;

	int index2Varray ( int i, int j, int k, int component, int stencil ) const ;
	int index2Parray ( int i, int j, int k, int stencil ) const ;
	void connect();
	void convertPressure(
			std::vector<int>& keys,
			std::vector<int>& flips,
			std::vector<int>& offset,
			std::vector<double>& pressure);
	void convertVelocity(
			std::vector<int>& keys,
			std::vector<int>& flips,
			std::vector<int>& offset,
			std::vector<double>& velocities);
	void gatherVelocity(
			std::vector<int>& keys,
			std::vector<int>& flips,
			std::vector<int>& offset,
			std::vector<double>& velocities);
	void gatherPressure(
			std::vector<int>& keys,
			std::vector<int>& flips,
			std::vector<int>& offset,
			std::vector<double>& pressure);
	void gatherPressureInit();
	void gatherVelocityInit();
	void gatherArray(
			int& count,
			std::vector<int>& data_size,
			std::vector<int>& data_displ,
			std::vector<int>& data);
	void gatherArray(
				int& count,
				std::vector<int>& data_size,
				std::vector<int>& data_displ,
				std::vector<double>& data);
	std::vector<double> _velocityValues;
	std::vector<int> _velocityOffsets;
	std::vector<int> _velocityFlips;
	std::vector<int> _keysVelocity;

	std::vector<double> _pressureValues;
	std::vector<int> _keysPressure;
	std::vector<int> _pressureOffsets;
	std::vector<int> _pressureFlips;


public:
	NSLBCommunicator(
			const Parameters & parameters,
			int index,
			int* start,
			int* end,
			std::string mid,
			std::vector<int>& maxSizeCommunicators,
			std::vector<int>& sizeCommunicators
	);
	std::vector<double>& getCouplingData(){
		return _couplingData;
	}
	std::vector<double>& getSecondaryCouplingData(){
			return _couplingDataSecondary;
	}
	~NSLBCommunicator();
	const bool isInside(
			const int i,const int j , const int k) const;

	void gather_init();
	void gather();
	void flush();
	void setPressure(
			int i,
			int j,
			int k,
			int stencilIndex,
			const int *  const offset, const int * const flip,
			double value);
	void setVelocityComponent(
			const int i,
			const int j,
			const int k,
			const int stencilIndex,
			const int component,
			const int *  const offset, const int * const flip,
			const double velocity);
};
#endif
