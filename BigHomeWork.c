/*
Name: Nguyen Huy Hoang
Class: SE1809
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>

struct StudentInfo {
	char Name[30];
	char ID[10];
	int NumberOfCourse;	
};

struct CourseInfo {
	char StudentID[10];
	char Name[20];
};

struct StudentInfo Students[100];
struct CourseInfo Courses[500];

// bien toan cuc
int i, j;
int TotalStudents = 0;
int TotalCourse = 0;
bool IsRunning = true;
//

void Menu();
void Create();
int Find(char StudentID[10]);
void Sort();   // chua nghi ra
void Update(int StudentFoundIndex);  
void DeleteStudent(int StudentIndex);
void DeleteAllStudent();
int IsAlreadyExists(char GivenLine[30], char InfoType, char StudentID[300]);
void ErrorAndRestart(char *Error[100]);
void DeleteCourseByIndex(int CourseIndex);
void DeleteStudentByIndex(int CourseIndex);
void GoBackOrExit();
void ExitProject();

int main () {
	while (IsRunning) {
		Menu();
		int Option;
		scanf("%d", &Option);
		switch(Option) {
			case 1: 
				system("cls");
				printf("\n\t\t********Add a New Student********\n\n");
				Create();
				break;
		}
	}
	return 0;
}

void Menu () {   // menu nguoi dung
	printf("\n\n\t********Student Management System********\n\n");
	printf("\t\t\tMAIN MENU\n");
	printf("\t\t=========================\n");
	printf("\t\t[1] Create.\n");
	printf("\t\t[2] Find student.\n");
	printf("\t\t[3] Sort list.\n");
	printf("\t\t[4] Update student.\n");
	printf("\t\t[5] Delete a student.\n");
	printf("\t\t[6] Delete all student.\n");
	printf("\t\t[0] Exit the Program.\n");
	printf("\t\t=========================\n");
	printf("\t\tEnter your Choice: ");
}

int IsAlreadyExists(char GivenLine[300], char InfoType, char StudentID[300]) { //kiem tra ID da bi trung hay ko
	int IDExists = 0;
	int ep;
	
	for (ep = 0; ep < TotalStudents; ep++) {
		if (strcmp(GivenLine, Students[ep].ID) == 0) {
			IDExists++;
		}
	}
	if (InfoType == 'i') {
		return IDExists;
	} else {
		return 0;
	}
}

void Create () {  // tao hoc sinh
	char StudentID[300];
	char Name[300];
	int NumberOfCourses;
	char CourseName[300];
		
	int IsValidID = 0;  
	while (!IsValidID) {
		printf(" Enter the ID: ");
		scanf("%s", &StudentID);
		if (IsAlreadyExists(StudentID, 'i', StudentID) > 0) {
			printf(" Error: This ID is already exists.\n\n");
			IsValidID = 0;
		} else if (strlen(StudentID) > 10) {
			printf(" Error: ID can not be more than 10 characters.\n\n");
			IsValidID = 0;
		} else if (strlen(StudentID) <= 0) {
			printf(" Error: ID can not be empty.\n\n");
			IsValidID = 0;
		} else {
			IsValidID = 1;
		}
	}
	
	int IsValidName = 0;
	while (!IsValidName) {
		printf(" Enter the Name: ");
		scanf(" %[^\n]s", &Name);
		if (strlen(Name) > 20) {
			printf(" Error: Name can not be more than 20 characters.\n\n");
			IsValidName = 0;
		} else if (strlen(Name) <= 0) {
			printf(" Error: Name can not be empty.\n\n");
			IsValidName = 0;
		} else {
			IsValidName = 1;
		}
	}
	
	int IsValidNumberOfCourse = 0;
	while (!IsValidNumberOfCourse) {
		printf(" Number of courses: ");
		scanf("%d", &NumberOfCourses);
		if(NumberOfCourses <= 0 || NumberOfCourses > 3) {
			printf(" Error: NUmber of courses can not be more than 4 and less than 1.\n\n");
			IsValidNumberOfCourse = 0;
		} else {
			IsValidNumberOfCourse = 1;
		}
	}
	
	strcpy(Students[TotalStudents].ID, StudentID);  // copy lai ID
	strcpy(Students[TotalStudents].Name, Name);
	Students[TotalStudents].NumberOfCourse = NumberOfCourses;
	TotalStudents++;
	
	for (i = 0; i < NumberOfCourses; i++) {
		printf(" Enter Course %d Name: ", i + 1);
		scanf(" %[^\n]s", &CourseName);
		
		strcpy(Courses[TotalCourse].StudentID, StudentID);
		strcpy(Courses[TotalCourse].Name, CourseName);
		TotalCourse++;
	}
	
	printf("\n Student Added Succesfully.\n\n");
}










