#ifndef _TREENODE_H
#define _TREENODE_H
#include "globals.h"
#include "symtable.h"
#include "funtable.h"

struct TreeNode{
	NodeKind nodeKind;
	union {
		TokenType op; /* operation node: '+', '-', '*', '\', '==', '<=', '<', '>', '>='*/
		int val; /* the value of const */
		SymTable* scope; /* symbol table */
		BucketList* varInfo;
		FunList* funInfo;
	} attr;
	const char* name;
	VarType varType;
	const int lineNo;
	TreeNode* sibling;
	TreeNode** child;
	int childNum;

	TreeNode(const char* name, int lineNo, int childNum = 1):name(name), 
		lineNo(lineNo), sibling(NULL), childNum(childNum), varType(Undef){
		if(childNum != 0) {
			child = new TreeNode*[childNum];
			for(int i = 0; i < childNum; i++)
				child[i] = NULL;
		}
	}

	void setOp(TokenType op) {this->attr.op = op;}
	void setVal(int val) {this->attr.val = val;}
	void setScope(SymTable* scope) {this->attr.scope = scope;}
	void setVarType(VarType varType) {this->varType = varType;}
	void setNodeKind(NodeKind nodeKind) {this->nodeKind = nodeKind;}
	void setVarInfo(BucketList* varInfo) {this->attr.varInfo = varInfo;}
	void setFunInfo(FunList* funInfo) {this->attr.funInfo = funInfo;}
	BucketList* getVarInfo() const {return attr.varInfo;}
	FunList* getFunInfo() const {return attr.funInfo;}
	NodeKind getNodeKind() const {return nodeKind;}
	TokenType getOp() const {return attr.op;}
	int getVal() const {return attr.val;}
	SymTable* getScope() const {return attr.scope;}
	VarType getVarType() const {return varType;}
	int getLineNo() const {return lineNo;}
	const int getChildNum() const {return childNum;}
	const char* getName() const {return name;}

	~TreeNode() {
		if(childNum != 0)
			delete[] child;
	}
};

#endif
