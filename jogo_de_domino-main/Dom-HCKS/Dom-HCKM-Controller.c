/*
    Contem a parte lógica do processamento
*/
# include "Dom-HCKM-Model.c"
# include "Dom-HCKM-View.c"

// ------------------------------Funções para a gravação do jogo------------------------------
void Salvajogo(); // Função que armazena as informações jogo
void Carregajogo(); // Função que carrega as informações do jogo
// ------------------------------Funções para o jogo de domino--------------------------------
void Iniciajogo(int vez, int Selecop);                      // Função que irá iniciar o jogo.
int Maiorpeca();                        // Função que  irá buscar a maior peça entre os jogadores, para o início do jogo.
void Comprapecas(peca Jogo[], char i, int Selecop);  // Função que irá fazer o jogador comprar peça(s)
void Jogavoce(peca Jogo[], char x, int Selecop);     // Jogada do jogador 1 ou 2
void verificaFim(peca Jogo[], mesa Mesa[]);          // Função que verifica se o jogo foi finalizado
int contarMao(peca Jogo[],char i);      // Função que retorna o total de peças da mão do jogador
int pontuacao(peca Jogo[],char i);      // Função que verifica a potuação das peças no caso de empate
void Jogacomput(peca Jogo[], int Selecop);           // Função do comportamento do computador
// ------------------------------Funções das peças-------------------------------------------
void Zeramesa(mesa Mesa[]);
void Ordenapecas(peca Jogo[]);            // Função que ordena as peças do jogo
void Embaralhapecas(peca Jogo[]);         // Função que irá embaralhar as peças para a partida do jogo.
void Mostrapecasmesa(mesa Mesa[]);        // Função que irá mostrar as peças do jogo.
void Mostrapecas(peca Jogo[], char i);    // Função que irá exibir as peças para o usuário.
void Distribuipecas();                    // Função que irá distribuir as peças aos jogadores.
int pecavalida(peca Jogo[], int num, char x); // Verifica se a peça colocada tem a mesma pontuação das peças das extremidades da mesa
int pecavalidaMaquina(peca Jogo[]);        // Verifica se a peça colocada tem a mesma pontuação das peças das extremidades da mesa para a máquina
void contar(peca Jogo[], char i);         // Função que separa as peças para o jogador comprar ou jogar
int contarMesa(mesa Mesa[]);              // Função que verifica as peças da mesa
void Inverter(peca Jogo[],char x, int z); // Função que inverte o sentido da peça 
// ------------------------------Funções para o menu----------------------------------------
void Seleciona_menu();


void Mostrapecasmesa(mesa Mesa[])           // Irá exibir as peças que estão na mesa para o usuário.
{
    int a;
    {
        printf("\n\n--------------------------------------Mesa--------------------------------------\n\n");
        for (a = 0; a < 28; a++)            // Loop que irá percorrer pela matriz.
        {    
            if(Mesa[a].info == 1)   //apenas imprime a parte da matriz com as peças
            {
                printf("[%d|", Mesa[a].esquerda);
                printf("%d]", Mesa[a].direita);
            }
        }
        printf("\n");
    }
}

void Mostrapecas(peca Jogo[], char i)       // Irá exibir as peças que estão na posse do usuário ou na area de compra.
{
    int a, x=0;
    printf("\n\n--------------------------------------Pecas--------------------------------------\n\n");
    for(a=0; a<28; a++) // Loop que irá percorrer pela matriz.
    {
        if(Jogo[a].info == i)
        {
            x++;
            printf("%d.[%d|", x, Jogo[a].lado1);
            printf("%d] ", Jogo[a].lado2);
        }
    }
    
}

void Embaralhapecas(peca Jogo[])
{
    int ale, a;
    peca z;
    srand(time(NULL));           // Criação de seed para cada embaralhamento ser unico.
    for(a=0; a<28;a++)
    {
        ale = rand()%27;
        z = Jogo[a];
        Jogo[a] = Jogo[ale];
        Jogo[ale] = z;
    }
    //printf("\n----------------As pecas foram embaralhadas.----------------\n\n");
}
void Zeramesa(mesa Mesa[])
{
    int a;
    for(a=0; a<28; a++)
    {
        Mesa[a].esquerda = 0;
        Mesa[a].direita = 0;
        Mesa[a].info = 0;
    }
}

void Ordenapecas(peca Jogo[])   // A função além de ordernar as peças, também cria as 28 peças.
{
    int a, j , i , p;
    p=0;
    for(i=0; i<7; i++)
    {
        for(j=i; j<7; j++)
        {
            Jogo[p].lado1 = i;
            Jogo[p].lado2 = j;
            Jogo[p].info = 'C';
            p++;
        }
    }
}

void Seleciona_menu()
{
    int selecJ;
    //char Nome[20], I[20] = "vazio";
    //Nome[20] =  I[20];
    do
    {   
        selecJ = Apresenta_menu();
        switch(selecJ)
        {
            case 1: //Inicia o jogo
                Ordenapecas(Jogo);
                Embaralhapecas(Jogo);
                Zeramesa(Mesa);
                Distribuipecas();
                vez = Maiorpeca();
                Selecop = JogarContra();
                Iniciajogo(vez,Selecop);
                break;
            case 2: //Continua o jogo
                Iniciajogo(vez,Selecop);
                break;
            case 3: //Salva o jogo
                salva_v.arm_op = Selecop;
                Salvajogo();
                break;
            case 4: //Carrega o jogo
                Carregajogo();
                Selecop = salva_v.arm_op;
                vez = salva_v.arm_v;
                break;
            case 5:
                Regras();
                //Regras do jogo
                break;
            case 6: 
            pause (0.05);
                printf("\n----------------Obrigado por jogar!----------------\n");
                exit(0);
            default:
                pause (0.05);
                printf("\n----------------Erro! Digite os numeros indicados!----------------\n");
                break;
        }
    }while(selecJ<6);
}

void Distribuipecas()
{
    int a;
    
    for(a=0; a<7;a++)           // 7 pecas pro jogador 1.
    {
        Jogo[a].info= '1';      // Peca sai da area de compra e vai pro jogador 1.
    }
    for(a=7; a<14;a++)          // 7 pecas pro jogador 2 ou para maquina.
    {
        Jogo[a].info= '2';      // Peca sai da area de compra e vai pro jogador 2.
    }
}

int Maiorpeca()
{
    int a, p;

        for(a=6; a>=0 ; a--)      // Loop para testar quem tem a peca maior para comecar (no formato seis-seis, cinco-cinco e assim por diante).
        {
            for(p=0; p<14; p++)   // Percorre as 7 pecas inicias dos jogadores ou da maquina.
            {
                if((Jogo[p].lado1== a) && (Jogo[p].lado2== a))
                {
                    Mesa[0].esquerda = Jogo[p].lado1;    // Coloca a primeira peça na mesa
                    Mesa[0].direita = Jogo[p].lado2;    // Coloca a primeira peça na mesa
                    Mesa[0].info = 1;
                    Jogo[p].info = 'M';
                    if(p<8)
                        return 2; // Se a maior peça for encontrada na mao do jogador 1, como ela foi colocada na mesa, a vez é transferido pro jogador 2
                    else if(p<15)
                        return 1; // Se a maior peça for encontrada na mao do jogador 2, como ela foi colocada na mesa, a vez é transferido pro jogador 1
                }
            }
            
        }
}

void Iniciajogo(int vez, int Selecop)
{
    int SelecMenu, ok, selecJ;
    char x;

    if(Selecop == 1)             // Jogador 1 Vs. Maquina
    {
        do
        {
            if(vez==1)            // Vez do jogador 1.
            {
                x = '1';   
                do
                {
                    SelecMenu = MenuJogada(x);
                    if(SelecMenu == 1)
                    {
                        Mostrapecasmesa(Mesa);
                        SelecMenu = 0;  //sair do if
                    }
                    if(SelecMenu == 2)
                    {
                        Mostrapecas(Jogo, x); 
                        SelecMenu = 0;  //sair do if 
                    }
                    if(SelecMenu == 3)
                    {   
                        Comprapecas(Jogo, x, Selecop);
                        SelecMenu = 0;  //sair do if
                    }
                    if(SelecMenu == 4)
                    {
                        Jogavoce(Jogo, x, Selecop);
                        verificaFim(Jogo, Mesa);
                        vez = 2; //passa a vez pro jogador 2
                        salva_v.arm_v = vez;    //A variavel armazena a vez para a opcao de salvar o jogo
                        SelecMenu = 0;  //sair do if 
                        limparInterface();           
                    }
                    if(SelecMenu == 5)  //volta ao menu inicial
                    {
                        break;
                    }
                    else if(SelecMenu > 5)
                    {
                        printf("\n\nDigite um numero valido\n");
                    }
                }while(SelecMenu>0 && vez == 1);
            }   
            else if(vez==2)      // Nesse caso, vez da maquina.
            {  
                SelecMenu = 0;  //apenas para permanecer no loop, já q a máquina n afaz a escolha de menu
                Jogacomput(Jogo, Selecop);
                verificaFim(Jogo, Mesa);
                vez = 1;   
                salva_v.arm_v = vez;    //A variavel armazena a vez para a opcao de salvar o jogo     
            }
        } while (SelecMenu < 5 );
        
    }       
    else if (Selecop == 2)           // Jogador 1 Vs. jogador 2.
    {
        do
        {
            if(vez==1)            // Vez do jogador 1. 
            {   
                x = '1';   
                do
                {
                    SelecMenu = MenuJogada(x);
                    if(SelecMenu == 1)
                    {
                        Mostrapecasmesa(Mesa);
                        SelecMenu = 0;  //sair do if
                    }
                    if(SelecMenu == 2)
                    {
                        Mostrapecas(Jogo, x); 
                        SelecMenu = 0;  //sair do if 
                    }
                    if(SelecMenu == 3)
                    {   
                        Comprapecas(Jogo, x, Selecop);
                        SelecMenu = 0;  //sair do if
                    }
                    if(SelecMenu == 4)
                    {
                        Jogavoce(Jogo, x, Selecop);
                        verificaFim(Jogo, Mesa);
                        vez = 2; //passa a vez pro jogador 2
                        salva_v.arm_v = vez;    //A variavel armazena a vez para a opcao de salvar o jogo
                        SelecMenu = 0;  //sair do if 
                        limparInterface();           
                    }
                    if(SelecMenu == 5)  //volta ao menu inicial
                    {
                        break;
                    }
                    else if(SelecMenu > 5)
                    {
                        printf("\n\nDigite um numero valido\n");
                    }
                }while(SelecMenu>0 && vez == 1);
            }
            else if(vez==2)      // Nesse caso, vez do jogador 2.
            {
                x = '2'; 
                do 
                { 
                    SelecMenu = MenuJogada(x);
                    if(SelecMenu == 1)
                    {
                        Mostrapecasmesa(Mesa);
                        SelecMenu = 0;  //sair do if
                    }
                    if(SelecMenu == 2)
                    {
                        Mostrapecas(Jogo,x);
                        SelecMenu = 0;  //sair do if  
                    }
                    if(SelecMenu == 3)
                    {   
                        Comprapecas(Jogo, x, Selecop);
                        SelecMenu = 0;  //sair do if
                    }
                    if(SelecMenu == 4)
                    {
                        Jogavoce(Jogo, x, Selecop);
                        verificaFim(Jogo, Mesa);
                        vez = 1; //passa a vez pro jogador 1
                        salva_v.arm_v = vez;    //A variavel armazena a vez para a opcao de salvar o jogo
                        SelecMenu = 0;  //sair do if   
                        limparInterface();       
                    }
                    if(SelecMenu == 5)  //volta ao menu inicial
                    {
                        break;
                    }
                    else if(SelecMenu > 5)
                    {
                        printf("\n\nDigite um numero valido\n");
                    }
                }while(SelecMenu<6 && vez == 2);
            }

        } while (SelecMenu < 5);
    }
}


void Comprapecas(peca Jogo[], char i, int Selecop)
{
    int a, bat = 0, test=0, op;
    char y, x = 'C';
    contar(Jogo, x);
    
    for(a=0; a<28; a++)
    {   
        
        if(Jogo[a].info == x && Jogo[a].count == 1)     //primeira peca da area de compra
        {
            Jogo[a].info = i;
            pause (0.05);
            printf("\n\n--------------------------------A peca [%d|%d] foi comprada--------------------------------\n", Jogo[a].lado1,Jogo[a].lado2);
            test = 1; //ainda existem peças  
        }
        
    }
    if(test == 0)   // não existe nunhuma peça na area de compra
    {
        pause (0.05);
        printf("\n--------------------------------As pecas acabaram--------------------------------\n");
        
        do
        {
            pause (0.05);
            printf("\nDeseja passar a vez?(1- Sim | 2- Nao)\n");
            scanf("%d",&op);
        } while (op<1 || op>2);
            
        
        if(op == 1)
        {
            
            if(i=='1' && Selecop == 2)
            {
                y = '2';
                pause (0.05);
                printf("\n\n-----------------------------------Vez do jogador #%c-----------------------------------\n",y); // Apresentada opçoes para o jogador
                Jogavoce(Jogo, y, Selecop); //passa a vez para o jogador 2
            }
            else if(i=='1' && Selecop == 1)
            {
                Jogacomput(Jogo, Selecop);
            }
            else if(i=='2')
            {
                y = '1';
                pause (0.05);
                printf("\n\n-----------------------------------Vez do jogador #%c-----------------------------------\n",y); // Apresentada opçoes para o jogador
                Jogavoce(Jogo, y, Selecop);//passa a vez para o jogador 1
            }
        }
        
        
    }

}

void Jogavoce(peca Jogo[], char x, int Selecop)               // Jogador 1 ou 2
{   
    int Fim = 0, quant;
    do
    {
        int lado;
        int num,esc, Bat, a;
        char y;
        Mostrapecasmesa(Mesa);
        contar(Jogo, x);
        Mostrapecas(Jogo, x); 
        pause (0.05);
        printf("\n\nDigite o numero da peca selecionada(0 para comprar uma peca): ");
        scanf("%d", &num);
        printf("\n");

        if(num == 0)
        {
            Comprapecas(Jogo, x, Selecop);
        }
        else if (num > 20 || num < 0)
        {
            printf("Erro digite o numero correto!");
        }
        else
        {
            Bat = pecavalida(Jogo, num, x);

            if(Bat == 1)   //peça valida colocada a esquerda
            {
                for(a=27; a>=0; a--)
                {
                    Mesa[a] = Mesa[a-1];
                
                }
                for(a=0; a<28;a++)
                {
                    if(Jogo[a].count == num && Jogo[a].info == x)
                    {
                        Mesa[0].esquerda = Jogo[a].lado1;     //troquei os lados pq estava imprimindo ao contrario
                        Mesa[0].direita = Jogo[a].lado2;
                        Mesa[0].info = 1;
                        Jogo[a].info = 'M';
                        Fim = 1;
                        pause (0.05);
                        printf("\n-Jogada feita, a peca do jogador %c foi colocada na esquerda\n\n", x);
                        printf("-------------------------------------------------------------------\n\n");
                    }
                }
            }
            else if (Bat == 2)
            {
                quant = contarMesa(Mesa);
                for(a=0; a<28;a++)
                {
                    if(Jogo[a].count == num && Jogo[a].info == x)
                    {
                
                        Mesa[quant].esquerda = Jogo[a].lado1;  
                        Mesa[quant].direita = Jogo[a].lado2;
                        Mesa[quant].info = 1;
                        Jogo[a].info = 'M';
                        Fim = 1;
                        pause (0.05);
                        printf("\n-Jogada feita, a a peca do jogador %c foi colocada na direita\n\n", x);
                        printf("-------------------------------------------------------------------\n\n");
                    }
                }
            }
        }
    
    }while( Fim == 0);
    
}

void Jogacomput(peca Jogo[], int Selecop)
{
    int  Bat, a, num=0, quant;
    char x = '2';

    do
    {
        contar(Jogo, x);
        quant = contarMesa(Mesa);
        for(a=0; a<28;a++)
        {
            if(Jogo[a].info == x)
            {
                if(Mesa[0].esquerda == Jogo[a].lado2)
                {
                    num = Jogo[a].count;
                }
                else if (Mesa[0].esquerda == Jogo[a].lado1)
                {
                    num = Jogo[a].count;
                }
                else if(Mesa[quant-1].direita == Jogo[a].lado1)
                {
                    num = Jogo[a].count;
                }
                else if(Mesa[quant-1].direita == Jogo[a].lado2)
                {
                    num = Jogo[a].count;
                }
            }

        }
        if(num == 0)
        {
            Comprapecas(Jogo, x, Selecop);
        }
        else
        {
            Bat = pecavalidaMaquina(Jogo);

            if(Bat == 1)   // peça valida colocada a esquerda
            {
                for(a=27; a>=0; a--)
                {
                    Mesa[a] = Mesa[a-1];

                }
                for(a=0; a<28;a++)
                {
                    if(Jogo[a].count == num && Jogo[a].info == x)
                    {
                        Mesa[0].esquerda = Jogo[a].lado1;    
                        Mesa[0].direita = Jogo[a].lado2;
                        Mesa[0].info = 1;
                        Jogo[a].info = 'M';
                        pause (0.05);
                        printf("\n-A maquina colocou a peca na esquerda\n\n");
                        printf("-------------------------------------------------------------------\n\n");
                    }
                }
            }
            else if (Bat == 2) // peça valida colocada a direita
            {
                quant = contarMesa(Mesa);
                for(a=0; a<28;a++)
                {
                    if(Jogo[a].count == num && Jogo[a].info == x)
                    {
                        Mesa[quant].esquerda = Jogo[a].lado1;
                        Mesa[quant].direita = Jogo[a].lado2;
                        Mesa[quant].info = 1;
                        Jogo[a].info = 'M';
                        pause (0.05);
                        printf("\n-A maquina colocou a peca na direita\n\n");
                        printf("-------------------------------------------------------------------\n\n");
                    }
                
                }    
            }
        }
    } while (num == 0);
    
}

void Inverter(peca Jogo[],char x, int z)
{
    int a;
    int y;
    
    for(a=0; a<28; a++)
    {
        if(Jogo[a].info == x && Jogo[a].count == z)
        {
               
            y = Jogo[a].lado1;
            Jogo[a].lado1 = Jogo[a].lado2;
            Jogo[a].lado2 = y;
            pause (0.05);
            printf("\n-A peca [%d|%d] foi invertida para [%d|%d]",Jogo[a].lado2, Jogo[a].lado1,Jogo[a].lado1, Jogo[a].lado2);
        }
    
    }    
}

int pecavalida(peca Jogo[], int num, char x)  // Verifica se a peça colocada tem a mesma pontuação das peças das extremidades da mesa
{
    int a, quant, lado;
    quant = contarMesa(Mesa);
    
        for(a=0; a<28;a++)
        {
            if(Jogo[a].count == num && Jogo[a].info == x)
            {
                if((Mesa[0].esquerda == Jogo[a].lado2 || Mesa[0].esquerda == Jogo[a].lado1) &&  (Mesa[quant-1].direita == Jogo[a].lado1 || Mesa[quant-1].direita == Jogo[a].lado2))
                {
                    pause (0.05);
                    printf("\nEscolha uma das opcoes:\n 1- Colocar a peca na esquerda\n 2- Colocar a peca na direita\nSua opcao: ");
                    scanf("%d", &lado);
                    printf("\n");
                    if(lado == 1)
                    {
                        if(Mesa[0].esquerda == Jogo[a].lado2)
                        {
                            pause (0.05);
                            printf("\n\n----------------------------INFORMACOES----------------------------");
                            return 1;   //1 para ser colocado na esquerda
                        }
                        else if (Mesa[0].esquerda == Jogo[a].lado1)
                        {
                            pause (0.05);
                            printf("\n\n----------------------------INFORMACOES----------------------------");
                            Inverter(Jogo, x, num);
                            return 1;   //1 para ser colocado na esquerda
                        }
                    }
                    else if(lado==2)
                    {
                        if(Mesa[quant-1].direita == Jogo[a].lado1)
                        {
                            pause (0.05);
                            printf("\n\n----------------------------INFORMACOES----------------------------");
                            return 2;   //2 para ser colocado na direita
                        }
                        else if(Mesa[quant-1].direita == Jogo[a].lado2)
                        {
                            pause (0.05);
                            printf("\n\n----------------------------INFORMACOES----------------------------");
                            Inverter(Jogo, x, num);
                            return 2;   //2 para ser colocado na direita
                        }
                    }
                    else
                    {
                        printf("Valor invalido"); // AINDA SERIA BOM FAZER UM LOOPING__________________________________________
                    }
                }
                else if(Mesa[0].esquerda == Jogo[a].lado2)
                {
                    pause (0.05);
                    printf("\n\n----------------------------INFORMACOES----------------------------");
                    return 1;   //1 para ser colocado na esquerda
                }
                else if (Mesa[0].esquerda == Jogo[a].lado1)
                {
                    pause (0.05);
                    printf("\n\n----------------------------INFORMACOES----------------------------");
                    Inverter(Jogo, x, num);
                    return 1;   //1 para ser colocado na esquerda
                }
                else if(Mesa[quant-1].direita == Jogo[a].lado1)
                {
                    pause (0.05);
                    printf("\n\n----------------------------INFORMACOES----------------------------");
                    return 2;
                }
                else if(Mesa[quant-1].direita == Jogo[a].lado2)
                {
                    pause (0.05);
                    printf("\n\n----------------------------INFORMACOES----------------------------");
                    Inverter(Jogo, x, num);
                    return 2;
                }
                else
                {
                    pause (0.05);
                    printf("\n\n----------------------------INFORMACOES----------------------------");
                    pause (0.05);
                    printf("\n-A peca [%d|%d] nao condiz com nenhum lado da mesa\n\n", Jogo[a].lado1, Jogo[a].lado2);
                    pause (0.05);
                    printf("-------------------------------------------------------------------\n\n");
                    return 0;
                }
            }
        }
}

int pecavalidaMaquina(peca Jogo[])  
{
    int a, quant, lado;
    int num;
    char x = '2';
    contar(Jogo, x);
    quant = contarMesa(Mesa);

    for(a=0; a<28;a++)
    {
        if(Jogo[a].info == x)
        {
            if(Mesa[0].esquerda == Jogo[a].lado2)
            {
                num = Jogo[a].count;
            }
            else if (Mesa[0].esquerda == Jogo[a].lado1)
            {
                num = Jogo[a].count;
            }
            else if(Mesa[quant-1].direita == Jogo[a].lado1)
            {
                num = Jogo[a].count;
            }
            else if(Mesa[quant-1].direita == Jogo[a].lado2)
            {
                num = Jogo[a].count;
            }
        }

    }
    for(a=0; a<28;a++)
    {
        if(Jogo[a].count == num && Jogo[a].info == x)
        {
            if(Mesa[0].esquerda == Jogo[a].lado2)
            {
                pause (0.05);
                printf("\n\n----------------------------INFORMACOES----------------------------");
                return 1;   //1 para ser colocado na esquerda
            }
            else if (Mesa[0].esquerda == Jogo[a].lado1)
            {
                pause (0.05);
                printf("\n\n----------------------------INFORMACOES----------------------------");
                Inverter(Jogo, x, num);
                return 1;   //1 para ser colocado na esquerda
            }
            else if(Mesa[quant-1].direita == Jogo[a].lado1)
            {
                pause (0.05);
                printf("\n\n----------------------------INFORMACOES----------------------------");
                return 2;
            }
            else if(Mesa[quant-1].direita == Jogo[a].lado2)
            {
                pause (0.05);
                printf("\n\n----------------------------INFORMACOES----------------------------");
                Inverter(Jogo, x, num);
                return 2;
            }
        }
    }
}

void contar(peca Jogo[], char i)
{
    int a, x=0;
    for(a=0; a<28; a++)
    {
        if(Jogo[a].info == i) 
        {
            x++;
            Jogo[a].count = x;
        }
    }
}

int contarMesa(mesa Mesa[])
{
    int a, x=0;
    for(a=0; a<28; a++)
    {
        if(Mesa[a].info == 1) 
        {
            x++;
        }
    
    }
    return x;
}

void verificaFim(peca Jogo[], mesa Mesa[])
{
    int a, quant, x=0;
    quant = contarMesa(Mesa);
    int jog1 = contarMao(Jogo, '1');
    int jog2 = contarMao(Jogo, '2');
    int comp = contarMao(Jogo, 'C');
    int pontj1 = pontuacao(Jogo, '1');
    int pontj2 = pontuacao(Jogo, '2');

    if (jog1 == 0 && comp == 0) // Vitoria do jogador 1
    {
        printf("\n\n\n\n\n\n\n\n");
        Mostrapecasmesa(Mesa);
        pause (0.05);
        printf("\n----------------------------O jogador 1 eh o vencedor!----------------------------\n"); 
        exit(0);
    }
    else if (jog2 == 0 && comp == 0) // Vitoria do Jogador 2
    {
        printf("\n\n\n\n\n\n\n\n");
        Mostrapecasmesa(Mesa);
        pause (0.05);
        printf("\n----------------------------O jogador 2 eh o vencedor!----------------------------\n");
        exit(0);
    }
    else if (jog1 != 0 && jog2 != 0 && comp == 0)   //empate técnico
    {
        for(a=0; a<28; a++)
        {
            if(Jogo[a].info != 'M')
            {
                if((Mesa[0].esquerda == Jogo[a].lado2) || (Mesa[0].esquerda == Jogo[a].lado1) || (Mesa[quant-1].direita == Jogo[a].lado1) || (Mesa[quant-1].direita == Jogo[a].lado2))
                {
                    x = 1; //passou no teste, ainda existe uma peça a ser colocada
                }
            }
            
        }
        if(x == 0)   //não existe nenhuma peça a ser colocada
        {
            pause (0.05);
            printf("\n----------------------------A area de compra esta vazia e nenhum jogador possui uma peca condizente a ser colocada. Fim de jogo----------------------------\n");
            if (pontj1 > pontj2) // Verifica a pontuação do jogador
            {
                pause (0.05);
                printf("\n\n\n\n\n\n\n\n");
                Mostrapecasmesa(Mesa);
                pause (0.05);
                printf("\n----------------------------O jogador 2 eh o vencedor!----------------------------\n");
                exit(0);
            }
            else
            {
                printf("\n\n\n\n\n\n\n\n");
                Mostrapecasmesa(Mesa);
                pause (0.05);
                printf("\n----------------------------O jogador 1 eh o vencedor!----------------------------\n");
                exit(0);
            }
        }
    }
}

int contarMao (peca Jogo[], char i)
{
    int a, x=0;

    for(a=0; a<28; a++)
    {
        if(Jogo[a].info == i) 
        {
            x++;
        }
    }
    return x;
}

int pontuacao(peca Jogo[],char i) // Vai somar os valores das peças de cada jogador
{
    int a, soma = 0;

    for(a=0; a<28; a++) // Loop dentro da matriz Jogo
    {
        if(Jogo[a].info == i) // Encontra a peça com o status i
        {
            soma = soma + Jogo[a].lado1 + Jogo[a].lado2; // Soma o valor da peça 
        }
    }
    return soma;
}

void mostrarCarregamento (char palavra[], char imagem[])
{    
    int i, j;
    float x = 0;

     clear();//limpa tela          
   
     for (i = 0; i <= 100; i++)
     {  
        //Animação da barrinha
         printf ("\n\n%s: ", palavra);    
         if(x == 0  || (x/10) >= 0  && (x/10) < 1)
            printf ("[|]  ");
         if(x == 1  || (x/10) >= 1  && (x/10) < 2)
            printf ("[/]  " );

         if(x == 2  || (x/10) >= 2  && (x/10) < 3)
            printf ("[-]  "  );
         if(x == 3  || (x/10) >= 3  && (x/10) < 4)
            printf ("[\\]  " );
         if(x == 4  || (x/10) >= 4  && (x/10) < 5)
            printf ("[|]  "  );
         if(x == 5  || (x/10) >= 5  && (x/10) < 6)
            printf ("[/]  "  );
         if(x == 6  || (x/10) >= 6  && (x/10) < 7)
            printf ("[-]  "  );
         if(x == 7  || (x/10) >= 7  && (x/10) < 8)
            printf ("[\\]  "  );
         if(x == 8  || (x/10) >= 8  && (x/10) < 9)
            printf ("[|]  "  );
         if(x == 9  || (x/10) >= 9  && (x/10) < 10)
            printf ("[/]  "  );


         printf ("%d%% ", i);      
         fflush (stdout);//garante a escrita de dados imediatamente na tela                  
         //repare mod 10, eu limito a qtd de pontos q serao gerados
         
         for (j = 0; j < i%10; j++)
         {
            printf("%s", imagem);
         } 

         //printf(">");
         
         fflush (stdout);//garante a escrita de dados imediatamente na tela
         pause (0.02);//função espera por tempo, parametro em microsegundos.
         printf("\r");//retorna para o inicio da linha 
         clear();
         x++;
     }                 
     printf (" ");//Apagar mensagem   
     
}

void Salvajogo() 
{
    int a;

    if ((fj = fopen("ArquivoJogo", "wb")) == NULL) //arquivo para as pecas do jogo
    {
        puts("\nErro ao abrir o arquivo!\n");
        exit(1);
    }
    for(a=0; a<28; a++)
    {
        if(fwrite(&Jogo[a], sizeof(peca), 1, fj) !=1)
        {
            printf("\nErro na gravacao do arquivo\n");
        }
    }
    fclose(fj);

    if ((fm = fopen("ArquivoMesa", "wb")) == NULL) //arquvo para as pecas da mesa
    {
        puts("\nErro ao abrir o arquivo!\n");
        exit(1);
    }
    for(a=0; a<28; a++)
    {
        if(fwrite(&Mesa[a], sizeof(mesa), 1, fm) !=1)
        {
            printf("\nErro na gravacao do arquivo\n\n");
        }
    }
    fclose(fm);

    if ((fv = fopen("ArquivoVariaveis", "wb")) == NULL) // arquivo para as variaveis gerias
    {
        puts("\nErro ao abrir o arquivo!\n");
        exit(1);
    }
    if(fwrite(&salva_v, sizeof(info_jogo), 1, fv) !=1) 
    {
        printf("Erro na gravacao do arquivo.\n");
    }
    fclose(fv);
    
    mostrarCarregamento("Salvando", ".");
    printf("\nJogo salvo, retornando ao menu inicial... \n");
}

void Carregajogo()
{
    int a;

    if ((fj = fopen("ArquivoJogo","rb")) == NULL) {
        puts("\nErro ao abrir o arquivo!\n");
        exit(1);
    }
    for(a=0; a<28; a++)
    {
        if(fread(&Jogo[a], sizeof(peca), 1, fj) !=1)
        {
            printf("\nErro ao ler o arquivo\n");
        }
    }
    fclose(fj);

    if ((fm = fopen("ArquivoMesa","rb")) == NULL) {
        puts("\nErro ao abrir o arquivo!\n");
        exit(1);
    }
    for(a=0; a<28; a++)
    {
        if(fread(&Mesa[a], sizeof(mesa), 1, fm) !=1)
        {
            printf("\nErro ao ler o arquivo\n");
        }
    }
    fclose(fm);

    if ((fv = fopen("ArquivoVariaveis","rb")) == NULL) {
        puts("\nErro ao abrir o arquivo!\n");
        exit(1);
    }
    if(fread(&salva_v, sizeof(info_jogo), 1, fv) !=1)
    {
        printf("\nErro ao ler o arquivo\n");
    }
    fclose(fv);
    
    mostrarCarregamento("Carregando", ".");
    printf("\nO jogo foi carregado, retornando a partida... \n");
}
