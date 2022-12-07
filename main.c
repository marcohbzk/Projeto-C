#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <time.h>
#include <locale.h>
#include <wchar.h>

//*Declarar Constantes*

#define MAXIMO_ESCOLAS 5
#define MAXIMO_UTILIZADORES 200
#define MAXIMO_TRANSACOES 5000
#define MAXIMO_CARACTERES 80

//*Declara��o Fun��es*

//Menu
void menu_opcoes(int numero_escolas,int numero_utilizadores, int numero_transacoes);
void func_Submenu();

//Escola
void func_Registar_Escola(numero_escolas);
void func_Mostrar_Escola(int numero_escolas);
int func_Quantidade_Escolas();

//Utilizadores
void func_Registar_Utilizadores(numero_utilizadores);
void func_Mostrar_Utilizadores(int numero_utilizadores);
int func_Quantidade_Utilizadores();

//Transa��es
void func_Registar_Transacoes(numero_transacoes);
void func_Mostrar_Transacoes(int numero_transacoes);
int func_Quantidade_Transacoes();
int func_Total_Transacoes(int numero_transacoes);
int func_Percentagem_Transacoes(int numero_transacoes);

//Ficheiros
void func_Validacao_Ficheiro(arq);

//*Typedef Structs*

typedef struct escola // Cria uma STRUCT para armazenar os dados da escola
{
    int escola_id;
    char nome[MAXIMO_CARACTERES];
    char abreviatura[MAXIMO_CARACTERES];
    int campus;
    char localidade[MAXIMO_CARACTERES];
}   escola;
//
typedef struct utilizador // Cria uma STRUCT para armazenar os dados do utilizador
{
    int utilizador_id;
    int escola_id;
    char nome[MAXIMO_CARACTERES];
    int nif;
    char tipo_utilizador[MAXIMO_CARACTERES]; //(Estudante, Docente, Funcion�rio)
    char email[MAXIMO_CARACTERES];
    float saldo;
}   utilizador;
//
typedef struct transacao // Cria uma STRUCT para armazenar os dados da transacao
{
    int transacao_id;
    int utilizador_id;
    int escola_id;
    char tipo_transacao[MAXIMO_CARACTERES]; //(Carregamento, Pagamento)
    float valor_transacao;
    char data[MAXIMO_CARACTERES]; //Data do Pagamento
    char hora[MAXIMO_CARACTERES]; //Hora:Minutos:Segundos da Transa��o
}   transacao;

    escola arr_escola[MAXIMO_ESCOLAS];
    utilizador arr_utilizador[MAXIMO_UTILIZADORES];
    transacao arr_transacao[MAXIMO_TRANSACOES];

//*Main*
int main()
{
    setlocale(LC_ALL,"Portuguese");
    int numero_escolas;
    int numero_utilizadores;
    int numero_transacoes;
    menu_opcoes(numero_escolas, numero_utilizadores, numero_transacoes);
    return 0;
}

//*Menu*
void menu_opcoes(int numero_escolas,int numero_utilizadores, int numero_transacoes)
{
	char escolha;

	do
	{
		func_Submenu();
		printf("\n Op��o ---> ");
		scanf(" %c", &escolha);
		system("cls || clear");
		getchar();

		switch(escolha)
		{
			case '1':
			    numero_escolas = func_Quantidade_Escolas();
			    func_Registar_Escola(numero_escolas);
				break;
            case '2':
                func_Mostrar_Escola(numero_escolas);
				break;
			case '3':
			    numero_utilizadores = func_Quantidade_Utilizadores();
                func_Registar_Utilizadores(numero_utilizadores);
				break;
            case '4':
                func_Mostrar_Utilizadores(numero_utilizadores);
                break;
            case '5':
                numero_transacoes = func_Quantidade_Transacoes();
                func_Registar_Transacoes(numero_transacoes);
                break;
            case '6':
                func_Mostrar_Transacoes(numero_transacoes);
                break;
            case '7':
                func_Total_Transacoes(numero_transacoes);
                break;
            case '8':
                func_Percentagem_Transacoes(numero_transacoes);
                break;
			case '9': printf("A encerrar o programa! Prima qualquer bot�o para sair.\n");
				exit(0);
				break;
			default: printf("\n\tEscolha inv�lida!\n");
				break;
		}
	} while (escolha != 9);
}

//Fun��o para registar os dados das escolas
void func_Registar_Escola(numero_escolas)
{
    FILE * arq;
    arq = func_Validacao_Ficheiro;
    arq = fopen("Dados_Escolas.bin", "wb");

    for(int i = 0; i < numero_escolas; i++ )
    {
        printf("\nColoque os detalhes da escola: %d\n\n", i+1);

        printf("Insira o identificador da escola: (ESECS-1,ESTG-2,ESS-3,ESAD-4,ESTM-5)\n");
        scanf("%d", &arr_escola[i].escola_id);
        if(arr_escola[i].escola_id < 1 || arr_escola[i].escola_id > 5)
        {
            do
            {
                printf("Identificador tem de ser entre 1 e 5\n");

                printf("\nInsira o identificador da escola: (ESECS-1,ESTG-2,ESS-3,ESAD-4,ESTM-5)\n");
                scanf("%d", &arr_escola[i].escola_id);

            }while(arr_escola[i].escola_id < 1 || arr_escola[i].escola_id > 5);
        }
        getchar();
        printf("Insira o nome da escola: \n");
        fgets(arr_escola[i].nome,MAXIMO_CARACTERES,stdin);
        arr_escola[i].nome[strlen(arr_escola[i].nome)-1] = '\0';

        printf("Insira a abreaviatura da escola: (ESECS,ESTG,ESS,ESAD,ESTM)\n");
        fgets(arr_escola[i].abreviatura,MAXIMO_CARACTERES,stdin);
        arr_escola[i].abreviatura[strlen(arr_escola[i].abreviatura)-1] = '\0';

        printf("Insira o campus da escola: (ESECS-1,ESTG-2,ESS-2,ESAD-3,ESTM-4)\n");
        scanf("%d", &arr_escola[i].campus);
        if(arr_escola[i].campus < 1 || arr_escola[i].campus > 4)
        {
            do
            {
                printf("Campus da escola tem de ser entre 1 e 4\n");

                printf("Insira o campus da escola: (ESECS-1,ESTG-2,ESS-2,ESAD-3,ESTM-4)\n");
                scanf("%d", &arr_escola[i].campus);

            }while(arr_escola[i].campus < 1 || arr_escola[i].campus > 4);
        }
        getchar();

        printf("Insira a localidade da escola: (ESECS/ESTG/ESS-Leiria, ESAD-Caldas da Rainha, ESTM-Peniche)\n");
        fgets(arr_escola[i].localidade,MAXIMO_CARACTERES,stdin);
        arr_escola[i].localidade[strlen(arr_escola[i].localidade)-1] = '\0';

        char result[MAXIMO_CARACTERES];
        fprintf(arq, "ID Escola\tCampus\tLocalidade\tAbreviatura Escola\tNome Escola\t\n");
        for(int i = 0;i < numero_escolas;i++)
        {
            result[i] = fprintf(arq,"%d\t\t\t%d\t\t%s\t\t\t%s\t\t\t%s\t\n",arr_escola[i].escola_id,
                arr_escola[i].campus,arr_escola[i].localidade,arr_escola[i].abreviatura,arr_escola[i].nome);
        }
        fclose(arq);
    }

}
//Fun��o para apresentar dados das escolas
void func_Mostrar_Escola(int numero_escolas)
{
    printf("\nEscola(Id)\tNome\t\t\t\t\tAbreviatura\tCampus\tLocalidade\n");
    for(int i = 0; i < numero_escolas; i++ )
    {
        printf("%d\t\t%s\t%s\t\t%d\t%s\n", arr_escola[i].escola_id, arr_escola[i].nome, arr_escola[i].abreviatura,
                arr_escola[i].campus, arr_escola[i].localidade);
    }
}
//Fun��o indicar o numero de escolas que pretender registar
int func_Quantidade_Escolas()
{
    int numero_escolas;

    printf("\nIndique o n�mero de escolas que pretende registar (M�ximo � 5): ");
    scanf("%d" ,&numero_escolas);

    if(numero_escolas > MAXIMO_ESCOLAS)
    {
        printf("\n\tERRO: O limite de escolas � 5.\n");
        return -1; //Volta para o menu.
    }
    else if(numero_escolas < 0)
    {
        printf("\n\tERRO: O n�mero de escolas n�o pode ser negativo. Tente novamente.\n");
    }
    else
    {
        return numero_escolas;
    }
}
//Fun��o para registar os dados dos utilizadores
void func_Registar_Utilizadores(numero_utilizadores)
{
    int i = 0;

    for(int i = 0; i < numero_utilizadores; i++ )
    {
        printf("\nColoque os detalhes do utilizador %d\n\n", i+1);

        printf("Insira o identificador do utilizador: \n");
        scanf("%d", &arr_utilizador[i].utilizador_id);
        getchar();

        printf("Insira o identificador da escola a qual quer registar o utilizador: (ESECS-1,ESTG-2,ESS-3,ESAD-4,ESTM-5)\n");
        scanf("%d", &arr_utilizador[i].escola_id);
        if(arr_escola[i].escola_id < 1 || arr_escola[i].escola_id > 5)
        {
            do
            {
                printf("Identificador tem de ser entre 1 e 5\n");

                printf("\nInsira o identificador da escola: (ESECS-1,ESTG-2,ESS-3,ESAD-4,ESTM-5)\n");
                scanf("%d", &arr_escola[i].escola_id);

            }while(arr_escola[i].escola_id < 1 || arr_escola[i].escola_id > 5);
        }
        getchar();

        printf("Insira o nome do utilizador: \n");
        fgets(arr_utilizador[i].nome,MAXIMO_CARACTERES,stdin);
        arr_utilizador[i].nome[strlen(arr_utilizador[i].nome)-1] = '\0';

        printf("Insira o nif do utilizador: \n");
        scanf("%d", &arr_utilizador[i].nif);

        if(sizeof arr_utilizador[i].nif != 9)
        {
            printf("Nif tem de ser 9\n");
            printf("Insira o nif do utilizador: \n");
            scanf("%d", &arr_utilizador[i].nif);
            i++;
        }
        getchar();

        printf("Insira o tipo de utilizador: (Estudante, Docente, Funcion�rio)\n");
        fgets(arr_utilizador[i].tipo_utilizador,MAXIMO_CARACTERES,stdin);
        arr_utilizador[i].tipo_utilizador[strlen(arr_utilizador[i].tipo_utilizador)-1] = '\0';

        printf("Insira o email do utilizador: \n");
        fgets(arr_utilizador[i].email,MAXIMO_CARACTERES,stdin);
        arr_utilizador[i].email[strlen(arr_utilizador[i].email)-1] = '\0';

        printf("Insira o saldo do utilizador: \n");
        scanf("%f", &arr_utilizador[i].saldo);
        if(arr_utilizador[i].saldo < 0)
        {
            do
            {
                printf("\nSaldo nao pode ser negativo\n");

                printf("Insira o saldo do utilizador: \n");
                scanf("%f", &arr_utilizador[i].saldo);

            }while(arr_utilizador[i].saldo < 0);
        }
    }
}
//Fun��o para apresentar dados dos utilizadores
void func_Mostrar_Utilizadores(int numero_utilizadores)
{
    printf("\nUtilizador(Id)\tEscola(Id)\tNome\t\t\t\tNIF\t\tTipo\t\tEmail\t\t\tSaldo\n");
    for(int i = 0; i < numero_utilizadores; i++)
    {
        printf("\n%d\t\t%d\t\t%s\t%d\t%s\t%s\t%0.2f\n", arr_utilizador[i].utilizador_id, arr_utilizador[i].escola_id,
               arr_utilizador[i].nome, arr_utilizador[i].nif, arr_utilizador[i].tipo_utilizador,arr_utilizador[i].email, arr_utilizador[i].saldo);
    }
}
//Fun��o indicar o numero de utilizadores que pretender registar
int func_Quantidade_Utilizadores()
{
    int numero_utilizadores;

    printf("\nIndique o n�mero de utilizadores que pretende registar: ");
    scanf("%d" ,&numero_utilizadores);

    if(numero_utilizadores > MAXIMO_UTILIZADORES)
    {
        printf("\n\tERRO: O limite de utilizadores � 200.\n");
        return -1; //Isto volta atr�s para o menu.
    }
    else if(numero_utilizadores < 0)
    {
        printf("\n\tERRO: O n�mero de utilizadores n�o pode ser negativo. Tente novamente.\n");
    }
    else
    {
        return numero_utilizadores;
    }
}
//Fun��o para registar os dados das transa��es
void func_Registar_Transacoes(numero_transacoes)
{
    for(int i = 0; i < numero_transacoes; i++ )
    {
        printf("\nColoque os detalhes da transa��o %d\n\n", i+1);

        printf("Insira o identificador da transa��o: \n");
        scanf("%d", &arr_transacao[i].transacao_id);
        getchar();

        printf("Insira o identificador do utilizador: \n");
        scanf("%d", &arr_transacao[i].utilizador_id);
        getchar();

        printf("Insira o identificador da escola: (ESECS-1,ESTG-2,ESS-3,ESAD-4,ESTM-5)\n");
        scanf("%d", &arr_transacao[i].escola_id);
        if(arr_escola[i].escola_id < 1 || arr_escola[i].escola_id > 5)
        {
            do
            {
                printf("Identificador tem de ser entre 1 e 5\n");

                printf("\nInsira o identificador da escola: (ESECS-1,ESTG-2,ESS-3,ESAD-4,ESTM-5)\n");
                scanf("%d", &arr_escola[i].escola_id);

            }while(arr_escola[i].escola_id < 1 || arr_escola[i].escola_id > 5);
        }
        getchar();

        printf("Insira o tipo de transa��o: (Carregamento, Pagamento)\n");
        fgets(arr_transacao[i].tipo_transacao,MAXIMO_CARACTERES,stdin);
        arr_transacao[i].tipo_transacao[strlen(arr_transacao[i].tipo_transacao)-1] = '\0';

        printf("Insira o valor da transa��o: \n");
        scanf("%f", &arr_transacao[i].valor_transacao);
        if(arr_transacao[i].valor_transacao < 0)
        {
            do
            {
                printf("\nO valor da transacao nao pode ser negativo\n");

                printf("Insira o valor da transa��o: \n");
                scanf("%f", &arr_transacao[i].valor_transacao);

            }while(arr_transacao[i].valor_transacao < 0);
        }
        getchar();

        printf("Insira a data: \n");
        fgets(arr_transacao[i].data,MAXIMO_CARACTERES,stdin);
        arr_transacao[i].data[strlen(arr_transacao[i].data)-1] = '\0';

        printf("Insira as horas: \n");
        fgets(arr_transacao[i].hora,MAXIMO_CARACTERES,stdin);
        arr_transacao[i].hora[strlen(arr_transacao[i].hora)-1] = '\0';
    }
}
//Fun��o para apresentar dados das transa��es
void func_Mostrar_Transacoes(int numero_transacoes)
{
    printf("\nTransa��o(Id)\tUtilizador(Id)\tTipo\t\tValor\tData\t\tHoras\n");
    for(int i = 0; i < numero_transacoes; i++)
    {
        printf("\n%d\t\t%d\t\t%s\t%0.2f\t%s\t%s\n", arr_transacao[i].transacao_id, arr_transacao[i].utilizador_id,
               arr_transacao[i].tipo_transacao, arr_transacao[i].valor_transacao, arr_transacao[i].data,arr_transacao[i].hora);
    }
}
//Fun��o indicar o numero de transa��es que pretender registar
int func_Quantidade_Transacoes()
{
    int numero_transacoes;

    printf("\nIndique o n�mero de transa��es que pretende registar: ");
    scanf("%d" ,&numero_transacoes);

    if(numero_transacoes > MAXIMO_TRANSACOES)
    {
        printf("\n\tERRO: O limite de transa��es � 5000.\n");
        return -1; //Isto volta atr�s para o menu.
    }
    else if(numero_transacoes < 0)
    {
        printf("\n\tERRO: O n�mero de transa��es n�o pode ser negativo. Tente novamente.\n");
    }
    else
    {
        return numero_transacoes;
    }
}
//Fun��o para fazer a fatura��o por escola
int func_Total_Transacoes(int numero_transacoes)
{
    int totalESECS = 0; int totalESTG = 0; int totalESS = 0; int totalESAD = 0; int totalESTM = 0; int totalEscolas = 0;
    for(int i = 0; i < numero_transacoes; i++)
    {
        if(arr_transacao[i].escola_id == 1)
        {
            totalESECS += arr_transacao[i].valor_transacao;
        }
        else if(arr_transacao[i].escola_id == 2)
        {
            totalESTG += arr_transacao[i].valor_transacao;
        }
        else if(arr_transacao[i].escola_id == 3)
        {
            totalESS += arr_transacao[i].valor_transacao;
        }
        else if(arr_transacao[i].escola_id == 4)
        {
            totalESAD += arr_transacao[i].valor_transacao;
        }
        else if(arr_transacao[i].escola_id == 5)
        {
            totalESTM += arr_transacao[i].valor_transacao;
        }
    }
    printf("Total de Fatura��o pela ESECS: %d \n",totalESECS);
    printf("Total de Fatura��o pela ESTG: %d \n",totalESTG);
    printf("Total de Fatura��o pela ESS: %d \n",totalESS);
    printf("Total de Fatura��o pela ESAD: %d \n",totalESAD);
    printf("Total de Fatura��o pela ESTM: %d \n",totalESTM);
}
//Fun��o para fazer a percentagem de transa��es(Pagamentos) por escola
int func_Percentagem_Transacoes(int numero_transacoes)
{
    float totalESECS = 0, totalESTG = 0, totalESS = 0, totalESAD = 0, totalESTM = 0, totalEscolas = 0;
    for(int i = 0; i < numero_transacoes; i++)
    {
        if(arr_transacao[i].escola_id == 1)
        {
            totalESECS += arr_transacao[i].valor_transacao;
        }
        else if(arr_transacao[i].escola_id == 2)
        {
            totalESTG += arr_transacao[i].valor_transacao;
        }
        else if(arr_transacao[i].escola_id == 3)
        {
            totalESS += arr_transacao[i].valor_transacao;
        }
        else if(arr_transacao[i].escola_id == 4)
        {
            totalESAD += arr_transacao[i].valor_transacao;
        }
        else if(arr_transacao[i].escola_id == 5)
        {
            totalESTM += arr_transacao[i].valor_transacao;
        }
    }

    float totalPercentagem = totalESECS + totalESTG + totalESS + totalESTM + totalESAD;

    float percentagemESECS = (totalESECS / totalPercentagem) * 100;
    float percentagemESTG = (totalESTG / totalPercentagem) * 100;
    float percentagemESS = (totalESS / totalPercentagem) * 100;
    float percentagemESAD = (totalESAD / totalPercentagem) * 100;
    float percentagemESTM = (totalESTM / totalPercentagem) * 100;

    printf("Percentagem de Transa��es pela ESECS: %0.0f%% \n",percentagemESECS);
    printf("Percentagem de Transa��es pela ESTG: %0.0f%% \n",percentagemESTG);
    printf("Percentagem de Transa��es pela ESS: %0.0f%% \n",percentagemESS);
    printf("Percentagem de Transa��es pela ESAD: %0.0f%% \n",percentagemESAD);
    printf("Percentagem de Transa��es pela ESTM: %0.0f%% \n",percentagemESTM);

}
//Fun��o para fazer print de linhas do menu
void func_Submenu ()
{
    printf("\n\t   * Menu *\n\n");
    printf(" 1. Registar Dados da Escola\n");
    printf(" 2. Mostrar Dados da Escola\n");
    printf(" 3. Registar Dados dos Utilizadores\n");
    printf(" 4. Mostrar Dados dos Utilizadores\n");
    printf(" 5. Registar Dados de Transa��es\n");
    printf(" 6. Mostrar Dados de Transa��es\n");
    printf(" 7. Mostrar Total de Fatura��o\n");
    printf(" 8. Mostrar Percentagem de Transa��es\n");
    printf(" 9. Sair (Guardar)\n");
}
//
void func_Validacao_Ficheiro(arq)
{
    if (arq == NULL)
    {
        printf("Problemas na criacao do arquivo\n");
        return;
    }
}
