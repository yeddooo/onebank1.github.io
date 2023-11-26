#include <stdio.h>
#include <string.h>
#include<stdlib.h>

struct User {
    char name[50];
    char studentID[100];
};

// Function to register a new user
void Register() {
    // Declare variables
    struct User user;

    // Get user input
    printf("Name: ");
    scanf("%s", user.name);

    printf("Student ID: ");
    scanf("%s", user.studentID);

    // Open the file for writing (append mode)
    FILE *file = fopen("user_data.txt", "a");

    if (file == NULL) {
        printf("Error opening file\n");
        return;
    }

    // Write user data to the file
    fwrite(&user, sizeof(struct User), 1, file);

    // Close the file
    fclose(file);

    printf("Registration successful!\n");
}

// Function to log in
int Login() {
    // Declare variables
    char inputName[50];
    char inputStudentID[100];
    struct User storedUser;
    FILE *file;
    int count = 0;

    // Display login prompt
    printf("--- Log In ---\n");

    // Get user input
    while (count < 3) {
        printf("Name: ");
        scanf("%s", inputName);

        printf("Student ID: ");
        scanf("%s", inputStudentID);

        // Open the file for reading
        file = fopen("user_data.txt", "r");

        // Check if the file is opened successfully
        if (file == NULL) {
            printf("Error opening file\n");
            return 0; // Return 0 indicates login failure
        }

        // Read each line in the file
        while (fread(&storedUser, sizeof(struct User), 1, file) == 1) {
            // Compare input name and student ID to stored user
            if (strcmp(inputName, storedUser.name) == 0 && strcmp(inputStudentID, storedUser.studentID) == 0) {
                // Match found
                printf("Login successful!\n");
                fclose(file);
                return 1; // Return 1 indicates login success
            }
        }

        // Close the file
        fclose(file);

        // No match found
        printf("Login failed. Incorrect name or student ID.\n");
        count++;
    }

    // Exceeded login attempts
    printf("Login failed. Exiting program...\n");
    return 0; // Return 0 indicates login failure
}

// Forward declaration of the Menu function
void Menu();

// Structure to store information about income transactions
struct income_info
{
    float amount; // Amount of the income
    int choice; // Choice representing the income category
    char income_detail[100]; // Description or detail of the income
};

// Structure to store information about expense transactions
struct ExpenseRecord
{
    float amount; // Amount of the expense
    char category[20]; // Category or type of the expense
};
// Note: These structures define the data structure for storing income and expense records.
// They are meant to be used in a financial management system where details about income
// and expense transactions are recorded and managed

void income()
{
    FILE *wf1;
    char continueIncome;
    struct income_info income_data;

    do
    {
        // Display message
        printf("--- Income ---\n");
        printf("Amount : ");

        // Receive input from the user
        scanf("%f", &income_data.amount);

        // Display options
        printf("1. Refund\n");
        printf("2. Special\n");
        printf("3. Revenue\n");
        printf("4. Free\n");
        printf("5. Business\n");
        printf("6. Borrow\n");
        printf("7. Other\n");

        // Receive choice
        printf("Category : ");
        scanf("%d", &income_data.choice);

        // Store details based on user's choice
        switch (income_data.choice)
        {
        case 1:
            snprintf(income_data.income_detail, sizeof(income_data.income_detail), "Refund");
            break;
        case 2: 
            snprintf(income_data.income_detail, sizeof(income_data.income_detail), "Special");
            break;
        case 3:
            snprintf(income_data.income_detail, sizeof(income_data.income_detail), "Revenue");
            break;
        case 4:
            snprintf(income_data.income_detail, sizeof(income_data.income_detail), "Free");
            break;
        case 5:
            snprintf(income_data.income_detail, sizeof(income_data.income_detail), "Business");
            break;
        case 6:
            snprintf(income_data.income_detail, sizeof(income_data.income_detail), "Borrow");
            break;
        case 7:
            snprintf(income_data.income_detail, sizeof(income_data.income_detail), "Other");
            break;
        default:
            snprintf(income_data.income_detail, sizeof(income_data.income_detail), "Unknown");
            break;
        }

        // Open the file for writing in append mode
        wf1 = fopen("income.txt", "w");
        if (wf1 != NULL)
        {
            // Write income_data to the file
            fprintf(wf1, "%.2f %s\n", income_data.amount,income_data.income_detail);

            // Close the file after writing
            fclose(wf1);
        }

        // Display message
        printf("Do you want to continue with 'Income'? (y/n) ");

        // Receive y/n input from the user
        scanf(" %c", &continueIncome);

    } while (continueIncome == 'y' || continueIncome == 'Y');

    printf("Save income information in file income.txt successfully.\n");
    printf("End of income section.\n");
}

void Expense()
{
    FILE *file;
    struct ExpenseRecord expenseRecord;
    char continueExpense;

    do
    {
        // Display message
        printf("--- Expense ---\n");
        printf("Amount : ");

        // Receive input from the user
        scanf("%f", &expenseRecord.amount);

        // Display options
        printf("1. Food\n");
        printf("2. Transport\n");
        printf("3. Shopping\n");
        printf("4. Medical Expenses\n");
        printf("5. Service\n");
        printf("6. Other\n");

        // Receive choice
        printf("Category : ");
        int choice;
        scanf("%d", &choice);

        // Map the choice to the corresponding category
        switch (choice)
        {
        case 1:
            strcpy(expenseRecord.category, "Food");
            break;
        case 2:
            strcpy(expenseRecord.category, "Transport");
            break;
        case 3:
            strcpy(expenseRecord.category, "Shopping");
            break;
        case 4:
            strcpy(expenseRecord.category, "Medical Expenses");
            break;
        case 5:
            strcpy(expenseRecord.category, "Service");
            break;
        case 6:
            strcpy(expenseRecord.category, "Other");
            break;
        default:
            strcpy(expenseRecord.category, "Unknown");
            break;
        }

        // Open the file in append mode
        file = fopen("expense.txt", "w");
        if (file != NULL)
        {
            // Write the expense record to the file
            fprintf(file, "%.2f %s\n", expenseRecord.amount, expenseRecord.category);

            // Close the file after writing
            fclose(file);
        }

        // Display message
        printf("Do you want to continue with 'Expense'? (y/n) ");

        // Receive y/n input from the user
        scanf(" %c", &continueExpense);

    } while (continueExpense == 'y' || continueExpense == 'Y');

    printf("Save expense information in file expense.txt successfully.\n");
    printf("End of expense section.\n");
}

// Function to calculate the total amount from a file
float calculateTotal(const char *filename)
{
    FILE *file = fopen(filename, "r"); // Open the file in read mode
    float total = 0.0; // Variable to store the total amount
    float amount; // Variable to store the amount read from the file
    char category[20]; // Variable to store the category read from the file

    if (file != NULL)
    {
        // Read each line in the file until the end-of-file is reached
        while (fscanf(file, "%f %s", &amount, category) != EOF)
        {
            // Add the amount to the total
            total += amount;
        }

        // Close the file after reading
        fclose(file);
    }
    // Return the calculated total
    return total;
}

void Saving()
{
    // Declare variables
    float amount;
    char continueSavings;
    do
    {
        // Display message
        printf("--- Savings ---\n");
        printf("Amount : ");

        // Receive input from the user
        scanf("%f", &amount);

        // Display message
        printf("Do you want to continue with 'Savings'? (y/n) ");

        // Receive y/n input from the user
        scanf(" %c", &continueSavings);

        // Check the value entered by the user
    } while (continueSavings == 'y' || continueSavings == 'Y');
}

void AccountBalance()
{

    char backInput[20];
    // Set initial values (replace with actual logic)

    float totalIncome = calculateTotal("income.txt");
    float totalExpense = calculateTotal("expense.txt");
    float totalAll = totalIncome - totalExpense;
    printf("Total Income: %.2f\n", totalIncome);
    printf("Total Expense: %.2f\n", totalExpense);
    printf("Total All: %.2f\n", totalAll);

    do
    {
        printf("--- Account balance ---\n");
        printf("Total : %.2f bath\n", totalAll);
        printf("Income : %.2f bath\n", totalIncome);
        printf("Expense : %.2f bath\n", totalExpense);
        printf("To go back to the Menu, please type 'Back' : ");
        scanf("%s", backInput);

        // Check if the user wants to go back to the main menu
    } while (strcmp(backInput, "Back") != 0);

    // After the loop, return to the main menu
    Menu();
}

void financialOverview()
{
    // Calculate total income
    char backInput[20];
    float totalIncome = calculateTotal("income.txt");
    float totalexpense = calculateTotal("expense.txt");
    float totalSaving = calculateTotal("saving.txt");

    // Print total income and expense
    do{
    printf("Total Income: %.2f\n", totalIncome);
    printf("Total Expense: %.2f\n", totalexpense);

    // Print each income category
    FILE *fp = fopen("income.txt", "r");
    FILE *fp2 = fopen("expense.txt", "r");
    FILE *fp3 = fopen("saving.txt", "r");
    struct income_info income_data;
    struct ExpenseRecord expenseRecord;

    if (fp != NULL)
    {
        while (fscanf(fp, "%f %s", &income_data.amount, income_data.income_detail) != EOF)
        {
            // Print each income category
            printf("Category: %s, Amount: %.2f\n", income_data.income_detail, income_data.amount);
        }

        fclose(fp);
    }
    if (fp2 != NULL)
    {
        while (fscanf(fp2, "%f %s", &expenseRecord.amount, expenseRecord.category) != EOF)
        {
            // Print each income category
            printf("Category: %s, Amount: %.2f\n", expenseRecord.category,expenseRecord.amount);
        }

        fclose(fp2);
    }
     if (fp3!= NULL)
     {
        printf("Total Saving: %.2f\n", totalSaving);
        fclose(fp3);
     }
    else
    {
        printf("Error opening file: income.txt\n");
    }
    printf("To go back to the Menu, please type 'Back' : ");
    scanf("%s", backInput);
    } while (strcmp(backInput, "Back") != 0);

    // After the loop, return to the main menu
    Menu();
}

void Menu()
{
    int menuChoice; // Declare menuChoice variable in the Menu function

    do
    {
        // Display the menu options
        printf("--- Welcome to One Bank ---\n");
        printf("--- Menu ---\n");
        printf("1. Income\n");
        printf("2. Expense\n");
        printf("3. Savings\n");
        printf("4. Account balance\n");
        printf("5. Financial Overview\n");
        printf("6. Exit the program\n");
        printf("Please select a menu to continue: ");

        // Receive user choice
        scanf("%d", &menuChoice);

        // Process the user's choice
        switch (menuChoice)
        {
        case 1:
            income();
            break;
        case 2:
            Expense();
            break;
        case 3:
            Saving();
            break;
        case 4:
            AccountBalance();
            break;
        case 5:
            financialOverview();
            break;
        case 6:
            // Exit the program
            printf("Exiting the program. Goodbye!\n");
            exit(0);
        default:
            // Invalid menu choice
            printf("Invalid menu choice. Please try again.\n");
            break;
        }

    } while (menuChoice != 6); // Continue the loop until the user chooses to exit
}

int main()
{
    Register();

    // Log in
    int loginResult = Login();

    if (loginResult == 1) {
        // Further actions after successful login
        printf("Welcome!\n");
        Menu();
    } else {
        // Handle unsuccessful login
        printf("Exiting program...\n");
    }
    return 0;
}