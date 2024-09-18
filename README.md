# AEGISCODE VAULT (Password Manager)

A versatile Password Manager built in C, designed to securely manage your passwords with various features and enhancements over its versions. This tool allows you to add, view, edit, and delete credentials, with additional functionalities introduced in later versions.

## Features Overview
- **Add Passwords**: Store new passwords for different websites.
- **View Passwords**: Access and review your saved credentials.
- **Edit Passwords**: Modify existing password entries.
- **Delete Passwords**: Remove unneeded credentials.
- **Generate Passwords**: Create new, random passwords.
- **Export Functionality**: Export decrypted passcodes for backup and sharing.
- **Access Code Protection**: Security with access codes required to start and use the program.

## Version Highlights

### Version 1.0
- **Core Functionalities**: Add, view, edit, delete, and generate passwords.
- **Encryption**: Uses Caesar cipher for storing passwords securely.

### Version 2.0
- **Enhanced Security**: Introduces access code protection for starting the program and viewing passcodes.
- **Existing Features**: Retains all features from Version 1.0 with added security measures.

### Version 2.1
- **Export Feature**: Adds functionality to export decrypted passwords to a text file.
- **Existing Features**: Includes all features from Version 2.0 with the new export capability.

### Version 3.0
- **Project Renaming**: Rebranded as AegisCode Vault.
- **Improved Security**: Enhanced encryption methods and overall security improvements.
- **Existing Features**: Includes all features from Version 2.1 with upgraded security.

## How It Works
The Password Manager encrypts passwords and saves them into a file, ensuring your data is secure. You can manage your passwords through a user-friendly interface, with encryption and export functionalities designed to protect and handle your data efficiently.

## Installation
To use the Password Manager, you'll need a C compiler installed.

1. Clone the repository:
    ```bash
    git clone https://github.com/23Benji/Password_Manager.git
    ```
2. Navigate to the project folder:
    ```bash
    cd Password_Manager
    ```
3. Navigate to the desired Verion:
    ```bash
    cd Version_[Version]
    ```
4. Run the makefile:
    ```bash
    make
    ```
    
## License
This project is licensed under the MIT License. See the `LICENSE` file for details.
