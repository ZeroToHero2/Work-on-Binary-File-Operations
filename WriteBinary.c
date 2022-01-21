#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
    fseek(filePtr, 0, SEEK_SET);
    while(!feof(filePtr)){
        printf("\n%-3s %-20s %-20s %-20s %s\n",
           "ID",
           "Name",
           "Surname",
           "Department",
           "Grade");

    printf("%-3d %-20s %-20s %-20s %d\n",
           student.id,
           student.name,
           student.surname,
           student.department,
           student.grade);


    }
}
int main() {
FILE *filePtr =fopen("exam.bin","wb+");
writeBinary(filePtr);
return 0;
}
