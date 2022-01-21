#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
    unsigned int id; // student id
    char name[20]; // student name
    char surname[20]; // student surname
    char department[20]; // department of student
    int grade; // grade of student
} studentData;

void showRecords(FILE *filePtr);
int updateGrade(FILE *filePtr, unsigned int id, int newGrade);
int addStudent(FILE *filePtr, unsigned int id, char name[], char surname[], char department[], int grade);
int deleteStudent(FILE *filePtr, unsigned int id);
int showDepartmentRecords(FILE *filePtr, char department[]);
void writeBinary(FILE *filePtr);

int main()
{
    static int writeOneTime =0;
    unsigned int id;
    int newGrade;
    int status;
    char name[20];
    char surname[20];
    char department[20];
    int grade;
    int count;
    FILE *filePtr;
    filePtr = fopen("exam.bin","rb+");
    writeOneTime++;
    if (filePtr == NULL)
    {
        printf("Could not open exam.bin");
        return 0;
    }

    showRecords(filePtr);

    int option;

    printf("\nPlease choose an operation:\n");
    printf("1 : Update Grade\n");
    printf("2 : Add Student\n");
    printf("3 : Delete Student\n");
    printf("4 : Show Department Record\n");
    printf("> ");
    scanf("%d",&option);

    switch (option)
    {
    case 1:
        printf("\nStudent id: ");
        scanf("%d",&id);
        printf("New grade: ");
        scanf("%d",&newGrade);
        status = updateGrade(filePtr, id, newGrade);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No student with id %d\n", id);
        break;
    case 2:
        printf("\nStudent id: ");
        scanf("%d",&id);
        printf("Name: ");
        scanf("%s",name);
        printf(" Surname: ");
        scanf("%s",surname);
        printf("Department: ");
        scanf("%s",department);
        printf("Grade: ");
        scanf("%d",&grade);
        status = addStudent(filePtr, id, name, surname, department, grade);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("There is already a student with id %d\n", id);
        break;
    case 3:
        printf("\nStudent id: ");
        scanf("%d",&id);
        status = deleteStudent(filePtr, id);
        if (status == 1)
            showRecords(filePtr);
        else
            printf("No student with id %d\n", id);
        break;
    case 4:
        printf("\nDepartment: ");
        scanf("%s",department);
        count = showDepartmentRecords(filePtr, department);
        if (count == 0)
        {
            printf("\n%-3s %-20s %-20s %-20s %s\n",
                   "ID",
                   "Name",
                   "Surname",
                   "Department",
                   "Grade");
            printf("No student in department %s\n", department);
        }

        else
            printf("There are %d students in department %s\n", count, department);
        break;
    }

    fclose(filePtr);
    return 0;
}

void showRecords(FILE *filePtr)
{
    fseek(filePtr, 0, SEEK_SET);

    printf("\n%-3s %-20s %-20s %-20s %s\n",
           "ID",
           "Name",
           "Surname",
           "Department",
           "Grade");

    while (!feof(filePtr))
    {
        studentData student;
        int result = fread(&student, sizeof(studentData), 1, filePtr);
        if (result != 0 && student.id != 0)
        {
            printf("%-3d %-20s %-20s %-20s %d\n",
                   student.id,
                   student.name,
                   student.surname,
                   student.department,
                   student.grade);
        }
    }
}

int updateGrade(FILE *filePtr, unsigned int id, int newGrade)
{
    fseek(filePtr, 0, SEEK_SET);
    int isFound=0;
    studentData currentStudent;
    int inputstatus;
    // filePtr = fopen("library.bin","rb+");
    for(int i=0; i<100; i++)
    {
        // printf("b");
        inputstatus=fread(&currentStudent,sizeof(studentData),1,filePtr);
        if(currentStudent.id == id)
        {
            // printf("b");
            isFound=1;
            currentStudent.grade=newGrade;
            // printf("b");
            fseek(filePtr,(currentStudent.id-2)*sizeof(studentData),SEEK_SET);
            fwrite(&currentStudent,sizeof(studentData),1,filePtr);
            // fclose(filePtr);
            // printf("b");
            return 1;
        }

    }
    if( isFound == 0)
    {
        // fclose(filePtr);
        return 0;
    }


}





int addStudent(FILE *filePtr, unsigned int id, char name[], char surname[], char department[], int grade)
{
    fseek(filePtr, 0, SEEK_SET);
    studentData addedStruct,temp;
    addedStruct.id=id;
    strcpy(addedStruct.name,name);
    strcpy(addedStruct.surname,surname);
    strcpy(addedStruct.department,department);
    addedStruct.grade=grade;

    // while(!feof(filePtr))


    fseek(filePtr,(addedStruct.id-2)*sizeof(studentData),SEEK_SET);
    fread(&temp,sizeof(studentData),1,filePtr);
    if(temp.id== id)
    {
        return 0;

    }
    else
    {
        fseek(filePtr,(addedStruct.id-2)*sizeof(studentData),SEEK_SET);
        fwrite(&addedStruct,sizeof(studentData),1,filePtr);
        return 1;
    }
}

int deleteStudent(FILE *filePtr, unsigned int id)
{
    fseek(filePtr, 0, SEEK_SET);

    int isFound=0;
    int inputstatus;
    studentData currentstruct;
    for(int i=0; i<100; i++)
    {
        inputstatus=fread(&currentstruct,sizeof(studentData),1,filePtr);
        if(currentstruct.id == id)
        {
            studentData temp= {0,"","",0,0};
            isFound=1;
            int tempid=currentstruct.id;
            fseek(filePtr,(tempid-2)*sizeof(studentData),SEEK_SET);
            fwrite(&temp,sizeof(studentData),1,filePtr);

            return 1;
        }
    }
    if(isFound==0)
    {
        return 0;
    }
}

int showDepartmentRecords(FILE *filePtr, char department[])
{
    int recordCounter=0;
    int printOnce=1;
    int isFound=0;
    fseek(filePtr, 0, SEEK_SET);
    studentData temp;
    while(!feof(filePtr))
    {
        fread(&temp,sizeof(studentData),1,filePtr);
        if(strcasecmp(department,temp.department)==0)
        {
            isFound=1;
            recordCounter++;
            if(printOnce>0)
            {
                printf("\n%-3s %-20s %-20s %-20s %s\n",
                       "ID",
                       "Name",
                       "Surname",
                       "Department",
                       "Grade");
                printOnce--;
            }

            printf("%-3d %-20s %-20s %-20s %d\n",
                   temp.id,
                   temp.name,
                   temp.surname,
                   temp.department,
                   temp.grade);

        }

    }
    return recordCounter;

}
void writeBinary(FILE *filePtr)
{
    /*ID  Name        Surname      Department        Grade
    3   Ozge        Saygi	     CMPE               78
    5   Mert        Kucuk        CMPE               65
    7   Cenk        Gulec        SENG               87
    12  Selen       Sahin        EE                 42
    15  Dolunay     Derin        SENG               71
    19  Suna        Yilmaz       EE                 94   */

    studentData currentstruct;
    int inputstatus;
    //FILE *inputfile = fopen("library.bin","rb");
    for(int i=0; i<100; i++)
    {
        if(i==2)
        {
            currentstruct.id=3;
            strcpy(currentstruct.name,"Ozge");
            strcpy(currentstruct.surname,"Saygi");
            strcpy(currentstruct.department,"CMPE");
            currentstruct.grade=78;
            fseek(filePtr,(i-1)*sizeof(studentData),SEEK_SET);
            fwrite(&currentstruct,sizeof(studentData),1,filePtr);
        }
        else if(i==4)
        {
            currentstruct.id=5;
            strcpy(currentstruct.name,"Mert");
            strcpy(currentstruct.surname,"Kucuk");
            strcpy(currentstruct.department,"CMPE");
            currentstruct.grade=65;
            fseek(filePtr,(i-1)*sizeof(studentData),SEEK_SET);
            fwrite(&currentstruct,sizeof(studentData),1,filePtr);
        }
        else if(i==6)
        {
            currentstruct.id=7;
            strcpy(currentstruct.name,"Cenk");
            strcpy(currentstruct.surname,"Gulec");
            strcpy(currentstruct.department,"SENG");
            currentstruct.grade=87;
            fseek(filePtr,(i-1)*sizeof(studentData),SEEK_SET);
            fwrite(&currentstruct,sizeof(studentData),1,filePtr);
        }
        else if(i==11)
        {
            currentstruct.id=12;
            strcpy(currentstruct.name,"Selen");
            strcpy(currentstruct.surname,"Sahin");
            strcpy(currentstruct.department,"EE");
            currentstruct.grade=42;
            fseek(filePtr,(i-1)*sizeof(studentData),SEEK_SET);
            fwrite(&currentstruct,sizeof(studentData),1,filePtr);
        }
        else if(i==14)
        {
            currentstruct.id=15;
            strcpy(currentstruct.name,"Dolunay");
            strcpy(currentstruct.surname,"Derin");
            strcpy(currentstruct.department,"SENG");
            currentstruct.grade=71;
            fseek(filePtr,(i-1)*sizeof(studentData),SEEK_SET);
            fwrite(&currentstruct,sizeof(studentData),1,filePtr);
        }
        else if(i==18)
        {
            currentstruct.id=19;
            strcpy(currentstruct.name,"Suna");
            strcpy(currentstruct.surname,"Yilmaz");
            strcpy(currentstruct.department,"EE");
            currentstruct.grade=94;
            fseek(filePtr,(i-1)*sizeof(studentData),SEEK_SET);
            fwrite(&currentstruct,sizeof(studentData),1,filePtr);
        }
    }
}
