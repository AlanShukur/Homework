#include <stdio.h>
#include <stdlib.h>

void nameTime() {
    char current_date[11]; 
    char user_name[50];
    
    printf("[Please enter the current date in the 'yyyy-mm-dd' format]: ");
    scanf("%10s", current_date);
    
    printf("[Please enter your name]: ");
    scanf(" %49[^\n]", user_name); 
    
    printf("**The input has been processed successfully.**\n");
    
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("\n                                        [Magrathea ver 0.1]                              \n");
    printf("                   Magrathea, where a shining planet is created in a wasteland with no grass,\n");
    printf("           a place where unseen potential is discovered and gems are polished by the hands of experts,\n");
    printf("                                        Welcome to Magrathea.   \n\n");
    printf("+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++\n");
    printf("[User]: %-50s [Execution Time]: %s\n", user_name, current_date);
    printf("=============================================================================================================\n");
}

int main() {
    nameTime();
    return 0;
}
