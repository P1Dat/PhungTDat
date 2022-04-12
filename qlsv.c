#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <ctype.h>
int n = 0, sl = 10;
const char *email = {"@sis.hust.edu.vn"};
struct hssv{
    char name[30];
    char gender;
    struct{
        int date;
        int month;
        int year;
    }dob;
    char mssv[10];
    char class[10];
    float grade;
    char mail[100];
} *ds, temp;
void add_student(){
    while(1){
        printf("\nStudent no %d\n", n+1);
        printf("Full name : "); fflush(stdin); gets(ds[n].name);
        if(ds[n].name[0] == '\0') break;
        printf("Gender (M/F) : "); scanf("%c", &ds[n].gender);
        printf("Enter date of birth : \n");
        printf("Enter date : "); scanf("%d", &ds[n].dob.date);
        printf("Enter month : "); scanf("%d", &ds[n].dob.month);
        printf("Enter year : "); scanf("%d", &ds[n].dob.year);
        printf("Enter student's ID : "); fflush(stdin); gets(ds[n].mssv);
        printf("Enter class : "); fflush(stdin); gets(ds[n].class);
        printf("Enter ICT grade : "); scanf("%f", &ds[n].grade);
        n++;
        if (n>=sl){
            sl+=10;
            ds = (struct hssv*) realloc(ds, sl);
        }
    }
    getch();
}
int get_firstName(char *name){
    int i = strlen(name) - 1;         
    while (i >= 0 && name[i] == ' ') i--;
    while (i >= 0 && name[i] != ' ') i--;
    return i+1;
}
void get_Email(){
    int i, j, index;
    char *p;
    char **name_array;
    name_array = (char**) malloc(n*sizeof(char*));
    for (i = 0; i < n; i++){
        name_array[i] = (char*) malloc(80*sizeof(char));
    }
    char **temp_Name;
    temp_Name = (char**) malloc(n*sizeof(char*));
    for (i = 0; i < n; i++){
        temp_Name[i] = (char*) malloc(80*sizeof(char));
    }
    for (i = 0; i < n; i++){
        strcpy(temp_Name[i], ds[i].name);
    }
    for (i = 0; i < n; i++){
        p = strtok(temp_Name[i], " ");
        while(p != NULL){
            name_array[index] = p; 
            index++;
            p = strtok(NULL, " ");
        }
        strcpy(ds[i].mail, name_array[index-1]);
        strcat(ds[i].mail, ".");
        for (j = 0; j < index-1; j++){
            strncat(ds[i].mail, name_array[j], 1);
        }
        strcat(ds[i].mail, ds[i].mssv+2);
        strcat(ds[i].mail, email);
        //printf("%s\n",ds[i].mail);
        index = 0;
    }
    printf("\n                            STUDENTS' EMAIL LIST  \n");
    printf("\n-----------------------------------------------------------------------------------");
    printf("\n| NO |      Full name       |     ID     |                  EMAIL                 |");
    printf("\n|----|----------------------|------------|----------------------------------------|");
    for (i = 0; i < n; i++){
        printf("\n| %02d | %-20s |  %-8s  | %-38s |", i+1, ds[i].name, ds[i].mssv, ds[i].mail);
    }
    printf("\n|----|----------------------|------------|----------------------------------------|");
    getch();
}
void sortbyname(){
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = i+1; j < n; j++){
            if (strcmpi(ds[i].class, ds[j].class) < 0){
                temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            } else if (strcmpi(ds[i].class, ds[j].class) == 0){
                if (strcmpi(ds[i].name+get_firstName(ds[i].name), ds[j].name+get_firstName(ds[j].name)) > 0){
                    temp = ds[i];
                    ds[i] = ds[j];
                    ds[j] = temp;
                } else if (strcmpi(ds[i].name+get_firstName(ds[i].name), ds[j].name+get_firstName(ds[j].name)) == 0){
                    if(strcmpi(ds[i].name, ds[j].name) > 0){
                        temp = ds[i];
                        ds[i] = ds[j];
                        ds[j] = temp;
                    }
                }
            }
        }
    }
    printf(" FINISHED SORTING !");
    getch();
}
void sortbygrade(){
    int i, j;
    for (i = 0; i < n-1; i++){
        for (j = i+1; j < n; j++){
            if (strcmpi(ds[i].class, ds[j].class) < 0){
                temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            } else if (strcmpi(ds[i].class, ds[j].class) == 0){
                if (ds[i].grade > ds[j].grade){
                    temp = ds[i];
                    ds[i] = ds[j];
                    ds[j] = temp;
                }
            }
        }
    }
    printf(" FINISHED SORTING !");
    getch();
}
void sortbyonlygrade(){
    int i, j;
    for (i = 0; i< n - 1; i++){
        for (j = i+1; j < n; j++){
            if (ds[i].grade > ds[j].grade){
                temp = ds[i];
                ds[i] = ds[j];
                ds[j] = temp;
            }
        }
    }
    printf(" FINISHED SORTING !\n");
    getch();
}
void printhelist(){
      int i;
  printf("\n                                  STUDENT LIST \n");
  printf("\n---------------------------------------------------------------------------------");
  printf("\n| NO |  Classname  |      Full name       |     ID     | G |     DOB    | Grade |");
  printf("\n|----|-------------|----------------------|------------|---|------------|-------|");
  for(i=0;i<n;i++) 
  printf("\n| %02d | %-11s | %-20s |  %8s  | %c | %02d/%02d/%4d | %5.1f |",i+1,ds[i].class,ds[i].name,
	ds[i].mssv,ds[i].gender,ds[i].dob.date,ds[i].dob.month,ds[i].dob.year,ds[i].grade);
  printf("\n|----|-------------|----------------------|------------|---|------------|-------|");
  getch();
}
int main(){
    ds = (struct hssv*) malloc(sl*sizeof(struct hssv));
    char key;
    while(1){
        system("cls");
        printf("    STUDENT MANAGING PROGRAM   \n");
        printf("1. Add student\n");
        printf("2. Sort by class name and first name\n");
        printf("3. Sort by class name and ICT grades\n");
        printf("4. Sort by ICT grades\n");
        printf("5. Get students' emails\n");
        printf("6. Print the list\n");
        printf("Press 1 - 4 to choose one option from the list, or another key to exit\n");
        key = getch();
        if (key == '1') add_student();
        else if (key == '2') sortbyname();
        else if (key == '3') sortbygrade();
        else if (key == '4') sortbyonlygrade();
        else if (key == '5') get_Email();
        else if (key == '6') printhelist();
        else {
            printf("Do you want to quit? Y/y \n");
            key = getch();
            if (key == 'y' || key == 'Y'){
                break;
                return 0;
            }
        }
    }
    return 0;
} 