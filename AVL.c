#include <stdio.h>
#include <stdlib.h>

typedef struct Nodo{
  int dado, altura;
  struct Nodo *direita;
  struct Nodo *esquerda;
} Nodo;

//prototipação
Nodo *insere(Nodo*, int x);
Nodo* remover(Nodo*, int);
Nodo* criarNodo(int);
void preOrdem(Nodo*);
void emOrdem(Nodo*);
void posOrdem(Nodo*);
Nodo *rotaDDir(Nodo*);
Nodo *rotaDEsq(Nodo*);
Nodo *rotaEsqDir(Nodo*);
Nodo *rotaDirEsq(Nodo*);


int altura(Nodo *raiz){
	int alt_esq, alt_dir;
	if(raiz == NULL){
		return 0;
	}
	if(raiz->esquerda == NULL){
		alt_esq = 0;
	}else{
		Nodo* aux1 = raiz->esquerda;
		alt_esq = 1 + aux1->altura;
	}
	if(raiz->direita == NULL){
		alt_dir = 0;
	}else{
		Nodo* aux2 = raiz->direita;
		alt_dir = 1 + aux2->altura;
	}
	if(alt_esq > alt_dir){
		return alt_esq;
	}
	return alt_dir;
}

Nodo *rotaDir(Nodo *raiz){
  Nodo *aux = raiz->esquerda;//inserindo na sub-árvore da esquerda do filho esq no desbalanceado

  //rotacoes a esquerda
  raiz->esquerda = aux->direita;
  aux->direita = raiz;
  raiz->altura = altura(raiz);
  aux->altura = altura(aux);
  return aux;
}
//rotacao simples esquerda
Nodo *rotaEsq(Nodo *raiz){
  Nodo *aux = raiz->direita;
  raiz->direita = aux->esquerda;
  aux->esquerda = raiz;
  raiz->altura = altura(raiz);
  aux->altura = altura(aux);
  return aux;
}
//rotacos duplas: no desbalanceado (pai) e seu filho estão inclinados no sentido inverso ao neto 
//- equivale a duas rotações simples. rotacao dupla direita
Nodo *rotaDDir(Nodo *raiz){
  raiz = rotaEsq(raiz);
  return raiz;
}
//rotacao dupla esquerda
Nodo *rotaDEsq(Nodo *raiz){
  raiz = rotaDir(raiz);
  return raiz;
}
//rotacao esq-direita
Nodo *rotaEsqDir(Nodo *raiz){
  raiz->esquerda = rotaEsq(raiz->esquerda);
  raiz = rotaDir(raiz);
  return raiz;
}
//rota dir-esq
Nodo *rotaDirEsq(Nodo *raiz){
  raiz->direita = rotaDir(raiz->direita);
  raiz = rotaEsq(raiz);
  return raiz;
}


int fatorBal(Nodo *raiz){
	int alt_esq, alt_dir;
	if(raiz == NULL){
		return 0;
	}
	if (raiz->esquerda == NULL){
		alt_esq = 0;
	}else{
		Nodo* aux1 = raiz->esquerda;
		alt_esq = 1 + aux1->altura;
	}
	if(raiz->direita == NULL){
		alt_dir = 0;
	}else{
		Nodo* aux2 = raiz->direita;
		alt_dir = 1 + aux2->altura;
	}
	return (alt_esq - alt_dir);
}

Nodo *insere(Nodo *raiz, int x){
  if(raiz == NULL){ 
  	raiz = criarNodo(x);
  }else{
    if(x > raiz->dado){
      raiz->direita = insere(raiz->direita, x);
      if(fatorBal(raiz) == -2){
        if(x > raiz->direita->dado){ 
			raiz = rotaDDir(raiz); 
		}
        else{
			raiz = rotaDirEsq(raiz);
		}
      }
    }else{
      if(x <= raiz->dado){
        raiz -> esquerda = insere(raiz->esquerda, x);
        if(fatorBal(raiz) == 2){
          if(x < raiz->esquerda->dado){
		  	raiz = rotaDEsq(raiz);
		  }
          else{
		  	raiz = rotaEsqDir(raiz);
		  }
        }
      }
    }
  }
  raiz -> altura = altura(raiz);
  return raiz;
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
                Nodo* temp = nodo; //Nodo temporário que aponta para o elemento atual
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
	         if(fatorBal(nodo) == 2){
	          if(dado < nodo->esquerda->dado){
			  	nodo = rotaDEsq(nodo);
			  	
			  }else{
			  	nodo = rotaEsqDir(nodo);
			  }
	        }
    }else{
        if(nodo->dado < dado){
            nodo->direita = remover(nodo->direita, dado);
		      if(fatorBal(nodo) == -2){
		        if(dado > nodo->direita->dado){ 
					nodo = rotaDDir(nodo); 
					
				}else{
					nodo = rotaDirEsq(nodo);
				}
		      }
            
        }else{ // Ao elemento ser encontrado
        	nodo = removerAoEncontrar(nodo, dado);
        }
    }

    return nodo;
}


Nodo* criarNodo(int dado){
	Nodo *nodo = (Nodo*)malloc(sizeof(Nodo));
  	nodo->dado = dado;
  	nodo->altura = 0;
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
	raiz = insere(raiz, 25);
	raiz = insere(raiz, 35);
	raiz = insere(raiz, 45);
	raiz = insere(raiz, 65);
	raiz = insere(raiz, 55);
	raiz = insere(raiz, 44);
	raiz = insere(raiz, 34);
	raiz = insere(raiz, 24);
	raiz = insere(raiz, 10);
	raiz = insere(raiz, 15);
	raiz = remover(raiz, 25);
	raiz = remover(raiz, 35);
	raiz = remover(raiz, 15);
	raiz = insere(raiz, 42);
	raiz = insere(raiz, 40);
	raiz = insere(raiz, 43);
	raiz = remover(raiz, 44);
	raiz = insere(raiz, 60);
	raiz = insere(raiz, 70);
	raiz = insere(raiz, 50);
	raiz = insere(raiz, 67);
	raiz = insere(raiz, 64);
	raiz = remover(raiz, 65);

	printf("====================\n");
	
	printf("PreOrdem\n");
	preOrdem(raiz);
	
	printf("EmOrdem\n");
	emOrdem(raiz);
	
	printf("PosOrdem\n");
	posOrdem(raiz);
	
	return 0;
 
}
