#ifndef _FILA_H_
#define _FILA_H_

#include "arvore.h"

/* Cabeçalho da fila
 * Autor: Rodrigo Ferreira Rodrigues
 * Disciplina: AED1
 * Data: 2018/02
*/

typedef struct fila{
	struct nodo * array;
	int inicio;
	int tam;
	int capacidade;
}FILA;

/*
 * Função que criar uma fila.
 * @param capacidade
 * @return referência
 */
struct fila *create_fila(int cap);

/*
 * Função que retorna o tamanho da fila.
 * @param f
 * @return tamanho da fila
 * @return 0 ERRO!
 */
int tamanho_fila(FILA *f);

/*
 * Função para exibir os elementos de uma fila.
 * @param f
 * @return mostra os elementos na fila.
 */
void exibirFila(FILA *f);

/*
 * Função para inserir um elemento na fila.
 * @param f
 * @param nodo tmp
 * @return 1 OK
 * @return 0 ERRO
 */
int insereFila(FILA *f, struct nodo * tmp);

/*
 * Função para excluir um elemento na fila.
 * @param f
 * @return ref elemento excluido
 */
struct nodo * excluirElemFila(FILA *f);

/*
 * Função para liberar memória da fila
 * @param fila
 */
void destroyFila(FILA *f);

#endif
