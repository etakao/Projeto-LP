#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>    
#include <math.h>     

struct stackNode {
    int data;
    struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;


int evaluatePostfixExpression(char *expr); /* Avalia a expressão pós-fixa */
int calculate(int op1, int op2, char operator); /* Avalia a expressão op1 operador op2 */
void push(StackNodePtr *topPtr, char value); /* Insere um valor na pilha */
int pop(StackNodePtr *topPtr); /* Retira um valor da pilha */
int isEmpty(StackNodePtr topPtr); /* Determina se a pilha está vazia */
void printStack(StackNodePtr topPtr); /* Imprime a pilha */
int returnLenght(char [], int maxLenght); /* Retorna o tamanho do array */
int isOperator(char c); /* Determina se c é um operador */

int main()
{
    char postfix[50];
    int resultado;
    
    printf("Introduza uma expressao pos-fixada, com os devidos espacamentos \nentre os operandos e operadores (ex.: 8 9 2 * +): ");
    returnLenght(postfix, 50); 
    
    resultado = evaluatePostfixExpression(postfix);
    printf("Resultado: %d\n", resultado);
    
    return 0;
}

int evaluatePostfixExpression(char *expr)
{
    StackNodePtr stackPtr = NULL;
    char c;
    int x, y;
    int i=0, mult=1, num=0;
    
    while(expr[i] != '\0')
    {
        mult=1; num=0;
        c = expr[i];
        if(isdigit(c)) 
        {
            while(isdigit(c)) 
            {
                num *= mult;
                num += c-48;
                c = expr[++i];
                mult *= 10;
            }
            --i;
            push(&stackPtr, num);
        }
        else if(isOperator(c))
        {
            if(isEmpty(stackPtr)) {
                printf("Expressao pos-fixada invalida!!\n");
                return 0;
            }
            x = pop(&stackPtr);
            
            if(isEmpty(stackPtr)) {
                printf("Expressao pos-fixada invalida!!\n");
                return 0;
            }
            y = pop(&stackPtr);
            
            push(&stackPtr, calculate(y, x, c));
        }
        i++;
    }
    
    if(isEmpty(stackPtr)) {
        printf("Expressao pos-fixada invalida!!\n");
        return 0;
    }
    
    return pop(&stackPtr);
}

int calculate(int op1, int op2, char operator)
{
    int resultado = 0;
    
    switch(operator)
    {
        case '+':
            resultado = op1 + op2;
            break;
        case '-':
            resultado = op1 - op2;
            break;
        case '*':
            resultado = op1 * op2;
            break;
        case '/':
            resultado = op1 / op2;
            break;
        case '^':
            resultado = pow( op1, op2 );
            break;
        case '%':
            resultado = op1 % op2;
            break;
        default:
            break;
    }
    
    return resultado;
}

void push(StackNodePtr *topPtr, char value)
{
    StackNodePtr newPtr;

    newPtr = malloc(sizeof(StackNode));

    if(newPtr != NULL){
        newPtr->data = value;
        newPtr->nextPtr = *topPtr;
        *topPtr = newPtr;
    }
    else
        printf("%d não inserido. Nenhuma memória disponível.\n", value);
}

int pop(StackNodePtr *topPtr)
{
    StackNodePtr tempPtr;
    int popValue;
    
    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free( tempPtr );
    
    return popValue;
}

int isEmpty(StackNodePtr topPtr)
{
    return topPtr == NULL;
}

void printStack(StackNodePtr topPtr){
    if(topPtr == NULL){
        printf("A pilha está vazia.\n\n");
    }
    else{
        printf("A expressão pos-fixada fica:\n");

        while(topPtr != NULL){
            printf("%d ", topPtr->data);
            topPtr = topPtr->nextPtr;
        }
    }
}

int returnLenght( char s[], int maxLength )
{
    int c, i=0;
    
    while( ( --maxLength > 0)  && ( (c=getchar())!=EOF ) && ( c!='\n' ) )
        s[i++]=c;

    s[i] = '\0';
    
    fflush(stdin);
    
    return i;   
}

int isOperator(char c){
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') 
        return 1;
    return 0;
}
