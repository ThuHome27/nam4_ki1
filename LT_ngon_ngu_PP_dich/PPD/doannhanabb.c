#include <stdio.h>
#include <string.h>

//char str[100];

int check_string(char str[100], int len) {
	enum state  {A,B,C,D};
	int Delta[4][2]={B,A,B,C,B,D,B,A}; //Hàm dịch chuyển dạng bảng
	char c;
	int i, L;
	enum state q = A;	
	printf("%d\n", len);
	// printf("Nhap xau.. :"); 	fflush(stdin);  gets(str);
	i = 0; L = len; 	c = str[i] - 97;
	while (i < L){
		// printf("%d\n", i);
	  if(c == 0 || c == 1){	//Xâu vào chỉ gồm các ký hiệu 0,1
	      q = Delta[q][c];	//Chuyển trạng thái mới
	      i++;			//Dịch chuyển đầu đọc
	      c = str[i] - 97;		//Ký hiệu đọc được
	  }  else {
	  	   //printf("Loi xau vao...\n"); //  break; 
	  		return 0;
	  	 }
	}
	if(i==L) //Nếu đọc hết toàn bộ xâu vào
	    if (q == D) {  //printf("\n Xau %s duoc doan nhan !\n\n",str); 
			return 1; }
	   	else {
	   		//printf("\n Xau %s khong duoc doan nhan !\n\n",str); 
	   		return 0; 	
	   	} 
	else return 0;
}

int main(int argc, char const *argv[])
{
	char str[100];
	FILE *fp;
	char ch;  int is_new = 0, index = 0;
	fp = fopen("text.c", "r");
	if (fp == NULL)
	{
		printf("Can not open the file.\n");
		return 1;
	}
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == ' ' || ch == 10)
		{
			if (is_new) { //printf("%s\n", str);
				if (check_string(str, index)) printf("YES\n");
				else printf("NO\n");
				is_new = 0; index = 0;
			}
		}
		else 
		{
			str[index] = ch; ++index;  is_new = 1;
		}
	}
// printf("%s\n", str);
	if (is_new) {
		if (check_string(str, index)) printf("YES\n");
		else printf("NO\n");
		is_new = 0; index = 0;
	}
	
	// char str[100] = "aabababababbbbabbaabb";
	// printf("%d", strlen(str));
	// if (check_string(str, strlen(str))) printf("YES\n");
	// else printf("NO\n");
	fclose(fp);
	return 0;
}
