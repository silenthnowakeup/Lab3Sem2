//
// Created by stasc on 31.03.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#ifndef LAB3SEM2_FUNCTIONS_H
#define LAB3SEM2_FUNCTIONS_H

#pragma pack(1)

typedef struct BMPHeader
{
    unsigned char ID[2];
    unsigned int fileSize;
    unsigned char unused[4];
    unsigned int pixelOffset;
}BMPHeader;

typedef struct DIBHeader
{
    unsigned int headerSize;
    unsigned int width;
    unsigned int height;
    unsigned short colorPlanes;
    unsigned short bitsPerPixel;
    unsigned int comp;
    unsigned int dataSize;
    unsigned int pwidth;
    unsigned int pheight;
    unsigned int colorsCount;
    unsigned int ipmColorsCount;
}DIBHeader;

typedef struct Pixel {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} Pixel;

typedef struct BMPFile
{
    BMPHeader bmphdr;
    DIBHeader dibhdr;
    unsigned char colorTable[1024];
    Pixel** pixels;
}BMPFile;

#pragma pop

BMPFile* loadBMPFile(char* fileName);
void freeBMPFile(BMPFile* bmp_file);
char* inputStr();
void printBMPHeaders (BMPFile* bmpFile);
void invertImage(BMPFile* bmp_file);
void BlackAndWhite(BMPFile* bmp_file);
void writeBMPFile(BMPFile* bmp_file, char*);
void gammaCorrection(BMPFile* bmp_file, double gamma);
void medianFilter(BMPFile* bmp_file, int windowWidth);
int menu();
#endif //LAB3SEM2_FUNCTIONS_H
