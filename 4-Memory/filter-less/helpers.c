#include "helpers.h"
#include "math.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // iterate over each row in the image
    {
        for (int j = 0; j < width; j++) // iterate over each pixel in that row i 
        {
            int avg_value = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            // set all the values of that pixel into the value of the color with highst vlue
            image[i][j].rgbtBlue = avg_value;
            image[i][j].rgbtGreen = avg_value;
            image[i][j].rgbtRed = avg_value;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) // iterate over each row in the image
    {
        for (int j = 0; j < width; j++) // iterate over each pixel in that row i 
        {
            int sepiaRed = (int) round((0.393 * image[i][j].rgbtRed) + (0.769 * image[i][j].rgbtGreen) + (0.189 * image[i][j].rgbtBlue));
            int sepiaGreen = (int) round((0.349 * image[i][j].rgbtRed) + (0.686 * image[i][j].rgbtGreen) + (0.168 * image[i][j].rgbtBlue));
            int sepiaBlue = (int) round((0.272 * image[i][j].rgbtRed) + (0.534 * image[i][j].rgbtGreen) + (0.131 * image[i][j].rgbtBlue));
            
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }

            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        // Initialazing temporary buffers for the current row data
        int rgbtRed_buffer[width];
        int rgbtGreen_buffer[width];
        int rgbtBlue_buffer[width];

        // Read the original row data into the buffers
        for (int j = 0; j < width; j++)
        {
            rgbtRed_buffer[j] = image[i][j].rgbtRed;
            rgbtGreen_buffer[j] = image[i][j].rgbtGreen;
            rgbtBlue_buffer[j] = image[i][j].rgbtBlue;
        }

        // Writing the data back to the image in reverse order
        for (int r = 0; r < width; r++)
        {
            image[i][width - 1 - r].rgbtRed = rgbtRed_buffer[r];
            image[i][width - 1 - r].rgbtGreen = rgbtGreen_buffer[r];
            image[i][width - 1 - r].rgbtBlue = rgbtBlue_buffer[r];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_buffer[height][width];
    for (int i = 0; i < height; i++) // iterate over each row in the image
    {
        for (int j = 0; j < width; j++) // iterate over each pixel in that row i 
        {
            int rgbtRed_avg = 0;
            int rgbtGreen_avg = 0;
            int rgbtBlue_avg = 0;
            int valid_value = 0;
            for (int bi = -1; bi < 2; bi++)
            {
                for (int bj = -1; bj < 2; bj++)
                {
                    int current_row = i + bi;
                    int current_colmen = j + bj;
                    if ((current_row >= 0) && (current_row < height) && (current_colmen >= 0) && (current_colmen < width))
                    {
                        rgbtRed_avg += image[i + bi][j + bj].rgbtRed;
                        rgbtGreen_avg += image[i + bi][j + bj].rgbtGreen;
                        rgbtBlue_avg += image[i + bi][j + bj].rgbtBlue;
                        valid_value++;
                    }
                }
            }
            image_buffer[i][j].rgbtRed = (int) round(rgbtRed_avg / (float) valid_value);
            image_buffer[i][j].rgbtGreen = (int) round(rgbtGreen_avg / (float) valid_value);
            image_buffer[i][j].rgbtBlue = (int) round(rgbtBlue_avg / (float) valid_value);
        }
    }
    for (int i = 0; i < height; i++) // iterate over each row in the image
    {
        for (int j = 0; j < width; j++) // iterate over each pixel in that row i 
        {
            image[i][j].rgbtRed = image_buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_buffer[i][j].rgbtBlue;
        }
    }
    return;
}
