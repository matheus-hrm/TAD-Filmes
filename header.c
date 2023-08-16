#include "header.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Filme* listaFilmes = NULL;                            // Inicializando a lista de filmes
const char *txtFile = "filmes.txt";                   // Nome do arquivo de texto
const char *csvFile = "filmes.csv";                   // Nome do arquivo csv


/**
 * @brief Funcao para inicializar a lista de filmes
 * 
 * Essa funcao recebe os dados de um filme e cria um novo filme com esses dados.
 * 
 * @param chave Chave para identificar o filme
 * @param nome Nome do filme
 * @param ano Ano de lancamento do filme
 * @param duracao Duracao do filme em minutos
 * @param genero Genero do filme
 * @return Retorna um ponteiro para o filme criado
*/
 
Filme* criarFilme(int chave, char nome[], int ano, int duracao, char genero[]) { 
    Filme* novoFilme = (Filme*)malloc(sizeof(Filme)); 
    novoFilme->chave = chave;                         // Atribuindo os valores ao novo filme
    strcpy(novoFilme->nome, nome);                    // A funcao strcpy copia o conteudo de uma string para outra
    novoFilme->ano = ano;                             
    novoFilme->duracao = duracao;                     
    strcpy(novoFilme->genero, genero);
    novoFilme->prox = NULL;                           // O novo filme nao tem um proximo filme
    novoFilme->ant = NULL;                            // O novo filme nao tem um filme anterior
    return novoFilme;
}

/**
 * @brief Funcao para adicionar um filme a lista de filmes
 * 
 * Essa funcao recebe os dados de um filme e cria um novo filme com esses dados.
 * 
 * Se a lista de filmes estiver vazia, o novo filme sera o primeiro da lista.
 * Senão, o novo filme sera adicionado ao final da lista.
 * o @param atual é um ponteiro que percorre a lista de filmes ate o ultimo filme.
 * 
*/

void adicionarFilme(int chave, char nome[], int ano, int duracao, char genero[]) {
    Filme* novoFilme = criarFilme(chave, nome, ano, duracao, genero); 
    
    if (listaFilmes == NULL) {
        listaFilmes = novoFilme; 
    } else { 
        Filme* atual = listaFilmes;
        while (atual->prox != NULL) { 
            atual = atual->prox;                      // Percorrendo a lista de filmes
        }
        atual->prox = novoFilme;                      // Adicionando o novo filme ao final da lista
        novoFilme->ant = atual;                       // O filme anterior ao novo filme sera o ultimo filme da lista
    }
}

/**
 * @brief Funcao menu
 * 
 * Essa funcao exibe um menu com as opcoes para o usuario escolher.
 * 
*/

void menu(){
  int opcao, chave, ano, duracao;
  char nome[50], genero[20];
  
    while(opcao != 5){
        printf("\n\n=============================\n");
        printf("MENU:\n");
        printf("1. Adicionar Filme\n");
        printf("2. Remover Filme\n");
        printf("3. Modificar Filme\n");
        printf("4. Exibir Filmes\n");
        printf("5. Sair\n");
        printf("Escolha uma opcao: ");
        printf("\n=============================\n");
        scanf("%d", &opcao);
        
        switch (opcao) {
            case 1:                                   // Adicionando um filme à lista
                printf("Chave: ");                    // A chave sera usada para identificar o filme
                scanf("%d", &chave);
                printf("Nome: ");
                scanf(" %[^\n]", nome);
                printf("Ano de lancamento: ");
                scanf("%d", &ano);
                printf("Duracao em min: ");
                scanf("%d", &duracao);
                printf("Genero: ");
                scanf(" %[^\n]", genero);
                adicionarFilme(chave, nome, ano, duracao, genero);
                updateFile();
                limparTerminal(); 
                printf("Filme adicionado com sucesso.\n"); 
                menu();
                break;
            case 2:                                   // Removendo um filme da lista
                printf("Chave do filme a ser removido: ");
                scanf("%d", &chave);
                removerFilme(chave);                 
                menu();
                break;
            case 3:                                   // Modificando um filme da lista
                modificarFilme(); 
                menu();
                break;
            case 4:                                   // Exibindo a lista de filmes
                exibirFilmes();
                menu();
                break;
            case 5:                                   // Encerrando o programa
                transcreverTxtParaCsv(txtFile, csvFile); // Transcrevendo o arquivo de texto para csv
                limparLista();
                limparTerminal();
                printf("Encerrando o programa.\n");
                exit(0);
            default:
                printf("Opcao inválida. Tente novamente.\n");
                break;
        }
        printf("\n");
    }
}



void removerFilme(int chave) {
    Filme* atual = listaFilmes;                       // cria um ponteiro para o primeiro filme da lista
    while (atual != NULL) {                           // percorre a lista de filmes
        if (atual->chave == chave) { 
            if (atual->ant == NULL) {                 // se o filme a ser removido for o primeiro da lista
                listaFilmes = atual->prox;            // o primeiro filme da lista sera o proximo filme do filme a ser removido
                if (atual->prox != NULL) {            // se o filme a ser removido nao for o ultimo da lista
                    atual->prox->ant = NULL;          // o filme anterior ao proximo filme do filme a ser removido sera NULL
                }
            } else if (atual->prox == NULL) {         // se o filme a ser removido for o ultimo da lista
                atual->ant->prox = NULL;              // o proximo filme do filme anterior ao filme a ser removido sera NULL
            } else {                                  // se o filme a ser removido nao for o primeiro nem o ultimo da lista
                atual->ant->prox = atual->prox;       // o proximo filme do filme anterior ao filme a ser removido sera o proximo filme do filme a ser removido
                atual->prox->ant = atual->ant;        // o filme anterior ao proximo filme do filme a ser removido sera o filme anterior ao filme a ser removido
            }
            free(atual);                              // libera o espaco de memoria do filme a ser removido
            updateFile();
            printf("Filme removido com sucesso.\n");
            return;
        }
        atual = atual->prox;                          // vai para o proximo filme da lista
    }
    printf("Filme nao encontrado.\n");
}

void modificarFilme() {
    int chave, opcao, ano, duracao;
    char nome[50], genero[20];
    printf("Chave do filme a ser modificado: ");
    scanf("%d", &chave);
    Filme* atual = listaFilmes;                       // cria um ponteiro para o primeiro filme da lista
    while (atual != NULL) {                           // percorre a lista de filmes
        if (atual->chave == chave) { 
            printf("O que deseja modificar?\n");
            printf("1. Nome\n");
            printf("2. Ano de lancamento\n");
            printf("3. Duracao\n");
            printf("4. Genero\n");
            printf("5. Sair\n");
            scanf("%d", &opcao);
            switch (opcao) {
                case 1:                               // Modificando o nome do filme
                    printf("Novo nome: ");
                    scanf(" %[^\n]", nome);
                    strcpy(atual->nome, nome);
                    break;
                case 2:                               // Modificando o ano de lancamento do filme
                    printf("Novo ano de lancamento: ");
                    scanf("%d", &ano);
                    atual->ano = ano;
                    break;
                case 3:                               // Modificando a duracao do filme
                    printf("Nova duracao: ");
                    scanf("%d", &duracao);
                    atual->duracao = duracao;
                    break;
                case 4:                               // Modificando o genero do filme
                    printf("Novo genero: ");
                    scanf(" %[^\n]", genero);
                    strcpy(atual->genero, genero);
                    break;
                case 5:                               // Encerrando a funcao
                    return;
                default:
                    printf("Opcao inválida. Tente novamente.\n");
                    break;
            }
            updateFile();
            printf("Filme modificado com sucesso.\n");
            return;
        }
        atual = atual->prox;                          // vai para o proximo filme da lista
    }   

}

void exibirFilmes() {
    FILE *arquivo;
    arquivo = fopen("filmes.txt", "r");               // Abre o arquivo para leitura
    if (arquivo == NULL) {                            // Se o arquivo nao existir
        printf("Erro ao abrir o arquivo.\n");         // Exibe uma mensagem de erro
        exit(1);                                      // Encerra o programa
    }
    char linha[100];                                  // Cria um vetor de caracteres para armazenar cada linha do arquivo
    while (fgets(linha, 100, arquivo) != NULL) {      // Enquanto nao chegar ao final do arquivo
        printf("%s", linha);                          // Exibe a linha
    }
    if (listaFilmes == NULL) {                        // Se a lista de filmes estiver vazia
        printf("Nenhum filme cadastrado na memória.\n");         // Exibe uma mensagem de erro
    }
    fclose(arquivo);                                  // Fecha o arquivo
}

void limparLista() { 
    Filme* atual = listaFilmes; 
    while (atual != NULL) {                           // Percorrendo a lista de filmes
        Filme* temp = atual;                          // Cria um ponteiro para o filme atual
        atual = atual->prox;                          // Vai para o proximo filme da lista
        free(temp);                                   // Libera a memoria ocupada pelo filme atual
    }
    listaFilmes = NULL;
}

void limparTerminal() {
    printf("\e[1;1H\e[2J");                           // Limpa o terminal
}

int readFile() {
    FILE *arquivo;
    char nome[50], genero[20];
    int chave, ano, duracao;
    arquivo = fopen("filmes.txt", "r");               // Abre o arquivo para leitura
    if (arquivo == NULL) {                            // Se o arquivo nao existir
        printf("Erro ao abrir o arquivo.\n");
        return 0;
    }
    while (fscanf(arquivo, "Chave:  %d\n", &chave) != EOF) { // Enquanto nao chegar ao fim do arquivo
        fscanf(arquivo, "Nome:   %[^\n]\n", nome);
        fscanf(arquivo, "Ano:    %d\n", &ano);
        fscanf(arquivo, "Duracao:%d\n", &duracao);
        fscanf(arquivo, "Genero: %[^\n]\n\n", genero);
        adicionarFilme(chave, nome, ano, duracao, genero);
    }
    
    fclose(arquivo);                                  // Fecha o arquivo
    return 1;
}

void updateFile () {
    FILE *arquivo;
    arquivo = fopen("filmes.txt", "w");               // Abre o arquivo para escrita
    if (arquivo == NULL) {                            // Se o arquivo nao existir
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    Filme* atual = listaFilmes;                       // Ponteiro para o primeiro filme da lista    
    while (atual != NULL) {                           // Percorrendo a lista de filmes
        fprintf(arquivo, "Chave:  %d\n", atual->chave);
        fprintf(arquivo, "Nome:   %s\n", atual->nome);
        fprintf(arquivo, "Ano:    %d\n", atual->ano);
        fprintf(arquivo, "Duracao:%d\n", atual->duracao);
        fprintf(arquivo, "Genero: %s\n\n", atual->genero);
        
        atual = atual->prox;                          // Vai para o proximo filme da lista
    }
    fclose(arquivo);                                  // Fecha o arquivo
}

void updateList() {
    FILE *arquivo;
    char nome[50], genero[20];
    int chave, ano, duracao;
    arquivo = fopen("filmes.txt", "r");               // Abre o arquivo para leitura
    if (arquivo == NULL) {                            // Se o arquivo nao existir
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    while (fscanf(arquivo, "Chave:  %d\n", &chave) != EOF) { // Enquanto nao chegar ao fim do arquivo
        fscanf(arquivo, "Nome:   %[^\n]\n", nome);
        fscanf(arquivo, "Ano:    %d\n", &ano);
        fscanf(arquivo, "Duracao:%d\n", &duracao);
        fscanf(arquivo, "Genero: %[^\n]\n\n", genero);
        adicionarFilme(chave, nome, ano, duracao, genero);
    }
    
    fclose(arquivo);                                  // Fecha o arquivo
}

void transcreverTxtParaCsv(const char* filmestxt, const char* filmescsv) {
    FILE *txt, *csv;
    char line[MAX_LINE_LENGTH];
    char *token;
    
    txt = fopen(filmestxt, "r");
    if(txt == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
    csv = fopen(filmescsv, "w");
    if (csv == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return;
    }
   
    
    while (fgets(line, MAX_LINE_LENGTH, txt) != NULL) {
        // Remove o caractere de nova linha
        line[strcspn(line, "\n")] = '\0';
        
        // Divide a linha em colunas usando o separador (no exemplo, '\t' para tabulação)
        token = strtok(line, "\t");
        while (token != NULL) {
            // Escreve a coluna no arquivo CSV
            fprintf(csv, "%s,", token);
            token = strtok(NULL, "\t");
        }
        
        // Insere uma nova linha no arquivo CSV
        fprintf(csv, "\n");
    }
    
    fclose(txt);
    fclose(csv);
    
    printf("Transcrição concluída com sucesso!\n");
}