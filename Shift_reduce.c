#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>

char ip_sym[15], stack[15];
int ip_ptr = 0, st_ptr = 0, len;
char temp[2], temp2[2];
char act[15];

void check();

int main()
{
    printf("\nSHIFT REDUCE PARSER\n");
    printf("\nGRAMMAR\n");
    printf("\nE -> E+E\nE -> E*E");
    printf("\nE -> (E)\nE -> id");

    printf("\nEnter the input symbol: ");
    scanf("%s", ip_sym);

    printf("\nStack\tInput Symbol\tAction\n");
    printf("\n$\t%s$\t-\n", ip_sym);

    strcpy(act, "Shift");
    temp[0] = ip_sym[ip_ptr];
    temp[1] = '\0';

    strcat(stack, temp);
    ip_ptr++;

    printf("\n$%s\t%s$\t%s", stack, ip_sym + ip_ptr, act);

    len = strlen(ip_sym);

    for (; ip_ptr < len; ip_ptr++)
    {
        temp[0] = ip_sym[ip_ptr];
        temp[1] = '\0';

        strcat(stack, temp);
        st_ptr++;

        printf("\n$%s\t%s$\tShift", stack, ip_sym + ip_ptr + 1);

        check();
    }

    check();

    return 0;
}

void check()
{
    int flag = 0;
    char temp[20];

    strcpy(temp, stack);

    if (strcmp(temp, "id") == 0)
    {
        strcpy(stack, "E");
        printf("\n$%s\t$\tREDUCE E->id", stack);
    }
    else if (strcmp(temp, "E+E") == 0)
    {
        strcpy(stack, "E");
        printf("\n$%s\t$\tREDUCE E->E+E", stack);
    }
    else if (strcmp(temp, "E*E") == 0)
    {
        strcpy(stack, "E");
        printf("\n$%s\t$\tREDUCE E->E*E", stack);
    }
    else if (strcmp(temp, "(E)") == 0)
    {
        strcpy(stack, "E");
        printf("\n$%s\t$\tREDUCE E->(E)", stack);
    }
    else
    {
        flag = 1;
    }

    if (flag == 0)
        printf("\nString is ACCEPTED\n");
    else
        printf("\nString is not accepted\n");
}
