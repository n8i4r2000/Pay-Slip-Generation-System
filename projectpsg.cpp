
#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <vector>
#include <limits>

using namespace std;

struct Employee {
    string name;
    string id;
    string designation;
    string department;
    double basicSalary;
    double hra;
    double da;
    double ta;
    double grossSalary;
    double pf;
    double tax;
    double totalDeductions;
    double netSalary;
};

vector<Employee> employees;

void clearInputBuffer() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void calculateSalary(Employee &emp) {
    emp.hra = emp.basicSalary * 0.25;
    emp.da = emp.basicSalary * 0.15;
    emp.ta = emp.basicSalary * 0.10;
    emp.grossSalary = emp.basicSalary + emp.hra + emp.da + emp.ta;
    emp.pf = emp.basicSalary * 0.12;

    if (emp.grossSalary <= 250000) {
        emp.tax = 0;
    } else if (emp.grossSalary <= 500000) {
        emp.tax = (emp.grossSalary - 250000) * 0.05;
    } else if (emp.grossSalary <= 1000000) {
        emp.tax = 12500 + (emp.grossSalary - 500000) * 0.20;
    } else {
        emp.tax = 112500 + (emp.grossSalary - 1000000) * 0.30;
    }

    emp.totalDeductions = emp.pf + emp.tax;
    emp.netSalary = emp.grossSalary - emp.totalDeductions;
}

void displayPayslip(const Employee &emp) {
    cout << "\n============== PAY SLIP ==============\n";
    cout << "Employee Name: " << emp.name << endl;
    cout << "Employee ID: " << emp.id << endl;
    cout << "Designation: " << emp.designation << endl;
    cout << "Department: " << emp.department << endl << endl;

    cout << fixed << setprecision(2);
    cout << "---------- Earnings ----------" << endl;
    cout << "Basic Salary: \t\t₹" << emp.basicSalary << endl;
    cout << "HRA (25%): \t\t₹" << emp.hra << endl;
    cout << "DA (15%): \t\t₹" << emp.da << endl;
    cout << "TA (10%): \t\t₹" << emp.ta << endl;
    cout << "Gross Salary: \t\t₹" << emp.grossSalary << endl << endl;

    cout << "---------- Deductions ----------" << endl;
    cout << "PF (12%): \t\t₹" << emp.pf << endl;
    cout << "Income Tax: \t\t₹" << emp.tax << endl;
    cout << "Total Deductions: \t₹" << emp.totalDeductions << endl << endl;

    cout << "Net Salary: \t\t₹" << emp.netSalary << endl;
    cout << "=====================================\n";
}

void saveToFile(const Employee &emp) {
    string filename = "Payslip_" + emp.id + ".txt";
    ofstream outFile(filename);

    outFile << "============== PAY SLIP ==============\n";
    outFile << "Employee Name: " << emp.name << "\n";
    outFile << "Employee ID: " << emp.id << "\n";
    outFile << "Designation: " << emp.designation << "\n";
    outFile << "Department: " << emp.department << "\n\n";

    outFile << fixed << setprecision(2);
    outFile << "---------- Earnings ----------\n";
    outFile << "Basic Salary: \t\t₹" << emp.basicSalary << "\n";
    outFile << "HRA (25%): \t\t₹" << emp.hra << "\n";
    outFile << "DA (15%): \t\t₹" << emp.da << "\n";
    outFile << "TA (10%): \t\t₹" << emp.ta << "\n";
    outFile << "Gross Salary: \t\t₹" << emp.grossSalary << "\n\n";

    outFile << "---------- Deductions ----------\n";
    outFile << "PF (12%): \t\t₹" << emp.pf << "\n";
    outFile << "Income Tax: \t\t₹" << emp.tax << "\n";
    outFile << "Total Deductions: \t₹" << emp.totalDeductions << "\n\n";

    outFile << "Net Salary: \t\t₹" << emp.netSalary << "\n";
    outFile << "=====================================\n";

    cout << "\nPay slip saved as '" << filename << "'" << endl;
}

void addEmployee() {
    Employee emp;

    cout << "\n===== ADD NEW EMPLOYEE =====" << endl;
    cout << "Enter Employee Name: ";
    getline(cin, emp.name);
    cout << "Enter Employee ID: ";
    getline(cin, emp.id);
    cout << "Enter Designation: ";
    getline(cin, emp.designation);
    cout << "Enter Department: ";
    getline(cin, emp.department);
    cout << "Enter Basic Salary: ₹";
    while (!(cin >> emp.basicSalary)) {
        cout << "Invalid input. Please enter a valid salary: ₹";
        clearInputBuffer();
    }
    clearInputBuffer();

    calculateSalary(emp);
    employees.push_back(emp);
    cout << "\nEmployee added successfully!" << endl;
}

void generatePayslip() {
    if (employees.empty()) {
        cout << "\nNo employees found. Please add employees first." << endl;
        return;
    }

    string empId;
    cout << "\nEnter Employee ID to generate pay slip: ";
    getline(cin, empId);

    bool found = false;
    for (const auto &emp : employees) {
        if (emp.id == empId) {
            displayPayslip(emp);
            saveToFile(emp);
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nEmployee with ID " << empId << " not found." << endl;
    }
}

void viewAllEmployees() {
    if (employees.empty()) {
        cout << "\nNo employees found." << endl;
        return;
    }

    cout << "\n===== EMPLOYEE LIST =====" << endl;
    cout << left << setw(15) << "ID" << setw(25) << "Name"
         << setw(20) << "Designation" << setw(15) << "Department"
         << setw(15) << "Net Salary" << endl;
    cout << string(90, '-') << endl;

    for (const auto &emp : employees) {
        cout << left << setw(15) << emp.id << setw(25) << emp.name
             << setw(20) << emp.designation << setw(15) << emp.department
             << "₹" << fixed << setprecision(2) << emp.netSalary << endl;
    }
}

void mainMenu() {
    int choice;
    do {
        cout << "\n===== RAFI PAY SLIP GENERATOR =====" << endl;
        cout << "1. Add New Employee" << endl;
        cout << "2. Generate Pay Slip" << endl;
        cout << "3. View All Employees" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice (1-4): ";

        while (!(cin >> choice) || choice < 1 || choice > 4) {
            cout << "Invalid input. Please enter a number between 1 and 4: ";
            clearInputBuffer();
        }
        clearInputBuffer();

        switch (choice) {
            case 1:
                addEmployee();
                break;
            case 2:
                generatePayslip();
                break;
            case 3:
                viewAllEmployees();
                break;
            case 4:
                cout << "\nExiting system. Goodbye!" << endl;
                break;
        }
    } while (choice != 4);
}

int main() {
    mainMenu();
    return 0;
}
