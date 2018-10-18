//bibliotecas do c
#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>
//defenir as teclas que vao ser usadaspara controlar o "rato"
#define cima 72
#define baixo 80
#define direita 77
#define esquerda 75
#define ESC 27
//defenir o que o mapa vai conter
#define caminho 0
#define paredes 1
#define ratos 2
#define keijo 3
#define muralha 5
//declaração de variaveis
int distanciahorizontal=20,distanciavertical=10,paredehorizontal=79,paredevertical=13,mapa[79][13],linha,coluna,desbloquear=0,falhas=0,numerojogos=0,vitorias=0,rato[1],queijo[1],pontocontrolo1[1],pontocontrolo2[1];
char nome[10];
//procedimento para criar o caminho entre o "rato" e o "queijo"
void encontrarcaminho(int pontocontrolohorizontal,int pontocontrolovertical)
{
     int x,y;
     int ratohorizontal=rato[0],ratovertical=rato[1];
     //este while e o que ele contem basicamente vai criar uma linha na horizontal a partir do local onde se encontra o "rato" e uma linha na vertical a partir do sitio onse se encontra o "queijo"
     while((pontocontrolohorizontal!=ratohorizontal) || (pontocontrolovertical!=ratovertical))
     {   
         if(pontocontrolohorizontal < ratohorizontal)
         {
                                                     ratohorizontal = ratohorizontal-1;
                                                     mapa[ratohorizontal][ratovertical]=caminho; 
                                                     continue;
         }
         if(pontocontrolovertical < ratovertical)
         {
                                                 ratovertical = ratovertical-1;
                                                 mapa[ratohorizontal][ratovertical]=caminho; 
                                                 continue;
         }
         if(pontocontrolohorizontal > ratohorizontal)
         {
                                            ratohorizontal = ratohorizontal+1;
                                            mapa[ratohorizontal][ratovertical]=caminho; 
                                            continue;
         }
         
         if(pontocontrolovertical > ratovertical)
         {
                                                 ratovertical = ratovertical+1;
                                                 mapa[ratohorizontal][ratovertical]=caminho; 
                                                 continue;
         }
     }
}
//procedimento para criar o mapa do labirinto
void criarmapa()
{
     //sorteia aleatoriamente dois numeros e desses doi numeros encontra a posição do "queijo"
     queijo[0]=rand()%(paredehorizontal-2)+1; 
     queijo[1]=rand()%(paredevertical-2)+1; 
     //os proximos do while servem para testar se o "queijo" esta perto do "rato" ou de uma das paredes da "muralha"
     do
     {
       rato[0]=rand()%(paredehorizontal-2)+1; 
       rato[1]=rand()%(paredevertical-2)+1;          
     }while(verificar(rato[0],rato[1]) == 1);
     do
     {
       pontocontrolo1[0]=rand()%(paredehorizontal-2)+1; 
       pontocontrolo1[1]=rand()%(paredevertical-2)+1;          
     }while(verificar(pontocontrolo1[0],pontocontrolo1[1])==1);
     do
     {
       pontocontrolo2[0]=rand()%(paredehorizontal-2)+1; 
       pontocontrolo2[1]=rand()%(paredevertical-2)+1;         
     }while(verificar(pontocontrolo2[0],pontocontrolo2[1])==1);
     srand(time(NULL)); //linha nesseçario para a criação aleatoria de numeros
     
     int x,y;
     //condição para criar uma"muralha" a volta do mapa do labirinto
     for(y=0;y<paredevertical;y++)
     {
         for (x=0;x<paredehorizontal;x++)
         {
              if ((x==0 || y==0) || (x==(paredehorizontal-1) || y==(paredevertical-1)))
              {
                  mapa[x][y]=muralha;
              }
              else
              {
                  mapa[x][y]=rand()%2;
              }
         }
     }
     //cria o caminho entre o "rato" e o "queijo"
     encontrarcaminho(pontocontrolo1[0],pontocontrolo1[1]);
     encontrarcaminho(pontocontrolo2[0],pontocontrolo2[1]);
     encontrarcaminho(queijo[0],queijo[1]);
     //marca no mapa a posição do "rato"
     mapa[rato[0]][rato[1]]=ratos;
     //marca no mapa a posição do "queijo"
     mapa[queijo[0]][queijo[1]]=keijo;
     //o desbloquear serve para "prender o rato" ou seja para que depois de o "rato" encontrar o "queijo" o jogador nao volte a mover o "rato" na mesma jogada
     desbloquear=0;
     //o numerojogos serve para contabilizar o numero de jogos que o jogador fez
     numerojogos++;
     //a linha e a coluna servem para guardar a posição do "rato" para que este se possa mover
     linha=rato[0];
     coluna=rato[1];   
}
//procedimento para desenhar no mapa a "muralha", as paredes, o "rato", eo o "queijo"
void desenharmapa()
{
     int x,y;
     system("cls");
     printf("#################################### Jogar #####################################\n");
     for(y=0;y<paredevertical;y++)
     {
         for (x=0;x<paredehorizontal;x++)
         {
                                         
                                         //desenha o mapa
                                         if (mapa[x][y] == muralha)
                                         {
                                                                   printf("#");
                                         }
                                         if(mapa[x][y] == paredes)
                                         {
                                                                 printf("#");
                                         }
                                         if(mapa[x][y] == caminho)
                                         { 
                                                                  printf(" ");
                                         }
                                         if(mapa[x][y] == ratos)
                                         {    
                                                                printf("R");
                                         }
                                         if(mapa[x][y] == keijo)
                                         {
                                                                printf("Q");
                                         }
         }
         printf("\n");
     }
     //desenha as setas para mostrar ao jogador as direçoes que ele pode escolher
     printf("\n\t\t\t\t      (%c)\n\n\t\t\t\t   (%c) + (%c)\n\n\t\t\t\t      (%c)\n",30,17,16,31);  
}

//verifica se existe algum "rato" ou alguma parede perto do "queijo"
int verificar(int verificarhorizontal, int verificarvertical) 
{
     int limiteinferiorhorizontal=verificarhorizontal-distanciahorizontal;
     int limiteinferiorvartical=verificarvertical-distanciavertical;
     int limitesuperiorhorizontal=verificarhorizontal+distanciahorizontal;
     int limitesuperiorvertical=verificarvertical+distanciavertical;
     //aqui vai servir para se sertificar se o programa nao esta a colocar o rato em cima da muralha ou fora do mapa
     if (limiteinferiorhorizontal < 1)
     {
                                      limiteinferiorhorizontal=1;
     }
     if (limiteinferiorvartical < 1)
     {
                                    limiteinferiorvartical=1;
     }
     if (limitesuperiorhorizontal > (paredehorizontal-2))
     {
                                                         limitesuperiorhorizontal=(paredehorizontal-2);
     }
     if (limitesuperiorvertical > (paredevertical-2))
     {
                                                     limitesuperiorvertical=(paredevertical-2);
     }
     
     int y,x;
     //condições para defenir o ponto no mapa onde o queijo vai ser colocado
     for (y=limiteinferiorvartical;y<limitesuperiorvertical;y++)
     {
         for (x=limiteinferiorhorizontal;x<limitesuperiorhorizontal;x++)
         {
                                                                        if(mapa[x][y] == keijo)
                                                                        {
                                                                                               //se isto acontecer quer dizer que o queijo nao pode ser escrito no mapa porque esta em cima da "muralha" ou fora do mapa
                                                                                               return 1;
                                                                        }
         }
     }
     //se isto acontecer o queijo pode ser escrito no mapa
     return 0;
}
//procedimento para mostrar ao utilizador que ganhou
void ganhou()
{
     printf("\n\t\t\tParabens, ganhou o jogo do labirinto!\n\t\t\tCarregue em ESC para voltar ao menu.\n");
     if(desbloquear==1)
     {
                       //quando isto acontecer aumenta um numero nas vitorias do jogador e nao perite que este volte a jogar pela segunda vez no mesmo mapa
                       vitorias++;
                       desbloquear=2;
     }
}
//procedimento para mostrar ao jogador que ele foi contra uma parede e para aumentar o numero de tentativas do jogador
void caminhoinvalido()
{
     desenharmapa();
     printf("\n\t\t\t\tNão pode passar!\n\t\t\t     Foi contra uma parede.\n");
     falhas++;  
}


main()
{
      int opcao,mover;
      char ler[100],guardarnome[10];
      //funções do c para que seja possivel guardar a hora e a data do sistema
      SYSTEMTIME str_t;
      GetSystemTime(&str_t);
      printf("################################### Inicio #####################################");
      printf("\n\nIntruduza o nome do jogador:\n");
      gets(nome);
      fflush(stdin);                         
      do
      {
            system("cls");
            printf("############################## Jogo do Labirinto ###############################");
            printf("\n\n\t\t\t #############################");
            printf("\n\t\t\t ## 1 - Jogar               ##");
            printf("\n\t\t\t ## 2 - Ver Score Actual    ##");
            printf("\n\t\t\t ## 3 - Ver Todos os Scores ##");
            printf("\n\t\t\t ## 4 - Guardar Scores      ##");
            printf("\n\t\t\t ## 0 - Sair                ##");
            printf("\n\t\t\t #############################");      
            printf("\n\t\t\t\t    Opcao: ");      
            fflush(stdin);
            scanf("%d",&opcao);
            system("cls");
            switch(opcao)
            {
              case 1:
                   criarmapa();
                   desenharmapa();
                   fflush(stdin);
                   mover=getch();
                   while (mover!=ESC)
                   {
                                     if(mover==cima)
                                     {
                                                    if(desbloquear == 0)
                                                    {
                                                                        //move o rato uma posição para cima se o rato nao tiver uma parede no seu caminho
                                                                        if((mapa[linha][coluna-1]!=paredes) && (mapa[linha][coluna-1]!=muralha))
                                                                        {
                                                                                                            if(mapa[linha][coluna-1]==keijo)
                                                                                                            {
                                                                                                                                            desbloquear=1;
                                                                                                            }          
                                                                                                            mapa[linha][coluna]=caminho;
                                                                                                            coluna--;
                                                                                                            mapa[linha][coluna]=ratos;
                                                                                                            desenharmapa();          
                                                                                                            if(desbloquear!=0)
                                                                                                            {
                                                                                                                              ganhou();
                                                                                                            }
                                                                        }
                                                                        else
                                                                        {
                                                                            caminhoinvalido();
                                                                        }
                                                    }
                                     }
                                     if(mover==baixo)
                                     {
                                                     if(desbloquear==0)
                                                     {
                                                                       //move o rato uma posição paa baixo
                                                                       if((mapa[linha][coluna+1]!=paredes) && (mapa[linha][coluna+1]!=muralha))
                                                                       {
                                                                                                           if(mapa[linha][coluna+1]==keijo)
                                                                                                           {
                                                                                                                                           desbloquear=1;
                                                                                                           }          
                                                                                                           mapa[linha][coluna]=caminho;
                                                                                                           coluna++;
                                                                                                           mapa[linha][coluna]=ratos;
                                                                                                           desenharmapa();          
                                                                                                           if(desbloquear!=0)
                                                                                                           {
                                                                                                                             ganhou();
                                                                                                           }
                                                                       }
                                                                       else
                                                                       {
                                                                           caminhoinvalido();
                                                                       }
                                                     }
                                     }
                                     if(mover==esquerda)
                                     {
                                                        if(desbloquear == 0)
                                                        {
                                                                            //move o rato uma posição para a esquerda
                                                                            if((mapa[linha-1][coluna]!=paredes) && (mapa[linha-1][coluna]!=muralha))
                                                                            {
                                                                                                                if(mapa[linha-1][coluna]==keijo)
                                                                                                                {
                                                                                                                                                desbloquear=1; 
                                                                                                                }         
                                                                                                                mapa[linha][coluna]=caminho;
                                                                                                                linha--;
                                                                                                                mapa[linha][coluna]=ratos;
                                                                                                                desenharmapa();          
                                                                                                                if(desbloquear!=0)
                                                                                                                {
                                                                                                                                  ganhou();
                                                                                                                }
                                                                            }
                                                                            else
                                                                            {
                                                                                caminhoinvalido();
                                                                            }
                                                        }
                                     }
                                     if(mover==direita)
                                     {
                                                       if(desbloquear==0)
                                                       {                 
                                                                         //move o rato uma posição para a direita
                                                                         if((mapa[linha+1][coluna]!=paredes) && (mapa[linha+1][coluna]!=muralha))
                                                                         {
                                                                                                             if(mapa[linha+1][coluna]==keijo)
                                                                                                             {
                                                                                                                                             desbloquear=1;
                                                                                                             }          
                                                                                                             mapa[linha][coluna]=caminho;
                                                                                                             linha++;
                                                                                                             mapa[linha][coluna]=ratos;
                                                                                                             desenharmapa();          
                                                                                                             if(desbloquear!=0)
                                                                                                             {
                                                                                                                               ganhou(); 
                                                                                                             }
                                                                         }
                                                                         else
                                                                         {
                                                                             caminhoinvalido();
                                                                         }
                                                       }
                                     }
                                     fflush(stdin);
                                     mover=getch();
                   }
                   break;
              case 2:
                     system("cls");
                     fflush(stdin);
                     printf("################################## Ver Scores ##################################");
                     printf("\n\nJogador: %s\nData: %d-%d-%d\nHora: %d:%d:%d\nNº Jogos: %d\nVitorias: %d\nTentativas: %d",nome,str_t.wDay,str_t.wMonth,str_t.wYear,str_t.wHour,str_t.wMinute,str_t.wSecond,numerojogos,vitorias,falhas);
                     getch();
                     break;
              case 3:
                     system("cls");
                     fflush(stdin);
                     FILE *fp2 = fopen("scores.txt","r");
                     printf("############################## Ver odos os scores ##############################");
                     if(fp2 != NULL)
                     {
                                   while(!feof(fp2))
                                   {
                                                   
       		                                       fgets(ler, 100, fp2);
       		                                       puts(ler);
                                   }           
                                   fclose(fp2);
                     }
                     getch();
                     break;
              case 4:
                     system("cls");
                     fflush(stdin);
                     //abre o ficheiro para escrita
                     FILE *fp = fopen("scores.txt","a");
                     printf("################################ Guardar Scores ################################");
                     printf("\n\n\t\t\t    Score guardado com sucesso.");
                     fprintf(fp,"\n\nJogador: %s\nData: %d-%d-%d\nHora: %d:%d:%d\nNº Jogos: %d\nVitorias: %d\nTentativas: %d",nome,str_t.wDay,str_t.wMonth,str_t.wYear,str_t.wHour,str_t.wMinute,str_t.wSecond,numerojogos,vitorias,falhas);
                     fclose(fp);
                     getch();
                     break;
              default:
                      break;
          }
      }while(opcao!=0);
}
