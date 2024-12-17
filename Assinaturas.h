#ifndef ASSINATURAS_H
#define ASSINATURAS_H

#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <time.h>

#define LIMITE 10000

typedef struct{

    char nome[100], cpf[15], nascimento[11];
    double salario;
    int cod;

}Funcionario;

Funcionario* Cria_Funcionario();
Funcionario* Read(FILE* file);
Funcionario* Funcionario_Base(int cod, char* nome, char* cpf, char* nascimento, double salario);

int Menu();
int Tamanho();
int Tamanho_Arquivo(FILE *arq);
int Escolhe_Codigo();
int Classificacao_Interna(FILE* file, int M);

bool Quantidade_Element_Invalid(int* qtd_element);

void Selecao(FILE* file);
void Criar_Base_Ordenada(FILE* file);
void Criar_Base_Desordenada(FILE* file);
void Salva(Funcionario* func, FILE* file, bool flag);
void Imprime_Funcionarios(FILE* file, bool flag);
void Imprime_Partitions();
void Quantidade_Element_Partitions(FILE* file, int* qtd_Element_Partitions);
void Imprime(Funcionario* func);
void Buscar_Sequencial(FILE* file, int key);
void Busca_Binaria(FILE* file, int key);
void Quantidade_Funcionarios(FILE* file);
void Log_Sequencial(FILE* file, Funcionario* func, double full_time, int cont, bool flag, int key);
void Log_Binario(FILE* file, Funcionario* func, double full_time, int cont, bool flag, int key);
void Exclui_Funcionarios(FILE* file);
void Excluir_Particoes();
void Excluir_Dados(FILE* file);
void Insertion_Sort(FILE* file);
void Log_Ordenacao(FILE* file, int cont, int cont_comp, double full_time);

#endif