#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>

using namespace std;

struct Ticket {
    int id;
    string student_name;
    string professor_name;
    string concern;
    string status;
};

class User {
private:
    string username;
    string password;
    string role;

public:
    User() : username(""), password(""), role("") {} // Default constructor

    User(string uname, string pwd, string r) : username(uname), password(pwd), role(r) {}

    string getUsername() const { // Marked as const
        return username;
    }

    string getPassword() const { // Marked as const
        return password;
    }

    string getRole() const { // Marked as const
        return role;
    }
};

unordered_map<string, User> users;

void loadUsers() {
    ifstream infile("users.txt");
    string uname, pwd, role;
    while (infile >> uname >> pwd >> role) {
        users[uname] = User(uname, pwd, role);
    }
    infile.close();
}

void saveUser(const User& user) {
    ofstream outfile("users.txt", ios_base::app);
    outfile << user.getUsername() << " " << user.getPassword() << " " << user.getRole() << endl;
    outfile.close();
}

void registerUser() {
    string username, password, role;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;
    cout << "Enter role (student/professor): ";
    cin >> role;

    if (users.find(username) != users.end()) {
        cout << "Username already exists. Try a different one." << endl;
    } else {
        User newUser(username, password, role);
        users[username] = newUser;
        saveUser(newUser);
        cout << "User registered successfully!" << endl;
    }
}

User* loginUser() {
    string username, password;
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    if (users.find(username) != users.end() && users[username].getPassword() == password) {
        cout << "Login successful!" << endl;
        return &users[username];
    } else {
        cout << "Invalid username or password." << endl;
        return nullptr;
    }
}

// Function to display tickets addressed to a specific professor or created by a specific student
void displayTickets(const string& name, const string& role) {
    ifstream infile("tickets.txt");
    string line;

    if (role == "professor") {
        cout << "Tickets addressed to Professor " << name << ":\n";
    } else if (role == "student") {
        cout << "Tickets created by Student " << name << ":\n";
    }

    while (getline(infile, line)) {
        if (line.find(name) != string::npos) {
            cout << line << endl;
        }
    }
    infile.close();
}

// Function to add a ticket
void addTicket(const User& user) {
    Ticket new_ticket;
    ofstream outfile("tickets.txt", ios_base::app);  // Append mode

    new_ticket.student_name = user.getUsername();
    cout << "Enter professor name: ";
    cin >> new_ticket.professor_name;
    cout << "Enter concern: ";
    cin.ignore();
    getline(cin, new_ticket.concern);

    new_ticket.status = "open";
    outfile << new_ticket.student_name << ", " << new_ticket.professor_name << ", "
            << new_ticket.concern << ", " << new_ticket.status << endl;
    outfile.close();

    // Log the new ticket in a separate file for the professor
    ofstream prof_outfile(new_ticket.professor_name + "_notifications.txt", ios_base::app);
    prof_outfile << new_ticket.student_name << ", " << new_ticket.professor_name << ", "
                 << new_ticket.concern << ", " << new_ticket.status << endl;
    prof_outfile.close();

    cout << "Ticket created successfully!\n";
}

void checkNewTickets(const string& professor_name) {
    ifstream infile(professor_name + "_notifications.txt");
    string line;

    cout << "New Tickets for Professor " << professor_name << ":\n";
    while (getline(infile, line)) {
        cout << line << endl;
    }
    infile.close();

    // Clear the notifications file after displaying the tickets
    ofstream outfile(professor_name + "_notifications.txt", ios_base::trunc);
    outfile.close();
}
// Function to mark ticket as resolved (Professor)
void resolveTicket() {
    ifstream infile("tickets.txt");
    ofstream temp("temp.txt");
    string line;
    string ticket_to_resolve;

    cout << "Enter the name of the student whose ticket you want to resolve: ";
    cin >> ticket_to_resolve;

    while (getline(infile, line)) {
        if (line.find(ticket_to_resolve) != string::npos) {
            cout << "Resolving ticket for " << ticket_to_resolve << endl;
            line.replace(line.find("open"), 4, "resolved");
        }
        temp << line << endl;
    }

    infile.close();
    temp.close();
    remove("tickets.txt");
    rename("temp.txt", "tickets.txt");

    cout << "Ticket resolved successfully!\n";
}

int main() {
    loadUsers();
    User* loggedInUser = nullptr;
    int choice;

    while (true) {
        if (loggedInUser == nullptr) {
            cout << "1. Register\n2. Login\n3. Exit\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    registerUser();
                    break;
                case 2:
                    loggedInUser = loginUser();
                    if (loggedInUser && loggedInUser->getRole() == "professor") {
                        checkNewTickets(loggedInUser->getUsername());
                    }
                    break;
                case 3:
                    exit(0);
                    break;
                default:
                    cout << "Invalid option. Please try again.\n";
            }
        } else {
            cout << "1. Display Tickets (Professor)\n2. Add Ticket (Student)\n3. Resolve Ticket (Professor)\n4. Display My Tickets (Student)\n5. Logout\n";
            cin >> choice;

            switch (choice) {
                case 1:
                    if (loggedInUser->getRole() == "professor") {
                        displayTickets(loggedInUser->getUsername(), "professor");
                    } else {
                        cout << "Only professors can view tickets addressed to them.\n";
                    }
                    break;
                case 2:
                    if (loggedInUser->getRole() == "student") {
                        addTicket(*loggedInUser);
                    } else {
                        cout << "Only students can add tickets.\n";
                    }
                    break;
                case 3:
                    if (loggedInUser->getRole() == "professor") {
                        resolveTicket();
                    } else {
                        cout << "Only professors can resolve tickets.\n";
                    }
                    break;
                case 4:
                    if (loggedInUser->getRole() == "student") {
                        displayTickets(loggedInUser->getUsername(), "student");
                    } else {
                        cout << "Only students can view their own tickets.\n";
                    }
                    break;
                case 5:
                    loggedInUser = nullptr;
                    break;
                default:
                    cout << "Invalid option. Please try again.\n";
            }
        }
    }
}