#include "funtable.h"

static int myHash(const char* key) {
	int temp = 0;
	for(int i = 0; key[i] != '\0'; i++) {
		temp = ((temp << SHIFT) + key[i]) % TABLESIZE;
	}
	return temp;
}

bool FunTable::isExist(const char* funName) const{
	int no = myHash(funName);
	for(auto it = hashTable[no].begin(); it != hashTable[no].end(); it++) {
		if(strcmp((*it)->funName, funName) == 0)
			return true;
	}
	return false;
}

std::vector<FunList*>::iterator FunTable::insert(const char* funName, VarType type) {
	int no = myHash(funName);
	hashTable[no].push_back(new FunList(funName, type));
	return hashTable[no].end() - 1;
}

void FunTable::insertParam(std::vector<FunList*>::iterator fun, const char* parName, VarType type) {
	(*fun)->params.push_back(new Param(parName, type));
}

FunList* FunTable::find(const char* funName) const {
	int no = myHash(funName);
	for(auto it = hashTable[no].begin(); it != hashTable[no].end(); it++) {
		if(strcmp((*it)->funName, funName) == 0)
			return (*it);
	}
	return NULL;
}

