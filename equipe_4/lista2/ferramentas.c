#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include<time.h>

#include "ferramentas.h"

/* Manipulação de listas não ordenadas*/
int buscaAluno_NOrd(TAluno lista[], int tam, int chave){
    /*
        Utilizar a implementação proposta no Exemplo_06
        para busca em listas não ordenadas. Você pode
        propor modificações no código visando melhorias
        no desempenho.*/
    
   int i = 0;
	while (i < tam)
	{
		if (lista[i].numMatricula == chave)
			return i; //achou retorna o índice  
		i++;
	}
	return tam; //não achou, retorna tamLista
}

int incAluno_NOrd(TAluno aluno, TAluno lista[], int *tam, int cap){
    /*
        Utilizar a implementação proposta no Exemplo_06
        para inclusão em listas não ordenadas. Você pode
        propor modificações no código visando melhorias
        no desempenho.
    */
   if (*tam == cap)
        return FALSE; //lista cheia
	if (buscaAluno_NOrd(lista, *tam, aluno.numMatricula) == *tam){
		lista[*tam].numMatricula = aluno.numMatricula;
		strcpy(lista[*tam].nome, aluno.nome);
		strcpy(lista[*tam].email, aluno.email);
        *tam += 1;
        return TRUE;
	}else
        return FALSE;
}

int remAluno_NOrd(int chave, TAluno lista[], int *tam){
    /*
        Utilizar a implementação proposta no Exemplo_06
        para remoção em listas não ordenadas. Você pode
        propor modificações no código visando melhorias
        no desempenho.
    */
    if(*tam == 0)
        return FALSE; //lista vazia
    int pos = buscaAluno_NOrd(lista, *tam, chave);
    if (pos < *tam){
        *tam -= 1;
        lista[pos].numMatricula = lista[*tam].numMatricula;
        strcpy(lista[pos].nome, lista[*tam].nome);
        strcpy(lista[pos].email, lista[*tam].email);
        //se o cara que for removido for o ultimo o elemento continua na memoria
        return TRUE;
    }else
        return FALSE;
}

// Manipulação de listas ordenadas
int buscaAluno_Ord(TAluno lista[], int tam, int chave){
    /*
        Utilizar a implementação proposta no Exemplo_10
        para busca em listas ordenadas. Você pode
        propor modificações no código visando melhorias
        no desempenho.
    */
    int min = 0, max = tam, i = 0;
    while (min != max)      {
        i = (max + min) / 2;
        if (lista[i].numMatricula < chave)
            min = i + 1;
        else {
            if (lista[i].numMatricula > chave)
                max = i;
            else
                return i;
        }
    }
    return i;
}

int incAluno_Ord(TAluno aluno, TAluno lista[], int *tam, int cap){
    /*
        Utilizar a implementação proposta no Exemplo_10
        para inclusão em listas ordenadas. Você pode
        propor modificações no código visando melhorias
        no desempenho. 
        Em sala de aula foi proposta abrir
        espaço para o novo item da lista deslocando os 
        elementos no array da direita para esquerda. Esta
        modificação precisa ser implementada.
    */
    if (*tam == cap)
        return FALSE; //lista cheia
    int pos = buscaAluno_Ord(lista, *tam, aluno.numMatricula);
	if ( pos == *tam){
        lista[*tam].numMatricula = aluno.numMatricula; 
		strcpy(lista[*tam].nome, aluno.nome);
		strcpy(lista[*tam].email, aluno.email);
        *tam += 1;
        return TRUE;
	}else{
        if(lista[pos].numMatricula != aluno.numMatricula){
            TAluno troca;
            int i;
            for(i = pos; i < *tam; i++){
                troca.numMatricula = lista[i].numMatricula;
                strcpy(troca.nome, lista[i].nome);
                strcpy(troca.email, lista[i].email);
                
                lista[i].numMatricula = aluno.numMatricula;
                strcpy(lista[i].nome, aluno.nome);
                strcpy(lista[i].email, aluno.email);

                aluno.numMatricula = troca.numMatricula;
                strcpy(aluno.nome, troca.nome);
                strcpy(aluno.email, troca.email);
            }
            lista[*tam].numMatricula = aluno.numMatricula;
            strcpy(lista[*tam].nome, aluno.nome);
            strcpy(lista[*tam].email, aluno.email);
            *tam += 1;
            return TRUE;
        }else
            return FALSE;
    }   
}

int remAluno_Ord(int chave, TAluno lista[], int *tam){
    /*
        Utilizar a implementação proposta no Exemplo_10
        para remoção em listas ordenadas. Você pode
        propor modificações no código visando melhorias
        no desempenho.
        Veja se a modificação feita na função de inclusão
        se aplica de alguma forma nesta função 
    */
    if(*tam == 0)
        return FALSE; //lista vazia
    int pos = buscaAluno_Ord(lista, *tam, chave);
    if (pos < *tam && lista[pos].numMatricula == chave){
    	int i;
        for(i = pos; i < *tam - 1 ; i++){
            lista[i].numMatricula = lista[i+1].numMatricula;
            strcpy(lista[i].nome, lista[i+1].nome);
            strcpy(lista[i].email, lista[i+1].email);
        }
        *tam -= 1;
        return TRUE;
    }else
        return FALSE;
}


// Utilizar isto aqui no projeto
//void iniListAlunos(TListAlunos* lista, int cap, int eOrd) 
//ou 
TListAlunos* iniListAlunos(int cap, int eOrd){
    /*
        Esta função aloca uma variável do tipo TListAluno
        contendo os atributos:
        * lista: Um array de tipo TAluno de tamanho definido em
        função da capacidade da lista (cap) e do tipo de 
        lista: ordenada (eOrd é verdadeiro) ou
        não ordenada (eOrd é falso);
        * cap: a capacidade da lista definida pelo parametro
        cap;
        * tam: o tamanho da lista inicializado como zero;
        * eOrd: o tipo de lista ordenada (eOrd é verdadeiro) ou
        não ordenada (eOrd é falso);
        Apresentamos duas versões
        do cabeçalho. Escolha a que achar mais apropriada. 
        Verifique se sua escolha bate com a definição do 
        ferramentas.h 
    */
    TListAlunos *list = malloc (sizeof (TListAlunos));
    list->tam = 0;
    list->cap = cap;
    list->eOrd = eOrd;
    list->lista = malloc (cap * sizeof (TAluno));
    
    if (eOrd == TRUE){ //Ordenado - chaves sequenciais
    	int i;
		for (i=0;i<cap;i++){
    		list->lista[i].numMatricula = 200010000 + i;
    	}
	}
    
    return list;
}

TListAlunos* uniListas(TListAlunos *ListaA, TListAlunos *ListaB){
    /*
        Retorna uma nova lista formada pela união das duas
        listas (ListaA e ListaB). A nova lista deverá ser
        do mesmo tipo das listas de entrada (ordenada ou
        não ordenada) caso as duas listas sejam do mesmo 
        tipo. Escolha como definir o tipo da lista de saída
        caso as listas de entrada seja de tipos diferentes. 
        Como discutido em sala de aula, a capacidade da 
        lista de saída se calcula como a soma do tamanho da
        ListaA e o tamanho da lista 2. 
    */
    //criar uma nova lista com tamanho e cap = tamanho Lista 1 + tamanho Lista 2
    // juntar elementos Lista 1 + elementos Lista 2
    int cap = ListaA->tam + ListaB->tam;
    int eOrd = FALSE;
    if (ListaA->eOrd == ListaB->eOrd) {
        eOrd = ListaA->eOrd;
    }
    TListAlunos *resultado = iniListAlunos(cap, eOrd);
    int i;
    for (i = 0; i < ListaA->tam; i++) {
        resultado->lista[i] = ListaA->lista[i];
    }
    resultado->tam = ListaA->tam;
    for (i = 0; i < ListaB->tam; i++) {
        if (eOrd) {
            incAluno_Ord(ListaB->lista[i], resultado->lista, &resultado->tam, resultado->cap);
        } else {
            incAluno_NOrd(ListaB->lista[i], resultado->lista, &resultado->tam, resultado->cap);
        }
    }
    return resultado;
}

TListAlunos* difListas(TListAlunos *ListaA, TListAlunos *ListaB){
    /*
        Retorna uma nova lista formada pela diferença da 
        ListaA com a ListaB, que representa os elementos 
        da ListaA que não aparecem na ListaB. A nova lista 
        deverá ser do mesmo tipo da ListaA. Como discutido 
        em sala de aula, a capacidade da lista de saída se 
        calcula como o tamanho da ListaA 
    */
   // A[1,2,4,6,8] - B[1,4,5,7,8]
   //Resultado[2,6]
   
    int cap = ListaA->tam;
    int eOrd =ListaA->eOrd;
    TListAlunos *resultado = iniListAlunos(cap, eOrd);
    int i, pos;
    for (i = 0; i < ListaA->tam; i++) {
        if (eOrd) {
            pos = buscaAluno_Ord(ListaB->lista, ListaB->tam, ListaA->lista[i].numMatricula);
			if (pos == ListaB->tam || ListaA->lista[i].numMatricula != ListaB->lista[pos].numMatricula){
				incAluno_Ord(ListaA->lista[i], resultado->lista, &resultado->tam, resultado->cap);
			}
        } else {
        	pos = buscaAluno_NOrd(ListaB->lista, ListaB->tam, ListaA->lista[i].numMatricula);
			if (pos == ListaB->tam){
				incAluno_NOrd(ListaA->lista[i], resultado->lista, &resultado->tam, resultado->cap);
			}
        }
    }
    return resultado;
}

TListAlunos* intListas(TListAlunos *ListaA, TListAlunos *ListaB){
    /*
        Retorna uma nova lista formada pela intersecção da 
        ListaA com a ListaB, que representa os elementos 
        da ListaA que também estão na ListaB. A nova lista 
        deverá ser do mesmo tipo das listas de entrada 
        (ordenada ou não ordenada) caso as duas listas sejam 
        do mesmo tipo. Escolha como definir o tipo da lista 
        de saída caso as listas de entrada seja de tipos 
        diferentes. Como discutido em sala de aula, a 
        capacidade da lista de saída se calcula como o 
        menor tamanho entre as ListaA e ListaB.
    */
   // A[1,2,4,6,8] - B[1,4,5,7,8]
   //Resultado[1,4,8]
   	
   	int cap;
   	if(ListaA->tam < ListaB->tam){
   		cap = ListaA->tam;}
   	else{
   		cap = ListaB->tam;}
	
    int eOrd = FALSE;
    if (ListaA->eOrd == ListaB->eOrd) {
        eOrd = ListaA->eOrd;}
    
    TListAlunos *resultado = iniListAlunos(cap, eOrd);
    int i;
    int pos;
    for (i = 0; i < ListaA->tam; i++) {
        if (eOrd) {
            pos = buscaAluno_Ord(ListaB->lista, ListaB->tam, ListaA->lista[i].numMatricula);
			if (pos != ListaB->tam && ListaA->lista[i].numMatricula == ListaB->lista[pos].numMatricula){
				incAluno_Ord(ListaA->lista[i], resultado->lista, &resultado->tam, resultado->cap);
			}
        } else {
        	pos = buscaAluno_NOrd(ListaB->lista, ListaB->tam, ListaA->lista[i].numMatricula);
			if (pos != ListaB->tam){
				incAluno_NOrd(ListaA->lista[i], resultado->lista, &resultado->tam, resultado->cap);
			}
        }
    }
    return resultado;
}

void ordenaLista(TListAlunos *ListaA){
    /*
        Caso a ListaA seja uma lista não ordenada, muda
        a campo eOrd para verdadeiro e utiliza um 
        algoritmo apropriado para ordenar a lista em
        ordem crescente do campo chave. 
        Na aula do dia 12 de abril discutiremos em sala de
        aula os melhores algoritmos de ordenação. 

    */
   if (ListaA->eOrd == FALSE){
		int i, j;
		TAluno aux;
		for(i=0; i<ListaA->tam; i++){
			for(j=i; j<ListaA->tam; j++){
				if(ListaA->lista[j].numMatricula > ListaA->lista[i].numMatricula){
					aux = ListaA->lista[i];
					ListaA->lista[i] = ListaA->lista[j];
					ListaA->lista[j] = aux;
				}
			}
		}
		ListaA->eOrd = TRUE;
   }
}

void printLista(TAluno lista[], int tam){
    /*
        Utilizar a implementação ja disponível nos
        exemplos anteriores.
    */
    int i;
	printf("[ \n ");
	for (i = 0; i < tam; i++)
	{
		printf("%d, ", lista[i].numMatricula);
		printf("%s, ", lista[i].nome);
		printf("%s;\n ", lista[i].email);
	}
	printf(" ]\n");
}

TListAlunos* geraListaDeAlunos(int tam, int cap, int eOrd){
    /*
        Retorna uma lista de alunos com capacidade cap de 
        tipo ordenada (eOrd verdadeiro) o não ordenada (eOrd
        falso) preenchida com tam itens com chaves geradas de 
        forma aleatória entre os anos 2000 e 2022. 
        * A chave tem que respeitar o número de 9 dígitos
        comecando com o ano seguido do semestre e do 
        sequencial de quatro dígitos;
        * As chaves geradas tem que ter itens de primeiro
        e segundo semestre;
        * Os campos nome e email dos itens podem ser
        preenchidos com um valor padrão qualquer.
    */
    
    TListAlunos *list = malloc (sizeof (TListAlunos));
    list->tam = tam;
    list->cap = cap;
    list->eOrd = eOrd;
    list->lista = malloc (cap * sizeof (TAluno));
    
    int i;
    if (eOrd == TRUE){ //Ordenado - Chaves sequenciais
    	int ano = 2000, semestre = 1;
    	for (i=0;i<tam;i++){
    		list->lista[i].numMatricula = ano*100000 + semestre*10000 + i;
    		if (i >= 9999){
    			semestre += 1;
    			if (semestre > 2){
    				ano += 1;
    				semestre = 1;
				} 
			}
		}	
	}
	else { //N�o ordenada - Chaves aleat�rias
		srand(time(NULL));
		for (i=0;i<tam;i++){
    		list->lista[i].numMatricula = (2000 + rand() % 23)*100000 + (rand() % 2 + 1)*10000 + (rand() % 1000);
		}
	}
    
    return list;
}
