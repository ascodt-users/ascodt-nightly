#ifndef LB_NS_COMMUNICATOR
#define LB_NS_COMMUNICATOR
#include <string>
#include <hash_map>
#include "Parameters.h"
#include "cca/cfd/NSSolverCxx2SocketPlainPort.h"
#include <vector>
#include <fstream>
struct LBNSData{
	int offset[3];
	int flip[3];
	double value;
};
class LBNSCommunicator{
private:

	const Parameters & _parameters;
	std::string _mid;
	int _startIndex[3];
	int _endIndex[3];
	std::ofstream _logComm;
	bool _open;
	__gnu_cxx::hash_map<int,std::vector<LBNSData> > _velocities;
	cca::cfd::NSSolverCxx2SocketPlainPort *_lbnsPeer2Peer;
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
	int _index;
	std::vector<double> _velocityValues;
	std::vector<int> _velocityOffsets;
	std::vector<int> _velocityFlips;
	std::vector<int> _velocityKeys;
	int index2array ( int i, int j, int k, int component, int stencil ) const ;
	void connect();
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
	void open();
public:
	LBNSCommunicator(const Parameters & parameters,int index,
			int* start,int* end,std::string mid,
			std::vector<int>& maxSizeCommunicators,
			std::vector<int>& sizeCommunicators);
	~LBNSCommunicator();
	const bool isInside(int i, int j ,int k) const;

	void flush();
	void gather();
	void gather_init();
	void setDensity(
			int i,
			int j,
			int k,
			int stencilIndex,
			double value);
	void setVelocityComponent(
			int i,
			int j,
			int k,
			int stencilIndex,
			int component,
			const int* offset,
			const int* flip,
			double velocity);
};
#endif
