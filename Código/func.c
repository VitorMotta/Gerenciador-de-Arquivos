#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "func.h"

// inicializa a memória
Memory* init_memory(size_t size) {
  Memory* mem = malloc(sizeof(Memory));
  mem->total_size = size;
  mem->used_size = 0;
  mem->head = NULL;
  return mem;
 } 

// insere um arquivo na memória
void insert_file(Memory* mem, File* file) {
  // verifica se há espaço suficiente na memória
  if (mem->used_size + file->size > mem->total_size) {
    printf("Erro: sem espaço na memória.\n");
    return;
  }
  // insere o arquivo na lista encadeada
  file->next = mem->head;
  mem->head = file;
  // atualiza o tamanho da memória utilizada
  mem->used_size += file->size;
  printf("Sucesso: Arquivo inserido da memória.\n");
}

// remove um arquivo da memória
void remove_file(Memory* mem, File* file) {
  // procura o arquivo na lista encadeada
  File* prev = NULL;
  File* curr = mem->head;
  while (curr != NULL) {
    if (curr == file) {
      // encontrou o arquivo; remove-o da lista encadeada
      if (prev != NULL) {
        prev->next = curr->next;
      } else {
        mem->head = curr->next;
      }
      // libera a memória alocada para o arquivo
      free(curr->content);
      free(curr);
      // atualiza o tamanho da memória utilizada
      mem->used_size -= file->size;
      printf("Sucesso: Arquivo removido da memória.\n");
      return;
    }
    prev = curr;
    curr = curr->next;
  }
  printf("Erro: arquivo não encontrado na memória.\n");
}

// lê o conteúdo de um arquivo do disco e o armazena na memória
File* read_file(char* filename) {
  // abre o arquivo
  FILE* fp = fopen(filename, "r");
  if (fp == NULL) {
    printf("Erro: Arquivo não pode ser aberto.\n");
    return NULL;
  }
  // aloca memória para armazenar o arquivo
  File* file = malloc(sizeof(File));
  strcpy(file->name, filename);
  // descobre o tamanho do arquivo
  fseek(fp, 0, SEEK_END);
  file->size = ftell(fp);
  fseek(fp, 0, SEEK_SET);
  // aloca memória para armazenar o conteúdo do arquivo
  file->content = malloc(file->size + 1);
  // lê o conteúdo do arquivo
  fread(file->content, file->size, 1, fp);
  fclose(fp);
  // adiciona o caractere de terminação de string
  file->content[file->size] = '\0';
  return file;
}

// pesquisa um arquivo pelo nome
File* search_file(Memory* mem, char* name) {
  File* curr = mem->head;
  while (curr != NULL) {
    if (strcmp(curr->name, name) == 0) {
      // encontrou o arquivo; retorna o ponteiro para ele
      return curr;
    }
    curr = curr->next;
  }
  // não encontrou o arquivo; retorna NULL
  return NULL;
}


// exibe o conteúdo de um arquivo
void show_file(File* file) {
  printf("\n");
  printf("Nome do arquivo: %s\n", file->name);
  printf("Tamanho do arquivo: %zu bytes\n", file->size);
  printf("Conteúdo do arquivo:\n%s\n", file->content);
}

// exibe informações sobre um arquivo
void show_file_info(File* file) {
  printf("\n");
  printf("Nome do arquivo: %s\n", file->name);
  printf("Tamanho do arquivo: %zu bytes\n", file->size);
  printf("Numero de blocos usados: %zu\n", (file->size + BLOCK_SIZE - 1) / BLOCK_SIZE);
  printf("Endereço dos blocos:\n");
  // percorre a lista encadeada de arquivos
  File* curr = file;
  int count = 0;
  while (curr != NULL) {
    printf("%d. %p\n", count, (void*)curr);
    curr = curr->next;
    count++;
  }
}


// conta o número de vezes que um termo aparece em um arquivo
int count_term_occurrences(File* file, char* term) {
  int count = 0;
  char* p = file->content;
  while ((p = strstr(p, term)) != NULL) {
    count++;
    p += strlen(term);
  }
  return count;
}

// exibe uma tabela com os resultados da pesquisa por um termo em todos os arquivos
void show_results_table(Memory* mem, char* term) {
  printf("Resultados para o termo '%s':\n", term);
  printf("Nome do arquivo      Ocorrências\n");
  printf("-------------------- -----------\n");
  // percorre a lista encadeada de arquivos
  File* curr = mem->head;
  while (curr != NULL) {
    // procura o termo no conteúdo do arquivo
    int count = count_term_occurrences(curr, term);
    if (count > 0) {
      // encontrou o termo no arquivo; exibe a linha da tabela
      printf("%-20s %d\n", curr->name, count);
    }
    curr = curr->next;
  }
}

// percorre a lista encadeada associada a um arquivo e exibe os elementos graficamente
void show_block_addresses_graphic(File* file) {
  File* curr = file;
  while (curr != NULL) {
    printf("|corrente|\t\t|proximo|\n");
    printf("|%p|\t|%p|\n", (void*)curr, (void*)curr->next);
    curr = curr->next;
  }
}
