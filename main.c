#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <ctype.h>

typedef struct n{
	char checkk[30];
	int score;
	struct n*next;
	struct n*back;
}FILES;
typedef FILES node;
FILES passwords[100000];

int search(char pw[30])
{
    FILE *file = fopen("10-million-password-list-top/100000.txt", "r");
    if (file == NULL)
    {
        printf("File doesn't exist.\n");
    }
    else
    {
        rewind(file);
        int i=0,j;
        while(!feof(file))
		{
		fscanf(file,"%s",passwords[i].checkk);
		i++;
        }
     for(j=0;j<100000;j++)
	 {
	 	if(strcmp(pw,passwords[j].checkk)==0)
		 {
		 	return 1;
		 }
	 } 
	 return -1;  
    }
    fclose(file);
return 0;
}

void sorting()
{
	FILE *file = fopen("10-million-password-list-top/10000.txt","r"); 
	if(file==NULL)
	{
		printf("File isn't exist.");
	}
	else
	{	
		node hold;
		int i=0,j=0,l=1,k,a,b;
        while(!feof(file))
		{
		fscanf(file,"%s",passwords[i].checkk);
		i++;
		}
		for(i=0;i<9999;i++)
		{
			for(j=9999;j>i;j--)
			{
				if(strcmp(passwords[j].checkk,passwords[i].checkk)>0)
				{
				hold=passwords[j];
				passwords[j]=passwords[i];
				passwords[i]=hold;
				}
			}
		}
		printf("---------TOP 10 DESCENDING PASSWORDS---------\n");
		for(k=0;k<10;k++)
		{
			printf("%d) %s\n",k+1,passwords[k]);
		}
		printf("---------TOP 10 ASCENDING PASSWORDS---------\n");
		i=1;
		for(k=9999;k>=9990;k--)
		{
			printf("%d) %s\n",i,passwords[k]);
			i++;
		}
	}
	
	fclose(file);
}

int hash(char pw[30]){
	FILE *file = fopen("10-million-password-list-top/1000.txt","r");
	if(file==NULL)
	{
		printf("File isn't exist.");
	}
	else
	{
		rewind(file);
        int i=0,j;
        while(!feof(file))
		{
		fscanf(file,"%s",passwords[i].checkk);
		passwords[i].score=calculate_score(passwords[i].checkk);
		i++;
        }
		for(i=0;i<999;i++)
		{
			for(j=999;j>i;j--)
			if(strcmp(pw,passwords[i].checkk))
			{
			printf("%d collusion | [%d]th row in table - ",collusion(i),passwords[i].score);
			return 1;
			}
		}
		return-1;
	}
	fclose(file);
	return 0;
}
int collusion(int a)
{
	int i,count=-1;
	while(i<999)
	{
		if(passwords[a].score==passwords[i].score)
		{
			count++;
		}
	i++;
	}
	return count%31;
}
void linked_list()
{
	FILE *file = fopen("10-million-password-list-top/1000.txt","r");
	if(file==NULL)
	{
		printf("File isn't exist.");
	}
	else
	{
		int i=0,count=0,j=1;
		while(i<1000)
		{
		fscanf(file,"%s",passwords[i].checkk);
		passwords[i].score=calculate_score(passwords[i].checkk);
		if(i>0)
		{
			passwords[i-1].next=&passwords[i];   // The size of the linked list is already declared(1000). That is why I don't need to use malloc
			passwords[i].back=&passwords[i-1];
		}
		i++;
		}
		FILES temp;
		node *temp2;
		for(i=0;i<999;i++)
		{
			for(j=999;j>i;j--)
			{
				if(passwords[j].score>passwords[i].score)
				{
				temp=passwords[j];
				passwords[j]=passwords[i];
				passwords[i]=temp;
				temp2=passwords[j].next;
				passwords[j].next=passwords[i].next;
				passwords[i].next=temp2;
				temp2=passwords[j].back;
				passwords[j].back=passwords[i].back;
				passwords[i].back=temp2;
				}
			}
		}
		node *root;
		root=&passwords[0];
		printf("---------TOP 10 Strongest Passwords---------\n");
		int a=0;
		while(root!=NULL)
		{
			printf("%d) %s | SCORE: %d\n",a+1,root->checkk,root->score);
			root=root->next;
			a++;
			if(a>10)
				break;
			
		}
		node *rootreverse;
		a=0;
		rootreverse=&passwords[999];
		printf("---------TOP 10 Weakest Passwords---------\n");
		while(rootreverse!=NULL)
		{
			printf("%d) %s | SCORE: %d\n",a+1,rootreverse->checkk,rootreverse->score);
			rootreverse=rootreverse->back;
			a++;
			if(a>10)
				break;
		}
	}
	fclose(file);
}

int calculate_score(char password[30])
{
	int i,a;
	int hhasdigit=0;
	int haslower=0;
	int hasupper=0;
	a=strlen(password);
	for(i=0;i<a;i++)
	{
		if(isupper(password[i]))
		{
			hasupper=1;
		}
		if(isdigit(password[i])==1)
		{
			
			hhasdigit=1;
		}
		if(islower(password[i]))
		{
			haslower=1;
		}
	}

	int score = strlen(password);
	
	
	if(hasupper==1)
	{
		score+=10;
	}
	if(hhasdigit==1)
	{
		score+=10;
	}
	if(haslower==1)
	{
		score+=10;
	}
return score;
}

void main()
{	
	setlocale(LC_ALL,"Turkish");
	int choice;
	char scan[30];
	
	printf( "1)Search in 100.000 passwords.\n"
		    "2)Sort 10.000 passwords with ascending and descending order.\n"
		    "3)Insert 1000 password list in to hash table .\n"
			"4)Sort Top 10 strongest and weakest passwords with linked list in 1000 passwords .\n"
			"Any other key for Exit\n->");
	scanf("%d",&choice);
	switch(choice)
	{
		case 1:
			printf("Enter your password for checking on the list\n->");
			scanf("%s",&scan);
			if(search(scan)==1)
			{
				printf("MATCH!!");
			}
			else if(search(scan)==-1)
			{
				printf("FILE COULDN'T FIND!");
			}
			break;
		case 2:
			sorting();
			break;
		case 3:
			printf("Enter your password for checking on the Hash Table\n->");
			scanf("%s",&scan);
			if(hash(scan)==1)
			{
				printf("MATCH!!");
			}
			else if(hash(scan)==-1)
			{
				printf("FILE COULDN'T FIND!");
			}
			break;
		case 4:
			linked_list();
			break;
		default:
			break;
	}
}
