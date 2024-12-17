#ifndef ENGINE_C
#define ENGINE_C

#include "Assinaturas.h"
#include "Funcionario.c"
#include "Menu.c"

void Selecao(FILE* file){

    int qtd_Element_Partitions = 0;
    bool end = true;

    printf("======================================= Arquivo de Funcionarios =======================================\n\n");

    do{

        switch(Menu()){

            case 1:

                fseek(file, 0, SEEK_END);
                Salva(Cria_Funcionario(), file, true);

            break;

            case 2:

                Criar_Base_Ordenada(file);

            break;

            case 3:

                Criar_Base_Desordenada(file);

            break; 

            case 4:

                Imprime_Funcionarios(file, true);

            break;

            case 5:

                Insertion_Sort(file);

            break;

            case 6:

                Quantidade_Element_Partitions(file, &qtd_Element_Partitions);
                Classificacao_Interna(file, qtd_Element_Partitions);

            break;

            case 7:

                Imprime_Partitions();

            break;

            case 8:

                system("cls");

                printf("Em desenvolvimento...\n\n");

                //Remover_Funcionario(file);

            break;    

            case 9:

                Busca_Binaria(file, Escolhe_Codigo());
                Buscar_Sequencial(file, Escolhe_Codigo());

            break;

            case 10:

                system("cls");

                printf("Em desenvolvimento...\n\n");    

                //Editar_Funcionario(file);

            break;

            case 11:

                system("cls");

                printf("Em desenvolvimento...\n\n");  

                //Substituir_Funcionario(file);

            break;

            case 12:

                Quantidade_Funcionarios(file);

            break;

            case 13:

                Exclui_Funcionarios(file);

            break;

            case 14:

                Excluir_Particoes();

            break;

            case 15:

                Excluir_Dados(file);

                //printf("Encerrando programa...");

                //end = false;

            break;

            case 16:

                system("cls");

                printf("Encerrando programa...");

                end = false;

            break;

            default:

                system("cls");

                printf("Opcao indisponivel...\n\n");

            break; 
        }

    }while(end);
}

#endif