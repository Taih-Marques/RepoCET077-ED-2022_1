#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ferramentas.c"

int main(void)
{
    	int i, falso, verdade;
    	
        /* Criar uma listaA não ordenada de tamanho 
        2*LSIZE preenchida de forma aleatória.*/
        TListAlunos *listaA = geraListaDeAlunos(2*LSIZE, 2*LSIZE, FALSE);
		printf("Tamanho listaA: %d\n", listaA->tam);
        
        
        /* Declarar uma listaB não ordenada de capacidade
        LSIZE*/
        TListAlunos *listaB = iniListAlunos(LSIZE, FALSE);
        
        
        /* Selecione em ordem aleatória todos os itens da 
        listaA e inclua na listaB. Conte quantas vezes a 
        função de inclusão retorna verdadeiro e quantas 
        retorna falso. No final mostre os valores 
        contabilizados junto com o tamanho da listaB*/
        falso = 0; verdade = 0;
        srand(time(NULL));
        while (listaB->tam < listaB->cap) {
        	if(incAluno_NOrd(listaA->lista[rand() % listaA->tam], listaB->lista, &listaB->tam, listaB->cap) == FALSE){
        		falso += 1;
			}
			else {
				verdade +=1;
			}
		}
		printf("\nlistB Preenchida. Verdadeiro: %d | Falso: %d | Tamanho listaB: %d\n",verdade, falso, listaB->tam);
        
        
        /* Declarar uma listaC ordenada de capacidade
        LSIZE*/
        TListAlunos *listaC = iniListAlunos(LSIZE, TRUE);
        
        
        /* Selecione em ordem aleatória todos os itens da 
        listaA e inclua na listaC. Conte quantas vezes a 
        função de inclusão retorna verdadeiro e quantas 
        retorna falso. No final mostre os valores 
        contabilizados junto com o tamanho da listaC*/
        falso = 0; verdade = 0;
        srand(time(NULL) + 1);
        while (listaC->tam < listaC->cap) {
        	if(incAluno_Ord(listaA->lista[rand() % listaA->tam], listaC->lista, &listaC->tam, listaC->cap) == FALSE){
        		falso += 1;
			}
			else {
				verdade +=1;
			}
		}
		printf("\nlistC Preenchida. Verdadeiro: %d | Falso: %d | Tamanho listaC: %d\n",verdade, falso, listaC->tam);
        
        
        /* Crie a lista união da listaB com a ListaC. 
        Mostre o tamanho desta lista.*/
        TListAlunos *Lista_Uniao = uniListas(listaB, listaC);
        printf("\nTamanho Lista Uniao B e C: %d\n", Lista_Uniao->tam);
        
        
        /* Crie a lista diferença da listaB com a ListaC. 
        Mostre o tamanho desta lista.*/
        TListAlunos *Lista_DifBC = difListas(listaB, listaC);
        printf("\nTamanho Lista Diferenca B e C: %d\n", Lista_DifBC->tam);
        
        
        /* Crie a lista diferença da listaC com a ListaB. 
        Mostre o tamanho desta lista.*/
        TListAlunos *Lista_DifCB = difListas(listaC, listaB);
        printf("\nTamanho Lista Diferenca C e B: %d\n", Lista_DifCB->tam);
        
        
        /* Crie a lista intersecção da listaB com a ListaC. 
        Mostre o tamanho desta lista.*/
        TListAlunos *Lista_intersecao = intListas(listaB, listaC);
        printf("\nTamanho Lista Intersecao B e C: %d\n", Lista_intersecao->tam);
        
        
        /* Verifique se os tamanhos reportados são 
        consistentes.*/
        
        
        /* Transforma a listaA numa lista ordenada.*/
        ordenaLista(listaA);
        printf("\nlista A ordenada!\n");
        //Se quiser imprimir a lista A:
		//printLista(listaA->lista, listaA->tam);
        
    return 0;
}
