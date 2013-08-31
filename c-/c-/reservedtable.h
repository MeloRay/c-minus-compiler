#ifndef _RESERVEDTABLE_H
#define _RESERVEDTABLE_H
#include "globals.h"
#include <vector>

struct ReservedWord {
	const char* name;
	TokenType type;
	ReservedWord(const char* name, TokenType type):name(name), type(type) {}
};

class ReservedTable {
private:
	std::vector<ReservedWord*> hashTable[TABLESIZE];
public:
	ReservedTable(){}
	void insert(const char* name, TokenType type);
	TokenType lookUp(const char* name) const;
};


#endif