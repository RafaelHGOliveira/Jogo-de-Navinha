#include <stdio.h>
#include <windows.h>

// Definição da estrutura de dados para armazenar informações do jogo
struct jogo{
    int tiro[2];        // Posição do tiro (linha e coluna)
    int bixo[2];        // Posição do inimigo (linha e coluna)
    int morrido[100];   // Array para rastrear status dos inimigos (morto ou vivo)
};

struct jogo x;          // Variável que armazena os dados do jogo atual

HANDLE mutex_tela;      // Variável de controle de acesso à tela do console

// Move o cursor para uma posição específica na tela
void gotoxy(int x, int y){
    COORD coord;
    coord.X=(short)x;
    coord.Y=(short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}

// Declaração das funções utilizadas
void teste(int x);
void inimigo();
void tiro(int lin);

int main(void){
    int linNave=12, colNave=0;
    char tecla;

    mutex_tela=CreateMutex(NULL,FALSE,NULL);  // Inicialização do mutex

    gotoxy(colNave,linNave);
    printf("K");

    srand(time(0));

    _beginthread(inimigo,0,0);   // Inicia a função que controla os inimigos em uma nova thread

    while(1){
        tecla=getch();

        switch(tecla){
            case 32:  // Barra de espaço: disparar tiro
                _beginthread(tiro,0,linNave);  // Inicia a função de tiro em uma nova thread
                break;
            case -32: // Tecla especial
                tecla=getch();
                if (tecla==72){  // Tecla para cima: mover nave para cima
                    WaitForSingleObject(mutex_tela,INFINITE);
                    gotoxy(colNave,linNave);
                    printf(" ");
                    linNave--;
                    if (linNave<0)
                        linNave=0;
                    gotoxy(colNave,linNave);
                    printf("K");
                    ReleaseMutex(mutex_tela);
                }
                else if(tecla==80){  // Tecla para baixo: mover nave para baixo
                    WaitForSingleObject(mutex_tela,INFINITE);
                    gotoxy(colNave,linNave);
                    printf(" ");
                    linNave++;
                    if (linNave>24)
                        linNave=24;
                    gotoxy(colNave,linNave);
                    printf("K");
                    ReleaseMutex(mutex_tela);
                }
        }
    }
}

// Função que controla o movimento dos inimigos
void inimigo(){
    int col=30,lin=20,i,j,t;

    // Encontra um inimigo disponível para iniciar seu movimento
    for(j=0;j<100;j++){
        if(x.morrido[j]!=1 && x.morrido[j]!=2){
            x.morrido[j]=1;
            t=j;
            j=100;
        }
    }

    _beginthread(teste,0,j);  // Inicia a função de teste para verificar colisão com o tiro

    while(col>2){
        i=0;
        while (i<10){
            WaitForSingleObject(mutex_tela,INFINITE);
            gotoxy(col,lin);
            printf(" ");
            lin--;
            gotoxy(col,lin);
            printf("I");
            x.bixo[0]=lin;
            x.bixo[1]=col;
            ReleaseMutex(mutex_tela);
            _sleep(100);
            if (x.morrido[t]==2){
                i=10;
                printf("entro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\nentro\n");
            }
            else{
                i++;
            }
        }
        WaitForSingleObject(mutex_tela,INFINITE);
        printf(" ");
        if (x.morrido[t]==2){
            col=col;
        }
        else{
            col--;
        }
        gotoxy(col,lin);
        printf("I ");
        x.bixo[0]=lin;
        x.bixo[1]=col;
        ReleaseMutex(mutex_tela);
        _sleep(50);
        i=0;
        while(i<10){
            WaitForSingleObject(mutex_tela,INFINITE);
            gotoxy(col,lin);
            printf(" ");
            lin++;
            gotoxy(col,lin);
            printf("I");
            x.bixo[0]=lin;
            x.bixo[1]=col;
            ReleaseMutex(mutex_tela);
            _sleep(100);
            if (x.morrido[t]==2){
                i=10;
            }
            else{
                i++;
            }
        }
        WaitForSingleObject(mutex_tela,INFINITE);
        printf(" ");
        if (x.morrido[t]==2){
            col=col;
        }
        else{
            col--;
        }
        gotoxy(col,lin);
        printf("I ");
        x.bixo[0]=lin;
        x.bixo[1]=col;
        ReleaseMutex(mutex_tela);
        _sleep(100);
        if (x.morrido[t]==2){
            col=2;
        }
        else{
            i++;
        }
    }
}

// Função para controlar o movimento do tiro
void tiro(int lin){
    int col=1;

    while(col<80){
        WaitForSingleObject(mutex_tela,INFINITE);
        gotoxy(col,lin);
        printf("-");
        x.tiro[0]=lin;
        x.tiro[1]=col;
        ReleaseMutex(mutex_tela);
        _sleep(20);
        WaitForSingleObject(mutex_tela,INFINITE);
        gotoxy(col,lin);
        printf(" ");
        x.tiro[0]=lin;
        x.tiro[1]=col;
        ReleaseMutex(mutex_tela);
        col++;
    }
}

// Função de teste para verificar se o tiro colidiu com o inimigo
void teste(int w){
    int i=1;
    while(i){
        if (x.tiro[0]==x.bixo[0] && x.tiro[1]==x.bixo[1]){
            x.morrido[w]=2;
        }
    }
}
