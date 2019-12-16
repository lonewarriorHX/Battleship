#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <time.h>
#pragma comment(lib, "winmm.lib")
#include<MMsystem.h>
#include <conio.h>
#include <stdbool.h>
#define NROWS     4
#define NCOLLUMNS 4
//COLOR DEFINITION
#define BLACK 0
#define BLUE 1
#define GREEN 2
#define LLBLUE 3
#define RED 4
#define PURPLE 5
#define YELLOW 6
#define LGREY 7
#define GREY 8
#define LBLUE 9
#define LGREEN 10
#define LLLBLUE 11
#define PINK 12
#define LPURPLE 13
#define LYELLOW 14
#define WHITE 15

	int score;
void setRes(const int pX, const int pY);
COORD setc(int x, int y);
typedef struct boxID_struct {
	COORD curs;
	int sizeX;
	int sizeY;
	int type;
	int color;
} boxID;


#define COLORFORG 1
#define COLORBACK 2
int getconsolecolor(int colortype);
COORD c(int x, int y);
#define PNULL -1
void printSuper(COORD cursor, int ForgC, int BackC, const char* val, ...);

#define BOX_LINES 1
#define BOX_FILL 2
boxID makebox(COORD curs, int sizeX, int sizeY, int color, int type) ;
#define DRAW 1
#define ERASE 0
#define UPDATE 2
boxID loopForBox(int state, boxID box_ID) ;
#define BOX_SETCOLOR 1
#define BOX_SETSIZEX 2
#define BOX_SETSIZEY 3
#define BOX_SETCURSOR 4
#define BOX_SETTYPE 5
boxID box(int state, boxID box_ID,...) ;



void gambar();
char name[100];

COORD c(int x, int y){
	COORD curs;
	curs.X = x;
	curs.Y = y;
	return curs;
}
void printSuper(COORD cursor, int ForgC, int BackC, const char* val, ...) {
	CONSOLE_SCREEN_BUFFER_INFO psBI;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &psBI);
	if (cursor.X == -1) {
		cursor.X = psBI.dwCursorPosition.X;
	}
	if (cursor.Y == -1) {
		cursor.Y = psBI.dwCursorPosition.Y;
	}
	setc(cursor.X,cursor.Y);
	va_list arg_list;
	int my_arg;
	va_start(arg_list, val);
	int charlen = strlen(val);
	WORD wOldColorAttrs;
	wOldColorAttrs = psBI.wAttributes;
	if (ForgC == PNULL && BackC != PNULL) {
		WORD dump = wOldColorAttrs >> 4 << 4;
		dump = wOldColorAttrs - dump;
		WORD wColor = ((BackC & 0x0F) << 4 + dump);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	}
	else if (BackC == PNULL && ForgC != PNULL) {
		WORD wColor = ((wOldColorAttrs >> 4) << 4 + (ForgC & 0x0F));
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	}
	else if (ForgC != PNULL && BackC != PNULL) {
		WORD wColor = ((BackC & 0x0F) << 4) + (ForgC & 0x0F);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wColor);
	}
	for (my_arg = 0; my_arg < charlen; my_arg++) {
		if (val[my_arg] == '%') {
			int r = 0;
			char value[16];
			while (my_arg < charlen) {
				value[r] = val[my_arg];
				value[r + 1] = 0;
				if (val[my_arg] == 'd' || val[my_arg] == 'c' || val[my_arg] == 's') {
					printf(value, va_arg(arg_list, int));
					break;
				}
				else if (val[my_arg] == 'f') {
					printf(value, va_arg(arg_list, double));
					break;
				}
				my_arg++; r++;
			}
		}
		else if (val[my_arg] != '%')printf("%c", val[my_arg]);
	}
	va_end(arg_list);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), wOldColorAttrs);
}

int getconsolecolor(int colortype) {
	CONSOLE_SCREEN_BUFFER_INFO psBI;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &psBI);
	if (colortype == COLORFORG) {
		WORD dump = psBI.wAttributes >> 4 << 4;
		dump = psBI.wAttributes - dump;
		return (int)dump;
	}
	else if (colortype == COLORBACK) {
		return (int)psBI.wAttributes >> 4;
	}
}
COORD setc(int x, int y) {
	COORD cursor;
	cursor.X = x;
	cursor.Y = y;
	CONSOLE_SCREEN_BUFFER_INFO psBI;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &psBI);
	COORD pos;
	pos.X = cursor.X; pos.Y = cursor.Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
	return pos;
}
boxID makebox(COORD curs, int sizeX, int sizeY, int color, int type) {
	boxID myBox;
	myBox.curs = curs;
	myBox.sizeX = sizeX;
	myBox.sizeY = sizeY;
	myBox.color = color;
	myBox.type = type;
	return myBox;
}

boxID loopForBox(int state, boxID box_ID) {
	if (box_ID.type == BOX_LINES) {
		int backg = getconsolecolor(GREY);
		int forg;
		if (state == DRAW) {
			forg = box_ID.color;
		}
		else if (state == ERASE) {
			forg = backg;
		}
		printSuper(box_ID.curs, forg, backg, "%c", 218);
		int a; for (a  = box_ID.curs.X; a < box_ID.curs.X + box_ID.sizeX; a++) printSuper(c(PNULL, PNULL), forg, backg, "%c", 196);
		printSuper(c(box_ID.curs.X + box_ID.sizeX, box_ID.curs.Y), forg, backg, "%c", 191);
		for (a  = box_ID.curs.Y + 1; a < box_ID.curs.Y + box_ID.sizeY; a++) {
			printSuper(c(box_ID.curs.X, a), forg, backg, "%c", 179);
			printSuper(c(box_ID.curs.X + box_ID.sizeX, a), forg, backg, "%c", 179);
		}
		printSuper(c(box_ID.curs.X, box_ID.curs.Y + box_ID.sizeY), forg, backg, "%c", 192);
		for (a  = box_ID.curs.X; a < box_ID.curs.X + box_ID.sizeX; a++) printSuper(c(PNULL, PNULL), forg, backg, "%c", 196);
		printSuper(c(box_ID.curs.X + box_ID.sizeX, box_ID.curs.Y + box_ID.sizeY), forg, backg, "%c", 217);
	}
	else if (box_ID.type == BOX_FILL) {
		int backg;
		if (state == DRAW) backg = box_ID.color;
		else backg = getconsolecolor(GREY);
		int i; for ( i  = 0; i < box_ID.sizeY; i++) {
			int j; for ( j = 0; j < box_ID.sizeX; j++) {
				printSuper(c((box_ID.curs.X + j), (box_ID.curs.Y + i)), backg, backg, " ");
			}
		}
	}
	return box_ID;
}

boxID box(int state, boxID box_ID,...) {
	if (state == UPDATE) {
		int eraseState = FALSE;
		boxID box_ID_Old = box_ID;
		va_list xcols;
		va_start(xcols, box_ID);
		int a;
		for (a = 0; a < 5; a++) {
			int Ttype = va_arg(xcols, int);
			if (Ttype < 1 || Ttype > 5) break;
			else if (Ttype == BOX_SETCOLOR) {
				box_ID.color = va_arg(xcols, int);
				if (eraseState != TRUE) eraseState = FALSE;
			}
			else if (Ttype == BOX_SETCURSOR) {
				box_ID.curs = va_arg(xcols, COORD);
				eraseState = TRUE;
			}
			else if (Ttype == BOX_SETSIZEX) {
				box_ID.sizeX = va_arg(xcols, int);
				if ((box_ID.sizeX < box_ID_Old.sizeX) && eraseState == FALSE) {
					eraseState = TRUE;
				}
			}
			else if (Ttype == BOX_SETSIZEY) {
				box_ID.sizeY = va_arg(xcols, int);
				if ((box_ID.sizeY < box_ID_Old.sizeY) && eraseState == FALSE) {
					eraseState = TRUE;
				}
			}
			else if (Ttype == BOX_SETTYPE) {
				box_ID.type = va_arg(xcols, int);
				if ((box_ID.type < box_ID_Old.type) && eraseState == FALSE) {
					eraseState = TRUE;
				}
			}
		}
		va_end(xcols);
		if(eraseState != FALSE) loopForBox(ERASE, box_ID_Old);
		loopForBox(DRAW, box_ID);
	}
	else {
		loopForBox(state, box_ID);
	}
	return box_ID;
}


void gambar(){
	int a=10, b=5, c=15;
	int i,j;
    int key=0;
    int posisi=1;
    boxBorder(3,2,34,1,a,1,1);
    boxBorder(41,2,8,1,a,1,1);
    
    boxBorder(3,3,2,1,a,1,1);
    boxBorder(9,3,5,1,a,1,1);
    boxBorder(16,3,3,1,a,1,1);
    boxBorder(19,3,18,1,a,1,1);
    boxBorder(41,3,2,1,a,1,1);
    
    boxBorder(3,4,16,1,a,1,1);
     boxBorder(22,4,2,1,a,1,1);
     boxBorder(30,4,2,1,a,1,1);
     boxBorder(35,4,2,1,a,1,1);
     boxBorder(41,4,8,1,a,1,1);
     
    boxBorder(3,5,2,1,a,1,1);
    boxBorder(9,5,5,1,a,1,1);
    boxBorder(16,5,3,1,a,1,1);
    boxBorder(22,5,2,1,a,1,1);
     boxBorder(30,5,2,1,a,1,1);
     boxBorder(35,5,2,1,a,1,1);
     boxBorder(41,5,2,1,a,1,1);
     
    boxBorder(3,6,11,1,a,1,1);
    boxBorder(16,6,3,1,a,1,1);
    boxBorder(22,6,2,1,a,1,1);
     boxBorder(30,6,2,1,a,1,1);
     boxBorder(35,6,14,1,a,1,1);
     
     boxBorder(53,2,16,1,b,1,1);
     boxBorder(73,2,4,1,b,1,1);
     boxBorder(80,2,3,1,b,1,1);
     boxBorder(86,2,12,1,b,1,1);
     
     boxBorder(53,3,4,1,b,1,1);
     boxBorder(65,3,4,1,b,1,1);
     boxBorder(73,3,4,1,b,1,1);
     boxBorder(80,3,3,1,b,1,1);
     boxBorder(86,3,4,1,b,1,1);
     boxBorder(94,3,4,1,b,1,1);
     
     boxBorder(53,4,24,1,b,1,1);
     boxBorder(80,4,3,1,b,1,1);
     boxBorder(86,4,12,1,b,1,1);
     
    boxBorder(61,5,8,1,b,1,1);
     boxBorder(73,5,4,1,b,1,1);
     boxBorder(80,5,3,1,b,1,1);
     boxBorder(86,5,4,1,b,1,1);

	 boxBorder(53,6,16,1,b,1,1);
     boxBorder(73,6,4,1,b,1,1);
     boxBorder(80,6,3,1,b,1,1);
     boxBorder(86,6,4,1,b,1,1);
	
}

void buff_clr(void)
{
    char junk;
    do{
        junk=getchar();
    }while(junk!='\n');
}
struct coord
{
    int y;
    int x;

}coords;

void arrowHere(int realposition, int arrowposition){

			if (realposition == arrowposition){
				printf ("\n\n>>>");
			}
			else {
				printf ("\n\n   ");
			}
	}

void arrowHere1(int realposition1, int arrowposition1){

			if (realposition1 == arrowposition1){
				printf ("\n\n>>>");
			}
			else {
				printf ("\n\n   ");
			}
	}
	
int randgen(int **ships_ptr,int n)
{
    int i,j,count=0;
    srand((unsigned)time(NULL));
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            ships_ptr[i][j]=rand()%2;
            if(ships_ptr[i][j]==1)
            {
                count++;
            }
        }
    }
    return count;
}
void draw_gui(char **pseudo_gui_ptr,int n)
{
    int i,j;
    //int x = 30;
	//int y = 10;
    //setc(x,y);
    //box(DRAW,(makebox(c(29,9),50,2,BLUE,BOX_LINES)));
	
    pseudo_gui_ptr[0][0]=' ';
    for(i=1;i<(n+1);i++)
    {
        pseudo_gui_ptr[0][i]=i+48;
        pseudo_gui_ptr[i][0]=i+48;
    }

    for(i=1;i<(n+1);i++)
    {
        for(j=1;j<(n+1);j++)
        {
            pseudo_gui_ptr[i][j]='+';
        }
    }
}


void battle(int **ships_ptr, char **pseudo_gui_ptr,int n, struct coord x,int* count,int* miss)
{

    int i,j;

     for(i=0;i<n;i++)
        {
            for(j=0;j<n;j++)
            {
                if(x.x-1 == i && x.y-1 == j)
                {
                    if(ships_ptr[i][j]==1)
                    {
                        if(pseudo_gui_ptr[i+1][j+1]=='O')
                        {
                            printf("\nYou've already uncovered this field!\n");
                            break;
                        }
                        PlaySound(TEXT("Explosion.wav"), NULL, SND_ASYNC);
                        //PlaySound(TEXT("bgmm.wav"), NULL, SND_ASYNC | SND_LOOP);
                        printf("\nA SHIP WAS HIT!\n\n");
                        box(DRAW,(makebox(c(29,9),50,2,BLUE,BOX_LINES)));
                        printf("\n");
                        pseudo_gui_ptr[i+1][j+1]='O';
                        (*count)--;
                    }
                    else
                    {
                        if(pseudo_gui_ptr[i+1][j+1]=='X')
                        {
                            printf("\nYou've already uncovered this field!\n\n");
                            break;
                        }
                        PlaySound(TEXT("water.wav"), NULL, SND_ASYNC);
                        //PlaySound(TEXT("bgmm.wav"), NULL, SND_ASYNC | SND_LOOP);
                        printf("\nSORRY SIR, WE JUST MISSED!\n\n");
                        box(DRAW,(makebox(c(29,9),50,2,BLUE,BOX_LINES)));
                        printf("\n");
                        pseudo_gui_ptr[i+1][j+1]='X';
                        (*miss)++;
                    }

                }
            }
        }


}


void result(char **pseudo_gui_ptr,int n)
{
    int i,j;

    for(i=0;i<(n+1);i++)
    {
        for(j=0;j<(n+1);j++)
        {
        	printf("\t\t");
            printf("%6c",pseudo_gui_ptr[i][j]);
        }
        printf("\n\n");
    }
}


int main2(){

  SetConsoleTextAttribute (GetStdHandle (STD_OUTPUT_HANDLE),3); 
   int **ships;
   char **pseudo_gui;
   int i,j;
   int n;
   char switch_size,switch_difficulty;
   int difficulty=0;
   int shipcount=0;
   int x_count=0;


   
   		int pil = 1;
		int keyPressed = 0;

		#define MAX 3
		#define MIN 1

	while (keyPressed !=13){
			
			system("cls");
			gambar();
   			printf("\t\t\t\t\tBattle Ship Ver 2.1.1");
   			printf("\n\t\tChoose size:");
			arrowHere (1,pil); printf ("1.Small");
			arrowHere (2,pil); printf ("2.Medium");
			arrowHere (3,pil); printf ("3.Large");

			keyPressed = getch();

		if (keyPressed == 80 && pil != MAX ){
			pil++;
		}
		else if (keyPressed == 72 && pil != MIN){
			pil--;
		}
		else {
			pil == pil;
		}
	}
	
	if (pil==1){
		n=3;
	}
	
	else if (pil==2){
		n=5;
	}
	
	else if (pil==3){
		n=8;
	}
	
//s	PlaySound(TEXT("D:\\latian proglan sem\\projek akhit\\Lose.wav"), NULL, SND_ASYNC);
   
  	 	int pil1 = 1;
		int keyPressed1 = 0;

		#define MAX 2
		#define MIN 1

	while (keyPressed1 !=13){
		
			
			system("cls");
			gambar();
   			printf("\t\t\t\t\tBattle Ship Ver 2.1.1");
   			 printf("\n\t\tChoose difficulty :");
			arrowHere1 (1,pil1); printf ("1.Easy");
			arrowHere1 (2,pil1); printf ("2.Hard");

			keyPressed1 = getch();

		if (keyPressed1 == 80 && pil1 != MAX ){
			pil1++;
		}
		else if (keyPressed1 == 72 && pil1 != MIN){
			pil1--;
		}
		else {
			pil1 == pil1;
		}
	}
	
	if (pil1==1){
		difficulty=(n*2)-2;
	}
	
	else if (pil1==2){
		difficulty=(n/2);
	}


   ships=(int**)malloc(n*sizeof(int*));

   for(i=0;i<n;i++)
   {
       ships[i]=(int*)malloc(n*sizeof(int));
   }

   pseudo_gui=(char**)malloc((n+1)*sizeof(char*));

   for(i=0;i<(n+1);i++)
   {
       pseudo_gui[i]=(char*)malloc((n+1)*sizeof(char));
   }

   shipcount=randgen(ships,n);

   printf("\n\n\t\t\tShips to get destroyed:%d",shipcount);
   printf("\n\t\t\tMissile Missed Allowed: %d\n\n",difficulty);

   draw_gui(pseudo_gui,n);
   result(pseudo_gui,n);

   while(shipcount!=0 && x_count!=difficulty)
   {

   printf("\nEnter coordinates (row,column):");
   scanf("%d,%d",&coords.x,&coords.y);
   buff_clr();
   
   system("cls");
	gambar();
   battle(ships,pseudo_gui,n,coords,&shipcount,&x_count);
   result(pseudo_gui,n);

   printf("\t\t\tShips to get destroyed:%d",shipcount);
   printf("\n\t\t\tMissile Missed Allowed(out of %d): %d\n\n",difficulty,x_count);

   }
   if(shipcount==0)
   {
       printf("\nWinner!\n\n");
       PlaySound(TEXT("bgm-win.wav"), NULL, SND_ASYNC);
      FILE *fp;
    char str[MAXCHAR];
    char* filename = "win.txt";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);
       
         FILE *out=fopen("scoreboard.csv","a");
        fprintf(out,"%s,%d\n",name, difficulty*100);
        fclose(out);
         printf("%s won!!, score = %d", name, difficulty*100);
         score = difficulty*100;
         getch();
   }
   else if(x_count==difficulty)
   {
       printf("\nYou Lose!\n\n");
       PlaySound(TEXT("Lose.wav"), NULL, SND_ASYNC);
    FILE *fp;
    char str[MAXCHAR];
    char* filename = "fail.txt";
 
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf("Could not open file %s",filename);
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
    printf("%s", str);
    fclose(fp);
    
      FILE *out=fopen("scoreboard.csv","a");
        fprintf(out,"%s,%d\n",name, difficulty*10);
        printf("%s failed, score = %d", name, difficulty*10);
        score = difficulty*10;
        fclose(out);
       getch();
   }


  return 0;
}
