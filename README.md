# Arvore Balanceada AVL


Obs: A árvore balanceada não validou a sequência correta de valores durante a apresentação, pois o código não aceitava a inserção de dois ou mais valores iguais(se era maior, inseria à direita e se era menor inseria à esquerda).

A única alteração feita foi a adição de um "=" na linha 125 do código, dentro da função insere();

    if(x < raiz->dado){
               ⇩
    if(x <= raiz->dado){
