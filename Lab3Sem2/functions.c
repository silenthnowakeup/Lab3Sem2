//
// Created by stasc on 31.03.2023.
//

#include "functions.h"
#define count 1024

BMPFile* loadBMPFile(const char* fileName)
{
    FILE* fp;
    if ((fp = fopen(fileName,"rb")) == NULL)
    {
        printf("Error\n");
        exit(1);
    }
    BMPFile* bmp_file = (BMPFile*)calloc(1,sizeof(BMPFile));
    fread(&bmp_file->bmphdr,sizeof(BMPHeader),1,fp);
    fread(&bmp_file->dibhdr,sizeof(DIBHeader),1,fp);

    bmp_file->pixels = malloc(sizeof(Pixel*) * bmp_file->dibhdr.height);
    for (int i = 0; i < bmp_file->dibhdr.height; i++) {
        bmp_file->pixels[i] = malloc(sizeof(Pixel) * bmp_file->dibhdr.width);
    }
    if (bmp_file->dibhdr.bitsPerPixel == 1 || bmp_file->dibhdr.bitsPerPixel == 2 || bmp_file->dibhdr.bitsPerPixel == 4 || bmp_file->dibhdr.bitsPerPixel == 8  || bmp_file->dibhdr.bitsPerPixel == 16)
    {
        unsigned int rowPadding = (4-((bmp_file->dibhdr.width * bmp_file->dibhdr.bitsPerPixel / 8) %4 )) %4;
        fread(bmp_file->colorTable,sizeof(unsigned char),count,fp);
        for (int i = bmp_file->dibhdr.height-1; i >=0;i--)
        {
            for (int j = 0;j < bmp_file->dibhdr.width;j++)
            {
                unsigned char pixel;
                fread(&pixel, sizeof(unsigned char),1, fp);
                bmp_file->pixels[i][j].red = pixel;
                bmp_file->pixels[i][j].green = pixel;
                bmp_file->pixels[i][j].blue = pixel;
            }
                if(bmp_file->dibhdr.bitsPerPixel == 8)
                {
                    fseek(fp,rowPadding,SEEK_CUR);
                }
        }
    }
    else if(bmp_file->dibhdr.bitsPerPixel == 24) {
        fseek(fp, bmp_file->bmphdr.pixelOffset, SEEK_SET);
        for (int i = 0; i < bmp_file->dibhdr.height; i++) {
            for (int j = 0; j < bmp_file->dibhdr.width; j++) {
                fread(&bmp_file->pixels[i][j], sizeof(Pixel), 1, fp);
            }
        }
    }
    fclose(fp);
    return bmp_file;
}


void writeBMPFile(const BMPFile* bmp_file,const char* fileName)
{
    FILE* fp;
    if ((fp = fopen(fileName,"wb")) == NULL)
    {
        printf("Error\n");
        exit(1);
    }
    fwrite(&bmp_file->bmphdr, sizeof(bmp_file->bmphdr), 1, fp);
    fwrite(&bmp_file->dibhdr, sizeof(bmp_file->dibhdr), 1, fp);

    if (bmp_file->dibhdr.bitsPerPixel == 1 || bmp_file->dibhdr.bitsPerPixel == 2 || bmp_file->dibhdr.bitsPerPixel == 4 || bmp_file->dibhdr.bitsPerPixel == 8  || bmp_file->dibhdr.bitsPerPixel == 16) {
        unsigned int rowPadding = (4 - ((bmp_file->dibhdr.width * bmp_file->dibhdr.bitsPerPixel / 8) % 4)) % 4;;
        fwrite(bmp_file->colorTable, sizeof(unsigned char), count, fp);
        for (int i = bmp_file->dibhdr.height-1; i >= 0; i--) {
            for (int j = 0; j < bmp_file->dibhdr.width; j++) {
                unsigned char pixel = bmp_file->pixels[i][j].red;
                fwrite(&pixel, sizeof(unsigned char), 1, fp);
            }
            if (bmp_file->dibhdr.bitsPerPixel == 8) {
                int k = 0;
                while (k < rowPadding) {
                    fputc(0x00, fp);
                    k++;
                }
            }
        }
    }
    else if(bmp_file->dibhdr.bitsPerPixel == 24)
    {
        fseek(fp,bmp_file->bmphdr.pixelOffset,SEEK_SET);
        for (int i = 0; i < bmp_file->dibhdr.height; i++) {
            for (int j = 0; j < bmp_file->dibhdr.width; j++) {
                fwrite(&bmp_file->pixels[i][j],sizeof(Pixel),1,fp);
            }
        }
    }
    fclose(fp);
}



    void freeBMPFile(BMPFile* bmp_file)
{
    if (bmp_file)
    {
        free(bmp_file);
    }
}

char* inputStr() {
    char* str = NULL;
    int pos = 0;
    int len = 0;
    int c = getchar();

    while (c != '\n') {
        if (pos == len) {
            len += 10;
            str = (char*) realloc(str, len * sizeof(char));
        }

        str[pos] = c;
        pos++;
        c = (int)getchar();
    }

    if (pos == len) {
        len++;
        str = (char*) realloc(str, len * sizeof(char));
    }

    str[pos] = '\0';
    return str;
}

void printBMPHeaders (const BMPFile* bmpFile)
{
    printf("ID[2]=%c%c;\nfileSize = %d;\npixelOffset=%d;\n",bmpFile->bmphdr.ID[0],bmpFile->bmphdr.ID[1],bmpFile->bmphdr.fileSize,bmpFile->bmphdr.pixelOffset);
    printf("headerSize=%d;\n"
           "width=%d;\n"
           "height=%d;\n"
           "colorPlanes=%d;\n"
           "bitsPerPixel=%d;\n"
           "comp=%d;\n"
           "dataSize=%d;\n"
           "pwidth=%d;\n"
           "pheight=%d;\n"
           "colorsCount=%d;\n"
           "ipmColorsCount=%d;\n",bmpFile->dibhdr.headerSize,
           bmpFile->dibhdr.width,
           bmpFile->dibhdr.height,
           bmpFile->dibhdr.colorPlanes,
           bmpFile->dibhdr.bitsPerPixel,
           bmpFile->dibhdr.comp,
           bmpFile->dibhdr.dataSize,
           bmpFile->dibhdr.pwidth,
           bmpFile->dibhdr.pheight,
           bmpFile->dibhdr.colorsCount,
           bmpFile->dibhdr.ipmColorsCount);
}

int menu()
{
    int value;
    printf("1. Negative\n");
    printf("2. Grayscale\n");
    printf("3. Gamma correction\n");
    printf("4. Median Filter\n");
    printf("5. Show information of header\n");
    printf("6. Exit\n");

    while (scanf("%d", &value) != 1 || getchar() != '\n' || value <= 0 || value>6)
    {
        printf("Wrong input!\n");
        rewind(stdin);

    }
    return value;
}

void invertImage(BMPFile* bmp_file) {
    if (bmp_file->dibhdr.bitsPerPixel == 1 || bmp_file->dibhdr.bitsPerPixel == 2 || bmp_file->dibhdr.bitsPerPixel == 4 || bmp_file->dibhdr.bitsPerPixel == 8) {
        for (int i = 0; i < count; i++) {
            bmp_file->colorTable[i] = 255 - bmp_file->colorTable[i];
        }
    } else {
        for (int i = 0; i < bmp_file->dibhdr.height; i++) {
            for (int j = 0; j < bmp_file->dibhdr.width; j++) {
                Pixel pixel = bmp_file->pixels[i][j];
                pixel.red = 255 - pixel.red;
                pixel.green = 255 - pixel.green;
                pixel.blue = 255 - pixel.blue;
                bmp_file->pixels[i][j] = pixel;
            }
        }
    }
}


void BlackAndWhite(BMPFile* bmp_file) {
    if (bmp_file->dibhdr.bitsPerPixel == 1 || bmp_file->dibhdr.bitsPerPixel == 2 || bmp_file->dibhdr.bitsPerPixel == 4 || bmp_file->dibhdr.bitsPerPixel == 8 || bmp_file->dibhdr.bitsPerPixel == 16) {
        for (int i = 0; i < count/3; i+=3) {
            unsigned char gray = (bmp_file->colorTable[i] + bmp_file->colorTable[i+1] + bmp_file->colorTable[i+2]) / 3;
            bmp_file->colorTable[i] = gray;
            bmp_file->colorTable[i+1] = gray;
            bmp_file->colorTable[i+2] = gray;


        }
    }

    else {
        for (int i = 0; i<bmp_file->dibhdr.height;i++)
        {
            for (int j=0;j<bmp_file->dibhdr.width;j++)
            {
                Pixel* pixel = &bmp_file->pixels[i][j];
                unsigned char gray = (pixel->red + pixel->green + pixel->blue)/3;
                pixel->red = gray;
                pixel->green = gray;
                pixel->blue = gray;
            }

        }
    }
}

double power(double base, int exponent) {
    double result = 1.0;

    while (exponent > 0) {
        result *= base;
        exponent--;
    }

    return result;
}

void gammaCorrection(BMPFile* bmp_file, double gamma1) {
    if (bmp_file->dibhdr.bitsPerPixel == 1 || bmp_file->dibhdr.bitsPerPixel == 2 || bmp_file->dibhdr.bitsPerPixel == 4 || bmp_file->dibhdr.bitsPerPixel == 8  || bmp_file->dibhdr.bitsPerPixel == 16) {
        for (int i = 0; i<count; i++)
        {
            unsigned char gamma = (char)(255.0 * power(bmp_file->colorTable[i] / 255.0, gamma1));
            bmp_file->colorTable[i] = gamma;
        }
    }

    else
    {
    for (int i = 0; i < bmp_file->dibhdr.height; i++) {
        for (int j = 0; j < bmp_file->dibhdr.width; j++) {
            unsigned char red = (char)(255.0 * power(bmp_file->pixels[i][j].red / 255.0,  gamma1));
            unsigned char green = (char)(255.0 * power(bmp_file->pixels[i][j].green / 255.0, gamma1));
            unsigned char blue = (char)(255.0 * power(bmp_file->pixels[i][j].blue / 255.0, gamma1));
            bmp_file->pixels[i][j].red = red;
            bmp_file->pixels[i][j].green = green;
            bmp_file->pixels[i][j].blue = blue;
        }
    }
    }
}

int median(unsigned char arr[], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[i]) {
                unsigned char temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }

    if (n % 2 == 0) {
        return (arr[n/2] + arr[n/2-1]) / 2;
    } else {
        return arr[n/2];
    }
}

void medianFilter(BMPFile* bmp, int size) {

    int radius = size / 2;

    Pixel** oldPixels = bmp->pixels;
    Pixel** newPixels = (Pixel**) malloc(bmp->dibhdr.height * sizeof(Pixel*));
    for (int i = 0; i < bmp->dibhdr.height; i++) {
        newPixels[i] = (Pixel*) malloc(bmp->dibhdr.width * sizeof(Pixel));
    }

    for (int y = radius; y < bmp->dibhdr.height-radius; y++) {
        for (int x = radius; x < bmp->dibhdr.width-radius; x++) {
            unsigned char red[size*size], green[size*size], blue[size*size];
            int idx = 0;
            for (int j = y-radius; j <= y+radius; j++) {
                for (int i = x-radius; i <= x+radius; i++) {
                    red[idx] = oldPixels[j][i].red;
                    green[idx] = oldPixels[j][i].green;
                    blue[idx] = oldPixels[j][i].blue;
                    idx++;
                }
            }
            newPixels[y][x].red = (unsigned char)median(red, size*size);
            newPixels[y][x].green = (unsigned char)median(green, size*size);
            newPixels[y][x].blue = (unsigned char)median(blue, size*size);
        }
    }

    bmp->pixels = newPixels;

    for (int i = 0; i < bmp->dibhdr.height; i++) {
        free(oldPixels[i]);
    }
    free(oldPixels);
}
