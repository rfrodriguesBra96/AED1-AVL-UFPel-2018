#include <stdio.h>
#include <stdlib.h>
#include "arvore.h"
#include "fila.h"
#include "extra.h"

/* Programa principal que implementa as funções básicas para manipular um árvore AVL.
 * Autor: Rodrigo Ferreira Rodrigues
 * Disciplina: AED1
 * Data: 2018/02
*/

struct nodo* inicializa_arvore(int entradas, int* valores){
	if(entradas <= 0 || valores == NULL){
		return NULL;
	}
	
	int i = 0;
	struct nodo * raiz = NULL;
	
	for(i = 0; i < entradas; i++){
		raiz = insere_nodo(raiz,valores[i]);
	}
	
	raiz->capacidade_fila = entradas;
	
	return raiz;
}

int altura(struct nodo * raiz){
	if(raiz == NULL){
		return 0;
	}else{
		int he,hd;
		he = altura(raiz->esq);
		hd = altura(raiz->dir);
		if(he > hd){
			return he + 1;
		}else{
			return hd + 1;
		}
	}
}

struct nodo * insere_nodo(struct nodo * raiz, int valor){
	if(raiz == NULL){
		struct nodo * raiz = NULL;
	
		raiz = (struct nodo*)malloc(sizeof(struct nodo));
	
		if(raiz == NULL){
			return NULL;
		}
	
		raiz->valor = valor;
			raiz->esq = NULL;
				raiz->dir = NULL;
					raiz->h = 0;
	
		return raiz;
	
	}
	
	if(valor < raiz->valor){
		raiz->esq = insere_nodo(raiz->esq,valor);
		if(altura(raiz->esq) - altura(raiz->dir) == 2 || altura(raiz->esq) - altura(raiz->dir) == - 2){
			if(valor < raiz->esq->valor){
				raiz = rotacao_direita(raiz);
			}else{
				raiz = rotacao_esquerda_direita(raiz);
			}
		}
	}
	if(valor > raiz->valor){
		raiz->dir = insere_nodo(raiz->dir,valor);
		if(altura(raiz->dir) - altura(raiz->esq) == 2 || altura(raiz->dir) - altura(raiz->esq) == - 2){
			if(valor > raiz->dir->valor){
				raiz = rotacao_esquerda(raiz);
			}else{
				raiz = rotacao_direita_esquerda(raiz);
			}
		}
	}
	
	raiz->h = max(altura(raiz->esq),altura(raiz->dir)) + 1;
	
	return raiz;
}

struct nodo *remove_nodo(struct nodo * raiz, int valor){
	if(raiz == NULL){
		return NULL;
	}
	
	if(valor < raiz->valor){
		raiz->esq = remove_nodo(raiz->esq,valor);
	}else if(valor > raiz->valor){
		raiz->dir = remove_nodo(raiz->dir,valor);
	}
	else{
		if(raiz->esq == NULL){
			struct nodo * tmp = raiz->dir;
			free(raiz);
			return tmp;
		}
		else if(raiz->dir == NULL){
			struct nodo * tmp = raiz->esq;
			free(raiz);
			return tmp;
		}
		struct nodo * tmp = NULL;
		tmp = sucessor(raiz->dir);
		raiz->valor = tmp->valor;
		raiz->dir = remove_nodo(raiz->dir,valor);
	}
	
	if(raiz == NULL){
		return raiz;
	}
	
	raiz->h = 1 + max(altura(raiz->esq), altura(raiz->dir));
	
	int fdb = fator_de_balanceamento(raiz);
	
	if(fdb > 1 && fator_de_balanceamento(raiz->esq) >= 0){
		return rotacao_direita(raiz);
	}
	
	if(fdb > 1 && fator_de_balanceamento(raiz->esq) < 0){
		raiz->esq = rotacao_esquerda(raiz);
		return rotacao_direita(raiz);
	}
	
	if(fdb < -1 && fator_de_balanceamento(raiz->dir) <= 0){
		return rotacao_esquerda(raiz);
	}
	
	if(fdb < -1 && fator_de_balanceamento(raiz->dir) > 0){
		raiz->dir = rotacao_direita(raiz->dir);
		return rotacao_esquerda(raiz);
	}
	return raiz;
}

struct nodo * busca(struct nodo * raiz, int valor){
	if(raiz == NULL){
		return NULL;
	}
	if(raiz->valor == valor){
		return raiz;
	}else if(raiz->valor > valor){
		return busca(raiz->esq,valor);
	}else{
		return busca(raiz->dir,valor);
	}
}

int balanceada(struct nodo * raiz){
	if(raiz == NULL){
		return 1;
	}
	
	int he = 0,hd = 0;
	
	he = altura(raiz->esq);
	hd = altura(raiz->dir);
	
	return (he-hd);
}

int numero_elementos(struct nodo * raiz){
	if(raiz == NULL){
		return 0;
	}
	return (numero_elementos(raiz->esq) + 1 + numero_elementos(raiz->dir));
}

int abrangencia(struct nodo * raiz, int * resultado){
	if(raiz == NULL || resultado == NULL){
		return 0;
	}
	int i = 0;
	printf("CAPACIDADE: %d\n", raiz->capacidade_fila);
	struct fila* queue = create_fila(raiz->capacidade_fila);
	struct nodo* tmp = raiz;
	while(tmp){
		resultado[i++] = tmp->valor;
		if(tmp->esq != NULL){
			insereFila(queue,tmp->esq);
		}
		if(tmp->dir != NULL){
			insereFila(queue,tmp->dir);
		}
		tmp = excluirElemFila(queue);
	}
	
	destroyFila(queue);
	return i;
}

// caminhamentos
int prefix(struct nodo * raiz, int * resultado){
	if(raiz == NULL || resultado == NULL){
		return 0;
	}
	int count = 1;
	resultado[0] = raiz->valor;
	count += prefix(raiz->esq,&resultado[count]);
	count += prefix(raiz->dir,&resultado[count]);
	return count;
}

int postfix(struct nodo * raiz, int * resultado){
	if(raiz == NULL || resultado == NULL){
		return 0;
	}
	int count = 1;
	count += postfix(raiz->esq,&resultado[count]);
	count += postfix(raiz->dir,&resultado[count]);
	resultado[0] = raiz->valor;
	return count;
}

int infix(struct nodo * raiz, int * resultado){
	if(raiz == NULL || resultado == NULL){
		return 0;
	}
	int count = 0;
	count += postfix(raiz->esq,resultado);
	resultado[count++] = raiz->valor;
	count += postfix(raiz->dir,&resultado[count]);
	return count;
}
// fim caminhamentos

// imprime
void imprime(int * valores, int tamanho){
	if(valores == NULL || tamanho <= 0){
		return;
	}
	int i,k = 0;
	for(i = 0; i < tamanho; i++){
		k++;
		printf("(%d)", valores[i]);
		if(k > 10){
			printf("\n");
			k = 0;
		}
	}
}

// Função para liberar árvore
void remove_todos(struct nodo * raiz){
	if(raiz == NULL){
		return;
	}
	// chama auxiliar
	destruir_filhos(raiz);
	raiz = NULL;
}

