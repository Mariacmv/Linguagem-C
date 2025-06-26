#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> //Biblioteca que da acesso a diretorios do sistema
#include <string.h> //5 - Biblioteca para manipular strings

void usarDepois(){
    int i;
    //2 - LEITURA DO ARQUIVO//
    FILE *fin = fopen("arquivos/teste.txt", "rb"); //aponto para um arquivo que quero abrir, que vou criptografar
    fseek(fin, 0, SEEK_END); //posiciona o ponteiro no 0 - comeco do arquivo e procura o final (funcao da linguagem C)
    long len = ftell(fin); //pego o tamanho do arquivo?
    rewind(fin); //volta para o comeco do arquivo (pq?)

    void *buffer = malloc(len); //aloco memoria para o tamanho do arquivo
    fread(buffer, len, 1, fin); //passa o endereco de memoria, o tamanho que vou ler, quantas vezes vou ler e aponto para o arquivo que vou ler

    fclose(fin); //fecho o arquivo porque ja salvei os dados na memoria

    //3 - CRIPTOGRAFIA DO ARQUIVO//
    for (i = 0; i < len; i++){ //agora itera sobre o buffer
        *(char*)(buffer + i) += 1;//pego o endereço do quê? Como é um ponteiro vou pegar apenas o primeiro byte (pq?) e o * no começo porque buffer é um ponteiro. Soma 1 para trocar os dados do documento (é a cifra)
    }

    //2 - VOLTANDO O ARQUIVO PARA O DISCO//
    FILE *fout = fopen("arquivos/teste_editado.txt", "wb");
    fwrite(buffer, len, 1, fout);
    fclose(fout);

    //3 - DESCRIPTOGRAFANDO//
    for (i = 0; i < len; i++){
        *(char*)(buffer + i) -= 1;
    }

    //3 - VOLTANDO O ARQUIVO PARA O DISCO//
    FILE *fout2 = fopen("arquivos/teste_decifrado.txt", "wb");
    fwrite(buffer, len, 1, fout2);
    fclose(fout2);
}

void buscaArquivos(char *raiz){ //4 - defino um ponteiro para deixar o diretório flexível
    //1- ACESSANDO UM DIRETÓRIO E O CONTEÚDO DELE//
    DIR  *d; //1 - Comando que acessa as bibliotecas do sistema
    struct dirent *dir; //1 - defino um ponteiro que aponta para a estrutura dirent?
    //estrutura que vai pegar uma pasta do diretorio

    d = opendir(raiz); //1 - determino que o ponteiro pega o diretorio em que o codigo esta rodando. 4 - Determino a pasta arquivos pq quero que pegue apenas ela (para teste): "./arquivos"
    dir = readdir(d); //1 - pega a primeira pasta e determina o ponteiro para ela e tambem o primeiro elemento do diretorio

    while (dir != NULL){
        if (dir->d_type == 0){ //4 - para listar apenas arquivo
            printf("%s\n", dir->d_name); //1 - imprime o diretorio que esta pegando
        }else if(dir->d_name[0] != '.'){ //4 - para não pegar a pasta raiz
            //char caminho[1024]; //5 - variável que vai pegar o tamanho do caminho de um diretório ou arquivo?
            char caminho[strlen(raiz) + dir->d_namlen + 1]; //6 - Para pegar o tamanho dinamicamente pego o tamanho da string do nome da pasta e somo com o tamanho do comprimento mais o /0
            snprintf(caminho, sizeof(caminho), "%s/%s", raiz, dir->name); //5 - função que envia uma mensagem(?) para algum endereço de memória que eu especificar. Primeiro determino o caminho para o qual vou passar a mensagem, o tamanho do buffer (é o tamanho máximo de caracteres que posso escrever) - pode chamar a variável ou pegar com sizeof(caminho) e o que será escrito
            // printf("Pasta: %s\n", dir->d_name); //4 - para exibir os diretórios também
            printf("Caminho da pasta: %s\n", dir->d_name); //5 -  Agora imprime o caminho da pasta ao invés de apenas o nome dela
        }
        dir = readdir(d); //1 - roda de novo porque senao so pega o primeiro 
    }

    closedir(d); //1 - fecha o diretorio
}

int main(){

    //4 - buscaArquivos("./arquivos"); //para pegar dentro da pasta 'arquivos'
    buscaArquivos("./arquivos"); 

    return 0;
}

//ÁRVORE DE ARQUIVOS -> FALTAM 02:13
