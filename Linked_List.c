#include<stdio.h>
#include<stdlib.h>
#include<string.h>

// Structure to store student information
struct student {
    char usn[11];
    char name[50];
    char branch[50];
    int semester;
    char phone[15];
    struct student *next;
};

// Function to create a new student node
struct student *create_node(char usn[], char name[], char branch[], int semester, char phone[]) {
    struct student *new_node = (struct student *)malloc(sizeof(struct student));
    strcpy(new_node->usn, usn);
    strcpy(new_node->name, name);
    strcpy(new_node->branch, branch);
    new_node->semester = semester;
    strcpy(new_node->phone, phone);
    new_node->next = NULL;
    return new_node;
}

// Function to insert a new node at the end of the list
struct student *insert_at_end(struct student *head, char usn[], char name[], char branch[], int semester, char phone[]) {
    struct student *new_node = create_node(usn, name, branch, semester, phone);
    if (head == NULL) {
        return new_node;
    }
    struct student *current = head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
    return head;
}

// Function to display the linked list
void display(struct student *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct student *current = head;
    printf("USN\t\tName\t\tBranch\t\tSemester\t\tPhone\n");
    while (current != NULL) {
        printf("%s\t%s\t\t%s\t\t%d\t\t\t%s\n", current->usn, current->name, current->branch, current->semester, current->phone);
        current = current->next;
    }
}

// Function to delete the first node of the list
struct student *delete_at_beginning(struct student *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    struct student *temp = head;
    head = head->next;
    free(temp);
    return head;
}

// Function to delete the last node of the list
struct student *delete_at_end(struct student *head) {
    if (head == NULL) {
        printf("List is empty\n");
        return NULL;
    }
    if (head->next == NULL) {
        free(head);
        return NULL;
    }
    struct student *current = head;
    while (current->next->next != NULL) {
        current = current->next;
    }
    free(current->next);
    current->next = NULL;
    return head;
}

// Function to demonstrate the linked list as a queue
void queue_demo() {
struct student *head = NULL;
printf("Queue demonstration using linked list\n");
head = insert_at_end(head, "1BM18CS001", "Alice", "CSE", 5, "1234567890");
head = insert_at_end(head, "1BM18CS002", "Bob", "CSE", 5, "2345678901");
head = insert_at_end(head, "1BM18CS003", "Charlie", "CSE", 5, "3456789012");
display(head);
printf("Deleting the first student from the queue\n");
head = delete_at_beginning(head);
display(head);
printf("Inserting a new student at the end of the queue\n");
head = insert_at_end(head, "1BM18CS004", "David", "CSE", 5, "4567890123");
display(head);
}

int main() {
struct student *head = NULL;
int choice;
char usn[11], name[50], branch[50], phone[15];
int semester;
while (1) {
printf("Linked List Operations:\n");
printf("1. Create\n");
printf("2. Display\n");
printf("3. Insert\n");
printf("4. Delete\n");
printf("5. Queue Demo\n");
printf("6. Exit\n");
printf("Enter your choice: ");
scanf("%d", &choice);
switch(choice) {
case 1:
printf("Enter the details of the first student:\n");
printf("USN: ");
scanf("%s", usn);
printf("Name: ");
scanf(" %[^\n]s", name);
printf("Branch: ");
scanf(" %[^\n]s", branch);
printf("Semester: ");
scanf("%d", &semester);
printf("Phone: ");
scanf("%s", phone);
head = create_node(usn, name, branch, semester, phone);
printf("First student created successfully!\n");
break;
case 2:
printf("Displaying the list of students:\n");
display(head);
break;
case 3:
printf("Enter the details of the student to be inserted:\n");
printf("USN: ");
scanf("%s", usn);
printf("Name: ");
scanf(" %[^\n]s", name);
printf("Branch: ");
scanf(" %[^\n]s", branch);
printf("Semester: ");
scanf("%d", &semester);
printf("Phone: ");
scanf("%s", phone);
head = insert_at_end(head, usn, name, branch, semester, phone);
printf("Student inserted successfully!\n");
break;
case 4:
printf("Deleting a student from the list:\n");
printf("1. Delete from beginning\n");
printf("2. Delete from end\n");
printf("Enter your choice: ");
int del_choice;
scanf("%d", &del_choice);
if (del_choice == 1) {
head = delete_at_beginning(head);
} else if (del_choice == 2) {
head = delete_at_end(head);
} else {
printf("Invalid choice\n");
}
break;
case 5:
queue_demo();
break;
case 6:
printf("Exiting the program...\n");
exit(0);
default:
printf("Invalid choice\n");
}
}
return 0;
}
