#include <stdio.h>
#include <stdlib.h>

struct node
{
    int st;
    struct node *link;
};

void findclosure(int, int);
void insert_tranbt(int, char, int);
int findalpha(char);
void print_e_closure(int);

static int nostate, noalpha, notransition, r, s;
static int buffer[20];
static int e_closure[20][20] = {0};
static int count;

char alphabet[20];

struct node *transition[20][20] = {NULL};

void main()
{
    int i, j;
    int n;
    char c;
    struct node *temp;

    printf("Enter the number of alphabets:\n");
    scanf("%d", &noalpha);
    getchar();

    printf("NOTE: Use letter e as epsilon if it is present\n");
    printf("NOTE: e must be the last character, if it is present\n");
    printf("\nEnter alphabets\n");

    for (i = 0; i < noalpha; i++)
    {
        alphabet[i] = getchar();
        getchar();
    }

    printf("\nEnter the number of states\n");
    scanf("%d", &nostate);

    printf("\nEnter no of transition\n");
    scanf("%d", &notransition);

    printf("NOTE: Transition is in the form: qno alphabet qno\n");
    printf("NOTE: States number must be greater than zero\n");

    printf("\nEnter transition\n");

    for (i = 0; i < notransition; i++)
    {
        scanf("%d %c %d", &r, &c, &s);
        insert_tranbt(r, c, s);
    }

    printf("\n");
    printf("e-closure of states........\n");
    printf("--------------------------\n");

    for (i = 1; i <= nostate; i++)
    {
        count = 0;

        for (j = 0; j < 20; j++)
        {
            buffer[j] = 0;
            e_closure[i][j] = 0;
        }

        findclosure(i, i);

        printf("\ne-closure(q%d): ", i);
        print_e_closure(i);
    }
}

void findclosure(int x, int sta)
{
    struct node *temp;

    if (buffer[x])
        return;

    e_closure[sta][count++] = x;
    buffer[x] = 1;

    if (alphabet[noalpha - 1] == 'e' &&
        transition[x][noalpha - 1] != NULL)
    {
        temp = transition[x][noalpha - 1];

        while (temp != NULL)
        {
            findclosure(temp->st, sta);
            temp = temp->link;
        }
    }
}

void insert_tranbt(int r, char c, int s)
{
    int j;
    struct node *temp;

    j = findalpha(c);

    if (j == 999)
    {
        printf("Error\n");
        exit(0);
    }

    temp = (struct node *)malloc(sizeof(struct node));
    temp->st = s;
    temp->link = transition[r][j];

    transition[r][j] = temp;
}

int findalpha(char c)
{
    int i;

    for (i = 0; i < noalpha; i++)
    {
        if (alphabet[i] == c)
            return i;
    }

    return 999;
}

void print_e_closure(int i)
{
    int j;

    printf("{");

    for (j = 0; e_closure[i][j] != 0; j++)
    {
        printf("q%d, ", e_closure[i][j]);
    }

    printf("}");
}