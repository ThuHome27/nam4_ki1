#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#define MAX_IDENT_LEN 10
#define tab_to_space 4  // co the bang 2 tuy theo nguoi lap trinh cai dat

typedef enum {//da duoc sua lai de su dung cho kiem tra Ident co phai Key khong
	BEGIN = 0, CALL, CONST, DO,  ELSE, END, FOR, IF, ODD,
	PROCEDURE, PROGRAM, THEN, TO, VAR, WHILE,
	NONE, IDENT, NUMBER, 
	PLUS, MINUS, TIMES, SLASH, EQU, NEQ, LSS,
	LEQ, GTR, GEQ, LPARENT, RPARENT, LBRACK, 
	RBRACK, PERIOD, COMMA, SEMICOLON,  ASSIGN, PERCENT
} TokenType;

char token_string[][10] = {
	{"BEGIN"}, {"CALL"}, {"CONST"}, {"DO"}, {"ELSE"}, {"END"}, {"FOR"}, {"IF"}, {"ODD"},
	{"PROCEDURE"}, {"PROGRAM"}, {"THEN"}, {"TO"}, {"VAR"}, {"WHILE"},
	{"NONE"}, {"IDENT"}, {"NUMBER"}, 
	{"PLUS"}, {"MINUS"}, {"TIMES"}, {"SLASH"}, {"EQU"}, {"NEQ"}, {"LSS"}, 
	{"LEQ"}, {"GTR"}, {"GEQ"}, {"LPARENT"}, {"RPARENT"}, {"LBRACK"},
	{"RBRACK"}, {"PERIOD"}, {"COMMA"}, {"SEMICOLON"}, {"ASSIGN"}, {"PERCENT"}
};

TokenType Token;	
int	      Num;		// luu gia tri tu vung la NUMBER
char  Id[MAX_IDENT_LEN + 1]; //luu gia tri cua tu vung la IDENT
char ch;
FILE *fp;
int col = 1, row = 1, ind, i; 

char getCh() {
	ch = toupper(fgetc(fp)); 
	// // danh so dong, cot de tien theo doi
	// printf("%d %d", row, col);  printf(" %c\n", ch);
	// if (ch == 10)  {++row; col = 1;}
	// else if (ch == '\t')  col += 4;
	// else  ++col;
	return ch;
}

int getToken() {
	while (ch == ' ' || ch == 10 || ch == '\t')  ch = getCh();
	if (ch == EOF) exit(0);
	else if (isalpha(ch)) {
		// ghi nhan xau
		ind = 0;
		while (isalpha(ch) || isdigit(ch)) {
			Id[ind] = ch; ++ind; 
			ch = getCh();	
		} 
		Id[ind] = '\0';
		// printf("%s\n", Id);
		// kiem tra co phai la tu khoa
		for (i=0; i < 15; ++i) {
			if (!strcmp(Id, token_string[i])) return i;
		}
		return IDENT; 
	}
	else if (isdigit(ch)) {
		Num = 0;
		while (isdigit(ch)) {
			Num = 10 * Num + ch - 48;  // tinh gia tri so
			ch = getCh();	
		} 
		return NUMBER;
	}
	else if (ch == '+') {
		ch = getCh();
		return PLUS;
	}
	else if (ch == '-') {
		ch = getCh(MINUS);
		return ;
	}
	else if (ch == '*') {
		ch = getCh();
		return TIMES;
	}
	else if (ch == '/') {
		ch = getCh();
		// kiem tra comment
		if (ch == '*') {
			ch = getCh();
			while (ch != EOF) {
				if (ch == '*') {
					ch = getCh();
					if (ch == '/') {
						ch = getCh();
						return getToken();
					}
				}
				else ch = getCh();
			}
			exit(0);
		}//
		else return SLASH;
	}
	else if (ch == '=') {
		ch = getCh();
		return EQU;
	}
	else if (ch == '<') {
		ch = getCh();
		if (ch == '>') {
			ch = getCh();
			return NEQ;
		}
		else if (ch == '=') {
			ch = getCh();
			return LEQ;
		}
		else return LSS;
	}
	else if (ch == '>') {
		ch = getCh();
		if (ch == '=') {
			ch = getCh();
			return GEQ;
		}
		return GTR;
	}
	else if (ch == '(') {
		ch = getCh();
		return LBRACK;
	}
	else if (ch == ')') {
		ch = getCh();
		return RBRACK;
	}
	else if (ch == '[') {
		ch = getCh();
		return LPARENT;
	}
	else if (ch == ']') {
		ch = getCh();
		return RPARENT;
	}
	else if (ch == ',') {
		ch = getCh();
		return COMMA;
	}
	else if (ch == ';')  {
		ch = getCh();
		return SEMICOLON;
	}
	else if (ch == '.') {
		ch = getCh();
		return PERIOD;
	}
	else if (ch == ':') {
		ch = getCh();
		if (ch == '=') {
			ch = getCh();
			return ASSIGN;	
		} 
		else NONE;
	}
	else  {
		ch = getCh();
		return NONE;
	}
}


int main(int argc, char const *argv[])
{
	// read file
	if (argc == 1) fp = fopen("input_tex.c", "r");
	else if (argc == 2) fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Khong mo duoc file.\n");
		return 1;
	}

	ch = getCh();
	while (1) {
		Token = getToken();
		printf("%s", token_string[Token]);
		if (Token == IDENT) printf(" (%s)\n", Id);
		else if (Token == NUMBER) printf(" (%d)\n", Num);
		else printf("\n");
	}
	return 0;
}
