#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <ctime>

using namespace std;

string g_usr;
string g_pwd;
const char xorKey = '43';


void generate_password();

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
