#include "Assinaturas.h"
#include "Engine.c"

int main(){

    FILE* arq = fopen("Funcionarios.dat", "a+b");
    
    fclose(arq);

    FILE* file = fopen("Funcionarios.dat", "r+b");

    if(file == NULL){
        printf("Erro ao abrir o arquivo!\n");

        exit(1);
    }

    Selecao(file);

    fclose(file);

    return 0;
}