// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // Copy header from input file to output file
    uint8_t header_buffer[HEADER_SIZE]; // Create a buffer to store the header data
    fread(header_buffer, HEADER_SIZE, 1, input); // Reading and storing the header data in header buffer
    fwrite(header_buffer, HEADER_SIZE, 1, output); // write that header data onto the output file

    // Read samples from input file and write updated data to output file
    int16_t wav_buffer; // A buffer for a single sample 2 bytes
    // Read single sample from input into buffer while there are samples left to read
    while (fread(&wav_buffer, sizeof(int16_t), 1, input))
    {
        // Update volume of sample
        wav_buffer *= factor;

        // Write updated sample to new file
        fwrite(&wav_buffer, sizeof(int16_t), 1, output);
    }
    // Close files
    fclose(input);
    fclose(output);
}
