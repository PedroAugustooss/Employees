#ifndef FUNCIONARIO_C
#define FUNCIONARIO_C

#include "Assinaturas.h"

int Escolhe_Codigo(){

    system("cls");

    int cod = 0;

    printf("Digite o codigo que deseja buscar: ");
    scanf("%d", &cod);

    return cod;
}

int Tamanho(){

    return ((sizeof(char) * 100) + (sizeof(char) * 15) + (sizeof(char) * 11) + sizeof(double) + sizeof(int));
}

int Tamanho_Arquivo(FILE* file){

    fseek(file, 0, SEEK_END);

    int tam = trunc(ftell(file) / Tamanho());

    return tam;
}

void Quantidade_Funcionarios(FILE* file){

    system("cls");

    printf("Quantidade de Funcionarios: %d\n\n", Tamanho_Arquivo(file));
}

Funcionario* Cria_Funcionario(){

    system("cls");

    printf("==================================== Criacao de Funcionario ====================================\n\n");

    Funcionario *func = (Funcionario*)malloc(sizeof(Funcionario));

    if(func == NULL){

        printf("Erro ao alocar memoria para a criacao do funcionario!");

        exit(1);
    }

    memset(func, 0, sizeof(Funcionario));
    
    while (getchar() != '\n'){} // Consumir o \n deixado pelo scanf

    printf("Digite o nome do funcionario: ");
    fgets(func->nome, sizeof(func->nome), stdin);
    func->nome[strcspn(func->nome, "\n")] = '\0'; //Remove o \n

    printf("\nDigite o CPF: ");
    fgets(func->cpf, sizeof(func->cpf), stdin);
    func->nome[strcspn(func->nome, "\n")] = '\0';

    while (getchar() != '\n');

    printf("\nDigite o aniversario (Separe por as datas por /): ");
    fgets(func->nascimento, sizeof(func->nascimento), stdin);
    func->nome[strcspn(func->nome, "\n")] = '\0';

    printf("\nDigite o salario: ");
    scanf("%lf", &func->salario);

    printf("\nDigite o codigo: ");
    scanf("%d", &func->cod);

    return func;
}

Funcionario* Funcionario_Base(int cod, char* nome, char* cpf, char* nascimento, double salario){

    Funcionario* func = (Funcionario*)malloc(sizeof(Funcionario));

    if(func == NULL){

        printf("Erro ao alocar memoria para a criacao do funcionario!");

        exit(1);
    }

    memset(func, 0, sizeof(Funcionario));

    strcpy(func->nome, nome);
    strcpy(func->cpf, cpf);
    strcpy(func->nascimento, nascimento);

    func->cod = cod;
    func->salario = salario;

    return func;
}

void Criar_Base_Ordenada(FILE* file){

    system("cls");

    int tam = 0;

    printf("Digite o tamanho: ");
    scanf("%d", &tam);

    Funcionario* func;

    for (int i = 1; i <= tam ; i++){

        fseek(file, 0, SEEK_END);

        func = Funcionario_Base(i, "A", "000.000.000-00", "01/01/1980", (3000 * i));

        Salva(func, file, false);
    }

    printf("Funcionario salvo com sucesso!\n\n");
}

void Criar_Base_Desordenada(FILE* file){

    system("cls");

    srand(time(NULL));

    int tam = 0;

    printf("Digite o tamanho: ");
    scanf("%d", &tam);

    Funcionario* func;

    for (int i = 1; i <= tam ; i++){

        int cod = (rand() % LIMITE);

        fseek(file, 0, SEEK_END);

        func = Funcionario_Base(cod, "A", "000.000.000-00", "01/01/1980", (3000 * i));

        Salva(func, file, false);
    }

    printf("Funcionario salvo com sucesso!\n\n");
}

void Salva(Funcionario* func, FILE* file, bool flag){

    system("cls");

    fwrite(func->nome, sizeof(char), sizeof(func->nome), file);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), file);
    fwrite(func->nascimento, sizeof(char), sizeof(func->nascimento), file);
    fwrite(&func->salario, sizeof(double), 1, file);
    fwrite(&func->cod, sizeof(int), 1, file);

    if(flag){

        printf("Funcionario salvo com sucesso!\n\n");
    }
}

Funcionario* Read(FILE* file){

    Funcionario* func = (Funcionario*)malloc(sizeof(Funcionario));

    if((fread(func->nome, sizeof(char), sizeof(func->nome), file)) <= 0){

        free(func);

        return NULL;
    }

    fread(func->cpf, sizeof(char), sizeof(func->cpf), file);
    fread(func->nascimento, sizeof(char), sizeof(func->nascimento), file);
    fread(&func->salario, sizeof(double), 1, file);
    fread(&func->cod, sizeof(int), 1, file);

    return func;
}

void Imprime(Funcionario* func){

    printf("**********************************************\n");
    printf("Nome: %s\nCPF: %s\nAniversario: %s\n", func->nome, func->cpf, func->nascimento);
    printf("Salario: $%.2lf\nCodigo: %d", func->salario, func->cod);
    printf("\n**********************************************\n\n");
}

void Imprime_Funcionarios(FILE* file, bool flag){

    if(flag){

        printf("\n==================================== Lista de Funcionarios ====================================\n\n");
    }

    rewind(file);

    Funcionario* func;
    //Funcionario* func = (Funcionario*)malloc(sizeof(Funcionario));

    while((func = Read(file)) != NULL){

        Imprime(func);
    }

    printf("===============================================================================================\n\n");

    free(func);
}

void Busca_Binaria(FILE* file, int key){

    system("cls");
    
    bool flag = false;

    Funcionario* func = (Funcionario*)malloc(sizeof(Funcionario));

    if (func == NULL){

        printf("Erro na alocação de memória na Busca Binária.\n");
        exit(1);
    }

    clock_t start = clock();

    int inicio = 0, fim = (Tamanho_Arquivo(file) - 1), meio, cont = 0;

    while(inicio <= fim){

        rewind(file);

        cont++;

        meio = ((fim + inicio) / 2);

        fseek(file, (meio*Tamanho()), SEEK_SET);

        func = Read(file);

        if(func->cod == key){

            Imprime(func);

            flag = true;

            break;
        }

        if(func->cod < key){

            inicio = (meio + 1);
        }

        if(key < func->cod){

            fim = (meio - 1);
        }
    }

    clock_t end = clock();

    double full_time = (((double)(end - start)) / CLOCKS_PER_SEC);

    Log_Binario(file, func, full_time, cont, flag, key);

    free(func);
}

void Log_Binario(FILE* file, Funcionario* func, double full_time, int cont, bool flag, int key){

    FILE* log = fopen("Log_Binario.txt", "a+");

    if(log == NULL){

        system("cls");

        printf("Erro ao acessar o log de registros binario.");

        return;
    }

    fprintf(log, "**********************************************************\n\n");
    fprintf(log, "Resultado para %d funcionarios: %s\nCodigo buscado: %d\nQuantidade de comparacoes: %d\nTempo para encontrar: %.40lf seg\n\n", Tamanho_Arquivo(file), (flag ? "Encontrado" : "Nao encontrado"), key, cont, full_time);

    if(flag){

        fprintf(log, "Nome: %s\nCPF: %s\nData de Nascimento: %s\nSalario: %.2lf\nCodigo: %d\n\n", func->nome, func->cpf, func->nascimento, func->salario, func->cod);
    }

    fclose(log);
}

void Buscar_Sequencial(FILE* file, int key){

    system("cls");

    Funcionario* func = (Funcionario*)malloc(sizeof(Funcionario));

    if(func == NULL){

        printf("Erro na alocacao de memoria na Busca Sequecial.");

        exit(1);
    }

    rewind(file);

    int cont = 0;
    bool flag = false;

    clock_t start = clock();

    while((func = Read(file)) != NULL){

        cont++;

        if(key == func->cod){

            Imprime(func);

            flag = true;

            break;
        }
    }

    clock_t end = clock();

    double full_time = (((double)(end - start)) / CLOCKS_PER_SEC);

    Log_Sequencial(file, func, full_time, cont, flag, key);

    free(func);
}

void Log_Sequencial(FILE* file, Funcionario* func, double full_time, int cont, bool flag, int key){

    FILE* log = fopen("Log_Sequencial.txt", "a+");

    if(log == NULL){

        system("cls");

        printf("Erro ao acessar o log de registros sequencial.");

        return;
    }

    fprintf(log, "**********************************************************\n\n");
    fprintf(log, "Resultado para %d funcionarios: %s\nCodigo buscado: %d\nQuantidade de comparacoes: %d\nTempo para encontrar: %.40lf seg\n\n", Tamanho_Arquivo(file), (flag ? "Encontrado" : "Nao encontrado"), key, cont, full_time);

    if(flag){

        fprintf(log, "Nome: %s\nCPF: %s\nData de Nascimento: %s\nSalario: %.2lf\nCodigo: %d\n\n", func->nome, func->cpf, func->nascimento, func->salario, func->cod);
    }

    fclose(log);
}

void Exclui_Funcionarios(FILE* file){

    system("cls");

    fclose(file);

    freopen("Funcionarios.dat", "w", file);
    freopen("Funcionarios.dat", "r+b", file);

    printf("Lista de funcionarios excluidas com sucesso!\n\n");
}

void Excluir_Dados(FILE* file){

    system("cls");

    fclose(file);

    remove("Log_Sequencial.txt");
    remove("Log_Binario.txt");
    remove("Log_Ordenacao.txt");

    freopen("Funcionarios.dat", "w", file);
    freopen("Funcionarios.dat", "r+b", file);

    Excluir_Particoes();

    printf("Arquivos excluidos com sucesso!\n\n");
}

void Log_Ordenacao(FILE* file, int cont, int cont_comp, double full_time){

    FILE* log = fopen("Log_Ordenacao.txt", "a+");

    if(log == NULL){

        system("cls");

        printf("Erro ao acessar o log de registros de ordenacao.");

        return;
    }

    fprintf(log, "**********************************************************\n\n");
    fprintf(log, "Foram realizadas %d troca(s) e %d comparacoes para uma base de %d funcionario(s).\n\n", cont, cont_comp, Tamanho_Arquivo(file));
    fprintf(log, "Tempo necessario: %.40lf seg\n\n", full_time);

    fclose(log);
}

void Insertion_Sort(FILE* file){

    system("cls");

    clock_t start = clock();

    rewind(file);

    Funcionario *fi, *fj;
    int qtd_Func = Tamanho_Arquivo(file), tam_Func = Tamanho(), i, cont = 0, cont_comp = 1;

    for(int j = 2; j <= qtd_Func; j++){
        
        fseek(file, ((j-1)*tam_Func), SEEK_SET);
        fj = Read(file);

        i = (j - 1);

        fseek(file, ((i-1)*tam_Func), SEEK_SET);
        fi = Read(file);

        cont_comp++;

        while((0 < i) && (fj->cod < fi->cod)){

            cont++;

            fseek(file, (i*tam_Func), SEEK_SET);
            Salva(fi, file, false);

            i--;

            fseek(file, ((i-1)*tam_Func), SEEK_SET);
            fi = Read(file);
        }

        fseek(file, (i*tam_Func), SEEK_SET);
        Salva(fj, file, false);
    }

    clock_t end = clock();

    double full_time = (((double)(end - start)) / CLOCKS_PER_SEC);

    Log_Ordenacao(file, cont, cont_comp, full_time);

    printf("Ordenado com sucesso!\n\n");
}

int Classificacao_Interna(FILE* file, int M){

    clock_t start = clock();

    rewind(file);

    int reg = 0, qtd_Func = Tamanho_Arquivo(file), qtd_Particoes = 0, tam = Tamanho();
    char nomeParticao[20];

    while (reg < qtd_Func){

        //le o arquivo e coloca no vetor
        Funcionario *v[M];

        int i = 0;

        while((i < M) && (reg < qtd_Func)){

            fseek(file, (reg * tam), SEEK_SET);
            v[i] = Read(file);

            i++;
            reg++;
        }

        //ajusta tamanho M caso arquivo de entrada tenha terminado antes do vetor
        if (i != M){

            M = i;
        }

        //faz ordenacao
        for (int j = 1; j < M; j++){

            Funcionario* func = v[j];

            i = (j - 1);

            while ((0 <= i) && (func->cod < v[i]->cod)){

                v[i + 1] = v[i];
                i = i - 1;
            }

            v[i + 1] = func;
        }

        sprintf(nomeParticao, "Partition%i.dat", (qtd_Particoes + 1)); //Cria arquivo de partição e faz gravação

        FILE* arq;

        if ((arq = fopen(nomeParticao, "wb+")) == NULL){

            printf("Erro ao criar arquivo de particao!\n\n");
        }

        rewind(arq);

        for (int i = 0; i < M; i++){

            fseek(arq, (i * tam), SEEK_SET);
            Salva(v[i], arq, false);
        }

        fclose(arq);

        qtd_Particoes++;

        for(int k = 0; k < M; k++){

            free(v[k]);
        }
    }

    clock_t end = clock();

    double full_time = (((double)(end - start)) / CLOCKS_PER_SEC);

    printf("Tempo para dividir em %d particoes: %.40lf seg\n\n", qtd_Particoes, full_time);

    return qtd_Particoes;
}

bool Quantidade_Element_Invalid(int* qtd_element){

    if((*qtd_element) < 1){

        printf("\nQuantidade invalida, tente novamente.\n\n");

        return true;
    }

    return false;
}

void Quantidade_Element_Partitions(FILE* file, int* qtd_Element_Partitions){

    system("cls");

    int qtd = Tamanho_Arquivo(file);

    do{

        printf("No momento existem %d funcionario(s) registrados.\n\nDigite a quantidade de elementos que cada particao tera: ", qtd);
        scanf("%d", qtd_Element_Partitions);

    }while(Quantidade_Element_Invalid(qtd_Element_Partitions));
}

void Imprime_Partitions(){

    system("cls");

    FILE* arq;
    int i = 1;
    char name[20];

    while(true){

        sprintf(name, "Partition%i.dat", i);

        if((arq = fopen(name, "rb")) == NULL){

            break;
        }

        printf("==================================== Particao %i ====================================\n\n", i);

        Imprime_Funcionarios(arq, false);

        printf("\n\n");

        i++;

        fclose(arq);
    }
}

void Excluir_Particoes(){

    system("cls");

    int i = 1;
    char name[20];

    while(true){

        sprintf(name, "Partition%i.dat", i);

        if(remove(name)){

            break;
        }

        i++;
    }

    printf("Particoes excluidas com sucesso!\n\n");
}

#endif