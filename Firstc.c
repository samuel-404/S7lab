#include <stdio.h>
#include <string.h>
#include <ctype.h>

int n, m = 0;
char a[10][10], f[10];

void follow(char c);
void first(char c);
int dup(char c);

int main()
{
    int i, z;
    char c;

    printf("Enter the no of productions:\n");
    scanf("%d", &n);

    printf("Enter the productions (e.g., S=AB):\n");
    for(i = 0; i < n; i++)
        scanf("%s", a[i]);

    do
    {
        m = 0;
        printf("Enter the element whose first and follow is to be found: ");
        scanf(" %c", &c);

        first(c);

        printf("First(%c)={", c);
        for(i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        m = 0; 

        follow(c);

        printf("Follow(%c)={", c);
        for(i = 0; i < m; i++)
            printf("%c", f[i]);
        printf("}\n");

        printf("Continue(0/1)? ");
        scanf("%d", &z);

    } while(z == 1);

    return 0;
}

void first(char c)
{
    if(!isupper(c)) {
        if(!dup(c)) f[m++] = c;
        return;
    }

    for(int k = 0; k < n; k++)
    {
        if(a[k][0] == c)
        {
            if(a[k][2] == '$') {
                if(!dup('$')) f[m++] = '$'; 
            }
            else if(!isupper(a[k][2])) {
                if(!dup(a[k][2])) f[m++] = a[k][2];
            }
            else {
                first(a[k][2]);
            }
        }
    }
}

void follow(char c)
{
    if(a[0][0] == c) {
        if(!dup('$')) f[m++] = '$'; 
    }

    for(int i = 0; i < n; i++)
    {
        for(int j = 2; j < strlen(a[i]); j++)
        {
            if(a[i][j] == c)
            {
                if(a[i][j + 1] != '\0') {
                    int current_m = m; 
                    first(a[i][j + 1]);
                    
                    int has_epsilon = 0;
                    for(int k = current_m; k < m; k++) {
                        if(f[k] == '$') has_epsilon = 1;
                    }
                    
                    if(has_epsilon && c != a[i][0]) {
                        follow(a[i][0]);
                    }
                }
                
                if(a[i][j + 1] == '\0' && c != a[i][0]) {
                    follow(a[i][0]);
                }
            }
        }
    }
}

int dup(char c)
{
    for(int i = 0; i < m; i++)
    {
        if(f[i] == c)
            return 1;
    }
    return 0;
}
