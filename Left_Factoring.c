#include <stdio.h>
#include <string.h>

void left_factoring(char buffer[]);
void findCommonStarter(char options[][10], int r_count);

char longestPrefix[10],common;

void left_factoring(char buffer[]) {
    char options[5][10],flag[4]={'\0'};
    int starter=0;
    memset(options, '\0', sizeof(options));
    int i=0, j=0, k = 0;
    for(i=0;i<strlen(buffer);i++)
        if(buffer[i]!='-')
            flag[i]=buffer[i];
        else if(buffer[i]=='-'){
            flag[i]=='\0';
            starter=i+2;
            break;
        }
    //decompose all options of production in a 2d array
    for (i=starter; i < strlen(buffer); i++) {
        if (buffer[i] != '|') {
            options[j][k] = buffer[i];
            k++;
        } else {
            options[j][k] = '\0';
            j++;
            k = 0;
        }
    }
    //if there is only option, then left factoring is not applicable
    if(j==0)
        return;
    //find alpha value
    findCommonStarter(options,j);
    //if there is no common value, left factoring is not applicable
    if(common=='\0')
        return;
    printf("\nLeft Factoring Required for %s\n",buffer);
    //print solution in file
    printf("\nSolution \n");
    FILE *fp=fopen("line1.txt","w");
    fprintf(fp,"%s->%s%s'",flag,longestPrefix,flag);
    for(i=0;i<=j;i++)
        //printing gamma
        if(strncmp(options[i],longestPrefix,strlen(longestPrefix))!=0)
            fprintf(fp,"|%s",options[i]);
    fprintf(fp,"\n%s'->",flag);
    for(i=0;i<=j;i++){
        if(strncmp(options[i],longestPrefix,strlen(longestPrefix))==0){
            char derived[10];
            strcpy(derived, options[i] + strlen(longestPrefix));
            if(derived[0]=='\0'){
                fprintf(fp,"ε");
                starter=i;
                break;
            }
            else{
                fprintf(fp,"%s",derived);
                starter=i;
                break;
            }
        }
    }
    for(i=starter+1;i<=j;i++){
        if(strncmp(options[i],longestPrefix,strlen(longestPrefix))==0){
            char derived[10];
            strcpy(derived, options[i] + strlen(longestPrefix));
            if(derived[0]=='\0')
                fprintf(fp,"|ε");
            else
                fprintf(fp,"|%s",derived);
        }
    }
    fclose(fp);
    char line1[100],line2[100];
    line1[0]='\0';
    line2[0]='\0';
    fp=fopen("line1.txt","r");
    fscanf(fp,"%s",line1);
    fscanf(fp,"%s",line2);
    fclose(fp);
    printf("%s\n%s\n",line1,line2);
    left_factoring(line1);
    left_factoring(line2);
    
    
}
void findCommonStarter(char options[][10], int r_count){
    int temp=0,frequent=0;
    common='\0';
    longestPrefix[0]='\0';
    //find common to search among common options
    for(int i=0;i<=r_count;i++){
        temp=frequent;
        frequent=0;
        for(int j=0;j<=r_count;j++){
            if(options[i][0]==options[j][0] && i!=j ){
                frequent++;
            }
        }
        if(frequent>temp)
            common=options[i][0];
    }
    //find largest prefix
    for(int i=0;i<=r_count;i++)
        if(options[i][0]==common){
            strcpy(longestPrefix, options[i]);
            break;
        }
    for (int i=1;i<=r_count;i++) {
        if(options[i][0]==common){
            char *currentString=options[i];
            int j=0;
            while (longestPrefix[j]==currentString[j]) {
                j++;
            }
            longestPrefix[j] = '\0';
        }
    }
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
    //call left factoring for each production using loop
    for (i = 0; i < n_p; i++)
        left_factoring(p[i]);
    return 0;
}