#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct S_State {
	char name[20];
	int isFinal;
	int isStart;
}S_State;

typedef struct S_Transition {
	char source[20];
	char symbol;
	char dest[20];
}S_Transition;

typedef struct S_DFA {
	int stateCount;
	int transitionCount;
	char alphabet[50];
	char word[50];
	S_State *states;
	int currentStateId;
	int initialStateId;
	S_Transition *transitions;
}S_DFA;

void loadStates(S_DFA *DFA, char readedFile[], int start, int end);
void loadFinalStates(S_DFA *DFA, char readedFile[], int start, int end);
void loadStartState(S_DFA *DFA, char readedFile[], int start, int end);
void loadAlphabet(S_DFA *DFA, char readedFile[], int start, int end);
void loadWord(S_DFA *DFA, char readedFile[], int start, int end);
void printStates(S_DFA *DFA);
void printTransitions(S_DFA *DFA);
void printAlphabet(S_DFA *DFA);
void printWord(S_DFA *DFA);
void loadTransitions(S_DFA *DFA, char readedFile[], int start, int end);
void processTransition(S_DFA *DFA, char readedTransition[], int position);
void processDFA(S_DFA *DFA);
int getDestState(S_DFA *DFA, char sourceStateName[], char symbol);
int getStateIdByName(S_DFA *DFA, char stateName[]);

int main() {
	S_DFA P_DFA;
	//T Transições
	//Estado Inicial | {ALFABETO} |{ESTADO0,ESTADO1,ESTADO2,...} | {ESTADOFINAL1,ESTADOFINAL2,...} | {T1{ORIGEM>SIMBOLO>DESTINO};T2{ORIGEM>SIMBOLO>DESTINO}...} | {PALAVRA} #
	char readedFile[1000] = "s0|&abcdef|s0,s1,s2,s3,s4,s5|s4,s5,s2|s0>a>s1;s0>b>s2;s1>a>s2;s2>a>s3;s3>b>s4;s4>a>s1|aaabaa#";
	int i;
	char starts[6]  /*
						0 = Read Inital State
						1 = Read Alphabet
						2 = Read States
						3 = Read Final States
						4 = Read Transitions
						5 = Read Word
					*/;
	starts[0] = 0;
	char aux = 1;
	for(i = 0; i < strlen(readedFile); i++)	{
		if(aux == 6)
			break;
		if(readedFile[i] == '|') {
			starts[aux] = i;
			aux++;
		}
	}
	P_DFA.stateCount = getStateCount(readedFile, starts[2], starts[3]);
	P_DFA.transitionCount = getTransitionCount(readedFile, starts[4], starts[5]);
	P_DFA.states = (S_State*)malloc(sizeof(S_State) * P_DFA.stateCount);
	P_DFA.transitions = (S_Transition*)malloc(sizeof(S_Transition) * P_DFA.transitionCount);
	loadStates(&P_DFA, readedFile, starts[2]+1, starts[3]);
	loadTransitions(&P_DFA, readedFile, starts[4]+1, starts[5]);
	loadStartState(&P_DFA, readedFile, 0, starts[1]);
	loadFinalStates(&P_DFA, readedFile, starts[3]+1, starts[4]);
	loadAlphabet(&P_DFA, readedFile, starts[1]+1, starts[2]);
	loadWord(&P_DFA, readedFile, starts[5]+1, strlen(readedFile));
	printStates(&P_DFA);
	printTransitions(&P_DFA);
	printAlphabet(&P_DFA);
	printWord(&P_DFA);
	processDFA(&P_DFA);


	/*char read;
	FILE *lp = fopen("DFA.txt", "r");
	for(;;) {
		fread(&read, 1, 1, lp);
		if(feof(lp))
			break;
	}
	fseek(lp, 0, SEEK_END);*/
	return 0;
}
void processDFA(S_DFA *DFA) {
	int head;
	DFA->currentStateId = DFA->initialStateId;
	for(head = 0; head < strlen(DFA->word); head++) {
		printf("[[[Estado atual %s, simbolo atual %c\n", DFA->states[DFA->currentStateId].name, DFA->word[head]);
		int destState = getDestState(DFA, DFA->states[DFA->currentStateId].name, DFA->word[head]);
		if(destState >= 0) {
			DFA->currentStateId = destState;
		}
		else {
			printf("Automato nao aceita a palavra %s [SEM TRANSICOES PARA %s com %c]\n", DFA->word, DFA->states[DFA->currentStateId].name, DFA->word[head]);
			return;
		}
	}
	if(DFA->states[DFA->currentStateId].isFinal == 1)
		printf("Automato aceitou a palavra %s", DFA->word);
	else
		printf("Automato nao aceita a palavra %s [ESTADO %s NAO TERMINAL]\n", DFA->word, DFA->states[DFA->currentStateId].name);



}
int getDestState(S_DFA *DFA, char sourceStateName[], char symbol) {
	int i;
	for(i = 0; i < DFA->transitionCount; i++)
		if(strcmp(DFA->transitions[i].source, sourceStateName) == 0) 
			if(DFA->transitions[i].symbol == symbol)
				return getStateIdByName(DFA, DFA->transitions[i].dest);
	return -1;
}
int getStateIdByName(S_DFA *DFA, char stateName[]) {
	int i;
	for(i = 0; i < DFA->stateCount; i++) {
		if(strcmp(DFA->states[i].name, stateName) == 0) {
			return i;
		}
	}
	return -1;
}
void printStates(S_DFA *DFA) {
	int i;
	printf("Existem %d estados\n\n", DFA->stateCount);
	for(i = 0; i < DFA->stateCount; i++) {
		printf("Estado [%s]", DFA->states[i].name);
		if(DFA->states[i].isStart == 1)
			printf(" [INICIAL]");
		if(DFA->states[i].isFinal == 1)
			printf(" [FINAL]");
		printf("\n");
	}
}
void printTransitions(S_DFA *DFA) {
	int i;
	printf("Existem %d transicoes\n\n", DFA->transitionCount);
	for(i = 0; i < DFA->transitionCount; i++) {
		printf("Transicao: Origem = %s\tSimbolo = %c\tDestino = %s\n", DFA->transitions[i].source, DFA->transitions[i].symbol, DFA->transitions[i].dest);
	}
}
void printAlphabet(S_DFA *DFA) {
	int i;
	printf("Existem %d simbolos no alfabeto\n\n", strlen(DFA->alphabet));
	for(i = 0; i < strlen(DFA->alphabet); i++) {
		printf("Simbolo [%c]\n", DFA->alphabet[i]);
	}
}
void printWord(S_DFA *DFA) {
	int i;
	printf("Palavra de tamanho %d\n\n", strlen(DFA->word));
	for(i = 0; i < strlen(DFA->word); i++) {
		printf("Simbolo [%c]\n", DFA->word[i]);
	}
}
void loadStates(S_DFA *DFA, char readedFile[], int start, int end) {
	int i;
	int aux = 0;
	char readedState[20] = "";
	for(i = start; i <= end; i++) {
		if(readedFile[i] == ',' || readedFile[i] == '|') {
			sprintf(DFA->states[aux].name, "%s", readedState);
			sprintf(readedState,"");
			aux++;
			i++;
		}
		sprintf(readedState, "%s%c",readedState, readedFile[i]);
	}
}
void loadTransitions(S_DFA *DFA, char readedFile[], int start, int end) {
	int i;
	int aux = 0;
	char readedTransition[50] = "";
	for(i = start; i <= end; i++) {
		if(readedFile[i] == ';' || readedFile[i] == '|') {
			sprintf(readedTransition, "%s%c",readedTransition,'>');
			processTransition(DFA, readedTransition,aux);
			sprintf(readedTransition,"");
			aux++;
			i++;
		}
		sprintf(readedTransition, "%s%c",readedTransition, readedFile[i]);
	}
}
void processTransition(S_DFA *DFA, char readedTransition[], int position) {
	int i;
	int readControl = 0;
	char readedToken[20];
	for(i = 0; i <= strlen(readedTransition); i++) {
		if(readedTransition[i] == '>' || readedTransition[i] == ';') {
			if(readControl == 0) {
				sprintf(DFA->transitions[position].source, "%s",readedToken);
				readControl = 1;
			}
			else if(readControl == 1) {
				DFA->transitions[position].symbol = readedToken[0];
				readControl = 2;
			}
			else if(readControl == 2) {
				sprintf(DFA->transitions[position].dest, "%s",readedToken);
			}
			sprintf(readedToken,"");
			i++;
		}
		sprintf(readedToken, "%s%c", readedToken, readedTransition[i]);
	}
}
void loadFinalStates(S_DFA *DFA, char readedFile[], int start, int end) {
	int i, j;
	char readedState[20] = "";
	for(i = start; i <= end; i++) {
		if(readedFile[i] == ',' || readedFile[i] == '|') {
			for(j = 0; j < DFA->stateCount; j++) {
				if(strcmp(DFA->states[j].name,readedState) == 0)
					DFA->states[j].isFinal = 1;
			}
			sprintf(readedState,"");
			i++;
		}
		sprintf(readedState, "%s%c",readedState, readedFile[i]);
	}
}
void loadStartState(S_DFA *DFA, char readedFile[], int start, int end) {
	int i, j;
	char readedState[20] = "";
	for(i = start; i <= end; i++) {
		if(readedFile[i] == '|') {
			for(j = 0; j < DFA->stateCount; j++) {
				if(strcmp(DFA->states[j].name,readedState) == 0){
					DFA->states[j].isStart = 1;
					DFA->initialStateId = j;
				}
				else
					DFA->states[j].isStart = 0;
			}
			sprintf(readedState,"");
		}
		sprintf(readedState, "%s%c",readedState, readedFile[i]);
	}
}
void loadAlphabet(S_DFA *DFA, char readedFile[], int start, int end) {
	int i, j;
	char readedAlphabet[50] = "";
	for(i = start; i <= end; i++) {
		if(readedFile[i] == '|') {
			sprintf(DFA->alphabet, "%s", readedAlphabet);
		}
		sprintf(readedAlphabet, "%s%c",readedAlphabet, readedFile[i]);
	}
}
void loadWord(S_DFA *DFA, char readedFile[], int start, int end) {
	int i, j;
	char readedWord[50] = "";
	for(i = start; i <= end; i++) {
		if(readedFile[i] == '#') {
			sprintf(DFA->word, "%s", readedWord);
		}
		sprintf(readedWord, "%s%c",readedWord, readedFile[i]);
	}
}
int getStateCount(char readedFile[], int start, int end) {
	int i;
	int count = 0;
	for(i = start; i < end; i++) {
		if(readedFile[i] == ',')
			count++;
	}
	return count+1;
}
int getTransitionCount(char readedFile[], int start, int end) {
	int i;
	int count = 0;
	for(i = start; i < end; i++) {
		if(readedFile[i] == ';')
			count++;
	}
	return count+1;
}