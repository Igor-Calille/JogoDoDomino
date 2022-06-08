/*
    Contem os menus e todas as interações com os usuarios.
*/
void Regras();                    // Apresenta as regras do jogo de domino
int  Apresenta_menu();  // Apresenta o menu com multiplas escolhas.
int JogarContra();      // Menu onde ao definido a quantidade de jogadores: (1 - Jogador X Maquina) (2-Jogador X Jogador)
int MenuJogada(char x);                // Menu que representa as opcoes do jogador

void clear();               //Funcão indentifica o sistema do usuário para a funcao de limpar a interface
void limparInterface();     //Funcão que limpa o terminal
void flush_in();            //funcão que limpa o buffer
void pause (float);         //Funcao que cria um delay entre os printf's,(Uma ideia de deixar o terminal com uma apresentacao melhor)

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>

void NomeDoDomino()
{

    printf("\n\n\n########   #######  ##     ## #### ##    ##  #######        ##     ##  ######  ##    ## ##     ## \n");
    pause (0.05);
    printf("##     ## ##     ## ###   ###  ##  ###   ## ##     ##       ##     ## ##    ## ##   ##  ###   ### \n");
    pause (0.05);
    printf("##     ## ##     ## #### ####  ##  ####  ## ##     ##       ##     ## ##       ##  ##   #### #### \n");
    pause (0.05);
    printf("##     ## ##     ## ## ### ##  ##  ## ## ## ##     ##       ######### ##       #####    ## ### ## \n");
    pause (0.05);
    printf("##     ## ##     ## ##     ##  ##  ##  #### ##     ##       ##     ## ##       ##  ##   ##     ## \n");
    pause (0.05);
    printf("##     ## ##     ## ##     ##  ##  ##   ### ##     ##       ##     ## ##    ## ##   ##  ##     ## \n");
    pause (0.05);
    printf("########   #######  ##     ## #### ##    ##  #######        ##     ##  ######  ##    ## ##     ## \n");
    pause (0.05);
}

void clear()    //Funcão indentifica o sistema do usuário para a funcao de limpar a interface
{
    #if defined(__linux__) || defined(__unix__) || defined(__APPLE__)
        system("clear");
    #endif

    #if defined(_WIN32) || defined(_WIN64)
        system("cls");
    #endif
}

void pause (float delay1) //Funcao que cria um delay entre os printf's,(Uma ideia de deixar o terminal com uma apresentacao melhor)
{

   if (delay1<0.001) return; // pode ser ajustado e/ou evita-se valores negativos.

   float inst1=0, inst2=0;

   inst1 = (float)clock()/(float)CLOCKS_PER_SEC;

   while (inst2-inst1<delay1) inst2 = (float)clock()/(float)CLOCKS_PER_SEC;

   return;

}

void flush_in()     //funcão que limpa o buffer
{
    char op;
    while ((op = fgetc(stdin)) != EOF && op != '\n')
    {
    };
    printf("\r");
}

void limparInterface()  //Funcão que limpa o terminal
{ 
    char op;
    printf("\n\n----------------Pressione <ENTER> para continuar----------------");
    getchar();
    flush_in();
    clear();
}

int Apresenta_menu() 
{
    int SelecJ;
    int opcao;
    pause (0.05); //Funcao que cria um delay de 0.05 segundos entre os printf's,(Uma ideia de deixar o terminal com uma apresentacao melhor)
    printf("\n\n---------------------------------------------------\n\tMENU Inicial\n"); 
    pause (0.05);
    printf("1- Iniciar um novo jogo\n");
    pause (0.05);
    printf("2- Continuar a jogar\n");
    pause (0.05);
    printf("3- Salvar Jogo\n");
    pause (0.05);
    printf("4- Carregar jogo\n");
    pause (0.05);
    printf("5- Regras do jogo\n");
    pause (0.05);
    printf("6- SAIDA\n");  
    pause (0.05);
    printf("\n---------------------------------------------------\n");
    pause (0.05);
    printf("\nEscolha uma das opcoes seguintes (digite o numero da opcao): ");
    pause (0.05);
    scanf("%d", &SelecJ);
    opcao = SelecJ;
    limparInterface();

    return opcao;
}

void Regras() 
{
    printf("\n\n----------------Regras do jogo----------------\n"); 
    pause (0.05);
    printf("1- O conjunto eh formado  por  28  pecas retangulares com combinacoes possiveis de numeros que vao de 0 a 6.\n"); 
    pause (0.05);
    printf("2- Cada jogador comeca com sete pecas.\n"); 
    pause (0.05);
    printf("3- O jogador pode comprar sempre que precisar de uma peca para poder jogar.\n"); 
    pause (0.05);
    printf("4- Inicia-se o jogador que tiver a peca  com  os  numeros  repetidos  mais  altos,  ou  seja, [6|6], [5|5]  e  assim sucessivamente.\n"); 
    pause (0.05);
    printf("5- Cada jogador, no seu turno, deve colocar uma das suas pecas em uma das 2 extremidades abertas, de forma que os pontos de um dos lados coincidam com os pontos da extremidade onde esta  sendo  colocada.\n"); 
    pause (0.05);
    printf("6- Se um jogador nao puder jogar, ele deve comprar do monte tantas pecas como forem necessarias. Se nao houver pecas no monte, passara o turno ao seguinte jogador.\n\n");
    pause (0.05);
    printf("7- A partida continua com os jogadores colocando suas pecas sobre a mesa ate que se apresente alguma das seguintes situacoes:\n   - Quando um jogador coloca sua ultima pedra na mesa, essa acao eh chamada de bater.Quando joga-se sozinho, o jogador que ganhou a partida soma os pontos de todos os seus adversarios.\n   -Existem casos onde nenhum dos jogadores pode continuar a partida. Isto ocorre quando o numero das extremidades saiu 7 vezes antes. Nesse momento se diz que a partida esta fechada. Os jogadores contarao os pontos das pedras que ficaram; o jogador com menos pontos vencem e somam-se os pontos da maneira habitual.");
    pause (0.05);
    limparInterface();
}

int JogarContra()
{
    int QtdJogadores;
    int opcao;
    do
    {
        printf("\n\n-----------------------------------Escolha contra quem ira jogar-----------------------------------\n1- Jogar contra a maquina    2- Jogar contra o jogador\n Sua opcao: ");
        scanf("%d", &QtdJogadores);
        printf("\n");

        if (QtdJogadores != 1 && QtdJogadores != 2)
            printf("Erro! Digite novamente\n");

        else
            printf("Ok, vamos jogar!\n");
    } while (QtdJogadores < 1 || QtdJogadores > 2);
    limparInterface();

    opcao = QtdJogadores;

    return opcao;
}

int MenuJogada(char x)
{

   int opcao, SelecJ;
   do
    {
        printf("\n\n-----------------------------------Vez do jogador #%c-----------------------------------\n",x); // Apresentada opçoes para o jogador
        pause (0.05);
        printf("1- Mesa\n");
        pause (0.05);
        printf("2- Ver suas pecas\n");
        pause (0.05);
        printf("3- Comprar peca\n");
        pause (0.05);
        printf("4- Jogar\n");
        pause (0.05);
        printf("5- Voltar ao menu principal\n");
        pause (0.05);
        printf("\nEscolha uma das opcoes seguintes (digite o numero da opcao): ");
        scanf("%d", &SelecJ);
        opcao = SelecJ;

    }while(SelecJ > 5); 
    limparInterface();

    return opcao;          
}
