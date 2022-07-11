#ifndef _EXTRA_H_
#define _EXTRA_H_

/* Cabeçalho das funções extras
 * Autor: Rodrigo Ferreira Rodrigues
 * Disciplina: AED1
 * Data: 2018/02
*/

/*
 * Função que retorna o maior dentre dois elementos.
 * @param a
 * @param b
 * @return o mair número
 */ 
int max(int a, int b);

/*
 * Relização rotação para o lado right;
 * @param nodo(descabalanceado)
 */
struct nodo * rotacao_direita(struct nodo * y);

/*
 * Relização rotação para o lado left;
 * @param nodo(descabalanceado)
 */
struct nodo * rotacao_esquerda(struct nodo * x);

/*
 * Relização rotação para o lado left_right.
 * @param nodo(descabalanceado)
 */
struct nodo * rotacao_esquerda_direita(struct nodo * raiz);

/*
 * Relização rotação para o lado right_left.
 * @param nodo(descabalanceado)
 */
struct nodo * rotacao_direita_esquerda(struct nodo * raiz);

/*
 * Calcula o fator de balanceamento.
 * @retorna um inteiro que representa o fator de balanceamento
 */
int fator_de_balanceamento(struct nodo * raiz);

/*
 * Função auxiliar para implementar a funçaõ remove_nodo
 * @param referência da sub_árvore para buscar o sucessor
 * @return successor
 */ 
struct nodo *sucessor(struct nodo *node);

/*
 * Função auxiliar que ajuda na liberação de memória.
 * @param raiz da árvore
 */
void destruir_filhos(struct nodo * raiz);

#endif
