#include <stdio.h>
#include <stdlib.h>
#include "fila.h"

/* Implementação das funções da fila
 * Autor: Rodrigo Ferreira Rodrigues
 * Disciplina: AED1
 * Data: 2018/02
*/

// Criar uma fila.
struct fila* create_fila(int cap){
	struct fila* f = NULL;
	
	f = (struct fila*)malloc(sizeof(struct fila));
	
	if(f == NULL){
		return NULL;
	}
	
	f->inicio = 0;
	f->tam = 0;
	f->capacidade = cap;
	f->array = malloc(sizeof(struct nodo)* cap);
	
	if(f->array == NULL){
		return NULL;
	}
	
	return f;
}

// Retorna o tamanho da fila.
int tamanho_fila(FILA *f){
	if(f == NULL){
		return 0;
	}
	
	return f->tam;
}


// Inserir um elemento na fila.
int insereFila(FILA *f, struct nodo * tmp){
	if(f == NULL || tmp == NULL || f->tam >= f->capacidade){
		return 0;
	}
	
	int pos = (f->inicio + f->tam) % f->capacidade;
	
	f->array[pos] = *tmp;
	f->tam++;
	
	return 1;
}

/* Excluir um elemento da fila */
struct nodo * excluirElemFila(FILA *f){
	if(f == NULL || f->tam == 0){
		return 0;
	}
	struct nodo * tmp = NULL;
	
	tmp = &f->array[f->inicio];
	f->inicio = (f->inicio + 1) % f->capacidade;
	f->tam--;
	
	return tmp;
}

int filaIsEmpty(FILA *f){
	if(f->tam == 0 || f == NULL){
		return 1;
	}
		return 0;
}

void destroyFila(FILA *f){
	if(f == NULL){
		return;
	}
	free(f);
}
