#include <stdio.h>
#include <cs50.h>
#include <stdint.h>
#include <stdlib.h>

int main(int argc, char *argv[]) 
//int main(void) 
{
    //ensure 1 argument is entered
   if (argc != 2)
    {
        fprintf(stderr, "Usage: No File entered\n");
        return 1;
    }
    //open file
   
    FILE *file = fopen(argv[1], "r");
   //FILE *file = fopen("card.raw", "r");
    
    if (file == NULL)
    {
        fclose(file);
        printf("Cannot recover files\n");
        return 2;
    }
    
    //repeat over memory card until end of file
   // int a = (sizeof(atio(argv[1])) / 512);
    //int a = atoi(sizeof(argv[1]));
    //int a = sizeof(argv[1]);
    //for (int z = 0; z > a; z++)
  
  FILE* img = NULL;
   
 int picfound = 0;
  
  unsigned char buffer[512];
  
  int b = 0;
  
    //while (!feof(file))
  while (fread(buffer, 512, 1, file) == 1)
    {
        //read file in 512 byte increments
       // fread(file, 512, 1, file);
       //unsigned char buffer[512];
       // fread(&buffer, 512, 1, file);
        
        //int q = 1;
        //determine if block is not equal to 512 bytes and end the file/program
        //if(buffer[q - 1] != 512)
        //if(file[a] != 512)
        
        //{
          //  return 0;
        //}
       // int b = 0;
        //determine if first first bytes of 512 block are start of JPEG,
       
       //FILE* img = NULL;
       
        if(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
       // if(file[0] == 0xff && file[1] == 0xd8 && file[2] == Oxff && (file[3] & 0xf0) == 0xe0)
        {
            if (picfound == 1)
            {
                fclose(img);
            }
            else
            {
                picfound = 1;
            }
            //create new filename for JPEG
            char filename[8];
            sprintf(filename, "%03d.jpg", b);
            //b++;
            //open new jpeg file
            img = fopen(filename, "w");
            b++;
            //write blocks into new file until the first first bytes of the block are the begging of a JPEG
           //do
            //{
            //fread(buffer, 512, 1, file);
        }
            if (picfound == 1)
            {
                fwrite(&buffer, 512, 1, img);
            }
            //fwrite(&buffer, 512, 1, img);
            //}
           // while (!(buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0));
           // while ((file[0] != 0xff && file[1] != 0xd8 && file[2] != Oxff && (file[3] & 0xf0) != 0xe0))
            
           //fclose(img);
        
       // else if (b > 0)
    //    {
            // put jpg into temp
         //   fwrite(buffer, 512, 1, img); 
  //  }
    
     //fclose(img);
   //  fread(&buffer, sizeof(buffer), 1, file);
    }
    fclose(img);
    fclose(file);
    return 0;
    

    
}

