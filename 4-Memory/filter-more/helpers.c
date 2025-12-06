#include "helpers.h"
#include "math.h"
#include <stdlib.h> // for abs()

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

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++) // iterate till the middle of the image
        {
            // Swap pixel on the right with pixel on the left
            RGBTRIPLE tem_pixel = image[i][j]; // Create a temprury buffer to store the pixel on the left
            image[i][j] = image[i][width - 1 - j]; // Put the left pixel on the place of the right pixel
            image[i][width - 1 - j] = tem_pixel; // put the the right pixel in the place of the left pixel
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

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE image_buffer[height][width];
    for (int i = 0; i < height; i++) // iterate over each row in the image
    {
        for (int j = 0; j < width; j++) // iterate over each pixel in that row i 
        {
            // Gx values
            int Gx_Red_sum = 0;
            int Gx_Green_sum = 0;
            int Gx_Blue_sum = 0;

            // Gy values
            int Gy_Red_sum = 0;
            int Gy_Green_sum = 0;
            int Gy_Blue_sum = 0;

            for (int bi = -1; bi < 2; bi++)
            {
                for (int bj = -1; bj < 2; bj++)
                {
                    // Check if the pixel is near the Edge or corner
                    int current_row = i + bi;
                    int current_colmen = j + bj;
                    if ((current_row >= 0) && (current_row < height) && (current_colmen >= 0) && (current_colmen < width))
                    {
                        // Calculate Gx values for each pixel's rgb
                        Gx_Red_sum += image[i + bi][j + bj].rgbtRed * ((2 - abs(bi)) * bj);
                        Gx_Green_sum += image[i + bi][j + bj].rgbtGreen * ((2 - abs(bi)) * bj);
                        Gx_Blue_sum += image[i + bi][j + bj].rgbtBlue * ((2 - abs(bi)) * bj);

                        // Calculate Gy values for each pixel's rgb
                        Gy_Red_sum += image[i + bi][j + bj].rgbtRed * ((2 - abs(bj)) * bi);
                        Gy_Green_sum += image[i + bi][j + bj].rgbtGreen * ((2 - abs(bj)) * bi);
                        Gy_Blue_sum += image[i + bi][j + bj].rgbtBlue * ((2 - abs(bj)) * bi);
                    }
                }
            }

            int final_Red = (int) round(sqrt(pow(Gx_Red_sum, 2.0) + pow(Gy_Red_sum, 2.0)));
            int final_Green = (int) round(sqrt(pow(Gx_Green_sum, 2.0) + pow(Gy_Green_sum, 2.0)));
            int final_Blue = (int) round(sqrt(pow(Gx_Blue_sum, 2.0) + pow(Gy_Blue_sum, 2.0)));

            image_buffer[i][j].rgbtRed = final_Red <= 255 ? final_Red : 255;
            image_buffer[i][j].rgbtGreen = final_Green <= 255 ? final_Green : 255;
            image_buffer[i][j].rgbtBlue = final_Blue <= 255 ? final_Blue : 255;
        }
    }
    for (int i = 0; i < height; i++) // iterate over each row in the image
    {
        for (int j = 0; j < width; j++) // iterate over each pixel in that row i, and eplace it with the new one
        {
            image[i][j].rgbtRed = image_buffer[i][j].rgbtRed;
            image[i][j].rgbtGreen = image_buffer[i][j].rgbtGreen;
            image[i][j].rgbtBlue = image_buffer[i][j].rgbtBlue;
        }
    }
    return;
}
