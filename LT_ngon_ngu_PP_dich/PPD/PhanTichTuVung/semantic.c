/*
doan nhan loi
*/


#include "semantic.h"

#define MAX_IDENT 100
#define MAX_LEVEL 100
// #define MAX_IDENT_LEN 10

// typedef enum {
// 	const_type, variable_type, subPro_type, program_type, para_type 
// } Objects;

// mang 2 chieu luu kieu cua tham so cua thu tuc la tham chieu hay tham tri
Objects params[MAX_LEVEL][MAX_IDENT];
int no_procedure = - 1; // so thu tu cua mot thu tuc

struct 
{
	char Id[MAX_IDENT_LEN + 1];
	Objects kind;
	int no_param;
	int no_proce;
} symTable[MAX_IDENT];

struct 
{
	int base;
	int top;
} symTab[MAX_LEVEL];

int curSymTab;

////////////////////////////

void enter(char *Id, Objects kind) {
	int c = curSymTab;
	int b = symTab[c].base;
	int t = symTab[c].top;
	if (b + t == MAX_IDENT) error("Qua nhieu bien.");
	if (checkIdent(Id) != 0) error("Ten bien da ton tai.");
	++t;
	strcpy(symTable[b + t].Id, Id);
	symTable[b + t].kind = kind;
	symTable[b + t].no_param = 0;
	if (kind == para_type) {
		symTable[b - 1].no_param += 1;
	}
	symTab[c].top = t;
	if (kind == subPro_type) {
		++no_procedure;
		symTable[b + t].no_proce = no_procedure;
	}
}

int position(char *Id) {
	int c = curSymTab;
	do {
		int b = symTab[c].base;
		int t = symTab[c].top;
		while (t >= 0) {
			if (strcmp(Id, symTable[b + t].Id) != 0) --t;
			else return b + t;
		}
		--c;
	} while (c >=0);
	return -1;
}

int checkIdent(char *Id) {
	int b = symTab[curSymTab].base;
	int t = symTab[curSymTab].top;
	while (t >= 0) {
		if (strcmp(Id, symTable[b + t].Id) != 0) --t;
		else return 1;
	}
	return 0;
}

void mkSymTable() {
	++curSymTab;
	if (curSymTab == 0) {
		symTab[curSymTab].base = 0;
	}
	else {
		symTab[curSymTab].base = symTab[curSymTab - 1].base + symTab[curSymTab - 1].top + 1;
	}
	symTab[curSymTab].top = -1;
}

void delSymTab() {
	--curSymTab;
}

Objects getKind(int pos) {
	return symTable[pos].kind;
}


////////////////////////////////

void compileProgram() {
	if (Token == PROGRAM) {
		Token = getToken();
		if (Token == IDENT) {
			curSymTab = -1;
			mkSymTable();
			enter(Id, program_type);
			Token = getToken();
			if (Token == SEMICOLON) {
				Token = getToken();
				compileBlock(0); // block();
				if (Token == PERIOD) printf("Thanh cong.");
				else error("Thieu dau cham");
			}
			else error("Thieu dau cham phay.");
		}
		else error("Thieu ten chuong trinh.");
	}
	else error("Thieu tu khoa PROGRAM");
}

void compileBlock(int TX) {
	if (Token == CONST) {
		do {
			Token = getToken();
			compileDecleConst();
		} while (Token == COMMA);
		if (Token == SEMICOLON) {
			Token = getToken();
		}
		else error("Thieu dau cham phay.");
	}

	if (Token == VAR) {
		do {
			Token = getToken();
			compileDecleVariable();
		} while (Token == COMMA);
		if (Token == SEMICOLON) {
			Token = getToken();
		}
		else error("thieu dau cham phay");
	}
	
	while (Token == PROCEDURE) {
		Token = getToken();
		compileDecleProce(TX);
	}

	if (Token == BEGIN) {
		do {
			Token = getToken();
			compileStatement();
		} while (Token == SEMICOLON);
		if (Token == END) Token = getToken();
		// else error("thieu dau cham phay hoac tu khoa END");
		else if (Token == PROCEDURE || Token == BEGIN || Token == PERIOD) {
			error("Thieu tu khoa END");
		}
		else error("Thieu dau cham phay");
	}
	else error("Thieu tu khoa BEGIN");
}

void compileStatement() {
	int p;
	if (Token == IDENT) {
		p = position(Id);
		if (p < 0) error("Bien chua khai bao.");
		if (getKind(p) != variable_type && getKind(p) != para_type) error("Ve trai phai la mot bien.");
		Token = getToken();
		if (Token == LBRACK) {
			Token = getToken();
			compileExpression();
		}
		if (Token == ASSIGN) {
			Token = getToken();
			compileExpression();
		}
		else error("thieu toan tu gan.");
	}
	else if (Token == CALL) {
		Token = getToken();
		if (Token == IDENT) {
			p = position(Id);
			if (p < 0) error("Thu tuc chua duoc khai bao.");
			if (getKind(p) != subPro_type) error("Khong phai ten thu tuc.");
			Token = getToken();
			if (Token == LPARENT) {
				// Token = getToken();
				if (symTable[p].no_param == 0) {
					error("Thu tuc khong co tham so.");
				}
				int _noPar = 0;
				int _noProce = symTable[p].no_proce;
				// printf("%d %d %d %d %d\n", params[_noProce][0], params[_noProce][1], params[_noProce][2], params[_noProce][3], params[_noProce][4] );
				do {
					Token = getToken();
					if (params[_noProce][_noPar] == tham_tri) { // truyen tham tri
						compileExpression();
					}
					else {
						if (Token == IDENT) { // truyen tham chieu
							int p1 = position(Id);
							if (p1 < 0) error("Bien chua duoc khai bao.");
							if (symTable[p1].kind != variable_type && symTable[p1].kind != para_type) 
								error("Vi tri nay phai la bien do la truyen tham chieu.");
							Token = getToken();
						}
						else error("Vi tri nay phai la bien do la truyen tham chieu.");
					}
					++_noPar;

				} while (Token == COMMA);
				if (Token == RPARENT) {
					// printf("%d %d\n", symTable[p].no_param, _noPar);
					if (_noPar != symTable[p].no_param) error("So luong tham so truyen vao khong hop le.");
					Token = getToken();
				}
				else error("thieu dau dong ngoac.");
			}
		}
		else error("thieu ten thu tuc/ham.");
	}
	else if (Token == BEGIN) {
		Token = getToken();
		compileStatement();
		while (Token == SEMICOLON) {
			Token = getToken();
			compileStatement();
		}
		if (Token == END) Token = getToken();
		else error("thieu dau cham phay");
	}
	else if (Token == IF) {
		Token = getToken();
		compileCondition();
		if (Token == THEN) {
			Token = getToken();
			compileStatement();
			if (Token == ELSE) {
				Token = getToken();
				compileStatement();
			}
		}
		else error("thieu tu khoa THEN.");
	}
	else if (Token == WHILE) {
		Token = getToken();
		compileCondition();
		if (Token == DO) {
			Token = getToken();
			compileStatement();
		}
		else error("thieu tu khoa DO.");
	}
	else if (Token == FOR) {
		Token = getToken();
		if (Token == IDENT) {
			p = position(Id);
			if (p < 0) error("Bien chua khai bao.");
			if (getKind(p) != variable_type) error("Ve trai phai la mot bien.");
			Token = getToken();
			if (Token == ASSIGN) {
				Token = getToken();
				compileExpression();
				if (Token == TO) {
					Token = getToken();
					compileExpression();
					if (Token == DO) {
						Token = getToken();
						compileStatement();
					}
					else error("thieu tu khoa DO");
				}
				else error("thieu tu khoa TO");
			}
			else error("thieu toan tu gan.");
		}
		else error("thieu bien chay cua vong lap.");
	}
}

void compileCondition() {
	if (Token == ODD) {
		Token = getToken();
		compileExpression();
	}
	else {
		compileExpression();
		if (Token == EQU || Token == NEQ || Token == LSS || 
			Token == LEQ || Token == GTR || Token == GEQ) {
			Token = getToken();
			compileExpression();
		} 
		else error("thieu dau quan he so sanh.");	
	}
}

void compileFactor() {
	int p;
	if (Token == IDENT) {
		p = position(Id);
		if (p < 0) error("Bien chua duoc khai bao.");
		Objects _kind = getKind(p);
		if (_kind != const_type && _kind != variable_type &&  _kind != para_type && _kind != var_array_type) 
			error("Dinh danh phai la bien, hang, hoac tham so.");
		// if (getKind(p) != variable_type) {printf("%d %d %d\n",p, getKind(p), getKind(position("b"))); error("Expected variable"); }
		if (_kind == var_array_type) {
			Token = getToken();
			if (Token == LBRACK) {
				Token = getToken();
				compileExpression();
				if (Token == RBRACK) Token = getToken();
				else error("thieu dau dong ngoac vuong.");
			}
			else error("Thieu [chi so phan tu cua mang]");			
		}
		else Token = getToken();
	}
	else if (Token == NUMBER) Token = getToken();
	else if (Token == LPARENT) {
		Token = getToken();
		compileExpression();
		if (Token == RPARENT) Token = getToken();
		else error("thieu dau dong ngoac tron.");
	}
	else error("thieu ten bien/so/(bieu thuc)");
}

void compileTerm() {
	compileFactor();
	while (Token == TIMES || Token == SLASH || Token == PERCENT) {
		Token = getToken();
		compileFactor();
	}
}

void compileExpression() {
	if (Token == PLUS || Token == MINUS) {
		Token = getToken();
	}
	compileTerm();
	while (Token == PLUS || Token == MINUS) {
		Token = getToken();
		compileTerm();
	}
}

void compileDecleConst() {
	if (Token == IDENT) {
		enter(Id, const_type);
		Token = getToken();
		if (Token == EQU) {
			Token = getToken();
			if (Token == NUMBER) {
				Token = getToken();
			}
			else error("Thieu gia tri so cua hang.");
		}
		else error("Thieu dau bang.");
	}
	else error("thieu ten hang.");
}

void compileDecleVariable() {
	if (Token == IDENT) {
		// enter(Id, variable_type);
		Token = getToken();
		if (Token == LBRACK) {
			enter(Id, var_array_type);
			Token = getToken();
			if (Token == NUMBER) {
				Token = getToken();
				if (Token == RBRACK) Token = getToken();
				else error("thieu dong ngoac vuong.");
			}
			else error("thieu size cua mang");
		}
		else enter(Id, variable_type);
	}
	else error("thieu ten bien.");
}

void compileDecleProce(int TX) {	
	if (Token == IDENT) {
		// ++no_procedure;
		enter(Id, subPro_type);
		mkSymTable();
		Token = getToken();
		if (Token == LPARENT) {
			int cnt_param = 0;
			do {
				
				Token = getToken();
				if (Token == VAR) { //truyen tham tri
					Token = getToken();
					if (Token == IDENT) {
						enter(Id, para_type);
						params[no_procedure][cnt_param] = tham_chieu;
						++cnt_param;
						Token = getToken();
					} 
					else error("thieu tham so.");
				}
				else if (Token == IDENT) { //truyen tham chieu
					enter(Id, para_type);
					params[no_procedure][cnt_param] = tham_tri;
					cnt_param++;
					Token = getToken();
				} 
				else error("thieu tham so.");
			} while (Token == SEMICOLON);
			if (Token == RPARENT) Token = getToken();
			else error("thieu dau dong ngoac");
		}
		if (Token == SEMICOLON) {
			Token = getToken();
			compileBlock(TX);
			if (Token == SEMICOLON) {
				Token = getToken();
			}
			else error("thieu dau cham phay.");
		} 
		else error("thieu dau cham phay.");
		//
		delSymTab();
	}
	else error("thieu ten thu tuc.");	
}

