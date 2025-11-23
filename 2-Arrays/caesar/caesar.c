 #include <ctype.h>
 #include <stdio.h>
 #include <string.h>
 #include <stdlib.h>

 void encrypt_text(char plainText[], int secret_key);

 int main(int argc, char *argv[])
 {
    // Check if there is valid number of cli arguments were given
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    
    // Check if the argumet is a dicimal digit
    for (int i = 0; i < strlen(argv[1]); i++)
    {
        if (!isdigit(argv[1][i]) || atoi(argv[1]) < 0)
        {
            printf("The Key must be only non-negative number\n");
            return 1;
        }
    }
    
    // Get the Secret Key
    int secret_key = atoi(argv[1]);

    // Get the PlainText
    char plainText[1024];
    printf("plaintext: ");
    fgets(plainText, sizeof(plainText), stdin);

    // Encrypt the plaintext and print the ciphertext
    encrypt_text(plainText, secret_key);
    return 0;
}

char rotate(char c, int k)
{
    char cipher_char;

    if (isupper(c))
    {
        int p = c - 65;
        cipher_char = ((p + k) % 26) + 65;
    }
    else
    {
        int p = c - 97;
        cipher_char = ((p + k) % 26) + 97;
    }
    
    return cipher_char;
}

void encrypt_text(char plainText[], int secret_key)
{
    char cipherText[strlen(plainText) + 1];

    // Initialize the array as an empty string properly
    cipherText[0] = '\0';
    
    // Iterate over the plaintext
    for (int i = 0; i < strlen(plainText); i++)
    {
        char cipher_char = plainText[i];
        
        if (isalpha(plainText[i]))
        {
            cipher_char = rotate(plainText[i], secret_key);
        }
        
        // Append the cipher character to the cipherText string
        strncat(cipherText, &cipher_char, 1);
    }

    printf("ciphertext: %s\n", cipherText);
}

