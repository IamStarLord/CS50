#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through the image matrix,
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            RGBTRIPLE pixel = image[h][w];
            // check if the pixel is black
            if (pixel.rgbtBlue == 0x00 && pixel.rgbtGreen == 0x00 && pixel.rgbtRed == 0x00)
            {
                image[h][w].rgbtBlue = 0x7a;
                image[h][w].rgbtGreen = 0x25;
                image[h][w].rgbtRed = 0x94;
            }
        }
    }
    // Change all black pixels to a color of your choosing
}
