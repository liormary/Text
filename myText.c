#include <stdio.h>
#include <stdlib.h>
#define SIZE 60 /* row length */

typedef struct Node* ptr; /* pointer to Node */
typedef struct Node { /* new typetef called node */
    char data[SIZE+1];
    ptr next;
} node;
/*----------------------------------------------------------------------*/
void FreeText(int type, void **head) /* this function delete the list from the computer memory after we print the list to clean space */
{
    ptr *p2 = (ptr*)head;
    ptr p1 = *p2;

    ptr tmp;

    while (p1 != NULL)
    {
        tmp = p1;
        p1 = p1->next;
        free(tmp);
    }
}
/*----------------------------------------------------------------------*/
int ReadText(int type, void *s) {
    char ch;
    int i=0;
    char *buffer = (char *)s;
    char *newbuffer= NULL;

    ptr head= (ptr)s;
    ptr pnew= head;
    pnew->next= NULL;

    if (type==1) /* the user choose buffer data structure */
    {
        while ((ch=getchar()) != EOF)
        {
            if (ch != '\0' && ch != '\n') /* we dont need to save '\n' and '\0' */
            {
                if ( i !=0 && i%SIZE == 0) /* we have space for 60 chars every time, to after we save 60 chars we need to allocate more space */
                {
                    newbuffer = (char *)realloc(buffer,(SIZE*sizeof(char))+i); /* allocation of memory*/

                    if (!newbuffer) /* if we cant allocate the memory */
                    {
                       
                        return -1; /* error code */
                    }
                }
                buffer[i] = ch; /* save every char*/
                i++;
            }
        }
    }
    else if (type == 2) /* the user choose linked list data structure */
    {
        while ((ch=getchar()) != EOF)
        {
            if (ch != '\n') /* we dont need to save '\n' */
            {
                if (i == SIZE) /* we have space for 60 chars every time, to after we save 60 chars we need to allocate more space */
                {
                    pnew->next = (ptr)calloc(1, sizeof(node)); /* allocation of memory*/

                    if (!pnew->next) /* if we cant allocate the memory*/
                    {
                        pnew->data[i]='\0';
                        return -1; /* error code */
                    }
                    pnew= pnew->next;  /* go futher to the next node */
                    i=0;
                 }
                pnew->data[i]= (char)ch; /* save every char*/
                i++;
            }
        }
    }
    return 1;
}
/*----------------------------------------------------------------------*/
int PrintText (int type, void *s) {
    int i=0;
    char *buffer= (char *)s;
    int ch=buffer[i];

    ptr p= (ptr)s;

    if (type == 1) /* the user choose buffer data structure */
    {
        while (ch != '\0') /* after the lest char thers is '\0' */
        {
            if (i!=0 && i%SIZE ==0) /* everey 60 chars we need to print '\n' */
            {
                printf("\n");
            }
            ch= buffer[i]; 
            putchar(ch);  /*print the char we saved */
            i++;
        }
        printf("\n"); 
    }

    else if (type == 2) /* the user choose linked list data structure */
    {
        while(p->next) /* the last node point to NULL */
        {

	    if (i == SIZE) 
	    {
		printf("\n"); /* everey 60 chars we need to print '\n' */
		i=0;
		p= p->next; /* go futher to the next node */
	    }
                putchar(p->data[i]); /*print 60 char we saved */
                i++;
        }
	if (p->next == NULL)
	{
	   i=0;
	   while (i<= SIZE && p->data[i] != '\0')
		{
		  putchar(p->data[i]); /*print the last 60 char we saved */
      	 	  i++;
		}
	}
	printf("\n");
    }
    return 1;
}
/*----------------------------------------------------------------------*/
int main() {
    int answer=0;
    int error=0;
    void *p;
    printf("Please choose data structure: \n 1. Buffer \n 2. Linked list \n"); /* choose data structure */
    scanf("%d", &answer); /* save user preference */
    if (answer==1) /* buffer data structure */
    {
        p= (char*)calloc(SIZE, sizeof(char)); /*First allocation of memory*/
    }
    if (answer==2) /* linked list data structure */
    {
        p= (ptr)calloc(1, sizeof(node)); /*First allocation of memory*/
    }
    if(p) /* if we can allocate memory */
    {
        printf("\n please enter your text \n");
        error= ReadText(answer, p); /* the user insert text */

	if (error == -1) /* error code */
	{ 
	    printf("\n there is no more memory \n"); 
	}

        printf("\n output: \n");
        PrintText(answer, p); /* print text with maximum 60 chars in every line */
    }
    else /* we cant allocate memory */
    {
        printf("\n your memory is full \n");
    }
    if (answer==1) /* buffer data structure */
    {
        free(p); /* delete buffer from computer memory */
    }
    else if(answer==2) /* linked list data structure */
    {
        FreeText(answer, &p); /* delete linked list from computer memory */
    }
}

