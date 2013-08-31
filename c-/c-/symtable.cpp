#include "symtable.h"

static int myHash(const char* key) {
	int temp = 0;
	for(int i = 0; key[i] != '\0'; i++) {
		temp = ((temp << SHIFT) + key[i]) % TABLESIZE;
	}
	return temp;
}

bool SymTable::isExist(const char* varName) const{
	int no = myHash(varName);
	for(auto it = hashTable[no].begin(); it != hashTable[no].end(); it++) {
		if(strcmp((*it)->varName, varName) == 0)
			return true;
	}
	return false;
}

void SymTable::insert(const char* varName, VarType type, int varSize, bool flag) {
	int no = myHash(varName);
	totalOffset += varSize;

	if(flag)
		memsize += varSize;

	if(!flag && type == Array) {
		hashTable[no].push_back(new BucketList(varName, type, global, true));	
	}
	else {
		hashTable[no].push_back(new BucketList(varName, type, global));
	}
	
	hashTable[no].back()->varSize = varSize;
	hashTable[no].back()->offset = totalOffset;
}

BucketList* SymTable::thisFind(const char* varName) const {
	int no = myHash(varName);
	for(auto it = hashTable[no].begin(); it != hashTable[no].end(); it++) {
		if(strcmp((*it)->varName, varName) == 0)
			return (*it);
	}

	return NULL;
}

BucketList* SymTable::find(const char* varName) const {
	BucketList* result = thisFind(varName);
	if(result != NULL)
		return result;
	else {
		for(SymTable* tmp = pre; tmp; tmp = tmp->pre) {
			result = tmp->find(varName);
			if(result != NULL)
				return result;
		}
		return NULL;
	}
}

