#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#define MAX 1000
/* Define um novo tipo de dado chamado Pilha que é um ponteiro para "struct pilha". */
typedef struct node * link;

struct node{
    int item;       /* t é o topo da pilha -- proximo espaco vazio do vetor */
    link baixo;     /* v é o vetor que armazena os elementos da pilha */
};

typedef struct{
    link topo;
} *Pilha;

/* Aloca espaço para armazenar uma nova Pilha */
Pilha novaPilha () {
    Pilha p = malloc(sizeof(*p));
    if (p == NULL){
        printf("Algum erro aconteceu !\n");
        exit(-1);
    }
    p->topo = NULL; /* devemos inicializar o topo com 0 */
    return p;
}
/* Libera memória de uma dada pilha p */
void destroiPilha (Pilha p){
    free(p);
}
/* Operação de inserir novo elemento na pilha */
void push (Pilha p, int valor){
    link n =  malloc(sizeof * n);
    n->item = valor;
    n->baixo = p->topo;
    p->topo = n;
}
/* Operação de remover um elemento da pilha */
int pop (Pilha p) {
    int valor;
    if(p == NULL){
        printf("Pilha vazia!!!!");
        exit(-1);
    }
    link n;

    n = p->topo;
    valor = n->item;
    p->topo = p->topo->baixo;
    free(n);

    return valor;
}
int topo (Pilha p) {
    return p->topo->item;
}
/* Transforma a notação infixa para a notação posfixa */
int infixoParaPosfixo (char * entrada, char * saida, int n)
{
    Pilha p = novaPilha();
    int i,k;
    int j = 0;
    char c;
    push(p, '(');
    for (i = 0; entrada[i] != '\0' &&  i < n; i++)
        {
            if((j-1 > 0) && (saida[j-1] != ' '))
                saida[j++]  = ' ';
            if(entrada[i] == '(') {
                push(p, entrada[i]);
            } else if(entrada[i] == ')'){
                while (1) {
                    c = pop(p);
                    if(c == '(') break;
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
            } else if((entrada[i] == '+') || (entrada[i] == '-')){
                while (1) {
                    c = topo(p);
                    if(c == '(') break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if((entrada[i] == '*') || (entrada[i] == '/')) {
                while (1) {
                    c = topo(p);
                    if(c == '(' || c == '+' || c == '-'  ) break;
                    pop(p);
                    saida[j++] = c;
                    saida[j++] = ' ';
                }
                push(p, entrada[i]);
            } else if (entrada[i] >= '0' && entrada[i] <= '9') {
                while (entrada[i] >= '0' && entrada[i] <= '9') {
                    saida[j++] = entrada[i];
                    i++;
                }
                saida[j++] = ' ';
                i--;
            }

        }
    while (1) {
        c = pop(p);
        if(c == '(') break;
        saida[j++] = c;
        saida[j++] = ' ';
    }
    saida[j] = '\0';
    destroiPilha(p);
    return 0;
}

int bemEncaixado (char* s) {
    Pilha p = novaPilha();
    int i;
    int resultado = 1;
    for(i = 0; s[i] != '\0'; i++) {
        if(s[i] == '(') {
            if(p->t >= MAX) {
                resultado = 0;
                break;
            }
            push(p, 1);
        } else if (s[i] == ')') {
            if(p->t <= 0) {
                resultado = 0;
                break;
            }
            pop(p);
        }
    }
    if(p->t > 0)
        resultado = 0;
    destroiPilha(p);
    return resultado;
}


int calcula ( char * s ) {
    int i = 0;
    int d = 0,k;
    int numero = 0;
    Pilha p = novaPilha();
    int resultado ;
    int a,b;
    while  (s[i] != '\0') {
        if(s[i] >= '0' && s[i] <= '9' ) {
            sscanf(&s[i], "%d", & numero);
            while(s[i] >= '0' && s[i] <= '9')
                i++;
            i--;
            push(p, numero);
        } else if (s[i] == '+') {
            b = pop(p);
            a = pop(p);
            push (p, a + b);
        } else if (s[i] == '-') {
            b = pop(p);
            a = pop(p);
            push (p, a - b);
        } else if (s[i] == '*') {
            b = pop(p);
            a = pop(p);
            push (p, a * b);
        } else if (s[i] == '/') {
            b = pop(p);
            a = pop(p);
            push (p, a/b);
        }
        i++;
    }

    resultado = topo(p);
    destroiPilha(p);
    return resultado;
}

/* Exemplo de utilização */
int main () {
    char infixo[255] ;
    char posfixo[255];
    printf("Sou uma calculadora de inteiros implementado com pilha!\n");
    printf("Digite quit para sair !\n");
    printf ("> ");
    while(fgets(infixo, 255, stdin) != NULL) {
        if(strcmp(infixo, "quit\n") == 0)  {
            printf ("morri !\n");
            return 0;
        }
        if(bemEncaixado(infixo)) {
            infixoParaPosfixo(infixo, posfixo, 255);
            printf("%d\n", calcula(posfixo));
        } else
            printf ("Erro nos parenteses\n");
        printf ("> ");
    }
    return 0;
}
