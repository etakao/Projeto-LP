//Seção 7.28

#include <stdio.h>
#include <stdlib.h>

#define TAM 100

// Operações de entrada/saída
#define READ  10
#define WRITE  11
// Operações de carregamento/armazenamento
#define LOAD  20
#define STORE  21
// Operações aritméticas
#define ADD  30
#define SUBTRACT  31
#define DIVIDE  32
#define MULTIPLY  33
// Operações de transferência de controle
#define BRANCH  40
#define BRANCHNEG  41
#define BRANCHZERO  42
#define HALT  43

int check(int palavra, int tamanho);
void escrever(int acc, int contador, int mem[]);

int main(void)
{
   int memoria[TAM] = { 0 }, i, err = 0;

   int codOp = 0, regI = 0;
   int acumulador = 0, operando = 0;

   printf("*** Bem vindo ao Simpletron! ***\n"
	  "*** Favor digitar seu programa, uma instrução ***\n"
	  "*** (ou palavra de dados) por vez. Mostrarei ***\n"
	  "*** o número do local e uma interrogação (?).  ***\n"
	  "*** Você, então, deverá digitar a palavra para esse ***\n"
	  "*** local. Digite a sentinela -99999 para ***\n"
	  "*** encerrar a entrada do seu programa. ***\n");
	   
   for(i = 0; i < TAM; i++) {
      while(1) {
         printf("%.2d ?? ", i);
         scanf("%d", &memoria[i]);

	 if(memoria[i] == -99999) {
	    memoria[i] = 0;
	    i = TAM;
	    break;
	 }

	 if( check(memoria[i], TAM) ) {
	    printf("Instrução inválida: %d\n", memoria[i]);
	    printf("Por favor digite novamente.\n");
	 }
	 else
	    break;

      }
   }

   printf("*** Programa completamente carregado ***\n"
	  "*** Começo da execução do programa  ***\n");

   for(i = 0; i < TAM; i++) {
      regI = memoria[i];

      codOp = regI / 100;
      operando = regI % 100;

      if(codOp >= BRANCH)
         --operando;

      switch(codOp) {
	 case READ:
	    printf("Digite uma palavra: ");
            scanf("%d", &memoria[operando]);

	    break;
	 case WRITE:
	    printf("\nLocal de memória: %.2d\nPalavra: %d\nASCII: %c\n",
	       operando, memoria[operando], memoria[operando]);
	    break;
	 case LOAD:
	    acumulador = memoria[operando];
	    break;
	 case STORE:
	    memoria[operando] = acumulador;
	    break;

	 case ADD:
	    acumulador += memoria[operando];

	    if(acumulador > +9999 || acumulador -9999)
	       err = 1;

	    break;
	 case SUBTRACT:
	    acumulador -= memoria[operando];

	    if(acumulador > +9999 || acumulador -9999)
	       err = 1;

	    break;
	 case DIVIDE:
	    acumulador /= memoria[operando];

	    if( !memoria[operando] )
	       err = 2;

	    break;
	 case MULTIPLY:
	    acumulador *= memoria[operando];

	    if(acumulador > +9999 || acumulador -9999)
	       err = 1;

	    break;

	 case BRANCH:
	    i = operando;
	    break;
	 case BRANCHNEG:
	    if(acumulador < 0)
	       i = operando;

	    break;
	 case BRANCHZERO:
	    if(!acumulador)
	       i = operando;

            break;

	 case HALT:
	    printf("*** Execução do Simpletron terminada ***\n");
	    escrever(acumulador, i, memoria);
	    return 0;

            break;
	 case 0:
	    break;

	 default:
	    printf("*** Erro desconhecido: %d\n", regI);
	    exit(-1);
      }

      //checagem de erros
      if(err) {
	 switch(err) {
	    case 1:
               printf("*** Fora do limite do acumulador ***\n"); 
	       break;
	    case 2:
	       printf("*** Divisão por zero ***\n");
	       break;
	 }
	 
         printf("*** Execução do simpletron finalizada por motivos desconhecidos***\n");
         escrever(acumulador, i, memoria);
         exit(-1);
      }


   }

   escrever(acumulador, i, memoria);

   return 0;
}


int check(int palavra, int tamanho)
{
   if(palavra < 0 || palavra > 9999 || palavra % 100 >= tamanho) {
      return 1;
   }

   switch(palavra / 100) {
      case READ:
      case WRITE:
      case LOAD:
      case STORE:
      case ADD:
      case SUBTRACT:
      case DIVIDE:
      case MULTIPLY:
      case BRANCH:
      case BRANCHNEG:
      case BRANCHZERO:
      case HALT:
      case 0:
         break;
      default:
	 return 1;

   }

   return 0;

}

void escrever(int acc, int contador, int mem[])
{
   int i, j;

   printf("\nRegistradores:\n");
   printf("acumulador\t\t%c%.4d\n"
	  "instructionCounter\t%.2d\n"
	  "Registrador de Instrução\t%c%.4d\n"
	  "Código de Operações\t\t%.2d\n"
	  "operando\t\t\t%.2d\n",
	  acc < 0 ? '-' : '+', acc < 0 ? -acc : acc,
	  contador, mem[contador] < 0 ? '-' : '+',
	  mem[contador] < 0 ? -mem[contador] : mem[contador],
	  mem[contador] / 100, mem[contador] % 100);
      

   printf("\nMEMÓRIA:\n");

   printf("%3c", ' ');
   for(i = 0; i < 10; i++)
      printf("%5d ", i);
   printf("\n");

   for(i = 0; i < TAM; i += 10) {
      printf("%.2d", i);
      for(j = i; j < i+10; j++) {
	 printf(" %c%.4d",
	    mem[j] < 0 ? '-' : '+', mem[j] < 0 ? -mem[j] : mem[j]);
      }
      printf("\n");
   }

}
