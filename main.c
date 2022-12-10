#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.c"

// Attention! For save, load, and deleteStudent functions, I got some help from the Stackoverflow.com

int main(int argc, char** argv) {
    
    student st;
    int option = 0;     //Used for the menu's options
    char wish = 'a';    //Used if the user wishes to exits before the appearance of the menu, to save space

    //We want 2 arguments. './main' and 'students.txt'
    if (argc != 2) {
        printf("ERROR - PLEASE GIVE TWO ARGUMENTS\n");
        return 0;
    }

    //Here we load the student list from the file,if there is one
    list l = load(argv[1]);  

    //The menu
    while (option != 6) {

        printf("\n**************HAROKOPIO UNIVERSITY STUDENT LIST**************\n");

        printMenu();

        scanf("%d", &option);

        switch(option) {
            case 1: 
                printf("\nPlease give the name and the ID of the student, you want to add:  ");
                scanf("%s%d", st.name, &st.id);
                addStudent(st, l);
                break;
            case 2:
                printf("\nPlease give the id of the student you want to delete:  ");
                scanf("%d", &st.id);
                deleteStudent(st, l);
                break;
            case 3:
                printf("\nPlease give the id of the student you want to find:  ");
                scanf("%d", &st.id);
                student* currentStudent = findStudent(st.id, l);
                print(*currentStudent);
                break;
            case 4:
                printf("\nPlease give the student's id, whose name you want to be changed:  ");
                scanf("%d", &st.id);
                updateStudent(st, l);
                break;
            case 5:
                printstudents(l);
                break;
            case 6:
                save(argv[1], l);
                printf("Student List has been saved!\n\n");
                printf("\nExiting...\n");
                return 0;
            default:
                printf("\nThat number doesn't represent a valid option!\n");
                break;
        }
        printf("\nDo you wish to continue? (y/n)\n");
        
        scanf(" %c", &wish);
        
        if (wish == 'y') {
            option = 1;
        } else {
            option = 6;
            save(argv[1], l);
            printf("Student List has been saved!\n\n");
            printf("Exiting...\tBye bye\n\n");
        }
    }    
    return 0;
}