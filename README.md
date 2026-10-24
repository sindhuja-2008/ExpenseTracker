# Expense Tracker (C++)

A menu-driven C++ command-line application for recording expenses and calculating category-wise and overall spending totals.

## Features

- Add expenses with a name, category, and amount
- List all recorded expenses
- Calculate category-wise totals
- Calculate the overall expense total
- Validate menu choices and expense amounts
- Save expenses to a local file and load them automatically when the program restarts

## Technologies

- C++17
- Vectors and structures
- Functions and input validation
- File handling using `fstream`

## How to Compile

```bash
g++ -std=c++17 main.cpp -o expense_tracker.exe
```

## How to Run

```bash
./expense_tracker.exe
```

Run these commands from the project folder in your MSYS2 UCRT64 terminal.

## Menu

1. Add Expense
2. List Expenses
3. Category Total
4. Overall Total
5. Exit

## Data Storage

Expenses are stored in `expenses.txt`. The program loads saved expenses when it starts and updates the file when a new expense is added. Keep the file in the directory from which you run the program.

## Project Structure

- `main.cpp` — C++ source code
- `README.md` — Project documentation
- `.gitignore` — Files excluded from version control

## Purpose

This project demonstrates C++ programming fundamentals, input validation, formatted console output, and persistent file storage.
