// Matthew Likwarz
// Project 0
// CS 421

#include <stdio.h>
#include <limits.h>
#include <math.h>
#include<string.h>
#include "student.h"

//Prototyped methods
// method comments are above actual methods instead of both prototyped and method.

int getFileSize(FILE* f);

void createFile(char *fileName, struct student students[], struct superMath math, int size);

void buildStudentArray(FILE* f, struct student students[], int length);

void calculateGrades(struct student students[], int length);

void getMin(float arr[], struct student students[], int length);

void getMax(float arr[], struct student students[], int length);

void getAvg(float arr[], struct student students[], int length);

void getSD(float arr[], struct student students[], int length);

float calcStandDev(float arr[], int length);

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

			// create array of structs
			struct student students[numOfStudents];

			// populate the array of structs
			buildStudentArray(fp, students, numOfStudents);

			// clost the read file
		    fclose(fp);
			
			// calculate the students grade based on read in data
			calculateGrades(students, numOfStudents);

			struct superMath mathStruct;

			// do math and populate mathStruct
			getMin(mathStruct.min, students, numOfStudents);
			getMax(mathStruct.max, students, numOfStudents);
			getAvg(mathStruct.avg, students, numOfStudents);
			getSD(mathStruct.std, students, numOfStudents);

			// create .csv file
			createFile(argv[2], students, mathStruct, numOfStudents);
        }
    }
	return 0;
}

// This method will return how many bytes are in the file.
int getFileSize(FILE* f)
{
	fseek(f, 0 , SEEK_END);
	// an int should work unless George Thomas gives us a huge file.
    int fileSize = ftell(f);
    fseek(f, 0 , SEEK_SET);// needed for next read from beginning of file
    rewind(f);
    return fileSize;
}

// this will create a csv in the specified format from handout
void createFile(char *fileName, struct student students[], struct superMath math, int size)
{
	// create a file
	FILE *fp;
	
	// check to see if fileName passed in has .csv extension
	char *isPresent;
	isPresent = strchr(fileName, '.');
	if(isPresent == NULL)
	{
		fileName = strcat(fileName,".csv");
	}
	
	// open a write stream
	fp=fopen(fileName,"w+");
	
	// Write into csv
	
	// print out column header to file
	fprintf(fp, "Id,First Name,Last Name,Quiz1,Quiz2,Quiz3,Lab1,Lab2,Assignment1,Exam1,Exam2,Grade");
	
	//print out student scores and grade
	int i;
	for(i=0; i<size; i++)
	{
		// print Id and name
		fprintf(fp, "\n%i,%s,%s,", students[i].Id, students[i].First, students[i].Last);
		// print quiz scores
		fprintf(fp, "%i,%i,%i,", (int)students[i].Q1, (int)students[i].Q2, (int)students[i].Q3);
		// print labs
		fprintf(fp, "%i,%i,", (int)students[i].L1, (int)students[i].L2);
		// print assignment
		fprintf(fp, "%i,", (int)students[i].A1);
		// print exams
		fprintf(fp, "%i,%i,", (int)students[i].E1, (int)students[i].E2);
		// print Grade
		fprintf(fp, "%.2f", students[i].Grade);
	}

	// print out min
	fprintf(fp, "\n,,Min");
	int j;
	for(j=0; j<8; j++)
	{
		fprintf(fp, ",%i", (int)math.min[j]);
	}
	fprintf(fp, ",%.2f", math.min[8]);

	// print out max
	fprintf(fp, "\n,,Max");
	for(j=0; j<8; j++)
	{
		fprintf(fp, ",%i", (int)math.max[j]);
	}
	fprintf(fp, ",%.2f", math.max[8]);

	// print out avg
	fprintf(fp, "\n,,Avg");
	for(j=0; j<9; j++)
	{
		fprintf(fp, ",%.2f", math.avg[j]);
	}

	// print out std
	fprintf(fp, "\n,,Std");
	for(j=0; j<9; j++)
	{
		fprintf(fp, ",%.2f", math.std[j]);
	}
	
	// close the file
	fclose(fp);
}

// This method will read a file and build an array of students out of it
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

/* This method takes in an array of students and a number of students
	and calculates their grade and sets that value in Grade
*/
void calculateGrades(struct student students[], int length)
{
	int i;
	for(i = 0; i<length; i++)
	{
		float quizAvg = (students[i].Q1 + students[i].Q2 + students[i].Q3) / 30;
		float labAvg = (students[i].L1 + students[i].L2) / 40;
		float assAvg = students[i].A1 / 50;
		float examAvg = (students[i].E1 + students[i].E2) / 200;
		float grade = (quizAvg * 10) + (labAvg * 20) + (assAvg * 30) + (examAvg * 40);
		students[i].Grade = grade;
	}
}

// This will get the min for each assignment and push it into an array
void getMin(float arr[], struct student students[], int length)
{
	int i, j;
	for(i=0; i<9; i++)
	{
		float min = INT_MAX;
		for(j=0; j<length; j++)
		{
			if(i==0)
			{
				if(students[j].Q1 < min)
					min = students[j].Q1;
			}
			else if(i==1)
			{
				if(students[j].Q2 < min)
					min = students[j].Q2;
			}
			else if(i==2)
			{
				if(students[j].Q3 < min)
					min = students[j].Q3;
			}
			else if(i==3)
			{
				if(students[j].L1 < min)
					min = students[j].L1;
			}
			else if(i==4)
			{
				if(students[j].L2 < min)
					min = students[j].L2;
			}
			else if(i==5)
			{
				if(students[j].A1 < min)
					min = students[j].A1;
			}
			else if(i==6)
			{
				if(students[j].E1 < min)
					min = students[j].E1;
			}
			else if(i==7)
			{
				if(students[j].E2 < min)
					min = students[j].E2;
			}
			else if(i==8)
			{
				if(students[j].Grade < min)
					min = students[j].Grade;
			}
		}
		arr[i] = min;
	}
}

// This will get the max for each assignment and push it into an array
void getMax(float arr[], struct student students[], int length)
{
	int i, j;
	for(i=0; i<9; i++)
	{
		float max = INT_MIN;
		for(j=0; j<length; j++)
		{
			if(i==0)
			{
				if(students[j].Q1 > max)
					max = students[j].Q1;
			}
			else if(i==1)
			{
				if(students[j].Q2 > max)
					max = students[j].Q2;
			}
			else if(i==2)
			{
				if(students[j].Q3 > max)
					max = students[j].Q3;
			}
			else if(i==3)
			{
				if(students[j].L1 > max)
					max = students[j].L1;
			}
			else if(i==4)
			{
				if(students[j].L2 > max)
					max = students[j].L2;
			}
			else if(i==5)
			{
				if(students[j].A1 > max)
					max = students[j].A1;
			}
			else if(i==6)
			{
				if(students[j].E1 > max)
					max = students[j].E1;
			}
			else if(i==7)
			{
				if(students[j].E2 > max)
					max = students[j].E2;
			}
			else if(i==8)
			{
				if(students[j].Grade > max)
					max = students[j].Grade;
			}
		}
		arr[i] = max;
	}
}

// This will get the avg for each assignment and push it into an array
void getAvg(float arr[], struct student students[], int length)
{
	int i, j;
	for(i=0; i<9; i++)
	{
		float avg = 0;
		for(j=0; j<length; j++)
		{
			if(i==0)
			{
				avg += students[j].Q1;
			}
			else if(i==1)
			{
				avg += students[j].Q2;
			}
			else if(i==2)
			{
				avg += students[j].Q3;
			}
			else if(i==3)
			{
				avg += students[j].L1;
			}
			else if(i==4)
			{
				avg += students[j].L2;
			}
			else if(i==5)
			{
				avg += students[j].A1;
			}
			else if(i==6)
			{
				avg += students[j].E1;
			}
			else if(i==7)
			{
				avg += students[j].E2;
			}
			else if(i==8)
			{
				avg += students[j].Grade;
			}
		}
		arr[i] = avg / length;
	}
}

// this will build an array of standard deviations
void getSD(float arr[], struct student students[], int length)
{
	int i, j;
	for(i=0; i<9; i++)
	{
		float tempArr[length];
		float sd;
		for(j=0; j<length; j++)
		{
			if(i==0)
			{
				tempArr[j] = students[j].Q1;
				sd = calcStandDev(tempArr, length);
			}
			else if(i==1)
			{
				tempArr[j] = students[j].Q2;
				sd = calcStandDev(tempArr, length);
			}
			else if(i==2)
			{
				tempArr[j] = students[j].Q3;
				sd = calcStandDev(tempArr, length);
			}
			else if(i==3)
			{
				tempArr[j] = students[j].L1;
				sd = calcStandDev(tempArr, length);
			}
			else if(i==4)
			{
				tempArr[j] = students[j].L2;
				sd = calcStandDev(tempArr, length);
			}
			else if(i==5)
			{
				tempArr[j] = students[j].A1;
				sd = calcStandDev(tempArr, length);
			}
			else if(i==6)
			{
				tempArr[j] = students[j].E1;
				sd = calcStandDev(tempArr, length);
			}
			else if(i==7)
			{
				tempArr[j] = students[j].E2;
				sd = calcStandDev(tempArr, length);
			}
			else if(i==8)
			{
				tempArr[j] = students[j].Grade;
				sd = calcStandDev(tempArr, length);
			}
		}
		arr[i] = sd;
	}
}

// this will calculate the standard deviation
float calcStandDev(float arr[], int length)
{
    float sum = 0.0, avg, standardDeviation = 0.0;

    int i;

    for(i=0; i<length; ++i)
        sum += arr[i];

    avg = sum/length;

    for(i=0; i<length; ++i)
        standardDeviation += pow(arr[i] - avg, 2);

    return sqrt(standardDeviation/(length - 1));
}






