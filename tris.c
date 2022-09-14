#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>

/*
le mosse applicate dal computer sono riconducibili ad uno di questi 6 step:

	1 Se il vostro avversario ha occupato due caselle di fila, occupate la
		casella rimanente.

	2 Altrimenti, se c'è una mossa che crea due coppie di caselle adiacenti
		in un colpo solo, scegliete quella.

	3 Altrimenti, se la casella centrale è libera, occupatela.

	4 Altrimenti, se il vostro avversario ha occupato una casella d'angolo
		occupate la casella opposta.

	5 Altrimenti, se c'è un angolo vuoto, occupatelo.

	6 Altrimenti, occupate una casella vuota qualsiasi.
*/

void welcome();
int** matchup();
void tabdisplay(int** tab);
void printcomputer(int i, int j,int** tab);
char checkRIG(int** tab);
char checkCOL(int** tab);
char checkDIAG(int** tab);
int wincond(int** tab, char* vincitore); // 0 if none won 
int move(int** tab, char n);
int makemove(int** tab, char n, int round);
int winningmove(int** tab, int n);
int adjmove(int** tab, int n);
int centremove(int** tab, int N);
int oppAnglmove(int** tab, int N);
int anglmove(int** tab, int N);
void randmove(int** tab, int n, int round);




int main(int argc, char const *argv[]){
	srand(time(NULL));
	int** tab = matchup();
	char* vincitore= malloc(sizeof(char));

	int round=0;
	int player=1; //comicia sempre la X; se si vuole rendere randomico =rand()%2;
	int computer=0;
	char p;
	char d[200];
	welcome();
	do{
		if (round){
			printf("\033[0m");
			printf("Seleziona una modalita valida (1 / 2):");
			printf("\033[0;32m");
		}
		fgets(d,200,stdin);
		if (d[0]=='1'){
			computer=1;}
		else if(d[0]=='q'){
			printf("\033[0m");
			printf("\033[0;31m");
			printf("EXIT...");
			printf("\033[0m");
			return 0;}
		round =1;
	}while(!(d[0]=='1' || d[0]=='2'));
	printf("\033[0m");
	round = 0;	//reset round per il prossimo while
	if (computer==0){
		computer=-1;
	}
	else{
		computer=rand()%2+0;
	}
	while(!wincond(tab, vincitore) && round != 9){
		printf("\n------TURNO n°%i------", round+1);
		tabdisplay(tab);
		if (player==1){
			p='X';
			//printf("\033[0;34m");
			if (computer==1){
				makemove(tab,p,round);
			}
			else{
				if (move(tab,p))
					return 0; //this for exit
				}
			player=0;
			//printf("\033[0m");
		}
		else if(player==0){
			p='O';
			//printf("\033[1;31m");
			if (computer==0){
				makemove(tab,p,round);
				}
			else{		
				if (move(tab,p))
					return 0;
			}
			player=1;
			//printf("\033[0m");
		}
		round +=1;
	}
	printf("\n---Match--Concluso---");
	tabdisplay(tab);
	if(*vincitore!='n')
		if ((*vincitore=='X' && computer==1) || (*vincitore=='0' && computer==0))
			printf("Vince il Computer(%c)!",*vincitore);
		else{
			printf("Vince %c!\n",*vincitore );
		}

	else if (round == 9)
		puts("Pareggio :(");
	free(tab);
	free(vincitore);
	return 0;
}
void welcome(){
	printf("\n|");
	printf("\033[0;32m");
	printf("1 ");
	printf("\033[0m");
	printf("-> 1vsComputer \n|" );
	printf("\033[0;32m");
	printf("2 ");
	printf("\033[0m");
	printf("-> 1vs1 \n|");
	printf("\033[0;31m");
	printf("q ");
	printf("\033[0m");
	printf("-> EXIT (anche durante il match)\n|Buon divertimento!\n");
	printf("\033[0;32m");
	printf(">> ");




}
int** matchup(){
    int** tab= malloc(3*sizeof(int*));
	for (int i = 0; i < 3; ++i){
		tab[i] = malloc(3*sizeof(int));
		for (int j = 0; j < 3; ++j){
			tab[i][j]=1;
		}
	}
	return tab;
}
int wincond(int** tab, char* vincitore){
	if (checkRIG(tab)!='n'){
		*vincitore = checkRIG(tab);
		return 1;
	}
	if (checkCOL(tab)!='n'){
		*vincitore = checkCOL(tab);
		return 1;
	}
	if (checkDIAG(tab)!='n'){
		*vincitore = checkDIAG(tab);
		return 1;
	}
	*vincitore = 'n';
	return 0;
} 
char checkRIG(int** tab){
	for (int i = 0; i < 3; ++i){
			if ((tab[i][0]*tab[i][1]*tab[i][2])==125)
				//printf("%i%i%i",tab[0][i],tab[1][i],tab[2][i]);
				return 'O';
			if ((tab[i][0]*tab[i][1]*tab[i][2])==27)
				//printf("%i%i%i",tab[0][i],tab[1][i],tab[2][i]);
				return 'X';		
	}
	return 'n';
}
char checkCOL(int** tab){
	for (int i = 0; i < 3; ++i){
			if ((tab[0][i]*tab[1][i]*tab[2][i])==125)
				//printf("%i%i%i",tab[0][i],tab[1][i],tab[2][i]);
				return 'O';
			if ((tab[0][i]*tab[1][i]*tab[2][i])==27)
				//printf("%i%i%i",tab[0][i],tab[1][i],tab[2][i]);
				return 'X';	
	}
	return 'n';
}
char checkDIAG(int** tab){
	int check1 = tab[0][0]*tab[1][1]*tab[2][2];
	int check2 = tab[0][2]*tab[1][1]*tab[2][0];
	if (check1==125 || check2==125)
		return 'O';
	if (check1==27 || check2==27)
		return 'X';	
	return 'n';
}
void tabdisplay(int** tab){
    printf("\n     T--a-b-c--R\n");
	for (int i = 0; i < 3; ++i){
		printf("     %d  ",i+1);
		for (int j = 0; j < 3; ++j){
			
			if (tab[i][j]==1)
				printf(".");
			else if (tab[i][j]==3){
				printf("\033[0;36m");
				printf("X");
				printf("\033[0m");}
			else if (tab[i][j]==5){
				printf("\033[1;31m");
				printf("O");
				printf("\033[0m");}
			if (j!=2)
				printf(" ");
		}puts("  |");
	};
	printf("     I---------S\n");
}
int move(int** tab, char c){
	char pos[200];
	int postab[2];
	int time=0;

	char q='Q', x='X', o='O';
	int N;
	if (c==x){N=3;}
	else if (c==o){N=5;}

	do{	
		if (time == 0){
			printf("Scegli una posizione per ");
			if (c==x){
				printf("\033[0;36m");
				printf("X");
				printf("\033[0m");}
			else if(c==o) {
				printf("\033[1;31m");
				printf("O");
				printf("\033[0m");
			}
			printf(": ");
		}
		else if (time!=0){
			if (time==2){
				printf("Pozione non valida. ");
			}
			else if(time==3){
				printf("\t\t\t   ^ Casella gia occupata.\n");
			}
			printf("Scegli una posizione valida:");
		}
		time=2;
		if (c==x){
				printf("\033[0;36m");}
		else if(c==o) {
				printf("\033[1;31m");}
		fgets(pos, 200, stdin);
		printf("\033[0m");
		if (isalpha(pos[0]) && !(isdigit(pos[1]))){
			pos[0]=toupper(pos[0]);
			if (pos[0]==q){
				printf("\031[0;32m");
				printf("EXIT...");
				printf("\031[0m");
				free(tab);
				return 1;
			}
			else{time=2;}
		}
		else if ((isalpha(pos[0]) && isdigit(pos[1]))  ||  (isdigit(pos[0]) && isalpha(pos[1]))){
				if (isdigit(pos[0])){
					if (isalpha(pos[1])){
						char temp= pos[0];
						pos[0]=pos[1];
						pos[1]=temp;
					}	
				}
				pos[0]=toupper(pos[0]);
				// per compilare postab serve A n
				char abc[3]="ABC";
				char n[3]="123";

				if (pos[0]==abc[0]){
					postab[0]=0; time-=1;
				}
				else if (pos[0]==abc[1]){
					postab[0]=1; time-=1;
				}
				else if (pos[0]==abc[2]){
					postab[0]=2; time-=1;
				}

				if (pos[1]==n[0]){
					postab[1]=0; time-=1;
				}
				else if (pos[1]==n[1]){
					postab[1]=1; time-=1;
				}
				else if (pos[1]==n[2]){
					postab[1]=2; time-=1;
				}

				if (tab[postab[1]][postab[0]]==1 && time==0){
					tab[postab[1]][postab[0]]=N;
				}else{time=3;}
		} 
		else{time=2;}
	}while(!(isalpha(pos[0]) && isdigit(pos[1]) && time==0));

	return 0;
}
int makemove(int** tab, char n, int round){
	char q='Q', x='X', o='O';
	int N;
	if (n==x)N=3;
	else if (n==o)N=5;

	if (winningmove(tab, N)){
		printf("\n(mossa 1)");
		return 0;}
	if (adjmove(tab, N)){
		printf("\n(mossa 2)");
		return 0;}
	if (centremove(tab, N)){
		printf("\n(mossa 3)");
		return 0;}
	if (oppAnglmove(tab, N)){
		printf("\n(mossa 4)");
		return 0;}
	if(anglmove(tab, N)){
		printf("\n(mossa 5)");
		return 0;}
	randmove(tab, N,round);
	printf("\n(mossa 6)");
	return 0;
}
void printcomputer(int i, int j,int** tab){
	char c;
	char xo;
	if (j==0){c='A';}
	else if (j==1){c='B';}
	else if (j==2){c='C';}
	if (tab[i][j]==3){xo= 'X';}else if(tab[i][j]==5){xo='O';}
	printf("Posizione scelta dal computer: ");
	if (xo=='X'){printf("\033[0;36m");
				printf("X ");
				printf("\033[0m");
				printf("in ");
				printf("\033[0;36m");
				printf("%c%d",c, ++i);
				printf("\033[0m");
	}
	else if(xo=='O'){printf("\033[1;31m");
				printf("O ");
				printf("\033[0m");
				printf("in ");
				printf("\033[0;31m");
				printf("%c%d",c, ++i);
				printf("\033[0m");
	}
}
int  winningmove(int** tab, int N){
	int priority[4][3]={{0,0,0},{0,0,0},{0,0,0},{0,0,0}};
	int counterW=0;
	for (int i = 0; i < 3; ++i){
		int rig = tab[i][0]*tab[i][1]*tab[i][2];	
		if (rig==25 || rig==9){
			for (int j = 0; j < 3; ++j){
				if (tab[i][j]==1){
					priority[0][1]=i;
					priority[0][2]=j;
					priority[0][0]=rig;
				}
			}
		}
	}
	for (int i = 0; i < 3; ++i){
		int col=tab[0][i]*tab[1][i]*tab[2][i];
		if (col==25 || col==9){
			for (int j = 0; j < 3; ++j){
				if (tab[j][i]==1){
					priority[1][1]=j;
					priority[1][2]=i;
					priority[1][0]=col;
				}
			}
		}
	}
	int check1 = tab[0][0]*tab[1][1]*tab[2][2];
	int check2 = tab[0][2]*tab[1][1]*tab[2][0];

	if (check1==25 || check1==9){
		for (int i = 0; i < 3; ++i){
			if (tab[i][i]==1){
				priority[2][1]=i;
				priority[2][2]=i;
				priority[2][0]=check1;
			}
		}
	}
	else if (check2==25 || check2==9){
		for (int i = 0; i < 3; i++) {
        	for (int j = 0; j < 3; j++) {
        	    if ((i + j) == 2){
        	       if (tab[i][j]==1){
        	       	priority[3][1]=i;
					priority[3][2]=j;
					priority[3][0]=check2;
        	    	}
       			}
    		}	
		}
	}
	int maxpriority[3]={0,0,0};
	for (int i = 0; i < 4; ++i){
		if ((priority[i][0])>maxpriority[0]){
			for (int j = 0; j < 3; ++j){
				maxpriority[j]=priority[i][j];
			}
		}
	}
	if (maxpriority[0]==N*N){
		tab[maxpriority[1]][maxpriority[2]]=N;
		printcomputer(maxpriority[2],maxpriority[1],tab);
		return 1;
		
	}
	else if (maxpriority[0]==25 || maxpriority[0]==9){
		tab[maxpriority[1]][maxpriority[2]]=N;
		printcomputer(maxpriority[2],maxpriority[1],tab);
		return 1;	
	}
	return 0;
}
int adjmove(int** tab, int N){
	int adj[2];
	for (int i = 0; i < 2; ++i){
		for (int j = 0; j < 2; ++j){
			int checkADJ=0;
			int possibl=0;
			for (int z = 0; z < 2; ++z){
				for(int t=0 ; t < 2 ;++t){
					if (tab[i+z][t+z]==N){
						checkADJ+=1;
					}
					else if (tab[i+z][t+z]==1){
						possibl++;
						adj[0]=i+z;
						adj[1]=t+z;
					}
				}
			}
			if (checkADJ==3 && possibl==1){
				tab[adj[0]][adj[1]]=N;
				printcomputer(adj[0],adj[1],tab);
				return 1;
			}

		}		
	}
	return 0;
}
int centremove(int** tab, int N){
	if (tab[1][1]==1){
		tab[1][1]=N;
		printcomputer(1,1,tab);
		return 1;
	}
	return 0;
}
int oppAnglmove(int** tab, int N){
	int checkopposite;
	for (int i = 0; i < 3; i+=2){
		for (int j = 0; j < 3; j+=2){
			if(tab[i][j]!=N && tab[i][j]!=1){
				for (int z = 0; z < 3; z+=2){
					for (int t = 0; t < 3; t+=2){
						if((z!=i) && (t!=j)){
							if (tab[z][t]==1){
								tab[z][t]=N;
								printcomputer(z,t,tab);
								return 1;
							}
						}
					}
				}
			}
		}
	}
	return 0;
}
int anglmove(int** tab, int N){	
	for (int i = 0; i < 3; i=+2){
		for (int j = 0; j < 3; j=+2){
			if(tab[i][j]==1){
				tab[i][j]=N;
				printcomputer(i,j,tab);
				return 1;
			}
		}
	}
	return 0;
}
void randmove(int** tab, int N, int round){
	int free[9][2];
	int counter=0;
	for (int i = 0; i < 3; ++i){
		for (int j = 0; j < 3; ++j)
		{
			if (tab[i][j]==1){
				free[counter][0]=i;
				free[counter][1]=j;
				counter++;
			}
		}
	}
	srand(time(NULL));
	int r= rand()%counter+0;
	tab[free[r][0]][free[r][1]]=N;
	printcomputer(free[r][0],free[r][1],tab);
}