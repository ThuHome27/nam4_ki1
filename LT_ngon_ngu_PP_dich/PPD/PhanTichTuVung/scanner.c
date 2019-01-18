#include "scanner.h"

#define MAX_IDENT_LEN 10
#define MAX_DIGIT_LEN 9
#define tab_to_space 4 
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

int Token;	
int	      Num;		// luu gia tri tu vung la NUMBER
char  Id[MAX_IDENT_LEN + 1]; //luu gia tri cua tu vung la IDENT
char ch;
FILE *fp;
int col = 1, row = 1, ind, i; 
int n_of_readable_ele;

/////////////////////////////////

void error(const char ms[]) {
	printf("\nLoi: %s, tai dong %d, cot %d.", ms, row, col);
	exit(1);
}

char getCh() {
	// ch = toupper(fgetc(fp)); 
	n_of_readable_ele = fread(&ch, sizeof(ch), 1, fp);
	printf("%c", ch);
	// ch = toupper(ch);
	// // danh so dong, cot de tien theo doi
	// printf("%d %d", row, col);  printf(" %c\n", ch);
	if (ch == 10)  {++row; col = 1;}
	else if (ch == '\t')  col += 4;
	else  ++col;
	return toupper(ch);
}

int getToken() {
	while ((ch == ' ' || ch == 10 || ch == '\t') && (n_of_readable_ele == 1))  ch = getCh();
	if (n_of_readable_ele != 1) return -1; //exit(0);	//if (ch == EOF) exit(0);
	else if (isalpha(ch)) {
		// ghi nhan xau
		ind = 0;
		while (isalpha(ch) || isdigit(ch)) {
			if (ind < MAX_IDENT_LEN) {
				Id[ind] = ch; ++ind; 
			}			 
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
		Num = 0; ind = 0;
		while (isdigit(ch)) {
			if (ind < MAX_DIGIT_LEN) {
				Num = 10 * Num + ch - 48;  ++ind;// tinh gia tri so	
				ch = getCh();		
			}
			else error("So qua lon vuot qua 9 chu so.");
		} 
		return NUMBER;
	}
	else if (ch == '+') {
		ch = getCh();
		return PLUS;
	}
	else if (ch == '-') {
		ch = getCh();
		return MINUS;
	}
	else if (ch == '*') {
		ch = getCh();
		return TIMES;
	}
	else if (ch == '/') {
		ch = getCh();
		return SLASH;
	}
	else if (ch == '(') {
		ch = getCh();
		// kiem tra comment
		if (ch == '*') {
			ch = getCh();
			while (n_of_readable_ele == 1) {
				if (ch == '*') {
					ch = getCh();
					if (ch == ')') {
						ch = getCh();
						return getToken();
					}
				}
				else ch = getCh();
			}
			return -1;
		}
		return LPARENT;
	}
	else if (ch == ')') {
		ch = getCh();
		return RPARENT;
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
	else if (ch == '[') {
		ch = getCh();
		return LBRACK;
	}
	else if (ch == ']') {
		ch = getCh();
		return RBRACK;
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
	else if (ch == '%') {
		ch = getCh();
		return PERCENT;
	}
	else  {
		ch = getCh();
		return NONE;
	}
}
