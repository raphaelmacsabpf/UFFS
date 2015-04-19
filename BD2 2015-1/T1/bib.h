#include <stdio.h>

#define MAX_FIELD_NAME_LENGHT 50 //Aqui é definido o tamaho máximo do nome de um campo

typedef struct S_field {//Estrutura do campo
	char fieldName[MAX_FIELD_NAME_LENGHT];//Nome do campo
	char fieldType;//Tipo do campo [INTEIRO, DOUBLE, STRING]
	int fieldLenght;//Tamanho do campo
	char fieldCanNull;//Define se o campo pode ser nulo ou não
}S_field;

typedef struct S_table {//Estrutura da Tabela
	int fieldCount;//Quantidade de campos da tabela
	S_field *fields;//Ponteiro para o vetor de campos
}S_table;

//Inicializa o processo de leitura de metadados e dados
//char metaFile[] = Nome do arquivo de metadados
//char dataFile[] = Nome do arquivo de dados
//Retorno = Código de erro, [0 caso nenhum erro tenha sido encontrado]
					      //[1 caso algum erro no arquivo de metadados tenha sido encontrado]
					      //[2 caso algum erro no arquivo de dados tenha sido encontrado]
int intialize(char metaFile[], char dataFile[]);

//Retorna a quantidade de campos de um arquivo de metadados
//FILE *file = Ponteiro para o arquivo dos metadados
//retorno = Quantidade de campos existentes no arquivo de metadados
int getFieldCount(FILE *file);

//Armazena em um vetor de campos as informações dos campos que estrão no arquivo de metadados
//FILE *file = Ponteiro para o arquivo de metadados
//S_field *fields = Ponteiro para o vetor de campos
//int countFields = Quantidade de campos a serem lídos
void getFields(FILE *file, S_field *fields, int countFields);

//Imprime os dados do arquivo de dados de acordo ao que foi lido no arquivo de metadados
//S_table *table = Ponteiro para a tabela onde contém os dados do arquivo de metadados
//FILE *dataFile = Ponteiro para o arquivo de dados
void printData(S_table *table, FILE *dataFile);