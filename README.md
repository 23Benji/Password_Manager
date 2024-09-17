![Screenshot](img/Screenshot1.png)
# Password Manager

A command-line-based password manager written in C. This application allows users to securely store, manage, and retrieve their passwords. It also includes functionalities such as adding new passwords, editing existing ones, deleting passwords, and generating strong random passwords. All passwords are encrypted and stored in a text file for security.

## Features

- **Add Password:** Save a new password along with the associated website and username.
- **View Passwords:** Search for and retrieve passwords based on the website name.
- **Edit Password:** Modify existing password entries without revalidating the old password.
- **Delete Password:** Remove saved passwords from the file.
- **Generate Password:** Create a strong, random password to use for your accounts.
- **Encryption:** All stored passwords are encrypted in the text file.

  
## How It Works

1. The password manager allows you to:
   - Add a new password entry by specifying a website, username, and password.
   - Edit an existing entry by searching for the website name and updating the details.
   - View all your saved passwords or search for a specific one by website.
   - Delete passwords if they are no longer needed.
   
2. **Encryption**: Passwords are encrypted before being saved to the text file, ensuring that they are not stored in plain text.

3. **Search Functionality**: Easily find passwords by searching for the website name.

## Usage

1. Clone the repository:
    ```bash
    git clone https://github.com/yourusername/password-manager.git
    ```
2. Navigate to the project folder:
    ```bash
    cd password-manager
    ```
2. Navigate to the Verion folder:
    ```bash
    cd Version_1.0
    ```   
     ```bash
    cd Version_2.0
    ```
   ```bash
    cd Version_2.1
    ```
4. Run the Makefile:
    ```bash
    make
    ```
## Future Enhancements
   
- **Password Strength Checker**: Implement a feature to assess the strength of user-provided passwords.
- **Multiple File Support**: Allow users to manage different sets of passwords across multiple files.

## Requirements

- A **C compiler** (e.g., GCC)
- **Basic understanding** of command-line usage

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
