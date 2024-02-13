#include "helpers.h"
#include "math.h"

#define RED_COLOUR 0
#define GREEN_COLOUR 1
#define BLUE_COLOUR 2

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int GreyRgb = round((image[row][column].rgbtBlue + image[row][column].rgbtGreen + image[row][column].rgbtRed) /3.0);

            image[row][column].rgbtBlue = GreyRgb;
            image[row][column].rgbtGreen = GreyRgb;
            image[row][column].rgbtRed = GreyRgb;
        }
    }
    return;
}

// Convert image to sepia; brownish image
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            int sepiaRed = round(.393 * image[row][column].rgbtRed + .769 * image[row][column].rgbtGreen + .189 * image[row][column].rgbtBlue);
            int sepiaGreen = round(.349 * image[row][column].rgbtRed + .686 * image[row][column].rgbtGreen + .168 * image[row][column].rgbtBlue);
            int sepiaBlue = round(.272 * image[row][column].rgbtRed + .534 * image[row][column].rgbtGreen + .131 * image[row][column].rgbtBlue);

            image[row][column].rgbtRed = fmin(255, sepiaRed);
            image[row][column].rgbtGreen = fmin(255, sepiaGreen);
            image[row][column].rgbtBlue = fmin(255, sepiaBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp;

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width / 2; column++)
        {
            temp = image[row][column];
            image[row][column] = image[row][width - column - 1];
            image[row][width - column - 1] = temp;
        }
    }
    return;
}

int getBlur(int i, int j, int height, int width, RGBTRIPLE image[height][width], int position)
{
    float count = 0;
    int sum = 0;

    for (int row = i - 1; row <= (i + 1); row++)
    {
        for (int column = j - 1; column <= (j + 1); column++)
        {
            if (row < 0 || row >= height || column < 0 || column >= width)
            {
                continue;
            }
            if (position == RED_COLOUR)
            {
                sum += image[row][column].rgbtRed;
            }
            else if (position == GREEN_COLOUR)
            {
                sum += image[row][column].rgbtGreen;
            }
            else if (position == BLUE_COLOUR) // Corrected the syntax here
            {
                sum += image[row][column].rgbtBlue;
            }

            count++;
        }
    }

    return round(sum / count);
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            copy[row][column] = image[row][column];
        }
    }

    for (int row = 0; row < height; row++)
    {
        for (int column = 0; column < width; column++)
        {
            image[row][column].rgbtRed = getBlur(row, column, height, width, copy, RED_COLOUR);
            image[row][column].rgbtGreen = getBlur(row, column, height, width, copy, GREEN_COLOUR);
            image[row][column].rgbtBlue = getBlur(row, column, height, width, copy, BLUE_COLOUR);
        }
    }

    return;
}
