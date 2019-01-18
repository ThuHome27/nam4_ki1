#include <stdio.h>

FILE *fp;
char ch = ' ';

int main(int argc, char const *argv[])
{
	fp = fopen("input_tex.c", "r");
	if (fp == NULL)
	{
		printf("Can not open the file.\n");
		return 1;
	}
	int g = 40;
	ch = fgetc(fp);
	while (ch != EOF) {
		
		printf("%c", ch);
		ch = fgetc(fp);
	}
	// if (ch == EOF) {
	// 	printf("fuck");
	// }
	// ch = fgetc(fp);
	// if (ch == EOF) {
	// 	printf("fuck");
	// }
	return 0;
}
