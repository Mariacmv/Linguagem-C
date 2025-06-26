#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> //Biblioteca que da acesso a diretorios do sistema

int main(){

    // DIR  *d; //Comando que acessa as bibliotecas do sistema
    // struct dirent *dir; //defino um ponteiro que aponta para a estrutura dirent?
    // //estrutura que vai pegar uma pasta do diretorio

    // d = opendir("."); //determino que o ponteiro pega o diretorio em que o codigo esta rodando
    // dir = readdir(d); //pega a primeira pasta e determina o ponteiro para ela e tambem o primeiro elemento do diretorio

    // while (dir != NULL){
    //     printf("%d %s\n", dir->d_type, dir->d_name); //imprime o diretorio que esta pegando
    //     dir = readdir(d); //roda de novo porque senao so pega o primeiro 
    // }

    // closedir(d); //fecha o diretorio

    //LEITURA DO ARQUIVO//
    FILE *fin = fopen("arquivos/teste.txt", "rb"); //aponto para um arquivo que quero abrir, que vou criptografar
    fseek(fin, 0, SEEK_END); //posiciona o ponteiro no 0 - comeco do arquivo e procura o final (funcao da linguagem C)
    long len = ftell(fin); //pego o tamanho do arquivo?
    rewind(fin); //volta para o comeco do arquivo (pq?)

    void *buffer = malloc(len); //aloco memoria para o tamanho do arquivo
    fread(buffer, len, 1, fin); // passa o endereco de memoria, o tamanho que vou ler, quantas vezes vou ler e aponto para o arquivo que vou ler

    fclose(fin); //fecho o arquivo porque ja salvei os dados na memoria


    //CRIPTOGRAFIA DO ARQUIVO//

    //VOLTANDO O ARQUIVO PARA O DISCO//
    FILE *fout = fopen("arquivos/teste_editado.txt", "wb");
    fwrite(buffer, len, 1, fout);
    fclose(fout);

    return 0;
}