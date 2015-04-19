#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_LENGHT 128
#define MAX_RESERVED_WORD_LENGHT 64
#define MAX_TOKENS_BY_FILE 100

typedef struct S_resWords {
	int id;
	char rW[MAX_RESERVED_WORD_LENGHT];
}S_resWords;

typedef struct S_Tokens {
	int id;
	char rW;
}S_Tokens;

typedef struct S_Lex {
	char token[MAX_RESERVED_WORD_LENGHT];
	int type;
	int lineId;
	int columnId;
}S_Lex;

S_Lex G_Lex[MAX_TOKENS_BY_FILE];
S_Lex G_SymbolTable[MAX_TOKENS_BY_FILE];
int G_finalToken = 0;
int G_finalSymbol = 0;
S_resWords G_resWords[] = {
	{6, "void"},
	{6, "int"},
	{6, "float"},
	{6, "char"},
	{3, "//"},
	{3, "/*"},
	{5, "*/"},
	{4, ">="},
	{4, "<="},
	{4, "=="},
	{4, "!="},
	{4, "++"},
	{4, "--"},
	{4, "-="},
	{4, "+="},
	{4, "*="},
	{4, "/="},
	{4, "||"},
	{4, "&&"},
	{2, "return"},
	{2, "for"},
	{2, "if"}

};

S_Tokens G_Start_Tokens[] = {
	{6, '#'},
	{1, '('},
	{1, '\''},
	{10, '"'},
	{3, '<'},
	{8, '='},
	{4, ';'},
	{3, '+'},
	{4, ' '},
	{1, ')'},
	{3, '>'},
	{5, ';'},
	{3, '|'},
	{3, '&'},
	{7, ','}
};

S_Tokens G_Ignored_Tokens[] = {
	{1, '\t'},
	{2, '\0'},
	{3, ' '},
	{4, '\n'}
};
char G_tokenType[][20] = {
	"Var",
	"Literal",
	"Reserved Word",
	"Operator",
	"NU",
	"NU",
	"Type",
	"Separator",
	"NU",
	"Function",
};
int tryInsertToken(char lineBuffer [], char c);
void bufferProcess(char buffer[], int lineId);
int isAStartToken(char c);
int isAReservedWord(char cmm[]);
void buildToken(char token[], int type, int lineId, int columnId);
int isAFunction(char buffer[], int i);

int main() {
	char lineBuffer[BUFFER_LENGHT+1] = "";
	char read;
	FILE *lp = fopen("testMain.c", "r");
	int i;
	int lineId = 1;
	for(;;) {
		fread(&read, 1, 1, lp);
		if(feof(lp))
			break;
		int result = tryInsertToken(lineBuffer,read);
		if(result == 2) {
			bufferProcess(lineBuffer, lineId);
			sprintf(lineBuffer,"");
			lineId ++;
		}
		else if(result != 0) {
			printf("Erro %d\n", result);
			break;
		}
	}
	fseek(lp, 0, SEEK_END);
	bufferProcess(lineBuffer, lineId);
	FILE * pFile;
   	pFile = fopen ("tokens.txt","w");
   	fprintf(pFile, "\n---------------------Token Table---------------------\n");
	fprintf(pFile, "\n\n%20s | %20s | %10s | %10s\n\n","Token", "Type", "Line", "Column");
	for(i = 0; i < G_finalToken; i++) {
		fprintf (pFile, "%20s | %20s | %10d | %10d\n",G_Lex[i].token, G_tokenType[G_Lex[i].type], G_Lex[i].lineId, G_Lex[i].columnId);
	}
	fclose(pFile);
	pFile = fopen ("symbols.txt","w");
	fprintf(pFile, "\n---------------------Symbol Table---------------------\n");
	fprintf(pFile, "\n\n%20s | %20s\n\n","Symbol", "Type");
	for(i = 0; i < G_finalSymbol; i++) {
		fprintf(pFile, "%20s | %20s\n",G_SymbolTable[i].token, G_tokenType[G_SymbolTable[i].type]);
	}
	return 1;
}
int isAIgnoredToken(char c) {
	int i;
	for(i = 0; i < sizeof(G_Ignored_Tokens) / sizeof(S_Tokens); i++)
	{
		if(G_Ignored_Tokens[i].rW == c)
			return 1;
	}
	return 0;
}
int tryInsertToken(char lineBuffer [], char c) {
	int len = strlen(lineBuffer);
	if(len != BUFFER_LENGHT-1) {
		char str[2];
		sprintf(str, "%c",c);
		if(c == '\n')
			return 2;
		strcpy(lineBuffer + strlen(lineBuffer),str);
	}
	else
		return 1;
	return 0;
}
void bufferProcess(char buffer[], int lineId) {
	int i;
	int lineLenght = strlen(buffer);
	char lex[MAX_RESERVED_WORD_LENGHT] = "";
	int quoteReaded = 0;
	if(lineLenght > 1) {
		for(i = 0; i < lineLenght+1; i++) {
			int start = isAStartToken(buffer[i]);
			if(start == 6)//Diretiva
				break;
			if(isAReservedWord(lex) == 3)
				break;//Comentário
			if(start == 10) {//Aspa
				if(quoteReaded == 0)
					quoteReaded = 1;
			}
			if(start) {
				if(strlen(lex) > 0) {
					char str[2];
					sprintf(str, "%c",buffer[i]);
					if(isAFunction(buffer, i))
						buildToken(lex,9, lineId, i);
					else {
						if(quoteReaded == 0)
							buildToken(lex,0, lineId, i);
						else
							buildToken(lex, 1, lineId, i);
							quoteReaded = 0;
					}
					sprintf(lex,"");
				}
				else {
					if(!isAIgnoredToken(buffer[i])) {
						if(start == 3 || start == 8) {//Operando
							if(isAStartToken(buffer[i+1]) == 3 || isAStartToken(buffer[i+1]) == 8) {
								char str[3];
								sprintf(str, "%c%c",buffer[i],buffer[i+1]);
								if(isAReservedWord(str) == 4) {
									buildToken(str, 3, lineId, i);
									i++;
								}
							}
							else {
								char str[2];
								sprintf(str, "%c",buffer[i]);
								buildToken(str,3, lineId, i);
							}
						}
						if(start == 7) {
							char str[2];
							sprintf(str, "%c",buffer[i]);
							buildToken(str,7, lineId, i);
						}
					}
				}
			}
			else {
				if(!isAIgnoredToken(buffer[i])) {
					char str[2];
					sprintf(str, "%c",buffer[i]);
					strcpy(lex + strlen(lex),str);
				}
			}
		}
	}
}
void buildToken(char token[], int type, int lineId, int columnId) {
	/*
		types =
				0 = "Var",
				1 = "Literal",
				2 = "Reserved Word",
				3 = "Operator",
				4 = "Type",
				5 = "Separator",
				6 = "NU",
				7 = "Function",

	*/
	if(isdigit(token[0]))
		type = 1;
	if(type == 0 || type == 9) {
		int ntype = isAReservedWord(token);
		if(ntype == 2 || ntype == 6)
			type = ntype;
	}
	strcpy(G_Lex[G_finalToken].token,token);
	G_Lex[G_finalToken].type = type;
	G_Lex[G_finalToken].lineId = lineId;
	G_Lex[G_finalToken].columnId = columnId;
	G_finalToken ++;
	if(type == 9 || type == 0) {
		if(isOnSymbolTable(token) == 0) {
			strcpy(G_SymbolTable[G_finalSymbol].token,token);
			G_SymbolTable[G_finalSymbol].type = type;
			G_finalSymbol ++;
		}
	}
}
int isOnSymbolTable(char token[]) {
	int i;
	for(i = 0; i < G_finalSymbol; i++) {
		if(strcmp(G_SymbolTable[i].token, token) == 0)
			return 1;
	}
	return 0;
}
int isAFunction(char buffer[], int i) {
	for(; i < strlen(buffer); i++) {
		if(!isAIgnoredToken(buffer[i])) {
			if(buffer[i] == '(') {
				return 1;
			}
			break;
		}
	}
	return 0;
}
int isAEmptyToken(char token[]) {
	int len = strlen(token);	
	int i;
	for(i = 0; i <= len; i++){
		if(!isAIgnoredToken(token[i])) 
			return 0;
	}
	return 1;
}
int isAReservedWord(char cmm[]) {
	int i;
	for(i = 0; i < sizeof(G_resWords) / sizeof(S_resWords); i++)
	{
		if(strcmp(G_resWords[i].rW,cmm) == 0) {
			return G_resWords[i].id;
		}
	}
	return 0;
}

int isAStartToken(char c) {
	int i;
	for(i = 0; i < sizeof(G_Start_Tokens) / sizeof(S_Tokens); i++)
	{
		if(G_Start_Tokens[i].rW == c)
			return G_Start_Tokens[i].id;
	}
	return 0;
}
