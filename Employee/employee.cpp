#include "constants.h" // include a copy of the constants file
#include <conio.h>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// Employee class to store information about employees
class Employee {
    private:
        string name;
        int id;
        string role;
        string department;
        double salary;
        string email;
        string password;
    public:
        Employee(string empName="", int empId=0, string empRole="", string empDepartment="", double empSalary=0.00, string empEmail="", string empPassword="") {
            name = empName;
            id = empId;
            role = empRole;
            department = empDepartment;
            salary = empSalary;
            email = empEmail;
            password = empPassword;
        }

        void displayInfo() {
            cout
                << left
                << setw(25)
                << name
                << left
                << setw(6)
                << id
                << left
                << setw(10)
                << role
                << left
                << setw(20)
                << department
                << left
                << setw(8)
                << salary
                << left
                << setw(22)
                << email
                << endl;
        }

        void getHeader() {
            cout << endl;
            cout
                << left
                << setw(25)
                << "Employee Name"
                << left
                << setw(6)
                << "ID #"
                << left
                << setw(10)
                << "Role"
                << left
                << setw(20)
                << "Department"
                << left
                << setw(8)
                << "Salary"
                << left
                << setw(22)
                << "Email"
                << endl;
            cout << endl;
        }

        int getId() {
            return id;
        }

        string getName() {
            return name;
        }

        string getRole() {
            return role;
        }

        string getDepartment() {
            return department;
        }

        double getSalary() {
            return salary;
        }

        string getEmail() {
            return email;
        }

        string getPassword() {
            return password;
        }

        void setName(const string& newName) {
            name = newName;
        }

        void setRole(const string& newRole) {
            role = newRole;
        }

        void setDepartment(const string& newDepartment) {
            department = newDepartment;
        }

        void setSalary(double newSalary) {
            salary = newSalary;
        }

        void setEmail(const string& newEmail) {
            email = newEmail;
        }

        void setPassword(const string& newPassword) {
            password = newPassword;
        }
};


class Login {
    private:
        string email;
        string password;
        string role;
    public:
        Login(string eml, string pwd) {
            email = eml;
            password = pwd;
        }

        string getRole(vector<Employee>& employees, string& empEmail, string& empPassword) {
            email = empEmail;
            password = empPassword;

            for (int i = 0; i < employees.size(); i++) {
                if (employees[i].getEmail() == email && employees[i].getPassword() == password) {
                    return employees[i].getRole();
                }
            }
            return "Invalid";
        }

        int getUser(vector<Employee>& employees, string email) {
            for (int i = 0; i < employees.size(); i++) {
                if (employees[i].getEmail() == email) {
                    return i;
                }
            }
            return -1;
        }

};


class IO_Service {
    private:
        ofstream file_out;
        ifstream file_in;
    public:
        IO_Service() {
        }

        ~IO_Service() {

        }

        void write(vector<Employee>& employees) {
            file_out.open(constants::FILENAME, ios::out);
            for (int i = 0; i < employees.size(); i++) {
                file_out << employees[i].getName() << "," << employees[i].getId() << "," << employees[i].getRole() << ","
                         << employees[i].getDepartment() << "," << employees[i].getSalary() << ","
                         << employees[i].getEmail() << "," << employees[i].getPassword() << "," << endl;
            }
            file_out.close();
        }


        void read(vector<Employee>& employees) {
            file_in.open(constants::FILENAME, ios::in);
            string line;
            while (getline(file_in, line)) {
                stringstream ss(line);
                string name, role, department, email, password, salary_str, id_str;
                int id, salary;
                getline(ss, name, ',');
                getline(ss, id_str, ',');
                id = stoi(id_str);
                getline(ss, role, ',');
                getline(ss, department, ',');
                getline(ss, salary_str, ',');
                salary = stoi(salary_str);
                getline(ss, email, ',');
                getline(ss, password, ',');
                Employee newEmployee(name, id, role, department, salary, email, password);
                employees.push_back(newEmployee);
            }
            file_in.close();
        }
};


// Manager class to search and view employee records
class Manager {
    public:
        int search(vector<Employee>& employees, int empId) {
            for (int i = 0; i < employees.size(); i++) {
                if (employees[i].getId() == empId) {
                    cout << endl;
                    getHeader();
                    employees[i].displayInfo();
                    return i;
                }
            }
            cout << "Employee not found." << endl;
            return false;
        }

        void viewAll(vector<Employee>& employees) {
            getHeader();
            for (int i = 0; i < employees.size(); i++) {
                employees[i].displayInfo();
                cout << endl;
            }
        }

        void getHeader() {
            cout << endl;
            cout
                << left
                << setw(25)
                << "Employee Name"
                << left
                << setw(6)
                << "ID #"
                << left
                << setw(10)
                << "Role"
                << left
                << setw(20)
                << "Department"
                << left
                << setw(8)
                << "Salary"
                << left
                << setw(22)
                << "Email"
                << endl;
            cout << endl;
        }

};


// Human Resources class to manage employee records
class HumanResources {
    private:
        // Declare an IO_Service object
        IO_Service io_service;

        int getMaxId(vector<Employee>& employees) {
            int maxId = 0;
            for (int i = 0; i < employees.size(); i++) {
                if (employees[i].getId() > maxId) {
                    maxId = employees[i].getId();
                }
            }
            return maxId;
        }

    public:
        int addEmployee(vector<Employee>& employees, string empName, int empId, string empRole, string empDepartment, double empSalary, string empEmail, string empPassword) {
            empId = getMaxId(employees) + 1;
            Employee newEmployee(empName, empId, empRole, empDepartment, empSalary, empEmail, empPassword);
            employees.push_back(newEmployee);
            io_service.write(employees); // Write the updated vector to file
            cout << endl;
            return empId;
        }

        void deleteEmployee(vector<Employee>& employees, int empId) {
            for (int i = 0; i < employees.size(); i++) {
                if (employees[i].getId() == empId) {
                    employees.erase(employees.begin() + i);
                    io_service.write(employees); // Write the updated vector to file
                    cout << endl;
                    cout << "Employee # " << empId << " is deleted." << endl;
                    return;
                }
            }

            cout << "Unable to delete. Employee not found." << endl;
        }

        void updateEmployee(vector<Employee>& employees, string empName, int empId,  string empRole, string empDepartment, double empSalary, string empEmail, string empPassword) {
            for (int i = 0; i < employees.size(); i++) {
                if (employees[i].getId() == empId) {
                    employees[i] = Employee(empName, empId, empRole, empDepartment, empSalary, empEmail, empPassword);
                    io_service.write(employees); // Write the updated vector to file
                    cout << endl;
                    cout << "Employee # " << empId << " successfully updated." << endl;
                    return;
                }
            }

            cout << "Unable to update. Employee not found." << endl;
        }
};


//check if number or string
bool check_num(string str) {
    for (int i = 0; i < str.length(); i++)
        if (isdigit(str[i]) == false)
            return false;
    return true;
}

bool isSubstr(string s1, string s2) {
    // This function is used with permission from GeeksforGeeks.com
    // using find method to check if s1 is
    // a substring of s2
    if (s2.find(s1) != string::npos)
        return true;
    return false;
}

string titleCase(string s) {
    // Convert a string to titlecase
    bool space = true;
    for (int i = 0; i < s.length(); i++) {
        if (space && s[i] != ' ') {
            s[i] = toupper(s[i]);
            space = false;
        }
        else if (s[i] == ' ')
            space = true;
        else
            s[i] = tolower(s[i]);
	}
    return s;
}

string upperCase(string s) {
    // Convert a string to uppercase
    for (int i = 0; i < s.length(); i++) {
        s[i] = toupper(s[i]);
    }
    return s;
}


int main() {
    // Set up some initial employees
    vector<Employee> employees;
    // Declare a Manager object
    Manager manager;
    // Declare an HR object
    HumanResources hr;
    // Declare an employee object
    Employee currentUser;

    // Declare an IO_Service object
    IO_Service io_service;
    // Read employees from file
    io_service.read(employees);

    string strTest;
    string input;
    bool isLoggedin = false;
    bool isWelcome = true;
    int empId = 0;
    int empIndex = -1;
    // string strTest;
    double dblTest;
    string empPassword = "";
    string empName = "";
    string empRole = "";
    string empDepartment = "";
    double empSalary = 0.0;
    string empEmail = "";
    string userRole = "Invalid";
    int userIndex = -1;

    if (employees.size() == 0) {
        // Add some initial employees
        employees.push_back(Employee("John Doe", 123, "HR", "HR", 50000, "john.doe@myco.com", "12345AB*"));
        employees.push_back(Employee("Jane Smith", 456, "Employee", "Sales", 60000, "jane.smith@myco.com", "12345AB*"));
        employees.push_back(Employee("Bob Johnson", 789, "Manager", "Marketing", 95000, "bob.johnson@myco.com", "12345AB*"));
        employees.push_back(Employee("Jim Robinson", 976, "Employee", "Marketing", 50000, "jim.robinson@myco.com", "12345AB*"));
        employees.push_back(Employee("Jill Hanson", 769, "Manager", "Marketing", 80000, "jill.hanson@myco.com", "12345AB*"));
        employees.push_back(Employee("Rick Riordan", 879, "Employee", "Sales", 55000, "rick.riordan@myco.com", "12345AB*"));
        employees.push_back(Employee("Tom Dillon", 132, "HR", "HR", 50000, "tom.dillon@myco.com", "12345AB*"));
        employees.push_back(Employee("Marty Munson", 465, "Employee", "Sales", 60000, "marty.munson@myco.com", "12345AB*"));
        employees.push_back(Employee("Dan Brophy", 543, "Employee", "Marketing", 55000, "dan.brophy@myco.com", "12345AB*"));
        employees.push_back(Employee("Ben Testoni", 381, "Manager", "Sales", 75000, "ben.testoni@myco.com", "12345AB*"));

        // IO_Service::write(employees); // Write the updated vector to file
        io_service.write(employees); // Write the updated vector to file
    }

    // Create login objects for different users
    Login employeeLogin("employee", "password1");
    Login managerLogin("manager", "password2");
    Login hrLogin("hr", "password3");

    if (isWelcome == true) {
        cout << endl;
        cout << endl;
        cout << "Welcome to EmploySoft's Employee Management System... " << endl;
    };

    // Loop to allow multiple logins
    while (true) {
        if (isLoggedin == false) {
            cout << "\nPlease enter your email: ";
            cin >> empEmail;

            cout << "Please enter your password: ";
            cin >> empPassword;
            cout << "\n";

            userRole = employeeLogin.getRole(employees, empEmail, empPassword);

            if (userRole == "Invalid") {
                cout << "\nEmail not found or invalid password. Please try logging in again.\n";
                continue;
            }

            // Ask the login object for the index of the user in the vector
            // and pass it to the currentUser object
            userIndex = employeeLogin.getUser(employees, empEmail);
            if (userIndex == -1) {
                cout << "\nUser not found. Please try logging in again.\n";
                continue;
            }
            currentUser = employees[userIndex];
            empId = currentUser.getId();
            isLoggedin = true;
        }

        if (userRole == "Employee") {
            int choice;
            strTest = "";
            // Employee menu
            if (isWelcome == true) {
                cout << "Welcome, " << currentUser.getName() << ". You have Employee access." << endl;
                cout << endl;
                // currentUser.displayInfo();
                empIndex = manager.search(employees, empId);
                cout << endl;
                isWelcome = false;
            }

            cout << "1. Log out and exit" << endl;
            cout << endl;
            cout << "Please enter 1 to log out and exit: ";
            cin >> strTest;
            if (!check_num(strTest)) {
                cout << endl;
                cout << "Invalid choice." << endl;
                while ((getchar()) != '\n');
                continue;
            }
            choice = stoi(strTest);
            if (choice != 1) {
                cout << endl;
                cout << "The only available choice is '1'." << endl;
                continue;
            }
            cout << endl;
            if (choice == 1) {
                cout << "Logging out and exiting..." << endl;
                break;
            } else {
                cout << "The only available choice is '1'." << endl;
            }
        }
        else if (userRole == "Manager") {
            int choice;
            strTest = "";
            // Manager menu
            cout << endl;
            if (isWelcome == true) {
                cout << "Welcome, " << currentUser.getName() << ". You have Manager access." << endl;
                cout << endl;
                // currentUser.displayInfo();
                empIndex = manager.search(employees, empId);
                cout << endl;
                isWelcome = false;
            }
            cout << endl;
            cout << "1. Search for employee by ID" << endl;
            cout << "2. View all employees" << endl;
            cout << "3. Log out and exit" << endl;
            cout << endl;
            cout << "Please enter your choice: ";
            cin >> strTest;
            if (!check_num(strTest)) {
                cout << endl;
                cout << "Invalid choice." << endl;
                while ((getchar()) != '\n');
                continue;
            }
            choice = stoi(strTest);
            if (choice < 1 || choice > 3) {
                cout << endl;
                cout << "Please make a valid choice (1 - 3)." << endl;
                continue;
            }
            cout << endl;
            if (choice == 1) {
                cout << "Enter employee ID: ";
                cin >> empId;
                cout << endl;
                empIndex = manager.search(employees, empId);
                cout << endl;
            } else if (choice == 2) {
                manager.viewAll(employees);
                cout << endl;
            } else if (choice == 3) {
                cout << endl;
                cout << "Logging out and exiting..." << endl;
                break;
            } else {
                cout << endl;
                cout << "Please enter a valid choice." << endl;
            }
        }
        else if (userRole == "HR") {
            // Human resources menu
            int choice;
            strTest = "";
            cout << endl;
            if (isWelcome == true) {
                cout << "Welcome, " << currentUser.getName() << ". You have HR access." << endl;
                cout << endl;
                // currentUser.displayInfo();
                empIndex = manager.search(employees, empId);
                cout << endl;
                isWelcome = false;
            }
            cout << endl;
            cout << "1. Search for employee by ID" << endl;
            cout << "2. View all employees" << endl;
            cout << "3. Add new employee" << endl;
            cout << "4. Update employee" << endl;
            cout << "5. Delete employee" << endl;
            cout << "6. Log out and exit" << endl;
            cout << endl;
            cout << "Please enter your choice: ";
            cin >> strTest;
            cin.ignore(123, '\n'); // ignore the leftover newline character
            if (!check_num(strTest)) {
                cout << endl;
                cout << "Invalid choice." << endl;
                while ((getchar()) != '\n');
                continue;
            }
            choice = stoi(strTest);
            if (choice < 1 || choice > 6) {
                cout << endl;
                cout << "Please make a valid choice (1 - 6)." << endl;
                continue;
            }
            cout << endl;
            if (choice == 1) {
                cout << "Enter employee ID: ";
                cin >> empId;
                cout << endl;
                empIndex = manager.search(employees, empId);
                cout << endl;
            }
            else if (choice == 2) {
                manager.viewAll(employees);
                cout << endl;
            }
            else if (choice == 3) {
                // Add new employee
                cout << endl;

                strTest = "";
                // cin.ignore(123, '\n'); // ignore the leftover newline character
                while (true) {
                    cout << "Enter employee name: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    strTest = titleCase(strTest);
                    if (strTest == "") {
                        cout << endl;
                        cout << "Invalid input. Please enter a valid name" << endl;
                        cout << endl;
                        continue;
                    } else {
                        empName = strTest;
                    }
                    break;
                }

                strTest = "";
                // cin.ignore(123, '\n'); // ignore the leftover newline character
                while (true) {
                    cout << "Enter employee role ('Employee', 'Manager', or 'HR'): ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest.length() < 5) {
                        strTest = upperCase(strTest);
                    } else {
                        strTest = titleCase(strTest);
                    }
                    if (strTest == "" || !isSubstr(strTest+",", constants::ROLES)) {
                        cout << endl;
                        cout << "Invalid input. Please enter a valid role from: " << constants::ROLES << endl;
                        cout << endl;
                        continue;
                    } else {
                        empRole = strTest;
                    }
                    break;
                }

                strTest = "";
                // cin.ignore(123, '\n'); // ignore the leftover newline character
                while (true) {
                    cout << "Enter employee department: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest.length() < 5) {
                        strTest = upperCase(strTest);
                    } else {
                        strTest = titleCase(strTest);
                    }
                    if (strTest == "" || !isSubstr(strTest+",", constants::DEPARTMENTS)) {
                        cout << endl;
                        cout << "Invalid input. Please enter a valid department from: " << constants::DEPARTMENTS << endl;
                        cout << endl;
                        continue;
                    } else {
                        empDepartment = strTest;
                    }
                    break;
                }

                cin.ignore(123, '\n'); // ignore the leftover newline character
                while (true) {
                    strTest = "";
                    cout << "Enter employee salary: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest == "" || !check_num(strTest) || stoi(strTest) <= 0) {
                        cout << endl;
                        cout << "Invalid input. Please enter a valid number for salary." << endl;
                        cout << endl;
                        continue;
                    } else {
                        empSalary = stoi(strTest);
                        break;
                    }
                }

                strTest = "";
                // cin.ignore(); // ignore the leftover newline character
                while (true) {
                    strTest = "";
                    cout << "Enter employee Email: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest == "") {
                        cout << endl;
                        cout << "Invalid input. Please enter a valid email: 'jane.doe@anyco.com' ." << endl;
                        cout << endl;
                        continue;
                    } else {
                        empEmail = strTest;
                    }
                    break;
                }

                strTest = "";
                // cin.ignore(); // ignore the leftover newline character
                while (true) {
                    cout << "Enter password: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest == "" || strTest.length() < 8 || strTest.length() > 20 ) {
                        cout << endl;
                        cout << "Invalid input. Please enter a password between 8 and 20 characters." << endl;
                        cout << endl;
                        continue;
                    } else {
                        empPassword = strTest;
                    }
                    break;
                }

                empId = hr.addEmployee(employees, empName, empId, empRole, empDepartment, empSalary, empEmail, empPassword);
                cout << endl;
                manager.search(employees, empId);
                cout << endl;
                cout << "Employee # " << empId << " successfully added." << endl;
                cout << endl;
            }
            else if (choice == 4) {
                // Update employee
                cout << endl;
                cout << "Enter ID of employee to update: ";
                // getline(cin, empId);
                cin >> empId;
                cout << endl;
                empIndex = manager.search(employees, empId);
                if (empIndex == -1) {
                    continue;
                };
                cout << endl;

                strTest = "";
                cin.ignore(123, '\n'); // ignore the leftover newline character
                cout << "Update name (Press 'enter' to leave unchanged): ";
                getline(cin, strTest);
                // cin >> strTest;
                if (strTest != "") {
                    empName = titleCase(strTest);
                } else {
                    empName = employees[empIndex].getName();
                }

                strTest = "";
                // cin.ignore(123, '\n'); // ignore the leftover newline character
                while (true) {
                    cout << "Update employee role ('Employee', 'Manager', or 'HR'), or press 'enter' to leave unchanged: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest.length() < 5) {
                        strTest = upperCase(strTest);
                    } else {
                        strTest = titleCase(strTest);
                    }
                    if (strTest == "") {
                        empRole = employees[empIndex].getRole();
                        break;
                    } else if (!isSubstr(strTest+",", constants::ROLES)) {
                        cout << endl;
                        cout << "Invalid input. Please enter a valid role from: " << constants::ROLES << endl;
                        cout << endl;
                        continue;
                    } else {
                        empRole = strTest;
                    }
                    break;
                }

                // cin.ignore(123, '\n'); // ignore the leftover newline character
                strTest = "";
                while (true) {
                    cout << "Update employee department, or press 'enter' to leave unchanged: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest.length() < 5) {
                        strTest = upperCase(strTest);
                    } else {
                        strTest = titleCase(strTest);
                    }
                    if (strTest == "") {
                        empDepartment = employees[empIndex].getDepartment();
                        break;
                    } else if (!isSubstr(strTest+",", constants::DEPARTMENTS)) {
                        cout << endl;
                        cout << "Invalid input. Please enter a valid department from: " << constants::DEPARTMENTS << endl;
                        cout << endl;
                        continue;
                    } else {
                        empDepartment = strTest;
                    }
                    break;
                }

                cin.ignore(123, '\n'); // ignore the leftover newline character
                strTest = "";
                while (true) {
                    cout << "Update employee salary, or press 'enter' to leave unchanged: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest == "") {
                        empSalary = employees[empIndex].getSalary();
                        break;
                    } else if ( !check_num(strTest) || stoi(strTest) <= 0) {
                        cout << endl;
                        cout << "Invalid input. Please enter a valid salary" << endl;
                        cout << endl;
                        continue;
                    } else {
                        empSalary = stoi(strTest);
                    }
                    break;
                }

                strTest = "";
                // cin.ignore(); // ignore the leftover newline character
                cout << "Update email (Press 'enter' to leave unchanged): ";
                getline(cin, strTest);
                // cin >> strTest;
                if (strTest != "") {
                    empEmail = strTest;
                } else {
                    empEmail = employees[empIndex].getEmail();
                }

                strTest = "";
                // cin.ignore(123, '\n'); // ignore the leftover newline character
                while (true) {
                    cout << "Update password, or press 'enter' to leave unchanged: ";
                    getline(cin, strTest);
                    // cin >> strTest;
                    if (strTest == "") {
                        empPassword = employees[empIndex].getPassword();
                        break;
                    } else if (strTest.length() < 8 || strTest.length() > 20 ) {
                        cout << endl;
                        cout << "Invalid input. Please enter a password between 8 and 20 characters." << endl;
                        cout << endl;
                        continue;
                    } else {
                        empDepartment = strTest;
                    }
                    break;
                }

                hr.updateEmployee(employees, empName, empId, empRole, empDepartment, empSalary, empEmail, empPassword);
                cout << endl;
                manager.search(employees, empId);
                cout << endl;
                cout << "Employee # " << empId << " successfully updated." << endl;
                cout << endl;
            }
            else if (choice == 5) {
                cout << "Enter employee ID: ";
                cin >> empId;
                hr.deleteEmployee(employees, empId);
                cout << endl;
                manager.search(employees, empId);
                cout << endl;
                cout << "Employee # " << empId << " successfully added." << endl;
                cout << endl;
            }
            else if (choice == 6) {
                cout << "Logging out and exiting..." << endl;
                break;
            }
            else {
                cout << "Invalid choice." << endl;
            }
        }
        else {
            isLoggedin = false;
            empRole = "Invalid";
            int choice;
            cout << "Invalid login. Please enter 1 to login again, or 2 to exit: ";
            cin >> choice;
            cout << endl;

            if (choice == 1) {
                continue;
            } else {
                cout << "Logging out and exiting..." << endl;
                break;
            }
        }
    }

    return 0;
}
