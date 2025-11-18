#include <stdio.h>

int get_height(void);
void print_row(int blocks, int spaces);

int main(void)
{
    int height = get_height();

    // Print a pyramid of that height
    for (int i = 0; i < height; i++)
    {
        // Print row of bricks
        print_row(i + 1, height - (i + 1));
    }
}

int get_height(void)
{
    // Prompt the user for the pyramid's height
    int height = 0;
    do
    {
        printf("Height: ");
        scanf("%d", &height);
    }
    while (height < 1);

    return height;
}

void print_row(int blocks, int spaces)
{
    for (int j = 0; j < spaces; j++)
    {
        // Print Spaces
        printf(" ");
    }
    
    for (int n = 0; n < blocks; n++)
    {
        // Print Blocks
        printf("#");
    }
    printf("  ");
    for (int z = 0; z < blocks; z++)
    {
        printf("#");
    }
    printf("\n");
}
