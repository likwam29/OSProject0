#include <stdio.h>
#include "student.h"

//Prototyped methods

int getFileSize(FILE* f);

void createFile(char *fileName, int size);

void buildStudentArray(FILE* f, struct student students[], int length);

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
        FILE* fp = fopen( argv[1], "rb" );

        // file failed to open
        if ( fp == 0 )
        {
            printf( "Could not open file\n" );
        }
        else 
        {
			// get the file size and # of records
		    int fileSize = getFileSize(fp);
			int numOfStudents = fileSize / 76;
			printf("%i students\n", numOfStudents);
			// create array of structs
			struct student students[numOfStudents];
			// populate the array of structs
			buildStudentArray(fp, students, numOfStudents);
		    printf("%i bytes.\n", fileSize);
			// create .csv file
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

void buildStudentArray(FILE* f, struct student students[], int length)
{
	int i;
	for(i=0; i<length; i++)
	{
		fread(&students[i].Id, sizeof(students[i].Id), 1, f);
		fread(&students[i].First, sizeof(students[i].First), 1, f);
		fread(&students[i].Last, sizeof(students[i].Last), 1, f);
		fread(&students[i].Q1, sizeof(students[i].Q1), 1, f);
		fread(&students[i].Q2, sizeof(students[i].Q2), 1, f);
		fread(&students[i].Q3, sizeof(students[i].Q3), 1, f);
		fread(&students[i].L1, sizeof(students[i].L1), 1, f);
		fread(&students[i].L2, sizeof(students[i].L2), 1, f);
		fread(&students[i].A1, sizeof(students[i].A1), 1, f);
		fread(&students[i].E1, sizeof(students[i].E1), 1, f);
		fread(&students[i].E2, sizeof(students[i].E2), 1, f);
	}
}


