#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int letters_count(char text[]);
int words_count(char text[], int letters);
int sentences_counts(char text[], int words);
int coli_index(int letters_counts, int words_counts, int sentences_counts);
void grade_level(int index);

int main()
{
    // Get the user input
    char text[1024];
    printf("Text: ");
    fgets(text, sizeof(text), stdin);

    // Calculate the number of letters, words, sentences
    int counts[3] = {0};
    counts[0] = letters_count(text);
    counts[1] = words_count(text, counts[0]);
    counts[2] = sentences_counts(text, counts[1]);

    // Calculate the Coleman-Liau index 
    int index = coli_index(counts[0], counts[1], counts[2]);
    
    // Print the Grade Level
    grade_level(index);
    return 0;
}

int letters_count(char text[])
{
    int letter_count = 0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letter_count += 1; 
        }
    }
    return letter_count;
}

int words_count(char text[], int letters)
{
    int word_count = 0;
    if (letters > 0) // Check if there is at lest one letter
    {
        for (int i = 0; i < strlen(text); i++)
        {
            if (text[i] == ' ')
            {
                word_count += 1;
            }
        }

        return word_count + 1;
    }
    return word_count;
}

int sentences_counts(char text[], int words)
{
    int sentence_count = 0;

    if (words > 0) // Check if there is at lest one word
    {
        for (int i = 0; i < strlen(text); i++)
        {
            if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            {
                sentence_count += 1; 
            }
        }
    }
    return sentence_count;
}

int coli_index(int letters_count, int words_count, int sentences_count)
{
    if (letters_count > 0)
    {
        // Calculate the averges of Letters and sentences 
        float avg_ltrs = ((float) letters_count / words_count) * 100;
        float avg_sntncs = ((float) sentences_count / words_count) * 100;

        // Calculating the grade value using Coleman-Liau index formula
        int index = round(0.0588 * avg_ltrs - 0.296 * avg_sntncs - 15.8);
        
        return index;
    }
}

void grade_level(int index)
{
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }
}
