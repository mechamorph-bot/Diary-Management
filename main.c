#include <stdio.h>

void encrypt() //Function to encrypt the diary entry before saving to the file
{
    
}


int isValidDate(int y, int m, int d) //Function to validate date input
{
    if (m < 1 || m > 12 || d < 1 || d > 31 ||
        (m == 2 && d > 28) || // needs leap year handling in the future
        ((m == 4 || m == 6 || m == 9 || m == 11) && d > 30)) {
        return 0; // invalid date
    }
    return 1; // valid date
}


void addEntry() //Function to add a new diary entry with date and content
{
   
    // Need to declare a structure to store diary entry (date + content)
    // Need a way to store and manage multiple entries (array, file)
    
    int y, m, d;
    
    do {
        printf("Enter date (YYYY-MM-DD): ");
        if (scanf("%d-%d-%d", &y, &m, &d) != 3 || !isValidDate(y, m, d)) 
        {
            printf("Invalid date! Try again.\n");
        } 
        else 
        {
            // Need string to store formatted date
            break; // exit loop on valid date
        }
    } while (1); // loop will run forever unless explicitly broken
    
    printf("Enter diary entry: ");
    // Need string to store the diary content

    // Need file to store the entry permanently 
    printf("Entry added successfully!\n");

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
            case 1: addEntry(); 
                break;
            case 2: viewEntry(); 
                break;
            case 3: searchEntry(); 
                break;
            case 4: editEntry(); 
                break;
            case 5: deleteEntry(); 
                break;
            case 6: printf("Exiting...\n"); 
                break;
            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);
    return 0;
}
