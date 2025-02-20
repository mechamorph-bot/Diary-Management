#include <stdio.h>

void encrypt() //Function to encrypt the diary entry before saving to the file
{
    
}

void addEntry() //Function to add a new diary entry with date and content
{
    
}

void viewEntry() //Function to display all diary entries in chronological order
{

}

void searchEntry() //Function to search for a diary entry by date
{

}

void editEntry() //Function to edit an existing diary entry by date
{

}



void deleteEntry() //Function to delete a diary entry by date
{

}

int authenticate() //Function to verify the user's password before accessing the diary
{

}


int main() {
    if (!authenticate()) {
        return 0;
    }
    
    int choice;
    do {
        printf("\nPersonal Diary Management System\n");
        printf("1. Add Entry\n");
        printf("2. View Entries\n");
        printf("3. Search Entry\n");
        printf("4. Edit Entry\n");
        printf("5. Delete Entry\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        
        
        switch (choice) {
            case 1: addEntry(); break;
            case 2: viewEntry(); break;
            case 3: searchEntry(); break;
            case 4: editEntry(); break;
            case 5: deleteEntry(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);
    return 0;
}
