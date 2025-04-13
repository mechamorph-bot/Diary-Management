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


// ------------------- View Entries -------------------

void viewEntries() {
    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No entries found.\n");
        return;
    }

    DiaryEntry entry;
    printf("\n--- All Diary Entries ---\n");
    while (fscanf(file, "%d %d %d\n", &entry.year, &entry.month, &entry.day) == 3) {
        fgets(entry.content, MAX_CONTENT, file);
        decrypt(entry.content);
        printf("Date: %04d-%02d-%02d\n", entry.year, entry.month, entry.day);
        printf("Content: %s\n", entry.content);
    }
    fclose(file);
}

//  Search Entry

void searchEntry() {
    int y, m, d;
    printf("Enter date to search (YYYY-MM-DD): ");
    scanf("%d-%d-%d", &y, &m, &d);

    if (!isValidDate(y, m, d)) {
        printf("Invalid date.\n");
        return;
    }

    FILE *file = fopen(FILE_NAME, "r");
    if (!file) {
        printf("No entries found.\n");
        return;
    }

    DiaryEntry entry;
    int found = 0;
    while (fscanf(file, "%d %d %d\n", &entry.year, &entry.month, &entry.day) == 3) {
        fgets(entry.content, MAX_CONTENT, file);
        if (entry.year == y && entry.month == m && entry.day == d) {
            decrypt(entry.content);
            printf("Entry found:\n%s\n", entry.content);
            found = 1;
            break;
        }
    }

    fclose(file);
    if (!found) {
        printf("No entry found for this date.\n");
    }
}




void editEntry() //Function to edit an existing diary entry by date
{
    int y, m, d;

    int found = 0;

    do {
        printf("Enter date (YYYY-MM-DD): ");
        if (scanf("%d-%d-%d", &y, &m, &d) != 3 || !isValidDate(y, m, d))
        {
            printf("Invalid date! Try again.\n");
        }
        else
        {
            //If valid then it will print the content

            break;
        }
    }
    while (1);

    if (found)
        {
            found = 1;
        printf("Current Entry: %s\n");
        printf("Enter new content: ");
        }
    else{

    // If no entry is found with the entered date:
    printf("No entry found for the given date.\n");
    }


    int y, m, d;

    int found = 0;

    do {
        printf("Enter date (YYYY-MM-DD): ");
        if (scanf("%d-%d-%d", &y, &m, &d) != 3 || !isValidDate(y, m, d))
        {
            printf("Invalid date! Try again.\n");
        }
        else
        {
            //If valid then it will print the content

            break;
        }
      }
        while (1);

    if (//if file found)
        {
            found = 1;
        printf("Current Entry: %s\n", entry);
        printf("Enter new content: ");
        }
    else{

    // If no entry is found with the entered date:
    printf("No entry found for the given date.\n");
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
