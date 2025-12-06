#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // Make sure the user provides valid rgs
    if (argc != 2)
    {
        printf("Usage: ./recover FILE\n");
        return 1;
    }

    // Open the input file
    FILE *input = fopen(argv[1], "rb");
    if (input == NULL)
    {
        printf("Could not open the file: %s\n", argv[1]);
        return 1;
    }

    // Create an array of the first bytes signature of JPEG file
    uint8_t signature[3]= {0xff, 0xd8, 0xff};

    // Create a buffer for a block of data
    int BLOCK_SIZE = 512; 
    uint8_t buffer[BLOCK_SIZE];

    // Craft the name of the output JPEG file    
    int image_count = 0; // JPEG count for naming the output file
    int FILENAME_MAX_LEN = 20; // output file name size
    char output_filename[FILENAME_MAX_LEN];
    FILE *output = NULL; // Initialize to NULL
    size_t bytes_read = 0; // Use size_t for fread/fwrite count

    // Iterate over the file and look for JPEGs While there's still data left to read from the memory card
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), input)) > 0)
    {
        // Check the first 3 bytes, to see if it matches the signature of jpeg, and the fourth byte starts with the four bits 1110 
        if (buffer[0] == signature[0] && buffer[1] == signature[1] && buffer[2] == signature[2] && (buffer[3] & 0xF0) == 0xE0)
        {
            // Close the previous opened output file if any
            if (output != NULL)
            {
                fclose(output);
            }
            snprintf(output_filename, FILENAME_MAX_LEN, "%03d.jpg", image_count);
            
            // Open a new JPEG file
            output = fopen(output_filename, "wb");
            if (output == NULL)
            {
                printf("Could not open the file: %s\n", output_filename);
                return 1;
            }

            fwrite(buffer, 1, bytes_read, output); // write the first buffer immidiatly
            image_count++;
        }

        // Check if currently in the middle of writing a valid JPEG file
        else if (output != NULL)
        {
            // write the JPEG to the output file
            fwrite(buffer, 1, bytes_read, output);
        }
    }

    if (output != NULL)
    {
        fclose(output); // Close the last JPEG file if there is 
    }

    fclose(input);
    return 0;
}
