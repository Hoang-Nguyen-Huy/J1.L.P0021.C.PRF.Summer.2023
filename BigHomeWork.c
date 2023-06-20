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
void SearchStudent(const char *filename);
int compareNames(const void* a, const void* b);
void Sort(const char *filename);   // chua nghi ra
void Update(const char *filename);  
void DeleteSelectedStudent(const char *filename);		
void DeleteAllStudent(const char *filename);		// xoa tat ca trong  file
bool IsExistsInFile(const char *filename, const char *code);
void GoBackOrExit();			// thoat case de quay lai menu chinh hoac exit chuong trinh
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
				GoBackOrExit();
				break;
			case 2: 
			    system("cls");
			    printf("\n\t\t********List of all profile********\n\n");
			    ShowAllList("StudentManagement.txt");
			    printf("\n\n");
			    GoBackOrExit();
			    break;
			case 3: 
				system("cls");
				printf("\n\t\t********Updating profile********\n\n");
				Update("StudentManagement.txt");
				printf("\n\n");
				GoBackOrExit();
				break;
			case 4: 
			    system("cls");
			    DeleteSelectedStudent("StudentManagement.txt");
			    printf("\n\n");
			    GoBackOrExit();
			    break;
			case 5: 
				system("cls");
				DeleteAllStudent("StudentManagement.txt");
				GoBackOrExit();
				break;
			case 6: 
				system("cls");
				SearchStudent("StudentManagement.txt");
				GoBackOrExit();
				break;
			case 7: 
				system("cls");
				Sort("StudentManagement.txt");
				GoBackOrExit();
				break;
			case 0: 
				IsRunning = false;
				ExitProject();
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
	printf("\t\t[7] Sort all list.\n");				//???
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
	char line[500];
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
		
	int IsValidName = 0;
	while (!IsValidName) {				// nhap ten sinh vien
		printf(" Enter the Name: ");
		scanf(" %[^\n]s", &Name);			// co the nhap co khoang trang
		if (strlen(Name) > 30) {
			printf(" Error: Name can not be more than 30 characters.\n\n");
			IsValidName = 0;
		} else if (strlen(Name) <= 0) {
			printf(" Error: Name can not be empty.\n\n");
			IsValidName = 0;
		} else {
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "Full name: %s\t", Name);				// nhap ten vao file
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
			fprintf(file, "ID: %s\t", StudentID);			// nhap ma sinh vien vao file
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
	fprintf(file,"Birthday: %s\t", DateOfBirth);		// xuat ngay thang nam sinh vao file
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
			fprintf(file, "Sex: %s\t", Sex);  				// nhap gioi tinh vao file
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
			fprintf(file, "Sex: %s\t", Sex);  				// nhap gioi tinh vao file
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
			fprintf(file, "Email: %s\t", Email);			// nhap email vao file
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
			fprintf(file, "  Phone number: %s\t", Phone);			// nhap phone vao file
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
			fprintf(file, "Address: %s\t", PresentAddress);		// ghi vao file
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
			fprintf(file, "Country: %s\t\n", Countries);		// ghi vao file
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
	
	printf("\n Student Added Succesfully.\n\n");

}

void ShowAllList (const char *filename) {			// xuat tat ca cac ho so cua sinh vien trong file
	file = fopen(filename, "r");
	if (file == NULL) {
		printf(" There are no profile of any students.\n\n");
		return;
	}
	int IsEmpty = 1;
	char ch;
	while ((ch = fgetc(file)) != EOF) {
		putchar(ch);
		IsEmpty = 0;
	}
	fclose(file);
	if (IsEmpty == 1) {
		printf(" EMPTY file.\n\n");
	}
}

void SearchStudent(const char *filename) {			// tim kiem
	char Option;			// lua chon de nhap ten hoac id
	char Name[40];			// ten
	char ID[20];			// ma sinh vien			
	char line[500];			// bien dung de tim kiem bang ten va id
	
	// kiem tra file co rong hay khong
	file = fopen(filename, "r");	
	fseek(file, 0, SEEK_END);	// di chuyen con tro toi cuoi file
	if (ftell(file) == 0) {
		printf(" EMPTY file.\n\n");
		fclose(file);
		return;		// neu file rong thi return 
	}
	fclose(file);
	//kiem tra xong
	
	int IsSearching = 0;
	while (!IsSearching) {
		printf(" Search by name[N]? or by ID[I]?: ");
		scanf(" %c", &Option);
		printf("\n");
		if (Option == 'N' || Option == 'n') {		// tim kiem bang ten
			printf(" Enter the name: ");
			scanf(" %[^\n]s", &Name);
			printf("\n\n");
			if (IsExistsInFile(filename, Name) == false) {
				printf(" The '%s' is not found.\n\n", Name);
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;									// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);
				printf("\n");	
				if (Choices == 'Y' || Choices == 'y') {			
					IsSearching = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsSearching = 1;
				}
			} else {
				file = fopen(filename, "r");
				while (fgets(line, sizeof(line), file) != NULL) {
					if (strstr(line, Name) != NULL) {
						printf("%s", line);	
					}
				}
				printf("\n\n");
				fclose(file);
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;								// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);						
				printf("\n");
				if (Choices == 'Y' || Choices == 'y') {
					IsSearching = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsSearching = 1;
				}
			}
		} else if (Option == 'I' || Option == 'i') {			// tim kien bang ma sinh vien 
			printf(" Enter the ID: ");				
			scanf(" %s", &ID);
			printf("\n\n");
			if (IsExistsInFile(filename, ID) == false) {
				printf(" The ID: '%s' is not found.\n\n", ID);
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;						// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);
				printf("\n");
				if (Choices == 'Y' || Choices == 'y') {
					IsSearching = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsSearching = 1;
				}
			} else {
				file = fopen(filename, "r");
				while (fgets(line, sizeof(line), file) != NULL) {
					if (strstr(line, ID) != NULL) {
						printf("%s", line);	
					}
				}
				printf("\n\n");
				fclose(file);
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;							// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);
				printf("\n");
				if (Choices == 'Y' || Choices == 'y') {
					IsSearching = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsSearching = 1;
				}
			}
		}
	}
	
}

int compareNames(const void* a, const void* b) {
	const struct StudentInfo* StudentsA = (const struct StudentInfo*)a;
	const struct StudentInfo* StudentsB = (const struct StudentInfo*)b;
	return strcmp(StudentsA->Name, StudentsB->Name);
}

void Sort (const char *filename) {
	qsort(Students, TotalStudents, sizeof(struct StudentInfo), compareNames);
	file = fopen(filename, "w");
	
	for (i = 0; i < TotalStudents; i++) {
		fprintf(file, "Full name: %s\t", Students[i].Name);				// nhap ten vao file		
		fprintf(file, "ID: %s\t", Students[i].ID);			// nhap ma sinh vien vao file
		fprintf(file,"Birthday: %s\t", Students[i].DateOfBirth);		// xuat ngay thang nam sinh vao file
		fprintf(file, "Sex: %s\t", Students[i].Sex);  				// nhap gioi tinh vao file
		fprintf(file, "Email: %s\t", Students[i].Email);			// nhap email vao file
		fprintf(file, "  Phone number: %s\t", Students[i].PhoneNumber);			// nhap phone vao file
		fprintf(file, "Address: %s\t", Students[i].PresentAddress);		// ghi vao file
		fprintf(file, "Country: %s\t\n", Students[i].Countries);		// ghi vao file
	}
	fclose(file);
	printf("\n\n Sort successfully\n\n");
	
}

void Update (const char *filename) {   // cap nhat thong tin 
	FILE *inputFile;
	FILE *tempFile;
	char line[200];
	char Option;
	char Name[40];
	char ID[20];
	
	// kiem tra file co rong hay khong
	inputFile = fopen(filename, "r");	
	fseek(inputFile, 0, SEEK_END);	// di chuyen con tro toi cuoi file
	if (ftell(inputFile) == 0) {
		printf(" EMPTY file.\n\n");
		fclose(inputFile);
		return;		// neu file rong thi return 
	}
	fclose(inputFile);
	//kiem tra xong
	
	int IsUpdating = 0;
	while (IsUpdating == 0) {
		printf(" Enter the name[N] or the id[I]: ");
		scanf(" %c", &Option);
		printf("\n");
		if (Option == 'N' || Option == 'n') {
			printf(" Enter the name: ");
			scanf(" %[^\n]s", &Name);
			printf("\n\n");
			if (IsExistsInFile(filename, Name) == false) {
				printf(" The '%s' is not found.\n\n", Name);
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;									// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);
				printf("\n");	
				if (Choices == 'Y' || Choices == 'y') {			
					IsUpdating = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsUpdating = 1;
				}
			} else {
				int numEl = 0;
				// tim xem ten co trong file hay khong
				inputFile = fopen(filename, "r");
				while (fgets(line, sizeof(line), inputFile) != NULL) {
					if (strstr(line, Name) != NULL) {
						numEl++;
						printf("%s", line);	
					}
				}
				printf("\n\n");
				fclose(inputFile);
				// end
				
				if (numEl < 2) {
					char Choice;
					printf(" There is %d student. \n\n", numEl);
					printf(" Do you want to update the above student? [Y/N]. Your answer: ");
					scanf(" %c", &Choice);
					printf("\n\n");
					if (Choice == 'Y' || Choice == 'y') {
						int found = 0;
						//mo file goc de doc du lieu
						inputFile = fopen(filename, "r");
						if (inputFile == NULL) {
							printf(" Can't access to file!!!");
							return;
						}
						
						// tao file tam thoi de luu du lieu sau khi cap nhat
						tempFile = fopen("temp.txt", "w");
						if (tempFile == NULL) {
							printf(" Can't access to file!!!");
							fclose(inputFile);
							return;
						}
						
						// tim va cap nhat dong chua thong tin nguoi dung muon cap nhat
						while (fgets(line, sizeof(line), inputFile)) {
							if (strstr(line, Name) != NULL) {
								found = 1;
								char newName[40];
								char newID[20];
								char newEmail[100];
								char newPhone[20];
								char newSex[10];
								char newBirthday[50];
								char newAddress[100];
								char newCountry[50];
								
								int IsValidName = 0;
								while (!IsValidName) {				// nhap ten sinh vien
									printf(" Enter the Name: ");
									scanf(" %[^\n]s", &newName);			// co the nhap co khoang trang
									if (strlen(newName) > 30) {
										printf(" Error: Name can not be more than 30 characters.\n\n");
										IsValidName = 0;
									} else if (strlen(newName) <= 0) {
										printf(" Error: Name can not be empty.\n\n");
										IsValidName = 0;
									} else {
										fprintf(tempFile, "Full name: %s\t", newName);				// nhap ten vao file
										IsValidName = 1;
									}
								}
								
								int IsValidID = 0;  
								while (!IsValidID) {				// nhap ma sinh vien
									printf(" Enter the ID: ");
									scanf("%s", &newID);
									if (IsExistsInFile("StudentManagement.txt", newID) == true) {
										printf(" Error: This ID has been used.\n");
										IsValidID = 0;
									} else if (strlen(newID) > 10) {
										printf(" Error: ID can not be more than 10 characters.\n\n");
										IsValidID = 0;
									} else if (strlen(newID) <= 0) {
										printf(" Error: ID can not be empty.\n\n");
										IsValidID = 0;
									} else {
										fprintf(tempFile, "ID: %s\t", newID);			// nhap ma sinh vien vao file
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
								
								sprintf(newBirthday, "%02d-%02d-%04d", day, month, year);      // tao thanh chuoi dd-mm-yy
								fprintf(tempFile,"Birthday: %s\t", newBirthday);		// xuat ngay thang nam sinh vao file
								
								int IsValidSex = 0;
								while (!IsValidSex) {				// nhap gioi tinh
									printf(" Are you [M] Male or [F] Female? ");
									scanf("%s", &newSex);
									if (newSex[0] == 'M' || newSex[0] == 'm') {
										newSex[0] = 'M';
										newSex[1] = 'a';
										newSex[2] = 'l';
										newSex[3] = 'e';
										fprintf(tempFile, "Sex: %s\t", newSex);  				// nhap gioi tinh vao file
										IsValidSex = 1;
									} else if (newSex[0] == 'F' || newSex[0] == 'f') {
										newSex[0] = 'F';
										newSex[1] = 'e';
										newSex[2] = 'm';
										newSex[3] = 'a';
										newSex[4] = 'l';
										newSex[5] = 'e';
										fprintf(tempFile, "Sex: %s\t", newSex);  				// nhap gioi tinh vao file
										IsValidSex = 1;
									} else {
										printf(" Error: Your option is not valid!!!\n");
										IsValidSex = 0;
									}
								}
								
								int IsValidEmail = 0;		
								while (!IsValidEmail) {			// nhap email
									printf(" Enter the email: ");
									scanf("%s", &newEmail);
									if (IsExistsInFile("StudentManagement.txt", newEmail) == true) {
										printf(" Error: This email has already been used.\n\n");
										IsValidEmail = 0;
									} else if (strlen(newEmail) > 30) {
										printf(" Error: Email can not be more than 30 characters.\n\n");
										IsValidEmail = 0;
									} else if (strlen(newEmail) <= 0) {
										printf(" Error: Email can not be empty.\n\n");
										IsValidEmail = 0;
									} else {
										fprintf(tempFile, "Email: %s\t", newEmail);			// nhap email vao file
										IsValidEmail = 1;
									}
								}
								
								int IsValidPhone = 0;
								while (!IsValidPhone) {								// nhap phone
									printf(" Enter the Phone Number: ");
									scanf("%s", &newPhone);
									if (IsExistsInFile("StudentManagement.txt", newPhone) == true) {
										printf(" Error: This phone number has already been used.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) > 11) {
										printf(" Error: Phone can not be more than 11 characters.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) <= 0) {
										printf(" Error: Phone can not be empty.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) < 10 && strlen(newPhone) > 0) {
										printf(" Error: This is not a valid phone number.\n");
										IsValidPhone = 0;	
									} else { 
										fprintf(tempFile, "  Phone number: %s\t", newPhone);			// nhap phone vao file
										IsValidPhone = 1;
									}
								}
								
								int IsValidPresentAddress = 0;
								while (!IsValidPresentAddress) {		// nhap dia chi hien tai
									printf(" Enter the present address: ");
									scanf(" %[^\n]s", &newAddress);			// nhap co khoang trang
									if (strlen(newAddress) > 200) {
										printf(" Error: Enter the address which has under 200 characters.\n\n");
										IsValidPresentAddress = 0;
									} else if (strlen(newAddress) <= 0) {
										printf(" Error: Please enter the address.\n\n");
										IsValidPresentAddress = 0;
									} else {
										fprintf(tempFile, "Address: %s\t", newAddress);		// ghi vao file
										IsValidPresentAddress = 1;
									}
								}
								
								int IsValidCountries = 0;
								while (!IsValidCountries) {				// nhap que quan
									printf(" Enter the country: ");
									scanf(" %[^\n]s", &newCountry);		// nhap co khoang trang
									if (strlen(newCountry) > 50) {
										printf(" Error: This is not valid!\n\n");
										IsValidCountries = 0;
									} else if (strlen(newCountry) <= 0) {
										printf(" Error: Please enter the conutry.\n\n");
										IsValidCountries = 0;
									} else {
										fprintf(tempFile, "Country: %s\t\n", newCountry);		// ghi vao file
										IsValidCountries = 1;
									}
								}
								
							} else {
								fputs(line, tempFile);
							}
						}
						
						//dong file goc va file tam thoi
						fclose(inputFile);
						fclose(tempFile);
						
						if (found) {
							// xoa file goc
							remove(filename);
							
							// doi ten file tam thoi thanh ten file goc
							rename("temp.txt", filename);
							printf(" \n\nUpdate successfully\n\n");
						} else {
							printf(" The '%s' is not found", Name);
							remove("temp.txt");
						}
					} else if (Choice == 'N' || Choice == 'n') {
						IsUpdating = 1;
					}
				} else {
					char studentID[20];
					printf(" There are %d students.\n\n", numEl);
					printf(" Enter the student's ID that you want to update: ");
					scanf(" %s", &studentID);
					int found = 0;
					//mo file goc de doc du lieu
					inputFile = fopen(filename, "r");
					if (inputFile == NULL) {
						printf(" Can't access to file!!!");
						return;
					}
						
					// tao file tam thoi de luu du lieu sau khi cap nhat
					tempFile = fopen("temp.txt", "w");
					if (tempFile == NULL) {
						printf(" Can't access to file!!!");
						fclose(inputFile);
						return;
					}
					
					// tim va cap nhat dong chua thong tin nguoi dung muon cap nhat
						while (fgets(line, sizeof(line), inputFile)) {
							if (strstr(line, studentID) != NULL) {
								found = 1;
								char newName[40];
								char newID[20];
								char newEmail[100];
								char newPhone[20];
								char newSex[10];
								char newBirthday[50];
								char newAddress[100];
								char newCountry[50];
								
								int IsValidName = 0;
								while (!IsValidName) {				// nhap ten sinh vien
									printf(" Enter the Name: ");
									scanf(" %[^\n]s", &newName);			// co the nhap co khoang trang
									if (strlen(newName) > 30) {
										printf(" Error: Name can not be more than 30 characters.\n\n");
										IsValidName = 0;
									} else if (strlen(newName) <= 0) {
										printf(" Error: Name can not be empty.\n\n");
										IsValidName = 0;
									} else {
										fprintf(tempFile, "Full name: %s\t", newName);				// nhap ten vao file
										IsValidName = 1;
									}
								}
								
								int IsValidID = 0;  
								while (!IsValidID) {				// nhap ma sinh vien
									printf(" Enter the ID: ");
									scanf("%s", &newID);
									if (IsExistsInFile("StudentManagement.txt", newID) == true) {
										printf(" Error: This ID has been used.\n");
										IsValidID = 0;
									} else if (strlen(newID) > 10) {
										printf(" Error: ID can not be more than 10 characters.\n\n");
										IsValidID = 0;
									} else if (strlen(newID) <= 0) {
										printf(" Error: ID can not be empty.\n\n");
										IsValidID = 0;
									} else {
										fprintf(tempFile, "ID: %s\t", newID);			// nhap ma sinh vien vao file
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
								
								sprintf(newBirthday, "%02d-%02d-%04d", day, month, year);      // tao thanh chuoi dd-mm-yy
								fprintf(tempFile,"Birthday: %s\t", newBirthday);		// xuat ngay thang nam sinh vao file
								
								int IsValidSex = 0;
								while (!IsValidSex) {				// nhap gioi tinh
									printf(" Are you [M] Male or [F] Female? ");
									scanf("%s", &newSex);
									if (newSex[0] == 'M' || newSex[0] == 'm') {
										newSex[0] = 'M';
										newSex[1] = 'a';
										newSex[2] = 'l';
										newSex[3] = 'e';
										fprintf(tempFile, "Sex: %s\t", newSex);  				// nhap gioi tinh vao file
										IsValidSex = 1;
									} else if (newSex[0] == 'F' || newSex[0] == 'f') {
										newSex[0] = 'F';
										newSex[1] = 'e';
										newSex[2] = 'm';
										newSex[3] = 'a';
										newSex[4] = 'l';
										newSex[5] = 'e';
										fprintf(tempFile, "Sex: %s\t", newSex);  				// nhap gioi tinh vao file
										IsValidSex = 1;
									} else {
										printf(" Error: Your option is not valid!!!\n");
										IsValidSex = 0;
									}
								}
								
								int IsValidEmail = 0;		
								while (!IsValidEmail) {			// nhap email
									printf(" Enter the email: ");
									scanf("%s", &newEmail);
									if (IsExistsInFile("StudentManagement.txt", newEmail) == true) {
										printf(" Error: This email has already been used.\n\n");
										IsValidEmail = 0;	
									} else if (strlen(newEmail) > 30) {
										printf(" Error: Email can not be more than 30 characters.\n\n");
										IsValidEmail = 0;
									} else if (strlen(newEmail) <= 0) {
										printf(" Error: Email can not be empty.\n\n");
										IsValidEmail = 0;
									} else {
										fprintf(tempFile, "Email: %s\t", newEmail);			// nhap email vao file
										IsValidEmail = 1;
									}
								}
								
								int IsValidPhone = 0;
								while (!IsValidPhone) {								// nhap phone
									printf(" Enter the Phone Number: ");
									scanf("%s", &newPhone);
									if (IsExistsInFile("StudentManagement.txt", newPhone) == true) {
										printf(" Error: This phone number has already been used.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) > 11) {
										printf(" Error: Phone can not be more than 11 characters.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) <= 0) {
										printf(" Error: Phone can not be empty.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) < 10 && strlen(newPhone) > 0) {
										printf(" Error: This is not a valid phone number.\n");
										IsValidPhone = 0;	
									} else { 
										fprintf(tempFile, "  Phone number: %s\t", newPhone);			// nhap phone vao file
										IsValidPhone = 1;
									}
								}
								
								int IsValidPresentAddress = 0;
								while (!IsValidPresentAddress) {		// nhap dia chi hien tai
									printf(" Enter the present address: ");
									scanf(" %[^\n]s", &newAddress);			// nhap co khoang trang
									if (strlen(newAddress) > 200) {
										printf(" Error: Enter the address which has under 200 characters.\n\n");
										IsValidPresentAddress = 0;
									} else if (strlen(newAddress) <= 0) {
										printf(" Error: Please enter the address.\n\n");
										IsValidPresentAddress = 0;
									} else {
										fprintf(tempFile, "Address: %s\t", newAddress);		// ghi vao file
										IsValidPresentAddress = 1;
									}
								}
								
								int IsValidCountries = 0;
								while (!IsValidCountries) {				// nhap que quan
									printf(" Enter the country: ");
									scanf(" %[^\n]s", &newCountry);		// nhap co khoang trang
									if (strlen(newCountry) > 50) {
										printf(" Error: This is not valid!\n\n");
										IsValidCountries = 0;
									} else if (strlen(newCountry) <= 0) {
										printf(" Error: Please enter the conutry.\n\n");
										IsValidCountries = 0;
									} else {
										fprintf(tempFile, "Country: %s\t\n", newCountry);		// ghi vao file
										IsValidCountries = 1;
									}
								}
								
							} else {
								fputs(line, tempFile);
							}
						}
						//dong file goc va file tam thoi
						fclose(inputFile);
						fclose(tempFile);
						
						if (found) {
							// xoa file goc
							remove(filename);
							
							// doi ten file tam thoi thanh ten file goc
							rename("temp.txt", filename);
							printf(" \n\nUpdate successfully\n\n");
						} else {
							printf(" The '%s' is not found", Name);
							remove("temp.txt");
						}
				}
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;								// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);						
				printf("\n");
				if (Choices == 'Y' || Choices == 'y') {
					IsUpdating = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsUpdating = 1;
				}
			}
		} else if (Option == 'I' || Option == 'i') {
			printf(" Enter the ID: ");
			scanf(" %s", &ID);
			printf("\n\n");
			if (IsExistsInFile("StudentManagement.txt", ID) == false) {
				printf(" The '%s' is not found.\n\n", ID);
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;									// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);
				printf("\n");	
				if (Choices == 'Y' || Choices == 'y') {			
					IsUpdating = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsUpdating = 1;
				}
			} else {
				int found = 0;
				// tim xem ten co trong file hay khong
				inputFile = fopen(filename, "r");
				while (fgets(line, sizeof(line), inputFile) != NULL) {
					if (strstr(line, ID) != NULL) {
						printf("%s", line);	
					}
				}
				printf("\n\n");
				fclose(inputFile);
				// end
				//mo file goc de doc du lieu
					inputFile = fopen(filename, "r");
					if (inputFile == NULL) {
						printf(" Can't access to file!!!");
						return;
					}
						
					// tao file tam thoi de luu du lieu sau khi cap nhat
					tempFile = fopen("temp.txt", "w");
					if (tempFile == NULL) {
						printf(" Can't access to file!!!");
						fclose(inputFile);
						return;
					}
					
				// tim va cap nhat dong chua thong tin nguoi dung muon cap nhat
						while (fgets(line, sizeof(line), inputFile)) {
							if (strstr(line, ID) != NULL) {
								found = 1;
								char newName[40];
								char newID[20];
								char newEmail[100];
								char newPhone[20];
								char newSex[10];
								char newBirthday[50];
								char newAddress[100];
								char newCountry[50];
								
								int IsValidName = 0;
								while (!IsValidName) {				// nhap ten sinh vien
									printf(" Enter the Name: ");
									scanf(" %[^\n]s", &newName);			// co the nhap co khoang trang
									if (strlen(newName) > 30) {
										printf(" Error: Name can not be more than 30 characters.\n\n");
										IsValidName = 0;
									} else if (strlen(newName) <= 0) {
										printf(" Error: Name can not be empty.\n\n");
										IsValidName = 0;
									} else {
										fprintf(tempFile, "Full name: %s\t", newName);				// nhap ten vao file
										IsValidName = 1;
									}
								}
								
								int IsValidID = 0;  
								while (!IsValidID) {				// nhap ma sinh vien
									printf(" Enter the ID: ");
									scanf("%s", &newID);
									if (IsExistsInFile("StudentManagement.txt", newID) == true) {
										printf(" Error: This ID has been used.\n");
										IsValidID = 0;
									} else if (strlen(newID) > 10) {
										printf(" Error: ID can not be more than 10 characters.\n\n");
										IsValidID = 0;
									} else if (strlen(newID) <= 0) {
										printf(" Error: ID can not be empty.\n\n");
										IsValidID = 0;
									} else {
										fprintf(tempFile, "ID: %s\t", newID);			// nhap ma sinh vien vao file
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
								
								sprintf(newBirthday, "%02d-%02d-%04d", day, month, year);      // tao thanh chuoi dd-mm-yy
								fprintf(tempFile,"Birthday: %s\t", newBirthday);		// xuat ngay thang nam sinh vao file
								
								int IsValidSex = 0;
								while (!IsValidSex) {				// nhap gioi tinh
									printf(" Are you [M] Male or [F] Female? ");
									scanf("%s", &newSex);
									if (newSex[0] == 'M' || newSex[0] == 'm') {
										newSex[0] = 'M';
										newSex[1] = 'a';
										newSex[2] = 'l';
										newSex[3] = 'e';
										fprintf(tempFile, "Sex: %s\t", newSex);  				// nhap gioi tinh vao file
										IsValidSex = 1;
									} else if (newSex[0] == 'F' || newSex[0] == 'f') {
										newSex[0] = 'F';
										newSex[1] = 'e';
										newSex[2] = 'm';
										newSex[3] = 'a';
										newSex[4] = 'l';
										newSex[5] = 'e';
										fprintf(tempFile, "Sex: %s\t", newSex);  				// nhap gioi tinh vao file
										IsValidSex = 1;
									} else {
										printf(" Error: Your option is not valid!!!\n");
										IsValidSex = 0;
									}
								}
								
								int IsValidEmail = 0;		
								while (!IsValidEmail) {			// nhap email
									printf(" Enter the email: ");
									scanf("%s", &newEmail);
									if (IsExistsInFile("StudentManagement.txt", newEmail) == true) {
										printf(" Error: This email has already been used.\n\n");
										IsValidEmail = 0;
									} else if (strlen(newEmail) > 30) {
										printf(" Error: Email can not be more than 30 characters.\n\n");
										IsValidEmail = 0;
									} else if (strlen(newEmail) <= 0) {
										printf(" Error: Email can not be empty.\n\n");
										IsValidEmail = 0;
									} else {
										fprintf(tempFile, "Email: %s\t", newEmail);			// nhap email vao file
										IsValidEmail = 1;
									}
								}
								
								int IsValidPhone = 0;
								while (!IsValidPhone) {								// nhap phone
									printf(" Enter the Phone Number: ");
									scanf("%s", &newPhone);
									if (IsExistsInFile("StudentManagement.txt", newPhone) == true) {
										printf(" Error: This phone number has already been used.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) > 11) {
										printf(" Error: Phone can not be more than 11 characters.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) <= 0) {
										printf(" Error: Phone can not be empty.\n\n");
										IsValidPhone = 0;
									} else if (strlen(newPhone) < 10 && strlen(newPhone) > 0) {
										printf(" Error: This is not a valid phone number.\n");
										IsValidPhone = 0;	
									} else { 
										fprintf(tempFile, "  Phone number: %s\t", newPhone);			// nhap phone vao file
										IsValidPhone = 1;
									}
								}
								
								int IsValidPresentAddress = 0;
								while (!IsValidPresentAddress) {		// nhap dia chi hien tai
									printf(" Enter the present address: ");
									scanf(" %[^\n]s", &newAddress);			// nhap co khoang trang
									if (strlen(newAddress) > 200) {
										printf(" Error: Enter the address which has under 200 characters.\n\n");
										IsValidPresentAddress = 0;
									} else if (strlen(newAddress) <= 0) {
										printf(" Error: Please enter the address.\n\n");
										IsValidPresentAddress = 0;
									} else {
										fprintf(tempFile, "Address: %s\t", newAddress);		// ghi vao file
										IsValidPresentAddress = 1;
									}
								}
								
								int IsValidCountries = 0;
								while (!IsValidCountries) {				// nhap que quan
									printf(" Enter the country: ");
									scanf(" %[^\n]s", &newCountry);		// nhap co khoang trang
									if (strlen(newCountry) > 50) {
										printf(" Error: This is not valid!\n\n");
										IsValidCountries = 0;
									} else if (strlen(newCountry) <= 0) {
										printf(" Error: Please enter the conutry.\n\n");
										IsValidCountries = 0;
									} else {
										fprintf(tempFile, "Country: %s\t\n", newCountry);		// ghi vao file
										IsValidCountries = 1;
									}
								}
								
							} else {
								fputs(line, tempFile);
							}
						}
				
				//dong file goc va file tam thoi
						fclose(inputFile);
						fclose(tempFile);
						
						if (found) {
							// xoa file goc
							remove(filename);
							
							// doi ten file tam thoi thanh ten file goc
							rename("temp.txt", filename);
							printf(" \n\nUpdate successfully\n\n");
						} else {
							printf(" The '%s' is not found", Name);
							remove("temp.txt");
						}
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;								// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);						
				printf("\n");
				if (Choices == 'Y' || Choices == 'y') {
					IsUpdating = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsUpdating = 1;
				}	
			}	
		}
	}
}

void DeleteSelectedStudent (const char *filename) {   // xoa hoc sinh duoc chon, xoa bang ten hoac bang ma sinh vien
	FILE *inputFile;
	FILE *tempFile;
	char line[200];
	int found = 0;
	char Name[40];
	char ID[20];
	char studentID[20];
	char Option;
	
	// kiem tra file co rong hay khong
	inputFile = fopen(filename, "r");	
	fseek(inputFile, 0, SEEK_END);	// di chuyen con tro toi cuoi file
	if (ftell(inputFile) == 0) {
		printf(" EMPTY file.\n\n");
		fclose(inputFile);
		return;		// neu file rong thi return 
	}
	fclose(inputFile);
	//kiem tra xong
	
	int IsDeleting = 0;
	while (!IsDeleting) {
		printf(" Delete by Name[N] ? or by ID[I]? ");
		printf(" Your choices: ");
		scanf(" %c", &Option);
		printf("\n");
		if (Option == 'N' || Option == 'n') {
			printf(" Enter the name: ");
			scanf(" %[^\n]s", &Name);
			printf("\n\n");
			if (IsExistsInFile(filename, Name) == false) {
				printf(" The '%s' is not found.\n\n", Name);
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;									// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);
				printf("\n");	
				if (Choices == 'Y' || Choices == 'y') {			
					IsDeleting = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsDeleting = 1;
				}
			} else {
				int numEl = 0;
				// tim xem ten co trong file hay khong
				inputFile = fopen(filename, "r");
				while (fgets(line, sizeof(line), inputFile) != NULL) {
					if (strstr(line, Name) != NULL) {
						numEl++;
						printf("%s", line);	
					}
				}
				printf("\n\n");
				fclose(inputFile);
				// end
				
				if (numEl < 2) {
					char Choice;
					printf(" There is %d student. \n\n", numEl);
					printf(" Do you want to delete the above student? [Y/N]. Your answer: ");
					scanf(" %c", &Choice);
					printf("\n\n");
					if (Choice == 'Y' || Choice == 'y') {
						// mo file goc de doc du lieu
						inputFile = fopen(filename, "r");
						if (inputFile == NULL) {
							printf(" Can't access to file!!");
							return;
						}
						// tao file tam thoi de luu du lieu sau khi xoa
						tempFile = fopen("temp.txt", "w");
						if (tempFile == NULL) {
							printf(" Can't access to file!!\n\n");
							fclose(inputFile);
							return;
						}
						// xoa dong chua ten sinh vien
						while (fgets(line, sizeof(line), inputFile)) {
							if (strstr(line, Name) != NULL) {
								found = 1;
							} else {
								fputs(line, tempFile);
							}
						}
						// dong file goc va file tam thoi
						fclose(inputFile);
						fclose(tempFile);
						if (found) {
							// xoa file goc
							remove(filename);
							
							// doi ten file tam thoi thanh ten file goc
							rename("temp.txt", filename);
							printf(" Delete succesfully.\n\n");
						} else {
							printf(" The '%s' is not found.\n\n", studentID);
							remove("temp.txt");
						}
					} else if (Choice == 'N' || Choice == 'n') {
						IsDeleting = 1;
					}
				} else {
					printf(" There are %d students. \n\n", numEl);
					printf(" Enter the student's ID that you want to delete: ");
					scanf(" %s", &studentID);
					printf("\n\n");
					// mo file goc de doc du lieu
					inputFile = fopen(filename, "r");
					if (inputFile == NULL) {
						printf(" Can't access to file!!");
						return;
					}
					
					// tao file tam thoi de luu du lieu sau khi xoa
					tempFile = fopen("temp.txt", "w");
					if (tempFile == NULL) {
						printf(" Can't access to file!!\n\n");
						fclose(inputFile);
						return;
					}
					
					// xoa dong chua ma sinh vien nguoi dung nhap
					while (fgets(line, sizeof(line), inputFile)) {
						if (strstr(line, studentID) != NULL) {
							found = 1;
						} else {
							fputs(line, tempFile);
						}
					}
					// Dong file goc va file tam thoi
					fclose(inputFile);
					fclose(tempFile);
					
					if (found) {
						// xoa file goc
						remove(filename);
						
						// doi ten file tam thoi thanh ten file goc
						rename("temp.txt", filename);
						printf(" Delete succesfully.\n\n");
					} else {
						printf(" The '%s' is not found.\n\n", studentID);
						remove("temp.txt");
					}
				}
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;								// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);						
				printf("\n");
				if (Choices == 'Y' || Choices == 'y') {
					IsDeleting = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsDeleting = 1;
				}
			}
		} else if (Option == 'I' || Option == 'i') {
			printf(" Enter the ID: ");
			scanf(" %s", &ID);
			printf("\n\n");
			if (IsExistsInFile(filename, ID) == false) {
				printf(" The '%s' is not found.\n\n", ID);
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;									// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);
				printf("\n");	
				if (Choices == 'Y' || Choices == 'y') {			
					IsDeleting = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsDeleting = 1;
				}
			} else {
				int find = 0;
				// xuat hoc sinh co ma sinh vien 
				inputFile = fopen(filename, "r");
				while (fgets(line, sizeof(line), inputFile) != NULL) {
					if (strstr(line, ID) != NULL) {
						printf("%s", line);
					}
				}
				printf("\n\n");
				fclose(inputFile);
				//  end
				
				//xoa hoc sinh co ma sinh vien la ID
				inputFile = fopen(filename, "r");
				if (inputFile == NULL) {
					printf(" Can't access to file!!!");
					return;
				}
				
				   // tao file tam thoi de luu du lieu sau khi xoa
				tempFile = fopen("temp.txt", "w");
				if (tempFile == NULL) {
					printf(" Can't access to file !!!");
					fclose(inputFile);
					return;
				}
				// xoa dong chua ma sinh vien
				while (fgets(line, sizeof(line), inputFile)) { 
					if (strstr(line, ID) != NULL) {
						find = 1;
					} else {
						fputs(line, tempFile);
					}
				}
				// dong file goc va file tam thoi
				fclose(inputFile);
				fclose(tempFile);
				if (find) {
					// xoa file goc
					remove(filename);
					
					// doi ten file tam thoi thanh file goc
					rename("temp.txt", filename);
					printf(" Delete successfully.\n\n");
				} else {
					printf(" The '%s' is not found.\n\n", ID);
					remove("temp.txt");
				}
				// end
				printf(" Do you want to continue ? [Y/N]. Your answer: ");
				char Choices;								// bien de nguoi dung nhap yes/no
				scanf(" %c", &Choices);						
				printf("\n");
				if (Choices == 'Y' || Choices == 'y') {
					IsDeleting = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsDeleting = 1;
				}
			}
		}
	}
	
}

void DeleteAllStudent(const char *filename) {		// xoa tat ca trong file
	
	file = fopen(filename, "r");
	if (file == NULL) {
		printf(" INVALID file.\n\n");
		return;
	}
	// kiem tra xem file co rong hay khong
	fseek(file, 0, SEEK_END);	// di chuyen con tro toi cuoi file
	if (ftell(file) == 0) {
		printf(" EMPTY file.\n\n");
		fclose(file);
		return;		// neu file rong thi return 
	}
	
	fclose(file);	
	// xoa tat ca du lieu
	file = fopen(filename, "w");  // w la ghi de, de xoa du lieu
	if (file == NULL) {
		printf(" INVALID file.\n\n");
		return;
	}
	
	fclose(file);
	printf(" Delete all student succesfully.\n\n");
}

void GoBackOrExit() {		// thoat hoac quay lai menu chinh
    getchar();
    char Option;
    printf(" Go back[b]? or Exit[e]?: ");
    scanf("%c",&Option);
    if(Option == 'e') {
        ExitProject();
    } else {
        system("cls");
    }
}

void ExitProject() {      // thoat chuong trinh
	system("cls");
    char ThankYou[100]     = " ========= Thank You =========\n";
    char SeeYouSoon[100]   = " ========= See You Soon ======\n";
    for (i = 0; i < strlen(ThankYou); i++) {			// chay chu thank you
        printf("%c",ThankYou[i]);
        Sleep(40);
    }
    for (i = 0; i < strlen(SeeYouSoon); i++) {		// chay chu thank you
        printf("%c",SeeYouSoon[i]);
        Sleep(40);
    }
    exit(0);	
}







