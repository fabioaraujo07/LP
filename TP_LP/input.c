#include <stdio.h>
#include <string.h>

#define INVALID_VALUE "O valor inserido é inválido."


/**
 * Esta função apaga o terminal
*/
void clearConsole() {
    system("cls || clear");
}


// Esta função apaga qualquer tipo de caratere lido no stdinput
void cleanInputBuffer() {
    char ch;
    while ((ch = getchar()) != '\n' && ch != EOF);
}

// Função para ler um número pedido ao utilizador
int getInt(int minValor, int maxValor, char *msg){
    int valor;
    printf(msg);
    while(scanf("%d", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

//Função para obter um número do tipo float
float obterFloat(float minValor, float maxValor, char *msg){
    float valor;
    printf(msg);
    while(scanf("%f", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

// Função para obter um número do tipo double
double obterDouble(double minValor, double maxValor, char *msg) {
    double valor;
    printf(msg);
    while(scanf("%lf", &valor) != 1 || valor < minValor || valor > maxValor) {
        puts(INVALID_VALUE);
        cleanInputBuffer();
        printf(msg);
    }
    cleanInputBuffer();
    return valor;
}

// Função para obter carateres
char obterChar(char *msg){
    char valor;
    printf(msg);
    valor = getchar();
    cleanInputBuffer();
    return valor;
}

// Função utilizada para ler string
void readString(char *string, unsigned int tamanho, char *msg) {
    
    printf(msg);
    if (fgets(string, tamanho, stdin) != NULL) {
        unsigned int len = strlen(string) - 1;
        if (string[len] == '\n') {
            string[len] = '\0';
        } else {
            cleanInputBuffer();
        }
    }
}

