#include "helpers.h"
#include <math.h>
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            RGBTRIPLE point = image[i][j];
            int mean = (int) (point.rgbtBlue + point.rgbtGreen + point.rgbtRed) / 3;
            point.rgbtBlue = mean; point.rgbtGreen = mean; point.rgbtRed = mean;
            image[i][j] = point; //??? Do I actually need this or pointer handles that?
            // Answer: It doesn't. Either this way or the one below works.
//            RGBTRIPLE *point = &image[i][j];
//            int mean = (int) (point->rgbtBlue + point->rgbtGreen + point->rgbtRed) / 3;
//            point->rgbtBlue = mean; point->rgbtGreen = mean; point->rgbtRed = mean;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < (width/2); column++) {
            RGBTRIPLE temp = image[row][(width-1-column)];
            image[row][(width-1-column)] = image[row][column];
            image[row][column] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];
    int difs[] = { -1, 0, 1 };
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            int count = 0, redSum = 0,  blueSum = 0, greenSum = 0;
            for (int indexX = 0; indexX < 3; indexX++) {
                for (int indexY = 0; indexY < 3; indexY++) {
                    if (row+difs[indexX] < height && row+difs[indexX] > 0 && column+difs[indexY] < width && column+difs[indexY] > 0) {
                        RGBTRIPLE neighbor = image[row+difs[indexX]][column+difs[indexY]];
                        redSum += neighbor.rgbtRed ; greenSum += neighbor.rgbtGreen; blueSum += neighbor.rgbtBlue;
                        count++;
                    }
                }
            }
            RGBTRIPLE point;
            point.rgbtBlue = (int) blueSum / count; point.rgbtGreen = (int) greenSum / count; point.rgbtRed = (int) redSum / count;
            temp[row][column] = point;
        }
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }
    
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    
    RGBTRIPLE temp[height][width];
    
    int x[] = {1, 2 ,1};
    int multipliers[] = { -1, 0, 1 };
    
    int mulXs[3][3];
    int mulYs[3][3];
    
    int locsX[3][3];
    int locsY[3][3];
    
    for (int i = 0; i < 3; i++) {
        int y = multipliers[i];
        for (int j = 0; j < 3; j++) {
            locsX[i][j] = multipliers[j];
            locsY[i][j] = y;
        }
    }

    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            mulXs[i][j] = x[i] * multipliers[j];
            mulYs[i][j] = x[i] * multipliers[i];
        }
    }
    
    for (int row = 0; row < height; row++) {
        for (int column = 0; column < width; column++) {
            int redGx = 0, redGy = 0, greenGx = 0, greenGy = 0, blueGx = 0, blueGy = 0;
            int red; int green; int blue; RGBTRIPLE newPoint;
            for (int xIndex = 0; xIndex < 3; xIndex++) {
                for (int yIndex = 0; yIndex < 3; yIndex++) {
                    int dx = locsX[xIndex][yIndex];
                    int dy = locsY[xIndex][yIndex];
                    int mulX = mulXs[xIndex][yIndex];
                    int mulY = mulYs[xIndex][yIndex];
                    if (row + dx < height && row + dx > 0 && column + dy < width && column + dy > 0) {
                        RGBTRIPLE point = image[row+dx][column+dy];
                        redGx += (point.rgbtRed * mulX);
                        redGy += (point.rgbtRed * mulY);
                        greenGx += (point.rgbtGreen * mulX);
                        greenGy += (point.rgbtGreen * mulY);
                        blueGx += (point.rgbtBlue * mulX);
                        blueGy += (point.rgbtBlue * mulY);
                    }
                }
            }
            red = (int) sqrt(pow(redGx, 2) + pow(redGy, 2)) % 255;
            green = (int) sqrt(pow(greenGx, 2) + pow(greenGy, 2)) % 255;
            blue = (int) sqrt(pow(blueGx, 2) + pow(blueGy, 2)) % 255;
            newPoint.rgbtRed = red; newPoint.rgbtGreen = green; newPoint.rgbtBlue = blue;
            temp[row][column] = newPoint;
        }
    }
    
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = temp[i][j];
        }
    }
    
    return;
}
