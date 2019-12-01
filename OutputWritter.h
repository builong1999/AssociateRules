#ifndef _OUTPUTWRITTER_H_
#define _OUTPUTWRITTER_H_
#include <fstream>
#include <vector>
using namespace std;
class OutputWritter
{
private:
	ofstream fileOutput;
	vector < tuple<vector<int>, vector<int>, long double, long double>> AprioriRules;
public:
	OutputWritter(string filename, vector < tuple<vector<int>, vector<int>, long double, long double>> _ARules);
	string toString(vector<int>arr);
};
#endif