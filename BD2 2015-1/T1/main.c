#include "bib.h"

int main() {
	int out = intialize("meta.dat", "data.dat");
	if(out == 1)
		printf("Erro na leitura do arquivo de metadados\n");
	else if(out == 2)
		printf("Erro na leitura do arquivo de dados\n");
	return 1;
}


