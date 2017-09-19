#include <stdio.h>

//Prototyped methods

int getFileSize(FILE* f);

void createFile(char *fileName, int size);

//Main method

int main ( int argc, char *argv[] )
{
	// argc should have 3 for this program. programName, readFile, writeFile
    if ( argc != 3 )
    {
        /* We print argv[0] assuming it is the program name */
        printf( "usage: %s filename", argv[0] );
    }
    else 
    {
        // argv[1] is the file we read from
        FILE* fp = fopen( argv[1], "r" );

        // file failed to open
        if ( fp == 0 )
        {
            printf( "Could not open file\n" );
        }
        else 
        {
		    int fileSize = getFileSize(fp);
		    printf("%i bytes.\n", fileSize);
			createFile(argv[2], fileSize);
		    fclose(fp);
        }
    }
}

// This method will return how many bytes are in the file.
int getFileSize(FILE* f)
{
	fseek(f, 0 , SEEK_END);
	// an int should work unless George Thomas gives us a huge file.
    int fileSize = ftell(f);
    fseek(f, 0 , SEEK_SET);// needed for next read from beginning of file
    rewind(f);
    printf("%i bytes.\n", fileSize);
    return fileSize;
}

// this will create a csv
void createFile(char *fileName, int size)
{
	FILE *fp;
	fp=fopen(fileName,"w+");
	fprintf(fp, "%i", size);
	
	fclose(fp);
}


