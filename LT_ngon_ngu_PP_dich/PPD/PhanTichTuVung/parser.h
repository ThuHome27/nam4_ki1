// #include "scanner.c"

#include "scanner.h"
extern int Token;
 typedef enum {//da duoc sua lai de su dung cho kiem tra Ident co phai Key khong
	BEGIN = 0, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	NONE, IDENT, NUMBER, 
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS,
	LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, 
	RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT
} TokenType;


void expression();
void factor();
void term();
void condition();
void statement();
void block();
void program();