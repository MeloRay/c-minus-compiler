#ifndef _PARSER_H
#define _PARSER_H
#include "globals.h"
#include "scan.h"
#include "symtable.h"
#include "funtable.h"
#include "treenode.h"


class Parser {
private:
	Scan scan;
	FunTable funTable;
	SymTable* globalScope;

	void pushScope(int flag = 0);	//遇到“{”压入新的符号表，flag = 1代表是函数，flag = 0 代表普通嵌套语句
	void popScope();	//遇到“}”弹出栈顶符号表
	void match(TokenType expectd);

	/**************以下为状态机********************************/
	TreeNode* program();
	void varDec();	//变量定义
	TreeNode* funDec(VarType varType);
	void param();	
	TreeNode* stmtList();
	TreeNode* stmt();
	TreeNode* expStmt();
	TreeNode* exp();
	TreeNode* iteStmt();
	TreeNode* retStmt();
	TreeNode* ifStmt();
	TreeNode* comStmt(int flag = 0);//1代表是函数定义，0代表普通嵌套语句
	TreeNode* arrayExp();
	TreeNode* simpleExp(TreeNode* leftOp = NULL);
	TreeNode* additiveExp(TreeNode* leftOp = NULL);
	TreeNode* call();
	TreeNode* term(TreeNode* leftOp = NULL);
	TreeNode* factor(TreeNode* leftOp = NULL);
	/*****************************************************************/
public:
	Parser(const char* fileName);
	TreeNode* parse();
	void syntaxError(const char* msg = NULL) const;
	void printTree(const TreeNode* node) const;
	const SymTable* getGlobalScope() const {return globalScope;}
};

#endif