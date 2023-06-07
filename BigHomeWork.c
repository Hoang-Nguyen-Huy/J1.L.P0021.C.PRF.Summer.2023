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
bool checkInt (char input[]) {	// kiem tra co phai la so nguyen hay khong
	int valid = 0;
		while (valid == 0) {
			int isNegative = 0;
			if (input[0] == '-') {
				isNegative = 1;
			}
			int i = isNegative ? 1 : 0;
			while (input[i] != '\0') {
				if (input[i] < '0' || input[i] > '9') {
					break;
				}
				i++;
			}
			if (input[i] == '\0') {
				valid = 1;
				return true;
			} else {
				return false;
			}
		} 
}
void Menu();
void Create();
void ShowAllList();
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
		char Option[50]; // kiem tra su lua chon cua nguoi dung
		int chosen;   // kiem tra su lua chon cua nguoi dung
		scanf("%s", Option);
		while (checkInt(Option) == false) {
			printf("\tPlease enter a valid option: ");
			scanf("%s", Option);
		}
		if (checkInt(Option) == true) {
			chosen = atoi(Option);
		}
		switch(chosen) {
			case 1: 
				system("cls");
				printf("\n\t\t********Add a New Student********\n\n");
				Create();
				break;
			case 7: 
			    system("cls");
			    printf("\n\t\t********List of all students********\n\n");
			    ShowAllList();
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
	printf("\t\t[7] Show all list.\n");
	printf("\t\t[8] Report.\n");
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
	char CheckNumberOfCourses[300]; // kiem tra so luong khoa hoc
	int NumberOfCourses; // kiem tra so luong khoa hoc
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
		scanf("%s", CheckNumberOfCourses);
		while (checkInt(CheckNumberOfCourses) == false) {
			printf(" Please enter a valid number of courses: ");
			scanf("%s", CheckNumberOfCourses);
		}
		if (checkInt(CheckNumberOfCourses) == true) {
			NumberOfCourses = atoi(CheckNumberOfCourses);
		}
		if(NumberOfCourses <= 0 || NumberOfCourses > 3) {
			printf(" Error: NUmber of courses can not be more than 4 and less than 1.\n\n");
			IsValidNumberOfCourse = 0;
		} else {
			IsValidNumberOfCourse = 1;
		}
	}
	
	
	
	for (i = 0; i < NumberOfCourses; i++) {
		printf(" Enter Course %d Name: ", i + 1);
		scanf(" %[^\n]s", &CourseName);
		
		strcpy(Courses[TotalCourse].StudentID, StudentID);
		strcpy(Courses[TotalCourse].Name, CourseName);
		TotalCourse++;
	}
	
	strcpy(Students[TotalStudents].ID, StudentID);  // copy lai ID
	strcpy(Students[TotalStudents].Name, Name);   // copy lai Name
	Students[TotalStudents].NumberOfCourse = NumberOfCourses;	// lay gia tri cua so khoa hoc
	TotalStudents++;
	
	printf("\n Student Added Succesfully.\n\n");
}

void ShowAllList () {    // xuat ra full list
	printf("|==========|====================|===================================================|===============|\n");
    printf("|    ID    |        Name        |                    Course Name                    |   NO.Course   |\n");
    printf("|==========|====================|===================================================|===============|\n");
    
    for (i = 0; i < TotalStudents; i++) {
    	printf("|");
    	printf("%s", Students[i].ID);								// ma sinh vien
    	for (j = 0; j < (10 - strlen(Students[i].ID)); j++) {
    		printf(" ");
		}
		
		printf("|");
		printf("%s", Students[i].Name);								// ten sinh vien
		for (j = 0; j < (20 - strlen(Students[i].Name)); j++) {
			printf(" ");
		}	
		
		printf("|");
		for (j = 0; j < Students[i].NumberOfCourse; j++) {
			printf("%s", Courses[j].Name);
			if (j == Students[i].NumberOfCourse - 1) {
				printf(". ");
				continue;
			}
			printf(", ");
		}
		
		if (Students[i].NumberOfCourse == 1) {
			for (j = 0; j < (51 - 5); j++) {
				printf(" ");
			}
		} else if (Students[i].NumberOfCourse == 2) {
			for (j = 0; j < (51 - 10); j++) {
				printf(" ");
			}
		} else if (Students[i].NumberOfCourse == 3) {
			for (j = 0; j < (51 - 15); j++) {
				printf(" ");
			}
		}
		
		printf("|");
		printf("%d", Students[i].NumberOfCourse);			// so luong khoa hoc
		for (j = 0; j < 14; j++) {
			printf(" ");
		}	
		
		printf("|\n");
		printf("|----------|--------------------|---------------------------------------------------|---------------|\n");
	}
	printf("\n");
}









