#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <limits>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <numeric>
using namespace std;

struct Ticket
{
    string studentName, studentId, concern, date, professor, status, role, department, scheduledMeeting;
};
struct Sched
{
    string days[7] = {"Monday: ", "Tuesday: ", "Wednesday: ", "Thursday: ", "Friday: ", "Saturday: ", "Sunday: "};
    string time[7];
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
void notifTickets();
void Messenger();
void enroll();
void clearscreen()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Unix/Linux/Mac
#endif
}
void analytics();
void profSched();
void chooseProf();
void chooseDay();
void viewSched();

int main()
{
    clearscreen();
    int choice;
    cout << "========================================\n";
    cout << "=                Welcome               =\n";
    cout << "=          Precious University         =\n";
    cout << "=              Students Inq            =\n";
    cout << "========================================\n";
    while (true)
    {
        cout << "\nMenu: \n";
        cout << "\n (1) Login\n (2) Register\n (3) Forgot Password\n (4) Exit\n";
        cout << "\nMenu(#): ";
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid input! Please enter a number between 1 and 4.\n";
        }
        else
        {
            cin.ignore(); // Ignore the newline character left in the input buffer
            break;
        }
    }

    switch (choice)
    {
    case 1:
        clearscreen();
        login();
        break;
    case 2:
        clearscreen();
        registerUser();
        break;
    case 3:
        clearscreen();
        retrievePassword();
        break;
    case 4:
        clearscreen();
        cout << "Thank you for using our system!\n";
        exit(0);
        break;
    default:
        clearscreen();
        cout << "Invalid input!\n";
        main();
        break;
    }
}

class User
{
private:
    string username, password, role, sid, department;

public:
    User() : username(""), password(""), role(""), sid(""), department("") {}
    User(string uname, string pass, string r, string id, string d) : username(uname), password(pass), role(r), sid(id), department(d) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    string getSid() const { return sid; }
    string getDepartment() const { return department; }

    void setUsername(const string &u)
    { // Accepts a string argument
        username = u;
    }

    void setPassword()
    {
        cin >> password;
    }

    void setRole(const string &r)
    { // Accepts a string argument
        role = r;
    }

    void setDepartment(const string &d)
    { // Accepts a string argument
        department = d;
    }
    void setSid(const string &id)
    { // Accepts a string argument
        sid = id;
    }
};
struct Message
{
    string msg;
};

Message message;
User user;
Ticket ticket;
Sched sched;
void registerUser()
{
    cout << "Registration\n\n";
    string uname;
    cout << setw(3) << " " << "Enter username: ";
    getline(cin, uname);
    user.setUsername(uname);
    cout << setw(3) << " " << "Enter password: ";
    user.setPassword();

    char departmentInputInt;
    do
    {
        cout << setw(3) << " " << "Enter Department-Options(Enter # only):\n";
        cout << setw(3) << " " << "(1) College of Engineering and Architecture\n";
        cout << setw(3) << " " << "(2) College of Computer Studies\n";
        cout << setw(3) << " " << "(3) College of Business Education\n";
        cout << setw(3) << " " << "(4) College of Arts and Sciences\n";
        cout << setw(3) << " " << "Department: ";
        cin >> departmentInputInt;

        switch (departmentInputInt)
        {
        case '1':
            user.setDepartment("CEA");
            break;
        case '2':
            user.setDepartment("CCS");
            break;
        case '3':
            user.setDepartment("CBE");
            break;
        case '4':
            user.setDepartment("CAS");
            break;
        default:
            cout << "Invalid input!\n";
            break;
        }
    } while (departmentInputInt != '1' && departmentInputInt != '2' && departmentInputInt != '3' && departmentInputInt != '4');

    char roleInput;
    cout << "Enter role ((s)student/(p)professor): ";
    cin >> roleInput;
    string sidInput;
    switch (roleInput)
    {
    case 's':
        user.setRole("s");
        cout << setw(3) << " " << "Enter student no.: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, sidInput);
        user.setSid(sidInput);
        ticket.studentName = uname;
        break;
    case 'p':
        user.setRole("p");
        sidInput = "0";
        user.setSid(sidInput);
        ticket.professor = uname;
        profSched();
        break;
    default:
        cout << "Invalid input!\n";
        break;
    }

    ofstream reg("accounts.txt", ios::app);
    if (reg.is_open())
    {
        reg << user.getUsername() << setw(10) << user.getPassword() << setw(10) << user.getDepartment() << setw(10) << user.getRole() << setw(10) << user.getSid() << endl;
        reg.close();
        clearscreen();
        cout << "Registration Successful!\n";
        main();
    }
}

void login()
{
    cout << "Login\n\n";
    int count = 0;
    string id, pass;
    string lpass, luname, lrole;
    do
    {
        cout << setw(3) << " " << "Enter username: ";
        getline(cin, id);
        cout << setw(3) << " " << "Enter Password: ";
        getline(cin, pass);

        ifstream input("accounts.txt");
        if (!input.is_open())
        {
            clearscreen();
            cout << "Error: Unable to open the accounts file. Please ensure it exists.\n";
            return; // Exit the login function
        }

        if (input.is_open())
        {
            while (input >> luname >> lpass >> ticket.department >> ticket.role >> ticket.studentId)
            {
                if (luname == id && lpass == pass && ticket.role == "s")
                {
                    ticket.studentName = luname;
                    user.setUsername(luname);
                    user.setRole(ticket.role);
                    user.setDepartment(ticket.department);
                    clearscreen();
                    studentsInterface();
                    break;
                }
                else if (luname == id && lpass == pass && ticket.role == "p")
                {
                    ticket.professor = luname;
                    user.setUsername(luname);
                    user.setRole(ticket.role);
                    user.setDepartment(ticket.department);
                    clearscreen();
                    professorsInterface();
                    break;
                }
                else
                {
                    count = 1;
                    clearscreen();
                    cout << "Invalid username or password!\n";
                    cout << "Please try again.\n\n";
                }
            }
            input.close();
        }
    } while (count == 1);
}

void retrievePassword()
{
    int count = 0;
    string fuse, user, pass, role, sid;
    cout << "Enter username: ";
    cin >> fuse;

    ifstream ret("accounts.txt");
    if (ret.is_open())
    {
        while (ret >> user >> pass >> role >> sid)
        {
            if (user == fuse)
            {
                count = 1;
                break;
            }
        }
        ret.close();
    }
    if (count == 1)
    {
        cout << "Your password is: " << pass << endl;
    }
    else
    {
        cout << "Username not found!\n";
    }
}

void studentsInterface()
{
    int action;
    string departmentName = user.getDepartment();

    cout << "Welcome, student " << ticket.studentName << " of " << departmentName << endl;
    cout << "\n";
    while (true)
    {
        notifTickets();
        cout << "\n";
        cout << "Option: \n\n";
        cout << " (1) Create Ticket\n (2) View Tickets\n (3) Enroll\n (4) Message \n (5) Logout\n (6) Logout and Exit\n";
        cout << "\nOption(#): ";
        cin >> action;

        if (cin.fail())
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid input! Please enter a number between 1 and 3.\n";
        }
        else
        {
            cin.ignore(); // Ignore the newline character left in the input buffer
            break;
        }
    }

    switch (action)
    {
    case 1:
        clearscreen();
        addTickets();
        break;
    case 2:
        clearscreen();
        viewTickets();
        break;
    case 3:
        enroll();
        studentsInterface();
        break;
    case 4:
        clearscreen();
        Messenger();
        studentsInterface();
        break;
    case 5:
        cout << "Logging out...\n";
        clearscreen();
        main();
        break;
    case 6:
        clearscreen();
        cout << "Thank you for using our system!\n";
        exit(0);
        break;
    default:
        clearscreen();
        cout << "Invalid input!\n";
        studentsInterface();
        break;
    }
}

void professorsInterface()
{
    string departmentName = user.getDepartment();
    int action;
    cout << "Welcome, professor " << ticket.professor << " of " << departmentName << endl;
    cout << "\n";
    while (true)
    {
        notifTickets();
        cout << "\n";
        cout << "Option: \n\n";
        cout << " (1) View Ticket\n (2) Resolve Tickets\n (3) View Analytics \n (4) View Schedule \n (5) Message \n (6) Logout\n (7) Logout and Exit\n";
        cout << "\nOption(#): ";
        cin >> action;
        cout << "\n";

        if (cin.fail())
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid input! Please enter a number between 1 and 4.\n";
        }
        else
        {
            cin.ignore(); // Ignore the newline character left in the input buffer
            break;
        }
    }

    switch (action)
    {
    case 1:
        clearscreen();
        viewTickets();
        break;
    case 2:
        clearscreen();
        resolveTicket();
        break;
    case 3:
        clearscreen();
        analytics();
        break;
    case 4:
        clearscreen();
        viewSched();
        professorsInterface();
        break;
    case 5:
        clearscreen();
        Messenger();
        professorsInterface();
    case 6:
        clearscreen();
        cout << "Logging out...\n";
        main();
        break;
    case 7:
        clearscreen();
        cout << "Thank you for using our system!\n";
        exit(0);
        break;
    default:
        clearscreen();
        cout << "Invalid input!\n";
        professorsInterface();
        break;
    }
}

void viewTickets()
{
    string username = user.getUsername();
    string role = user.getRole();
    string line;

    if (role == "s")
    { // Student interface
        string filename = ticket.studentName + "_tickets.txt";
        ifstream viewfile(filename);
        if (viewfile.is_open())
        {
            cout << "\n--- Your Tickets ---\n";
            cout << "========================================\n";
            while (getline(viewfile, line))
            {
                cout << line << endl;
            }
            viewfile.close();
        }
        else
        {
            cout << "Unable to open file.\n";
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        clearscreen();
        studentsInterface();
    }
    else if (role == "p")
    { // Professor interface
        string filename = ticket.professor + "_tickets.txt";
        ifstream ticketFiles(filename);
        if (ticketFiles.is_open())
        {
            cout << "\n--- Tickets Assigned to You ---\n";
            cout << "========================================\n";
            while (getline(ticketFiles, line))
            {
                cout << line << endl;
            }
            ticketFiles.close();
        }
        else
        {
            cout << "Error opening the tickets file.\n";
        }
        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();
        clearscreen();
        professorsInterface();
    }
    else
    {
        cout << "Invalid role.\n";
    }
}

void addTickets()
{
    // Aby gael
    // dapat bawat students may kanya kanyang text file tapos dun naka store yung mga concerns nila
    //(student name, id, concern, date&time (if possible), professor, status(open/resolved))
    // dapat may unique id yung bawat ticket
    string concern, concern1, professor, departmentName;

    int concernChoice;
    char back;
    string additionalDetails;
    while (true)
    {
        cout << "Concern: \n\n";
        cout << " (1) Grades and Assessments\n";
        cout << " (2) Course Material and Content\n";
        cout << " (3) Assignment Deadlines and Extensions\n";
        cout << " (4) Class Schedule and Attendance\n";
        cout << " (5) Exam Schedules and Conflicts\n";
        cout << " (6) Feedback and Improvement\n";
        cout << " (7) Academic Advising\n";
        cout << " (8) Personal Issues Affecting Academic Performance\n";
        cout << " (9) Technical Issues\n";
        cout << " (10) General Inquiries\n\n";
        cout << "Concern(#): ";
        cin >> concernChoice;
        if (cin.fail() || concernChoice < 1 || concernChoice > 10)
        {
            cin.clear();                                         // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number between 1 and 10.\n\n";
        }
        else
        {
            cin.ignore(); // Ignore the newline character left in the input buffer
            break;
        }
    }
    switch (concernChoice)
    {
    case 1:
        concern = "Grades and Assessments";
        break;
    case 2:
        concern = "Course Material and Content";
        break;
    case 3:
        concern = "Assignment Deadlines and Extensions";
        break;
    case 4:
        concern = "Class Schedule and Attendance";
        break;
    case 5:
        concern = "Exam Schedules and Conflicts";
        break;
    case 6:
        concern = "Feedback and Improvement";
        break;
    case 7:
        concern = "Academic Advising";
        break;
    case 8:
        concern = "Personal Issues Affecting Academic Performance";
        break;
    case 9:
        concern = "Technical Issues";
        break;
    case 10:
        concern = "General Inquiries";
        break;
    default:
        cout << "Invalid Input!";
        addTickets();
        break;
    }

    cout << "\nEnter additional details about your concern: ";
    getline(cin, additionalDetails);

    // Continue with the rest of the code...

    // Get the current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", ltm);

    // ticketno
    srand(time(0));
    int ticketno = rand() % 1000 + 1;
    string ticketnoStr = to_string(ticketno);

    if (ticket.studentName.empty() || ticket.studentId.empty())
    {
        cout << "Error: Student name or ID is not initialized.\n";
        return;
    }
    chooseProf();
    chooseDay();
    string stufile = ticket.studentName + "_tickets.txt";
    ofstream ticketFile(stufile, ios::app);
    if (ticketFile.is_open())
    {
        ticketFile << "Department: " << ticket.department << endl;
        ticketFile << "Student: " << ticket.studentName << endl;
        ticketFile << "Student ID: " << ticket.studentId << endl;
        ticketFile << "Ticket ID: " << ticketno << endl;
        ticketFile << "Concern: " << concern << endl;
        ticketFile << "Additional Details: " << additionalDetails << endl;
        ticketFile << "Date of Inquiry: " << date << endl;
        ticketFile << "Scheduled Meeting: " << ticket.scheduledMeeting << endl;
        ticketFile << "Professor: " << ticket.professor << endl;
        ticketFile << "Status: open" << endl;
        ticketFile << "Date Resolved: " << "Pending" << endl; // New field for resolution timestamp
        ticketFile << "----------------------------------------" << endl;
        ticketFile.close();
        cout << "Ticket added successfully...\n";
    }
    else
    {
        cout << "Unable to open file.\n";
    }

    string profile = ticket.professor + "_tickets.txt";
    ofstream proticket(profile, ios::app);
    if (proticket.is_open())
    {
        proticket << "Department: " << ticket.department << endl;
        proticket << "Student: " << ticket.studentName << endl;
        proticket << "Student ID: " << ticket.studentId << endl;
        proticket << "Ticket ID: " << ticketno << endl;
        proticket << "Concern: " << concern << endl;
        proticket << "Additional Details: " << additionalDetails << endl;
        proticket << "Date of Inquiry: " << date << endl;
        proticket << "Scheduled Meeting: " << ticket.scheduledMeeting << endl;
        proticket << "Professor: " << ticket.professor << endl;
        proticket << "Status: open" << endl;
        proticket << "Date Resolved: " << "Pending" << endl;
        proticket << "----------------------------------------" << endl;
        proticket.close();
        cout << "Ticket sent to professor...\n";
    }
    else
    {
        cout << "Unable to open file.\n";
    }
    cout << "Press 'q' to return to Student Interface or any other key to create another ticket: ";
    char choice;
    cin >> choice;
    if (choice == 'q' || choice == 'Q')
    {
        clearscreen();
        addTickets(); 
    }
}

void resolveTicket()
{
    string linya;
    string filename = ticket.professor + "_tickets.txt";
    ifstream printTix(filename);
    if (printTix.is_open())
    {
        cout << "\n--- Tickets Assigned to You ---\n";
        cout << "========================================\n";
        while (getline(printTix, linya))
        {
            cout << linya << endl;
        }
        printTix.close();
    }
    else
    {
        cout << "Error opening the tickets file.\n";
    }

    string ticketId, studentName;
    cout << "Enter the ticket ID you want to resolve: ";
    cin >> ticketId;
    cout << "Enter the student name: ";
    cin >> studentName;

    // Capture resolution timestamp
    time_t now = time(0);
    char resolvedDate[20];
    strftime(resolvedDate, sizeof(resolvedDate), "%Y-%m-%d %H:%M:%S", localtime(&now));

    // Update Professor's File
    ifstream inputFile(ticket.professor + "_tickets.txt");
    ofstream tempFile("temp_tickets_prof.txt");
    bool found = false;

    if (inputFile.is_open() && tempFile.is_open())
    {
        string line;
        while (getline(inputFile, line))
        {
            if (line.find("Ticket ID: " + ticketId) != string::npos)
            {
                found = true;
                tempFile << line << endl; // Ticket ID

                for (int i = 0; i < 8; i++)
                {
                    getline(inputFile, line);
                    if (line.find("Status: open") != string::npos)
                    {
                        line.replace(line.find("open"), 4, "resolved");
                    }
                    else if (line.find("Date Resolved: Pending") != string::npos)
                    {
                        line.replace(line.find("Pending"), 7, resolvedDate); // Add Date Resolved
                    }
                    tempFile << line << endl; // Write the updated line
                }
            }
            else
            {
                tempFile << line << endl; // Copy unchanged lines
            }
        }
        inputFile.close();
        tempFile.close();

        if (!found)
        {
            cout << "Ticket ID " << ticketId << " not found in professor's file.\n";
        }
        else
        {
            if (rename("temp_tickets_prof.txt", (ticket.professor + "_tickets.txt").c_str()) != 0)
            {
                perror("Error renaming professor's file");
            }
            else
            {
                cout << "Ticket resolved successfully in professor's file!\n";
            }
        }
    }

    // Update Student's File
    ifstream studentFile(studentName + "_tickets.txt");
    ofstream tempStudentFile("temp_tickets_student.txt");
    found = false; // Reset found flag for student file

    if (studentFile.is_open() && tempStudentFile.is_open())
    {
        string line;
        while (getline(studentFile, line))
        {
            if (line.find("Ticket ID: " + ticketId) != string::npos)
            {
                found = true;
                tempStudentFile << line << endl; // Ticket ID

                for (int i = 0; i < 8; i++)
                {
                    getline(studentFile, line);
                    if (line.find("Status: open") != string::npos)
                    {
                        line.replace(line.find("open"), 4, "resolved");
                    }
                    else if (line.find("Date Resolved: Pending") != string::npos)
                    {
                        line.replace(line.find("Pending"), 7, resolvedDate); // Add Date Resolved
                    }
                    tempStudentFile << line << endl; // Write the updated line
                }
            }
            else
            {
                tempStudentFile << line << endl; // Copy unchanged lines
            }
        }
        studentFile.close();
        tempStudentFile.close();

        if (!found)
        {
            cout << "Ticket ID " << ticketId << " not found in student's file.\n";
        }
        else
        {
            if (rename("temp_tickets_student.txt", (studentName + "_tickets.txt").c_str()) != 0)
            {
                perror("Error renaming student's file");
            }
            else
            {
                cout << "Ticket resolved successfully in student's file!\n";
            }
        }
    }
    else
    {
        cout << "Error opening student's file.\n";
    }

    cout << "Press 'q' to return to Professor Interface or any other key to resolve another ticket: ";
    char choice;
    cin >> choice;
    if (choice == 'q' || choice == 'Q')
    {
        clearscreen();
        resolveTicket(); 
    }
}

void notifTickets()
{
    string username = user.getUsername();
    string role = user.getRole();
    string line, status;
    status = "Status: open";
    int newTicketCount = 0, newMessageCount = 0;

    if (role == "s")
    {
        string studentFile = ticket.studentName + "_tickets.txt";
        ifstream stunotif(studentFile);

        if (stunotif.is_open())
        {
            while (getline(stunotif, line))
            {
                if (line.find("Status: resolved") != string::npos)
                {
                    newTicketCount++;
                }
            }
            stunotif.close();
        }

        // Check for new messages
        string chatFile = ticket.studentName + "_" + ticket.professor + ".txt";
        ifstream chatNotif(chatFile);
        if (chatNotif.is_open())
        {
            while (getline(chatNotif, line))
            {
                if (line.find(ticket.professor + ":") != string::npos)
                { // Assume professor sends messages
                    newMessageCount++;
                }
            }
            chatNotif.close();
        }

        if (newTicketCount > 0)
        {
            cout << "\nYou have " << newTicketCount << " resolved ticket(s)!\n";
        }
        else
        {
            cout << "\nNo resolved tickets at the moment.\n";
        }

        if (newMessageCount > 0)
        {
            cout << "You have " << newMessageCount << " new message(s) from your professor.\n";
        }
        else
        {
            cout << "No new messages at the moment.\n";
        }
    }
    else if (role == "p")
    {
        string professorFile = ticket.professor + "_tickets.txt";
        ifstream pronotif(professorFile);

        if (pronotif.is_open())
        {
            while (getline(pronotif, line))
            {
                if (line.find(status) != string::npos)
                {
                    newTicketCount++;
                }
            }
            pronotif.close();
        }

        // Check for new messages
        ifstream studentList("StudentsOf_" + ticket.professor + ".txt");
        string studentName;
        while (getline(studentList, studentName))
        {
            string chatFile = studentName + "_" + ticket.professor + ".txt";
            ifstream chatNotif(chatFile);
            if (chatNotif.is_open())
            {
                while (getline(chatNotif, line))
                {
                    if (line.find(studentName + ":") != string::npos)
                    { // Assume student sends messages
                        newMessageCount++;
                    }
                }
                chatNotif.close();
            }
        }

        if (newTicketCount > 0)
        {
            cout << "\nYou have " << newTicketCount << " new tickets to resolve!\n";
        }
        else
        {
            cout << "\nNo new tickets at the moment.\n";
        }

        if (newMessageCount > 0)
        {
            cout << "You have " << newMessageCount << " new message(s) from students.\n";
        }
        else
        {
            cout << "No new messages at the moment.\n";
        }
    }
    else
    {
        cout << "Invalid role!\n";
    }
}

void analytics() {
    int A1 = 0, A2 = 0, A3 = 0, A4 = 0, A5 = 0, A6 = 0, A7 = 0, A8 = 0, A9 = 0, A10 = 0;
    vector<int> durations; // To track resolution times
    string professorFile = ticket.professor + "_tickets.txt";
    ifstream analytics(professorFile);
    string line, createdDate, resolvedDate;

    bool hasResolvedTickets = false; // Flag to check if any tickets have been resolved
    int totalTickets = 0;

    if (analytics.is_open()) {
        while (getline(analytics, line)) {
            totalTickets++; // Count total tickets
            if (line.find("Concern: Grades and Assessments") != string::npos)
                A1++;
            else if (line.find("Concern: Course Material and Content") != string::npos)
                A2++;
            else if (line.find("Concern: Assignment Deadlines and Extensions") != string::npos)
                A3++;
            else if (line.find("Concern: Class Schedule and Attendance") != string::npos)
                A4++;
            else if (line.find("Concern: Exam Schedules and Conflicts") != string::npos)
                A5++;
            else if (line.find("Concern: Feedback and Improvement") != string::npos)
                A6++;
            else if (line.find("Concern: Academic Advising") != string::npos)
                A7++;
            else if (line.find("Concern: Personal Issues Affecting Academic Performance") != string::npos)
                A8++;
            else if (line.find("Concern: Technical Issues") != string::npos)
                A9++;
            else if (line.find("Concern: General Inquiries") != string::npos)
                A10++;

            // Look for the Date of Inquiry and Date Resolved
            if (line.find("Date of Inquiry:") != string::npos) {
                createdDate = line.substr(line.find(":") + 2);
            }
            else if (line.find("Date Resolved:") != string::npos) {
                resolvedDate = line.substr(line.find(":") + 2);
                if (resolvedDate != "Pending") {
                    hasResolvedTickets = true; // Mark that we found a resolved ticket
                    struct tm tmCreated = {}, tmResolved = {};
                    strptime(createdDate.c_str(), "%Y-%m-%d %H:%M:%S", &tmCreated);
                    strptime(resolvedDate.c_str(), "%Y-%m-%d %H:%M:%S", &tmResolved);
                    time_t tCreated = mktime(&tmCreated);
                    time_t tResolved = mktime(&tmResolved);
                    durations.push_back(difftime(tResolved, tCreated) / 60); // Store resolution time in minutes
                }
            }
        }
        analytics.close();
    }

    // Calculate the total ticket count and percentages
    int totalTix = A1 + A2 + A3 + A4 + A5 + A6 + A7 + A8 + A9 + A10;
    float A1percentage = (static_cast<float>(A1) / totalTix) * 100;
    float A2percentage = (static_cast<float>(A2) / totalTix) * 100;
    float A3percentage = (static_cast<float>(A3) / totalTix) * 100;
    float A4percentage = (static_cast<float>(A4) / totalTix) * 100;
    float A5percentage = (static_cast<float>(A5) / totalTix) * 100;
    float A6percentage = (static_cast<float>(A6) / totalTix) * 100;
    float A7percentage = (static_cast<float>(A7) / totalTix) * 100;
    float A8percentage = (static_cast<float>(A8) / totalTix) * 100;
    float A9percentage = (static_cast<float>(A9) / totalTix) * 100;
    float A10percentage = (static_cast<float>(A10) / totalTix) * 100;

    // Print the analytics
    cout << "\n================================================================================\n";
    cout << setw(25) << " " << "Concern Analytics\n\n";
    cout << left << setw(50) << "Concern Categories" << setw(10) << "Frequency" << setw(10) << "Percentage" << endl;
    
    // Print all concern categories, including those with 0 tickets
    cout << left << setw(50) << "Grades and Assessments: " << setw(12) << A1 << setw(12) << A1percentage << "%" << endl;
    cout << left << setw(50) << "Course Material and Content: " << setw(12) << A2 << setw(12) << A2percentage << "%" << endl;
    cout << left << setw(50) << "Assignment Deadlines and Extensions: " << setw(12) << A3 << setw(12) << A3percentage << "%" << endl;
    cout << left << setw(50) << "Class Schedule and Attendance: " << setw(12) << A4 << setw(12) << A4percentage << "%" << endl;
    cout << left << setw(50) << "Exam Schedules and Conflicts: " << setw(12) << A5 << setw(12) << A5percentage << "%" << endl;
    cout << left << setw(50) << "Feedback and Improvement: " << setw(12) << A6 << setw(12) << A6percentage << "%" << endl;
    cout << left << setw(50) << "Academic Advising: " << setw(12) << A7 << setw(12) << A7percentage << "%" << endl;
    cout << left << setw(50) << "Personal Issues Affecting Academic Performance: " << setw(12) << A8 << setw(12) << A8percentage << "%" << endl;
    cout << left << setw(50) << "Technical Issues: " << setw(12) << A9 << setw(12) << A9percentage << "%" << endl;
    cout << left << setw(50) << "General Inquiries: " << setw(12) << A10 << setw(12) << A10percentage << "%" << endl;

    // Check if any resolved tickets exist
    if (hasResolvedTickets) {
        int totalDuration = accumulate(durations.begin(), durations.end(), 0);
        cout << "\nAverage Resolution Time: " << (totalDuration / durations.size()) << " minutes.\n";
    } else {
        cout << "\nNo resolved tickets yet.\n";
    }

    // Print total number of tickets
    cout << "\nTotal Tickets Created: " << totalTickets << endl;

    cout << "================================================================================\n";
    cout << "\nPress Enter to continue...";
    cin.ignore();
    cin.get();
    clearscreen();
    professorsInterface();
}

void profSched()
{
    cout << "Enter your Schedule (hh:mm[in] - hh:mm[out]):\n";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < 7; ++i)
    {
        cout << sched.days[i];
        getline(cin, sched.time[i]);
    }

    ofstream pSched("Schedule.txt", ios::app);
    if (pSched.is_open())
    {
        pSched << ticket.professor << endl;
        for (int i = 0; i < 7; ++i)
        {
            pSched << sched.days[i] << sched.time[i] << endl;
        }
        pSched << endl;
        pSched.close();
        clearscreen();
        cout << "Your Schedule for the week has been saved!\n";
    }
    else
    {
        cout << "Error opening file!";
    }
}

bool isDayOfWeek(const string &line, const Sched &sched)
{
    for (const auto &day : sched.days)
    {
        if (line.find(day) == 0)
        {
            return true;
        }
    }
    return false;
}

void chooseProf()
{
    int profChoice;
    ifstream profs("Schedule.txt");
    if (!profs)
    {
        cerr << "Error: File could not be opened." << endl;
        return;
    }

    string line;
    vector<string> professors;
    Sched sched;

    while (getline(profs, line))
    {
        if (!line.empty() && !isDayOfWeek(line, sched))
        {
            professors.push_back(line);
        }
    }
    profs.close();

    sort(professors.begin(), professors.end());
    cout << "\nProfessors:" << endl;
    for (size_t i = 0; i < professors.size(); i++)
    {
        cout << "(" << i + 1 << ") " << professors[i] << endl;
        continue;
    }
    cout << "\nEnter which Professor you have concern with(# only): ";
    while (true)
    {
        cin >> profChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a number: " << endl;
            continue;
        }

        if (profChoice >= 1 && profChoice <= static_cast<int>(professors.size()))
        {
            ticket.professor = professors[profChoice - 1];
            break;
        }
        else
        {
            cout << "Please enter a number between 1 and " << professors.size() << endl;
        }
    }
}

void chooseDay()
{
    cout << "\nChoose the available time with Professor " << ticket.professor << ":(Enter # only)\n";

    ifstream profs("Schedule.txt");
    if (!profs)
    {
        cerr << "Error: File could not be opened." << endl;
        return;
    }

    const vector<pair<string, int>> days = {
        {"Monday:", 1},
        {"Tuesday:", 2},
        {"Wednesday:", 3},
        {"Thursday:", 4},
        {"Friday:", 5},
        {"Saturday:", 6},
        {"Sunday:", 7}};

    string line;
    bool foundProfSection = false;
    vector<string> availableDays;

    while (getline(profs, line))
    {
        if (line == ticket.professor)
        {
            foundProfSection = true;
            continue;
        }

        if (foundProfSection)
        {
            for (const auto &[day, number] : days)
            {
                if (line.find(day) == 0)
                {
                    cout << "(" << number << ") " << line << endl;
                    availableDays.push_back(line);
                    break;
                }
            }

            if (line.empty())
                break;
        }
    }

    if (!foundProfSection)
    {
        cerr << "Error: Professor's schedule not found in the file." << endl;
        profs.close();
        return;
    }
    cout << "Which Day(# only): ";
    int dayChoice;
    while (true)
    {
        cin >> dayChoice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Please enter a valid number." << endl;
            continue;
        }

        if (dayChoice >= 1 && dayChoice <= availableDays.size())
        {
            ticket.scheduledMeeting = availableDays[dayChoice - 1];
            break;
        }
        else
        {
            cout << "Please enter a number between 1 and " << availableDays.size() << endl;
        }
    }

    profs.close();
}

void enroll()
{
    cout << "\n"
         << setw(3) << " " << "List of the Professors:\n\n";
    ifstream list("accounts.txt");
    string line, user, pass, dep, role, id;
    int count = 0, i = 0;
    vector<string> professors;

    if (list.is_open())
    {
        while (list >> user >> pass >> dep >> role >> id)
        {
            if (role == "p")
            {
                i = 1 + count++;
                cout << "(" << i << ") " << user << endl;
                professors.push_back(user);
            }
        }
        list.close();
    }

    cout << "\nEnroll to (enter professor number): ";
    int profIndex;
    cin >> profIndex;
    cin.ignore(); // Ignore the newline character left in the input buffer

    if (profIndex > 0 && profIndex <= professors.size())
    {
        ticket.professor = professors[profIndex - 1];
    }
    else
    {
        clearscreen();
        cout << "Invalid selection.\n";
        return;
    }

    ofstream students("StudentsOf_" + ticket.professor + ".txt", ios::app);
    if (students.is_open())
    {
        students << ticket.studentName << endl;
        students.close();
    }

    cout << "Successfully Enrolled to professor, " << ticket.professor << "\n\n";
    cout << "Press Enter to continue...\n";
    cin.get();
    clearscreen();
    studentsInterface();
}

void Messenger()
{
    string exit;
    string user;
    // Student to Professor
    if (ticket.role == "s")
    {
        cout << "Professors:\n";
        ifstream proflist("accounts.txt");
        string line, users, pass, dep, role, id;
        int count = 0, i = 0;
        vector<string> professors;

        if (proflist.is_open())
        {
            while (proflist >> users >> pass >> dep >> role >> id)
            {
                if (role == "p")
                {
                    i = 1 + count++;
                    cout << "(" << i << ") " << users << endl;
                    professors.push_back(users);
                }
            }
            proflist.close();
        }
        cout << "\n===========================================";
        cout << "\nChoose which professor to talk to(# only): ";
        int profIndex;
        cin >> profIndex;
        cin.ignore(); // Ignore the newline character left in the input buffer
        if (profIndex > 0 && profIndex <= professors.size())
        {
            ticket.professor = professors[profIndex - 1];
        }
        else
        {
            cout << "Invalid selection.\n";
            return;
        }

        do
        {
            ifstream convo(ticket.studentName + "_" + ticket.professor + ".txt");
            if (convo.is_open())
            {
                while (getline(convo, line))
                {
                    cout << line << endl;
                }
                convo.close();
            }
            cout << "\n==================================";
            cout << "\nEnter a message(Enter Q to Exit): ";
            getline(cin, exit);
            if (exit == "q" || exit == "Q")
            {
                clearscreen();
                studentsInterface();
                break;
            }
            else
            {
                message.msg = exit;
                clearscreen();
                ofstream chat(ticket.studentName + "_" + ticket.professor + ".txt", ios::app);
                if (chat.is_open())
                {
                    chat << setw(30) << " " << ticket.studentName << ":" << endl;
                    chat << setw(30) << " " << message.msg << endl;
                    chat.close();
                }
            }
        } while (exit != "q" && exit != "Q");
    }
    // Professor to Student
    else if (ticket.role == "p")
    {
        cout << "Students: \n";
        ifstream students("StudentsOf_" + ticket.professor + ".txt");
        int count = 1;
        string line;
        vector<string> studentList;

        if (students.is_open())
        {
            while (students >> user)
            {
                cout << setw(3) << " " << "(" << count++ << ") " << user << endl;
                studentList.push_back(user);
            }
            students.close();
        }
        cout << "\n===========================================";
        cout << "\nChoose which student to talk to(# only): ";
        int studentIndex;
        cin >> studentIndex;
        cin.ignore(); // Ignore the newline character left in the input buffer
        if (studentIndex > 0 && studentIndex <= studentList.size())
        {
            ticket.studentName = studentList[studentIndex - 1];
        }
        else
        {
            cout << "Invalid selection.\n";
            return;
        }

        do
        {
            ifstream pconvo(ticket.studentName + "_" + ticket.professor + ".txt");
            if (pconvo.is_open())
            {
                while (getline(pconvo, line))
                {
                    cout << line << endl;
                }
                pconvo.close();
            }
            cout << "\n==================================";
            cout << "\nEnter a message(Enter Q to Exit): ";
            getline(cin, exit);
            if (exit == "q" || exit == "Q")
            {
                clearscreen();
                studentsInterface();
                break;
            }
            else
            {
                message.msg = exit;
                clearscreen();
                ofstream schat(ticket.studentName + "_" + ticket.professor + ".txt", ios::app);
                if (schat.is_open())
                {
                    schat << ticket.professor << ":" << endl;
                    schat << message.msg << endl;
                    schat.close();
                }
            }
        } while (exit != "q" && exit != "Q");
    }
}

void viewSched()
{
    ifstream profs("Schedule.txt");

    if (!profs.is_open())
    {
        cout << "Error: Could not open Schedule.txt" << endl;
        return;
    }

    string line;
    Sched sched;
    bool foundProfessor = false;

    while (getline(profs, line))
    {
        if (line == ticket.professor)
        {
            foundProfessor = true;
            cout << "======================" << endl;
            cout << "Your Current Schedule:" << endl;
            cout << "======================" << endl;
            // Read and display the professor's schedule
            for (int i = 0; i < 7; ++i)
            {
                if (getline(profs, line) && line.find(sched.days[i]) != string::npos)
                {
                    cout << line << endl;
                }
            }
            break;
        }
    }

    if (!foundProfessor)
    {
        cout << "You have no schedule yet." << endl;
    }

    // If the professor wants to change his schedule...
    char changeSched;
    cout << "=================================================" << endl;
    cout << "Do you want to change your current schedule?(Y/N)";
    cin >> changeSched;

    switch (changeSched)
    {
    case 'Y':
    case 'y':

        break;
    default:
        break;
    }

    profs.close();
    cout << "Press Enter to continue...";
    cin.ignore();
    cin.get();
    clearscreen();
    professorsInterface();
}
