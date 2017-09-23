
// this is a struct built to represent a student
typedef struct student {
	int Id;
	char First[20];
	char Last[20];
	float Q1;
	float Q2;
	float Q3;
	float L1;
	float L2;
	float A1;
	float E1;
	float E2;
	float Grade;
}Student;

// this struct acts as a container class for the csv. that way I dont have so many arguments
typedef struct superMath {
	float min[9];
	float max[9];
	float avg[9];
	float std[9];
}SuperMath;
