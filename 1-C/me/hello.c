#include <stdio.h>

int main()
{
    // Initializing the name variable
    char name[50] = "";
    // Asking for the name
    printf("What's your name? ");
    scanf("%s", &name);
    // Printing the gretting to the name
    printf("Hello, %s\n", name);
    return 0;
}