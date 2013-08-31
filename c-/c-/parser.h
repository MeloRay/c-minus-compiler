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

	void pushScope(int flag = 0);	//������{��ѹ���µķ��ű�flag = 1�����Ǻ�����flag = 0 ������ͨǶ�����
	void popScope();	//������}������ջ�����ű�
	void match(TokenType expectd);

	/**************����Ϊ״̬��********************************/
	TreeNode* program();
	void varDec();	//��������
	TreeNode* funDec(VarType varType);
	void param();	
	TreeNode* stmtList();
	TreeNode* stmt();
	TreeNode* expStmt();
	TreeNode* exp();
	TreeNode* iteStmt();
	TreeNode* retStmt();
	TreeNode* ifStmt();
	TreeNode* comStmt(int flag = 0);//1�����Ǻ������壬0������ͨǶ�����
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