// #include <string.h>
#include "scanner.h"
#define MAX_IDENT_LEN 10

extern int Token;
extern char  Id[MAX_IDENT_LEN + 1];
typedef enum {//da duoc sua lai de su dung cho kiem tra Ident co phai Key khong
	BEGIN = 0, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	NONE, IDENT, NUMBER, 
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS,
	LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, 
	RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT
} TokenType;

typedef enum {
	const_type = 0, variable_type, subPro_type, program_type, para_type,
	tham_chieu, tham_tri, var_array_type
} Objects;

void enter(char *Id, Objects kind);
int position(char *Id);
int checkIdent(char *Id);
void mkSymTable();
void delSymTab();
Objects getKind(int pos);
void compileProgram();
void compileBlock(int TX);
void compileStatement();
void compileCondition();
void compileFactor();
void compileTerm();
void compileExpression();
void compileDecleConst();
void compileDecleVariable();
void compileDecleProce(int TX);