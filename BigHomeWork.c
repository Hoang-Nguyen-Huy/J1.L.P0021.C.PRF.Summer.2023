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
#include <conio.h>


struct StudentInfo {
	char LastName[10];
	char MiddleName[10];
	char FirstName[10];
	char Name[30];			// ten
	char ID[10];			// ma sinh vien
	char Email[100];		// email
	char PhoneNumber[15];	// so dien thoai
	char Sex[10];		// gioi tinh
	char DateOfBirth[50];	// ngay sinh
	char PresentAddress[100];	// noi o hien tai
	char Countries[100];		// que quan
};

struct UserInfo {
	char NickName[20];
	char password[20];
};

struct StudentInfo Students[100];
struct UserInfo Users[100];

// bien toan cuc
int i, j, z;
char IsNone[200];
int TotalStudents = 0;
int TotalUsers = 0;
FILE *file;
//

/*
StudentManagement.txt 		file de quan ly hoc sinh
SignUp.txt					file de luu cac thong tin nguoi dung sau khi dang ky
SignIn.txt					file de luu cac thong tin nguoi dung sau khi dang nhap
Admin.txt					file chua tai khoan cua admin
*/

// cac ham de dang nhap, dang ki
void takePassword(char pwd[50]);  // bien mat khau thanh***
void SignIn(const char *filename);
void SignUp(const char *filename);
// end

// cac ham menu
void MenuForLogging();  // menu dung de dang nhap, dang ki
void Menu();		// menu chua cac chuc nang quan ly hoc sinh
void MenuForDeleting();	// menu de xoa hoc sinh
void MenuForSignIn();  // menu de cho nguoi dung chon role
void MenuForAdmin();	// ham menu danh rieng cho admin
void AccountManager(); // ham quan ly tai khoan nguoi dung danh rieng cho admin
//end

// cac ham chuc nang
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
void Create();	//nhap cac thong tin hoc sinh vao file
void ShowAllList(const char *filename);			// xuat tat ca cac ho so cua sinh vien trong file
void SearchStudent(const char *filename);  // tim kiem
int compareNames(const void* a, const void* b);  // dung de sap xep thu tu trong file
void Sort(const char *filename);   // sap xep
void Update(const char *filename);   // cap nhat
void DeleteSelectedStudent(const char *filename);		// xoa 1 hoc sinh duoc chon
void DeleteManyStudents(const char *filename);		// xoa nhieu hoc sinh
void DeleteInOneRange(const char *filename);		// xoa 1 khoang
void DeleteManyRanges(const char *filename);	// xoa nhieu khoang
void DeleteAllStudent(const char *filename);		// xoa tat ca trong  file
bool IsExistsInFile(const char *filename, const char *code); // kiem tra xem da xuat hien trong file hay chua
void GoBackOrExit();			// thoat case de quay lai menu chinh hoac exit chuong trinh
void ExitProject();     // thoat chuong trinh
//end

// cac ham dung de quan ly tai khoan
void ShowAllAcc(const char *filename);
void GrantPermission(const char *filename);
//

int main () {
	MenuForLogging();
	return 0;
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

void MenuForSignIn() {   //menu de chon role
	int Role = 0;
	while (!Role) {
		int choose;
		char checkChoose[50];
		printf("===================================SIGN IN=====================================\n\n");
		printf(" [1].Admin            [2].Employee            [0].Go back\n\n");
		printf(" Enter your role: ");
		scanf(" %s", checkChoose);
		while (checkInt(checkChoose) == false) {
			printf(" Your ans is not valid!!!\n\n");
			printf(" Enter your role: ");
			scanf("%s", checkChoose);
		}
		if (checkInt(checkChoose) == true) {
			choose = atoi(checkChoose);
		}
		switch(choose) {
			case 1: 
				system("cls");
				SignIn("Admin.txt");
				break;
			case 2: 
				system("cls");
				SignIn("SignIn.txt");
				break;
			case 0:
				system("cls");
				Role = 1;
				break;
			default: 
				system("cls");
				printf(" Error: Please enter a valid option\n\n");
				break;
		}
	}
}

void SignIn(const char *filename) {   //dang nhap cho nguoi dung
	char nickName[20];
	char password[20];
	int Success = 0;
	int helloAdmin = 0;
	char yesNo;
	char line[200];
	char checkNick[20];
	char checkPass[20];
	int IsSignIn = 1;
	int Admin = 1;
	printf("===================================SIGN IN=====================================\n\n");
	
	if (filename == "SignIn.txt") {
		IsSignIn = 0;
	} else if (filename == "Admin.txt") {
		Admin = 0;
	}
	
	while (!IsSignIn) {
		
		printf("Enter your nick name: ");
		scanf(" %[^\n]s", &nickName);
		
		// kiem tra xem nickName co khoang trang hay khong
		int hasWhitespace = 0;
		for (i = 0; i < strlen(nickName); i++) {
			if (nickName[i] == ' ') {
				hasWhitespace = 1;
				break;
			}
		}
		if (hasWhitespace == 1) {
			printf("Nickname cannot contain whitespace!!! Please try again.\n");
			IsSignIn = 0;
		}
		
		printf("Enter your password: ");
		scanf(" %s", &password);
		
		file = fopen(filename, "r");
		while (fgets(line, sizeof(line), file)) {
			if (strstr(line, nickName) != NULL) {
				fseek(file, -40, SEEK_CUR);
				fscanf(file, "%s", checkNick);
				fscanf(file, "%s", checkPass);
			}
		}
		fclose(file);
		
		if (strcmp(nickName, checkNick) == 0 && strcmp(password, checkPass) == 0) {
				Success = 1;
				IsSignIn = 1;
		}
		
		if (Success == 0) {
			printf(" Your nick name or password is incorrect\n\n");
			printf(" You want to sign in again ? [Y/N]: ");
			scanf(" %c", &yesNo);
			if (yesNo == 'Y' || yesNo == 'y') {
				IsSignIn = 0;
			} else {
				IsSignIn = 1;
			}
		}
		
	} // end IsSignIn
	
	while (!Admin) {
		printf("Enter your nick name: ");
		scanf(" %[^\n]s", &nickName);
		
		// kiem tra xem nickName co khoang trang hay khong
		int hasWhitespace = 0;
		for (i = 0; i < strlen(nickName); i++) {
			if (nickName[i] == ' ') {
				hasWhitespace = 1;
				break;
			}
		}
		if (hasWhitespace == 1) {
			printf("Nickname cannot contain whitespace!!! Please try again.\n");
			Admin = 0;
		}
		
		printf("Enter your password: ");
		scanf(" %s", &password);
		
		file = fopen(filename, "r");
		while (fgets(line, sizeof(line), file)) {
			if (strstr(line, nickName) != NULL) {
				fseek(file, -40, SEEK_CUR);
				fscanf(file, "%s", checkNick);
				fscanf(file, "%s", checkPass);
			}
		}
		fclose(file);
		
		if (strcmp(nickName, checkNick) == 0 && strcmp(password, checkPass) == 0) {
				helloAdmin = 1;
				Admin = 1;
		}
		
		if (helloAdmin == 0) {
			printf(" Your nick name or password is incorrect\n\n");
			printf(" You want to sign in again ? [Y/N]: ");
			scanf(" %c", &yesNo);
			if (yesNo == 'Y' || yesNo == 'y') {
				Admin = 0;
			} else {
				Admin = 1;
			}
		}
	} // end Admin
	
	if (Success == 1) {
		system("cls");
	    char SignInSuccess[100]     = " ========= Sign In successfully =========\n";
	    char Welcome[100]   = " ========= Welcome to my project ======\n";
	    for (i = 0; i < strlen(SignInSuccess); i++) {			// chay chu thank you
	        printf("%c", SignInSuccess[i]);
	        Sleep(40);
	    }
	    for (i = 0; i < strlen(Welcome); i++) {		// chay chu thank you
	        printf("%c", Welcome[i]);
	        Sleep(40);
	    }
	    system("cls");
	    Menu();    // chuong trinh chay
	} else if (helloAdmin == 1) {
		system("cls");
		char SignInSuccess[100]     = " ========= Sign In successfully =========\n";
		char Welcome[100]   = " ========= Hello Admin ======\n";
		for (i = 0; i < strlen(SignInSuccess); i++) {			// chay chu thank you
	        printf("%c", SignInSuccess[i]);
	        Sleep(40);
	    }
	    for (i = 0; i < strlen(Welcome); i++) {		// chay chu thank you
	        printf("%c", Welcome[i]);
	        Sleep(40);
	    }
	    system("cls");
	    MenuForAdmin();  // menu danh cho admin
	} else {
		system("cls");
		return;
	}
	
}

void SignUp(const char *filename) {		// dang ki
	char nickName[50];
	char password[20];
	
	int IsValidNickName = 0;
	while (!IsValidNickName) {
		printf("Enter your nick name: ");
		scanf(" %[^\n]s", &nickName);
	
		// kiem tra xem nickName co khoang trang hay khong
		int hasWhitespace = 0;
		for (i = 0; i < strlen(nickName); i++) {
			if (nickName[i] == ' ') {
				hasWhitespace = 1;
				break;
			}
		}
		if (hasWhitespace == 1) {
			printf("Nickname cannot contain whitespace!!! Please try again.\n");
			IsValidNickName = 0;
		} else if (IsExistsInFile("SignUp.txt", nickName) == true) {
			printf(" Your nick name is duplicated!!!\n\n");
			IsValidNickName = 0;
		} else if (strlen(nickName) > 18) {
			printf("Your nick name is too long!!!\n\n");
			IsValidNickName = 0;
		} else if (strlen(nickName) <= 0) {
			printf("Please enter your nick name!!!\n\n");
			IsValidNickName = 0;
		} else {
			IsValidNickName = 1;
		}
	}
	
	int IsValidPassword = 0;
	while (!IsValidPassword) {
		printf("Enter your password: ");
		scanf(" %s", &password);
		
		if (strlen(password) > 18) {
			printf(" Your password is too long.\n");
			IsValidPassword = 0;
		} else if (strlen(password) < 8) {
			printf(" Your password is too short.\n");
			IsValidPassword = 0;
		} else {
			IsValidPassword = 1;
		}
	}
	
		
	file = fopen(filename, "a");
	fprintf(file, "%s", nickName);
	for (i = 1; i <= 19 - strlen(nickName); i++) {
		fprintf(file, " ");
	}
	fprintf(file, "%s", password);
	for (i = 1; i <= 19 - strlen(password); i++) {
		fprintf(file, " ");
	}
	fprintf(file, "\n");
	fclose(file);
	
	FILE *waitFile = fopen("Waiting.txt", "a");
	fprintf(file, "%s", nickName);
	for (i = 1; i <= 19 - strlen(nickName); i++) {
		fprintf(file, " ");
	}
	fprintf(file, "%s", password);
	for (i = 1; i <= 19 - strlen(password); i++) {
		fprintf(file, " ");
	}
	fprintf(file, "\n");
	fclose(waitFile);
	
	system("cls");
	    char SignUpSuccess[100]     = "\nSign up successful! Waiting for admin approval.\n\n";
	    for (i = 0; i < strlen(SignUpSuccess); i++) {			// chay chu thank you
	        printf("%c", SignUpSuccess[i]);
	        Sleep(40);
	    }
	system("cls");
	
}

void MenuForLogging() {  // menu de logging
	int IsLogging = 0;
	while (!IsLogging) {
		int option;
		char checkOption[50];
		printf("===============Welcome to my project===============\n\n");
		printf("               [1]. Sign in.\n");
		printf("               [2]. Sign up.\n");
		printf("               [0]. Exit app.\n");
		printf(" Enter your option: ");
		scanf("%s", checkOption);
		while (checkInt(checkOption) == false) {
			printf(" Your option is not valid!!!. Enter again: ");
			scanf("%s", checkOption);
		}
		if (checkInt(checkOption) == true) {
			option = atoi(checkOption);
		}
		switch(option) {
			case 1: 
				system("cls");
				MenuForSignIn();
				break;
			case 2: 
				system("cls");
				printf("===============SIGN UP===============\n\n");
				SignUp("SignUp.txt");
				break;
			case 0: 
				system("cls");
				IsLogging = 1;
				ExitProject();
				break;
			default: 
				system("cls");
				printf(" Error: Please enter a valid option\n\n");
				break;
		}
	}
	
}

void MenuForDeleting() {  // menu de xoa
	int IsRunning = 0;
	while (!IsRunning) {
		int choice;
		char checkChoice[50];
		printf("\n\n\t********Deleting Profile********\n\n");
		printf("\t\t=========================\n");
		printf("\t\t[1] Delete any 1 student.\n");  // done
		printf("\t\t[2] Delete many students.\n"); 	// done
		printf("\t\t[3] Delete students in 1 RANGE.\n");	// done			
		printf("\t\t[4] Delete students in multi RANGES.\n"); //???          
		printf("\t\t[5] Delete all student.\n");  // done
		printf("\t\t[0] Stop deleting.\n");		 
		printf("\t\t=========================\n");
		printf("\t\tEnter your Choice: ");
		scanf("%s", checkChoice);
		
		while (checkInt(checkChoice) == false) {
			printf(" Your choice is not valid!!!. Enter again: ");
			scanf("%s", checkChoice);
		}
		if (checkInt(checkChoice) == true) {
			choice = atoi(checkChoice);
		}
		switch(choice) {
			case 1: 
				system("cls");
				printf("\n\n\t********Deleting any one student********\n\n");
				DeleteSelectedStudent("StudentManagement.txt");
				break;
			case 2: 
				system("cls");
				printf("\n\n\t********Deleting many students********\n\n");
				DeleteManyStudents("StudentManagement.txt");
				break;
			case 3: 
				system("cls");
				printf("\n\n\t********Deleting in 1 range********\n\n");
				ShowAllList("StudentManagement.txt");
				DeleteInOneRange("StudentManagement.txt");
				break;
			case 4: 
				system("cls");
				printf("\n\n\t********Deleting in many ranges********\n\n");
				ShowAllList("StudentManagement.txt");
				DeleteManyRanges("StudentManagement.txt");
				break;
			case 5: 
				system("cls");
				printf("\n\n\t********Deleting all students********\n\n");
				DeleteAllStudent("StudentManagement.txt");
				break;
			case 0: 
				IsRunning = 1;
				break;
			default: 
				system("cls");
				printf(" Error: Please enter a valid option\n\n");
				break;
		}
	}
	
}

void Menu () {   // menu cac chuc nang quan ly sinh vien
		bool IsRunning = true;
		while (IsRunning) {
			printf("\n\n\t********Student Management System********\n\n");
			printf("\t\t\tMAIN MENU\n");
			printf("\t\t=========================\n");
			printf("\t\t[1] Add a new student to the list.\n");
			printf("\t\t[2] Show all list of profile.\n");
			printf("\t\t[3] Update student.\n");			
			printf("\t\t[4] Delete students.\n");          
			printf("\t\t[5] Find a student.\n");
			printf("\t\t[6] Sort all list.\n");				
			printf("\t\t[0] Log out.\n");
			printf("\t\t=========================\n");
			printf("\t\tEnter your Choice: ");
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
				    MenuForDeleting();
				    printf("\n\n");
				    GoBackOrExit();
				    break;
				case 5: 
					system("cls");
					SearchStudent("StudentManagement.txt");
					GoBackOrExit();
					break;
				case 6: 
					system("cls");
					Sort("StudentManagement.txt");
					GoBackOrExit();
					break;
				case 0: 
					system("cls");
					IsRunning = false;
					break;
				default: 
					system("cls");
					printf(" Error: Please enter a valid option\n\n");
					break;
			}
	}
}

void MenuForAdmin () {	// menu danh rieng cho admin
	int IsAdmin = 0;
	while (!IsAdmin) {
		int choice;
		char checkChoice[20];
		printf("                    Admin                 \n\n");
		printf("	[1]. Student Management System\n");
		printf("	[2]. Account Management System\n");
		printf("	[0]. Log out\n");
		printf(" Enter your choice: ");
		scanf(" %s", &checkChoice);
		while (checkInt(checkChoice) == false) {
			printf(" Your choice is not valid!!!. Please enter again: ");
			scanf(" %s", &checkChoice);
		}
		if (checkInt(checkChoice) == true) {
			choice = atoi(checkChoice);
		}
		switch(choice) {
			case 1: 
				system("cls");
				Menu();
				break;
			case 2:
				system("cls");
				AccountManager();
				break;
			case 0: 
				system("cls");
				IsAdmin = 1;
				break;
			default:
				system("cls");
				printf("Your choice is not valid!!\n");
				break;
		}
	} // end IsAdmin
}

void AccountManager () {  // menu quan ly tai khoan danh rieng cho admin
	int IsManaging = 0;
	while (!IsManaging) {
		int choice;
		char checkChoice[20];
		printf("\n\n\t********Account Management System********\n\n");
		printf("\t\t\tMAIN MENU\n");
		printf("\t\t=========================\n");
		printf("\t\t[1] List of those who SIGNED UP.\n");
		printf("\t\t[2] List of those who have right to SIGN IN.\n");
		printf("\t\t[3] Grant permission for SIGN IN.\n");							
		printf("\t\t[0] Log out.\n");
		printf("\t\t=========================\n");
		printf("\t\tEnter your Choice: ");
		scanf(" %s", &checkChoice);
		while (checkInt(checkChoice) == false) {
			printf("\tPlease enter a valid option: ");
			scanf(" %s", &checkChoice);
		}
		if (checkInt(checkChoice) == true) {
			choice = atoi(checkChoice);
		}
		switch(choice) {
			case 1: 
				system("cls");
				printf("		Signed Up		\n\n");
				ShowAllAcc("SignUp.txt");
				GoBackOrExit();
				break;
			case 2: 
				system("cls");
				printf("		Right to sign in\n\n");
				ShowAllAcc("SignIn.txt");
				GoBackOrExit();
				break;
			case 3: 
				system("cls");
				printf("		Waiting for your permission\n\n");
				GrantPermission("Waiting.txt");
				GoBackOrExit();
				break;
			case 0: 
				system("cls");
				IsManaging = 1;
				break;
			default:
				system("cls");
				printf(" Your choice is not valid!!!\n\n");
				break;
		}
	}
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
		printf(" Enter the Full Name(enter 'exit' if you want to go back to menu): ");
		scanf(" %[^\n]s", &Name);			// co the nhap co khoang trang
		if (strcmp(Name, "exit") == 0) {
			printf("\n\n");
			return;
		}
		if (strlen(Name) >= 22) {
			printf(" Error: Name can not be more than 22 characters.\n\n");
			IsValidName = 0;
		} else if (strlen(Name) <= 0) {
			printf(" Error: Name can not be empty.\n\n");
			IsValidName = 0;
		} else {
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, " %s", Name);
			for (i = 1; i <= 25 - strlen(Name); i++) {
				fprintf(file, " ");
			}
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
		} else if (strlen(StudentID) > 8) {
			printf(" Error: ID can not be more than 8 characters.\n\n");
			IsValidID = 0;
		} else if (strlen(StudentID) <= 0) {
			printf(" Error: ID can not be empty.\n\n");
			IsValidID = 0;
		} else {
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "%s", StudentID);			// nhap ma sinh vien vao file
			for (i = 1; i <= 11 - strlen(StudentID); i++) {
				fprintf(file, " ");
			}
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
	fprintf(file,"%s", DateOfBirth);		// xuat ngay thang nam sinh vao file
	for (i = 1; i <= 16 - strlen(DateOfBirth); i++) {
		fprintf(file, " ");
	}
	fclose(file);		
	
	int IsValidSex = 0;
	while (!IsValidSex) {				// nhap gioi tinh
		printf(" Are you [M] Male or [F] Female? ");
		scanf("%s", &Sex);
		if (Sex[0] == 'M' || Sex[0] == 'm') {
			strcpy(Sex, "Male");
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "%s", Sex);  				// nhap gioi tinh vao file
			for (i = 1; i <= 10 - strlen(Sex); i++) {
				fprintf(file, " ");
			}
			fclose(file);
			IsValidSex = 1;
		} else if (Sex[0] == 'F' || Sex[0] == 'f') {
			strcpy(Sex, "Female");
			file = fopen("StudentManagement.txt", "a");
			fprintf(file, "%s", Sex);  				// nhap gioi tinh vao file
			for (i = 1; i <= 10 - strlen(Sex); i++) {
				fprintf(file, " ");
			}
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
			fprintf(file, "%s", Email);			// nhap email vao file
			for (i = 1; i <= 25 - strlen(Email); i++) {
				fprintf(file, " ");
			}
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
			fprintf(file, "%s", Phone);			// nhap phone vao file
			for (i = 1; i <= 15 - strlen(Phone); i++) {
				fprintf(file, " ");
			}
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
			fprintf(file, "%s", PresentAddress);		// ghi vao file
			for (i = 1; i <= 20 - strlen(PresentAddress); i++) {
				fprintf(file, " ");
			}
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
			fprintf(file, "%s", Countries);		// ghi vao file
			for (i = 1; i <= 15 - strlen(Countries); i++) {
				fprintf(file, " ");
			}
			fprintf(file, "\n");
			fclose(file);
			IsValidCountries = 1;
		}
	}
	printf("\n Student Added Succesfully.\n\n");

}

void ShowAllList (const char *filename) {			// xuat tat ca cac ho so cua sinh vien trong file
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
	
	printf("        Full name       |    ID    |    Birthday   |   Sex   |          Email         | Phone number |       Address     |    Country   |\n\n");
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
	printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
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
		printf(" Search by name[N]? or by ID[I]? or [E] to exit: ");
		scanf(" %c", &Option);
		printf("\n");
		
		if (Option == 'E' || Option == 'e') {
			printf("\n\n");
			return;
		}
		
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

int compareNames(const void* a, const void* b) {		// dung cho ham Sort
    const struct StudentInfo* studentA = (const struct StudentInfo*)a;
    const struct StudentInfo* studentB = (const struct StudentInfo*)b;

    int result = strcmp(studentA->FirstName, studentB->FirstName);
    if (result == 0) {  // FirstName is equal, compare MiddleName
        result = strcmp(studentA->MiddleName, studentB->MiddleName);
        if (result == 0) {  // MiddleName is equal, compare LastName
            result = strcmp(studentA->LastName, studentB->LastName);
        }
    }

    return result;
}

void Sort(const char* filename) {		// sap xep
	char Country1[10];
	char Country2[10];
	char Country[20];
	char line[200][200];
	
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
	
	
    file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }
    TotalStudents = 0;
    while (fgets(line, sizeof(line), file) != NULL) {
        char* p = strtok(line, " ");
        strcpy(Students[TotalStudents].LastName, p);

        p = strtok(NULL, " ");
        strcpy(Students[TotalStudents].MiddleName, p);

        p = strtok(NULL, " ");
        strcpy(Students[TotalStudents].FirstName, p);

        sprintf(Students[TotalStudents].Name, "%s %s %s", Students[TotalStudents].LastName, Students[TotalStudents].MiddleName, Students[TotalStudents].FirstName);

        p = strtok(NULL, " ");
        strcpy(Students[TotalStudents].ID, p);

        p = strtok(NULL, " ");
        strcpy(Students[TotalStudents].DateOfBirth, p);

        p = strtok(NULL, " ");
        strcpy(Students[TotalStudents].Sex, p);

        p = strtok(NULL, " ");
        strcpy(Students[TotalStudents].Email, p);

        p = strtok(NULL, " ");
        strcpy(Students[TotalStudents].PhoneNumber, p);

        p = strtok(NULL, " ");
        strcpy(Students[TotalStudents].PresentAddress, p);

        p = strtok(NULL, " ");
        strcpy(Country1, p);

        p = strtok(NULL, " ");
        strcpy(Country2, p);

        sprintf(Students[TotalStudents].Countries, "%s %s", Country1, Country2);

        TotalStudents++;
    }
    fclose(file);

    qsort(Students, TotalStudents, sizeof(struct StudentInfo), compareNames);

    file = fopen(filename, "w");
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }
   for (j = 0; j <= TotalStudents; j++) {
		fprintf(file, " %s", Students[j].Name);  // nhap ten
		for (i = 1; i <= 25 - strlen(Students[j].Name); i++) {
			fprintf(file, " ");
		}
					
		fprintf(file, "%s", Students[j].ID);			// nhap ma sinh vien vao file
		for (i = 1; i <= 11 - strlen(Students[j].ID); i++) {
			fprintf(file, " ");
		}
					
		fprintf(file, "%s", Students[j].DateOfBirth);		// xuat ngay thang nam sinh vao file
		for (i = 1; i <= 16 - strlen(Students[j].DateOfBirth); i++) {
			fprintf(file, " ");
		}
					
		fprintf(file, "%s", Students[j].Sex);  				// nhap gioi tinh vao file
		for (i = 1; i <= 10 - strlen(Students[j].Sex); i++) {
			fprintf(file, " ");
		}
					
		fprintf(file, "%s", Students[j].Email);			// nhap email vao file
		for (i = 1; i <= 25 - strlen(Students[j].Email); i++) {
			fprintf(file, " ");
		}
					
		fprintf(file, "%s", Students[j].PhoneNumber);			// nhap phone vao file
		for (i = 1; i <= 15 - strlen(Students[j].PhoneNumber); i++) {
			fprintf(file, " ");
		}
					
		fprintf(file, "%s", Students[j].PresentAddress);		// ghi vao file
		for (i = 1; i <= 20 - strlen(Students[j].PresentAddress); i++) {
			fprintf(file, " ");
		}
					
		fprintf(file, "%s", Students[j].Countries);		// ghi vao file
		for (i = 1; i <= 15 - strlen(Students[j].Countries); i++) {
			fprintf(file, " ");
		}
		fprintf(file, "\n");
	}
	
    fclose(file);

    printf("\n\nSort successfully.\n\n");
}

void Update(const char *filename) {    //cap nhat thong tin hoc sinh
	int countLine = 0; // dung de dem so dong trong file
	char lineToCount[200][200];	// bien nay dung de duyet file de DEM SO Dong trong file
	char Option;			// lua chon de nhap ten hoac id
	char Name[40];			// ten
	char ID[20];			// ma sinh vien	
	char line[200];   // bien nay dung de duyet file va tim kiem
	int indexUpdating = 0; // dia chi cua dong can cap nhat
	char LastName[10];
	char MiddleName[10];
	char FirstName[10];
	char FullName[40];
	char IDfromFile[10];
	char DateOfBirth[30];
	char Sex[10];
	char Email[40];
	char PhoneNumber[20];
	char Address[30];
	char Country1[30];
	char Country2[30];
	char Country[30];
	char checkDay[5];					// nhap ngay sinh
	int day; 
	char checkMonth[5];			// nhap thang sinh
	int month;
	char checkYear[5];			// nhap nam sinh
	int year;
	
	
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
	
	// dem so dong trong file
	file = fopen(filename, "r");
	while (fgets(lineToCount[countLine], sizeof(lineToCount[countLine]), file) != NULL) {
		countLine++;
	}
	fclose(file);
	// dem xong
	
	int IsUpdating = 0;
	while (!IsUpdating) {
		printf(" Search by name[N]? or by ID[I]?  or [E] to exit: ");
		scanf(" %c", &Option);
		printf("\n");
		if (Option == 'e' || Option == 'E') {
			printf("\n\n");
			return;
		}
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
					IsUpdating = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsUpdating = 1;
				}
			} else {
				int numEL = 0;
				printf("        Full name       |    ID    |    Birthday   |   Sex   |          Email         | Phone number |       Address     |    Country   |\n\n");
				// dem so hoc sinh co ten "Name" va in ra dong muon cap nhat
				file = fopen(filename, "r");
				while (fgets(line, sizeof(line), file) != NULL) {
					if (strstr(line, Name) != NULL) {
						numEL++;
						printf("%s", line);
					}
				}	
				fclose(file);
				//end
				printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
				if (numEL < 2) {
					printf(" \n\nThere is %d student.\n\n", numEL);
					
					file = fopen(filename, "r");
					countLine = 1;
					while (fgets(lineToCount[countLine], sizeof(lineToCount[countLine]), file) != NULL) {
						if (strstr(lineToCount[countLine], Name) != NULL) {
							indexUpdating = countLine;
							fseek(file, -139, SEEK_CUR);
							fscanf(file, "%s", LastName);
							fscanf(file, "%s", MiddleName);
							fscanf(file, "%s", FirstName);
							fscanf(file, "%s", IDfromFile);
							fscanf(file, "%s", DateOfBirth);
							fscanf(file, "%s", Sex);
							fscanf(file, "%s", Email);
							fscanf(file, "%s", PhoneNumber);
							fscanf(file, "%s", Address);
							fscanf(file, "%s", Country1);
							fscanf(file, "%s", Country2);
						}
						countLine++;
					}
					sprintf(FullName, "%s %s %s", LastName, MiddleName, FirstName);  // tao thanh full name
					sprintf(Country, "%s %s", Country1, Country2);
					fclose(file);
					
					char CheckchooseUpdating[10];
					int chooseUpdating;
					int IschoosingUpdating = 0;
					int countUp = 0;
					
					int IsValidName = 0;
					int IsValidID = 0;
					int IsValidSex = 0;
					int IsValidEmail = 0;
					int IsValidPhone = 0;
					int IsValidPresentAddress = 0;
					int IsValidCountries = 0;
					while (IschoosingUpdating == 0) {	
						printf("[1]. Name\n");
						printf("[2]. ID\n");
						printf("[3]. Birthday\n");
						printf("[4]. Sex\n");
						printf("[5]. Email\n");
						printf("[6]. Phone\n");
						printf("[7]. Address\n");
						printf("[8]. Country\n");
						printf("[0]. Exit\n");
						printf("Enter your choices: ");
						scanf(" %s", &CheckchooseUpdating);
						printf("\n\n");
						while (checkInt(CheckchooseUpdating) == false) {
							printf(" Error: Your answer is not valid!!!\n");
							printf(" Enter your choices: ");
							scanf(" %c", &CheckchooseUpdating);
						}
						if (checkInt(CheckchooseUpdating) == true) {
							chooseUpdating = atoi(CheckchooseUpdating);
						}
						if (chooseUpdating == 1) {
							countUp = 1;
							while (!IsValidName) {				// nhap ten sinh vien
								printf(" Enter the new Full Name: ");
								scanf(" %[^\n]s", &FullName);			// co the nhap co khoang trang
								if (strlen(FullName) >= 22) {
									printf(" Error: Name can not be more than 22 characters.\n\n");
									IsValidName = 0;
								} else if (strlen(FullName) <= 0) {
									printf(" Error: Name can not be empty.\n\n");
									IsValidName = 0;
								} else {
									IsValidName = 1;
								}
							}
						}
						if (chooseUpdating == 2) {
							countUp = 1;
							while (!IsValidID) {				// nhap ma sinh vien
								printf(" Enter the new ID: ");
								scanf("%s", &IDfromFile);
								if (IsExistsInFile("StudentManagement.txt", IDfromFile) == true) {
									printf(" Error: This ID is already exists.\n\n");
									IsValidID = 0;
								} else if (strlen(IDfromFile) > 8) {
									printf(" Error: ID can not be more than 8 characters.\n\n");
									IsValidID = 0;
								} else if (strlen(IDfromFile) <= 0) {
									printf(" Error: ID can not be empty.\n\n");
									IsValidID = 0;
								} else {
									IsValidID = 1;
								}
							}
						} 
						if (chooseUpdating == 3) {
							countUp = 1;
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
						}
						if (chooseUpdating == 4) {
							countUp = 1;
							while (!IsValidSex) {				// nhap gioi tinh
								printf(" [M] Male or [F] Female? ");
								scanf("%s", &Sex);
								if (Sex[0] == 'M' || Sex[0] == 'm') {
									strcpy(Sex, "Male");
									IsValidSex = 1;
								} else if (Sex[0] == 'F' || Sex[0] == 'f') {
									strcpy(Sex, "Female");
									IsValidSex = 1;
								} else {
									printf(" Error: Your option is not valid!!!\n");
									IsValidSex = 0;
								}
							}		
						}
						if (chooseUpdating == 5) {
							countUp = 1;
							while (!IsValidEmail) {			// nhap email
								printf(" Enter the new email: ");
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
									IsValidEmail = 1;
								}
							}
						}
						if (chooseUpdating == 6) {
							countUp = 1;
							while (!IsValidPhone) {								// nhap phone
								printf(" Enter the new Phone Number: ");
								scanf("%s", &PhoneNumber);
								if (IsExistsInFile("StudentManagement.txt", PhoneNumber) == true) {
									printf(" Error: This Phone Number is ALREADY EXISTS.\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) > 11) {
									printf(" Error: Phone can not be more than 11 characters.\n\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) <= 0) {
									printf(" Error: Phone can not be empty.\n\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) < 10 && strlen(PhoneNumber) > 0) {
									printf(" Error: This is not a valid phone number.\n");
									IsValidPhone = 0;	
								} else { 
									IsValidPhone = 1;
								}
							}
						}
						if (chooseUpdating == 7) {
							countUp = 1;
							while (!IsValidPresentAddress) {		// nhap dia chi hien tai
								printf(" Enter the present address: ");
								scanf(" %[^\n]s", &Address);			// nhap co khoang trang
								if (strlen(Address) > 200) {
									printf(" Error: Enter the address which has under 200 characters.\n\n");
									IsValidPresentAddress = 0;
								} else if (strlen(Address) <= 0) {
									printf(" Error: Please enter the address.\n\n");
									IsValidPresentAddress = 0;
								} else {
									IsValidPresentAddress = 1;
								}
							}
						}
						if (chooseUpdating == 8) {
							countUp = 1;
							while (!IsValidCountries) {				// nhap que quan
								printf(" Enter the country: ");
								scanf(" %[^\n]s", &Country);		// nhap co khoang trang
								if (strlen(Country) > 50) {
									printf(" Error: This is not valid!\n\n");
									IsValidCountries = 0;
								} else if (strlen(Country) <= 0) {
									printf(" Error: Please enter the conutry.\n\n");
									IsValidCountries = 0;
								} else {
									IsValidCountries = 1;
								}
							}
						}
						if (chooseUpdating == 0) {
							break;
						}
								
					}	// end chooseUpdating				
					// nhap vao file
					file = fopen(filename, "a");
					
					fprintf(file, " %s", FullName);  // nhap ten
					for (i = 1; i <= 25 - strlen(FullName); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", IDfromFile);			// nhap ma sinh vien vao file
					for (i = 1; i <= 11 - strlen(IDfromFile); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file,"%s", DateOfBirth);		// xuat ngay thang nam sinh vao file
					for (i = 1; i <= 16 - strlen(DateOfBirth); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Sex);  				// nhap gioi tinh vao file
					for (i = 1; i <= 10 - strlen(Sex); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Email);			// nhap email vao file
					for (i = 1; i <= 25 - strlen(Email); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", PhoneNumber);			// nhap phone vao file
					for (i = 1; i <= 15 - strlen(PhoneNumber); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Address);		// ghi vao file
					for (i = 1; i <= 20 - strlen(Address); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Country);		// ghi vao file
					for (i = 1; i <= 15 - strlen(Country); i++) {
						fprintf(file, " ");
					}
					fprintf(file, "\n");
					
					fclose(file);
					// end
					
					file = fopen(filename, "r");
					countLine = 1;
					while (fgets(lineToCount[countLine], sizeof(lineToCount[countLine]), file) != NULL) {
						countLine++;
					}
					
					countLine--;
					strcpy(lineToCount[indexUpdating], lineToCount[countLine]);
					strcpy(lineToCount[countLine], IsNone);
					countLine--;
					
					fclose(file);
				
					
					file = fopen(filename, "w");
					for (i = 1; i <= countLine; i++) {
						fprintf(file, "%s", lineToCount[i]);
					}
					fclose(file);
					
					if (countUp == 0) {
						printf("\n        The profile has not been updated.    \n\n");
					} else {
						printf("\n        Update successfully.                 \n\n");
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
				} else if (numEL >= 2) {
					printf("\n\n There are %d students.\n\n", numEL);
					
					char studentIDtoUpdate[10];
					printf(" Enter the student's ID that you want to update: ");
					scanf("%s", &studentIDtoUpdate);
					printf("\n\n");
					
					file = fopen(filename, "r");
					countLine = 1;
					while (fgets(lineToCount[countLine], sizeof(lineToCount[countLine]), file) != NULL) {
						if (strstr(lineToCount[countLine], studentIDtoUpdate) != NULL) {
							indexUpdating = countLine;
							fseek(file, -139, SEEK_CUR);
							fscanf(file, "%s", LastName);
							fscanf(file, "%s", MiddleName);
							fscanf(file, "%s", FirstName);
							fscanf(file, "%s", IDfromFile);
							fscanf(file, "%s", DateOfBirth);
							fscanf(file, "%s", Sex);
							fscanf(file, "%s", Email);
							fscanf(file, "%s", PhoneNumber);
							fscanf(file, "%s", Address);
							fscanf(file, "%s", Country1);
							fscanf(file, "%s", Country2);
						}
						countLine++;
					}
					sprintf(FullName, "%s %s %s", LastName, MiddleName, FirstName);  // tao thanh full name
					sprintf(Country, "%s %s", Country1, Country2);
					fclose(file);
					
					char CheckchooseUpdating[10];
					int chooseUpdating;
					int IschoosingUpdating = 0;
					int countUp = 0;
					
					int IsValidName = 0;
					int IsValidID = 0;
					int IsValidSex = 0;
					int IsValidEmail = 0;
					int IsValidPhone = 0;
					int IsValidPresentAddress = 0;
					int IsValidCountries = 0;
					while (IschoosingUpdating == 0) {	
						printf("[1]. Name\n");
						printf("[2]. ID\n");
						printf("[3]. Birthday\n");
						printf("[4]. Sex\n");
						printf("[5]. Email\n");
						printf("[6]. Phone\n");
						printf("[7]. Address\n");
						printf("[8]. Country\n");
						printf("[0]. Exit\n");
						printf("Enter your choices: ");
						scanf(" %s", &CheckchooseUpdating);
						printf("\n\n");
						while (checkInt(CheckchooseUpdating) == false) {
							printf(" Error: Your answer is not valid!!!\n");
							printf(" Enter your choices: ");
							scanf(" %c", &CheckchooseUpdating);
						}
						if (checkInt(CheckchooseUpdating) == true) {
							chooseUpdating = atoi(CheckchooseUpdating);
						}
						if (chooseUpdating == 1) {
							countUp = 1;
							while (!IsValidName) {				// nhap ten sinh vien
								printf(" Enter the new Full Name: ");
								scanf(" %[^\n]s", &FullName);			// co the nhap co khoang trang
								if (strlen(FullName) >= 22) {
									printf(" Error: Name can not be more than 22 characters.\n\n");
									IsValidName = 0;
								} else if (strlen(FullName) <= 0) {
									printf(" Error: Name can not be empty.\n\n");
									IsValidName = 0;
								} else {
									IsValidName = 1;
								}
							}
						}
						if (chooseUpdating == 2) {
							countUp = 1;
							while (!IsValidID) {				// nhap ma sinh vien
								printf(" Enter the new ID: ");
								scanf("%s", &IDfromFile);
								if (IsExistsInFile("StudentManagement.txt", IDfromFile) == true) {
									printf(" Error: This ID is already exists.\n\n");
									IsValidID = 0;
								} else if (strlen(IDfromFile) > 8) {
									printf(" Error: ID can not be more than 8 characters.\n\n");
									IsValidID = 0;
								} else if (strlen(IDfromFile) <= 0) {
									printf(" Error: ID can not be empty.\n\n");
									IsValidID = 0;
								} else {
									IsValidID = 1;
								}
							}
						} 
						if (chooseUpdating == 3) {
							countUp = 1;
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
						}
						if (chooseUpdating == 4) {
							countUp = 1;
							while (!IsValidSex) {				// nhap gioi tinh
								printf(" [M] Male or [F] Female? ");
								scanf("%s", &Sex);
								if (Sex[0] == 'M' || Sex[0] == 'm') {
									strcpy(Sex, "Male");
									IsValidSex = 1;
								} else if (Sex[0] == 'F' || Sex[0] == 'f') {
									strcpy(Sex, "Female");
									IsValidSex = 1;
								} else {
									printf(" Error: Your option is not valid!!!\n");
									IsValidSex = 0;
								}
							}		
						}
						if (chooseUpdating == 5) {
							countUp = 1;
							while (!IsValidEmail) {			// nhap email
								printf(" Enter the new email: ");
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
									IsValidEmail = 1;
								}
							}
						}
						if (chooseUpdating == 6) {
							countUp = 1;
							while (!IsValidPhone) {								// nhap phone
								printf(" Enter the new Phone Number: ");
								scanf("%s", &PhoneNumber);
								if (IsExistsInFile("StudentManagement.txt", PhoneNumber) == true) {
									printf(" Error: This Phone Number is ALREADY EXISTS.\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) > 11) {
									printf(" Error: Phone can not be more than 11 characters.\n\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) <= 0) {
									printf(" Error: Phone can not be empty.\n\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) < 10 && strlen(PhoneNumber) > 0) {
									printf(" Error: This is not a valid phone number.\n");
									IsValidPhone = 0;	
								} else { 
									IsValidPhone = 1;
								}
							}
						}
						if (chooseUpdating == 7) {
							countUp = 1;
							while (!IsValidPresentAddress) {		// nhap dia chi hien tai
								printf(" Enter the present address: ");
								scanf(" %[^\n]s", &Address);			// nhap co khoang trang
								if (strlen(Address) > 200) {
									printf(" Error: Enter the address which has under 200 characters.\n\n");
									IsValidPresentAddress = 0;
								} else if (strlen(Address) <= 0) {
									printf(" Error: Please enter the address.\n\n");
									IsValidPresentAddress = 0;
								} else {
									IsValidPresentAddress = 1;
								}
							}
						}
						if (chooseUpdating == 8) {
							countUp = 1;
							while (!IsValidCountries) {				// nhap que quan
								printf(" Enter the country: ");
								scanf(" %[^\n]s", &Country);		// nhap co khoang trang
								if (strlen(Country) > 50) {
									printf(" Error: This is not valid!\n\n");
									IsValidCountries = 0;
								} else if (strlen(Country) <= 0) {
									printf(" Error: Please enter the conutry.\n\n");
									IsValidCountries = 0;
								} else {
									IsValidCountries = 1;
								}
							}
						}
						if (chooseUpdating == 0) {
							break;
						}
								
					}	// end chooseUpdating				
					// nhap vao file
					file = fopen(filename, "a");
					
					fprintf(file, " %s", FullName);  // nhap ten
					for (i = 1; i <= 25 - strlen(FullName); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", IDfromFile);			// nhap ma sinh vien vao file
					for (i = 1; i <= 11 - strlen(IDfromFile); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file,"%s", DateOfBirth);		// xuat ngay thang nam sinh vao file
					for (i = 1; i <= 16 - strlen(DateOfBirth); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Sex);  				// nhap gioi tinh vao file
					for (i = 1; i <= 10 - strlen(Sex); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Email);			// nhap email vao file
					for (i = 1; i <= 25 - strlen(Email); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", PhoneNumber);			// nhap phone vao file
					for (i = 1; i <= 15 - strlen(PhoneNumber); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Address);		// ghi vao file
					for (i = 1; i <= 20 - strlen(Address); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Country);		// ghi vao file
					for (i = 1; i <= 15 - strlen(Country); i++) {
						fprintf(file, " ");
					}
					fprintf(file, "\n");
					
					fclose(file);
					// end
					
					file = fopen(filename, "r");
					countLine = 1;
					while (fgets(lineToCount[countLine], sizeof(lineToCount[countLine]), file) != NULL) {
						countLine++;
					}
					
					countLine--;
					strcpy(lineToCount[indexUpdating], lineToCount[countLine]);
					strcpy(lineToCount[countLine], IsNone);
					countLine--;
					
					fclose(file);
				
					
					file = fopen(filename, "w");
					for (i = 1; i <= countLine; i++) {
						fprintf(file, "%s", lineToCount[i]);
					}
					fclose(file);
					
					if (countUp == 0) {
						printf("\n        The profile has not been updated.    \n\n");
					} else {
						printf("\n        Update successfully.                 \n\n");
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
					
				} // if (numEL >= 2) 
				
			} // if (IsExistsInFile(filename, Name) == true)
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
					IsUpdating = 0;
				} else if (Choices == 'N' || Choices == 'n') {
					IsUpdating = 1;
				}
			} else {
				printf("        Full name       |    ID    |    Birthday   |   Sex   |          Email         | Phone number |       Address     |    Country   |\n\n");
				file = fopen(filename, "r");
				while (fgets(line, sizeof(line), file) != NULL) {
					if (strstr(line, ID) != NULL) {
						printf("%s", line);	
					}
				}
				fclose(file);
				printf("\n-----------------------------------------------------------------------------------------------------------------------------------------\n\n");
				
				file = fopen(filename, "r");
					countLine = 1;
					while (fgets(lineToCount[countLine], sizeof(lineToCount[countLine]), file) != NULL) {
						if (strstr(lineToCount[countLine], ID) != NULL) {
							indexUpdating = countLine;
							fseek(file, -139, SEEK_CUR);
							fscanf(file, "%s", LastName);
							fscanf(file, "%s", MiddleName);
							fscanf(file, "%s", FirstName);
							fscanf(file, "%s", IDfromFile);
							fscanf(file, "%s", DateOfBirth);
							fscanf(file, "%s", Sex);
							fscanf(file, "%s", Email);
							fscanf(file, "%s", PhoneNumber);
							fscanf(file, "%s", Address);
							fscanf(file, "%s", Country1);
							fscanf(file, "%s", Country2);
						}
						countLine++;
					}
					sprintf(FullName, "%s %s %s", LastName, MiddleName, FirstName);  // tao thanh full name
					sprintf(Country, "%s %s", Country1, Country2);
					fclose(file);
					
					char CheckchooseUpdating[10];
					int chooseUpdating;
					int IschoosingUpdating = 0;
					int countUp = 0;
					
					int IsValidName = 0;
					int IsValidID = 0;
					int IsValidSex = 0;
					int IsValidEmail = 0;
					int IsValidPhone = 0;
					int IsValidPresentAddress = 0;
					int IsValidCountries = 0;
					while (IschoosingUpdating == 0) {	
						printf("[1]. Name\n");
						printf("[2]. ID\n");
						printf("[3]. Birthday\n");
						printf("[4]. Sex\n");
						printf("[5]. Email\n");
						printf("[6]. Phone\n");
						printf("[7]. Address\n");
						printf("[8]. Country\n");
						printf("[0]. Exit\n");
						printf("Enter your choices: ");
						scanf(" %s", &CheckchooseUpdating);
						printf("\n\n");
						while (checkInt(CheckchooseUpdating) == false) {
							printf(" Error: Your answer is not valid!!!\n");
							printf(" Enter your choices: ");
							scanf(" %c", &CheckchooseUpdating);
						}
						if (checkInt(CheckchooseUpdating) == true) {
							chooseUpdating = atoi(CheckchooseUpdating);
						}
						if (chooseUpdating == 1) {
							countUp = 1;
							while (!IsValidName) {				// nhap ten sinh vien
								printf(" Enter the new Full Name: ");
								scanf(" %[^\n]s", &FullName);			// co the nhap co khoang trang
								if (strlen(FullName) >= 22) {
									printf(" Error: Name can not be more than 22 characters.\n\n");
									IsValidName = 0;
								} else if (strlen(FullName) <= 0) {
									printf(" Error: Name can not be empty.\n\n");
									IsValidName = 0;
								} else {
									IsValidName = 1;
								}
							}
						}
						if (chooseUpdating == 2) {
							countUp = 1;
							while (!IsValidID) {				// nhap ma sinh vien
								printf(" Enter the new ID: ");
								scanf("%s", &IDfromFile);
								if (IsExistsInFile("StudentManagement.txt", IDfromFile) == true) {
									printf(" Error: This ID is already exists.\n\n");
									IsValidID = 0;
								} else if (strlen(IDfromFile) > 8) {
									printf(" Error: ID can not be more than 8 characters.\n\n");
									IsValidID = 0;
								} else if (strlen(IDfromFile) <= 0) {
									printf(" Error: ID can not be empty.\n\n");
									IsValidID = 0;
								} else {
									IsValidID = 1;
								}
							}
						} 
						if (chooseUpdating == 3) {
							countUp = 1;
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
						}
						if (chooseUpdating == 4) {
							countUp = 1;
							while (!IsValidSex) {				// nhap gioi tinh
								printf(" [M] Male or [F] Female? ");
								scanf("%s", &Sex);
								if (Sex[0] == 'M' || Sex[0] == 'm') {
									strcpy(Sex, "Male");
									IsValidSex = 1;
								} else if (Sex[0] == 'F' || Sex[0] == 'f') {
									strcpy(Sex, "Female");
									IsValidSex = 1;
								} else {
									printf(" Error: Your option is not valid!!!\n");
									IsValidSex = 0;
								}
							}		
						}
						if (chooseUpdating == 5) {
							countUp = 1;
							while (!IsValidEmail) {			// nhap email
								printf(" Enter the new email: ");
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
									IsValidEmail = 1;
								}
							}
						}
						if (chooseUpdating == 6) {
							countUp = 1;
							while (!IsValidPhone) {								// nhap phone
								printf(" Enter the new Phone Number: ");
								scanf("%s", &PhoneNumber);
								if (IsExistsInFile("StudentManagement.txt", PhoneNumber) == true) {
									printf(" Error: This Phone Number is ALREADY EXISTS.\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) > 11) {
									printf(" Error: Phone can not be more than 11 characters.\n\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) <= 0) {
									printf(" Error: Phone can not be empty.\n\n");
									IsValidPhone = 0;
								} else if (strlen(PhoneNumber) < 10 && strlen(PhoneNumber) > 0) {
									printf(" Error: This is not a valid phone number.\n");
									IsValidPhone = 0;	
								} else { 
									IsValidPhone = 1;
								}
							}
						}
						if (chooseUpdating == 7) {
							countUp = 1;
							while (!IsValidPresentAddress) {		// nhap dia chi hien tai
								printf(" Enter the present address: ");
								scanf(" %[^\n]s", &Address);			// nhap co khoang trang
								if (strlen(Address) > 200) {
									printf(" Error: Enter the address which has under 200 characters.\n\n");
									IsValidPresentAddress = 0;
								} else if (strlen(Address) <= 0) {
									printf(" Error: Please enter the address.\n\n");
									IsValidPresentAddress = 0;
								} else {
									IsValidPresentAddress = 1;
								}
							}
						}
						if (chooseUpdating == 8) {
							countUp = 1;
							while (!IsValidCountries) {				// nhap que quan
								printf(" Enter the country: ");
								scanf(" %[^\n]s", &Country);		// nhap co khoang trang
								if (strlen(Country) > 50) {
									printf(" Error: This is not valid!\n\n");
									IsValidCountries = 0;
								} else if (strlen(Country) <= 0) {
									printf(" Error: Please enter the conutry.\n\n");
									IsValidCountries = 0;
								} else {
									IsValidCountries = 1;
								}
							}
						}
						if (chooseUpdating == 0) {
							break;
						}
								
					}	// end chooseUpdating				
					// nhap vao file
					file = fopen(filename, "a");
					
					fprintf(file, " %s", FullName);  // nhap ten
					for (i = 1; i <= 25 - strlen(FullName); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", IDfromFile);			// nhap ma sinh vien vao file
					for (i = 1; i <= 11 - strlen(IDfromFile); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file,"%s", DateOfBirth);		// xuat ngay thang nam sinh vao file
					for (i = 1; i <= 16 - strlen(DateOfBirth); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Sex);  				// nhap gioi tinh vao file
					for (i = 1; i <= 10 - strlen(Sex); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Email);			// nhap email vao file
					for (i = 1; i <= 25 - strlen(Email); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", PhoneNumber);			// nhap phone vao file
					for (i = 1; i <= 15 - strlen(PhoneNumber); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Address);		// ghi vao file
					for (i = 1; i <= 20 - strlen(Address); i++) {
						fprintf(file, " ");
					}
					
					fprintf(file, "%s", Country);		// ghi vao file
					for (i = 1; i <= 15 - strlen(Country); i++) {
						fprintf(file, " ");
					}
					fprintf(file, "\n");
					
					fclose(file);
					// end
					
					file = fopen(filename, "r");
					countLine = 1;
					while (fgets(lineToCount[countLine], sizeof(lineToCount[countLine]), file) != NULL) {
						countLine++;
					}
					
					countLine--;
					strcpy(lineToCount[indexUpdating], lineToCount[countLine]);
					strcpy(lineToCount[countLine], IsNone);
					countLine--;
					
					fclose(file);
				
					
					file = fopen(filename, "w");
					for (i = 1; i <= countLine; i++) {
						fprintf(file, "%s", lineToCount[i]);
					}
					fclose(file);
					
					if (countUp == 0) {
						printf("\n        The profile has not been updated.    \n\n");
					} else {
						printf("\n        Update successfully.                 \n\n");
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
				
			} //if (IsExistsInFile(filename, ID) == true
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
		printf(" Delete by Name[N] ? or by ID[I]? or [E] to exit");
		printf(" Your choices: ");
		scanf(" %c", &Option);
		printf("\n");
		if (Option == 'e' || Option == 'E') {
			printf("\n\n");
			system("cls");
			return;
		}
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
					system("cls");
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
					system("cls");
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
					system("cls");
					IsDeleting = 1;
				}
			}
		}
	}
	
}

void DeleteManyStudents (const char *filename) {	// xoa nhieu hoc sinh
	int IsDeletingMany = 0;
	while (!IsDeletingMany) {
		char studentsID[20][200];
		char DelId[200];
		char *p;
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
		
		ShowAllList(filename);
		
		printf("\n\n Eg: SE180123, SS180321, SE170433,...\n\n");
		
		printf(" Enter those ID that you want to delete('exit' to go back): ");
		scanf(" %[^\n]s", &DelId);
		
		if (strcmp(DelId, "exit") == 0) {
			system("cls");
			return;
		}
	
		i = 0;
		p = strtok(DelId, ", ");
		while (p != NULL) {				//lay cac ID trong mang ma nguoi dung nhap
			strcpy(studentsID[i], p);
			p = strtok(NULL, ", ");
			i++;
		}
		printf("\n");
		
		file = fopen(filename, "r");
		char line[200][200];
		int countLine = 0;
		while (fgets(line[countLine], sizeof(line[countLine]), file) != NULL) {
			countLine++;
		}
		fclose(file);
		
		for (j = 0; j < i; j++) {
			int found = 0;
			int k;
			for (k = 0; k < countLine; k++) {
				if (strstr(line[k], studentsID[j]) != NULL) {
					found = 1;
					strcpy(line[k], "");
					break;
				}
			}
			if (!found) {
				printf(" The '%s' is not found. \n\n", studentsID[j]);
			}
		}
		
		file = fopen(filename, "w");
		for (j = 0; j < countLine; j++) {
			if (strcmp(line[j], "") != 0) {
				fprintf(file, "%s", line[j]);
			}
		}
		fclose(file);
		
		char DeleteSuccess[100]   = "               Delete Successfully                       \n\n";
    	for (i = 0; i < strlen(DeleteSuccess); i++) {		// chay chu thank you
        	printf("%c", DeleteSuccess[i]);
        	Sleep(40);
    	}
			
		printf(" Do you want to continue ? [Y/N]. Your answer: ");
		char Choices;								// bien de nguoi dung nhap yes/no
		scanf(" %c", &Choices);						
		printf("\n");
		if (Choices == 'Y' || Choices == 'y') {
			IsDeletingMany = 0;
		} else if (Choices == 'N' || Choices == 'n') {
			system("cls");
			IsDeletingMany = 1;
		}
	}

}

void DeleteInOneRange (const char *filename) {			// xoa 1 khoang trong file
	int IsDeletingRange = 0;
	while(!IsDeletingRange) {
		char start[20];
		char end[20];
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
	
		int IsEntering = 0;
		while (!IsEntering) {
			
			int IsValidStart = 0;
			while (!IsValidStart) {
				printf("Enter the 'start' ID ('exit' to go back): ");
				scanf(" %s", &start);
				
				if (strcmp(start, "exit") == 0) {
					system("cls");
					return;
				}
				
				if (IsExistsInFile(filename, start) == false) {
					printf("The start ID is not found.\n\n");
					IsValidStart = 0;
				} else if (strlen(start) > 8) {
					printf("The ID is not valid\n\n");
					IsValidStart = 0;
				} else {
					IsValidStart = 1;
				}
			}
			
			
			int IsValidEnd = 0;
			while (!IsValidEnd) {
				printf("Enter the 'end' ID: ");
				scanf(" %s", &end);
				if (IsExistsInFile(filename, end) == false) {
					printf("The end ID is not found.\n\n");
					IsValidEnd = 0;
				} else if (strlen(end) > 8) {
					printf("The end ID is not found.\n\n");
					IsValidEnd = 0;
				} else {
					IsValidEnd = 1;
				}
			}
			
			//kiem tra 'start' co o tren 'end' hay khong
			file = fopen(filename, "r");
			char checkLineStart[200];
			char checkLineEnd[200];
			TotalStudents = 0;
			while(fgets(checkLineStart, sizeof(checkLineEnd), file) != NULL) {
				if (strstr(checkLineStart, start) != NULL) {
					char Country1[20], Country2[20];
					char* p = strtok(checkLineStart, " ");
			        strcpy(Students[TotalStudents].LastName, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].MiddleName, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].FirstName, p);
			
			        sprintf(Students[TotalStudents].Name, "%s %s %s", Students[TotalStudents].LastName, Students[TotalStudents].MiddleName, Students[TotalStudents].FirstName);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].ID, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].DateOfBirth, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].Sex, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].Email, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].PhoneNumber, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].PresentAddress, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Country1, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Country2, p);
			
			        sprintf(Students[TotalStudents].Countries, "%s %s", Country1, Country2);
			
			        TotalStudents++;
				}
			}
			
			while (fgets(checkLineEnd, sizeof(checkLineEnd), file) != NULL) {
				if (strstr(checkLineEnd, end) != NULL) {
					char Country1[20], Country2[20];
					char* p = strtok(checkLineEnd, " ");
			        strcpy(Students[TotalStudents].LastName, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].MiddleName, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].FirstName, p);
			
			        sprintf(Students[TotalStudents].Name, "%s %s %s", Students[TotalStudents].LastName, Students[TotalStudents].MiddleName, Students[TotalStudents].FirstName);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].ID, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].DateOfBirth, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].Sex, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].Email, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].PhoneNumber, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Students[TotalStudents].PresentAddress, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Country1, p);
			
			        p = strtok(NULL, " ");
			        strcpy(Country2, p);
			
			        sprintf(Students[TotalStudents].Countries, "%s %s", Country1, Country2);
			
				}
			}
			
			int result = strcmp(Students[0].FirstName, Students[1].FirstName);
			if (result == 0) {
				result = strcmp(Students[0].MiddleName, Students[1].MiddleName);
				if (result == 0) {
					result = strcmp(Students[0].LastName, Students[1].LastName);
				}
			}
			if (result > 0) {
				printf("\n You entered the wrong order!!!\n\n");
				IsEntering = 0;
			} else {
				IsEntering = 1;
			}
		
		fclose(file);
		//kiem tra xong
		} // nhap xong
		
		
		
		// M? file cho d?c
	    FILE* file = fopen(filename, "r");
	    if (file == NULL) {
	        printf("Can not access\n", filename);
	        return;
	    }
	
	    // T?o file t?m d? luu d? li?u dã l?c
	    FILE* tempFile = fopen("temp.txt", "w");
	    if (tempFile == NULL) {
	        printf("Can not access\n");
	        fclose(file);
	        return;
	    }
			
	    // Ð?c t?ng dòng trong file
	    char line[200];
	    int deleteFlag = 0; // C? xác d?nh khi nào b?t d?u và k?t thúc kho?ng c?n xóa
	
	    while (fgets(line, sizeof(line), file)) {
	        // Ki?m tra n?u dòng ch?a chu?i b?t d?u c?a kho?ng c?n xóa
	        if (strstr(line, start) != NULL) {
	            deleteFlag = 1;
	            continue; // Chuy?n d?n dòng ti?p theo
	        }
	
	        // Ki?m tra n?u dòng ch?a chu?i k?t thúc c?a kho?ng c?n xóa
	        if (strstr(line, end) != NULL) {
	            deleteFlag = 0;
	            continue; // Chuy?n d?n dòng ti?p theo
	        }
	
	        // Xóa dòng n?m trong kho?ng c?n xóa
	        if (deleteFlag == 1) {
	            continue; // Chuy?n d?n dòng ti?p theo
	        }
	
	        // Ghi dòng vào file t?m
	        fputs(line, tempFile);
	    }
	
	    // Ðóng file
	    fclose(file);
	    fclose(tempFile);
	
	    // Xóa file g?c
	    remove(filename);
	
	    // Ð?i tên file t?m thành tên file g?c
	    rename("temp.txt", filename);
	
	    char DeleteSuccess[100]   = "               Delete Successfully                       \n\n";
	    for (i = 0; i < strlen(DeleteSuccess); i++) {		// chay chu thank you
	        printf("%c", DeleteSuccess[i]);
	        Sleep(40);
	    }
	    
	    printf(" Do you want to continue ? [Y/N]. Your answer: ");
		char Choices;								// bien de nguoi dung nhap yes/no
		scanf(" %c", &Choices);						
		printf("\n");
		if (Choices == 'Y' || Choices == 'y') {
			IsDeletingRange = 0;
		} else if (Choices == 'N' || Choices == 'n') {
			system("cls");
			IsDeletingRange = 1;
		}
	    
	}
}

void DeleteManyRanges(const char *filename) {			// xoa nhieu khoang trong file
	int IsDeletingRanges = 0;
	while (!IsDeletingRanges) {
		char RangesOfId[200];
		char CopyRanges[100][200];
		char *token;
		char *p;
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
		printf("\n\nEnter with this format: Start-End");
		printf(" \n\nEg: SE180123-SE180321, SS180456-SE180567, ....\n\n");
		
		printf(" Enter those ranges of ID that you want to delete ('exit' to go back): ");
		scanf(" %[^\n]s", RangesOfId);
		
		if (strcmp(RangesOfId, "exit") == 0) {
			system("cls");
			return;
		}
		
		int i = 0;
		token = strtok(RangesOfId, ", ");
		while (token != NULL) {
			strcpy(CopyRanges[i], token);
			token = strtok(NULL, ", ");
			i++;
		}
		
		int j;
		for (j = 0; j < i; j++) {   // bat dau xoa nhieu khoang
			p = strtok(CopyRanges[j], "-");
			while(p != NULL) {
				char start[20], end[20];
				strcpy(start, p);
				p = strtok(NULL, "-");
				strcpy(end, p);
				p = strtok(NULL, "-");
				
				// M? file cho d?c
			    FILE* file = fopen(filename, "r");
			    if (file == NULL) {
			        printf("Can not access\n", filename);
			        return;
			    }
			
			    // T?o file t?m d? luu d? li?u dã l?c
			    FILE* tempFile = fopen("temp.txt", "w");
			    if (tempFile == NULL) {
			        printf("Can not access\n");
			        fclose(file);
			        return;
			    }
			    
				// Ð?c t?ng dòng trong file
			    char line[200];
			    int deleteFlag = 0; // C? xác d?nh khi nào b?t d?u và k?t thúc kho?ng c?n xóa
			
			    while (fgets(line, sizeof(line), file)) {
			        // Ki?m tra n?u dòng ch?a chu?i b?t d?u c?a kho?ng c?n xóa
			        if (strstr(line, start) != NULL) {
			            deleteFlag = 1;
			            continue; // Chuy?n d?n dòng ti?p theo
			        }
			
			        // Ki?m tra n?u dòng ch?a chu?i k?t thúc c?a kho?ng c?n xóa
			        if (strstr(line, end) != NULL) {
			            deleteFlag = 0;
			            continue; // Chuy?n d?n dòng ti?p theo
			        }
			
			        // Xóa dòng n?m trong kho?ng c?n xóa
			        if (deleteFlag == 1) {
			            continue; // Chuy?n d?n dòng ti?p theo
			        }
			
			        // Ghi dòng vào file t?m
			        fputs(line, tempFile);
			    }
			
			    // Ðóng file
			    fclose(file);
			    fclose(tempFile);
			
			    // Xóa file g?c
			    remove(filename);
			
			    // Ð?i tên file t?m thành tên file g?c
			    rename("temp.txt", filename);
			}
		}   // xoa xong
		printf("\n\n");
		char DeleteSuccess[100]   = "               Delete Successfully                       \n\n";
	    for (i = 0; i < strlen(DeleteSuccess); i++) {		// chay chu thank you
	        printf("%c", DeleteSuccess[i]);
	        Sleep(40);
	    }
		
		for (j = 0; j < i; j++) {
			strcpy(CopyRanges[j], "");
		}
		
		printf(" Do you want to continue ? [Y/N]. Your answer: ");
		char Choices;								// bien de nguoi dung nhap yes/no
		scanf(" %c", &Choices);						
		printf("\n");
		if (Choices == 'Y' || Choices == 'y') {
			IsDeletingRanges = 0;
		} else if (Choices == 'N' || Choices == 'n') {
			system("cls");
			IsDeletingRanges = 1;
		}
	} // end IsDeletingRanges		
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

void ShowAllAcc(const char *filename) {  // xuat cac file sign in, sign up
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
	
	printf("     Username    |     Password    |\n\n");
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
	printf("\n\n-------------------------------------\n\n");
}

void GrantPermission(const char *filename) {	//cho phep dang nhap
	int IsGranting = 0;
	while (!IsGranting) {
		char username[20];
		char accepted[20][200];
		char *token;
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
		ShowAllAcc(filename);
		printf(" Enter those username that you allow to sign in (enter 'exit' if you want to go back to menu): ");
		scanf(" %[^\n]s", &username);
		
		if (strcmp(username, "exit") == 0) {
			printf("\n\n");
			return;
		}
		
		file = fopen(filename, "r");
		char line[200][200];
		int countLine = 0;
		while (fgets(line[countLine], sizeof(line[countLine]), file) != NULL) {
			countLine++;
		}
		fclose(file);
		
		
		i = 0;
		token = strtok(username, ", ");
		while (token != NULL) {
			strcpy(accepted[i], token);
			token = strtok(NULL, ", ");
			i++;
		}
		
		FILE *tempFile = fopen("SignIn.txt", "a");
		for (j = 0; j < i; j++) {
			int found = 0;
			int k;
			for (k = 0; k < countLine; k++) {
				if (strstr(line[k], accepted[j]) != NULL) {
					found = 1;
					fputs(line[k], tempFile);
					strcpy(line[k], "");
					break;
				}
			}
			if (!found) {
				printf(" The '%s' is not found. \n\n", accepted[j]);
			}
		}
		fclose(tempFile);
		
		file = fopen(filename, "w");
		for (j = 0; j < countLine; j++) {
			if (strcmp(line[j], "") != 0) {
				fprintf(file, "%s", line[j]);
			}
		}
		fclose(file);
		
		printf("\n\n");
		char Success[100]   = "               Granting Successfully                       \n\n";
	    for (i = 0; i < strlen(Success); i++) {		// chay chu thank you
	        printf("%c", Success[i]);
	        Sleep(40);
	    }
		
		for (j = 0; j < i; j++) {
			strcpy(accepted[j], "");
		}
		printf(" Do you want to continue ? [Y/N]. Your answer: ");
		char Choices;								// bien de nguoi dung nhap yes/no
		scanf(" %c", &Choices);						
		printf("\n");
		if (Choices == 'Y' || Choices == 'y') {
			IsGranting = 0;
		} else if (Choices == 'N' || Choices == 'n') {
			IsGranting = 1;
		}
	} // end IsGranting
}





