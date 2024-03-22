#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

string g_usr;
string g_pwd;
const char xorKey = '43';


void main_menu();
void login();
void _register();
void delete_user();
void _quit();
void _menu();
void add_platform_account();
void list_platform_accounts();
void generate_password();
string xorEncryptDecrypt(const string& input);

void generate_password() {
    const char charset[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"!@#$%^&*()_+-=[]{}|;:',.<>/?";
const size_t max_index = (sizeof(charset) - 1);
random_device rd;
mt19937 generator(rd());
uniform_int_distribution<> distribution(0, max_index - 1);

cout << "[?] How long do you want your password to be?" << endl;
int length;
cin >> length;

string password;
for (int i = 0; i < length; ++i) {
    password += charset[distribution(generator)];
}

string xorEncryptDecrypt(const string& input) {
    string output = input;
    for (size_t i = 0; i < input.size(); i++) {
        output[i] = input[i] ^ xorKey;
    }
    return output;
}

void login() {
    string l_name, l_pwd, encryptedPwd, decryptedPwd;
    bool found = false;

    cout << "[?] What is your username?" << endl;
    getline(cin >> ws, l_name);
    cout << "[?] What is your password?" << endl;
    getline(cin >> ws, l_pwd);

    ifstream account_file("users.pmd");
    if (!account_file.is_open()) {
        cout << "Failed to open user file." << endl;
        return;
    }

    string line;
    while (getline(account_file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string name = line.substr(0, commaPos);
            encryptedPwd = line.substr(commaPos + 1);
            decryptedPwd = xorEncryptDecrypt(encryptedPwd);

            if (l_name == name && l_pwd == decryptedPwd) {
                found = true;
                g_usr = l_name;
                g_pwd = l_pwd;
                break;
            }
        }
    }

    account_file.close();

    if (found) {
        cout << "Login successful!" << endl;
        _menu();
    }
    else {
        cout << "Incorrect username or password." << endl;
        main_menu();
    }
}


bool isValidPassword(const string& password) {
    
    if (password.length() < 7) {
        return false;
    }

    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasSpecialChar = false;

    
    string specialChars = "!@#$%^&*()_+-=[]{}|;:',.<>/?";

    
    for (char ch : password) {
        
        if (isupper(ch)) {
            hasUppercase = true;
        }
        
        else if (islower(ch)) {
            hasLowercase = true;
        }
        
        else if (specialChars.find(ch) != string::npos) {
            hasSpecialChar = true;
        }
    }

    
    return hasUppercase && hasLowercase && hasSpecialChar;
}

bool usernameExists(const string& username) {
    ifstream account_file("users.pmd");
    if (!account_file.is_open()) {
        cout << "Failed to open user file." << endl;
        return true; 
    }

    string line;
    while (getline(account_file, line)) {
        size_t commaPos = line.find(',');
        if (commaPos != string::npos) {
            string name = line.substr(0, commaPos);
            if (name == username) {
                return true; 
            }
        }
    }

    account_file.close();
    return false; 
}

void _register() {
    string name, pwd, encryptedPwd;

    bool usernameAccepted = false;
    while (!usernameAccepted) {
        cout << "[?] What will be your new username?" << endl;
        getline(cin >> ws, name);

       
        if (usernameExists(name)) {
            cout << "Username already exists. Please choose a different username." << endl;
        }
        else {
            usernameAccepted = true; 
        }
    }

    bool validPassword = false;
    while (!validPassword) {
        cout << "[?] What will be your new password?" << endl;
        getline(cin >> ws, pwd);

        if (isValidPassword(pwd)) {
            validPassword = true;
            encryptedPwd = xorEncryptDecrypt(pwd);
        }
        else {
            cout << "Invalid password. Must be at least 7 characters long, include an uppercase letter, a lowercase letter, and a special character." << endl;
        }
    }

    ofstream account_file("users.pmd", ios::app); 
    if (!account_file.is_open()) {
        cout << "Failed to open user file." << endl;
        return;
    }

    account_file << name << "," << encryptedPwd << endl;
    account_file.close();

    cout << "[+] Successfully created new user! Returning back to main menu..." << endl;
    main_menu();
}

void _quit() {
    cout << "Exiting the password manager." << endl;
    exit(0);
}


void add_platform_account() {
    
}
void list_plateform_accoumts() {
    
}



void _menu() {
    cout << "Welcome, " << g_usr << ". How can we help you today?" << endl;
    cout << "[1] Add a new platform account" << endl;
    cout << "[2] List all stored platform accounts" << endl;
    cout << "[3] Return to main menu" << endl;
    cout << "[4] Generate a secure password" << endl;

    string option;
    getline(cin >> ws, option);

    if (option == "1") {
        add_platform_account();
    }
    else if (option == "2") {
        list_platform_accounts();
    }
    else if (option == "3") {
        main_menu();
    }
    else if (option == "4") {
        generate_password();
    }
    else {
        cout << "Not a valid option... Please choose from 1 to 4!" << endl;
        _menu();
    }
}
void main_menu() {
    string option;

    cout << "Welcome to the password manager... Please select one of the options:" << endl;
    cout << "[1] Login with user" << endl;
    cout << "[2] Create new user" << endl;
    cout << "[3] Delete user" << endl;
    cout << "[4] Quit the password manager" << endl;

    getline(cin >> ws, option);

    if (option == "1") {
        login();
    }
    else if (option == "2") {
        _register();
    }
    else if (option == "3") {
        delete_user();
        cout << "Delete user functionality not implemented." << endl;
        main_menu();
    }
    else if (option == "4") {
        _quit();
    }
    else {
        cout << "Not a valid option... Please choose from 1 to 4!" << endl;
        main_menu();
    }
}

int main() {
    main_menu();
    return 0;
}
