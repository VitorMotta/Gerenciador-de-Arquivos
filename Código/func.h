#ifndef FUNCAO_H
#define FUNCAO_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define BLOCK_SIZE 60 // tamanho do bloco em bytes

// estrutura para armazenar informações sobre arquivos
typedef struct File {
  char name[256];         // nome do arquivo
  size_t size;            // tamanho do arquivo em bytes
  char* content;          // conteúdo do arquivo
  struct File* next;      // ponteiro para o próximo arquivo na lista encadeada
} File;

// estrutura para armazenar informações sobre a memória
typedef struct Memory {
  size_t total_size;      // tamanho total da memória em bytes
  size_t used_size;       // tamanho da memória utilizada em bytes
  struct File* head;      // ponteiro para o primeiro arquivo na lista encadeada de arquivos
} Memory;

Memory* init_memory(size_t size);

void insert_file(Memory* mem, File* file);

void remove_file(Memory* mem, File* file);

File* read_file(char* filename);

File* search_file(Memory* mem, char* name);

void show_file(File* file);

void show_file_info(File* file);

int count_term_occurrences(File* file, char* term);

void show_results_table(Memory* mem, char* term);

void show_block_addresses_graphic(File* file);


#endif // funcoes