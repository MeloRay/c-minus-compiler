#ifndef _SYMTABLE_H
#define _SYMTABLE_H
#include "globals.h"
#include <vector>

struct BucketList {
	VarType type;
	char* varName;
	int offset;
	int varSize;
	const bool global;
	const bool reference;

	BucketList(const char* name, VarType type, bool global, bool reference = false): 
		type(type), global(global), reference(reference){
		varName = new char[strlen(name) + 1];
		strcpy_s(varName, strlen(name) + 1, name);
	}
	VarType getType() const {return type;}
	const char* getName() const {return varName;}
	int getOffset() const{return offset;}
	int getSize() const{return varSize;}
	bool isGlobal() const{return global;}
	bool isReference() const {return reference;}
};

class SymTable {
private:
	std::vector<BucketList*> hashTable[TABLESIZE];
	SymTable* pre;	//前一个作用域
	SymTable* parent;	//函数定义时，函数的parent为null，其他时候parent与pre相等
	bool global;
	int memsize;
	int totalOffset;

	VarType thisGetVarType(const char* varName) const;
	BucketList* thisFind(const char* varName) const;
public:
	SymTable(int totalOffset, bool global = false):totalOffset(totalOffset), global(global) {
		memsize = 0;
		pre = NULL;
		parent = NULL;
	}

	/* 语法分析阶段, 变量定义时使用，判断变量是否重定义*/
	bool isExist(const char* varName) const; //当前域中的符号表是否存在varName的变量， 存在返回true
	/*********************************/

	/*把变量插入到符号表**************/
	void insert(const char* varName, VarType type, int varSize, bool flag = true);
	/*********************************/

	BucketList* find(const char* varName) const; 

	//相对frame point的偏移位置和该域变量占用的地址大小
	int getMemsize() const {return memsize;}
	int getTotalOffset() const {return totalOffset;} 
	/*****************************************************/

	void setPre(SymTable *pre) { this->pre = pre;}
	void setParent(SymTable *parent) {this->parent = parent;}
	SymTable* getPre() const {return pre;}
};

#endif