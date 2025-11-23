#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>

void encrypt_text(char key[], char plaintext[]);

int main(int argc, char *argv[])
{
    // Check if a valid number of argument were given
    if (argc != 2)
    {
        printf("Usage: ./substitution key");
        return 1;
    }

    // Check if the Key is 26 characters
    if (strlen(argv[1]) < 26)
    {
        printf("Key must contain 26 characters.");
        return 1;
    }

    for (int i = 0; i < strlen(argv[1]); i++)
    {
        // Check if the Key is made of alphabets only
        if (!isalpha(argv[1][i]))
        {
            printf("The Key Must contain only alphabet characters");
            return 1;
        }
        // Check if the Key doesn't contain duplicated charachters
        int duplicates = 0;
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (duplicates > 1)
            {
                printf("The Key Must contain each letter exactly once");
                return 1;
            }

            if (tolower(argv[1][i]) == tolower(argv[1][j]))
            {
                duplicates++;
            }
        }
    }

    // Prompt the user for the plainText
    char plainText[1024];
    printf("plaintext: ");
    fgets(plainText, sizeof(plainText), stdin);

    // Encrypt the plainText using the secret Key
    encrypt_text(argv[1], plainText);
    return 0;
}

char encrypt_char(char letter, char key[])
{
    if (isupper(letter))
    {
        int char_index = letter - 65;
        for (int i = 0; i < strlen(key); i++)
        {
            if (i == char_index)
            {
                return toupper(key[i]);
            }
        }
    }
    else
    {
        int char_index = letter - 97;
        for (int i = 0; i < strlen(key); i++)
        {
            if (i == char_index)
            {
                return tolower(key[i]);
            }
        }
    }
}

void encrypt_text(char key[], char plaintext[])
{
    char cipherText[1024] = "\0";

    for (int i = 0; i < strlen(plaintext); i++)
    {
        char cipher_char = plaintext[i];

        if (isalpha(plaintext[i]))
        {
            cipher_char = encrypt_char(plaintext[i], key);
        }

        // Append the cipher character to the cipherText string
        strncat(cipherText, &cipher_char, 1);
    }

    printf("ciphertext: %s", cipherText);
}
