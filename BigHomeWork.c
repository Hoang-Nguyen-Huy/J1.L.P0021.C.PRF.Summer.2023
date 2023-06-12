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
void ShowAllList(const char *filename);			// xuat tat ca cac ho so cua sinh vien trong file
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
			case 2: 
			    system("cls");
			    printf("\n\t\t********List of all profile********\n\n");
			    ShowAllList("StudentManagement.txt");
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
	printf("\t\t[2] Show all list of profile.\n");
	printf("\t\t[3] Update student.\n");
	printf("\t\t[4] Delete a student.\n");
	printf("\t\t[5] Delete all student.\n");
	printf("\t\t[6] Find a student.\n");
	printf("\t\t[0] Exit the Program.\n");
	printf("\t\t=========================\n");
	printf("\t\tEnter your Choice: ");
}

bool IsExistsInFile(const char *filename, const char *code) {		// kiem tra ID, email, phone da xuat hien trong file hay chua
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
	char PresentAddress[200];  	// noi o hien tai
	char Countries[50];  		// que quan
	
	file = fopen("StudentManagement.txt", "a");
	fprintf(file, "\n");
	fclose(file);
	
	int IsValidName = 0;
	while (!IsValidName) {				// nhap ten sinh vien
		printf(" Enter the Name: ");
		scanf(" %[^\n]s", &Name);			// co the nhap co khoang trang
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
	

	char checkDay[5];					// nhap ngay sinh
	int day; 
	printf(" Enter the day of birth: ");
	scanf("%s", &checkDay);
	while (checkInt(checkDay) == false) {
		printf(" Please enter the valid day!!\n");
		printf(" Enter the day: ");
		scanf("%s", &checkDay);
	}
	if (checkInt(checkDay) == true) {
		day = atoi(checkDay);
	}
	while (day > 31 || day < 1) {
		printf(" Please enter the valid day!!\n");
		printf(" Enter the day: ");
		scanf(" %s", &checkDay);
		while (checkInt(checkDay) == false) {
			printf(" Please enter the valid day!!\n");
			printf(" Enter the day: ");
			scanf(" %s", &checkDay);
		}
		if (checkInt(checkDay) == true) {
			day = atoi(checkDay);
		}
		if (day <= 31 && day >= 1) {
			break;
		}
	}								// nhap xong ngay sinh
	
	
	char checkMonth[5];			// nhap thang sinh
	int month;
	printf(" Enter the month of birth: ");
	scanf("%s", &checkMonth);
	while (checkInt(checkMonth) == false) {
		printf(" Please enter the valid month!!\n");
		printf(" Enter the month of birth: ");
		scanf("%s", &checkMonth);
	}
	if (checkInt(checkMonth) == true) {
		month = atoi(checkMonth);
	}
	while (month > 12 || month < 1) {
		printf(" Please enter the valid month!!\n");
		printf(" Enter the month of birth: ");
		scanf("%s", &checkMonth);
		while (checkInt(checkMonth) == false) {
			printf(" Please enter the valid month!!\n");
			printf(" Enter the month of birth: ");
			scanf("%s", &checkMonth);
		}
		if (checkInt(checkMonth) == true) {
			month = atoi(checkMonth);
		}
		if (month <= 12 && month >= 1) {
			break;
		}
	}							// nhap xong thang sinh
	
	
	char checkYear[5];			// nhap nam sinh
	int year;
	printf(" Enter the year of birth: ");
	scanf("%s", &checkYear);
	while (checkInt(checkYear) == false) {
		printf(" Please enter the valid year!!\n");
		printf(" Enter the year of birth: ");
		scanf("%s", &checkYear);
	}
	if (checkInt(checkYear) == true) {
		year = atoi(checkYear);
	}
	while (year > 2005 || year < 1923) {
		printf(" Please enter the valid year!!\n");
		printf(" Enter the year of birth: ");
		scanf("%s", &checkYear);
		while (checkInt(checkYear) == false) {
			printf(" Please enter the valid year!!\n");
			printf(" Enter the year of birth: ");
			scanf("%s", &checkYear);
		}
		if (checkInt(checkYear) == true) {
			year = atoi(checkYear);
		}
		if (year <= 2005 && year >= 1923) {
			break;
		}
	}								// nhap xong nam sinh
	
	sprintf(DateOfBirth, "%02d-%02d-%04d", day, month, year);      // tao thanh chuoi dd-mm-yy
	file = fopen("StudentManagement.txt", "a");
	fprintf(file, "Date of birth: %s\n", DateOfBirth);		// xuat ngay thang nam sinh vao file
	fclose(file);		
	
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
	
	int IsValidPresentAddress = 0;
	while (!IsValidPresentAddress) {		// nhap dia chi hien tai
		printf(" Enter the present address: ");
		scanf(" %[^\n]s", &PresentAddress);			// nhap co khoang trang
		if (strlen(PresentAddress) > 200) {
			printf(" Error: Enter the address which has under 200 characters.\n\n");
			IsValidPresentAddress = 0;
		} else if (strlen(PresentAddress) <= 0) {
			printf(" Error: Please enter the address.\n\n");
			IsValidPresentAddress = 0;
		} else {
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "Address: %s\n", PresentAddress);		// ghi vao file
			fclose(file);
			IsValidPresentAddress = 1;
		}
	}
	
	int IsValidCountries = 0;
	while (!IsValidCountries) {				// nhap que quan
		printf(" Enter the country: ");
		scanf(" %[^\n]s", &Countries);		// nhap co khoang trang
		if (strlen(Countries) > 50) {
			printf(" Error: This is not valid!\n\n");
			IsValidCountries = 0;
		} else if (strlen(Countries) <= 0) {
			printf(" Error: Please enter the conutry.\n\n");
			IsValidCountries = 0;
		} else {
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "Country: %s\n", Countries);		// ghi vao file
			fclose(file);
			IsValidCountries = 1;
		}
	}
	strcpy(Students[TotalStudents].Name, Name);   					// copy lai Name
	strcpy(Students[TotalStudents].ID, StudentID);  				// copy lai ID
	strcpy(Students[TotalStudents].DateOfBirth, DateOfBirth);		// copy ngay thang nam sinh
	strcpy(Students[TotalStudents].Sex, Sex);						// copy gioi tinh
	strcpy(Students[TotalStudents].Email, Email);					// copy email
	strcpy(Students[TotalStudents].PhoneNumber, Phone); 			// copy dien thoai
	strcpy(Students[TotalStudents].PresentAddress, PresentAddress); // copy dia chi
	strcpy(Students[TotalStudents].Countries, Countries);			// copy que quan
	TotalStudents++;
	
	file = fopen("StudentManagement.txt", "a");
	fprintf(file, "------------------------------------------------\n");	
	
	printf("\n Student Added Succesfully.\n\n");
	fclose(file);
}

void ShowAllList (const char *filename) {			// xuat tat ca cac ho so cua sinh vien trong file
	file = fopen(filename, "r");
	if (file == NULL) {
		printf(" There are no profile of any students.\n\n");
		return;
	}
	
	char ch;
	while ((ch = fgetc(file)) != EOF) {
		putchar(ch);
	}
	fclose(file);
}












