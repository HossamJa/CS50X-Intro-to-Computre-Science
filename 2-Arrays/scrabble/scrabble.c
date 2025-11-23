#include <stdio.h>
#include <string.h>

int calculate_score(char player_input[]);
void check_winner(int p1_score, int p2_score);

int main(void)
{
    // Get the input of Player 1
    char p1[30];
    printf("Player 1: ");
    fgets(p1, sizeof(p1), stdin);

    // Get the input of Player 2
    char p2[30];
    printf("Player 2: ");
    fgets(p2, sizeof(p2), stdin);

    // Calculate the score for Player 1
    int p1_score = calculate_score(p1);

    // Calculate the Scoere for Player 2
    int p2_score = calculate_score(p2);

    // Print the result
    check_winner(p1_score, p2_score);
    return 0;
}

int calculate_score(char player_input[])
{
    char letters[][24] = {

                    {'A', 'a', 'E', 'e', 'I', 'i', 'L', 'l', 'N', 'n', 'O', 'o', 'R', 'r', 'S', 's', 'T', 't', 'U', 'u'},
                    {'D', 'd', 'G', 'g'},
                    {'B', 'b', 'C', 'c', 'M', 'm', 'P', 'p'},
                    {'F', 'f', 'H', 'h', 'V', 'v', 'W', 'w', 'Y', 'y'},
                    {'K', 'k'},
                    {'J', 'j', 'X', 'x'},
                    {'Q', 'q', 'Z', 'z'}
                };
    // Initialazing the score
    int score = 0;
    // Calculating the size of the letter Array (how many rows in it)
    int letters_size = sizeof(letters) / sizeof(letters[0]);

    // Itirate over the player input string letter by letter
    for (int i = 0; i < strlen(player_input); i++)
    {   
        // Itirate over the letter array row by row
        for (int j = 0; j < letters_size; j++)
        {
            // Calculating the row size to itirate over it
            int row_size = sizeof(letters[j]) / sizeof(letters[j][0]);

            // itirating over each letter in each row 
            for (int n = 0; n < row_size; n++)
            {
                // Check which letter is it and increase the score by the letter corresponding score
                if (player_input[i] == letters[j][n])
                {
                    switch (j)
                    {
                    case 0:
                        score += 1;
                        break;
                    case 1:
                        score += 2;
                        break;
                    case 2:
                        score += 3;
                        break;
                    case 3:
                        score += 4;
                        break;
                    case 4:
                        score += 5;
                        break;
                    case 5:
                        score += 8;
                        break;
                    case 6:
                        score += 10;
                        break;
                    }
                }
            }
        }
    }

    return score;
}

void check_winner(int p1_score, int p2_score)
{
    if (p1_score > p2_score)
    {
        printf("Player 1 wins!");
    }
    else if (p1_score < p2_score)
    {
        printf("Player 2 wins!");
    }
    else
    {
        printf("Tie!");
    }
}
