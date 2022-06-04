#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int baslangic[2];
int bitis[2];
int maze[50][50];
int puan=0;

void delay(int number_of_seconds){

    int milli_seconds = number_of_seconds;
    clock_t start_time = clock();
    while (clock() < start_time + milli_seconds);
    
}

void puanEksi(int x, int y){
	if(maze[x+1][y]==4 && maze[x-1][y]==0 && maze[x][y+1]==0 && maze[x][y-1]==0)
		puan -= 5;
	else if(maze[x+1][y]==0 && maze[x-1][y]==4 && maze[x][y+1]==0 && maze[x][y-1]==0)
		puan -= 5;
	else if(maze[x+1][y]==0 && maze[x-1][y]==0 && maze[x][y+1]==4 && maze[x][y-1]==0)
		puan -= 5;
	else if(maze[x+1][y]==0 && maze[x-1][y]==0 && maze[x][y+1]==0 && maze[x][y-1]==4)
		puan -= 5;
}

void mazeYazdir(){
	
	delay(300);
	for(int j=0;j<31;j++){
		for(int i=0;i<43;i++)
			if(maze[i][j]==0)
				printf("*");
			else if(maze[i][j]==1)	
				printf(" ");
			else if(maze[i][j]==2)	
				printf("b");
			else if(maze[i][j]==3)	
				printf("c");
			else if(maze[i][j]==4)	
				printf("+");
			else if(maze[i][j]==5)	
				printf("0");
				
		printf("\n");
	}	
	printf("\npuan:%d",puan);
	printf("\n");
	printf("\n");
}

int dfs(int x, int y){
	
	mazeYazdir();
	
	if(x==bitis[0] && y==bitis[1])
		exit(1);
	
	puanEksi(x,y);

	if(maze[x+1][y]==1 || maze[x+1][y]==3 || maze[x+1][y]==5){
		
		if(maze[x+1][y]==5)
			puan+=10;
			
		maze[x+1][y]=4;
		dfs(x+1,y);
		maze[x+1][y]=1;

	
	}

	if(maze[x][y-1]==1 || maze[x][y-1]==3 || maze[x][y-1]==5){
			
		if(maze[x][y-1]==5)
			puan+=10;
			
		maze[x][y-1]=4;
		dfs(x,y-1);
		maze[x][y-1]=1;

	}
	
	if(maze[x-1][y]==1 || maze[x-1][y]==3 || maze[x-1][y]==5){
		
		if(maze[x-1][y]==5)
			puan+=10;
			
		maze[x-1][y]=4;
		dfs(x-1,y);	
		maze[x-1][y]=1;

	}
	
	if(maze[x][y+1]==1 || maze[x][y+1]==3 || maze[x][y+1]==5){
		
		if(maze[x][y+1]==5)
			puan+=10;
			
		maze[x][y+1]=4;
		dfs(x,y+1);
		maze[x][y+1]=1;

	}
	
	mazeYazdir();
	
}

int matriseDonustur(){
	
	FILE *fptr;
	char satir1[50];
	int i,j=0;
	
   	if ((fptr = fopen("maze.txt","r")) == NULL){
       	printf("Error! opening file");
       	return 0;
   	}
	srand(time(NULL));
	while(fread(satir1, 44, 1, fptr) != NULL){
		for(i=0;i<43;i++){
			if(satir1[i]=='+' || satir1[i]=='-' || satir1[i]=='|')
				maze[i][j]=0;
			else if(satir1[i]=='b'){
				maze[i][j]=2;
				baslangic[0]=i;
				baslangic[1]=j;
			}
			else if(satir1[i]=='c'){
				maze[i][j]=3;
				bitis[0]=i;
				bitis[1]=j;
			}
			else{
				if(rand() % 20==0)
					maze[i][j]=5;
				else
					maze[i][j]=1;
			}	
		}
		j++;
	}
	
	fread(satir1, 44, 1, fptr);
	for(i=0;i<43;i++)
		if(satir1[i]=='+' || satir1[i]=='-' || satir1[i]=='|')
			maze[i][j]=0;
	return 1;		

}

int main(){
	matriseDonustur();
	dfs(baslangic[0],baslangic[1]);
	return 0;
	
}