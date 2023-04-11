//
// Created by stasc on 31.03.2023.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct.h"

#ifndef LAB3SEM2_FUNCTIONS_H
#define LAB3SEM2_FUNCTIONS_H
BMPFile* loadBMPFile(const char* fileName);
void freeBMPFile(BMPFile* bmp_file);
char* inputStr();
void printBMPHeaders (const BMPFile* bmpFile);
void invertImage(BMPFile* bmp_file);
double power(double base, double exponent);
void BlackAndWhite(BMPFile* bmp_file);
void writeBMPFile(const BMPFile* bmp_file,const char*);
void gammaCorrection(BMPFile* bmp_file, double gamma);
void medianFilter(BMPFile* bmp_file, int windowWidth);
int menu();
#endif //LAB3SEM2_FUNCTIONS_H
