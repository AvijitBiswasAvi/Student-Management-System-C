#include <stdio.h>
#include <string.h>



typedef struct studentinformation
{
    int id;
    char name[50];
    int age;
    float gpa;
} Student;

int main()
{
    Student info[100];
    
    int starting_choice;

    printf("\n");
    printf("|=========================|\n");
    printf("|          MENU           |\n");
    printf("|-------------------------|\n");
    printf("| 1. Add                  |\n");
    printf("| 2. Display              |\n");
    printf("| 3. Search               |\n");
    printf("| 4. Update               |\n");
    printf("| 5. Delete               |\n");
    printf("| 6. Exit                 |\n");
    printf("|=========================|\n");
    printf("\n");

    printf("Enter your choice = ");
    scanf("%d", &starting_choice);
    printf("\n");

    switch (starting_choice)
    {
    case 1:
        
        break;
    
    default:
        break;
    }
    return 0;
}