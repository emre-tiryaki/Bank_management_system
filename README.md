# Bank Management System

## Description

This program is a simple bank management system. Users can create new accounts, view their accounts, deposit money, withdraw money, and send money to another account.

## Compilation and Execution

This program is written in the C language. Follow the steps below to compile and run it:

1. **Compilation:**
   - You can compile it using GCC (GNU Compiler Collection).
   - Open a terminal or command prompt and type the following command:
     ```
     gcc bank_management_system.c -o bank_management_system
     ```

2. **Execution:**
   - If the compilation is successful, run the program using the following command:
     ```
     ./bank_management_system
     ```

## Usage

- When the program starts, the user is presented with options in the main menu.
- To create a new account, use option "1".
- To view account information, use option "2".
- To deposit money, use option "3".
- To withdraw money, use option "4".
- To send money to another account, use option "5".
- To exit, use option "6".

## Account Activities

Each account is stored in a file to keep track of user transactions. The files are stored under the "user_story" directory.

## Important Notes

- The program should handle sensitive information such as usernames, account numbers, and passwords with care.
- Special attention should be given to the security of files storing account activities.

## Contributing

If you find a bug or have suggestions for improving the program, please open an issue or submit a pull request.
