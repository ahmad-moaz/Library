#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    int id;
    char title[100];
    char author[100];
} Book;

typedef struct Node
{
    Book book;
    struct Node* next;
} Node;

Node* createNode(int id, char* title, char* author)
{
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->book.id = id;
    strcpy(newNode->book.title, title);
    strcpy(newNode->book.author, author);
    newNode->next = NULL;
    return newNode;
}

void addBook(Node** head, int id, char* title, char* author)
{
    Node* newNode = createNode(id, title, author);
    newNode->next = *head;
    *head = newNode;
}

Node* searchBookByTitle(Node* head, char* title)
{
    Node* current = head;
    while (current != NULL)
    {
        if (strcmp(current->book.title, title) == 0)
        {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void sortBooksByTitle(Node** head)
{
    Node* i, * j;
    Book temp;
    for (i = *head; i != NULL; i = i->next)
    {
        for (j = i->next; j != NULL; j = j->next)
        {
            if (strcmp(i->book.title, j->book.title) > 0)
            {
                temp = i->book;
                i->book = j->book;
                j->book = temp;
            }
        }
    }
}

void printBooks(Node* head)
{
    Node* current = head;
    while (current != NULL)
    {
        printf("ID: %d\nTitle: %s\nAuthor: %s\n\n", current->book.id, current->book.title, current->book.author);
        current = current->next;
    }
}

int main()
{
    system("color F8");
    Node* head = NULL;
    int choice,c2,c3;

    addBook(&head, 1, "The C Programming Language", "Kernighan and Ritchie");
    addBook(&head, 2, "Effective C", "Robert C. Seacord");
    addBook(&head, 3, "C Primer Plus", "Stephen Prata");
    addBook(&head, 4, "C Programming Absolute Beginner's Guide", "Greg Perry");
    addBook(&head, 5, "Programming in C", "Stephen G. Kochan");
    addBook(&head, 6, "Expert C Programming", "Peter van der Linden");


    printf("This is a simple library management tool.What do you want to do?\n");

xy:
    printf("1.Show available books.\n");
    printf("2.Sort all available books.\n");
    printf("3.Search for a book by its name.\n");
    scanf("%d",&choice);
    if(choice==1)
    {
        printBooks(head);
        printf("To go to main menu,press 1\n");
        scanf("%d",&c3);
        if(c3==1)
            goto xy;
        else return 0;
    }

    else if(choice==2)
    {
        sortBooksByTitle(&head);
        printf("All the books are sorted by title, if you want to see the sorted books, press 1\n");
        printf("If you want to go to main menu,press 2\n");
        scanf("%d",&c2);
        if(c2==1)
        {
            printf("Books after sorting by title:\n");
            printBooks(head);
        }
        else goto xy;
    }
    else if(choice==3)

    {
        char searchTitle[100];
        printf("Enter the title of the book to search: ");
        fflush(stdin);
        fgets(searchTitle, 100, stdin);
        searchTitle[strcspn(searchTitle, "\n")] = 0;

        Node* foundBook = searchBookByTitle(head, searchTitle);
        if (foundBook != NULL)
        {
            printf("Book found:\nID: %d\nTitle: %s\nAuthor: %s\n",
                   foundBook->book.id, foundBook->book.title, foundBook->book.author);
        }
        else
        {
            printf("Book not found.\n");
            printf("To go to main menu,press 1\n");
            scanf("%d",&c3);
            if(c3==1)
                goto xy;
            else return 0;
        }
    }

    return 0;
}
