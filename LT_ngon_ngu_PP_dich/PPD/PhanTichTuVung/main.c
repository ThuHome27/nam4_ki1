// #include "scanner.c"
// #include "parser.c"
#include "scanner.h"
// #include "parser.h"
#include "semantic.h"
extern int Token;	
// int	      Num;		// luu gia tri tu vung la NUMBER
// char  Id[MAX_IDENT_LEN + 1]; //luu gia tri cua tu vung la IDENT
extern char ch;
extern FILE *fp;
// int col = 1, row = 1, ind, i; 
// int n_of_readable_ele;

int main(int argc, char const *argv[])
{
	// read file
	if (argc == 1) fp = fopen("example_input.c", "r");
	else if (argc == 2) fp = fopen(argv[1], "r");
	if (fp == NULL) {
		printf("Khong mo duoc file.\n");
		return 1;
	}

	// ch = getCh();
	// while (1) {
	// 	Token = getToken();
	// 	if (Token == -1) return 0; // end of file
	// 	printf("%s", token_string[Token]);
	// 	if (Token == IDENT) printf(" (%s)\n", Id);
	// 	else if (Token == NUMBER) printf(" (%d)\n", Num);
	// 	else printf("\n");
	// }

	ch = getCh(); Token = getToken();
	compileProgram();
	return 0;
}
	