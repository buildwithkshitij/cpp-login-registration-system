#include <iostream>
#include <fstream>
using namespace std;

class temp
{
    string Username, Email, Password;
    string searchUsername, searchPassword;
    fstream file;

public:
    void login();
    void signup();
    void forgot();
} obj;

int main()
{
    char choice;
    cout << "\n1- login";
    cout << "\n2- Sign-up";
    cout << "\n3- Forgot password";
    cout << "\n4- Exit";
    cout << "\nEnter your choice: ";
    cin >> choice;

    switch (choice)
    {
    case '1':
        cout << "\nYou have chosen to login.";
        break;
    case '2':
        cout << "\nYou have chosen to sign-up.";
        break;
    case '3':
        cout << "\nYou have chosen to recover your password.";
        break;
    case '4':
        cout << "\nExiting the program.";
        break;
    default:
        cout << "\nInvalid choice. Please try again.";
        return 0;
    }
}
void temp::signup()
{
    cout << "\nEnter your username: ";
    cin >> Username;
    cout << "\nEnter your email: ";
    cin >> Email;
    cout << "\nEnter your password: ";
    cin >> Password;

    file.open("records.txt", ios::out | ios::app);
    file << Username << "*" << Email << "*" << Password << endl;
    file.close();
    cout << "\nAccount created successfully!";
}

void temp::login()
{
    cout << "-------------LOGIN-------------";
    cout << "\nEnter your username: ";
    cin >> searchUsername;
    cout << "\nEnter your password: ";
    cin >> searchPassword;

    file.open("records.txt", ios::in);
    bool found = false;
    while (getline(file, Username, '*') &&
           getline(file, Email, '*') &&
           getline(file, Password, '\n'))
    {
        if (Username == searchUsername && Password == searchPassword)
        {
            found = true;
            break;
        }
    }
    file.close();

    if (found)
        cout << "\nLogin successful!";
    else
        cout << "\nInvalid username or password.";
}
void temp::forgot()
{
    cout << "-------------FORGOT PASSWORD-------------";
    cout << "\nEnter your username: ";
    cin >> searchUsername;

    file.open("records.txt", ios::in);
    bool found = false;
    while (getline(file, Username, '*') &&
           getline(file, Email, '*') &&
           getline(file, Password, '\n'))
    {
        if (Username == searchUsername)
        {
            found = true;
            break;
        }
    }
    file.close();

    if (found)
        cout << "\nYour password is: " << Password;
    else
        cout << "\nUsername not found.";
}
