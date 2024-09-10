/*Lucas Mariano Cuani                  9066581
  Alan Lucindo Gomes                   7572130 */

/* A funçao LoadLevel funcionou corretamente na nossa casa, mas teve um erro na leitura das linhas qdo compilamos na rede linux */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LIM 500
#define MAXMOV 500
int main();
void LoadLevel(char map[LIM][LIM], int *m, int *n, char filename[]);
void PrintLevel(char map[LIM][LIM], int m, int n);
void GetPlayerPos(char map[LIM][LIM], int m, int n, int *i, int *j);
int Move(char *mov, char map[LIM][LIM], int m, int n);
void Undo(char mov[MAXMOV], char map[LIM][LIM], int m, int n);
int LevelComplete(char map[LIM][LIM], int m, int n);
int IsValidLevel (char map[LIM][LIM], int m, int n);


int main(){
    int m,n,i,j,k;
    char move[MAXMOV];
    char mov;
    char map[LIM][LIM];
    char filename[LIM];
    printf ("Digite o nome do arquivo do mapa:\n");
    scanf("%s", filename);
    LoadLevel(map,&m,&n,filename);
    if(!IsValidLevel (map,  m,  n))
    return 0;
    GetPlayerPos(map,m,n,&i,&j);
    for (k=0; k<MAXMOV; k++){
            if(LevelComplete(map,m,n)){
                printf("Parabens, voce concluiu a fase \n");
                return 0;}
        PrintLevel(map,m,n);
        printf("up, down, left, right, back or quit: (u,d,l,r,b,q): \n");
        scanf(" %c", &mov);
            if(mov=='b'){
            move[k]='\0';
            Undo(move,map,i,j);
            if(k>0){
            k--;
            if(k>0)
            k--;
            }
            }
        else if(mov != '\0' && mov != 'q'&&mov!='b'){
            if(Move(&mov,map,m,n)){
            move[k]=mov;}
        }
            else if((Move(&mov,map,m,n)==0)&& mov!='b'){
                if((mov=='u')||(mov=='d')||(mov=='r')||(mov=='l'))
                    move[k]=mov;
}
            printf("VK %d, (%c)\n", k, move[k]);
        }
    printf("\n");
    return 0;
}
void Undo(char move[MAXMOV], char map[LIM][LIM], int m, int n){
    int i,a, ijog,jjog;
    char movoposto;
    for(i=0;i<LIM;i++){
            printf("%d e (%c)\n", i, move[i]);
        if(move[i]=='\0'){
            a=i-1;
            printf("A-%d e (%c)\n", a, move[a]);
         break;
        }
    }

        GetPlayerPos(map,m,n,&ijog,&jjog);

            if (move[a]=='d'){
            movoposto='u';
            Move(&movoposto,  map,  m,  n);
        }
            else if (move[a]=='u'){
            movoposto='d';
            Move(&movoposto,  map,  m,  n);
        }
           else if (move[a]=='r'){
            movoposto='l';
            Move(&movoposto,  map,  m,  n);
        }
           else if (move[a]=='l'){
            movoposto='r';
            Move(&movoposto,  map,  m,  n);
        }
            else if (move[a]=='U'){
            movoposto='d';
            Move(&movoposto,  map,  m,  n);
            if(map[ijog-1][jjog]=='$'){
            map[ijog-1][jjog]=' ';
            if(map[ijog][jjog]=='+'){
            map[ijog][jjog]=='*';
            }
            else if (map[ijog][jjog]=='@'){
            map[ijog][jjog]=='$';
            }
            }
            else if(map[ijog-1][jjog]=='*'){
            map[ijog-1][jjog]='.';
            if(map[ijog][jjog]=='+'){
            map[ijog][jjog]=='*';
            }
            else if (map[ijog][jjog]=='@'){
            map[ijog][jjog]=='$';
            }}}


          else if (move[a]=='D'){
            movoposto='u';
            Move(&movoposto,  map,  m,  n);

        }
           else if (move[a]=='R'){
            movoposto='l';
            Move(&movoposto,  map,  m,  n);


        }
           else if (move[a]=='L'){
            movoposto='r';
            Move(&movoposto,  map,  m,  n);


        }
}

void LoadLevel(char map[LIM][LIM], int *m, int *n, char filename[]){
 FILE *fp;
 char C;
 int i,j,a,k;
 k=a=1;
 fp = fopen(filename,"r");
 if(fp == NULL){
printf("Erro na leitura do arquivo.\n");}
 for (i=0;i<LIM ;i++){
    for (j=0; j<LIM; j++){
        fscanf(fp,"%c",&C);

        if (C=='\n'){
            k++;
                        if (j>a)
            a=j;
            break;
        }
        if(C=='\0'){
                            if (j>a)
            a=j;
        break;}
    }
        if(C=='\0'){
                            if (j>a)
            a=j;
            k++;
        break;}
 }
 fclose(fp);

*n=a;
*m=k;

 fp = fopen(filename,"r");
   for (i=0;i<k;i++){
    for (j=0;j<=a;j++){
    fscanf(fp,"%c",&map[i][j]);
            if(map[i][j]=='\n')
            break;
}}
fclose(fp);
}

void PrintLevel(char map[LIM][LIM], int m, int n){
int i,j;
for(i=0;i<m;i++){
for(j=0;j<=n;j++){
            printf("%c", map[i][j]);
            if(map[i][j]=='\n'){
            break;
            }
}
}
printf("\n");
}

void GetPlayerPos(char map[LIM][LIM], int m, int n, int *i, int *j){
int a,b;
for(a=0;a<m;a++){
for(b=0;b<=n;b++){
if ((map[a][b]=='+')||(map[a][b]=='@')){
*i=a;
*j=b;}
}
}
}

int Move(char *mov, char map[LIM][LIM], int m, int n){
int i,j;
i=j=0;
 GetPlayerPos(map,m,n,&i,&j);
        if (*mov == 'u') {
            if(map[i-1][j]== '#') /* tentar se mover pruma cerca */
                return 0;
            else if( map[i-1][j]==' '){ /* se mover para uma casa vazia */
                map[i-1][j] = '@';
                if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                    map[i][j] = ' ';
                else  /* se o jogador estava em uma casa de armazenamento */
                    map[i][j] = '.';

            } else if( map[i-1][j]=='.'){ /* se mover pruma casa de armazenamento */
                    map[i-1][j] = '+';
                    if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                        map[i][j] = ' ';
                    else  /* se o jogador estava em uma casa de armazenamento */
                        map[i][j] = '.';

            }else if ((map [i-1][j]== '$') ||(map [i-1][j]== '*')  ){    /*empurrar uma caixa */
                    *mov= 'U';
                    if ((map [i-2][j]== '$')|| (map [i-2][j]== '*')   || (map [i-2][j]== '#') )
                        return 0;
                    else if(map [i-2][j]=='.'){
                        map[i-2][j]= '*';
                         if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                            map[i][j] = ' ';
                         else  /* se o jogador estava em uma casa de armazenamento */
                            map[i][j] = '.';
                         if (map [i-1][j]== '$') /* se a caixa estava em um local comum */
                            map [i-1][j] = '@';
                         else                     /* se a caixa estava num local de armazenamento */
                            map [i-1][j]= '+';
                    }else if(map [i-2][j]==' '){
                        map[i-2][j]= '$';
                         if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                            map[i][j] = ' ';
                         else  /* se o jogador estava em uma casa de armazenamento */
                            map[i][j] = '.';
                         if (map [i-1][j]== '$') /* se a caixa estava em um local comum */
                            map [i-1][j] = '@';
                         else                     /* se a caixa estava num local de armazenamento */
                            map [i-1][j]= '+';
                    }
            }

   } else if(*mov== 'd' ){
            if(map[i+1][j]== '#') /* tentar se mover pruma cerca */
                return 0;
            else if( map[i+1][j]==' '){ /* se mover para uma casa vazia */
                map[i+1][j] = '@';
                if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                    map[i][j] = ' ';
                else  /* se o jogador estava em uma casa de armazenamento */
                    map[i][j] = '.';

            } else if( map[i+1][j]=='.'){ /* se mover pruma casa de armazenamento */
                    map[i+1][j] = '+';
                    if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                        map[i][j] = ' ';
                    else  /* se o jogador estava em uma casa de armazenamento */
                        map[i][j] = '.';

            }else if ((map [i+1][j]== '$') ||(map [i+1][j]== '*')  ){    /*empurrar uma caixa */
                    *mov=='D';
                    if ((map [i+2][j]== '$')|| (map [i+2][j]== '*')   || (map [i+2][j]== '#') )
                        return 0;
                    else if(map [i+2][j]=='.'){
                        map[i+2][j]= '*';
                         if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                            map[i][j] = ' ';
                         else  /* se o jogador estava em uma casa de armazenamento */
                            map[i][j] = '.';
                         if (map [i+1][j]== '$') /* se a caixa estava em um local comum */
                            map [i+1][j] = '@';
                         else                     /* se a caixa estava num local de armazenamento */
                            map [i+1][j]= '+';
                    }else if(map [i+2][j]==' '){
                        map[i+2][j]= '$';
                         if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                            map[i][j] = ' ';
                         else  /* se o jogador estava em uma casa de armazenamento */
                            map[i][j] = '.';
                         if (map [i+1][j]== '$') /* se a caixa estava em um local comum */
                            map [i+1][j] = '@';
                         else                     /* se a caixa estava num local de armazenamento */
                            map [i+1][j]= '+';
                    }
            }

   }
else if(*mov=='l'){
            if(map[i][j-1]== '#') /* tentar se mover pruma cerca */
                return 0;
            else if(map[i][j-1]==' '){ /* se mover para uma casa vazia */
                map[i][j-1]='@';
                if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                    map[i][j]=' ';
                else  /* se o jogador estava em uma casa de armazenamento */
                    map[i][j] = '.';
            } else if( map[i][j-1]=='.'){ /* se mover pruma casa de armazenamento */
                    map[i][j-1] = '+';
                    if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                        map[i][j] = ' ';
                    else  /* se o jogador estava em uma casa de armazenamento */
                        map[i][j] = '.';

            }else if ((map [i][j-1]== '$') ||(map [i][j-1]== '*')  ){    /*empurrar uma caixa */
                *mov = 'L';
                    if ((map [i][j-2]== '$')||(map [i][j-2]== '*')||(map [i][j-2]== '#') )
                        return 0;
                    else if(map [i][j-2]=='.'){
                        map[i][j-2]= '*';
                         if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                            map[i][j] = ' ';
                         else  /* se o jogador estava em uma casa de armazenamento */
                            map[i][j] = '.';
                         if (map [i][j-1]== '$') /* se a caixa estava em um local comum */
                            map [i][j-1] = '@';
                         else                     /* se a caixa estava num local de armazenamento */
                            map [i][j-1]= '+';
                    }else if(map [i][j-2]==' '){
                        map[i][j-2]= '$';
                         if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                            map[i][j] = ' ';
                         else  /* se o jogador estava em uma casa de armazenamento */
                            map[i][j] = '.';
                         if (map [i][j-1]== '$') /* se a caixa estava em um local comum */
                            map [i][j-1] = '@';
                         else                     /* se a caixa estava num local de armazenamento */
                            map [i][j-1]= '+';
                    }
            }

   }
   else if(*mov=='r'){
            if(map[i][j+1]== '#') /* tentar se mover pruma cerca */
                return 0;
            else if(map[i][j+1]==' '){ /* se mover para uma casa vazia */
                map[i][j+1]='@';
                if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                    map[i][j]=' ';
                else  /* se o jogador estava em uma casa de armazenamento */
                    map[i][j] = '.';
            } else if( map[i][j+1]=='.'){ /* se mover pruma casa de armazenamento */
                    map[i][j+1] = '+';
                    if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                        map[i][j] = ' ';
                    else  /* se o jogador estava em uma casa de armazenamento */
                        map[i][j] = '.';

            }else if ((map [i][j+1]== '$') ||(map [i][j+1]== '*')  ){    /*empurrar uma caixa */
                    *mov='R';
                    if ((map [i][j+2]== '$')||(map [i][j+2]== '*')||(map [i][j+2]== '#') )
                        return 0;
                    else if(map [i][j+2]=='.'){
                        map[i][j+2]= '*';
                         if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                            map[i][j] = ' ';
                         else  /* se o jogador estava em uma casa de armazenamento */
                            map[i][j] = '.';
                         if (map [i][j+1]== '$') /* se a caixa estava em um local comum */
                            map [i][j+1] = '@';
                         else                     /* se a caixa estava num local de armazenamento */
                            map [i][j+1]= '+';
                    }else if(map [i][j+2]==' '){
                        map[i][j+2]= '$';
                         if (map[i][j]=='@') /*se o jogador estava em uma casa normal */
                            map[i][j] = ' ';
                         else  /* se o jogador estava em uma casa de armazenamento */
                            map[i][j] = '.';
                         if (map [i][j+1]== '$') /* se a caixa estava em um local comum */
                            map [i][j+1] = '@';
                         else                     /* se a caixa estava num local de armazenamento */
                            map [i][j+1]= '+';
                    }
            }

   }
}

int LevelComplete(char map[LIM][LIM], int m, int n){/*m e n sao tamanho real da matriz, nao coordenadas do jog.*/
int a, b, c;
c=1;
for(a=0;a<m;a++){
for(b=0;b<=n;b++){
if (map[a][b]=='$'){
    c=0;
}
}
}
return c;
}

int IsValidLevel (char map[LIM][LIM], int m, int n){
int a,b,c,d;
c=d=0;
for(a=0;a<m;a++){
for(b=0;b<=n;b++){
if ((map[a][b]=='.')||(map[a][b]=='+')|| (map [a][b]== '*')){
    c++;
}
if (map[a][b]=='$' || map[a][b]== '*'){
    d++;
}
}
if(d==c)
    return 1;
}
return 0;
}
