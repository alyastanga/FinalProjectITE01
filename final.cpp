#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime> 
#include <limits>
using namespace std;

struct Ticket
{
    string studentName, studentId, concern, date, professor, status, role;
};

void registerUser();
void login();
void retrievePassword();
void userInterface();
void addTickets();
void resolveTicket();
void viewTickets();
void studentsInterface();
void professorsInterface();
void notification();
void clearscreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/Mac
    #endif
}

int main() {
    int choice;
    do
    {
    cout << "--------------------------------------\n";
    cout << "                 Welcome              \n";
    cout << "           Precious University        \n";
    cout << "               Students Inq           \n";
    cout << "\nMenu \n";
    cout << "\n\n1. Login\n2. Register\n3. Forgot Password\n4. Exit\n";
    cout << "Enter the number of your choice: ";
    cin>> choice;

    switch (choice)
        {
            case 1: login();
            break;
            case 2: registerUser();
            break;
            case 3: retrievePassword();
            break;
            case 4: clearscreen();
            cout<<"Thank you for using our system!\n";
            exit(0);
            break;
            default: cout<<"Invalid input!\n";
        }
    }
    while(choice != 4);
    return 0;
}

class User {
private: 
    string username, password, role, sid;
public:
    User(): username(""), password(""), role(""), sid("") {}
    User(string uname, string pass, string r, string id) : username(uname), password(pass), role(r), sid(id) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    string getSid() const { return sid; }

    void setUsername() {
        cin >> username;
    }

    void setPassword() {
        cin >> password;
    }

    void setRole(const string& r) { 
        role = r;
    }

    void setSid() {
        cin >> sid;
    }
};

User user;
Ticket ticket;
void registerUser() {
    cout << "Enter username: "; user.setUsername();
    cout << "Enter password: "; user.setPassword();
    string roleInput;
    cout << "Enter role ((s)student/(p)professor): ";
    cin >> roleInput;
    user.setRole(roleInput); 
    cout << "Enter student no. if professor enter 0: "; user.setSid();

    ofstream reg("accounts.txt", ios::app);
    if (reg.is_open()) {
        reg << user.getUsername() << "\t" << user.getPassword() << "\t" << user.getRole() << "\t" << user.getSid() << endl;
        reg.close();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        clearscreen();
        cout << "Registration Successful!\n";
    }
}


void login() {   
    int r;
    cout << "Choose: \n1. Student\n2. Professor\n";
    cin >> r;
    switch (r) {
        case 1: {  // Student login
            int count = 0;
            string id, pass;
            string lpass, lrole, studentId;
            cout << "Enter username: "; cin >> id;
            cout << "Enter Password: "; cin >> pass;

            ifstream input("accounts.txt");
            if (input.is_open()) {   
                while (input >> ticket.studentName >> lpass >> lrole >> studentId) {
                    if (ticket.studentName == id && lpass == pass) {
                        user.setRole(lrole); // Set the role after successful login
                        count = 1;
                        clearscreen();
                        break;
                    }
                }
                input.close();
                if (count == 1) {
                    cout << "Login Successful!\n";
                    studentsInterface(); // Navigate to student interface
                } else {
                    cout << "Invalid username or password!\n";
                }
            }
        }
        break;

        case 2: {  // Professor login
            int count = 0;
            string id, pass;
            string lpass, lrole, lid;
            cout << "Enter username: "; cin >> id;
            cout << "Enter Password: "; cin >> pass;

            ifstream input("accounts.txt");
            if (input.is_open()) {   
                while (input >> ticket.professor >> lpass >> lrole >> lid) {
                    if (ticket.professor == id && lpass == pass) {
                        user.setRole(lrole); // Set the role after successful login
                        count = 1;
                        clearscreen();
                        break;
                    }
                }
                input.close();
                if (count == 1) {
                    cout << "Login Successful!\n";
                    professorsInterface(); // Navigate to professor interface
                } else {
                    cout << "Invalid username or password!\n";
                }
            }
        }
        break;

        default: 
            cout << "Invalid choice!\n";
            login(); // Re-prompt for login
            break;
    }
}


void retrievePassword()
{
    int count = 0;
    string fuse, user, pass, role, sid;
    cout<<"Enter username: "; cin>>fuse;

    ifstream ret("accounts.txt");
    if(ret.is_open())
    {
        while(ret>> user>>pass>>role>>sid)
        {
            if(user == fuse)
            {
                count = 1;
                break;
            }
        }
        ret.close();
    }
    if (count == 1){
        cout<<"Your password is: "<<pass<<endl;
    }
    else{
        cout<<"Username not found!\n";
    }
}

void studentsInterface() {
    int action;
    cout << "Welcome, student " << ticket.studentName << endl;
    cout << "1. Create Ticket\n2. View Tickets\n3. Logout\n";
    cout << "Enter the number of your choice: ";
    cin >> action;
    
    switch (action) {
        case 1: addTickets(); 
        break;
        case 2: viewTickets();
        break;  
        case 3: cout << "Logging out...\n"; 
        main();
        clearscreen(); 
        break;
        default: cout << "Invalid input!\n"; studentsInterface(); 
        break;
    }
}

void professorsInterface()
{
    int action;
    cout<<"Welcome, professor "<<ticket.professor<<endl;
    cout<<"1. View Ticket\n2. Resolve Tickets\n3. Logout\n";
    cout<<"Enter the number of your choice: ";
    cin>>action;

    switch(action){
        case 1: viewTickets();
        break;
        case 2: resolveTicket();
        break;
        case 3: cout<<"Logging out...\n";
        main();
        clearscreen();
        break;
        default: cout<<"Invalid input!\n";
        professorsInterface();
        break;
    }
}

void viewTickets() {
    string username = user.getUsername();
    string role = user.getRole();
    string line;

    if (role == "s") {  // Student view
        string filename = ticket.studentName + "_tickets.txt";
        ifstream viewfile(filename);
        if (viewfile.is_open()) {
            cout << "\n--- Your Tickets ---\n";
            cout << "----------------------------------------\n";
            while (getline(viewfile, line)) {
                cout << line << endl;
            }
            viewfile.close();
        } else {
            cout << "Unable to open file.\n";
        }

        cout << "----------------------------------------\n";
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        studentsInterface();
    } else if (role == "p") {  // Professor view
        string filename = ticket.professor + "_tickets.txt";
        ifstream ticketFiles(filename);
        if (ticketFiles.is_open()) {
            cout << "\n--- Tickets Assigned to You ---\n";
            cout << "----------------------------------------\n";
            while (getline(ticketFiles, line)) {
                cout << line << endl;
            }
            ticketFiles.close();
        } else {
            cout << "Error opening the tickets file.\n";
        }

        cout << "----------------------------------------\n";
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        professorsInterface();
    } else {
        cout << "Invalid role.\n";
    }
}

void addTickets(){
    //Aby gael
    //dapat bawat students may kanya kanyang text file tapos dun naka store yung mga concerns nila
    //(student name, id, concern, date&time (if possible), professor, status(open/resolved))
    //dapat may unique id yung bawat ticket
    
}

void resolveTicket(){
    //Kurt raneses
    //void resolveTicket() {
    }
    
void notifTickets() {
    string username = user.getUsername();  
    string role = user.getRole(); 
    string studentName, studentId, concern, date, ticketStatus, assignedProfessor;
    int newTicketCount = 0;

    if (role == "s") { 
       
        string studentFile = username + "_tickets.txt";
        ifstream ticketFile(studentFile);

        if (ticketFile.is_open()) {
            while (ticketFile >> studentName >> concern >> date >> assignedProfessor >> ticketStatus) {
                if (ticketStatus == "resolved") {
                    newTicketCount++;  
                }
            }
            ticketFile.close();

            if (newTicketCount > 0) {
                cout << "\nYou have " << newTicketCount << " resolved ticket(s)!\n";
            } else {
                cout << "\nNo resolved tickets at the moment.\n";
            }
        } else {
            cout << "Error opening your tickets file.\n";
        }
    } else if (role == "p") { 
       
        string professorFile = username + "_tickets.txt";
        ifstream ticketFile(professorFile);

        if (ticketFile.is_open()) {
            while (ticketFile >> studentName >> studentId >> concern >> date >> ticketStatus) {
                if (ticketStatus == "open") {
                    newTicketCount++;  
                }
            }
            ticketFile.close();

            if (newTicketCount > 0) {
                cout << "\nYou have " << newTicketCount << " new tickets to resolve!\n";
            } else {
                cout << "\nNo new tickets at the moment.\n";
            }
        } else {
            cout << "Error opening your tickets file.\n";
        }
    } else {
        cout << "Invalid role!\n";
    }
}
