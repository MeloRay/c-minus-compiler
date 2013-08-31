#include "generator.h"
#include <iostream>
#include <iomanip>
using namespace std;
#define FRAMEOFFSET 2
#define pc 7
#define mp 6
#define gp 5
#define ac 1
#define ac1 2
#define sp 3
#define fp 4
#define zero 0

static int emitLoc = 0;
static int highEmitLoc = 0;
static int entryLoc = -1;

static int emitSkip(int howMany) {
	int saveLoc = emitLoc;

	emitLoc += howMany;
	if(highEmitLoc < emitLoc)
		highEmitLoc = emitLoc;

	return saveLoc;
}

static void emitBackup(int loc) {
	if(loc > highEmitLoc) {
		cout << "BUG in emitBackup" << endl;
		exit(1);
	}
	else
		emitLoc = loc;
}

static void emitRestore() {
	emitLoc = highEmitLoc;
}


Generator::Generator(const char* fileName): traceCode(true){
	out.open(fileName);
	if(out.fail()) {
		cout << "File: \"" << fileName << "\" can't open." << endl;
		exit(1);		
	}
}

void Generator::emitComment(const char* comment, const TreeNode* node) {
	if(traceCode) {
		out << "* " << comment;
		if(node) {
			if(node->getName())
				out << ", \'" << node->getName() << "\', line: " << node->getLineNo();
			else
				out << ", line: " << node->getLineNo();
		}
		out << endl;
	}
}

void Generator::emitRO(const char* op, int r, int s, int t, const char* comment) {
	out << setw(5) << emitLoc++ <<  ':' << setw(5) << op <<
		"   " << r << ", " << s << ", " << t;	

	if(traceCode) {
		out << "   " << comment ;
	}
	
	out << endl;

	if(highEmitLoc < emitLoc) 
		highEmitLoc= emitLoc;
}

void Generator::emitRM(const char* op, int r, int d, int s, const char* comment) {
	out << setw(5) << emitLoc++ <<  ':' << setw(5) << op <<
		"   " << r << ", " << d << '(' << s << ')';	
	
	if(traceCode) {
		out << "   " << comment ;
	}
	
	out << endl;

	if(highEmitLoc < emitLoc) 
		highEmitLoc= emitLoc;
}

void Generator::emitRM_Abs(const char* op, int r, int a, const char* comment) {
	out << setw(5) << emitLoc++ <<  ':'  << setw(5) << op <<
		"   " << r << ", " << a - emitLoc << '(' << pc << ')';

	if(traceCode) {
		out << "   " << comment ;
	}
	
	out << endl;

	if(highEmitLoc < emitLoc) 
		highEmitLoc= emitLoc;
}

void Generator::nodeGen(const TreeNode* node) {
	if(node != NULL) {
		switch (node->getNodeKind())
		{
		//declaration
		case CompK:
			emitComment(">>>> compound", node);

			if(node->getScope()->getMemsize())
				emitRM("LDA", sp, -node->getScope()->getMemsize(), sp, "push new scope");

			nodeGen(node->child[0]);

			if(node->getScope()->getMemsize())
				emitRM("LDA", sp, node->getScope()->getMemsize(), sp, "pop old scope");

			emitComment("<<<< compound", node);
			break;
		case PrgK: {		
			emitComment(">>>> program", node);

			node->getFunInfo()->setLoc(emitLoc);

			bool isMain = false;
			if(strcmp(node->getFunInfo()->getName(), "main") == 0) {
				entryLoc = node->getFunInfo()->getLoc();
				isMain = true;
			}

			nodeGen(node->child[0]);

			if(isMain) 
				emitRO("HALT", 0, 0, 0, "END");
			else {
				emitRM("LDA", ac1, 0, fp, "save old fp");
				emitRM("LD", fp, -1, fp, "load new fp");

				emitRM("LDA", sp, 0, ac1, "load new sp = fp ");
				emitRM("LD", pc, -2, sp, "load old pc");
			}
			emitComment("<<<< program", node);
			break;
				   }
		//expression
		case OpK:
			emitComment(">>>> op", node);

			nodeGen(node->child[0]);
			emitRM("LDA", sp, -1, sp, "add new area");
			emitRM("ST", ac, 0, sp, "push the left operand");

			nodeGen(node->child[1]);
			emitRM("LD", ac1, 0, sp, "get the left operand");
			emitRM("LDA", sp, 1, sp, "pop the left operand");

			switch(node->getOp()) {
			case PLUS:
				emitRO("ADD", ac, ac1, ac, "op +");
				break;
			case MINUS:
				emitRO("SUB", ac, ac1, ac, "op -");
				break;
			case TIMES:
				emitRO("MUL", ac, ac1, ac, "op *");
				break;
			case OVER:
				emitRO("DIV", ac, ac1, ac, "op /");
				break;
			case LT:
				emitRO("SUB", ac, ac1, ac, "op <");
				emitRM("JLT", ac, 2, pc, "br if true");
				emitRM("LDC", ac, 0, ac, "false case");
				emitRM("LDA", pc, 1, pc, "uncoditional jmp");
				emitRM("LDC", ac, 1, ac, "true case");
				break;
			case LE:
				emitRO("SUB", ac, ac1, ac, "op <=");
				emitRM("JLE", ac, 2, pc, "br if true");
				emitRM("LDC", ac, 0, ac, "false case");
				emitRM("LDA", pc, 1, pc, "uncoditional jmp");
				emitRM("LDC", ac, 1, ac, "true case");
				break;
			case GT:
				emitRO("SUB", ac, ac1, ac, "op >");
				emitRM("JGT", ac, 2, pc, "br if true");
				emitRM("LDC", ac, 0, ac, "false case");
				emitRM("LDA", pc, 1, pc, "uncoditional jmp");
				emitRM("LDC", ac, 1, ac, "true case");
				break;
			case GE:
				emitRO("SUB", ac, ac1, ac, "op >=");
				emitRM("JGE", ac, 2, pc, "br if true");
				emitRM("LDC", ac, 0, ac, "false case");
				emitRM("LDA", pc, 1, pc, "uncoditional jmp");
				emitRM("LDC", ac, 1, ac, "true case");
				break;
			case EQ:
				emitRO("SUB", ac, ac1, ac, "op ==");
				emitRM("JEQ", ac, 2, pc, "br if true");
				emitRM("LDC", ac, 0, ac, "false case");
				emitRM("LDA", pc, 1, pc, "uncoditional jmp");
				emitRM("LDC", ac, 1, ac, "true case");
				break;
			case NEQ:
				emitRO("SUB", ac, ac1, ac, "op ==");
				emitRM("JNE", ac, 2, pc, "br if true");
				emitRM("LDC", ac, 0, ac, "false case");
				emitRM("LDA", pc, 1, pc, "uncoditional jmp");
				emitRM("LDC", ac, 1, ac, "true case");
				break;
			default:
				emitComment("BUG: Unknown operator");
				break;
			}
			emitComment("<<<< Op", node);
			break;

		case ConstK:
			emitComment("<<<< constant", node);
			emitRM("LDC", ac, node->getVal(), zero, "load const");
			emitComment(">>>> constant", node);
			break;
		case Idk: {
			emitComment(">>>> Id", node);

			if(node->getVarInfo()->isGlobal()) 
				emitRM("LD", ac, -node->getVarInfo()->getOffset(), mp, "global variable");
		
			else
				emitRM("LD", ac, -(node->getVarInfo()->getOffset() +  FRAMEOFFSET), fp, "local variable");
		
			emitComment("<<<< Id", node);
			break;
				  }
		case ArrayK:
			emitComment(">>>> Array", node);

			nodeGen(node->child[0]);

			if(node->getVarInfo()->isGlobal())  {
				if(node->getVarInfo()->isReference()) {
					emitRM("LD", ac1, -node->getVarInfo()->getOffset(), mp, "global variable's reference");
				}
				else
					emitRM("LDA", ac1, -node->getVarInfo()->getOffset(), mp, "global variable");
			}
			else {
				if(node->getVarInfo()->isReference()) {
					emitRM("LD", ac1, -(node->getVarInfo()->getOffset() +  FRAMEOFFSET), fp, "local variable's reference");
				}
				else
					emitRM("LDA", ac1, -(node->getVarInfo()->getOffset() +  FRAMEOFFSET), fp, "local variable");
			}
			emitRO("ADD", ac, ac, ac1, "Array index");
			emitRM("LD", ac, 0, ac, "Array value");

			emitComment("<<<< Array", node);
			break;
		case AssignK:
			emitComment(">>>> assign", node);

			if(node->child[0]->getNodeKind() == Idk) {
				if(node->child[0]->getVarInfo()->isGlobal())
					emitRM("LD", ac, -node->getVarInfo()->getOffset(), mp, "global variable's address");
				else
					emitRM("LDA", ac, -(node->child[0]->getVarInfo()->getOffset() +  FRAMEOFFSET), fp, "local variable's address");
			}
			else if(node->child[0]->getNodeKind() == ArrayK){
				nodeGen(node->child[0]->child[0]);

				if(node->child[0]->getVarInfo()->isGlobal()) {
					if(node->child[0]->getVarInfo()->isReference())
						emitRM("LD", ac1, -node->child[0]->getVarInfo()->getOffset(), mp, "global array's address");
					else
						emitRM("LDA", ac1, -node->child[0]->getVarInfo()->getOffset(), mp, "global array's address");
				}
				else {
					if(node->child[0]->getVarInfo()->isReference())
						emitRM("LD", ac1, -(node->child[0]->getVarInfo()->getOffset() +  FRAMEOFFSET), fp, "local array's address");
					else
						emitRM("LDA", ac1, -(node->child[0]->getVarInfo()->getOffset() +  FRAMEOFFSET), fp, "local array's address");
				}

				emitRO("ADD", ac, ac, ac1, "array index");
			}

			emitRM("LDA", sp, -1, sp, "add a new area");
			emitRM("ST", ac, 0, sp, "push the assigned variable address");

			nodeGen(node->child[1]);
			emitRM("LD", ac1, 0, sp, "get the assigned variable address");
			emitRM("LDA", sp, 1, sp, "pop tmp value");

			emitRM("ST", ac, 0, ac1, "assign the value");

			emitComment("<<<< assign", node);
			break;
		case CallK:
			emitComment("<<<< call", node);
			emitRM("LDA", sp, -(FRAMEOFFSET + node->getFunInfo()->getParamNum()), sp, "load new sp");	

			for(int i = 0; i < node->getFunInfo()->getParamNum(); i++) {
				if(node->child[i]->getVarType() == Array) {
					if(node->child[0]->getVarInfo()->isGlobal()) {
						if(node->child[0]->getVarInfo()->isReference())
							emitRM("LD", ac, -node->child[0]->getVarInfo()->getOffset(), mp, "pram reference");
						else
							emitRM("LDA", ac, -node->child[0]->getVarInfo()->getOffset(), mp, "global variable param");		
					}
					else {
						if(node->child[0]->getVarInfo()->isReference())
							emitRM("LD", ac, -(node->child[0]->getVarInfo()->getOffset() +  FRAMEOFFSET), fp, "pram reference");
						else
							emitRM("LDA", ac, -(node->child[0]->getVarInfo()->getOffset() +  FRAMEOFFSET), fp, "local variable param");
				
					}
				}
				else
					nodeGen(node->child[i]);
				emitRM("ST", ac, node->getFunInfo()->getParamNum() - i - 1, sp, "load param");
			}
			
			emitRM("ST", fp, FRAMEOFFSET + node->getFunInfo()->getParamNum() -1, sp, "save old fp");
			emitRM("LDA", fp, FRAMEOFFSET + node->getFunInfo()->getParamNum(), sp, "load new fp");
			
			emitRM("LDA", ac, 2, pc, "save old pc");
			emitRM("ST", ac, -2, fp, "push old pc");
			emitRM_Abs("LDA", pc, node->getFunInfo()->getLoc(), "call jmp");

			emitComment("<<<< call", node);
			break;
		//statement
		case IfK: {
			emitComment("<<<< if", node);
			
			//codition
			nodeGen(node->child[0]);
			int saveLoc1 = emitSkip(1);
			emitComment("if: jump to else belongs here");

			//true case
			nodeGen(node->child[1]);
			int saveLoc2 = emitSkip(1);
			emitComment("if: jump to end belongs here");

			int currentLoc = emitSkip(0);
			emitBackup(saveLoc1);
			emitRM_Abs("JEQ", ac, currentLoc, "if: jmp to else");
			emitRestore();

			//else 
			nodeGen(node->child[2]);
			currentLoc = emitSkip(0);
			emitBackup(saveLoc2);
			emitRM_Abs("LDA",pc, currentLoc, "if: jump to end");
			emitRestore();

			emitComment(">>>> if", node);
			break;
				  }
		case WhileK: {
			emitComment(">>>> while", node);

			int jmpLoc = emitSkip(0);
			//codition
			nodeGen(node->child[0]);
			int saveLoc1 = emitSkip(1);
			emitComment("while: jump to end belongs to here");

			nodeGen(node->child[1]);
			emitRM_Abs("LDA", pc, jmpLoc, "while: jump to condition");

			int currentLoc = emitSkip(0);
			emitBackup(saveLoc1);
			emitRM_Abs("JEQ", ac, currentLoc, "while: jump to end");
			emitRestore();

			emitComment("<<<< while", node);
			break;
					 }
		case ReturnK:
			emitComment(">>>> return", node);

			nodeGen(node->child[0]);

			emitRM("LDA", ac1, 0, fp, "save old fp");
			emitRM("LD", fp, -1, fp, "load new fp");
			emitRM("LDA", sp, 0, ac1, "load new sp = fp");
			emitRM("LD", pc, -2, sp, "load old pc");

			emitComment("<<<< return", node);
			break;
		default:
			break;
		}

		nodeGen(node->sibling);
	}
}

void Generator::codeGen(const TreeNode* root, const SymTable* globalScope) {

	//栈顶压入全局变量
	emitComment(">>>> initial");
	emitRM("LDA", sp, -(globalScope->getMemsize() + FRAMEOFFSET), sp, "push global scope");
	emitRM("LDA", fp, FRAMEOFFSET, sp, "set fp");
	emitComment("<<<< initial");

	int startLoc = emitSkip(1);
	//intput()函数
	emitComment("-> input");
	emitRO("IN", ac, 0, 0, "read value");
	emitRM("LDA", ac1, 0, fp, "save old fp");
	emitRM("LD", fp, -1, fp, "load new fp");
	emitRM("LDA", sp, 0, ac1, "load new sp = fp ");
	emitRM("LD", pc, -2, sp, "load old pc");
	emitComment("<- intput");

	//output()函数
	emitComment("<- output");
	emitRM("LD", ac, -(1 + FRAMEOFFSET), fp, "load output value");
	emitRO("OUT", ac, 0, 0, "output ac");
	emitRM("LDA", ac1, 0, fp, "save old fp");
	emitRM("LD", fp, -1, fp, "load new fp");
	emitRM("LDA", sp, 0, ac1, "load new sp = fp ");
	emitRM("LD", pc, -2, sp, "load old pc");
	emitComment("-> output");
	


	nodeGen(root);

	//跳转到main函数入口
	emitBackup(startLoc);
	emitRM_Abs("LDA", pc, entryLoc, "load main function pos");
	emitRestore();

	out.close();

	cout << "code generate finished..." << endl;
}