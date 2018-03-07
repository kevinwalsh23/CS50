/**
 * Copies a BMP piece by piece, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"
int paddingnew;
int main(int argc, char *argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        fprintf(stderr, "Usage: ./copy infile outfile\n");
        return 1;
    }

    // remember filenames
    int a = atoi(argv[1]);
    char *infile = argv[2];
    char *outfile = argv[3];

    // open input file 
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", infile);
        return 2;
    }

    // open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 3;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);
    
    // read infile's BITMAPINFOHEADER
    
    
    
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);
    
    BITMAPINFOHEADER bigone = bi;
    BITMAPFILEHEADER bfgone = bf;
    
    bigone.biWidth = bi.biWidth * a;
    bigone.biHeight = bi.biHeight * a ;
    bigone.biSizeImage = ((sizeof(RGBTRIPLE) * bigone.biWidth) + paddingnew) * abs(bigone.biHeight);
    //int Widthnew= bi.biWidth * a;
    bfgone.bfSize = (54 + bigone.biSizeImage);
    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 4;
    }

    // write outfile's BITMAPFILEHEADER
    fwrite(&bfgone, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bigone, sizeof(BITMAPINFOHEADER), 1, outptr);

    // determine padding for scanlines
    //bi.biWidth = bi.biWidth * a;
    //bi.biHeight = bi.biHeight * a;
    int padding = (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
     paddingnew = ((4 - (bigone.biWidth * sizeof(RGBTRIPLE)) % 4) % 4);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        //iterate over pixels in scanline
        //for (int y = 0; y < a; y++)
        //{
        
        
        for (int w = 0; w < a; w++)
        {
        for (int j = 0; j < bi.biWidth; j++)
        {
            // temporary storage
            RGBTRIPLE triple;

            // read RGB triple from infile
            fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

            // write RGB triple to outfile
            for (int z = 0; z < a; z++)
           {
            fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
            
           }
           
           //}
        //f   fseek(outptr, -(bigone.biWidth + paddingnew), SEEK_CUR);
        }
        
        

        // skip over padding, if any
        fseek(inptr, padding, SEEK_CUR);

        // then add it back (to demonstrate how)
        
        //if (paddingnew != 0)
        //{
        for (int k = 0; k < paddingnew; k++)
        {
            fputc(0x00, outptr);
        }
        
         fseek(inptr, -(bi.biWidth * 3 + padding), SEEK_CUR);
        }
        fseek(inptr, (bi.biWidth * 3 + padding), SEEK_CUR);
        
           
        //}
        //irelse
        //{ 
        //    return 1;
     //fseek(outptr, (bigone.biWidth * 3 + paddingnew), SEEK_CUR);
    // fseek(inptr, -(bi.biWidth * 3 + padding), SEEK_CUR);   
    }
     //fseek(outptr, (bigone.biWidth * 3 + paddingnew), SEEK_CUR);
     //fseek(inptr, (bi.biWidth * 3 + padding), SEEK_CUR);
        
    
   // }

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // success
    return 0;
}

