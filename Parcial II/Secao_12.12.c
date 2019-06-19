#include<stdio.h>
#include<conio.h>
#include<ctype.h>
 
struct stackNode
{
    char data;
    struct stackNode *nextPtr;
};

typedef struct stackNode StackNode;
typedef StackNode *StackNodePtr;

void convertToPostfix(char infix[],char postfix[]); /* Converte a expressao infixa para notacao pos-fixa */
int isOperator(char c); /* Determina se c é um operador */
int precedence(char operator1, char operator2);  /* Determina se a precedencia do operator1 é menor, igual ou maior do que a de operator2 */
void push(StackNodePtr *topPtr, char value); /* Insere um valor na pilha */
int isEmpty(StackNodePtr topPtr); /* Determina se a pilha está vazia */
int pop(StackNodePtr *topPtr); /* Retira um valor da pilha */
char stackTop(StackNodePtr topPtr); /* Retoma o valor do topo da pilha sem retirá-lo da pilha */
void printStack(StackNodePtr topPtr); /* Imprime a pilha */
int returnLenght( char [], int ); /* Retorna o tamanho do array */

void main()
{
    char infix[20],postfix[20];
    printf("Introduza uma expressao infixada: ");
    returnLenght(infix, 50); 

    convertToPostfix(infix, postfix); 
    printf("A expressao posfixada eh: %s\n", postfix);
    
}
 
void convertToPostfix(char infix[],char postfix[])
{
    int i = 0, j = 0;   
    char c;

    StackNodePtr stackPtr = NULL;
    push(&stackPtr, '('); 
    
    while(infix[i] != '\0')
        i++;

    infix[i++] = ')';
    infix[i] = '\0';
    
    i=0;
    
    while(!isEmpty(stackPtr) && infix[i] != '\0')
    {
        c = infix[i++];
        
        if(isdigit(c)) 
        {
            while(isdigit(c)) {
                postfix[j++] = c;
                c = infix[i++];
            }
            postfix[j++] = ' ';
            
            if(c == ')' || isOperator(c))
                i--;
        }
        else if(c == '(')
            push(&stackPtr, '(');
        else if(isOperator(c) == 1) 
        {
            if( !isEmpty(stackPtr) && isOperator(stackTop(stackPtr))) {
                while(isOperator(stackTop(stackPtr)) && 
                       (precedence(stackTop(stackPtr), c)) >= 0) 
                {
                    postfix[j++] = pop(&stackPtr);
                    postfix[j++] = ' ';
                }
                push(&stackPtr, c);
            }
            else
                push(&stackPtr, c);
        }
        else if( c == ')') 
        {
            if(!isEmpty(stackPtr)) 
            {
                c = pop(&stackPtr); 

                while(!isEmpty(stackPtr) && c != '(') {
                    postfix[j++] = c;
                    postfix[j++] = ' ';
                    c = pop(&stackPtr); 
                }
            }
        }
    }
    postfix[j] = '\0';
} 

int isOperator(char c){
    if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '%') 
        return 1;
    return 0;
}

int precedence(char operator1, char operator2)
{
    int resultado = 1;

    switch( operator1 )
    {
        case '^':
            if(operator2 == '^') resultado = 0;
            break;
        case '*': case '/': case '%':
            switch(operator2) {
                case '^':
                    resultado = -1;
                    break;
                case '*': case '/': case '%':
                    resultado = 0;
                    break;
                default:
                    break;
            }
            break;
        case '+': case '-': 
            switch(operator2) {
                case '-': case '+':
                    resultado = 0;
                    break;
                default:
                    resultado = -1;
                    break;
            }
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

int isEmpty(StackNodePtr topPtr){
    return topPtr == NULL;
}

int pop(StackNodePtr *topPtr){
    StackNodePtr tempPtr;
    int popValue;

    tempPtr = *topPtr;
    popValue = (*topPtr)->data;
    *topPtr = (*topPtr)->nextPtr;
    free(tempPtr);

    return popValue;
}

char stackTop(StackNodePtr topPtr){
    char topValue;

    topValue = topPtr->data;

    return topValue;
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
 

