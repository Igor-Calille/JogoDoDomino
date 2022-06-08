/*
    Contem a definição das estruturas, variáveis globais etc.
*/
# include <stdio.h>
# include <stdlib.h>
# include <time.h>

typedef struct    // Estrutura que representa a peça do dominó.
{ 
    int lado1, lado2; 
    char info;  // info = 'C': Peca na area de compra; info = 'M': Peca na mesa;
                // info = '1': Peca na posse do jogador 1; info = '2': Peca na posse do jogador 2 ou Peca na posse da maquina;
    int count;  // armazena a posição da peça
} peca;
typedef struct             // Estrutura que representa a mesa do dominó 
{
    int esquerda, direita; // Apresenta os lados da mesa em que as peças serão jogadas
    int info;              // Para saber se o local na matriz esta vazio ou se alguma peça foi alocada para o local(1-com peça; 2-sem peça)
} mesa;

typedef struct              // Estrutura usada para armazenar os dados do jogo  
{
    int arm_v;               // Armazena vez
    int arm_op;             // Armazena Selecop 
    char arm_nome;          // Armazena nome do jogo
} info_jogo;

info_jogo salva_v;          // Armazena as variáveis 

int vez;                   // Armazena a rodada do jogo 
int Selecop;               // Armazena a quantidade de jogadores 

peca Jogo[28];            // Matriz que será usada para armazenar as peças do jogo.
mesa Mesa[28];            // Matriz que será usada para representar a mesa no jogo.

FILE *fj;
FILE *fm;
FILE *fv;
