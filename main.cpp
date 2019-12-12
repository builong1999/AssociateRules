
#include "FileReader.h"
#include "OutputWritter.h"
#include "AprioriRule.h"

int main(int arg, char**argv)
{
	if (arg != 6){
		printf("The arguments run program must be 6"); exit(0);
	}
	double startTime = clock();
	printf("%f\tStart Execute\n", startTime - startTime);
	string input = string(argv[1]);
	double spThreshold = atof(argv[2]);
	double cfThreshold = atof(argv[3]);
	double numThreadPeerblock = atof(argv[4]);
	double numCores = atof(argv[5]);
	string output = "output.txt";
	FileReader InputReader(input);
	vector<int> transactions = InputReader.GetTransactions();
	vector<int> _product = InputReader.getProduct();
	AprioriRule aprioriRules(transactions,_product, numThreadPeerblock, numCores, spThreshold, cfThreshold);
	printf("Start analyst\n", clock()-startTime);
	aprioriRules.Process();
	printf("%f\tEnd Execute\n", clock() - startTime);
	OutputWritter _Output(output, aprioriRules.getResult());
	return 0;
}
