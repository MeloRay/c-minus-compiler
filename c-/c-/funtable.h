#ifndef _FUNTABLE_H
#define _FUNTABLE_H
#include "globals.h"
#include <vector>

struct Param {
	VarType type;
	char* parName;
	Param(const char* name, VarType type):type(type){
		if(name == NULL)
			parName = NULL;
		else {
			parName = new char[strlen(name) + 1];
			strcpy_s(parName, strlen(name) + 1, name);	
		}
	}
};

struct FunList {
	VarType returnType;
	char* funName;
	bool returned;
	int loc; /* for code generate */
	std::vector<Param*> params;

	FunList(const char* name, VarType returnType):returnType(returnType), returned(false){
		funName = new char[strlen(name) + 1];
		strcpy_s(funName, strlen(name) + 1, name);
	}
	VarType getType() const {return returnType;}
	const char* getName() const {return funName;}
	int getLoc() const {return loc;}
	int getParamNum() const {return params.size();}
	std::vector<Param*>::iterator getParam() {return params.begin();}
	bool isReturn() const {return returned;}
	void setReturn() {returned = true;}
	void setLoc(int loc) {this->loc = loc;}
};

class FunTable {
private:
	std::vector<FunList*> hashTable[TABLESIZE];
public:
	/***********以下4个函数在语法分析时使用*********************/
		//函数定义时插入到函数表
	bool isExist(const char* funName) const;
	std::vector<FunList*>::iterator insert(const char* funName, VarType type);
	void insertParam(std::vector<FunList*>::iterator fun, const char* parName, VarType type);

		//找到函数，返回函数说明的指针，找不到为NULL
	FunList* find(const char* funName) const;
	/***********************************************************/

	
};
#endif