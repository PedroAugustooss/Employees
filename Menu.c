#ifndef MENU_C
#define MENU_C

#include "Assinaturas.h"

int Menu(){

    int op = 0;

    printf("[1] Criar Funcionario.\n[2] Criar Funcionarios Aleatorios(Ordenados).\n[3] Criar Funcionarios Aleatorios(Desodernados).\n[4] Mostrar Funcionarios salvos.\n");
    printf("[5] Ordenar Funcionarios.\n[6] Classificacao Interna.\n[7] Imprime Particoes.\n[8] Remover Funcioanrio.\n[9] Buscar Funcionario.\n[10] Editar Funcionario.\n");
    printf("[11] Substituir Funcionario.\n[12] Mostrar quantidade de Funcionarios.\n");
    printf("[13] Excluir lista de Funcionarios.\n[14] Excluir Particoes.\n[15] Excluir todos os arquivos.\n[16] Sair do programa.\n");

    printf("\nEscolha: ");
    scanf("%d", &op);

    return op;
}

#endif