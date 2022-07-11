#include <stdio.h>
#include <stdlib.h>
#include "extra.h"
#include "arvore.h"

/* Implementação das funções extras
 * Autor: Rodrigo Ferreira Rodrigues
 * Disciplina: AED1
 * Data: 2018/02
*/

// Função MAX
int max(int a, int b){
	if(a >= b){
		return a;
	}else{
		return b;
	}
}
// Função de rotação_direita
struct nodo * rotacao_direita(struct nodo * raiz){
	if(raiz == NULL){
		return NULL;
	}
	struct nodo * aux = NULL;
	
	// Realizo a rotação
	aux = raiz->esq;
	raiz->esq = aux->dir;
	aux->dir = raiz;
	
	// Atualizo as alturas
	raiz->h = max(altura(raiz->dir),altura(raiz->esq)) + 1;
	aux->h = max(altura(aux->esq),raiz->h) + 1;
								   // x->altura	
	return aux;
}

// Função de rotação_esquerda
struct nodo * rotacao_esquerda(struct nodo * raiz){
	if(raiz == NULL){
		return NULL;
	}
	struct nodo * aux = NULL;
	
	// Realizo a rotação
	aux = raiz->dir;
	raiz->dir = aux->esq;
	aux->esq = raiz;
	
	// Atualizo as alturas
	raiz->h = max(altura(raiz->dir),altura(raiz->esq)) + 1;
	aux->h = max(altura(aux->dir),raiz->h) + 1;
								   // y->altura	
	return aux;
}

// Função de rotação_esquerda_direita
struct nodo * rotacao_esquerda_direita(struct nodo * raiz){
	if(raiz == NULL){
		return NULL;
	}
	raiz->esq = rotacao_esquerda(raiz->esq); // Resultado raiz da nova tree rotacionada guardada em raiz->esq
	return rotacao_direita(raiz); // retorno a raiz e rotaciono a direita
}

// Funçaõ de rotação_direita_esquerda
struct nodo * rotacao_direita_esquerda(struct nodo * raiz){
	if(raiz == NULL){
		return NULL;
	}
	raiz->dir = rotacao_direita(raiz->dir);
	return rotacao_esquerda(raiz);
}

// Função sucessor
struct nodo *sucessor(struct nodo *node){
	if(node == NULL){
		return NULL;
	}
	struct nodo * tmp = node;
	while(tmp->esq != NULL){
		tmp = tmp->esq;
	}
	return tmp;
}

// Função fator_de_balanceamento
int fator_de_balanceamento(struct nodo * raiz){
	if(raiz == NULL){
		return 0;
	}
	return altura(raiz->esq) - altura(raiz->dir);
}

// Função auxiliar para liberar arvore
void destruir_filhos(struct nodo * raiz){
	if(raiz != NULL){
		destruir_filhos(raiz->esq);
		destruir_filhos(raiz->dir);
		free(raiz);
	}
}

// papas da lingua - disco rock
