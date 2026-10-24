
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>
#include <fstream>

using namespace std;

struct Expense {
    string name;
    string category;
    double amount;
};

const string DATA_FILE = "expenses.txt";

// Read a non-empty string
string readText(const string& prompt) {
    string value;

    while (true) {
        cout << prompt;
        getline(cin, value);

        if (value.find_first_not_of(" \t\r\n") != string::npos) {
            return value;
        }

        cout << "Input cannot be empty. Please try again.\n";
    }
}

// Read a valid menu choice
int readChoice() {
    string line;
    int choice;
    char extra;

    while (true) {
        cout << "Enter your choice: ";

        if (!getline(cin, line)) {
            cout << "\nInput closed. Exiting program.\n";
            return 5;
        }

        stringstream ss(line);

        if ((ss >> choice) && !(ss >> extra)
            && choice >= 1 && choice <= 5) {
            return choice;
        }

        cout << "Invalid choice! Enter a number from 1 to 5.\n";
    }
}

// Read a valid positive amount
double readAmount() {
    string line;
    double amount;
    char extra;

    while (true) {
        cout << "Enter amount: ";

        if (!getline(cin, line)) {
            cout << "\nInput closed. Exiting program.\n";
            return -1;
        }

        stringstream ss(line);

        if ((ss >> amount) && !(ss >> extra)
            && amount > 0 && amount <= 1000000000.0) {
            return amount;
        }

        cout << "Invalid amount! Enter a positive number.\n";
    }
}

// Save all expenses to a file
bool saveExpenses(const vector<Expense>& expenses) {
    ofstream file(DATA_FILE, ios::trunc);

    if (!file.is_open()) {
        cerr << "Error: Could not open " << DATA_FILE
             << " for saving.\n";
        return false;
    }

    file << setprecision(17);

    for (const Expense& e : expenses) {
        file << quoted(e.name) << ' '
             << quoted(e.category) << ' '
             << e.amount << '\n';
    }

    file.close();

    if (file.fail()) {
        cerr << "Error: Could not save expenses successfully.\n";
        return false;
    }

    return true;
}

// Load previously saved expenses
void loadExpenses(vector<Expense>& expenses) {
    ifstream file(DATA_FILE);

    // A missing file is normal on the first run.
    if (!file.is_open()) {
        return;
    }

    Expense e;

    while (file >> quoted(e.name)
                >> quoted(e.category)
                >> e.amount) {

        if (e.name.empty() || e.category.empty()
            || e.amount <= 0 || e.amount > 1000000000.0) {
            cerr << "Warning: Invalid record in "
                 << DATA_FILE << ". Loading stopped.\n";
            break;
        }

        expenses.push_back(e);
    }

    if (!file.eof() && file.fail()) {
        cerr << "Warning: Could not read all records from "
             << DATA_FILE << ".\n";
    }

    cout << expenses.size()
         << " saved expense(s) loaded.\n";
}

// Add an expense
void addExpense(vector<Expense>& expenses) {
    Expense e;

    cout << "\n--- Add Expense ---\n";

    e.name = readText("Enter expense name: ");
    e.category = readText("Enter category: ");
    e.amount = readAmount();

    if (e.amount < 0) {
        cout << "Expense was not added.\n";
        return;
    }

    expenses.push_back(e);

    if (saveExpenses(expenses)) {
        cout << "Expense added and saved successfully!\n";
    } else {
        expenses.pop_back();
        cout << "Expense was not saved. Please check the file location.\n";
    }
}

// Display all expenses
void listExpenses(const vector<Expense>& expenses) {
    if (expenses.empty()) {
        cout << "\nNo expenses recorded yet.\n";
        return;
    }

    cout << "\n---------------- EXPENSE LIST ----------------\n";

    cout << left
         << setw(22) << "Name"
         << setw(18) << "Category"
         << right << setw(12) << "Amount" << '\n';

    cout << string(52, '-') << '\n';
    cout << fixed << setprecision(2);

    for (const Expense& e : expenses) {
        cout << left
             << setw(22) << e.name
             << setw(18) << e.category
             << right << setw(12) << e.amount << '\n';
    }

    cout << string(52, '-') << '\n';
}

// Calculate total for a category
void categoryTotal(const vector<Expense>& expenses) {
    string category = readText("Enter category to total: ");

    double total = 0.0;
    bool found = false;

    for (const Expense& e : expenses) {
        if (e.category == category) {
            total += e.amount;
            found = true;
        }
    }

    if (found) {
        cout << fixed << setprecision(2);
        cout << "Total for " << category << ": " << total << '\n';
    } else {
        cout << "No expenses found in that category.\n";
    }
}

// Calculate overall expense total
void overallTotal(const vector<Expense>& expenses) {
    double total = 0.0;

    for (const Expense& e : expenses) {
        total += e.amount;
    }

    cout << fixed << setprecision(2);
    cout << "Overall expense total: " << total << '\n';
}

// Main program
int main() {
    vector<Expense> expenses;

    loadExpenses(expenses);

    while (true) {
        cout << "\n========== EXPENSE TRACKER ==========\n";
        cout << "1. Add Expense\n";
        cout << "2. List Expenses\n";
        cout << "3. Category Total\n";
        cout << "4. Overall Total\n";
        cout << "5. Exit\n";
        cout << "=====================================\n";

        int choice = readChoice();

        switch (choice) {
            case 1:
                addExpense(expenses);
                break;

            case 2:
                listExpenses(expenses);
                break;

            case 3:
                if (expenses.empty()) {
                    cout << "No expenses recorded yet.\n";
                } else {
                    categoryTotal(expenses);
                }
                break;

            case 4:
                overallTotal(expenses);
                break;

            case 5:
                cout << "Thank you for using Expense Tracker!\n";
                return 0;
        }
    }
}
