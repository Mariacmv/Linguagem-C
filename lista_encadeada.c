#include <stdio.h>
#include <stdlib.h>

typedef struct s_node{ //struct ocupa 4 bytes. Nessa estrutura são usados 5 bytes
    char data; //dado
    struct s_node* next;//ponteiro; tem que ser do mesmo tipo do bloco
} node;

void printLst(node* lst){ //recebe o começo da lista
    node* atual = lst; //começa na cabeça porque não defini fixamente
    //transforma em ponteiro para ser por referência, para pegar o endereço e não o valor fixo
    do{
        printf("%c\n", atual->data); //-> porque é ponteiro e não estou acessando a variável diretamente
        atual = atual->next;
    }while(atual != NULL);
    //printf("%c\n", atual.data); //printa o último porque ele verifica que é nulo e acaba não printando no while
}

void lst_init(node* lst){ //recebe a lista
    lst->data = NULL; //defino que o primeiro elemento é null 
    lst->next = NULL; //e que ele aponta para null também
}

void lst_add(node* lst, char value){
    while(lst->next != NULL){ //enquanto o próximo elemento não for nulo
        lst = lst->next; //pega esse próximo elemento
    }
    //já estando no último elemento, agora posso adicionar elementos
    node* atual = malloc(sizeof(node)); //função que aloca um espaço na memória. Para definir o quanto é para alocar utiliza o sizeof, que, no caso, aloca o tamanho da estrutura. atual tem que ser um ponteiro porque recebe um
    atual->data = value;
    atual->next = NULL;

    lst->next = atual;
}

int main(){
    // node A;
    // A.data = 'A';

    // node B;
    // B.data = 'B';
    // A.next = &B;

    // node C;
    // C.data = 'C';
    // B.next = &C;

    // node D;
    // D.data = 'D';
    // C.next = &D;

    // D.next = NULL; //para apontar para o final da lista

    // printf("Exibindo lista");
    // printLst(&A);
    // printf("\n\nExibindo novamente: \n");
    // printLst(&A);

    node lst; //1º elemento da lista - uma nova lista
    lst_init(&lst); //inicia a lista
    lst_add(&lst, 'A');
    lst_print(&lst);

    return 0;
}