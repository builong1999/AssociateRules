
#include "OutputWritter.h"
#include <iostream>
#include <tuple>
#include <string>

OutputWritter::OutputWritter(string filename, vector < tuple<vector<int>, vector<int>, long double, long double>> _ARules) {
	fileOutput.open(filename);
	if (!fileOutput) {
		cout << "Output file could not be opened\n";
		exit(0);
	}
	AprioriRules = _ARules;
	int size = _ARules.size();
	fileOutput << _ARules.size() << " Associate Rules (Apriori)\n";
	printf("%d Associate Rules (Apriori)\n", size);
	for (auto&index : AprioriRules) {
		fileOutput << "( " << toString(get<0>(index)) << ")  ->  ";
		fileOutput << "( " << toString(get<1>(index)) << ")  \t";
		fileOutput << "{-Support Threshold: " << get<2>(index) << "\t Confidence Threshold: ";
		fileOutput << get<3>(index) << "}\n";
	}
}


string OutputWritter::toString(vector<int>arr) {
	string temp = "";
	for (int i = 0; i < arr.size(); i++) {
		temp += to_string(arr[i]);
		if (i != arr.size() - 1) {
			temp += ",";
		}
	}
	return temp;
}
