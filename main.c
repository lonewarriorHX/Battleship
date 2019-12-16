#include <stdio.h>
#include <windows.h>
#include <string.h>
#include <stdlib.h>
#include "std.h"
#include "battleship.c"
#pragma comment(lib, "winmm.lib")
#include<MMsystem.h>


void choose();
void logos();
int a=12, b=15;
char name[100];

	int i,j;
    int key=0;
    int posisi=1;
    char jwb[1], sectfalse, sectfalse2, ser;
struct node 
{
	struct node *prev;
	char nama[16];
	int score;
}*head = NULL, *tail = NULL;

void masukkannama(char *name, int new_data) 
{ 
	struct node *data;
    data = (struct node*) malloc(sizeof(struct node)); 
    strcpy (data->nama, name);
    data->score = new_data;
    
    if (head == NULL){
		data->prev = NULL;	
	}
	else {
		data->prev = head;
	}
	head = data;
} 

void urutdata (){
	struct node *temp, *temp2;
	temp = (struct node*)malloc(sizeof(struct node));
	temp2 = (struct node*)malloc(sizeof(struct node));	
	
	temp = head;	
	temp2 = head->prev;
	
	if(temp->score < temp2->score)
	{
		//do 
	}
}
    
int lead()
{
	system("cls");
	char buffer[1024] ;
    char *record,*line;
    int i=0,j=0;
    int mat[100][100];
    int ny=17;
    FILE *fstream;
    FILE *fp;

seq1 :
    fstream = fopen("scoreboard.csv","r");
    if(fstream == NULL)   {
        goto noscore;
    }
    else {
        goto checker;
    }
checker :

            //OPEN BORDER

	fp=fopen("border-leaderboard.txt", "r");
	do
    {
		ser=getc(fp);
		printf("%c", ser);
	}
	while(ser!=EOF);
	fflush(stdin);

        //OPEN FILE EASY

	    fstream = fopen("scoreboard.csv","r");

    	while((line=fgets(buffer,sizeof(buffer),fstream))!=NULL)
    {
		record = strtok(line,";");
		while(record != NULL)
			{
             gotoxy(30, ny);
			 printf("Name, score : %s",record) ;
			 ny = ny + 1;
            //here you can put the record into the array as per your requirement.
			 mat[i][j++] = atoi(record) ;
			 record = strtok(NULL,";");
			}
		++i ;
	}


	gotoxy(0,40);
	system("pause");
	choose();

noscore :

	            //BELUM ADA SKOR TERCETAK

    if(fstream == NULL)   {
    gotoxy(50,19);
    printf("   <<======================================================>>\n");
	gotoxy(50,21);
	printf("                 Belum ada yang Mencetak Skor");
	gotoxy(50,23);
	printf("      Jadilah pencetak Skor pertama dalam Test Your Logic!");
    gotoxy(50,25);
    printf("   <<======================================================>>\n\n");
    gotoxy(50,27);
    system ("pause");
    choose();
    }

}

void tutorial(){
	system("cls");
	printf("\n\n\n\tBatteShip is a game that require your skill and a little bit of luck...\n\n");
	
	printf("\tbefore you play, you will be given 3 choices.\n");
	printf("\tyou can select small size, which has 3x3 square box\n");
	printf("\tor medium size, with 5x5 square box.\n");
	printf("\tor large size , with 7x7 square\n\n");
	
	printf("\tand you can select the level,\n");
	printf("\teasy level, medium level or the hardest one. \n");
	printf("\tin easy level the winning percentage is almost 100%, \n");
	printf("\tin hard level, the winning percentage is below 25%,\n");
	printf("\tso i suggest to take the medium level,\n\n");
	
	printf("\tIts a simple game, by the way. \n");
	printf("\tyou can choose the coordinate to shot.\n");
	printf("\tif there was a ship, you hit it, but if there wasn't, you missed.\n");
	printf("\tthe harder the level is, the less chance to guess.\n");
	printf("\tgood luck. Have fun...\n");
	int x4; double y4;
	char salam21[]=    "\tEntering game in 3..2..1..\n\t[Press Any Key to Continue]";



   printf("\n\n\n");
   for(x4=0; salam21[x4]!=NULL; x4++)
   {
     printf("%c",salam21[x4]);
     for(y4=0; y4<=9999999; y4++)
      {
      }
   }
	getch();
	system("cls");
	choose();
	
}
void choose(){
	system("cls");
	logos();
	int pil=0;
	int keyPressed=0;
	    boxFill(40,20,8,2,0);
       boxFill(52,20,8,2,0);
       boxFill(64,20,8,2,0);
    printf("\t\t\t\t\t PLAY \t  LEADERBOARD\tTUTORIAL");
    printf("\n\n\t\t\t\tWelcome, %s , Do you already know about battleship?\n\t\t\t\tor you want to know more??(< v >)", name);
    
    while (keyPressed !=13){
    	keyPressed = getch();
    if (keyPressed==75){
    	system("cls");
    	logos();
        boxFill(40,20,8,2,a);
       boxFill(52,20,8,2,0);
       boxFill(64,20,8,2,0);
    printf("\t\t\t\t\t PLAY \t  LEADERBOARD\tTUTORIAL");
    printf("\n\n\t\t\t\tWelcome, %s , Do you already know about battleship?\n\t\t\t\tor you want to know more??(< v >)", name);
    pil=1;
	}
	else if (keyPressed==80 || keyPressed==72){
		system("cls");
		logos();
		boxFill(40,20,8,2,0);
       boxFill(52,20,8,2,a);
       boxFill(64,20,8,2,0);
    printf("\t\t\t\t\t PLAY \t  LEADERBOARD\tTUTORIAL");
    printf("\n\n\t\t\t\tWelcome, %s , Do you already know about battleship?\n\t\t\t\tor you want to know more??(< v >)", name);
    pil=2;
	}
	else if (keyPressed==77 ){
		system("cls");
		logos();
		boxFill(40,20,8,2,0);
       boxFill(52,20,8,2,0);
       boxFill(64,20,8,2,a);
    printf("\t\t\t\t\t PLAY \t  LEADERBOARD\tTUTORIAL");
    printf("\n\n\t\t\t\tWelcome, %s , Do you already know about battleship?\n\t\t\t\tor you want to know more??(< v >)", name);
    pil=3;
	}
	
	else if(keyPressed==13){
		if (pil==3){
		tutorial();
		}
		else if (pil==2){
		lead();
		}
		else if (pil==1){
    	system("cls");
    	fflush(stdin);
   		PlaySound(TEXT("bgmm.wav"), NULL, SND_ASYNC | SND_LOOP);
   		main2();
   }
	
}
/* printf("\n\n\t\t\t\tWelcome, %s , Do you already know about battleship?\n\t\t\t\tor you want to know more??", name); 
	    int yes = 0;
	scanf("%d", &yes);
	if (yes==1){
		tutorial();
	}
	else if (yes==2){
		lead();
	}
	else{
    system("cls");
    	fflush(stdin);
   	PlaySound(TEXT("bgmm.wav"), NULL, SND_ASYNC | SND_LOOP);
   	*/
}
}

void logos(){    
	boxBorder(33,2,34,1,a,1,1);
    boxBorder(71,2,8,1,a,1,1);
    
    boxBorder(33,3,2,1,a,1,1);
    boxBorder(39,3,5,1,a,1,1);
    boxBorder(46,3,3,1,a,1,1);
    boxBorder(49,3,18,1,a,1,1);
    boxBorder(71,3,2,1,a,1,1);
    
    boxBorder(33,4,16,1,a,1,1);
     boxBorder(52,4,2,1,a,1,1);
     boxBorder(60,4,2,1,a,1,1);
     boxBorder(65,4,2,1,a,1,1);
     boxBorder(71,4,8,1,a,1,1);
     
    boxBorder(33,5,2,1,a,1,1);
    boxBorder(39,5,5,1,a,1,1);
    boxBorder(46,5,3,1,a,1,1);
    boxBorder(52,5,2,1,a,1,1);
     boxBorder(60,5,2,1,a,1,1);
     boxBorder(65,5,2,1,a,1,1);
     boxBorder(71,5,2,1,a,1,1);
     
    boxBorder(33,6,11,1,a,1,1);
    boxBorder(46,6,3,1,a,1,1);
    boxBorder(52,6,2,1,a,1,1);
     boxBorder(60,6,2,1,a,1,1);
     boxBorder(65,6,14,1,a,1,1);
     
     boxBorder(33,8,16,2,b,1,1);
     boxBorder(53,8,4,2,b,1,1);
     boxBorder(60,8,3,2,b,1,1);
     boxBorder(66,8,12,2,b,1,1);
     
     boxBorder(33,10,4,2,b,1,1);
     boxBorder(45,10,4,2,b,1,1);
     boxBorder(53,10,4,2,b,1,1);
     boxBorder(60,10,3,2,b,1,1);
     boxBorder(66,10,4,2,b,1,1);
     boxBorder(74,10,4,2,b,1,1);
     
     boxBorder(33,12,24,2,b,1,1);
     boxBorder(60,12,3,2,b,1,1);
     boxBorder(66,12,12,2,b,1,1);
     
    boxBorder(41,14,8,2,b,1,1);
     boxBorder(53,14,4,2,b,1,1);
     boxBorder(60,14,3,2,b,1,1);
     boxBorder(66,14,4,2,b,1,1);

	 boxBorder(33,16,16,2,b,1,1);
     boxBorder(53,16,4,2,b,1,1);
     boxBorder(60,16,3,2,b,1,1);
     boxBorder(66,16,4,2,b,1,1);
}

int main(){
system("COLOR 30");

    
 for(i=0;i<3;i++){
 	PlaySound(TEXT("Explosion.wav"), NULL, SND_ASYNC);
    boxBorder(33,2,34,1,a,1,1);
    boxBorder(71,2,8,1,a,1,1);
    
    boxBorder(33,3,2,1,a,1,1);
    boxBorder(39,3,5,1,a,1,1);
    boxBorder(46,3,3,1,a,1,1);
    boxBorder(49,3,18,1,a,1,1);
    boxBorder(71,3,2,1,a,1,1);
    
    boxBorder(33,4,16,1,a,1,1);
     boxBorder(52,4,2,1,a,1,1);
     boxBorder(60,4,2,1,a,1,1);
     boxBorder(65,4,2,1,a,1,1);
     boxBorder(71,4,8,1,a,1,1);
     
    boxBorder(33,5,2,1,a,1,1);
    boxBorder(39,5,5,1,a,1,1);
    boxBorder(46,5,3,1,a,1,1);
    boxBorder(52,5,2,1,a,1,1);
     boxBorder(60,5,2,1,a,1,1);
     boxBorder(65,5,2,1,a,1,1);
     boxBorder(71,5,2,1,a,1,1);
     
    boxBorder(33,6,11,1,a,1,1);
    boxBorder(46,6,3,1,a,1,1);
    boxBorder(52,6,2,1,a,1,1);
     boxBorder(60,6,2,1,a,1,1);
     boxBorder(65,6,14,1,a,1,1);
     
     boxBorder(33,8,16,2,b,1,1);
     boxBorder(53,8,4,2,b,1,1);
     boxBorder(60,8,3,2,b,1,1);
     boxBorder(66,8,12,2,b,1,1);
     
     boxBorder(33,10,4,2,b,1,1);
     boxBorder(45,10,4,2,b,1,1);
     boxBorder(53,10,4,2,b,1,1);
     boxBorder(60,10,3,2,b,1,1);
     boxBorder(66,10,4,2,b,1,1);
     boxBorder(74,10,4,2,b,1,1);
     
     boxBorder(33,12,24,2,b,1,1);
     boxBorder(60,12,3,2,b,1,1);
     boxBorder(66,12,12,2,b,1,1);
     
    boxBorder(41,14,8,2,b,1,1);
     boxBorder(53,14,4,2,b,1,1);
     boxBorder(60,14,3,2,b,1,1);
     boxBorder(66,14,4,2,b,1,1);

	 boxBorder(33,16,16,2,b,1,1);
     boxBorder(53,16,4,2,b,1,1);
     boxBorder(60,16,3,2,b,1,1);
     boxBorder(66,16,4,2,b,1,1);
         printf("\n\n\t\t\t\t\tBattleship Ver 2.1.1");	
     sleep(2);

     system("cls");
     sleep(0);
 }
 PlaySound(TEXT("Explosion.wav"), NULL, SND_ASYNC);
	logos();
	 
    printf("\n");
    PlaySound(TEXT("game.wav"), NULL, SND_ASYNC | SND_LOOP);
    int x2; double y2;
	char salam[]=    "\t\t\t\t\tBattleship Ver 2.1.1\n\n	`\t\t\t\tCreated by, Hanvey Xavero & Helmi Arrazy\n\t\t\t\t\tPress Enter to continue...";


	
   printf("\n\n\n");
   for(x2=0; salam[x2]!=NULL; x2++)
   {
     printf("%c",salam[x2]);
     for(y2=0; y2<=9999999; y2++)
      {
      }
   }
	fflush(stdin);
	
    getch();
    system("cls");
    
    logos();
        int x3; double y3;
	char salam2[]=    "\n\t\t\t\tInsert Your Name Here: \n\t\t\t\t";



   printf("\n\n\n");
   for(x3=0; salam2[x3]!=NULL; x3++)
   {
     printf("%c",salam2[x3]);
     for(y3=0; y3<=9999999; y3++)
      {
      }
   }
    scanf("%s", &name);
    system("cls");
    
//printf("okay");

	choose();   
        return 0;
}
