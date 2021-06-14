#include <stdio.h>
#include <windows.h>
struct jogo{
    int tiro[2];
    int bixo[2];
    int morrido[100];
};
struct jogo x;
HANDLE mutex_tela;
void gotoxy(int x, int y){
    COORD coord;
    coord.X=(short)x;
    coord.Y=(short)y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),coord);
}
void teste(int x);
void inimigo(){
    int col=30,lin=20,i,j,t;
    for(j=0;j<100;j++){
        if(x.morrido[j]!=1 && x.morrido[j]!=2){
            x.morrido[j]=1;
            t=j;
            j=100;
        }
    }
    _beginthread(teste,0,j);
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
void teste(int w){
    int i=1;
    while(i){
        if (x.tiro[0]==x.bixo[0] && x.tiro[1]==x.bixo[1]){
            x.morrido[w]=2;

        }
    }
}
int main(void){
    int linNave=12,colNave=0;
    char tecla;
    mutex_tela=CreateMutex(NULL,FALSE,NULL);
    gotoxy(colNave,linNave);
    printf("K");
    srand(time(0));
    _beginthread(inimigo,0,0);
    while(1){
        tecla=getch();
        switch(tecla){
        case 32: //barra de espaco
            _beginthread(tiro,0,linNave);
            break;
        case -32: //tecla especial
            tecla=getch();
            if (tecla==72){ //Tecla para cima
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
            else if(tecla==80){ //Tecla para baixo
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
