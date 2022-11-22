#include <stdio.h>
typedef struct Nodo{
  int dado;
  struct Nodo *direita;
  struct Nodo *esquerda;
} Nodo;

//prototipação
Nodo* insere(Nodo*, int);
Nodo* remover(Nodo*, int);
Nodo* removerComSubarvores(Nodo*, int);
Nodo* removerAoEncontrar(Nodo*, int);
Nodo* criarNodo(int);
void preOrdem(Nodo*);
void emOrdem(Nodo*);
void posOrdem(Nodo*);

Nodo* insere(Nodo* nodo, int dado) {
	
	Nodo* novoNodo = criarNodo(dado);
	
	if(nodo != NULL) {
		if(nodo->dado > novoNodo->dado) {
			nodo->esquerda = insere(nodo->esquerda, dado);
		
		}else if(nodo->dado <= novoNodo->dado){
		
			nodo->direita = insere(nodo->direita, dado);
		}
		
	}else{
		nodo = novoNodo;
	}
	return nodo;
}

Nodo* removerComSubarvores(Nodo* nodo, int dado){
    //Encontrando o último nodo à direita do nodo à esquerda do nodo a ser removido
    Nodo* sae = nodo->esquerda;
    while (sae->direita != NULL){
        sae = sae->direita;
    }
    //trocando valor do nodo a ser removido com o nodo encontrado
    nodo->dado = sae->dado;
    sae->dado = dado;
    
    //removendo o ultimo nodo à direita da subarvore da esquerda
    nodo->esquerda = remover(nodo->esquerda, dado);
    return nodo;
}

Nodo* removerAoEncontrar(Nodo* nodo, int dado){
    // O nodo não possui subarvores
    if(nodo->esquerda == NULL && nodo->direita == NULL){
        free(nodo);
        nodo = NULL;
    }else{
        // O nodo possui subarvore somenta à direita
        if(nodo->esquerda == NULL){
            Nodo* temp = nodo; // Nodo temporário que aponta para o elemento atual
            nodo = nodo->direita;
            free(temp);
        }else{
            // O nodo possui subarvore somenta à esquerda
            if(nodo->direita == NULL){
                Nodo* temp = nodo; // /Nodo temporário que aponta para o elemento atual
                nodo = nodo->esquerda;
                free(temp);
            }else{ // O nodo possui duas subarvores
                nodo = removerComSubarvores(nodo, dado);
            }
        }
    }
    return nodo;
}

Nodo* remover(Nodo* nodo, int dado){
    if(nodo == NULL){
        return NULL;
    }

    if(nodo->dado > dado){
        nodo->esquerda = remover(nodo->esquerda, dado);
        
    }else{
        if(nodo->dado < dado){
            nodo->direita = remover(nodo->direita, dado);
            
        }else{ // Ao elemento ser encontrado
        	nodo = removerAoEncontrar(nodo, dado);
        }
    }
    return nodo;
}


Nodo* criarNodo(int dado){
	Nodo *nodo = (Nodo *)malloc(sizeof(Nodo));
  	nodo->dado = dado;
  	nodo->direita = NULL;
  	nodo->esquerda = NULL;
  	
  	return nodo;
}

void preOrdem(Nodo *nodo){
	printf("%i\n", nodo->dado);
	if(nodo->esquerda != NULL){
		preOrdem(nodo->esquerda);	
	}
	if(nodo->direita != NULL){
		preOrdem(nodo->direita);	
	}
	
}

void emOrdem(Nodo *nodo){
	if(nodo->esquerda != NULL){
		emOrdem(nodo->esquerda);	
	}
	
	printf("%i\n", nodo->dado);
	if(nodo->direita != NULL){
		emOrdem(nodo->direita);
	}
	
}

void posOrdem(Nodo *nodo){
	if(nodo->esquerda != NULL){
		posOrdem(nodo->esquerda);	
	}
	
	if(nodo->direita != NULL){
		posOrdem(nodo->direita);	
	}
	
	printf("%i\n", nodo->dado);
}


int main(void) {
		
	Nodo* raiz = criarNodo(15);
	insere(raiz, 25);
	insere(raiz, 35);
	insere(raiz, 45);
	insere(raiz, 65);
	insere(raiz, 55);
	insere(raiz,44);
	insere(raiz, 34);
	insere(raiz, 24);
	insere(raiz, 10);
	insere(raiz, 15);
	raiz = remover(raiz, 25);
	raiz = remover(raiz, 35);
	raiz = remover(raiz, 15);
	insere(raiz, 42);
	insere(raiz, 40);
	insere(raiz, 43);
	raiz = remover(raiz, 44);
	insere(raiz, 60);
	insere(raiz, 70);
	insere(raiz, 50);
	insere(raiz, 67);
	insere(raiz, 64);
	raiz = remover(raiz, 65);
	
	printf("PreOrdem\n");
	preOrdem(raiz);
	printf("EmOrdem\n");
	emOrdem(raiz);
	printf("PosOrdem\n");
	posOrdem(raiz);
	
	
	printf("====================\n");

	printf("%i", raiz->direita->direita->direita->direita->direita->esquerda->dado);

}
