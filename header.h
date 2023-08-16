#ifndef HEADER_H 
#define HEADER_H
 // Incluindo bibliotecas
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LINE_LENGTH 1000                          // Tamanho maximo da linha do arquivo
                         
typedef struct Filme {
    int chave;
    char nome[50];
    int ano;
    int duracao;
    char genero[20];
    struct Filme* prox;                               // Ponteiro para o proximo filme
    struct Filme* ant;                                // Ponteiro para o filme anterior
} Filme;

Filme* criarFilme(int chave, char nome[], int ano, int duracao, char genero[]);
void adicionarFilme(int chave, char nome[], int ano, int duracao, char genero[]);
void removerFilme(int chave);
void modificarFilme();
void exibirFilmes();
void limparLista();
void menu();
void limparTerminal();
void updateFile();
int readFile();
void updateList();
void transcreverTxtParaCsv(const char* txtFile, const char* csvFile);

#endif
