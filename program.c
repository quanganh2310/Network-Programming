#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct node {
	char userName[20];
	char pass[20];
	int status;
	struct node *next;
};

typedef struct node account;

account *head = NULL;

void insertAccount(char *userName, char *pass, int status) {
	account *temp = (account *)malloc(sizeof (account));
	strcpy(temp->userName, userName);
	strcpy(temp->pass,pass);
	temp->status = status;
	temp->next= head;
	head = temp;
}

account *search(char *userName) {
	account *current = head;
	while (current != NULL) {
		if (strcmp(current->userName,userName) == 0) return current;
		current = current->next;
	}
}

int searchAccount(char *userName, char *pass) {
	account *current = head;
	while (current != NULL) {
		if (strcmp(current->userName,userName) == 0) {
			if (strcmp(current->pass,pass) == 0 ) return 1;
			else return 2;
		}
		current = current->next;
	}
}

void printList() {
	account *current = head;
	while (current != NULL) {
		printf("\n%s %s %d\n",current->userName,current->pass,current->status );
		current = current->next;
	}
}

int checkSpace(char *userName)
{
    for (int i = 0; i < strlen(userName); i++)
        if (userName[i] == ' ')
            return 0;
    return 1;
}

void readFile() {
	FILE *fp = fopen("account.txt", "r");
	char userName[30];
	char pass[30];
	int status;
	if (fp == NULL)
	{
		printf("no such file.\n");
	}
	while (fscanf(fp, "%s %s %d\n", userName, pass, &status) != EOF)
	{
		insertAccount(userName,pass,status);
	}
	fclose(fp);
}

void updateFile()
{
	FILE *fp = fopen("account.txt", "w");
	account *current = head;
	while (current != NULL)
	{
		fprintf(fp, "%s %s %d\n", current->userName, current->pass, current->status);
		current = current->next;
	}
	fclose(fp);
}

void Register() {
	FILE *fp = fopen("account.txt", "a");
	char userName[20];
	char pass[20];
	printf("\n*** REGISTER ***");
	printf("\n----------------------------");
	
	do
    {
        printf("\nUsername: ");
        scanf("%s",userName);
        if (checkSpace(userName) == 0)
            printf("\nUsername cannot have space.");
        else if (search(userName) != NULL)
            printf("\nAccount existed.");
    }
    while ((checkSpace(userName) == 0) || (search(userName) == 1));

    do
    {
        printf("\nPassword: ");
        scanf("%s",pass);
        if (checkSpace(pass) == 0)
            printf("\nPassword cannot have space.");
    }
    while (checkSpace(pass) == 0);

    fprintf(fp, "%s %s %d\n", userName, pass, 1);
    insertAccount(userName,pass,1);
    fclose(fp);
    printf("\nSuccessful registration.\n");

}

void login(char *currentAccount) {
	char userName[20];
	char pass[20];
	int num=0;
 	printf("\n*** Login ***");
	printf("\n----------------------");
	while (num <3) {
		printf("\nUsername: ");
	    scanf("%s",userName);
	    while (getchar() != '\n');
	    printf("\nPassword: ");
        scanf("%s",pass); 
	    while (getchar() != '\n');
	    if (searchAccount(userName,pass) == 1) {
	    	strcpy(currentAccount,userName);
	    	printf("%s\n",search(currentAccount)->pass );
	    	printf("\nLogged in.");
	    	break;
	    }
	    else if (searchAccount(userName,pass) == 2) {
	    	printf("\nWrong password.\n");
	    	num = num + 1;
	    }
	    else if (search(userName) == NULL){
	    	printf("\nAccount is not existed.");
	    	break;
	    }	
	}
	if (num>=3) {
		account *temp = search(userName);
		temp->status = 0; 
		printf("\nAccount is blocked");
		updateFile();
	}

}

void logout(char *currentAccount) {
	char userName[20];
	if (search(currentAccount) != NULL)
		printf("\nInput yor username: ");
	else {
		 printf("\nYou are not sign in");
		 return;
	}
	scanf("%s",userName);
	account *temp = search(userName);
	if (temp != NULL ) {
		if (strcmp(temp -> userName,currentAccount)==0) 
			printf("\nLogged out.\n");
		else printf("\nAccount is not sign in.");
	}
	else printf("\nAccount not existed.");

}



void findAccount(char *currentAccount)
{
	char userName[20];
	account *temp;
	if ( search(currentAccount) != NULL)
	    {printf("\nPlease input your username  :   ");}
	else {
		printf("\nYou are not sign in\n");
		return;
	}
	scanf("%s", userName);
	temp = search(userName);
	printf("\nRESULT:\n");
	if (temp != NULL)
	{
		printf("\nUsername: %s", temp->userName);
		if (temp->status == 1)
		{
			printf("\nAccount is active");
		}
		else
		{
			printf("\nAccount is blocked");
		}
	}
	else
	{
		printf("\nCannot find account\n");
	}
	printf("\n");
}

void menu(char *currentAccount) {
	int n;
	do
    {
        printf("\nUSER MANAGEMENT PROGRAM");
	    printf("\n---------------------------------------");
	    printf("\n   1. Register");
	    printf("\n   2. Sign in");
	    printf("\n   3. Search");
	    printf("\n   4. Sign out");
	    printf("\nYour choice (1-4, other to quit) : ");        scanf("%d", &n);
        switch(n)
        {
        case 1:
            Register();
            break;
        case 2:
            login(currentAccount);
            break;
        case 3: 
        	findAccount(currentAccount);
            break;
        case 4:
            logout(currentAccount);
            break;
        }
    }
    while (n >= 1 && n <= 4);
	
}

int main() {
	char currentAccount[30];
	readFile();
	menu(currentAccount);
	return 0;
	
}