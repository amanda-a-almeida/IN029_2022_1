#include <stdio.h>
#include <stdlib.h>
#include <string.h> // elimina o '/n' durante o gets() por conta do espaço entre os inputs do usuário
#include <ctype.h>

// #include "cadastroPessoasV0.h"
//#include "opcoesMenuV0.h"

//  Variáveis Globais  
int opcao, cont =0, contd =0, verificador_menu_inicial = 1, cadastrar_novamente = 2, excluir_novamente = 2, atualizar_novamente = 2;//opcao = escolha do menu inicial
int comp, classificacao;
long long int matricula_exclusao;
#define TAM 5 //contador geral do vetor pessoas para o cadastro


//********************************************
// Verificadores
//********************************************

// Verificador data de nascimento
int valida_data (int d,int m,int a){//passar parametros para função (pessoas[].dia, pessoas[].mes, pessoas[].ano)
    int mes_fev;
    // Verificar se é Ano Bisexto
    if( (a%4==0)||((a%100==0)&&(a%400==0)) ){
        mes_fev = 29;
    } else{
        mes_fev = 28;
    }

    // Definir valor máximo de dias pors meses
    if( (m == 1) || (m ==3) || (m == 5) || (m == 7) || (m == 8) || (m == 10) || (m == 12) && (d <= 31) ){
        return 0;

    } else if( (m==2) && (d <= mes_fev) ){
        return 0;

    } else if( (m == 4) || (m ==6) || (m == 9) || (m ==11) && (d <= 30) ){
        return 0;

    }
    else{
        printf("\n* Data invalida! *");
        return -1; //
    } 
}


// Verificador CPF
int valida_cpf(char cpf[12]){
    int icpf[12];  
    int i, somador=0, digito1, result1, result2, digito2, valor;    
      
    for(i=0;i<11;i++){  //Efetua a conversao de array de char para um array de int pela tabela ASCII.
        icpf[i]=cpf[i]-48;  
    }  

    //Verificação do primeiro digito.    
    for(i=0;i<9;i++){  
        somador+=icpf[i]*(10-i);  
    }    
    result1=somador%11;    
    if( (result1==0) || (result1==1) ){  
        digito1=0;  
    } else{  
        digito1 = 11-result1;  
    }  
    
    //Verificação do segundo digito.
    somador=0;
    for(i=0;i<10;i++){  
        somador+=icpf[i]*(11-i);  
    }  
    valor=(somador/11)*11;  
    result2=somador-valor;
    
    if( (result2==0) || (result2==1) ){  
        digito2=0;  
    } else{  
        digito2=11-result2;  
    }  
    
    //RESULTADOS DA VALIDACAO FINAl DO CPF.  
    if((digito1==icpf[9]) && (digito2==icpf[10])){  
        return 0;  
    } else{  
        printf("\n* CFP Inválido! *\n");
        return -1;  
    }   
}


//**********************************************
// Struct Módulo cadastro Pessoas e Disciplinas
//**********************************************

//  Struct de cadatro de Alunos e Professores
typedef struct 
{
    long long int matricula;
    char nome[50];
    char sexo; // M , F
    int dia_nascimento;
    int mes_nascimento;
    int ano_nascimento; 
    char cpf[12];
    int classificacao; // 0 - professor / 1 - aluno
    int qtd_materias_pessoa;
} dados_pessoa;

dados_pessoa pessoas[TAM];//u será a variavel do vetor de pessoas[u].

//  Struct de cadatro das Disciplinas
typedef struct 
{
    char nome_disciplina[50];
    char codigo_disciplina[7];
    int semestre;
    long long int matricula_professor;
    long long int alunos_matriculados[60];
    int qtd_alunos_matriculados;
} dados_disciplina;

dados_disciplina disciplina[TAM];

//**********************************************
// Struct Módulo cadastro Pessoas e Disciplinas
//**********************************************

//  Módulo de cadatro de Disciplinas
int cadastro_disciplina(int cadastrar_novamente){
    getchar();  // absorve o '\n' que o scanf não leu
    printf("Nome da Disciplina: \n>>> ");    
    fflush(stdin);
    fgets(disciplina[contd].nome_disciplina, 50, stdin);
    for(int i=0; disciplina[contd].nome_disciplina[i]; i++) if(disciplina[contd].nome_disciplina[i]=='\n') disciplina[contd].nome_disciplina[i]=0;
    printf("Código da Disciplina (6 dígitos): \n>>> ");
    scanf("%s", &disciplina[contd].codigo_disciplina);
    
    do
    {
        printf("Semestre da Disciplina: \n>>> ");
        scanf("%i", &disciplina[contd].semestre);
        if ( !((disciplina[contd].semestre > 0) || (disciplina[contd].semestre <= 10)) ){
            printf("\n***** Semestre Inválido! *****\n");
        }
    } while ( !((disciplina[contd].semestre > 0) || (disciplina[contd].semestre <= 10)) );
    
    int veri_matri_prof = 0;
    do
    {
        printf("\nDigite o Numero da Matricula do Professor (11 Digitos):\n>>> ");
        scanf("%lld", &disciplina[contd].matricula_professor);
        getchar();  // absorve o '\n' que o scanf não leu
        for (int i=0; i < cont; i++){
            if (disciplina[contd].matricula_professor == pessoas[i].matricula){
                veri_matri_prof ++;
            }
        }
        if (veri_matri_prof == 0){
                printf("\n***** Não Existe Professor com a Matricula Informada! *****\n");
            }
    } while (veri_matri_prof == 0);
    contd++;
    printf("\n*****     Cadastro realizado com sucesso!     *****\n");

    do
    {
        printf("\nDeseja cadastrar outra Disciplina?\n  (1 - Sim / 0 - Não)\n>>> ");
        scanf("%d", &cadastrar_novamente);
        if (!(cadastrar_novamente == 1 || cadastrar_novamente == 0)){
            printf("\n***** Opção Inválida! ****\n");
        }
    } while (!(cadastrar_novamente == 1 || cadastrar_novamente == 0));
    return cadastrar_novamente;
}


//  Módulo de cadatro de Alunos e Professores
int cadastro_pessoa (int opcao_cadastro, int cadastrar_novamente) { 
    //char tipo_pessoa[15];
    char *tipo_pessoa;        
    if (opcao_cadastro == 1){
            tipo_pessoa = "Aluno";
            classificacao = 1;
        }
    else if (opcao_cadastro == 2){
            tipo_pessoa = "Professor";
            classificacao = 0;
        }

    printf("\nDigite o Numero da Matricula (11 Digitos):\n>>> ");
    scanf("%lld", &pessoas[cont].matricula);
    getchar();  // absorve o '\n' que o scanf não leu
    printf("\nDigite o Nome do %s:\n>>> ", tipo_pessoa); 
    fflush(stdin);
    fgets(pessoas[cont].nome, 50, stdin);
    for(int i=0; pessoas[cont].nome[i]; i++) if(pessoas[cont].nome[i]=='\n') pessoas[cont].nome[i]=0;
    do
    {
        printf("\nDigite o sexo (F / M):\n>>> ");    
        scanf("%c", &pessoas[cont].sexo);
        pessoas[cont].sexo = toupper(pessoas[cont].sexo);
        if (!(pessoas[cont].sexo == 'F' || pessoas[cont].sexo == 'M')){
            printf("\n***** Opção Inválida! ****\n");
        }
    } while (!(pessoas[cont].sexo == 'F' || pessoas[cont].sexo == 'M'));

    int check_data = -1;
    do
    {
        printf("\nDigite a Data de Nascimento (dd/mm/aaaa)\n>>> ");
        scanf("%d/%d/%d", &pessoas[cont].dia_nascimento, &pessoas[cont].mes_nascimento, &pessoas[cont].ano_nascimento);
        check_data = valida_data(pessoas[cont].dia_nascimento, pessoas[cont].mes_nascimento, pessoas[cont].ano_nascimento);//validaçao da data
    } while (check_data==-1);

    int check_cpf = -1;
    do
    {
        getchar();
        printf("\nDigite o CPF (sem pontos ou tracos):\n>>> ");
        fflush(stdin);
        fgets(pessoas[cont].cpf, 12, stdin);
        for(int i=0; pessoas[cont].cpf[i]; i++) if(pessoas[cont].cpf[i]=='\n') pessoas[cont].cpf[i]=0;
        check_cpf = valida_cpf(pessoas[cont].cpf);

    } while (check_cpf == -1);
    pessoas[cont].classificacao = classificacao;

        //dados cadastrados
    printf("Nome: %s, Matrícula: %lld, Sexo: %c, data de nascimento: %d/%d/%d, CPF: %s, Classificação: %d, Tipo Pessoa: %s\n", pessoas[cont].nome, pessoas[cont].matricula, pessoas[cont].sexo, pessoas[cont].dia_nascimento, pessoas[cont].mes_nascimento, pessoas[cont].ano_nascimento, pessoas[cont].cpf, pessoas[cont].classificacao, tipo_pessoa);
    printf("\n*****     Cadastro realizado com sucesso!     *****\n");
    cont++;

    do
    {
        printf("\nDeseja cadastrar outro %s?\n  (1 - Sim / 0 - Não)\n>>> ", tipo_pessoa);
        scanf("%d", &cadastrar_novamente);
        if (!(cadastrar_novamente == 1 || cadastrar_novamente == 0)){
            printf("\n***** Opção Inválida! ****\n");
        }
    } while (!(cadastrar_novamente == 1 || cadastrar_novamente == 0));
    return cadastrar_novamente;
}


// Módulo Excluir Alunos e Professores
int excluir_pessoa(int opcao_cadastro, int excluir_novamente){ //função de excluir cadastro
    char *tipo_pessoa;
    int u = 0, classificacao;
    if (opcao_cadastro == 1){
            tipo_pessoa = "Aluno";
            classificacao = 1;
            lista_alunos();
        }
    else if (opcao_cadastro == 2){
            tipo_pessoa = "Professor";
            classificacao = 0;
            lista_professores();
        
    }

    printf("\n********************************************************************\n");
    printf("Digite a matricula do %S que deseja excluir.\n>>> ", tipo_pessoa);
    scanf("%lld", &matricula_exclusao);

    int mat = 0; // contador que identifica quantas vezes o else if foi acessado para saber se a matricula existe ou não
    for(u ; u <= cont; u++){
        if( (pessoas[u].classificacao ==  classificacao) && (matricula_exclusao == pessoas[u].matricula) ){
            pessoas[u].matricula *= (-1);
            u = cont;
        }else if( (pessoas[u].classificacao ==  classificacao) && (matricula_exclusao != pessoas[u].matricula) ){
            mat++;
        }
    }
    if ((mat == cont)){
        printf("\n***** Matrícula não Encontrada! *****\n");

    } else if ( (u == cont) && (mat < cont)){
        printf("\n***** Matrícula Excluida! *****\n");
    }

    do
    {
        printf("\nDeseja excluir outra matrícula de %s?\n  (1 - Sim / 0 - Não)\n>>> ", tipo_pessoa);
        scanf("%d", &excluir_novamente);
        if (!(excluir_novamente == 1 || excluir_novamente == 0)){
            printf("\n***** Opção Inválida! ****\n");
        }
    } while (!(excluir_novamente == 1 || excluir_novamente == 0));
    return excluir_novamente;
}


// Módulo Alterar Alunos e Professores
int atualizar_pessoa(opcao_cadastro, atualizar_novamente){ ///função de atualizar cadastro
    int matricula_alterar;
    int u = 0, verificador_alterar;
    int campo_alterar;
    char *tipo_pessoa; 

    if (opcao_cadastro == 1){
        tipo_pessoa = "Aluno";
        classificacao = 1;
    }
    else if (opcao_cadastro == 2){
        tipo_pessoa = "Professor";
        classificacao = 0;
    }

    
    do
    {
        printf("Digite A matricula do %s que voce deseja alterar:\n>>> ", tipo_pessoa);
        scanf("%d",& matricula_alterar);
        do
        {        
            if(matricula_alterar == pessoas[u].matricula){      
                if(pessoas[u].classificacao == classificacao){
                    verificador_alterar = 1;
                } else{
                    printf("Matrícula Inválida! Não pertence a um %s\n", tipo_pessoa);
                    verificador_alterar = 2;
                }       
            }u++;
        } while ( (u <= cont) && (verificador_alterar == 0) );
    } while (verificador_alterar == 2); 

    u--;
    int check_data = -1;
    int check_cpf = -1;
    if (verificador_alterar == 1){
        do
        {
            do
            {
                printf("0 - Voltar\n1 - Matricula: %d\n2 - Nome: %s\n3 - Sexo: %c\n4 - Data de Nascimento: %d/%d/%d\n5 - CPF: %s\n", pessoas[u].matricula, pessoas[u].nome, pessoas[u].sexo, pessoas[u].dia_nascimento, pessoas[u].mes_nascimento, pessoas[u].ano_nascimento, pessoas[u].cpf);
                printf("Digite o campo que deseja alterar:\n>>> ");
                scanf("%d", &campo_alterar);
                if ( (campo_alterar < 0) || (campo_alterar > 6) ){
                    printf("\n***** Opção Inválida! ****\n");
                }
            } while ( (campo_alterar < 0) || (campo_alterar > 6) );

            switch(campo_alterar){
            case 0:
                menu_cadastro();
            case 1: // matricula
                printf("\nDigite a nova matricula:\n>>> ");
                scanf("%d",&pessoas[u].matricula);
                printf("\nMatricula Alterada!\n");
                break;
            case 2: // nome
                getchar();
                printf("Digite o novo nome:\n>>> ");                
                fgets(pessoas[u].nome, 50, stdin);
                size_t len = strlen(pessoas[u].nome)-1;
                if (pessoas[u].nome[len] == '\n'){
                    pessoas[u].nome[len] = '\0';
                }
                printf("\nNome Alterado!\n");
                break;
            case 3: // sexo
                printf("\nDigite o sexo (M / F):\n>>> ");
                scanf("%c", pessoas[u].sexo);
                printf("\nSexo Alterado!\n");
                break;
            case 4: // data
                do
                {
                    printf("\nDigite a nova Data de Nascimento (dd/mm/aaaa)\n>>> ");
                    scanf("%d/%d/%d", &pessoas[u].dia_nascimento, &pessoas[u].mes_nascimento, &pessoas[u].ano_nascimento);
                    check_data = valida_data(pessoas[u].dia_nascimento, pessoas[u].mes_nascimento, pessoas[u].ano_nascimento);//validaçao da data
                } while (check_data==-1);
                break;
            case 5: //cpf
                do
                {
                    getchar();
                    printf("\nDigite o novo CPF (sem pontos ou tracos):\n>>> ");
                    fflush(stdin);
                    fgets(pessoas[u].cpf, 12, stdin);
                    for(int i=0; pessoas[u].cpf[i]; i++) if(pessoas[u].cpf[i]=='\n') pessoas[u].cpf[i]=0;
                    check_cpf = valida_cpf(pessoas[u].cpf);
                } while (check_cpf == -1);
                break;
            }

            do
            {
                printf("\nDeseja atualizar outro campo de %s?\n  (1 - Sim / 0 - Não)\n>>> ", pessoas[u].nome);
                scanf("%d", &verificador_alterar);
                if (!(verificador_alterar == 1 || verificador_alterar == 0)){
                    printf("\n***** Opção Inválida! ****\n");
                }
            } while (!(verificador_alterar == 1 || verificador_alterar == 0));            
            
        } while (verificador_alterar == 1);
    }  

    do
    {
        printf("\nDeseja atualizar outro cadastro de %s?\n  (1 - Sim / 0 - Não)\n>>> ", tipo_pessoa);
        scanf("%d", &atualizar_novamente);
        if (!(atualizar_novamente == 1 || atualizar_novamente == 0)){
            printf("\n***** Opção Inválida! ****\n");
        }
    } while (!(atualizar_novamente == 1 || atualizar_novamente == 0));
    return atualizar_novamente, opcao_cadastro;
}


//**********************************************
// Módulo de Relatórios
//**********************************************

// 1 - Listar Alunos
int lista_alunos(void){
    printf("\n****************************\n");
    printf(  "*     Lista de Alunos:     *");
    printf("\n****************************\n");
    int u = 0, tam;
    tam = cont;
    while (u < tam){
        if( (pessoas[u].matricula > 0) && (pessoas[u].classificacao == 1) ){
            printf("Aluno: %s, Matrícula: %lld\n",pessoas[u].nome, pessoas[u].matricula);     
        }
        u++;
    }
}

// 2 - Listar de Professores
int lista_professores(void){
    printf("\n****************************\n");
    printf(  "*   Lista de Professores   *");
    printf("\n****************************\n");
    int u = 0, tam;
    tam = cont; // contador de pessoas cadastradas
    while (u < tam){
        if(pessoas[u].matricula > 0 && pessoas[u].classificacao == 0){
            printf("Professor: %s, Matrícula: %lld\n",pessoas[u].nome, pessoas[u].matricula);     
        }
        u++;
    }
}

// 3 - Listar Disciplinas
int lista_disciplinas(void){
    printf("\n****************************\n");
    printf(  "*     Lista Disciplinas    *");
    printf("\n****************************\n");
    int d = 0, tam, u = 0;
    char *nome_professor;
    tam = contd;  // contador de disciplinas cadastradas
    while (d < tam){
        for(u = 0; u < cont; u++){
            if( (pessoas[u].matricula == disciplina[d].matricula_professor) &&  (pessoas[u].classificacao) == 0){                
                nome_professor = &pessoas[u].nome;
                u = cont;                 
            }
        }
        printf("Nome: %s, Codigo: %s, Semestre: %d, Matrícula Professor: %lld, Nome Professor: %s\n",disciplina[d].nome_disciplina, disciplina[d].codigo_disciplina, disciplina[d].semestre, disciplina[d].matricula_professor, nome_professor);     
        d++;
    }
}

// 4 - Listar Disciplinas Específica


// 5 - Listar Alunos por Sexo (M/F)


// 6 - Listar Alunos Ordenados por Nome
/*
void ordenar (int opcao_relatorio){   
    printf("\n****************************\n");
    printf(  "*    Ordenados por Nome    *");
    printf("\n****************************\n");    

    char ordenador_aluno[cont];
    char ordenador_professor[cont];
    int u, u2, contador;
    char auxiliar[50];
    for(u=0; u<cont; u++){//preenche o ordenador de aluno e de professor
        if(opcao_relatorio == 6){
            if(pessoas[u].classificacao == 1){
            strcpy(pessoas[u].nome,ordenador_aluno[u]);
            }
        }else if(opcao_relatorio == 9){
            if(pessoas[u].classificacao == 0){
                strcpy(pessoas[u].nome,ordenador_professor[u]);
            }
        }
    }
    for (u = 0; u<cont; u++){//ordena aluno
        for (u2 = u+1; u2<cont; u2++){
            contador = strcmp(ordenador_aluno[u], ordenador_aluno[u2]);
            if(contador > 0){
                strcpy(auxiliar,ordenador_aluno[u]);
                strcpy(ordenador_aluno[u], ordenador_aluno[u2]);
                strcpy(ordenador_aluno[u2],auxiliar);
            }
        }
    }
    for (u = 0; u<cont; u++){//ordena professor
        for (u2 = u+1; u2<cont; u2++){
            contador = strcmp(ordenador_professor[u], ordenador_professor[u2]);
            if(contador > 0){
                strcpy(auxiliar,ordenador_professor[u]);
                strcpy(ordenador_professor[u], ordenador_professor[u2]);
                strcpy(ordenador_professor[u2],auxiliar);
            }
        }
    }
    if(opcao_relatorio == 6){
        for(u=0; u<cont; u++){
                printf("%s", ordenador_aluno[u]);
            }
    }
    else if(opcao_relatorio == 9){
        for(u=0; u<cont; u++){
                printf("%s", ordenador_professor[u]);
            }
    }
    
    
}
*/

// 7 - Listar Alunos Ordenados por Data de Nascimento


// 8 - Listar Professores por Sexo (M/F)


// 9 - Listar Professores Ordenados por Nome
        // >>> feito no item 6
void ordenar_pornome(int opcao_relatorio){
    //char *tipo_pessoa;
    char tipo_pessoa[14];
    char ordenador_pessoas[cont][50], auxiliar[50];
    int u = 0, u2, contador, qtd_pessoas = 0;

    if (opcao_relatorio == 9){
        classificacao = 0;
        char tipo_pessoa[] = "Professor";

    } else if (opcao_relatorio == 6){
        classificacao = 1;
        char tipo_pessoa[] = "Aluno";
    }    
    printf("\n******************************************************\n");
    printf(  "Lista %s Ordenado por Nome    ", tipo_pessoa);
    printf("\n******************************************************\n");
    printf("Teste antes do for");

    for(u = 0; u < cont; u++){ //preenche o ordenador de aluno e de professor
        printf("Teste entrou 1º for");
        if( (pessoas[u].classificacao == classificacao) && (pessoas[u].matricula > 0) ){
            strcpy(ordenador_pessoas[u], pessoas[u].nome);
            printf("Teste %s, %s", pessoas[u].nome, ordenador_pessoas[u]); // teste
            qtd_pessoas++;
        }        
    }

    for (u = 0; u<cont; u++){//ordena alunos ou professores
        printf("Teste entrou 2º for");
        for (u2 = u+1; u2<cont; u2++){
            printf("Teste entrou 3º for");
            contador = strcmp(ordenador_pessoas[u], ordenador_pessoas[u2]);
            if(contador > 0){
                strcpy(auxiliar, ordenador_pessoas[u]);
                strcpy(ordenador_pessoas[u], ordenador_pessoas[u2]);
                strcpy(ordenador_pessoas[u2], auxiliar);
                printf("Teste %s, %s", ordenador_pessoas[u], ordenador_pessoas[u2]); // teste
            }
        }
    }    
    for(u=0; u < qtd_pessoas; u++){
        printf("Teste entrou 4º for");
        for(u2=0; u2<cont; u2++){
            printf("Teste entrou 5º for");
            if(ordenador_pessoas[u] == pessoas[u2].nome){
                printf("Nome: %s, Matrícula: %lld\n", pessoas[u].nome, pessoas[u].matricula);
            }
            printf("Teste %s qtd_pessoas", qtd_pessoas);
        }
    }
}


// 10 - Listar Professores Ordenados por Data de Nascimento


// 11 - Aniversariantes do Mês


// 12 - Buscar (Professor / Aluno) por Parte do Nome
int buscar_pessoa(void){
    //char tipo_pessoa[15];
    char *tipo_pessoa;
    int buscalen, len, u = 0;
    char busca[50];
    char *pont_busca;
    printf("\n****************************\n");
    printf(  "*       Menu de Busca      *");
    printf("\n****************************\n");
    printf("Digite pelo menos 3 letras do nome da pessoa para busca-la:\n>>> ");
    getchar();
    fgets(busca, 50, stdin);
    do
    {
        printf("Digite pelo menos 3 letras do nome da pessoa para busca-la:\n>>> ");
        getchar();
        fgets(busca, 50, stdin);
    } while (strlen(busca) <= 2);

    for(int i=0; busca[i]; i++) if(busca[i]=='\n') busca[i]=0;
    do{        	
        pont_busca = strstr(pessoas[u].nome, busca);

        if( pont_busca != NULL ){
            if( pessoas[u].classificacao == 1){
                //char tipo_pessoa[] = "Aluno";
                tipo_pessoa = "Aluno";
            } else if(pessoas[u].classificacao == 0){
                //char tipo_pessoa[] = "Professor";
                tipo_pessoa = "Professor";
            }
            printf("Nome do %s: %s, Matricula: %lld\n", tipo_pessoa, pessoas[u].nome, pessoas[u].matricula);
        }
        u++;
    } while (u <= cont);

}

// 13 - Lista de Alunos Matriculados em Menos de 3 Disciplinas


// 14 - Listar Disciplinas que Extrapolam 40 Vagas


//**********************************************
// Módulo de Menus
//**********************************************

//   Menu Inicial
int menu_inicial(){
    printf("\n****************************\n");
    printf(  "*       Menu inicial       *");
    printf("\n****************************\n");
    printf("Digite a opção desejada.\n");
    printf("0 - Encerrar Programa.\n");
    printf("1 - Menu Cadastro.\n");
    printf("2 - Menu Relatórios.\n>>> ");
    scanf("%d", &opcao);

    switch (opcao){
    case 0: // Encerrar Programa
        printf("\n*       Programa Encerrado       *\n");
        verificador_menu_inicial = 0;

    case 1: //Menu Cadastro        
        menu_cadastro();
    
    case 2: // Menu Relatórios
        menu_relatorio();
    
    default:
        printf("\n***** Opção Inválida! ****\n");
        break;
    }

}


//   Menu de Cadastros
int menu_cadastro(void){
    int opcao_cadastro;
    int opcao_cadastro_aluno, opcao_cadastro_professor, opcao_cadastro_disciplina;
    printf("\n****************************\n");
    printf(  "*      Menu Cadastro       *");
    printf("\n****************************\n");
    printf("Digite a opção desejada.\n");
    printf("0 - Retornar ao Menu Anterior.\n");
    printf("1 - Cadastro de Aluno.\n");
    printf("2 - Cadastro de Professor.\n");
    printf("3 - Cadastro de Disciplina.\n");
    printf("4 - Matricular Aluno.\n>>> ");
    scanf("%d", &opcao_cadastro);

    switch (opcao_cadastro){
    case 0: //Retornar ao Menu Anterior.
        menu_inicial();

    case 1: //Cadastro de Aluno.
        printf("\n****************************\n");
        printf(  "*   Menu Cadastro Aluno    *");
        printf("\n****************************\n");
        printf("Digite a opção desejada.\n");
        printf("0 - Retornar ao Menu Anterior.\n");
        printf("1 - Cadastrar Novo Aluno.\n");
        printf("2 - Excluir Aluno.\n");
        printf("3 - Alterar Aluno.\n>>> ");
        scanf("%d", &opcao_cadastro_aluno);

        switch (opcao_cadastro_aluno){
        case 0: // Retornar ao Menu Anterior
            menu_cadastro();    

        case 1: // Cadastrar Novo Aluno         
            do
            {   
                cadastrar_novamente = cadastro_pessoa(opcao_cadastro, cadastrar_novamente);
                
            } while (cadastrar_novamente == 1);
            menu_inicial();
        
        case 2: // Excluir Aluno
            do 
            {
                excluir_novamente = excluir_pessoa(opcao_cadastro, excluir_novamente);
            } while (excluir_novamente == 1);
            menu_inicial();

        case 3: // Alterar Aluno
            do
            {
                atualizar_novamente = atualizar_pessoa(opcao_cadastro, atualizar_novamente);
            } while (atualizar_novamente == 1);         
            menu_inicial();
            
        }

    case 2: //Cadastro de Professor.
        printf("\n****************************\n");
        printf(  "* Menu Cadastro Professor  *");
        printf("\n****************************\n");
        printf("Digite a opção desejada.\n");
        printf("0 - Retornar ao Menu Anterior.\n");
        printf("1 - Cadastrar Novo Professor.\n");
        printf("2 - Excluir Professor.\n");
        printf("3 - Alterar Professor.\n>>> ");
        scanf("%d", &opcao_cadastro_professor);

        switch (opcao_cadastro_professor){
        case 0: // Retornar ao Menu Anterior
            menu_cadastro();    

        case 1: // Cadastrar Novo Professor       
            do
            {   
                cadastrar_novamente = cadastro_pessoa(opcao_cadastro, cadastrar_novamente);
                
            } while (cadastrar_novamente == 1);
            menu_inicial();

        case 2: // Excluir Professo
            do 
            {
                excluir_novamente = excluir_pessoa(opcao_cadastro, excluir_novamente);
            } while (excluir_novamente == 1);
            menu_inicial();
        
        case 3: // Alterar professor
            do
            {
                atualizar_novamente = atualizar_pessoa(opcao_cadastro, atualizar_novamente);
            } while (atualizar_novamente == 1);         
            menu_inicial();
        }

    case 3: //Cadastro de Disciplina.
        printf("\n****************************\n");
        printf(  "* Menu Cadastro Disciplina *");
        printf("\n****************************\n");
        printf("Digite a opção desejada.\n");
        printf("0 - Retornar ao Menu Anterior.\n");
        printf("1 - Cadastrar Nova Disciplina.\n");
        printf("2 - Excluir Disciplina.\n");
        printf("3 - Alterar Disciplina.\n >>>");
        scanf("%d", &opcao_cadastro_disciplina);

        switch (opcao_cadastro_disciplina){
        case 0: // Retornar ao Menu Anterior
            menu_cadastro();    

        case 1: // Cadastrar Nova Disciplina    
            do
            {   
                cadastrar_novamente = cadastro_disciplina(cadastrar_novamente);
                
            } while (cadastrar_novamente == 1);
            menu_inicial();

        case 2: // Excluir Disciplina
            menu_inicial();

        case 3: // Alterar Disciplina
            menu_inicial();
        }

          
        default:
            break;
    }
}


// Menu de Listas/Relatórios
int menu_relatorio(void){
    int opcao_relatorio;
    // int opcao_cadastro_aluno, opcao_cadastro_professor, opcao_cadastro_disciplina;
    printf("\n****************************\n");
    printf(  "*      Menu Relatorio      *");
    printf("\n****************************\n");
    printf("Digite a opção desejada.\n");
    printf("0  - Retornar ao Menu Anterior.\n");
    printf("1  - Listar Alunos.\n");
    printf("2  - Listar Professores.\n");
    printf("3  - Listar Disciplinas.\n");
    printf("4  - Listar Disciplinas Específica.\n");
    printf("5  - Listar Alunos por Sexo (M/F).\n");
    printf("6  - Listar Alunos Ordenados por Nome.\n");
    printf("7  - Listar Alunos Ordenados por Data de Nascimento.\n");
    printf("8  - Listar Professores por Sexo (M/F).\n");
    printf("9  - Listar Professores Ordenados por Nome.\n");
    printf("10 - Listar Professores Ordenados por Data de Nascimento.\n");
    printf("11 - Aniversariantes do Mês.\n");
    printf("12 - Buscar (Professor / Aluno) por Parte do Nome.\n");
    printf("13 - Lista de Alunos Matriculados em Menos de 3 Disciplinas.\n");
    printf("14 - Listar Disciplinas que Extrapolam 40 Vagas.\n>>> ");
    scanf("%d", &opcao_relatorio);

    switch (opcao_relatorio){
    case 0: // Retornar ao Menu Anterior.
        menu_inicial();

    case 1: // Listar Alunos
        lista_alunos();
        menu_relatorio();
    
    case 2: // Listar Professores
        lista_professores();
        menu_relatorio();
    
    case 3: // Listar Disciplinas
        lista_disciplinas();
        menu_relatorio();

    case 4: // Listar Disciplinas Específica
        
        menu_relatorio();

    case 5: // Listar Alunos por Sexo (M/F)
        
        menu_relatorio();

    case 6: //ordenar(opcao_relatorio);

        menu_relatorio();

    case 7: // Listar Alunos Ordenados por Data de Nascimento.
        
        menu_relatorio();

    case 8: // Listar Professores por Sexo (M/F)
        
        menu_relatorio();

    case 9: // Listar Professores Ordenados por Nome
        ordenar_pornome(opcao_relatorio);
        menu_relatorio();

    case 10: // Listar Professores Ordenados por Data de Nascimento
        
        menu_relatorio();

    case 11: // Aniversariantes do Mês
        
        menu_relatorio();

    case 12: // Buscar (Professor / Aluno) por Parte do Nome
        buscar_pessoa();
        menu_relatorio();

    case 13: // Lista de Alunos Matriculados em Menos de 3 Disciplinas
        
        menu_relatorio();

    case 14: // Listar Disciplinas que Extrapolam 40 Vagas
        
        menu_relatorio();

    default:
        break;
    }
}


//   Main Function 
int main(){

    while (verificador_menu_inicial == 1){
        menu_inicial();
               
    }
}
