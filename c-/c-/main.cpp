#include "globals.h"
#include "parser.h"
#include "analyzer.h"
#include "generator.h"
#include <iostream>
using namespace std;

int main(int argc, const char * argv[]){
	if(argc >= 2 || argc <= 4) {
		Parser parser(argv[1]);
		Analyzer analyzer;

		TreeNode* root = parser.parse();
		analyzer.typeCheck(root);

		if(analyzer.getError()) {
			exit(1);
		}

		const char* name = "code.tm";
		if(argc == 3) {
			name = argv[2];	
		}
		Generator gen(name);
		gen.codeGen(root, parser.getGlobalScope());
		
		if(argc == 4 && strcmp(argv[3], "-p") == 0)
			analyzer.printTree(root);

		cout << "end....";
	}
	else
		cout << "Error: intput c- file name and the generated TM code name";

	return 0;
}