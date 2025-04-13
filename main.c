#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "diaryy.txt"
#define MAX_ENTRIES 100
#define ENCRYPTION_KEY 'K' // XOR key

// global structure for diary entries
typedef struct
{
    char date[20];
    char title[50];
    char content[1000];
} DiaryEntry;

DiaryEntry entries[MAX_ENTRIES];
int entryCount = 0;

// Function to authenticate the user with a PIN
int authenticate()
{
    int x;
    printf("Enter The PIN: ");
    scanf("%d", &x);
    if (x == 1212)
    {
        printf("You have logged in successfully\n");
        return 1;
    }
    else
    {
        printf("You Have Entered a Wrong PIN\n");
        return 0;
    }
}

// XOR encryption/decryption (if you decide to add encryption later)
void xorEncryptDecrypt(char *text)
{
    for (int i = 0; text[i]; i++)
    {
        text[i] ^= ENCRYPTION_KEY;
    }
}

// Leap year check
int isLeapYear(int y)
{
    return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0);
}

// Date validation
int isValidDate(int y, int m, int d)
{
    if (m < 1 || m > 12 || d < 1)
        return 0;

    int daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    if (isLeapYear(y))
        daysInMonth[1] = 29;

    if (d > daysInMonth[m - 1])
        return 0;

    return 1;
}

// Function to load entries from the file
void loadEntries()
{
    FILE *fp = fopen(FILENAME, "rb");
    if (!fp)
        return;
    entryCount = 0;
    while (fread(&entries[entryCount], sizeof(DiaryEntry), 1, fp) == 1 && entryCount < MAX_ENTRIES)
    {
        xorEncryptDecrypt(entries[entryCount].date);
        xorEncryptDecrypt(entries[entryCount].title);
        xorEncryptDecrypt(entries[entryCount].content);
        entryCount++;
    }
    fclose(fp);
}

// Function to save entries to the file
void saveEntries()
{
    FILE *fp = fopen(FILENAME, "wb");
    if (!fp)
    {
        printf("Error saving entries.\n");
        return;
    }

    for (int i = 0; i < entryCount; i++)
    {
        xorEncryptDecrypt(entries[i].date);
        xorEncryptDecrypt(entries[i].title);
        xorEncryptDecrypt(entries[i].content);
        fwrite(&entries[i], sizeof(DiaryEntry), 1, fp);
        xorEncryptDecrypt(entries[i].date);
        xorEncryptDecrypt(entries[i].title);
        xorEncryptDecrypt(entries[i].content);
    }
    fclose(fp);
}

// Function to add a new entry
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
    entries[entryCount].date[strcspn(entries[entryCount].date, "\n")] = 0;

    int y, m, d;
    if (sscanf(entries[entryCount].date, "%4d-%2d-%2d", &y, &m, &d) != 3)
    {
        printf("Invalid date format. Please use the format YYYY-MM-DD.\n");
        return;
    }

    if (!isValidDate(y, m, d))
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

    entryCount++;
    saveEntries();
    printf("Entry added successfully.\n");
}

// Function to view all entries
void viewEntry()
{
    if (entryCount == 0)
    {
        printf("No entries to display.\n");
        return;
    }

    printf("\n--- All Diary Entries ---\n");

    for (int i = 0; i < entryCount; i++)
    {
        printf("\nEntry %d\n", i + 1);
        printf("Date   : %s\n", entries[i].date);
        printf("Title  : %s\n", entries[i].title);
        printf("Content: %s\n", entries[i].content);
    }
}

// Function to search for an entry by date
void searchEntry()
{
    char searchDate[20];
    getchar(); // Clear input buffer
    printf("Enter date to search (YYYY-MM-DD): ");
    fgets(searchDate, sizeof(searchDate), stdin);
    searchDate[strcspn(searchDate, "\n")] = 0; // Remove newline

     int y, m, d;
    if (sscanf(entries[entryCount].date, "%4d-%2d-%2d", &y, &m, &d) != 3)
    {
        printf("Invalid date format. Please use the format YYYY-MM-DD.\n");
        return;
    }

    if(!isValidDate(y, m, d))
    {
                printf("Invalid date format. Please enter a valid date(format YYYY-MM-DD.\n");
return;
    }

    int found = 0;

    for (int i = 0; i < entryCount; i++)
    {
        if (strcmp(entries[i].date, searchDate) == 0)
        {
            printf("\nEntry found:\n");
            printf("Date   : %s\n", entries[i].date);
            printf("Title  : %s\n", entries[i].title);
            printf("Content: %s\n", entries[i].content);
            found = 1;
        }
    }

    if (!found)
    {
        printf("No entry found for the given date.\n");
    }
}

void editEntry() // Function to edit an existing diary entry by date
{
    int y, m, d;
    char dateInput[20];
    int found = 0;

    getchar(); // clear input buffer

    // Ask user to enter a valid date
    do {
        printf("Enter date (YYYY-MM-DD): ");
        fgets(dateInput, sizeof(dateInput), stdin);
        dateInput[strcspn(dateInput, "\n")] = 0; // remove newline

        if (sscanf(dateInput, "%d-%d-%d", &y, &m, &d) != 3 || !isValidDate(y, m, d)) {
            printf("Invalid date! Try again.\n");
        } else {
            break;
        }
    } while (1);

    // Loop through entries to find a matching date
    for (int i = 0; i < entryCount; i++) {
        if (strcmp(entries[i].date, dateInput) == 0) {
            found = 1;
            printf("Current Title: %s\n", entries[i].title);
            printf("Current Content: %s\n", entries[i].content);

            printf("Enter new title: ");
            fgets(entries[i].title, sizeof(entries[i].title), stdin);
            entries[i].title[strcspn(entries[i].title, "\n")] = 0;

            printf("Enter new content: ");
            fgets(entries[i].content, sizeof(entries[i].content), stdin);
            entries[i].content[strcspn(entries[i].content, "\n")] = 0;

            saveEntries(); // save updated entries
            printf("Entry updated successfully.\n");
            break;
        }
    }

    if (!found) {
        printf("No entry found for the given date.\n");
    }
}

// Function to delete an entry (not yet implemented)
void deleteEntry()
{
    printf("\nDelete Entry functionality not implemented yet.\n");
}

int main()
{
    if (!authenticate())
    {
        return 0;
    }

    int choice;

    loadEntries(); // loads previously saved diary entries from the file into memory

    do
    {
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
        case 1:
            addEntry();
            break;
        case 2:
            viewEntry();
            break;
        case 3:
            searchEntry();
            break;
        case 4:
            editEntry();
            break;
        case 5:
            deleteEntry();
            break;
        case 6:
            printf("Exiting...\n");
            break;
        default:
            printf("Invalid choice!\n");
        }
    } while (choice != 6);

    return 0;
}
