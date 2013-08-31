#ifndef _GENERATOR_H
#define _GENERATOR_H
#include "globals.h"
#include "treenode.h"
#include "symtable.h"
#include <fstream>

class Generator {
private:
	std::ofstream out;
	bool traceCode;

	void nodeGen(const TreeNode* node);
	void emitComment(const char* comment, const TreeNode* node = NULL);
	void emitRM(const char* op, int r, int d, int s, const char* comment);
	void emitRO(const char* op, int r, int s, int t, const char* comment);
	void emitRM_Abs(const char* op, int r, int a, const char* comment);
public:
	Generator(const char* fileName);
	void codeGen(const TreeNode* root, const SymTable* globalScope);
	void openTrace() {traceCode = true;}
	void closeTrace() {traceCode = false;}
};

#endif