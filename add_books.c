#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "books.txt"

struct Book {
    int bookId;
    char title[50];
    char author[50];
    char publisher[50];
    char category[30];
    int totalCopies;
    int availableCopies;
    int issuedCopies;
};

/* Function declarations */
void addBook();
void displayBooks();
void searchBook();
void updateBook();
void deleteBook();
void menu();

/* Main function */
int main() {
    menu();
    return 0;
}

/* Menu */
void menu() {
    int choice;
    do {
        printf("\n===== BOOKS MODULE =====\n");
        printf("1. Add Book\n");
        printf("2. Display All Books\n");
        printf("3. Search Book\n");
        printf("4. Update Book\n");
        printf("5. Delete Book\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addBook(); break;
            case 2: displayBooks(); break;
            case 3: searchBook(); break;
            case 4: updateBook(); break;
            case 5: deleteBook(); break;
            case 0: printf("Exiting program...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 0);
}

/* 1. Add Book */
void addBook() {
    FILE *fp = fopen(FILE_NAME, "a");
    struct Book b;

    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("\nEnter Book ID: ");
    scanf("%d", &b.bookId);
    getchar();

    printf("Enter Title: ");
    fgets(b.title, 50, stdin);
    strtok(b.title, "\n");

    printf("Enter Author: ");
    fgets(b.author, 50, stdin);
    strtok(b.author, "\n");

    printf("Enter Publisher: ");
    fgets(b.publisher, 50, stdin);
    strtok(b.publisher, "\n");

    printf("Enter Category: ");
    fgets(b.category, 30, stdin);
    strtok(b.category, "\n");

    printf("Enter Total Copies: ");
    scanf("%d", &b.totalCopies);

    b.availableCopies = b.totalCopies;
    b.issuedCopies = 0;

    fprintf(fp, "%d|%s|%s|%s|%s|%d|%d|%d\n",
            b.bookId, b.title, b.author, b.publisher,
            b.category, b.totalCopies,
            b.availableCopies, b.issuedCopies);

    fclose(fp);
    printf("Book added successfully!\n");
}

/* 2. Display All Books */
void displayBooks() {
    FILE *fp = fopen(FILE_NAME, "r");
    struct Book b;

    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n----- BOOK LIST -----\n");
    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%49[^|]|%29[^|]|%d|%d|%d\n",
                  &b.bookId, b.title, b.author, b.publisher,
                  b.category, &b.totalCopies,
                  &b.availableCopies, &b.issuedCopies) != EOF) {

        printf("ID: %d | Title: %s | Author: %s | Available: %d\n",
               b.bookId, b.title, b.author, b.availableCopies);
    }

    fclose(fp);
}

/* 3. Search Book */
void searchBook() {
    FILE *fp = fopen(FILE_NAME, "r");
    struct Book b;
    int id, found = 0;

    if (fp == NULL) {
        printf("File not found!\n");
        return;
    }

    printf("Enter Book ID to search: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%49[^|]|%29[^|]|%d|%d|%d\n",
                  &b.bookId, b.title, b.author, b.publisher,
                  b.category, &b.totalCopies,
                  &b.availableCopies, &b.issuedCopies) != EOF) {

        if (b.bookId == id) {
            printf("\nBook Found:\n");
            printf("ID: %d\nTitle: %s\nAuthor: %s\nPublisher: %s\nCategory: %s\n",
                   b.bookId, b.title, b.author, b.publisher, b.category);
            printf("Total Copies: %d\nAvailable Copies: %d\n",
                   b.totalCopies, b.availableCopies);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("Book not found!\n");

    fclose(fp);
}

/* 4. Update Book */
void updateBook() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to update: ");
    scanf("%d", &id);
    getchar();

    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%49[^|]|%29[^|]|%d|%d|%d\n",
                  &b.bookId, b.title, b.author, b.publisher,
                  b.category, &b.totalCopies,
                  &b.availableCopies, &b.issuedCopies) != EOF) {

        if (b.bookId == id) {
            printf("Enter New Title: ");
            fgets(b.title, 50, stdin);
            strtok(b.title, "\n");

            printf("Enter New Author: ");
            fgets(b.author, 50, stdin);
            strtok(b.author, "\n");

            found = 1;
        }

        fprintf(temp, "%d|%s|%s|%s|%s|%d|%d|%d\n",
                b.bookId, b.title, b.author, b.publisher,
                b.category, b.totalCopies,
                b.availableCopies, b.issuedCopies);
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Book updated successfully!\n");
    else
        printf("Book not found!\n");
}

/* 5. Delete Book */
void deleteBook() {
    FILE *fp = fopen(FILE_NAME, "r");
    FILE *temp = fopen("temp.txt", "w");
    struct Book b;
    int id, found = 0;

    printf("Enter Book ID to delete: ");
    scanf("%d", &id);

    while (fscanf(fp, "%d|%49[^|]|%49[^|]|%49[^|]|%29[^|]|%d|%d|%d\n",
                  &b.bookId, b.title, b.author, b.publisher,
                  b.category, &b.totalCopies,
                  &b.availableCopies, &b.issuedCopies) != EOF) {

        if (b.bookId != id) {
            fprintf(temp, "%d|%s|%s|%s|%s|%d|%d|%d\n",
                    b.bookId, b.title, b.author, b.publisher,
                    b.category, b.totalCopies,
                    b.availableCopies, b.issuedCopies);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.txt", FILE_NAME);

    if (found)
        printf("Book deleted successfully!\n");
    else
        printf("Book not found!\n");
}
