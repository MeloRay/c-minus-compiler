#ifndef _ANALYZER_H
#define _ANALYZER_H
#include "globals.h"
#include "treenode.h"

class Analyzer {
private:
	int errorNum;

	void traverse(TreeNode* node);
	void checkNode(TreeNode* node);
	void typeError(const TreeNode* errorNode, const char* msg);
	void printNode(const TreeNode* node) const;
public:
	Analyzer():errorNum(0){}
	void typeCheck(TreeNode* root);
	void printTree(TreeNode* root) const;
	int getError() const {return errorNum;}
};

#endif