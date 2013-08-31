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
	SymTable* pre;	//ǰһ��������
	SymTable* parent;	//��������ʱ��������parentΪnull������ʱ��parent��pre���
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

	/* �﷨�����׶�, ��������ʱʹ�ã��жϱ����Ƿ��ض���*/
	bool isExist(const char* varName) const; //��ǰ���еķ��ű��Ƿ����varName�ı����� ���ڷ���true
	/*********************************/

	/*�ѱ������뵽���ű�**************/
	void insert(const char* varName, VarType type, int varSize, bool flag = true);
	/*********************************/

	BucketList* find(const char* varName) const; 

	//���frame point��ƫ��λ�ú͸������ռ�õĵ�ַ��С
	int getMemsize() const {return memsize;}
	int getTotalOffset() const {return totalOffset;} 
	/*****************************************************/

	void setPre(SymTable *pre) { this->pre = pre;}
	void setParent(SymTable *parent) {this->parent = parent;}
	SymTable* getPre() const {return pre;}
};

#endif