#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"


int main() {
  // inicializa a memória
  Memory* mem = init_memory(BLOCK_SIZE);
  
  int leave = 0;
  char filename[256];
  char term[256];

  printf("---------------------------------------------\n");
  printf("|               BEM VINDO                   |\n");
  printf("---------------------------------------------\n");

  // cria um loop para exibir o menu de opções e ler as entradas do usuário
  while (1) {
    printf("\t\nMenu:\n\n");
    printf("1 - Inserir arquivo\n");
    printf("2 - Remover arquivo\n");
    printf("3 - Procurar arquivo\n");
    printf("4 - Exibir arquivo\n");
    printf("5 - Exibir informações do arquivo\n");
    printf("6 - Procurar termo\n");
    printf("7 - Status da memória\n");
    printf("8 - Status gráfico da memória\n");
    printf("9 - Sair\n");
    printf("\n");

    printf("Entre com sua opção: ");
    int choice;
    scanf("%d", &choice);
    
    //cria uma ação para receber os comandos do usuário e entrar na opção desejada
    switch (choice){
        case 1:
            // insere um arquivo
            printf("Nome do arquivo: ");
            scanf("%s", filename);
            File* file = read_file(filename);
            if (file != NULL) {
              insert_file(mem, file);
            }
            break;

        case 2:
            // remove um arquivo
            printf("Nome do arquivo: ");
            scanf("%s", filename);
            File* file2 = search_file(mem, filename);
            if (file2 != NULL) {
              remove_file(mem, file2);
            } else {
              printf("Erro: Arquivo não encontrado na memória.\n");
            }
            break;

        case 3:
            // pesquisa um arquivo
            printf("Nome do arquivo: ");
            scanf("%s", filename);
            File* file5 = search_file(mem, filename);
            if (file5 != NULL) {
              printf("Sucesso: Arquivo encontrado na memória.\n\n");
            } else {
              printf("Erro: Arquivo não encontrado na memória.\n");
            }
            break;    
        
        case 4:
            // exibe um arquivo
            printf("Nome do arquivo: ");
            scanf("%s", filename);
            File* file3 = search_file(mem, filename);
            if (file3 != NULL) {
              show_file(file3);
            } else {
              printf("Erro: Arquivo não encontrado na memória.\n");
            }
            break;

        case 5:
            // exibe informações sobre um arquivo
            printf("Nome do arquivo: ");
            scanf("%s", filename);
            File* file4 = search_file(mem, filename);
            if (file4 != NULL) {
              show_file_info(file4);
            } else {
              printf("Erro: Arquivo não encontrado na memória.\n");
            }
            break;

        case 6:
        // pesquisa um termo em todos os arquivos
            printf("Digite o termo: ");
            scanf("%s", term);
            show_results_table(mem, term);
            break;            

        case 7:
            // exibe o status da memória
            printf("Tamanho total da memória: %zu bytes\n", mem->total_size);
            printf("Tamanho usado da memória: %zu bytes\n", mem->used_size);
            printf("Tamanho livre da memória: %zu bytes\n", mem->total_size - mem->used_size);
            break;                  


        case 8:
            // exibe os elementos graficamente  
            printf("Nome do arquivo: ");
            scanf("%s", filename);
            File* file8 = search_file(mem, filename);
            if (file8 != NULL) {
              show_block_addresses_graphic(file8);
            } else {
              printf("Erro: Arquivo não encontrado na memória.\n");
            }
            break;

        case 9:
            // sai da ação de receber comandos do usuário
            leave = 1;
            break;
    }    
    // sai do loop
    if (leave)
        break;
  }  

  return 0;
}