#ifndef _APRIORIRULE_H_
#define _APRIORIRULE_H_
#include <iomanip>
#include <set>
#include <tuple>
#include <cmath>
#include <string>
#include <vector>
#include <algorithm> // std::sort
#include <math.h>
#include <time.h>
#include <mutex>
#include <thread>
using namespace std;
class AprioriRule
{
private:
	int peerSize;
	int Step;
	long double minSuport;
	long double minConfin;
	int defineThread;
	int defineCores;
	int tranSize;
	int* _transactions_, *_lCount_, *_countC;
	double startTime;
	mutex Block;
	vector<int>Product;
	vector<vector<int>> transactions;
	vector<vector<int>> C, L;
	vector<vector<vector<int>>> frequentItemsets;
	vector<tuple<vector<int>, vector<int>, long double, long double>> AprioriRules;
	void generateAssociationRule(vector<int> items, vector<int> X, vector<int> Y, int index, long double minConfi);
	vector<vector<int>> concatenate(vector<vector<int>> joini);
	vector<vector<int>> join();
	vector<vector<int>> generateNextC();
	vector<vector<int>> generateNewL();
	long double getSupport(vector<int> item);
	vector<int> getIndex(vector<int> row);
	void generateCParallel1(int start, int loop, int Lsize, vector<vector<int>> &temp );
	void generateCParallel2(int start, int loop, set<vector<int>> LSet, vector<vector<int>> &temps, vector<vector<int>> temp);
	void generateLParallel(int start, int loop, vector<vector<int>> &ret);
	void generateCSet(int start, int loop, set<vector<int>> &Lset);
	void parallelFrequent(int start, int loop);
public:
	AprioriRule(vector<vector<int>> _transactions, vector<int>, int tPeerB, int Cores, long double _minSp, long double _minConfi = 0.0);
	vector<tuple<vector<int>, vector<int>, long double, long double>> getResult();
	void Process();
	~AprioriRule();
};
#endif