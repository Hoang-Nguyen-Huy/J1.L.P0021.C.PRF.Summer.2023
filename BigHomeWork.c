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
				printf("\t\tHow many students do you want to create ?\n");
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










