#include <string.h>
#include <stdio.h>
#include <stdlib.h>
// #define MAX_IDENT_LEN 10
// #define MAX_DIGIT_LEN 9
// #define tab_to_space 4  // co the bang 2 tuy theo nguoi lap trinh cai dat

// typedef enum {//da duoc sua lai de su dung cho kiem tra Ident co phai Key khong
// 	BEGIN = 0, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
// 	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
// 	NONE, IDENT, NUMBER, 
// 	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS,
// 	LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, 
// 	RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT
// } TokenType;

// char token_string[][10] = {
// 	{"BEGIN"}, {"CALL"}, {"CONST"}, {"DO"}, {"ELSE"}, {"END"}, {"FOR"}, {"IF"}, {"ODD"},
// 	{"PROCEDURE"}, {"PROGRAM"}, {"THEN"}, {"TO"}, {"VAR"}, {"WHILE"},
// 	{"NONE"}, {"IDENT"}, {"NUMBER"}, 
// 	{"PLUS"}, {"MINUS"}, {"TIMES"}, {"SLASH"}, {"EQU"}, {"NEQ"}, {"LSS"}, 
// 	{"LEQ"}, {"GTR"}, {"GEQ"}, {"LPARENT"}, {"RPARENT"}, {"LBRACK"},
// 	{"RBRACK"}, {"PERIOD"}, {"COMMA"}, {"SEMICOLON"}, {"ASSIGN"}, {"PERCENT"}
// };

// int Token;	
// int	      Num;		// luu gia tri tu vung la NUMBER
// char  Id[MAX_IDENT_LEN + 1]; //luu gia tri cua tu vung la IDENT
// char ch;
// FILE *fp;
// int col = 1, row = 1, ind, i; 
// int n_of_readable_ele;

void error(const char ms[]);
char getCh();
int getToken();