#pragma once
#include <stdio.h>
#include <windows.h>
#include <string.h>
#define filename "database.txt"

struct node 
{
	struct node *prev;
	char nama[16];
	int score;
}*head = NULL, *tail = NULL;

void push(char *name, int new_data) 
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

void sort (){
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

void display (){
	struct node *display;
	display = head;
	
	if (head == NULL){
		printf ("Empty.");
	}
	else {
		while (display != NULL){
			printf ("%s\t", display->nama);
			printf ("%d\n", display->score);
			display = display->prev;
		}
	}
}

void eksport()
{
	FILE *fp;
	fp = fopen(filename, "w");
	struct node *ptr = head;
	
	while(ptr != NULL)
	{
		fprintf(fp, "%s|", ptr->nama);
		fprintf(fp, "%d\n", ptr->score);
		ptr = ptr->prev;
	}
	
	fclose(fp);
}

void import()
{
	FILE *fp;
	fp = fopen(filename, "r");
	struct node import;

	char temp[32], *nama, *score;
	
	fscanf(fp, "%s", temp);
	//Pisahkan
	
	score = strtok(temp, "|");
	score = strtok(NULL, "|");
	nama = strtok(temp, "\n");
	
	fclose(fp);
}
