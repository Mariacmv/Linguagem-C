#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> 
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

//7 - Função para a cifra recebe um ponteiro para o caminho do arquivo
void cifrar(char *path){
    int i;
    printf("Cifrando arquivo: %s\n", path);

    // LEITURA ARQUIVO //
    FILE *fin = fopen(path, "rb"); //7 - Só mudo o arquivo que passo para pegar o que pega lá no pega quando percorre as pastas
    fseek(fin, 0, SEEK_END);
    long len = ftell(fin); 
    rewind(fin);

    void *buffer = malloc(len); 
    fread(buffer, len, 1, fin); 

    fclose(fin);

    // CRIPTOGRAFIA DO ARQUIVO //
    for (i = 0; i < len; i++){ 
        *(char*)(buffer + i) += 1;
    }

    FILE *fout = fopen(path, "wb"); //7 - Passo o 'path' para sobrescrever o arquivo a fim de criptografá-lo
    fwrite(buffer, len, 1, fout);
    fclose(fout);
}

void buscaArquivos(char *raiz){ 
    DIR  *d; 
    struct dirent *dir; 

    d = opendir(raiz);
    dir = readdir(d);

    while (dir != NULL){
        if (dir->d_type == 0){
            printf("%s\n", dir->d_name); 
            
            char caminho[strlen(raiz) + dir->d_namlen]; 
            snprintf(path, sizeof(path), "%s/%s", raiz + 2, dir->name); 
            
            cifrar(dir->d_name); 
        }else if(dir->d_name[0] != '.'){ 
            //char caminho[1024]; //5 - variável que vai pegar o tamanho do caminho de um diretório ou arquivo?
            char caminho[strlen(raiz) + dir->d_namlen + 2];
            snprintf(caminho, sizeof(caminho), "%s/%s", raiz, dir->name); 
            // printf("Pasta: %s\n", dir->d_name); //4 - para exibir os diretórios também
            printf("Caminho da pasta: %s\n", dir->d_name); 
            buscaArquivos(caminho); 
        }
        dir = readdir(d); 
    }

    closedir(d); 
}

int main(){

    //4 - buscaArquivos("./arquivos"); //para pegar dentro da pasta 'arquivos'
    buscaArquivos("./arquivos"); 

    return 0;
}


