#ifndef NS_LB_COMMUNICATOR
#define NS_LB_COMMUNICATOR
#include <string>
#include <unordered_map>
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
	std::unordered_map<int,std::vector<NSLBData> > _velocities[3];
	std::unordered_map<int,std::vector<NSLBData> > _pressure;

	cca::cfd::LBSolverCxx2SocketPlainPort *_nslbPeer2Peer;
	int index2Varray ( int i, int j, int k, int component, int stencil ) const ;
	int index2Parray ( int i, int j, int k, int stencil ) const ;
	void connect();
	void convert(
			std::vector<int>& keysVelocity,
			std::vector<int> &velocityOffsets,
			std::vector<int> &velocityFlips,
			std::vector<double>& velocityValues,
			std::vector<int>& componentSize,
			std::vector<int>& keysPressure,
			std::vector<int> &pressureOffsets,
			std::vector<int> &pressureFlips,
			std::vector<double>& pressureValues);
public:
	NSLBCommunicator(const Parameters & parameters,int index,
			int* start,int* end,std::string mid);
	~NSLBCommunicator();
	const bool isInside(
			const int i,const int j , const int k) const;

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
