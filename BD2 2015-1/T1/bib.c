#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bib.h"

int intialize(char metaFile[], char dataFile[]) {
	S_table table;
	//Abre o arquivo de metadados
	FILE *F_meta = fopen(metaFile, "rb");
	//Verifica por erro na leitura do arquivo de metadados
	if(F_meta == NULL)
		return 1;
	//Pega a quantidade de campos contido no arquivo de metadados
	table.fieldCount = getFieldCount(F_meta);
	//Aloca N quantidade de campos, de acordo ao que foi lido do arquivo
	table.fields = (S_field *) malloc(sizeof(S_field) * table.fieldCount);
	//A função getFields lê do arquivo de metadados todos os dados dos campos e armazena-os na estrutura
	getFields(F_meta, table.fields,  table.fieldCount);
	//O arquivo de metadados é fechado
	fclose(F_meta);
	//Abre o arquivo de dados
	FILE *F_data = fopen(dataFile, "rb");
	//Verifica por erro na leitura do arquivo de dados
	if(F_data == NULL)
		return 2;
	//A função printData é chamada para imprimir os dados do arquivo de dados, de acordo com a estrutura informada em &table
	printData(&table, F_data);
	//Fecha o arquivo de dados
	fclose(F_data);
	return 0;
}
int getFieldCount(FILE *file) {
	//Move o ponteiro para início do arquivo
	fseek(file, 0, SEEK_SET);
	int countField;
	// countField agora será o inteiro armazenado no início do arquivo, que contém a quantidade de campos da tabela
	fread(&countField, sizeof(int), 1, file);
	// retorna a quantidade de campos que foi encontrado no arquivo de metadados
	return countField;
}
void getFields(FILE *file, S_field *fields, int countFields) {
	//Move o ponteiro do arquivo para o início
	fseek(file, sizeof(int), SEEK_SET);
	//seekCount armazenará aonde o ponteiro do arquivo deverá estar apontando, para que haja controle independente de outros comandos do arquivo.
	int i, seekCount = sizeof(int);
	//Para cada campo será armazenado suas demais informações
	for(i = 0; i < countFields; i++) {
		//Pega o nome do campo, atente-se ao detalhe de que o nome do campo deverá ter no máximo MAX_FIELD_NAME_LENGHT caracteres
		fgets(fields[i].fieldName, MAX_FIELD_NAME_LENGHT-1, file);
		//Atualiza seekCount com o tamanho do nome lido
		seekCount += strlen(fields[i].fieldName)+1;
		//Atualiza o ponteiro do arquivo, para o valor que está em seekCount
		fseek(file, seekCount, SEEK_SET);
		//Faz a leiruta dos demais dados de cada campo.
		fread(&fields[i].fieldType, sizeof(char), 1, file);
		fread(&fields[i].fieldLenght, sizeof(int), 1, file);
		fread(&fields[i].fieldCanNull, sizeof(char), 1, file);
		//Atualiza seekCount de acordo a quantidade de bytes lidos
		seekCount += (sizeof(char) * 2)  + sizeof(int);
	}
}
void printData(S_table *table, FILE *dataFile) {
	//Move o ponteiro do arquivo para seu fim
	fseek(dataFile, 0, SEEK_END);
	//Armazena em fileLenght o tamanho do arquivo dados
	int fileLenght = ftell(dataFile);
	//Retorna o ponteiro para o início do arquivo
	fseek(dataFile, 0, SEEK_SET);
	//Imprime os nomes dos campos e a divisória
	int i;
	for(i = 0; i < table->fieldCount; i++) {
		if(i != 0)
			printf(" ");
		printf("%s", table->fields[i].fieldName);
	}
	printf("\n----------------------------------------------------\n");
	int dataInt;
	char dataChar;
	double dataDouble;
	char dataStr[100];
	int seekCount = 0;
	//Laço acontecerá enquanto o ponteiro do arquivo não atingir seu fim
	while(ftell(dataFile) != fileLenght) {
		//Laço se repete para cada campo lido anteriormente
		for(i = 0; i < table->fieldCount; i++) {
			if(table->fields[i].fieldType == 'N') { //Caso o campo seja um inteiro
				//Efetua a leitura do campo com tamanho de inteiro
				fread(&dataInt, sizeof(int), 1, dataFile);
				//Rotina de atualização de ponteiro
				seekCount += sizeof(int);
				fseek(dataFile, seekCount, SEEK_SET);
				//Imprime o dado inteiro
				printf("%d | ", dataInt);
			}
			else if(table->fields[i].fieldType == 'C') { //Caso o campo seja uma cadeia de caracteres
				if(table->fields[i].fieldLenght == 1) { //Tratará o dado como um char por se tratar de uma cadeia de caracteres de tamanho 1
					//Efetua a leitura do campo com tamanho de char
					fread(&dataChar, sizeof(char), 1, dataFile);
					//Imrpime o dado
					printf("%c | ", dataChar);
					//Rotina de atualização de ponteiro
					seekCount += sizeof(char);
					fseek(dataFile, seekCount, SEEK_SET);
				}
				else {//Tratará como uma string por se tratar de uma cadeia de caracteres de tamanho maior que 1
					//É lido os N bytes descritos na estrutura de campos
					fgets(dataStr, table->fields[i].fieldLenght+1, dataFile);
					//Imprime o dado
					printf("%s | ", dataStr);
					//Ronita de atualização de ponteiro
					seekCount += table->fields[i].fieldLenght;
					fseek(dataFile, seekCount, SEEK_SET);
				}
			}
			else if(table->fields[i].fieldType == 'D') {//Caso seja um double
				//Efetua a leitura do campo com tamanho de double
				fread(&dataDouble, sizeof(double), 1, dataFile);
				//Imprime o dado
				printf("%f | ", dataDouble);
				//Rotina de atualização do ponteiro
				seekCount += sizeof(double);
				fseek(dataFile, seekCount, SEEK_SET);
			}
		}
		printf("\n");
	}
}