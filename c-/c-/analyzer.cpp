#include "analyzer.h"
#include <iostream>
using namespace std;

static SymTable* topScope;
static FunList* fun;
static const char* nodeKindString[11] = {
	"\'If\'", "\'While\'", "\'Return\'", "\'Op\'", "\'Const\'", "\'Id\'", "\'Array\'", 
	"\'Call\'", "\'Assign\'", "\'Program\'", "\'Compound\'"
};
static const char* varTypeString[5] = {
	"\'void\'", "\'integer\'", "\'array\'", "\'program\'", "\'undefined\'"
};
static const char* tokenTypeString[] =  {
	"\'ENDFILE\'", "\'ERROR\'", "\'IF\'", "\'ELSE\'", "\'WHILE\'", "\'RETURN\'", "\'INT\'", 
	"\'VOID\'", "\'ID\'", "\'NUM\'", "\'=\'", "\'==\'", "\'!=\'", 
	"\'<\'", "\'>\'", "\'<=\'", "\'>=\'", "\'+\'", "\'-\'", "\'*\'", "\'\\'", 
	"\'(\'", "\')\'", "\'{\'", "\'}\'", "\'[\'", "\']\'", "\';\'", "\',\'"
};



void Analyzer::typeError(const TreeNode* node, const char* msg) {
	errorNum++;

	cout << "Line " << node->getLineNo() << ": " << nodeKindString[(int)node->getNodeKind()];
	if(node->getName())
		cout << "->" << node->getName();
	if(node->getNodeKind() == OpK) {
		cout << "-> " << tokenTypeString[(int)node->getOp()] << endl;
	}

	cout << "  \"" << msg << '\"' << endl;
}

void Analyzer::traverse(TreeNode* node) {
	if(node != NULL) {
		int num = node->getChildNum();

		if(node->getNodeKind() == CompK)
			topScope = node->getScope();
		else if(node->getNodeKind() == PrgK)
			fun = node->getFunInfo();

		if(num != 0)  {
			for(int i = 0; i < num; i++) {
				traverse(node->child[i]);
			}
		}
		checkNode(node);
			
		traverse(node->sibling);
	}
}

void Analyzer::checkNode(TreeNode* node) {
	switch (node->getNodeKind())
	{
	//declaration
	case PrgK:
		if(fun->isReturn() == false && fun->getType() != Void)
			typeError(node, "Function has no return.");
		break;
	case CompK:
		topScope = topScope->getPre();
		break;

	//expression
	case OpK:
		if(node->child[0]->getVarType() != Integer)
			typeError(node->child[0], "Op applied to non-integer value");
		if(node->child[1]->getVarType() != Integer)
			typeError(node->child[1], "Op applied to non-integer value");

		node->setVarType(Integer);
		break;
	case ConstK:
		node->setVarType(Integer);
		break;
	case Idk: {
		if(node->getVarInfo() == NULL) {
			node->setVarType(Undef);
			typeError(node, "variable undefined");
		}
		else
			node->setVarType(node->getVarInfo()->getType());
		break;
			  }
	case ArrayK: {
		if(node->child[0]->getVarType() != Integer)
			typeError(node->child[0], "index of non-integi value");
		
		if(node->getVarInfo() == NULL)
			typeError(node, "variable undefined");
		else {
			if(node->getVarInfo()->getType() != Array)
			typeError(node, "variable of non-array");
		}
		node->setVarType(Integer);
		break;
				 }
	case AssignK: 
		if(node->child[0]->getVarType() != Integer)
			typeError(node->child[0], "assigment applied to non-integer value");
		if(node->child[1]->getVarType() != Integer)
			typeError(node->child[1], "assigment applied to non-integer value");

		node->setVarType(Integer);
		break;
	case CallK: {
		int num = node->getFunInfo()->getParamNum();
		if(num != 0) {
			auto it = node->getFunInfo()->getParam();
			for(int i = 0; i < num; i++, it++) {
				if(node->child[i]->getVarType() != (*it)->type)
					typeError(node->child[i], "type of param is not as defined");
			}
		}

		VarType type = node->getFunInfo()->getType();
		node->setVarType(type);
		break;
				}
	//statement
	case IfK:
		if(node->child[0]->getVarType() != Integer)
					typeError(node->child[0], "if test is not integer");
		break;
	case WhileK:
		if(node->child[0]->getVarType() != Integer)
					typeError(node->child[0], "while test is not integer");
		break;
	case ReturnK: {
		VarType type = fun->getType();
		fun->setReturn();

		if(type == Void) {
			if(node->child[0] != NULL)
				typeError(node, "return is void");
		}
		else
			if(node->child[0]->getVarType() != type)
				typeError(node, "return value is not as defined");
			
		break;
				  }
	default:
		typeError(node, "unknown node");
		break;
	}
}

void Analyzer::typeCheck(TreeNode* root) {
	traverse(root);
	cout << "semantic analyze finished..." << endl;
}

static int indentno = 0;
#define UNINDENT indentno-=2
#define INDENT indentno+=2

static void printSpaces() {
	for(int i = 0; i < indentno; i++)
		cout << ' ';
}

void Analyzer::printNode(const TreeNode* node) const{
	INDENT;
	while(node != NULL) {
		printSpaces();
		switch (node->getNodeKind())
		{
		//statement
		case IfK:
			cout << "Line "<< node->getLineNo() << ": If" << endl;
			break;
		case WhileK:
			cout << "Line "<< node->getLineNo() << ": While" << endl;
			break;
		case ReturnK:
			cout << "Line "<< node->getLineNo() << ": Return" << endl;
			break;
		//declaration
		case PrgK:
			cout << "Line "<< node->getLineNo() << ": Program -> " << node->getName() 
				<< ". Return type-> " << varTypeString[(int)node->getFunInfo()->getType()] << endl;
			break;
		case CompK:
			topScope = node->getScope();
			cout << "Line "<< node->getLineNo() << ": Compound" 
				". Scope offset->\'" << topScope->getTotalOffset() 
				<<  "\', memory size->\'" << topScope->getMemsize() <<endl;
			break;
		//expression
		case OpK:
			cout << "Line "<< node->getLineNo() << ": Op -> " << tokenTypeString[(node->getOp())] << endl;
			break;
		case ConstK:
			cout << "Line "<< node->getLineNo() << ": Const -> " << node->getVal() << endl;
			break;
		case Idk:
			cout << "Line "<< node->getLineNo() << ": Id -> " << node->getName() << 
				". Type->" << varTypeString[node->getVarInfo()->getType()] << 
				", offset->\'" << node->getVarInfo()->getOffset() << "\', size->"<<
				node->getVarInfo()->getSize();

			if(node->getVarInfo()->isGlobal())
				cout << ", global";
			cout << endl;
			break;
		case ArrayK:
			cout << "Line "<< node->getLineNo() << ": Array -> " << node->getName() << 
				". Type->" << varTypeString[node->getVarInfo()->getType()] << 
				", offset->\'" << node->getVarInfo()->getOffset() << "\', size->"<<
				node->getVarInfo()->getSize();

			if(node->getVarInfo()->isGlobal())
				cout << ", global";
			cout << endl;
			break;
		case CallK:
			cout << "Line "<< node->getLineNo() << ": Call -> " << node->getName() << 
				". Return type-> " << varTypeString[(int)node->getFunInfo()->getType()] << endl;
			break;
		case AssignK:
			cout << "Line "<< node->getLineNo() << ": Assign" << endl;
			break;
		default:
			cout << "Line "<< node->getLineNo() << ": Unknow!" << endl; 
		}

		for(int i = 0; i < node->getChildNum(); i++)
			printNode(node->child[i]);
		
		if(node->getNodeKind() == CompK)
			topScope = topScope->getPre();

		node = node->sibling;
	}
	UNINDENT;
}

void Analyzer::printTree(TreeNode* root) const {
	printNode(root);
}