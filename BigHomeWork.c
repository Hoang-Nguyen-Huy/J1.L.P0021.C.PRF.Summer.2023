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
	char Name[30];			// ten
	char ID[10];			// ma sinh vien
	char Email[100];		// email
	char PhoneNumber[50];	// so dien thoai
	char Sex[10];		// gioi tinh
	char DateOfBirth[50];	// ngay sinh
	char PresentAddress[100];	// noi o hien tai
	char Countries[100];		// que quan
};


struct StudentInfo Students[100];


// bien toan cuc
int i, j, z;
int TotalStudents = 0;
bool IsRunning = true;
FILE *file;
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
		}
	}
	return 0;
}

void Menu () {   // menu nguoi dung
	printf("\n\n\t********Student Management System********\n\n");
	printf("\t\t\tMAIN MENU\n");
	printf("\t\t=========================\n");
	printf("\t\t[1] Add a new student to the list.\n");
	printf("\t\t[2] Find student.\n");
	printf("\t\t[3] Update student.\n");
	printf("\t\t[4] Delete a student.\n");
	printf("\t\t[5] Delete all student.\n");
	printf("\t\t[6] Show all list.\n");
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
	char StudentID[50];		// ma sinh vien 
	char Name[50]; 			// ten 
	char DateOfBirth[50]; 		// ngay sinh
	char Sex[10]; 				// gioi tinh
	char Phone[15];  			// so dien thoai
	char Email[50];   			// email
	char PresentAdress[100];  	// noi o hien tai
	char Countries[50];  		// que quan
	
	file = fopen("StudentManagement.txt", "a");			// goi file
	
	if (file == NULL) {
		printf("Can't access to file\n");
		exit(1);
	}
	
	int IsValidName = 0;
	while (!IsValidName) {			// nhap ten sinh vien
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
	
	int IsValidID = 0;  
	while (!IsValidID) {				// nhap ma sinh vien
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
	

	int IsValidSex = 0;
	while (!IsValidSex) {
		printf(" Are you [M]Male or [F]Female? ");
		scanf("%s", &Sex);
		if (Sex[0] == 'M' || Sex[0] == 'F') {
			IsValidSex = 1;
		} else {
			printf(" Error: Your gender is not valid!!!\n\n");
			IsValidSex = 0;
		}
	}		
	
	
	
	
	strcpy(Students[TotalStudents].ID, StudentID);  // copy lai ID
	strcpy(Students[TotalStudents].Name, Name);   // copy lai Name
	
	fprintf(file, "Name: %s\n", Name);
	fprintf(file, "ID: %s\n", StudentID);
	fprintf(file, "Sex: %c\n", Sex[0]);
	fprintf(file, "\n\n");
	TotalStudents++;
	
	
	printf("\n Student Added Succesfully.\n\n");
	fclose(file);
}











