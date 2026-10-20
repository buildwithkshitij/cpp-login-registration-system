#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <cctype>

using namespace std;

class temp
{
private:
    string Username, Email, Password;
    string searchUsername, searchPassword, searchEmail;
    fstream file;

    // Check whether a username already exists
    bool usernameExists(const string &username)
    {
        ifstream inputFile("records.txt");

        if (!inputFile)
            return false;

        string user, email, password;

        while (getline(inputFile, user, '*') &&
               getline(inputFile, email, '*') &&
               getline(inputFile, password))
        {
            if (!password.empty() && password.back() == '\r')
                password.pop_back();

            if (user == username)
                return true;
        }

        return false;
    }

public:
    void login();
    void signup();
    void forgot();
};

int main()
{
    temp obj;
    char choice;

    do
    {
        cout << "\n\n================================";
        cout << "\n       LOGIN SYSTEM";
        cout << "\n================================";
        cout << "\n1. Login";
        cout << "\n2. Sign Up";
        cout << "\n3. Forgot Password";
        cout << "\n4. Exit";
        cout << "\n================================";
        cout << "\nEnter your choice: ";

        cin >> choice;

        switch (choice)
        {
        case '1':
            obj.login();
            break;

        case '2':
            obj.signup();
            break;

        case '3':
            obj.forgot();
            break;

        case '4':
            cout << "\nThank you for using the Login System!";
            break;

        default:
            cout << "\nInvalid choice. Please select 1-4.";
        }

    } while (choice != '4');

    return 0;
}

// ================= SIGN UP =================

void temp::signup()
{
    cout << "\n========== SIGN UP ==========";

    cout << "\nEnter username: ";
    cin >> Username;

    cout << "Enter email: ";
    cin >> Email;

    cout << "Enter password: ";
    cin >> Password;

    // Basic input validation
    if (Username.find('*') != string::npos ||
        Email.find('*') != string::npos ||
        Password.find('*') != string::npos)
    {
        cout << "\nThe character '*' is not allowed.";
        return;
    }

    if (Username.empty() || Email.empty() || Password.empty())
    {
        cout << "\nFields cannot be empty.";
        return;
    }

    // Validate basic email format
    size_t at = Email.find('@');
    size_t dot = Email.find('.', at == string::npos ? 0 : at);

    if (at == string::npos ||
        at == 0 ||
        dot == string::npos ||
        dot <= at + 1 ||
        dot == Email.length() - 1)
    {
        cout << "\nPlease enter a valid email address.";
        return;
    }

    // Prevent duplicate usernames
    if (usernameExists(Username))
    {
        cout << "\nUsername already exists. Please choose another.";
        return;
    }

    file.open("records.txt", ios::out | ios::app);

    if (!file)
    {
        cout << "\nError: Unable to open records.txt.";
        return;
    }

    file << Username << "*"
         << Email << "*"
         << Password << '\n';

    file.close();

    cout << "\nRegistration successful!";
    cout << "\nYou can now log in.";
}

// ================= LOGIN =================

void temp::login()
{
    cout << "\n========== LOGIN ==========";

    cout << "\nEnter username: ";
    cin >> searchUsername;

    cout << "Enter password: ";
    cin >> searchPassword;

    ifstream inputFile("records.txt");

    if (!inputFile)
    {
        cout << "\nNo user records found. Please sign up first.";
        return;
    }

    bool found = false;
    string user, email, password;

    while (getline(inputFile, user, '*') &&
           getline(inputFile, email, '*') &&
           getline(inputFile, password))
    {
        if (!password.empty() && password.back() == '\r')
            password.pop_back();

        if (user == searchUsername &&
            password == searchPassword)
        {
            found = true;
            break;
        }
    }

    inputFile.close();

    if (found)
        cout << "\nLogin successful! Welcome, " << searchUsername << "!";
    else
        cout << "\nInvalid username or password.";
}

// ================= FORGOT PASSWORD =================

void temp::forgot()
{
    cout << "\n====== PASSWORD RECOVERY ======";

    cout << "\nEnter username: ";
    cin >> searchUsername;

    cout << "Enter registered email: ";
    cin >> searchEmail;

    ifstream inputFile("records.txt");

    if (!inputFile)
    {
        cout << "\nNo user records found. Please sign up first.";
        return;
    }

    bool found = false;
    string user, email, password;

    while (getline(inputFile, user, '*') &&
           getline(inputFile, email, '*') &&
           getline(inputFile, password))
    {
        if (!password.empty() && password.back() == '\r')
            password.pop_back();

        if (user == searchUsername && email == searchEmail)
        {
            found = true;
            break;
        }
    }

    inputFile.close();

    if (found)
    {
        cout << "\nAccount verified successfully.";
        cout << "\nYour password is: " << password;
    }
    else
    {
        cout << "\nUsername or email does not match.";
    }
}