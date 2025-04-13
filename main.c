#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "diaryy.txt"
#define MAX_ENTRIES 100
#define ENCRYPTION_KEY 'K' // XOR key




typedef struct           // global structure for diary entries
{
    char   date[20];
    char   title[50];
    char   content[1000];

} DiaryEntry;

DiaryEntry entries[MAX_ENTRIES];
int entryCount = 0;


int authenticate();
void xorEncryptDecrypt(char *text);
int isValidDate(int y, int m, int d);
int isLeapYear(int y);
void addEntry();
void saveEntries();
void loadEntries();
//void searchEntry();
//void editEntry();
//void deleteEntry();


int main()
{
    if (!authenticate())
    {
        return 0;
    }

    int choice;

    loadEntries(); //loads previously saved diary entries from the file into memory

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


        switch (choice)
        {
            case 1: addEntry();             break;

            // case 2: viewEntry();            break;

            //case 3: searchEntry();          break;

            //case 4: editEntry();            break;

            case 5: deleteEntry();          break;

            case 6: printf("Exiting...\n"); break;

            default: printf("Invalid choice!\n");
        }
    } while (choice != 6);
    return 0;
}




void xorEncryptDecrypt(char *text)           // XOR encryption/decryption
{
    for (int i = 0; text[i]; i++)
    {
        text[i] ^= ENCRYPTION_KEY;
    }
}




// Date validation
int isValidDate(int y, int m, int d)
{


    if (m < 1 || m > 12 || d < 1)                        // validates month and day
        return 0;


    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};     // array containing days in each month, index 0 is January, index 11 is December


    if (isLeapYear(y))             // checks for leap year and adjust February's days
        daysInMonth[1] = 29;


    if (d > daysInMonth[m - 1])      // checks if day is valid for the given month
        return 0;

    return 1;  // valid date
}






// Leap year check
int isLeapYear(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}



//adds a new entry
void addEntry()
{
    if (entryCount >= MAX_ENTRIES)
    {
        printf("Diary is full.\n");
        return;
    }

    getchar(); // clear buffer
    printf("Enter date (YYYY-MM-DD): ");
    fgets(entries[entryCount].date, sizeof(entries[entryCount].date), stdin);

    entries[entryCount].date[strcspn(entries[entryCount].date, "\n")] = 0;     //removes newline character at the end if present


    int y, m, d;            // parsing the date into year, month, and day


    if (sscanf(entries[entryCount].date, "%4d-%2d-%2d", &y, &m, &d) != 3)   //parsing the input date string into integers, checks date format
    {
        printf("Invalid date format. Please use the format YYYY-MM-DD.\n");
        return;
    }


    if (!isValidDate(y, m, d))               // using isValidDate to validate the entire date
    {
        printf("Invalid date. Please enter a valid date (format: year, month, and day).\n");
        return;
    }

    printf("Enter title: ");
    fgets(entries[entryCount].title, sizeof(entries[entryCount].title), stdin);
    entries[entryCount].title[strcspn(entries[entryCount].title, "\n")] = 0;

    printf("Enter content: ");
    fgets(entries[entryCount].content, sizeof(entries[entryCount].content), stdin);
    entries[entryCount].content[strcspn(entries[entryCount].content, "\n")] = 0;

    entryCount++;             //increases the entry count = new addition
    saveEntries();            //saves all entries including the new one
    printf("Entry added successfully.\n");
}






void saveEntries()           // saves/updates entries
{
    FILE *fp = fopen(FILENAME, "wb"); //opens the file in write mode
    if (!fp)
    {
        printf("Error saving entries.\n");
        return;
    }


    for (int i = 0; i < entryCount; i++)           //loops through all existing entries
    {

        xorEncryptDecrypt(entries[i].date);        //encrypts each field of the diary entry before saving
        xorEncryptDecrypt(entries[i].title);
        xorEncryptDecrypt(entries[i].content);


        fwrite(&entries[i], sizeof(DiaryEntry), 1, fp);   //writes the encrypted diary entry to the file


        xorEncryptDecrypt(entries[i].date);           //decrypts again to keep them readable
        xorEncryptDecrypt(entries[i].title);
        xorEncryptDecrypt(entries[i].content);
    }
    fclose(fp);
}





void loadEntries()                         // loads entries
{
    FILE *fp = fopen(FILENAME, "rb");      //opening the file in binary read mode
    if (!fp) return;
    entryCount = 0;                       //initializing the entry count to 0
    while (fread(&entries[entryCount], sizeof(DiaryEntry), 1, fp) == 1 && entryCount < MAX_ENTRIES) //reads entries from file one by one
    {

        xorEncryptDecrypt(entries[entryCount].date);     //decrypts entry fields
        xorEncryptDecrypt(entries[entryCount].title);
        xorEncryptDecrypt(entries[entryCount].content);
        entryCount++;                                    //moves to next entry slot
    }
    fclose(fp);           //closing after reading
}






// ------------------- View Entries -------------------

void viewEntries() {
    FILE *file = fopen("diaryy.txt", "r");
    if (!file) {
        printf("No entries found.\n");
        return;
    }

    DiaryEntry entry;
    printf("\n--- All Diary Entries ---\n");
    while (fscanf(file, "%d %d %d\n", &entry.year, &entry.month, &entry.date) == 3) {
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

    FILE *file = fopen("diary.txt", "r");
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




/*void editEntry() //Function to edit an existing diary entry by date
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



