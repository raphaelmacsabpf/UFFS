#include <stdio.h>

int main(argn) {
	int a = 2;
	int b = 3;
	b ++;
	int c;
	char test;
	int i;
	//Um comentário
	for(i = 0; i < 10; i ++) {
		if(i == 9)
			printf("OIEE");
	}

	c = a + b;
	c = funcao(a,b,c,"Tipo0");
	int d = c + 1;
	printf("%d\n", d);
	return 1;
}//