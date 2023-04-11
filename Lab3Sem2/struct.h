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
#pragma pack(pop)
