#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "student.h"

//Creates list  by reserving memory and returns a pointer to a list
list createList() {
    list l = (list) malloc(sizeof(struct listR));
    if (l == NULL) {
        printf("Error allocating memory!\n");
        return NULL;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    return l;
}


int fileExists(char* filename) {
    FILE* file = fopen(filename, "r");
    if (file != NULL) {
        fclose(file);
        return 1;
    }
    return 0;
}

void printMenu() {
    printf("\n\n");
    printf("Please select one of the following options by entering the number (1 to 6):\n\n");
    printf("1. Add a new student\n2. Remove an existing student\n");
    printf("3. Search for a student\n4. Update a student's info\n");
    printf("5. Print the student list\n6. Exit\n\nYour option: ");
}

void print(student st) {
    printf("\nYou searched for %s with ID %d\n\n", st.name, st.id);
}


void printstudents(list l) {
    printf("\n\nID\t\tNAME\n");
    node currentNode = l->head;
    
    while(currentNode != NULL) {
        printf("%d\t\t%s\n",currentNode->data.id, currentNode->data.name);
        currentNode = currentNode->next;
    }
}

list load(char *filename) {
    list l = createList();

    if (fileExists(filename) == 1) {
        FILE* fd = fopen(filename, "r");
        if (fd == NULL) {
            printf("ERROR - FILE COULD NOT BE OPENED FOR DATA LOADING\n");
            abort();
        }
        fseek(fd, 0, SEEK_END);
        long fileSize = ftell(fd);
        fseek(fd, 0, SEEK_SET);

        (int)fileSize;
        if(fileSize != 0) {
            int i = 0;
            while (feof(fd) == 0) {
                node n = (node) malloc(sizeof(struct nodeR));
                fscanf(fd, "%d\t\t%s\n", &n->data.id, n->data.name);
                n->next = NULL;
                if(l->size == 0) {
                    n->previous = NULL;
                    l->head = n;
                    l->tail = n;
                    (l->size)++;
                } else {
                    node previousLast = l->tail;
                    n->previous = previousLast;
                    previousLast->next = n;
                    l->tail = n;
                    (l->size)++;
                }
            }
        }
        fclose(fd);
    } else {
        FILE* fd = fopen(filename, "w");
        if (fd == NULL) {
            printf("ERROR OPENING THE FILE!\n");
            abort();
        }
        fclose(fd);
    }
    return l;
}

void save(char *filename, list l) {
    node currentNode = l->head;

    FILE* fd = fopen(filename, "w");
    if (fd == NULL) {
        printf("ERROR - FILE COULD NOT BE OPENED FOR DATA SAVING!\n");
        abort();
    }
    while (currentNode != NULL) {
        fprintf(fd, "%d\t\t%s\n",currentNode->data.id, currentNode->data.name);
        currentNode = currentNode->next;
    }
    fclose(fd);
}

int addStudent(student st, list l) {

    node n = (node)malloc(sizeof(struct nodeR));
    
    if (n == NULL) {
        printf("Error allocating memory!\n");
        return -1;
    }   
    n->data = st;
    n->next = NULL;  
    if((l->size) != 0) {
        node currentLast = l->tail;
        currentLast->next = n;
        n->previous = currentLast;
        l->tail = n;
    } else {
        n->previous = NULL;
        l->head = n;
        l->tail = n;
    }
    (l->size)++;
    printf("New student has been registered. ID: %d, Name: %s\n", st.id, st.name);
}

student* findStudent(int id, list l) {
    
    node currentNode = l->head;
    
    while (currentNode != NULL) {
        if (currentNode->data.id == id) {
            printf("\nStudent has been found!\n\n");
            return &(currentNode->data);
        }
        currentNode = currentNode->next;
    }
    return NULL;
}

int deleteStudent(student st, list l) {
    
    node temp = NULL;
    
    if (l->head == NULL) {
        printf("Empty list\n");
    }
    if (l->head->data.id == st.id) {
        temp = l->head;
        l->head = l->head->next;
        if (l->head != NULL) {
            l->head->previous = NULL;
        } else {
            l->tail = NULL;
        }
        printf("\nStudent named %s with ID %d has been deleted!\n", temp->data.name, st.id);
        free(temp);
        printf("<Student List Renewed>");
        printstudents(l);
    } else if (l->tail->data.id == st.id) {
        temp = l->tail;
        l->tail = l->tail->previous;
        if (l->tail != NULL) {
            l->tail->next = NULL;
        } else {
            l->head = NULL;
        }
        printf("\nStudent named %s with ID %d has been deleted!\n", temp->data.name, st.id);
        free(temp);
        printf("<Student List Renewed>");
        printstudents(l);
    } else {
        temp = l->head;
        while (temp != NULL && temp->data.id != st.id) {
            temp = temp->next;
        }
        if (temp == NULL) {
            printf("\nThe student doesn't exist\n");
        } else {
            temp->previous->next = temp->next;
            if (temp->next != NULL) {
                temp->next->previous = temp->previous;
            }
            printf("\nStudent named %s with ID %d has been deleted!\n", temp->data.name, st.id);
            free(temp);
            printf("<Student List Renewed>");
            printstudents(l);
        }
    }
}

int updateStudent(student st, list l) {
    student* currentStudent = findStudent(st.id, l);
    if (currentStudent != NULL) {
        printf("Please give the new name, for id '%d' :\n", st.id);
        scanf("%s", currentStudent->name);
        printf("Student has been updated\nNew info:");
        printf("\n%d\t\t%s\n\n",st.id, currentStudent->name);
        printf("<Student List Renewed>");
        printstudents(l);
        return 0;
    } else {
        printf("Student doesn't exist\n");
        return 0;
    }
}
