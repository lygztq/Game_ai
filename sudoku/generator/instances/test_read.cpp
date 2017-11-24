#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
	// FILE *ptr = fopen("instance1.txt","r");
	// char *pBuf;
	// fseek(ptr,0,SEEK_END);
	// int len = ftell(ptr);
	// pBuf = new char [len];
	// rewind(ptr);
	// fread(pBuf,1,len,ptr);
	// pBuf[len] = '\0';
	// fclose(ptr);
	// for(int i=0;i<len;++i)
	// 	printf("%c\n", pBuf[i]);
	int a = 1;
	char f[100];
	//strcpy(f,("instances/instance%d.txt",a));
	sprintf(f,"instances/instance%d.txt",a);
	printf("%s\n", f);

	system("PAUSE");
	return 0;
}
