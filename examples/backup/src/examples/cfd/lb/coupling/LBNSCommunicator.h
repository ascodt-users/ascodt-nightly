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
	__gnu_cxx::hash_map<int,std::vector<LBNSData> > _velocities[3];
	cca::cfd::NSSolverCxx2SocketPlainPort *_lbnsPeer2Peer;
	int index2array ( int i, int j, int k, int component, int stencil ) const ;
	void connect();
	void convert(
			std::vector<int>& keys,
			std::vector<double>& values,
			std::vector<int>& offsets,
			std::vector<int>& flips,
			std::vector<int>& componentSize);
	void open();
public:
	LBNSCommunicator(const Parameters & parameters,int index,
			int* start,int* end,std::string mid);
	~LBNSCommunicator();
	const bool isInside(int i, int j ,int k) const;

	void flush();
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
