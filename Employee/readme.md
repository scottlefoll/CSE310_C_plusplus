# EmployeeSoft Employee Management Program for Windows Desktop - written in C++ using OOP design.

# Overview

EmployeeSoft is a basic employe managemeent program that records some basic features about an employee (name, email, password, position, role, salary). It uses a login system based on a users email and password, and then shows a basic ASCII menu to the user based upon the user's role. The roles are Employee, Manager, and HR, and they have increasing levels of permissions.

The software is intended to show basic syntax, structures and design in OOP using the C++ language.

# Development Environment

The program is written in C++ using the g++ compiler, and and VS Code. The environment was Windows 10 Professional on an intel desktop.

## Requirements

Dependencies:

constants.h
<conio.h>
<iostream>
<iomanip>
<sstream>
<string>
<vector>
<fstream>

The data files are written to a simple "employees.txt" file. If the file is not found in the home directory, it is created and populated with 10 sample records.

To test the system the first time, try logging in using the following user credentials:

email: tom.dillon@myco.com
password: 12345AB*

# Useful Websites

- [Programmiz C++](https://www.programiz.com/cpp-programming)
- [W3 Schools C++](https://www.w3schools.com/cpp/)
- [Tutorialspoint C++](https://www.tutorialspoint.com/cplusplus/index.htm)
- [Codecademy](https://www.codecademy.com/learn/learn-c-plus-plus)
_ [Geeks for Geeks C++](https://www.geeksforgeeks.org/c-plus-plus/)
- [Wiki C++](https://en.wikipedia.org/wiki/C%2B%2B)

# Future Work

These are items for future development and enhancement:

- Convert the manu over to a GUI using GTK or a similar graphics library/framework.
- Allow users to make setting changes to a file.
- Convert the data file to an SQL database.

## How to use the software
To start, just click on the employee.exe file. The menus are self-explanatory.

## Code Structure
The program is divided into several classes, each representing a game object:

Employee class
Manager class
HumanResources class
IO_Service class
Login class

## Video Demo

{Provide a link to your YouTube demonstration. It should be a 4-5 minute demo of the software running and a walkthrough of the code. Focus should be on sharing what you learned about the language syntax.}

[C++ Module 4 Demo Video](https://youtu.be/4NfSFD-q0A8)
