#include "scan.h"
#include <iostream>
using namespace std;

static bool eofFlag = false;
typedef enum {
	START, INID, INNUM, DONE
} StateType;

Scan::Scan(const char* fileName) {
	in.open(fileName);
	if(in.fail()) {
		cout << "File: \"" << fileName << "\" not exist." << endl;
		exit(1);
	}
	else {
		cout << "open file: \'" << fileName << "\'..." << endl;
	}
	bufsize = -1;
	linePos = 0;
	lineNo = 0;
	reservedTable.insert("int", INT);
	reservedTable.insert("void", VOID);
	reservedTable.insert("if", IF);
	reservedTable.insert("else", ELSE);
	reservedTable.insert("while", WHILE);
	reservedTable.insert("return", RETURN);
}

char Scan::getNextChar() {
	if(linePos >= bufsize) {
		bufsize = 0;
		while(bufsize == 0) {
			lineNo++;
			if(in.getline(buf, BUFSIZE)) {
				bufsize = strlen(buf);
				linePos = 0;
			}
			else {
				eofFlag = true;
				in.close();
				return EOF;
			}		
		}
		return buf[linePos++];
	}
	else
		return buf[linePos++];
}

void Scan::ungetNextChar() {
	if(!eofFlag)
		linePos--;
}

TokenType Scan::reservedLookUp(char* name) const{
	return reservedTable.lookUp(name);
}

const char* Scan::getTokenString() const{
	char* newString = new char[strlen(tokenString) + 1];
	strcpy_s(newString, strlen(tokenString) + 1, tokenString);
	return newString;
}

TokenType Scan::getToken() {
	int tokenStringIndex = 0;
	TokenType currentToken;
	StateType state = START;
	bool save;

	while(state != DONE) {
		save = true;
		char c = getNextChar();
		switch(state) {
		case START:
			if(isdigit(c))
				state = INNUM;
			else if(isalpha(c))
				state = INID;
			else if( (c == ' ') || (c == '\t') || (c == '\n')) 
				save = false;
			else {
				switch(c) {
				case EOF:
					return ENDFILE;
				case ',':
					return COMMA;
				case ';':
					return SEMI;
				case '+':
					return PLUS;
				case '-':
					return MINUS;
				case '*':
					return TIMES;
				case '/':
					return OVER;
				case '(':
					return LPAREN;
				case ')':
					return RPAREN;
				case '{':
					return LBRACE;
				case '}':
					return RBRACE;
				case '[':
					return LBRACKET;
				case ']':
					return RBRACKET;
				case '=': 
					if(getNextChar() == '=') 
						currentToken = EQ;
					else {
						ungetNextChar();
						currentToken = ASSIGN;
					}
					return currentToken;
				case '<':
					if(getNextChar() == '=') {
						currentToken = LE;
						save = false;
					}
					else {
						ungetNextChar();
						currentToken = LT;
					}
					return currentToken;
				case '>':
					if(getNextChar() == '=')
						currentToken = GE;
					else {
						ungetNextChar();
						currentToken = GT;
					}
					return currentToken;
				case '!':
					if(getNextChar() == '=') 
						currentToken = NEQ;
					else {
						ungetNextChar();
						currentToken = ERROR;
					}
					return currentToken;
				}
			}
			break;
		case INNUM:
			if(!isdigit(c)) {
				ungetNextChar();
				save = false;
				state = DONE;
				currentToken = NUM;
			}
			break;
		case INID:
			if(!isalpha(c)) {
				ungetNextChar();
				save =false;
				state = DONE;
				currentToken = ID;
			}
			break;
		default:
			state = DONE;
			currentToken = ERROR;
			break;
		}
		if((save) && (tokenStringIndex < TOKENLEN))
			tokenString[tokenStringIndex++] = c;
		if(state == DONE) {
			tokenString[tokenStringIndex] = '\0';
			if(currentToken == ID)
				currentToken = reservedLookUp(tokenString);
		}
	}
	return currentToken;
}

static const char* tokenTypeString[] =  {
	"\'ENDFILE\'", "\'ERROR\'", "\'IF\'", "\'ELSE\'", "\'WHILE\'", "\'RETURN\'", "\'INT\'", 
	"\'VOID\'", "\'ID\'", "\'NUM\'", "\'=\'", "\'==\'", "\'!=\'", 
	"\'<\'", "\'>\'", "\'<=\'", "\'>=\'", "\'+\'", "\'-\'", "\'*\'", "\'\\'", 
	"\'(\'", "\')\'", "\'{\'", "\'}\'", "\'[\'", "\']\'", "\';\'", "\',\'"
};

void Scan::printToken(TokenType type) const{
	cout << tokenTypeString[(int)type];
}