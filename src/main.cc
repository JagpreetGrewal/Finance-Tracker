#include <iostream>
#include <sqlite3.h> // SQLite library header
#include <chrono>
#include <thread>


// Function to add an expense
void addExpense(sqlite3* db)
{
    // Prompt user for expense details
    std::string date, category;
    double amount;
    std::cout << "Enter the expense details:" << std::endl;
    std::cout << "Date: ";
    std::cin >> date;
    std::cout << "Category: ";
    std::cin >> category;
    std::cout << "Amount: ";
    std::cin >> amount;

    // Insert expense record into the database
    std::string insertQuery = "INSERT INTO expenses (date, category, amount) "
                              "VALUES ('" + date + "', '" + category + "', " + std::to_string(amount) + ");";
    int rc = sqlite3_exec(db, insertQuery.c_str(), nullptr, nullptr, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cout << "Error inserting expense: " << sqlite3_errmsg(db) << std::endl;
    }
    else
    {
        std::cout << "Expense added successfully." << std::endl;
    }
}

// Function to list expenses
void listExpenses(sqlite3* db)
{
    // Retrieve expense records from the database
    std::string selectQuery = "SELECT * FROM expenses;";
    sqlite3_stmt* stmt;
    int rc = sqlite3_prepare_v2(db, selectQuery.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK)
    {
        std::cout << "Error retrieving expenses: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    // Display expense records
    std::cout << "Expense Records:" << std::endl;
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char* date = sqlite3_column_text(stmt, 1);
        const unsigned char* category = sqlite3_column_text(stmt, 2);
        double amount = sqlite3_column_double(stmt, 3);
        
        std::cout << "ID: " << id << std::endl;
        std::cout << "Date: " << date << std::endl;
        std::cout << "Category: " << category << std::endl;
        std::cout << "Amount: " << amount << std::endl;
        std::cout << std::endl;
    }

    sqlite3_finalize(stmt);
}

int main()
{
    // Connect to the database
    sqlite3* db;
    int rc = sqlite3_open("expense_tracker.db", &db);

    if (rc)
    {
        std::cout << "Error opening the database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Create the expenses table if it doesn't exist
    std::string createTableQuery = "CREATE TABLE IF NOT EXISTS expenses ("
                                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                                   "date TEXT,"
                                   "category TEXT,"
                                   "amount REAL);";

    rc = sqlite3_exec(db, createTableQuery.c_str(), nullptr, nullptr, nullptr);

    if (rc != SQLITE_OK)
    {
        std::cout << "Error creating the expenses table: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Application loop
    int choice;
    std::cout<<"Loading for 10 seconds..."<<std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(10000));
    while (true)
    {
        // Display menu options
        std::cout << "Expense Tracker Menu:" << std::endl;
        std::cout << "1. Add Expense" << std::endl;
        std::cout << "2. List Expenses" << std::endl;
        std::cout << "3. Exit" << std::endl;
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        // Handle user choice
        switch (choice)
        {
            case 1:
                addExpense(db);
                break;
            case 2:
                listExpenses(db);
                break;
            case 3:
                // Exit the application
                sqlite3_close(db);
                return 0;
            default:
                std::cout << "Invalid choice. Please try again." << std::endl;
                break;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    }
}
