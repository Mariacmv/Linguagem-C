#include <stdio.h>
#include <stdlib.h>

int main(){
    int v[3][3];

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            printf("%d", v[i][j]);
        }
    }

    return 0;
}
