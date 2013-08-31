#include "parser.h"
#include <stack>
#include <iostream>
using namespace std;

static TokenType token;
static SymTable* topScope;
static stack<SymTable*> scope;
static int lineNo;
static const char* name;

void Parser::match(TokenType expected) {
	if(token == expected) {
		token = scan.getToken();
	}
	else {
		syntaxError();
	}
}

void Parser::syntaxError(const char* msg) const {
	cout << "Line " << scan.getLineNo() << ": "
		<< "Unexpected token \"" << scan.getTokenString() << "\". ";
	if(msg != NULL)
		cout << "->" << msg;
	cout << endl;
	exit(1);
}

Parser::Parser(const char* fileName):scan(Scan(fileName)){
	globalScope = new SymTable(0, true);
	scope.push(globalScope);
	topScope = scope.top();
	token = scan.getToken();

	//插入input，output函数
	funTable.insert("input", Integer);
	auto it = funTable.insert("output", Void);
	funTable.insertParam(it, "val", Integer);

	FunList* fun = funTable.find("input");
	fun->setLoc(3);
	fun = funTable.find("output");
	fun->setLoc(8);
}

void Parser::pushScope(int flag) {
	SymTable* newScope;
	if(flag == 0) {
		newScope = new SymTable(scope.top()->getTotalOffset());
		newScope->setParent(scope.top());
	}
	//如果是函数，压入新的fp指针，所以栈顶offset初始化为0
	else
		newScope = new SymTable(0);

	newScope->setPre(scope.top());
	
	scope.push(newScope);
	topScope = scope.top();
}

void Parser::popScope() {
	scope.pop();
	topScope = scope.top();
}

TreeNode* Parser::parse() {
	TreeNode* root = program();
	if(token != ENDFILE)
		cout << "Code ends before file" << endl; 

	FunList* mainFun = funTable.find("main");
	if(mainFun == NULL) {
		cout << "No definition of \'main\'" << endl;
		exit(1);
	}
	else {
		if(mainFun->getParamNum()) {
			cout << "param of \'main\' function should be void" << endl;
			exit(1);
		}
	}

	cout << "parse finished..." << endl;

	return root;
}

TreeNode* Parser::program() {
	TreeNode* front = NULL;
	TreeNode* back = NULL;

	while(token != ENDFILE) {
		TreeNode* newNode = NULL;
		
		//void 只能为函数返回值
		if(token == VOID) {
			match(VOID);
			name = scan.getTokenString();
			lineNo = scan.getLineNo();
			match(ID);
			newNode = funDec(Void);
		}
		else if(token == INT) {
			match(INT);
			name = scan.getTokenString();
			lineNo = scan.getLineNo();
			match(ID);

			//定义整数
			if(token == SEMI) {
				if(topScope->isExist(name) == false) {
					topScope->insert(name, Integer, 1);
					match(SEMI);
				}
				else
					syntaxError("Multiple definition variable!");
			}
			//定义数组
			else if(token == LBRACKET) {
				int size;
				match(LBRACKET);

				if(token == NUM)
					size = atoi(scan.getTokenString());
				else
					syntaxError();

				match(NUM);
				
				if(topScope->isExist(name) == false) {
					topScope->insert(name, Array, size);
					match(RBRACKET);
					match(SEMI);
				}
				else 
					syntaxError("Multiple definition variable!");
			}
			//定义函数
			else if(token == LPAREN) {
				newNode = funDec(Integer);
			}
			else
				syntaxError();
		}
		else 
			syntaxError();
		

		if(newNode != NULL) {
			if(front == NULL) {
				front = newNode;
				back = newNode;
			}
			else
				back->sibling = newNode;

			back = newNode;
		}
	}


	return front;
}

//变量定义从int开始，匹配完分号
void Parser::varDec() {
	match(INT);
	name = scan.getTokenString();
	match(ID);
	if(token == SEMI) {
		if(topScope->isExist(name) == false) {
			topScope->insert(name, Integer, 1);
			match(SEMI);
		}
		else
			syntaxError("Multiple definition variable!");
	}
	else if(token == LBRACKET) {
		int size;
		match(LBRACKET);

		if(token == NUM)
			size = atoi(scan.getTokenString());
		else
			syntaxError();

		match(NUM);

		if(topScope->isExist(name) == false) {
			topScope->insert(name, Array, size);
			match(RBRACKET);
			match(SEMI);
		}
		else 
			syntaxError("Multiple definition variable!");
	}
	else
		syntaxError();
}

//函数定义从左圆括号开始，匹配完右圆括号
TreeNode* Parser::funDec(VarType varType) {
	if(funTable.isExist(name) == false) {
		TreeNode* funNode = new TreeNode(name, lineNo);
		funNode->setNodeKind(PrgK);

		auto it = funTable.insert(name, varType);
		funNode->setFunInfo(funTable.find(name));

		pushScope(1);

		match(LPAREN);

		while(token != RPAREN) {
			if(token == VOID) {
				match(VOID);
				break;
			}
			else if(token == INT) {
				match(INT);
				name = scan.getTokenString();
				match(ID);

				VarType type = Integer;
				if(token == LBRACKET) {
					match(LBRACKET);
					match(RBRACKET);
					type = Array;
				}

				if(token == COMMA) {
					topScope->insert(name, type, 1, false);
					funTable.insertParam(it, name, type);
					match(COMMA);
				}
				
				else if(token == RPAREN) {
					topScope->insert(name, type, 1, false);
					funTable.insertParam(it, name, type);
				}
			}
			else
				break;
		}

		match(RPAREN);

		funNode->child[0] = comStmt(1);

		return funNode;
	}
	else {
		syntaxError("Multiple definition function!");
		return NULL;
	}
}

//从左大括号开始, 匹配完右大括号
TreeNode* Parser::comStmt(int flag) {
	if(flag == 0)
		pushScope();

	TreeNode* newNode = new TreeNode(NULL, scan.getLineNo());

	match(LBRACE);

	
	newNode->setNodeKind(CompK);
	newNode->setScope(topScope);

	while(token == INT) 
		varDec();

	newNode->child[0] = stmtList();

	match(RBRACE);
	
	popScope();

	return newNode;
}

TreeNode* Parser::stmtList() {
	TreeNode* front = NULL;
	TreeNode* back = NULL;

	while(token != RBRACE) {
		TreeNode* newNode = stmt();

		if(newNode != NULL) {
			if(front == NULL) {
				front = newNode;
				back = newNode;
			}
			else {
				back->sibling = newNode;
				back = back->sibling;
			}
		}
	}

	return front;
}

TreeNode* Parser::stmt(){
	TreeNode* newNode = NULL;

	switch(token) {
	case LBRACE:
		newNode = comStmt();
		break;
	case IF:
		newNode = ifStmt();
		break;
	case WHILE:
		newNode = iteStmt();
		break;
	case RETURN:
		newNode = retStmt();
		break;
	default:
		newNode = expStmt();
		break;
	}

	return newNode;
}

TreeNode* Parser::expStmt() {
	TreeNode* newNode = NULL;

	if(token != SEMI)
		newNode = exp();

	match(SEMI);

	return newNode;
}

TreeNode* Parser::exp() {
	TreeNode* newNode = NULL;

	if(token == ID) {
		name = scan.getTokenString();
		lineNo = scan.getLineNo();
		match(ID);

		if(token == LBRACKET)
			newNode = arrayExp();
		else {
			newNode = new TreeNode(name, lineNo, 0);
			newNode->setNodeKind(Idk);
			newNode->setVarInfo(topScope->find(name));
		}

		if(token == ASSIGN) {
			TreeNode* parent = new TreeNode(NULL, lineNo, 2);
			parent->setNodeKind(AssignK);

			match(ASSIGN);

			parent->child[0] = newNode;
			parent->child[1] = exp();
			newNode = parent;
		}
		else 
			newNode = simpleExp(newNode);
	}
	else
		newNode = simpleExp();

	return newNode;
}

//当已经读取了左操作数，进入到simpleExp阶段
TreeNode* Parser::simpleExp(TreeNode* leftOp) {
	TreeNode* newNode = additiveExp(leftOp);
	
	while(token == LE || token == LT || token == EQ ||
		token == NEQ || token == GE || token == GT) {
			TreeNode* parent = new TreeNode(NULL, scan.getLineNo(), 2);
			parent->setNodeKind(OpK);
			parent->setOp(token);

			match(token);

			parent->child[0] = newNode;
			parent->child[1] = additiveExp();
			newNode = parent;
	}

	return newNode;
}

TreeNode* Parser::additiveExp(TreeNode* leftOp) {
	TreeNode* newNode = term(leftOp);

	while(token == PLUS || token == MINUS){
			TreeNode* parent = new TreeNode(NULL, scan.getLineNo(), 2);
			parent->setNodeKind(OpK);
			parent->setOp(token);

			match(token);

			parent->child[0] = newNode;
			parent->child[1] = term();
			newNode = parent;
	}

	return newNode;
}

TreeNode* Parser::term(TreeNode* leftOp) {
	TreeNode* newNode = factor(leftOp);

	while(token == TIMES || token == OVER){
			TreeNode* parent = new TreeNode(NULL, scan.getLineNo(), 2);
			parent->setNodeKind(OpK);
			parent->setOp(token);

			match(token);

			parent->child[0] = newNode;
			parent->child[1] = factor();
			newNode = parent;
	}

	return newNode;
}

TreeNode* Parser::factor(TreeNode* leftOp) {
	TreeNode* newNode = leftOp;
	if(newNode != NULL) {
		//说明是函数调用
		if(token == LPAREN) {
			TreeNode* tmp = newNode;
			newNode = call();
			delete(tmp);		
		}
	}
	else {
		switch(token) {
		case LPAREN:
			match(LPAREN);
			newNode = exp();
			match(RPAREN);
			break;
		case NUM: {
			const char* val = scan.getTokenString();
			newNode = new TreeNode(NULL, scan.getLineNo(), 0);
			newNode->setNodeKind(ConstK);
			match(NUM);
			newNode->setVal(atoi(val));
			break;
				  }
		case ID: {
			name = scan.getTokenString();
			lineNo = scan.getLineNo();
			match(ID);

			if(token == LPAREN)
				newNode = call();
			else if(token == LBRACKET)
				newNode = arrayExp();
			else {
				newNode = new TreeNode(name, lineNo, 0);
				newNode->setVarInfo(topScope->find(name));
				newNode->setNodeKind(Idk);
			}

			break;
				 }
		default:
			syntaxError();
		}
	}

	return newNode;
}

//从左圆括号开始
TreeNode* Parser::call() {
	FunList* fun = funTable.find(name);
	if(fun == NULL)
		syntaxError("Function not definend!");

	int num = fun->getParamNum();
	TreeNode* newNode = new TreeNode(name, lineNo, num);
	newNode->setFunInfo(fun);
	newNode->setNodeKind(CallK);

	match(LPAREN);

	if(num != 0)
		for(int i = 0; i < num; i++) {
			newNode->child[i] = exp();
			if(i != num - 1)
				match(COMMA);
		}

	match(RPAREN);
		
	return newNode;
}

//表达式中的数组，从左方括号开始
TreeNode* Parser::arrayExp() {
	TreeNode* newNode = new TreeNode(name, lineNo, 1);
	newNode->setVarInfo(topScope->find(name));
	newNode->setNodeKind(ArrayK);

	match(LBRACKET);

	newNode->child[0] = exp();

	match(RBRACKET);

	return newNode;
}

TreeNode* Parser::ifStmt() {
	TreeNode* newNode = new TreeNode(NULL, scan.getLineNo(), 3);
	newNode->setNodeKind(IfK);

	match(IF);
	match(LPAREN);
	newNode->child[0] = exp();
	match(RPAREN);

	newNode->child[1] = stmt();

	if(token == ELSE) {
		match(ELSE);
		newNode->child[2] = stmt(); 
	}

	return newNode;
}

TreeNode* Parser::iteStmt() {
	TreeNode* newNode = new TreeNode(NULL, scan.getLineNo(), 2);
	newNode->setNodeKind(WhileK);

	match(WHILE);
	match(LPAREN);
	newNode->child[0] = exp();
	match(RPAREN);

	newNode->child[1] = stmt();

	return newNode;
}

TreeNode* Parser::retStmt() {
	TreeNode* newNode = new TreeNode(NULL, scan.getLineNo(), 1);
	newNode->setNodeKind(ReturnK);

	match(RETURN);
	if(token != SEMI)
		newNode->child[0] = exp();

	match(SEMI);

	return newNode;
}