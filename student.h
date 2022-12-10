#ifndef STUDENT_H
#define STUDENT_H

#define MAXSTRING 30

// Attention! For save, load, and deleteStudent functions, I got some help from the Stackoverflow.com

typedef struct {  //     <======================      It creates a student struct, that has a name and an id, and it names it 'student' (typedef)
    char name[MAXSTRING];
    int id;
}student;

typedef struct nodeR* node;  //     <===========      It creates a pointer to a node, and it names it 'node' (typedef)
typedef struct listR* list;  //     <===========      It creates a pointer to a list, and it names it 'list' (typedef)

struct nodeR{  //   <===========================      It creates a node struct that has the student data, a 'next' pointer to the next node, and a 'previous' pointer to the previous node
    student data;
    node next;
    node previous;
};

struct listR {  //  <===========================      It creates a list struct that has a 'head' pointer to the first node, and a 'tail' pointer to the last node
    node head;
    node tail;
    int size;
};

void printMenu();  //   <=======================      It prints the menu on user's screen

void print(student st);  //     <===============      It prints the student's info, for the chosen student

void printstudents(list l);  //     <===========      It prints the student list

list load(char *filename);  //      <===========      It loads the student list from the "student.txt" file

void save(char *filename, list l);  //  <=======      It saves the student list in "students.txt" file

int addStudent(student st, list l);  //    <====      It adds a new student if the student doesn't exist, or else it prints a message that the student exists

student* findStudent(int id, list l);  //   <===      It returns a pointer that points to the desirable student, according to the id

int deleteStudent(student st, list l);  //  <===      It deletes a student, if the students exists, or else it prints a message that the student doesn't exist

int updateStudent(student st, list l);  //  <===      It updates a student's name, according to the given id (in findStudent function), or else it prints that the student doesn't exist

list createList();  //   <======================      It creates a list, if there isn't one

int fileExists(char *filename);  //     <=======      It checks if the file exists or not. Returns 1 if it does, or else returns 0

#endif