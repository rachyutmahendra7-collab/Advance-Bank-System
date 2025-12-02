# Advanced Bank Management System (C++)

## Project Overview
This is a console-based **Bank Management System** in C++, demonstrating mastery of:

- **Object-Oriented Programming (OOP)**
- **Inheritance & Polymorphism**
- **Virtual functions and dynamic_cast**
- **Vectors for dynamic account storage**
- **Exception handling**
- **Password authentication & transaction history**

---

## Features

1. **Multiple Account Types**
   - Savings Account (with interest rate)
   - Checking Account (with overdraft protection)

2. **User Authentication**
   - Accounts require a password for deposits, withdrawals, and transaction viewing

3. **Transaction History**
   - All deposits, withdrawals, and interest applications are stored and viewable

4. **Polymorphism & dynamic_cast**
   - Interest applies only to Savings Accounts
   - Virtual functions for deposit, withdraw, and printInfo

5. **Exception Handling**
   - Invalid deposits/withdrawals are caught
   - Overdraft limits enforced

6. **Menu-driven Console**
   - Interactive menu for easy operation

---

## How to Run

g++ -std=c++17 -o BankSystem ConsoleApplication1/ConsoleApplication1.cpp && ./BankSystem

