#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "addressbook.txt"

struct Address {
    char name[50];
    char phone[15];
    char email[50];
};

// Function declarations
void createAddressBook();
void viewAddressBook();
void insertRecord();
void deleteRecord();
void modifyRecord();

int main() {
    int choice;

    while (1) {
        printf("\n===== ADDRESS BOOK MENU =====\n");
        printf("1. Create Address Book\n");
        printf("2. View Address Book\n");
        printf("3. Insert a Record\n");
        printf("4. Delete a Record\n");
        printf("5. Modify a Record\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAddressBook(); break;
            case 2: viewAddressBook(); break;
            case 3: insertRecord(); break;
            case 4: deleteRecord(); break;
            case 5: modifyRecord(); break;
            case 6: exit(0);
            default: printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}

void createAddressBook() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        printf("Error creating address book.\n");
        return;
    }
    printf("Address Book created successfully.\n");
    fclose(fp);
}

void viewAddressBook() {
    struct Address addr;
    FILE *fp = fopen(FILENAME, "r");

    if (fp == NULL) {
        printf("No address book found. Create it first.\n");
        return;
    }

    printf("\n----- ADDRESS BOOK CONTENT -----\n");

    while (fread(&addr, sizeof(addr), 1, fp)) {
        printf("Name : %s\n", addr.name);
        printf("Phone: %s\n", addr.phone);
        printf("Email: %s\n\n", addr.email);
    }
    fclose(fp);
}

void insertRecord() {
    FILE *fp = fopen(FILENAME, "a");
    struct Address addr;

    if (fp == NULL) {
        printf("No address book found. Create it first.\n");
        return;
    }

    printf("Enter Name  : ");
    scanf("%s", addr.name);
    printf("Enter Phone : ");
    scanf("%s", addr.phone);
    printf("Enter Email : ");
    scanf("%s", addr.email);

    fwrite(&addr, sizeof(addr), 1, fp);
    fclose(fp);
    printf("Record inserted successfully.\n");
}

void deleteRecord() {
    struct Address addr;
    char name[50];
    int found = 0;

    FILE *fp = fopen(FILENAME, "r");
    FILE *temp = fopen("temp.txt", "w");

    if (fp == NULL) {
        printf("No address book found.\n");
        return;
    }

    printf("Enter name to delete: ");
    scanf("%s", name);

    while (fread(&addr, sizeof(addr), 1, fp)) {
        if (strcmp(addr.name, name) != 0) {
            fwrite(&addr, sizeof(addr), 1, temp);
        } else {
            found = 1;
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILENAME);
    rename("temp.txt", FILENAME);

    if (found)
        printf("Record deleted successfully.\n");
    else
        printf("Record not found.\n");
}

void modifyRecord() {
    struct Address addr;
    char name[50];
    int found = 0;

    FILE *fp = fopen(FILENAME, "r+");

    if (fp == NULL) {
        printf("No address book found.\n");
        return;
    }

    printf("Enter name to modify: ");
    scanf("%s", name);

    while (fread(&addr, sizeof(addr), 1, fp)) {
        if (strcmp(addr.name, name) == 0) {
            printf("Enter new Name  : ");
            scanf("%s", addr.name);
            printf("Enter new Phone : ");
            scanf("%s", addr.phone);
            printf("Enter new Email : ");
            scanf("%s", addr.email);

            fseek(fp, -sizeof(addr), SEEK_CUR);
            fwrite(&addr, sizeof(addr), 1, fp);
            found = 1;
            printf("Record modified successfully.\n");
            break;
        }
    }

    if (!found)
        printf("Record not found.\n");

    fclose(fp);
}
