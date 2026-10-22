
#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <sstream>

using namespace std;

struct Expense {
    string name;
    string category;
    double amount;
};

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
        getline(cin, line);

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
        getline(cin, line);

        stringstream ss(line);

        if ((ss >> amount) && !(ss >> extra)
            && amount > 0 && amount <= 1000000000.0) {
            return amount;
        }

        cout << "Invalid amount! Enter a positive number.\n";
    }
}

// Add an expense
void addExpense(vector<Expense>& expenses) {
    Expense e;

    cout << "\n--- Add Expense ---\n";

    e.name = readText("Enter expense name: ");
    e.category = readText("Enter category: ");
    e.amount = readAmount();

    expenses.push_back(e);

    cout << "Expense added successfully!\n";
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
    int choice;

    do {
        cout << "\n========== EXPENSE TRACKER ==========\n";
        cout << "1. Add Expense\n";
        cout << "2. List Expenses\n";
        cout << "3. Category Total\n";
        cout << "4. Overall Total\n";
        cout << "5. Exit\n";
        cout << "=====================================\n";

        choice = readChoice();

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
                break;
        }

    } while (choice != 5);

    return 0;
}
