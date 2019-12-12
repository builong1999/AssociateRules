#ifndef _FILEREADER_H_
#define _FILEREADER_H_
#include <fstream>
#include <string>
#include <vector>
using namespace std;
class FileReader {
private:
	ifstream fileInput;
	vector<int>transactions;
	vector<int>Product;
	void GetTransaction();
public:
	FileReader(string filename);
	vector<int> GetTransactions();
	vector<int> getProduct();
};


#endif // _FILE_READER_