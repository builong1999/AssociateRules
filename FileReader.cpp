
#include "FileReader.h"
FileReader::FileReader(string filename) {
	fileInput.open(filename);
	if (!fileInput) {
		printf("Input file could not be opened\n");
		exit(0);
	}
	GetTransaction();
}

void FileReader::GetTransaction() {
	string str;
	getline(fileInput,str);
	int split_pos = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] == ',') {
			int num = atoi(str.substr(split_pos, i).c_str());
			Product.push_back(num);
			split_pos = i + 1;
		}
	}
	int num = atoi(str.substr(split_pos, str.size()).c_str());
	Product.push_back(num);
	while (!getline(fileInput, str).eof()) {
		vector<int>arr;
		split_pos = 0;
		int _size = str.size();
		for (int i = 0; i < _size; i++) {
			if (str[i] == ',') {
				int num = atoi(str.substr(split_pos, i).c_str());
				arr.push_back(num);
				split_pos = i + 1;
			}
		}
		int num = atoi(str.substr(split_pos, _size).c_str());
		arr.push_back(num);
		transactions.push_back(arr);
	}
}
vector<vector<int>> FileReader::GetTransactions() {
	return transactions;
}
vector<int> FileReader::getProduct() {
	return Product;
}
