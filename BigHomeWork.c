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
	char PhoneNumber[15];	// so dien thoai
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
bool IsExistsInFile(const char *filename, const char *code);
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

bool IsExistsInFile(const char *filename, const char *code) {
	file = fopen(filename, "r");
	if (file == NULL) {
		printf("Canot access to file........\n");
		return false;
	}
	char line[100];
	while (fgets(line, sizeof(line), file) != NULL) {			// kiem tra tung dong
		if (strstr(line, code) != NULL) {				// kiem tra chuoi con trong chuoi lon
			fclose(file);
			return true;
		}
	}
	fclose(file);
	return false;
}

void Create () {  // tao hoc sinh
	char StudentID[50];		// ma sinh vien 
	char Name[50]; 			// ten 
	char DateOfBirth[50]; 		// ngay sinh
	char Sex[10]; 				// gioi tinh
	char Phone[15];  			// so dien thoai
	char Email[50];   			// email
	char PresentAdress[200];  	// noi o hien tai
	char Countries[50];  		// que quan
	
	file = fopen("StudentManagement.txt", "a");
	fprintf(file, "\n");
	fclose(file);
	
	int IsValidName = 0;
	while (!IsValidName) {				// nhap ten sinh vien
		printf(" Enter the Name: ");
		scanf(" %[^\n]s", &Name);
		if (strlen(Name) > 20) {
			printf(" Error: Name can not be more than 20 characters.\n\n");
			IsValidName = 0;
		} else if (strlen(Name) <= 0) {
			printf(" Error: Name can not be empty.\n\n");
			IsValidName = 0;
		} else {
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "Name: %s\n", Name);				// nhap ten vao file
			fclose(file);
			IsValidName = 1;
		}
	}
	
	
	int IsValidID = 0;  
	while (!IsValidID) {				// nhap ma sinh vien
		printf(" Enter the ID: ");
		scanf("%s", &StudentID);
		if (IsExistsInFile("StudentManagement.txt", StudentID) == true) {
			printf(" Error: This ID is already exists.\n\n");
			IsValidID = 0;
		} else if (strlen(StudentID) > 10) {
			printf(" Error: ID can not be more than 10 characters.\n\n");
			IsValidID = 0;
		} else if (strlen(StudentID) <= 0) {
			printf(" Error: ID can not be empty.\n\n");
			IsValidID = 0;
		} else {
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "ID: %s\n", StudentID);			// nhap ma sinh vien vao file
			fclose(file);
			IsValidID = 1;
		}
	}
	
	
	int IsValidSex = 0;
	while (!IsValidSex) {				// nhap gioi tinh
		printf(" Are you [M] Male or [F] Female? ");
		scanf("%s", &Sex);
		if (Sex[0] == 'M' || Sex[0] == 'm') {
			Sex[0] = 'M';
			Sex[1] = 'a';
			Sex[2] = 'l';
			Sex[3] = 'e';
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "Sex: %s\n", Sex);  				// nhap gioi tinh vao file
			fclose(file);
			IsValidSex = 1;
		} else if (Sex[0] == 'F' || Sex[0] == 'f') {
			Sex[0] = 'F';
			Sex[1] = 'e';
			Sex[2] = 'm';
			Sex[3] = 'a';
			Sex[4] = 'l';
			Sex[5] = 'e';
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "Sex: %s\n", Sex);  				// nhap gioi tinh vao file
			fclose(file);
			IsValidSex = 1;
		} else {
			printf(" Error: Your option is not valid!!!\n");
			IsValidSex = 0;
		}
	}		
	

	int IsValidEmail = 0;		
	while (!IsValidEmail) {			// nhap email
		printf(" Enter the email: ");
		scanf("%s", &Email);
		if (IsExistsInFile("StudentManagement.txt", Email) == true) {
			printf(" Error: This Email is ALREADY EXISTS. \n\n");
			IsValidEmail = 0;
		} else if (strlen(Email) > 30) {
			printf(" Error: Email can not be more than 30 characters.\n\n");
			IsValidEmail = 0;
		} else if (strlen(Email) <= 0) {
			printf(" Error: Email can not be empty.\n\n");
			IsValidEmail = 0;
		} else {
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "Email: %s\n", Email);			// nhap email vao file
			fclose(file);
			IsValidEmail = 1;
		}
	}
	
	
	int IsValidPhone = 0;
	while (!IsValidPhone) {								// nhap phone
		printf(" Enter the Phone Number: ");
		scanf("%s", &Phone);
		if (IsExistsInFile("StudentManagement.txt", Phone) == true) {
			printf(" Error: This Phone Number is ALREADY EXISTS.\n");
			IsValidPhone = 0;
		} else if (strlen(Phone) > 11) {
			printf(" Error: Phone can not be more than 11 characters.\n\n");
			IsValidPhone = 0;
		} else if (strlen(Phone) <= 0) {
			printf(" Error: Phone can not be empty.\n\n");
			IsValidPhone = 0;
		} else if (strlen(Phone) < 10 && strlen(Phone) > 0) {
			printf(" Error: This is not a valid phone number.\n");
			IsValidPhone = 0;	
		} else { 
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "Phone number: %s\n", Phone);			// nhap phone vao file
			fclose(file);
			IsValidPhone = 1;
		}
	}
	
	
	strcpy(Students[TotalStudents].Name, Name);   		// copy lai Name
	strcpy(Students[TotalStudents].ID, StudentID);  	// copy lai ID
	strcpy(Students[TotalStudents].Sex, Sex);			// copy gioi tinh
	strcpy(Students[TotalStudents].Email, Email);		// copy email
	strcpy(Students[TotalStudents].PhoneNumber, Phone); // copy dien thoai
	TotalStudents++;
	
	file = fopen("StudentManagement.txt", "a");
	fprintf(file, "---------------------\n");	
	
	printf("\n Student Added Succesfully.\n\n");
	fclose(file);
}











