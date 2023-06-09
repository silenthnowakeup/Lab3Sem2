#include "functions.h"

int main() {
    printf("Enter Name of File::");
    char *str = inputStr();
    const char *check = strrchr(str, '.');
    if (check != NULL && strcmp(check + 1, "bmp") == 0) {
        printf("<<Okay, this file I support>>\n");
        } else {
        printf("File  <<%s>> is not BMP format.\n", str);
        return 0;
    }
    char *str2;
    int field;
    float gamma;
    printf("\n");
    BMPFile *bmpFile = loadBMPFile(str);

    while (1)
    {
        switch (menu())
        {
            case 1:
                invertImage(bmpFile);
                break;
            case 2:
                BlackAndWhite(bmpFile);
                break;
            case 3:
                printf("Enter gamma::");
                while (scanf("%f", &gamma) != 1 || getchar() != '\n' || gamma <= 0)
                {
                    printf("Wrong input!\n");
                    rewind(stdin);

                }
                printf("\n");
                gammaCorrection(bmpFile, gamma);
                break;
            case 4:
                printf("Enter field::");
                while (scanf("%d", &field) != 1 || getchar() != '\n' || field <= 0)
                {
                    printf("Wrong input!\n");
                    rewind(stdin);

                }
                printf("\n");
                medianFilter(bmpFile, field);
                break;
            case 5:
                printBMPHeaders(bmpFile);
                break;
            default:
                freeBMPFile(bmpFile);
                printf("Good luck :))))");
                return 0;
        }

        printf("Enter name of file::");
        str2 = inputStr();
        const char *check2 = strrchr(str2, '.');
        if (check != NULL && strcmp(check2 + 1, "bmp") == 0) {
            printf("<<Okay, this file I support>>\n");
        } else {
            printf("File  <<%s>> is not BMP format.\n", str2);
            return 0;
        }
        printf("\n");
        writeBMPFile(bmpFile, str2);
    }
}
