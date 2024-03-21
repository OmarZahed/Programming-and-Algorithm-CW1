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

void login() {
    
}
void _register() {
}
void delete_user() {
    
}
void _quit() {
    
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
