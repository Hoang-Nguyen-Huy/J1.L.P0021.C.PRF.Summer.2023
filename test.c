#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdbool.h>
#include <windows.h>
#include <unistd.h>
FILE *file;
struct StudentInfo {
    char LastName[10];
    char MiddleName[10];
    char FirstName[10];
    char Name[30];             // ten
    char ID[10];               // ma sinh vien
    char Email[100];           // email
    char PhoneNumber[15];      // so dien thoai
    char Sex[10];              // gioi tinh
    char DateOfBirth[50];      // ngay sinh
    char PresentAddress[100];  // noi o hien tai
    char Countries[100];       // que quan
};

struct StudentInfo Students[200];
int i,j;
int TotalStudents = 0;

struct StudentInfo Students[200];
int compareNames(const void* a, const void* b) {
    const struct StudentInfo* studentA = (const struct StudentInfo*)a;
    const struct StudentInfo* studentB = (const struct StudentInfo*)b;

    int result = strcmp(studentA->FirstName, studentB->FirstName);
    if (result == 0) {  // FirstName is equal, compare MiddleName
        result = strcmp(studentA->MiddleName, studentB->MiddleName);
    }

    return result;
}


void Sort(const char* filename) {
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

int main() {
    const char* filename = "test.txt";
    Sort(filename);

    return 0;
}

