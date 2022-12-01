#include <math.h>
#include <stdio.h>
#include <string.h>
#include "helpers.h"

typedef uint8_t  BYTE;

// do the pixel swaps
void swap(RGBTRIPLE *a, RGBTRIPLE *b)
{
    RGBTRIPLE tmp = *a;
    *a = *b;
    *b = tmp;
}

// checks if the pixel value is greater than the limit 255, if the value is set to the limit.
int is_greater_than_255(int *sepiaRgb)
{
    if (*sepiaRgb > 255)
    {
        *sepiaRgb = 255;
    }

    return *sepiaRgb;
}

// calculates the values of neighboring pixels and adds them to the pixels in the original image.
void take_the_average_blur(int h, int w, RGBTRIPLE copy[h][w], int values[3][3], RGBTRIPLE *pixel)
{
    int sum_rgbtblue = 0;
    int sum_rgbtgreen = 0;
    int sum_rgbtred = 0;

    int column_len = values[0][0];
    int line_len = values[0][1];

    for (int i = 0; i < column_len; i++)
    {
        int column_pixel = values[1][i];
        for (int j = 0; j < line_len; j++)
        {
            int line_pixel = values[2][j];
            RGBTRIPLE blur_pixel = copy[column_pixel][line_pixel];

            sum_rgbtblue += blur_pixel.rgbtBlue;
            sum_rgbtgreen += blur_pixel.rgbtGreen;
            sum_rgbtred += blur_pixel.rgbtRed;
        }
    }

    float matriz_size = column_len * line_len;

    float average_rgbtblue = round(sum_rgbtblue / matriz_size);
    float average_rgbtgreen = round(sum_rgbtgreen / matriz_size);
    float average_rgbtred = round(sum_rgbtred / matriz_size);

    pixel -> rgbtBlue = average_rgbtblue;
    pixel -> rgbtGreen = average_rgbtgreen;
    pixel -> rgbtRed = average_rgbtred;
}

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            float average = round(sum / 3.0);

            image[i][j].rgbtBlue = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtRed = average;
        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int sepiaRed = round(0.393 * image[i][j].rgbtRed + 0.769 * image[i][j].rgbtGreen + 0.189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(0.349 * image[i][j].rgbtRed + 0.686 * image[i][j].rgbtGreen + 0.168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(0.272 * image[i][j].rgbtRed + 0.534 * image[i][j].rgbtGreen + 0.131 * image[i][j].rgbtBlue);

            is_greater_than_255(&sepiaRed);
            is_greater_than_255(&sepiaGreen);
            is_greater_than_255(&sepiaBlue);

            image[i][j].rgbtBlue = sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;
        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            swap(&image[i][j], &image[i][width - (j + 1)]);
        }
    }

    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // create a copy of the image
    RGBTRIPLE copy_image[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            copy_image[i][j] = image[i][j];
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // separate the value from the size of a 2d array
            // to store information about neighboring pixel values
            int (*p)[3][3] = NULL;

            if (i != 0 && j != 0 && i != height && j != width)
            {
                int values[3][3] = {{ 3, 3 }, { i, i - 1, i + 1 }, { j, j - 1, j + 1 }};
                p = &values;
            }
            // canto superior esquerdo
            if (i == 0 && j == 0)
            {
                int values[3][3] = {{ 2, 2 }, { i, i + 1 }, { j, j + 1}};
                p = &values;
            }
            // canto superior direito
            if (i == 0 && j == (width - 1))
            {
                int values[3][3] = {{ 2, 2 }, { i, i + 1 }, { j, j - 1 }};
                p = &values;
            }
            // canto inferior esquerdo
            if (i == (height - 1) && j == 0)
            {
                int values[3][3] = {{ 2, 2 }, { i, i - 1 }, { j, j + 1 }};
                p = &values;
            }
            // canto inferior direito
            if (i == (height - 1) && j == (width - 1))
            {
                int values[3][3] = {{ 2, 2 }, { i, i - 1 }, { j, j - 1 }};
                p = &values;
            }
            // borda superior
            if (i == 0 && (j != 0 && j != (width - 1)))
            {
                int values[3][3] = {{ 2, 3 }, { i, i + 1 }, { j, j - 1, j + 1 }};
                p = &values;
            }
            // borda inferior
            if (i == (height - 1) && (j != 0 && j != (width - 1)))
            {
                int values[3][3] = {{ 2, 3 }, { i, i - 1 }, { j, j - 1, j + 1 }};
                p = &values;
            }
            // borda esquerda
            if ((i != 0 && i != (height - 1)) && j == 0)
            {
                int values[3][3] = {{ 3, 2 }, { i, i - 1, i + 1 }, { j, j + 1 }};
                p = &values;
            }
            // borda direita
            if ((i != 0 && i != (height  - 1)) && j == (width - 1))
            {
                int values[3][3] = {{ 3, 2 }, { i, i - 1, i + 1 }, { j, j - 1 }};
                p = &values;
            }
            take_the_average_blur(height, width, copy_image, *p, &image[i][j]);
        }

    }

    return;
}