#include <stdio.h>
#include <string.h>

void left_recursion_remover(char buffer[], char options[][5], int r_count);
void left_recursion_checker(char buffer[]);

void left_recursion_checker(char buffer[]) {
    char flag, options[5][5];
    memset(options, '\0', sizeof(options));
    int i=0, j=0, k = 0;
    flag = buffer[0];
    //decompose all options of production in a 2d array
    for (i = 3; i < strlen(buffer); i++) {
        if (buffer[i] != '|') {
            options[j][k] = buffer[i];
            k++;
        } else {
            options[j][k] = '\0';
            j++;
            k = 0;
        }
    }
    //check for left recursion among individual options
    for (i = 0; i <= j; i++) {
        if (flag == options[i][0]) {
            printf("\nThere is left recursion in %s \n", buffer);
            left_recursion_remover(buffer, options, j);
            return;
        }
    }
    printf("\nThere is no left recursion in %s\n", buffer);
}

void left_recursion_remover(char buffer[], char options[][5], int r_count) {
    printf("\nProcessing Removal\n");
    int a=0,b=0,i,j;
    char alpha[5][5],beta[5][5];
    memset(alpha, '\0', sizeof(alpha));
    memset(beta, '\0', sizeof(beta));
    //decompose alphas and betas in separate 2d array from options array
    for (i = 0; i <= r_count; i++) {
        if (options[i][0] == buffer[0]) {
            for (j = 1; j < strlen(options[i]); j++) {
                alpha[a][j - 1] = options[i][j];
            }
            alpha[a][j] = '\0';
            a++;
        } else {
            for (j = 0; j < strlen(options[i]); j++) {
                beta[b][j] = options[i][j];
            }
            beta[b][j] = '\0';
            b++;
        }
    }
    printf("\nOptions 1 %s 2 %s 3 %s",options[0],options[1],options[2]);
    // Implement the logic to rewrite the production rules to eliminate left recursion
    printf("\nSolution:\n\n");
    //printf("%s\n", buffer);

    // Rewrite the production rules here
    printf("%c->", buffer[0]);
    for ( i = 0; i < b-1; i++) {
        printf("%s%c'|",beta[i],buffer[0]);
    }
    printf("%s%c'\n", beta[b-1], buffer[0]);
    printf("%c'->", buffer[0]);
    for ( i = 0; i < a-1; i++) {
        printf("%s%c'|", alpha[i], buffer[0]);
    }
    printf("%s%c'|ε\n", alpha[a-1], buffer[0]);
}

int main() {
    int i, n_p;
    char p[10][20];
    printf("Enter the number of productions: ");
    scanf("%d", &n_p);
    for (i = 0; i < n_p; i++) {
        printf("Enter %d production: ", i + 1);
        scanf("%s", p[i]);
    }
    //call checker for each production using loop
    for (i = 0; i < n_p; i++)
        left_recursion_checker(p[i]);
    return 0;
}