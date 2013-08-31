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
	/***********����4���������﷨����ʱʹ��*********************/
		//��������ʱ���뵽������
	bool isExist(const char* funName) const;
	std::vector<FunList*>::iterator insert(const char* funName, VarType type);
	void insertParam(std::vector<FunList*>::iterator fun, const char* parName, VarType type);

		//�ҵ����������غ���˵����ָ�룬�Ҳ���ΪNULL
	FunList* find(const char* funName) const;
	/***********************************************************/

	
};
#endif