#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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


int j, i;
int compareNames(const void* a, const void* b) {
    const struct StudentInfo* studentA = (const struct StudentInfo*)a;
    const struct StudentInfo* studentB = (const struct StudentInfo*)b;
    return strcmp(studentA->FirstName, studentB->FirstName);
}

void Sort(const char* filename) {
	char Country1[10];
	char Country2[10];
	char Country[20];
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        printf("Cannot open file.\n");
        return;
    }
    
    struct StudentInfo Students[200];
    char line[200][200];

    int TotalStudents = 1;
    while (fgets(line[TotalStudents], sizeof(line[TotalStudents]), file) != NULL) {
        fscanf(file, "%s", Students[TotalStudents].LastName);
        fscanf(file, "%s", Students[TotalStudents].MiddleName);
        fscanf(file, "%s", Students[TotalStudents].FirstName);
        fscanf(file, "%s", Students[TotalStudents].ID);
        fscanf(file, "%s", Students[TotalStudents].DateOfBirth);
        fscanf(file, "%s", Students[TotalStudents].Sex);
        fscanf(file, "%s", Students[TotalStudents].Email);
        fscanf(file, "%s", Students[TotalStudents].PhoneNumber);
        fscanf(file, "%s", Students[TotalStudents].PresentAddress);
        fscanf(file, "%s", Country1);
        fscanf(file, "%s", Country2);
        
        sprintf(Country, "%s %s", Country1, Country2);
		strcpy(Students[TotalStudents].Countries, Country);	

        sprintf(Students[TotalStudents].Name, "%s %s %s",
                Students[TotalStudents].LastName,
                Students[TotalStudents].MiddleName,
                Students[TotalStudents].FirstName);

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

int main() {
	
    const char* filename = "test.txt";
    Sort(filename);

    return 0;
}

