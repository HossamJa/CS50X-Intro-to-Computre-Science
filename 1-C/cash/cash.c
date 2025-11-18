#include <stdio.h>

int get_change(void);
int minimum_coins(int change);

int main(void)
{
    // Get the owed change
    int change = get_change();

    // Calculate the minimum amount of cash
    int coins = minimum_coins(change);

    // Print the minimum amount of coins
    printf("%d\n", coins);
}

int get_change(void)
{
    int change_owed = 0;
    do
    {
        printf("Change owed: ");
        scanf("%d", &change_owed);
    }
    while (0 > change_owed);
    return change_owed;
}

int minimum_coins(int change)
{
    int remain_change = change;
    int coins = 0;

    do
    {
        if ((remain_change - 25) >= 0)
        {
            remain_change -= 25;
            coins++;
        }
        else if ((remain_change - 10) >= 0)
        {
            remain_change -= 10;
            coins++;
        }
        else if ((remain_change - 5) >= 0)
        {
            remain_change -= 5;
            coins++;
        }
        else if ((remain_change - 1) >= 0)
        {
            remain_change -= 1;
            coins++;
        }
    }
    while (remain_change > 0);

    return coins;
}
