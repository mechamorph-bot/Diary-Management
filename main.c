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
       } 
    while (1); // loop will run forever unless explicitly broken

    printf("Enter diary entry: ");
    // Need string to store the diary content

   // If an entry with the same date already exists, it will display a message and prevent the new entry from being added.

    // Need file to store the entry permanently
    printf("Entry added successfully!\n");

}


void viewEntry() //Function to display all diary entries in chronological order
{ 
    // Need to check if there are any saved entries
    // Need a way to read multiple entries
    
    // Loop through all saved entries
    // For each entry:
        // Display the date and content
    
    // If no entries are found:
    printf("No entries found.\n");

}


void searchEntry() //Function to search for a diary entry by date
{ 
    int y,m,d;


    do {
        printf("Enter date (YYYY-MM-DD): ");
        if (scanf("%d-%d-%d", &y, &m, &d) != 3 || !isValidDate(y, m, d))
        {
            printf("Invalid date! Try again.\n");
        }
        else
        {
            // Need to check if an entry with this date exists
            // If found, display the entry content
            break; // exit loop on valid date and entry
        }
       } 
   while (1); // loop will run forever unless explicitly broken

    // If no entry is found with the entered date:
    printf("No entry found for the given date.\n");

}
 
   

void editEntry() //Function to edit an existing diary entry by date
{

// Function to edit an entry
    int y, m, d;

    int found = 0;

    do {
        printf("Enter date (YYYY-MM-DD): ");
        if (scanf("%d-%d-%d", &y, &m, &d) != 3 || !isValidDate(y, m, d)) {
            printf("Invalid date! Try again.\n");
        } else {

            break;
        }
    } while (1);
    
    if (//if file found)
        {
            found = 1;
        printf("Old Entry: %s\n", entry);
        printf("Enter new entry: ");
            }



}



void deleteEntry() //Function to delete a diary entry by date
{
    int y,m,d;


    do {
        printf("Enter date of the entry to delete (YYYY-MM-DD): ");
        if (scanf("%d-%d-%d", &y, &m, &d) != 3 || !isValidDate(y, m, d))
        {
            printf("Invalid date! Try again.\n");
        }
        else
        {
            // Need to check if an entry with this date exists
            // If found, delete the entry
            break; // exit loop if valid date and entry is found
        }
      } 
    while (1); // loop until a valid date is entered

    // If no entry is found with the entered date:
    printf("No entry found for the given date.\n");

    // If entry is found:
    printf("Entry deleted successfully!\n");

}

int authenticate() //Function to verify the user's password before accessing the diary
{
    int x; //setting a variable to take input of pin
    printf("Enter The PIN:");    //prompt to enter pin
     scanf("%d",&x);    //receiving pin
      if(x==1212) //checking if pin x=1212
      {  
       printf("You have logged in successfully\n");
       return 1; //returns true
      }
      else 
      {
        printf("You Have Entered a Wrong PIN");  //giving prompt if the pin is mismatched
        return 0; //returns false
      }

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
