#include "helpers.h"
#include <math.h>
#define MAX_RGB_VALUE 255

#define RED_COLOR 0
#define GREEN_COLOR 1
#define BLUE_COLOR 2
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            // averages the color intensity and then applies the same value to all the colors to get gray
            int rgbGray = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);

            image[i][j].rgbtBlue = rgbGray;
            image[i][j].rgbtGreen = rgbGray;
            image[i][j].rgbtRed = rgbGray;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);

            image[i][j].rgbtRed = fmin(MAX_RGB_VALUE, sepiaRed);
            image[i][j].rgbtBlue = fmin(MAX_RGB_VALUE, sepiaBlue);
            image[i][j].rgbtGreen = fmin(MAX_RGB_VALUE, sepiaGreen);
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
     // Temporary storage
    RGBTRIPLE temp;

    // Iterate over every row of the image
    for (int i = 0; i < height; i++)
    {
        // Iterate over every column that are less than width / 2
        for (int j = 0; j < width / 2; j++)
        {
            // Swap pixels on horizontally opposite sides
            temp = image[i][j];
            image[i][j] = image[i][width - j - 1];
            image[i][width - j - 1] = temp;
        }
    }
    return;
}


int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width] , int color_position)
{
    float counter = 0;
    int sum = 0;

    /** Start from 1 row before it and end at 1 row after it- total of 3rows */
    for (int row = i - 1; row <=  (i + 1); row++)
    {
        /** Start from 1 col before it and end at 1 col after it- total of 3blocks */
        for (int col = j - 1; col <= (j + 1); col ++)
        {
            if(row < 0 || col < 0 || row >= height || col >= width)
            {
                continue;
            }
            if (color_position == RED_COLOR)
            {
                sum += image[row][col].rgbtRed;
            }
            else if (color_position == GREEN_COLOR)
            {
                sum += image[row][col].rgbtGreen;
            }
            else
            {
                sum += image[row][col].rgbtBlue;
            }
            counter++;

        }
    }
    return round(sum /counter);
}
// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = getBlur(i, j, height, width, copy, RED_COLOR);
            image[i][j].rgbtGreen = getBlur(i, j, height, width, copy, GREEN_COLOR);
            image[i][j].rgbtBlue = getBlur(i, j, height, width, copy, BLUE_COLOR);
        }
    }
    return;
}
