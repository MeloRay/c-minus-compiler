#ifndef _GLOBALS_H
#define _GLOBALS_H
#include <cstdlib>
#include <cstring>
#define TABLESIZE 211
#define SHIFT 4

typedef enum {
	/*statement*/
	IfK, WhileK, ReturnK,
	/* expression */
	OpK, ConstK, Idk, ArrayK, CallK, AssignK,
	/* declaration */
	PrgK, CompK
} NodeKind;

typedef enum {Void, Integer, Array, Prg, Undef} VarType;

typedef enum { 
	/* book-keeping tokens */
	ENDFILE, ERROR,
	/* reserved words */
	IF, ELSE, WHILE, RETURN, INT, VOID,
	/* multicharacter tokens */
	ID, NUM,
	/* special symbols */
	ASSIGN, EQ, NEQ, LT, GT, LE, GE, PLUS, MINUS, TIMES, OVER, LPAREN, RPAREN, LBRACE, RBRACE, LBRACKET, RBRACKET, SEMI, COMMA
} TokenType;

#endif