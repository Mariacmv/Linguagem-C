#include <stdio.h>
#include <stdlib.h>

int main(){

    char mensagem[] = "ola tudo bem?";//char, na memória, é um número, então permite realizar expressões matemáticas
    int chave = 4;
    int i;

    for (i=0; i<13; i++){
        if(mensagem[i] != ' ' && mensagem[i] != '?'){
            mensagem[i] += 4;
        }
    }
    printf("%s", mensagem);
    //printf("%d", mensagem[0]); mostra o endereço de memória

    return 0;
}