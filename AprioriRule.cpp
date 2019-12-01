#include "AprioriRule.h"

AprioriRule::~AprioriRule() {
}
AprioriRule::AprioriRule(vector<vector<int>> _transactions, vector<int> _product, int tPeerB, int Cores, long double _minSp, long double _minConfi)
{
	startTime = clock();
	Step = 0;
	minSuport = _minSp;
	minConfin = _minConfi;
	Product = _product;
	defineThread = tPeerB;
	defineCores = Cores;
	frequentItemsets.push_back({ {} });
	tranSize = _transactions.size();

	for (auto &row : _transactions)
	{
		transactions.push_back(row);
	}
	printf("%f\tLoad Data\n", clock() - startTime);
}
vector<tuple<vector<int>, vector<int>, long double, long double>> AprioriRule::getResult()
{
	return AprioriRules;
}
void AprioriRule::Process()
{
	for (auto i = Product.begin(); i != Product.end(); i++)
		C.push_back(vector<int>(1, *i));
	Step++;
	L = generateNewL();
	frequentItemsets.push_back(L);

	while (true)
	{
		printf("-Step %d -> %f\n", Step, clock() - startTime);
		C = generateNextC();
		if (C.size() == 0)
			break;
		Step++;
		L = generateNewL();

		frequentItemsets.push_back(L);
	}
	printf("Start check frequent Itemset %f\n", clock() - startTime);
	
	for (auto &ItemSet : frequentItemsets)
	{
		// Parallel here
		for (auto &items : ItemSet)
		{
			generateAssociationRule(items, {}, {}, 0, minConfin);
		}
	}
	printf("Frequent Itemset Done. Start write output %f\n", clock() - startTime);
}

void AprioriRule::generateAssociationRule(vector<int> items, vector<int> X, vector<int> Y, int index, long double minConfi) {
	if (index == items.size()) {
		if (X.size() == 0 || Y.size() == 0) return;
		long double XYsupport = getSupport(getIndex( items));
		long double Xsupport = getSupport(getIndex(X));

		if (Xsupport == 0) return;

		long double support = (long double)XYsupport;
		long double confidence = (long double)XYsupport / Xsupport * 100.0;
		if (confidence >= minConfi)
			AprioriRules.push_back({ X, Y, support, confidence });
		return;
	}

	X.push_back(items[index]);
	generateAssociationRule(items, X, Y, index + 1, minConfi);
	X.pop_back();
	Y.push_back(items[index]);
	generateAssociationRule(items, X, Y, index + 1, minConfi);
}



vector<vector<int>> AprioriRule::generateNextC() {
	printf("---Generate C:\t%f \t->", clock() - startTime);
	vector<vector<int>> temp;
	int Lsize = L.size();
	for (int i = 0; i < Lsize; i++) {
		// MAYBE
		for (int j = i + 1; j < Lsize; j++) {
			int k;
			for (k = 0; k < Step - 1; k++)
				if (L[i][k] != L[j][k]) break;
			if (k == Step - 1) {
				vector<int> ret;
				for (int h = 0; h < Step - 1; h++)
					ret.push_back(L[i][h]);
				int f = L[i][Step - 1];
				int s = L[j][Step - 1];
				if (f > s) swap(f, s);
				ret.push_back(f), ret.push_back(s);
				temp.push_back(ret);
			}
		}
	}
	vector<vector<int>> temps;
	set<vector<int>> LSet;
	for (auto&row : L) 
		LSet.insert(row);
	for (auto&row : temp) {
		//MAYBE
		int i, size = row.size();
		for (i = 0; i < size; i++) {
			vector<int> tmp = row;
			tmp.erase(tmp.begin() + i);
			if (LSet.find(tmp) == LSet.end())
				break;
		}
		if (i == size)
			temps.push_back(row);
	}

	printf("%f\n", clock() - startTime);
	return temps;
}
vector<vector<int>> AprioriRule::generateNewL() {
	printf("---Generate L:\t%f \t->", clock() - startTime);
	vector<vector<int>> ret;
	for (auto&row : C) {
		long double sp = getSupport(getIndex(row));
		if (sp < minSuport) continue;
		ret.push_back(row);
	}
	printf("%f\n", clock() - startTime);
	return ret;
}

vector<int> AprioriRule::getIndex(vector<int> row) {
	vector<int> temp;

	for (int i = 0, j = 0; j < row.size(); i++) {
		if (Product[i] == row[j]) {
			temp.push_back(i);
			j++;
		}
	}
	return temp;
}


long double AprioriRule::getSupport(vector<int> item) {
	int count = 0;

	bool boo;
	for (auto&row : transactions) {
		boo = true;
		for (int i = 0; i < item.size(); i++) {
			if (row[item[i]] == 0) {
				boo = false;
				break;
			}
		}
		if (boo) {
			count++;
		}
	}

	return (long double)count / tranSize * 100;
}