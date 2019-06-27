#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Compilador da seÃ§Ã£o 12.27
typedef struct entradaTabela{
	int simbolo;
	char Tipo;
	int local;
} cod;

cod CodEntrada;

int cont1=0, cont2=99, t=0;
char* token;
cod tabelaSimbolos[100];

void interpretador (char* token) {
	FILE *lms = fopen("C:\\Users\\lucas\\Desktop\\Unesp\\2º Ano ~ 1º Semestre\\LP\\Projeto-LP\\Final\\lms.txt", "a");
	printf("%s", token);
	if(strcmp(token, "input")) {
		//escreve no cÃ³digo 10
		char c = strtok(toke
		if (isdigit(atoi(token))) {
			CodEntrada.simbolo = (int)token[0];
			CodEntrada.Tipo = 'c';
		}
		else {
			CodEntrada.simbolo = atoi(token);
			CodEntrada.Tipo = 'v';
		}
		if (cont1 >= 0 && cont1 < 9) fprintf(lms, "0%d-", cont1);
		else fprintf(lms, "%d-", cont1);
		cont1++;
		CodEntrada.local = cont2;
		tabelaSimbolos[t] = CodEntrada;
		t++;
		fprintf(lms, "10%d\n", cont2);
		cont2--;
	}
	else if (strcmp(token, "let")) {
	}
	else if (strcmp(token, "if")) {
		
	}
	else if (strcmp(token, "print")) {
		printf("Hey");
		//escreve 11 no cÃ³digo
		char* c = strtok(NULL, " ");
		printf("%s", c);
		int i;
		for (i=0; i<t; i++){
			if (tabelaSimbolos[i].simbolo == atoi(c)){
				if (cont1 >= 0 && cont1 < 9) fprintf(lms, "0%d-", cont1);
				else fprintf(lms, "%d-", cont1);
				fprintf(lms, "11%d\n", tabelaSimbolos[i].simbolo); //escreve tabelasimbolos[i].local;
			}
		}
		cont1++;
	}
	else if (strcmp(token, "end")) {
		if (cont1 >= 0 && cont1 < 9) fprintf(lms, "0%d-", cont1);
		else fprintf(lms, "%d-", cont1);
		fprintf(lms, "4300");
		cont1++;
		//escreve 4300
	}
	else if (strcmp(token, "goto")) {
		if (cont1 >= 0 && cont1 < 9) fprintf(lms, "0%d-", cont1);
		else fprintf(lms, "%d-", cont1);
		fprintf(lms, "4000");
		cont1++;
	}
	else if (strcmp(token, "rem")) {
		//ignora o cÃ³digo
	}
	else {
		CodEntrada.simbolo = (int) token[0];
		CodEntrada.Tipo = 'l';
		tabelaSimbolos[t] = CodEntrada;
		t++;
		if (cont1 >= 0 && cont1 < 9) fprintf(lms, "0%d-", cont1);
		fprintf(lms, "%d-", cont1);
	}
	fclose (lms);
	return;
}

int main (void) {
	//abrimos um arquivo
	char* path = "C:\\Users\\lucas\\Desktop\\Unesp\\2º Ano ~ 1º Semestre\\LP\\Projeto-LP\\Final\\simples.txt";
	FILE *simples = fopen("simples.txt", "r");
	//fazemos a leitura do mesmo
	if (simples == NULL) {
		printf("Erro");
	}
	
	char text[100];
	
	while (fgets(text, 100, simples)) {
		token = strtok (text, " ");
		interpretador(token);
		token = strtok(NULL, " ");
		interpretador(token);
	}
	fclose(simples);
	return 0;
}
