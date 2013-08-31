#ifndef _SCAN_H
#define _SCAN_H
#include "globals.h"
#include "reservedtable.h"
#include <fstream>
#include <string>
#define BUFSIZE 256	
#define TOKENLEN 32

class Scan {
private:
	char buf[BUFSIZE];
	char tokenString[TOKENLEN + 1];
	int bufsize;
	int linePos;
	int lineNo;
	std::ifstream in;
	ReservedTable reservedTable;

	char getNextChar();
	void ungetNextChar();
	TokenType reservedLookUp(char* name) const;
public:
	Scan(const char* fileName);
	TokenType getToken();
	int getLineNo() const{return lineNo;}
	const char* getTokenString() const;
	void printToken(TokenType type) const;
};

#endif