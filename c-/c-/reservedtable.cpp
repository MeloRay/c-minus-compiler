#include "reservedtable.h"

static int myHash(const char* key) {
	int temp = 0;
	for(int i = 0; key[i] != '\0'; i++) {
		temp = ((temp << SHIFT) + key[i]) % TABLESIZE;
	}
	return temp;
}

void ReservedTable::insert(const char* name, TokenType type) {
	int no = myHash(name);
	char* tName = new char[strlen(name) + 1];
	strcpy_s(tName, strlen(name) + 1, name);
	hashTable[no].push_back(new ReservedWord(tName, type));
}

TokenType ReservedTable::lookUp(const char* name) const{
	int no = myHash(name);
	for(auto it = hashTable[no].begin(); it != hashTable[no].end(); it++) {
		if(strcmp((*it)->name, name) == 0)
			return (*it)->type;
	}
	return ID;
}

