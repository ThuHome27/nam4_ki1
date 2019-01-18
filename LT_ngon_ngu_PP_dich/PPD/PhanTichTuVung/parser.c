#include "parser.h"
// extern int Token;
// extern 

// void expression();

// void error(const char ms[]) {
// 	printf("\nLoi: %s", ms);
// 	exit(1);
// }

void factor() {
	if (Token == IDENT) {
		Token = getToken();
		if (Token == LBRACK) {
			Token = getToken();
			expression();
			if (Token == RBRACK) Token = getToken();
			else error("thieu dau dong ngoac vuong.");
		}
	}
	else if (Token == NUMBER) Token = getToken();
	else if (Token == LPARENT) {
		Token = getToken();
		expression();
		if (Token == RPARENT) Token = getToken();
		else error("thieu dau dong ngoac tron.");
	}
	else error("thieu ten bien/so/(bieu thuc)");
}

void term() {
	factor();
	while (Token == TIMES || Token == SLASH || Token == PERCENT) {
		Token = getToken();
		factor();
	}
}

void expression() {
	if (Token == PLUS || Token == MINUS) {
		Token = getToken();
	}
	term();
	while (Token == PLUS || Token == MINUS) {
		Token = getToken();
		term();
	}
}

void condition() {
	if (Token == ODD) {
		Token = getToken();
		expression();
	}
	else {
		expression();
		if (Token == EQU || Token == NEQ || Token == LSS || 
			Token == LEQ || Token == GTR || Token == GEQ) {
			Token = getToken();
			expression();
		} 
		else error("thieu dau quan he so sanh.");	
	}
}

void statement() {
	if (Token == IDENT) {
		Token = getToken();
		if (Token == ASSIGN) {
			Token = getToken();
			expression();
		}
		else error("thieu toan tu gan.");
	}
	else if (Token == CALL) {
		Token = getToken();
		if (Token == IDENT) {
			Token = getToken();
			if (Token == LPARENT) {
				Token = getToken();
				expression();
				while (Token == COMMA) {
					Token = getToken();
					expression();
				}
				if (Token == RPARENT) Token = getToken();
				else error("thieu dau dong ngoac.");
			}
		}
		else error("thieu ten thu tuc/ham.");
	}
	else if (Token == BEGIN) {
		Token = getToken();
		statement();
		while (Token == SEMICOLON) {
			Token = getToken();
			statement();
		}
		if (Token == END) Token = getToken();
		else error("thieu tu khoa END.");
	}
	else if (Token == IF) {
		Token = getToken();
		condition();
		if (Token == THEN) {
			Token = getToken();
			statement();
			if (Token == ELSE) {
				Token = getToken();
				statement();
			}
		}
		else error("thieu tu khoa THEN.");
	}
	else if (Token == WHILE) {
		Token = getToken();
		condition();
		if (Token == DO) {
			Token = getToken();
			statement();
		}
		else error("thieu tu khoa DO.");
	}
	else if (Token == FOR) {
		Token = getToken();
		if (Token == IDENT) {
			Token = getToken();
			if (Token == ASSIGN) {
				Token = getToken();
				expression();
				if (Token == TO) {
					Token = getToken();
					expression();
					if (Token == DO) {
						Token = getToken();
						statement();
					}
					else error("thieu tu khoa DO");
				}
				else error("thieu tu khoa TO");
			}
			else error("thieu tu khoa ASSIGN");
		}
		else error("thieu bien chay cua vong lap.");
	}
}

void block() {
	if (Token == CONST) {
		do {
			Token = getToken();
			if (Token == IDENT) {
				Token = getToken();
				if (Token == EQU) {
					Token = getToken();
					if (Token == NUMBER) Token = getToken();
					else error("Thieu gia tri so cua hang.");
				}
				else error("Thieu dau bang.");
			}
			else error("thieu ten hang.");
		} while (Token == COMMA);
		if (Token == SEMICOLON) {
			Token = getToken();
			//block();
		}
		else error("Thieu dau cham phay.");
	}

	if (Token == VAR) {
		do {
			Token = getToken();
			if (Token == IDENT) {
				Token = getToken();
				if (Token == LBRACK) {
					Token = getToken();
					if (Token == NUMBER) {
						Token = getToken();
						if (Token == RBRACK) Token = getToken();
						else error("thieu dong ngoac vuong.");
					}
					else error("thieu do dai cua mang");
				}
			}
		} while (Token == COMMA);
		if (Token == SEMICOLON) {
			Token = getToken();
			// block();
		}
		else error("thieu dau cham phay");
	}
	
	while (Token == PROCEDURE) {
		Token = getToken();
		if (Token == IDENT) {
			Token = getToken();
			if (Token == LPARENT) {
				do {
					Token = getToken();
					if (Token == VAR) {
						Token = getToken();
						if (Token == IDENT) Token = getToken();
						else error("thieu ten tham so.");
					}
					else if (Token == IDENT) Token = getToken();
					else error("thieu tham so.");
				} while (Token == SEMICOLON);
				if (Token == RPARENT) Token = getToken();
				else error("thieu dau dong ngoac");
			}
			if (Token == SEMICOLON) {
				Token = getToken();
				block();
				if (Token == SEMICOLON) {
					Token = getToken();
					// block();
				}
				else error("thieu dau cham phay.");
			} 
			else error("thieu dau cham phay.");
		}
		else error("thieu ten thu tuc/ham.");
	}

	if (Token == BEGIN) {
		do {
			Token = getToken();
			statement();
		} while (Token == SEMICOLON);
		if (Token == END) Token = getToken();
		else error("thieu dau cham phay hoac tu khoa END");
	}
	else error("Thieu phan than chuong trinh chinh.");
}

void program() {
	if (Token == PROGRAM) {
		Token = getToken();
		if (Token == IDENT) {
			Token = getToken();
			if (Token == SEMICOLON) {
				Token = getToken();
				block();
				if (Token == PERIOD) printf("Thanh cong.");
				else error("Thieu dau cham");
			}
			else error("Thieu dau cham phay.");
		}
		else error("Thieu ten chuong trinh.");
	}
	else error("Thieu tu khoa PROGRAM");
}
