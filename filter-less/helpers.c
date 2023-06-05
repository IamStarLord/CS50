#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through the pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average;
            // average all three colors
            average = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;
            average = round(average / 3.0);

            // printf("%i\n", (int) average);

            // assigin the average value
            image[i][j].rgbtBlue = (int) average;
            image[i][j].rgbtGreen = (int) average;
            image[i][j].rgbtRed = (int) average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // edge cases: make sure to round the result
    // make sure it is capped to 255

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixel = image[i][j];

            float sepiaRed = 0.393 * pixel.rgbtRed + 0.769 * pixel.rgbtGreen + 0.189 * pixel.rgbtBlue;
            float sepiaGreen = 0.349 * pixel.rgbtRed + 0.686 * pixel.rgbtGreen + 0.168 * pixel.rgbtBlue;
            float sepiaBlue = 0.272 * pixel.rgbtRed + 0.534 * pixel.rgbtGreen + 0.131 * pixel.rgbtBlue;

            // cap at 255
            if (sepiaRed > 255.0)
            {
                sepiaRed = 255.0;
            }
            if (sepiaGreen > 255.0)
            {
                sepiaGreen = 255.0;
            }
            if (sepiaBlue > 255.0)
            {
                sepiaBlue = 255.0;
            }

            // assign each as the new pixel value
            image[i][j].rgbtBlue = (int) round(sepiaBlue);
            image[i][j].rgbtGreen = (int) round(sepiaGreen);
            image[i][j].rgbtRed = (int) round(sepiaRed);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // horizontally reverse an image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            // reverse the row
            RGBTRIPLE pixel1 = image[i][j];
            RGBTRIPLE pixel2 = image[i][(width - 1) - j];

            RGBTRIPLE temp = pixel1;
            pixel1 = pixel2;
            pixel2 = temp;

            image[i][j] = pixel1;
            image[i][(width - 1) - j] = pixel2;

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // make a deep copy of the image
    RGBTRIPLE(*image_copy)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image_copy == NULL)
    {
        printf("Not enough memory to store image.\n");
        return;
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // image_copy[i][j] = image_copy[i][j];
            image_copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_copy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    // iterate over all the pixels in the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // re-initialize counter for averaging
            int avg_counter = 0;
            float blur_red = 0.0;
            float blur_blue = 0.0;
            float blur_green = 0.0;

            // add the pixel left of the current pixel
            if (j - 1 >= 0)
            {
                blur_blue += image_copy[i][j - 1].rgbtBlue;
                blur_green += image_copy[i][j - 1].rgbtGreen;
                blur_red += image_copy[i][j - 1].rgbtRed;
                // add to the counter for averaging
                avg_counter++;

            }
            // add the pixel right of the current pixel
            if (j + 1 < width)
            {
                blur_blue += image_copy[i][j + 1].rgbtBlue;
                blur_green += image_copy[i][j + 1].rgbtGreen;
                blur_red += image_copy[i][j + 1].rgbtRed;
                // add to the counter for averaging
                avg_counter++;
            }
            // add the pixel above the current pixel
            if (i - 1 >= 0)
            {
                blur_blue += image_copy[i - 1][j].rgbtBlue;
                blur_green += image_copy[i - 1][j].rgbtGreen;
                blur_red += image_copy[i - 1][j].rgbtRed;
                // add to the counter for averaging
                avg_counter++;
            }
            // add the pixel below the current pixel
            if (i + 1 < height)
            {
                blur_blue += image_copy[i + 1][j].rgbtBlue;
                blur_green += image_copy[i + 1][j].rgbtGreen;
                blur_red += image_copy[i + 1][j].rgbtRed;
                // add to the counter for averaging
                avg_counter++;
            }
            // add corner pixels
            if (i - 1 >= 0 && j - 1 >= 0)
            {
                blur_blue += image_copy[i - 1][j - 1].rgbtBlue;
                blur_green += image_copy[i - 1][j - 1].rgbtGreen;
                blur_red += image_copy[i - 1][j - 1].rgbtRed;
                // add to the counter for averaging
                avg_counter++;
            }
            if (i + 1 < height && j - 1 >= 0)
            {
                blur_blue += image_copy[i + 1][j - 1].rgbtBlue;
                blur_green += image_copy[i + 1][j - 1].rgbtGreen;
                blur_red += image_copy[i + 1][j - 1].rgbtRed;
                // add to the counter for averaging
                avg_counter++;
            }
            if (j + 1 < width && i - 1 >= 0)
            {
                blur_blue += image_copy[i - 1][j + 1].rgbtBlue;
                blur_green += image_copy[i - 1][j + 1].rgbtGreen;
                blur_red += image_copy[i - 1][j + 1].rgbtRed;
                // add to the counter for averaging
                avg_counter++;
            }
            if (i + 1 < height && j + 1 < width)
            {
                blur_blue += image_copy[i + 1][j + 1].rgbtBlue;
                blur_green += image_copy[i + 1][j + 1].rgbtGreen;
                blur_red += image_copy[i + 1][j + 1].rgbtRed;
                // add to the counter for averaging
                avg_counter++;
            }
            // compute final average

            blur_blue = blur_blue / avg_counter;
            blur_green = blur_green / avg_counter;
            blur_red = blur_red / avg_counter;

            image[i][j].rgbtBlue = (int) blur_blue;
            image[i][j].rgbtGreen = (int) blur_green;
            image[i][j].rgbtRed = (int) blur_red;


        }
    }
    free(image_copy);

    return;
}
