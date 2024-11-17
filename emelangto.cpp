#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime> 
#include <limits>
#include <iomanip>
using namespace std;

struct Ticket
{
    string studentName, studentId, concern, date, professor, status, role, department;
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
void addSchedule(string uname);
void clearscreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/Mac
    #endif
}
void analytics();
void viewSchedule(string uname);

int main() {
    clearscreen();
    int choice;
    //cout << "--------------------------------------\n";
    cout << "                 Welcome              \n";
    cout << "           Precious University        \n";
    cout << "               Students Inq           \n";
    while(true){
    cout << "\nMenu: \n";
    cout << "\n (1) Login\n (2) Register\n (3) Forgot Password\n (4) Exit\n";
    cout << "\nMenu(#): ";
    cin>> choice;

    if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid input! Please enter a number between 1 and 4.\n";
        } else {
            cin.ignore(); // Ignore the newline character left in the input buffer
            break;
        }
    }


    switch (choice)
    {
        case 1: clearscreen();
        login();
        break;
        case 2: clearscreen();
        registerUser();
        break;
        case 3: clearscreen();
        retrievePassword();
        break;
        case 4: clearscreen();
        cout << "Thank you for using our system!\n";
        exit(0);
        break;
        default: clearscreen();
        cout << "Invalid input!\n";
        main();
        break;
    }
}

class User {
private: 
    string username, password, role, sid, department;
public:
    User(): username(""), password(""), role(""), sid(""), department("") {}
    User(string uname, string pass, string r, string id, string d) : username(uname), password(pass), role(r), sid(id), department(d) {}

    string getUsername() const { return username; }
    string getPassword() const { return password; }
    string getRole() const { return role; }
    string getSid() const { return sid; }
    string getDepartment() const { return department; }

    void setUsername(const string& u) { // Accepts a string argument
        username = u;
    }   

    void setPassword() {
        cin >> password;
    }

    void setRole(const string& r) { // Accepts a string argument
        role = r;
    }
    
    void setDepartment(const string& d) { // Accepts a string argument
        department = d;
    }
    void setSid(const string& id) { // Accepts a string argument
        sid = id;
    }
    
};

struct Schedule{
    string monday, tuesday, wednesday, thursday, friday, saturday, sunday, schedule;
    
};
struct Message{
    string msg;
};

Message message;
Schedule schedule;
User user;
Ticket ticket;
void registerUser() {
    cout << "Registration\n\n";
    string uname;
    cout <<  setw(3) << " "<<"Enter username: "; getline(cin, uname);
    user.setUsername(uname);
    cout <<  setw(3) << " "<<"Enter password: "; user.setPassword();
    
    char departmentInputInt;
    do{
    cout << setw(3)<< " "<<"Enter Department-Options(Enter # only):\n ";
    cout<< setw(3) << " "<<"(1) College of Engineering and Architecture\n";
    cout<< setw(3) << " "<<"(2) College of Computer Studies\n";
    cout<< setw(3) << " "<<"(3) College of Business Education\n";
    cout<< setw(3) << " "<<"(4) College of Arts and Sciences\n";
    cout<< setw(3) << " "<<"Department: ";
    cin >> departmentInputInt;
     
    
    switch (departmentInputInt) {
        case '1': user.setDepartment("CEA");
        break;
        case '2': user.setDepartment("CCS");
        break;
        case '3': user.setDepartment("CBE");
        break;
        case '4': user.setDepartment("CAS");
        break;
        default: cout << "Invalid input!\n";
        break;
    }}while(departmentInputInt != '1' && departmentInputInt != '2' && departmentInputInt != '3' && departmentInputInt != '4');

    char roleInput;
    cout <<setw(3)<<" "<< "Enter role ((s)student/(p)professor): ";
    cin >> roleInput;
    string sidInput;
    switch(roleInput){
        case 's': user.setRole("s"); 
        cout << setw(3)<< " "<<"Enter student no.: "; 
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, sidInput);
        user.setSid(sidInput);
        break;
        case 'p': user.setRole("p"); 
        sidInput = "0";
        cin.ignore();
        user.setSid(sidInput);
        cout<< setw(3)<<" "<<"Enter your consulatation time"<<endl;
        cout<< setw(3)<<" "<<"Monday: "; getline(cin, schedule.monday);
        cout<< setw(3)<<" "<<"Tuesday: "; getline(cin, schedule.tuesday);
        cout<< setw(3)<<" "<<"Wednesday: "; getline(cin, schedule.wednesday);
        cout<< setw(3)<<" "<<"Thursday: "; getline(cin, schedule.thursday);
        cout<< setw(3)<<" "<<"Friday: "; getline(cin, schedule.friday);
        cout<< setw(3)<<" "<<"Saturday: "; getline(cin, schedule.saturday);
        cout<< setw(3)<<" "<<"Sunday: "; getline(cin, schedule.sunday);
        break;
        default: cout << "Invalid input!\n";
        break;
    }
    if(roleInput == 'p'){
    ofstream sched("schedules.txt", ios::app);
        if(sched.is_open()){
            sched << "Schedule of Professor, " << uname << endl;
            sched << "Monday: " << schedule.monday << endl;
            sched << "Tuesday: " << schedule.tuesday << endl;
            sched << "Wednesday: " << schedule.wednesday << endl;
            sched << "Thursday: " << schedule.thursday << endl;
            sched << "Friday: " << schedule.friday << endl;
            sched << "Saturday: " << schedule.saturday << endl;
            sched << "Sunday: " << schedule.sunday << endl;
            sched << "-------------------------------------------"<<endl;
            sched.close();
            cout<< "Schedule added successfully!\n";
        }
    }
    ofstream reg("accounts.txt", ios::app);
    if (reg.is_open()) {
        reg << user.getUsername() << setw(10) << user.getPassword() << setw(10) << user.getDepartment() << setw(10) << user.getRole() << setw(10) << user.getSid() << endl;
        reg.close(); 
        clearscreen();
        cout << "Registration Successful!\n";
        main();
    }
}


void login() {   
    cout<<"Login\n\n";
    int count = 0;
    string id, pass;
    string lpass,luname, lrole;
    do{
    cout << setw(3) << " "<<"Enter username: "; getline(cin, id);
    cout <<  setw(3) << " "<<"Enter Password: "; getline(cin, pass);


    ifstream input("accounts.txt");
    if (input.is_open()) {   
        while (input >> luname >> lpass >> ticket.department >> ticket.role >> ticket.studentId) {
            if (luname == id && lpass == pass && ticket.role == "s") {
                ticket.studentName = luname;
                user.setUsername(luname);
                user.setRole(ticket.role); 
                user.setDepartment(ticket.department);
                clearscreen();
                studentsInterface();
                break;}
            else if(luname == id && lpass == pass && ticket.role == "p"){
                ticket.professor = luname;
                user.setUsername(luname);
                user.setRole(ticket.role);
                user.setDepartment(ticket.department);
                clearscreen();
                professorsInterface();
                break;
            }
            else{count = 1;
            clearscreen();
            cout << "Invalid username or password!\n";
            cout << "Please try again.\n\n";
            }
        }
        input.close();
    }}while(count == 1);
    
}
       
void retrievePassword()
{
    int count = 0;
    string fuse, user, pass, role, sid;
    cout<<"Enter username: "; cin>>fuse;

    ifstream ret("accounts.txt");
    if(ret.is_open())
    {
        while(ret >> user >> pass >> role >> sid)
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
    string departmentName = user.getDepartment();

    cout << "Welcome, student " << ticket.studentName << " of " << departmentName << endl;
    cout<<"\n";
    while (true) {
    notifTickets();
    cout<<"\n";
    cout << "Option: \n\n";
    cout << " (1) Create Ticket\n (2) View Tickets\n (3) Enroll\n (4) Message \n (5) Logout\n";
    cout << "\nOption(#): ";
    cin >> action;

    if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid input! Please enter a number between 1 and 3.\n";
        } else {
            cin.ignore(); // Ignore the newline character left in the input buffer
            break;
        }
}
    
    switch (action) {
        case 1: clearscreen();
        addTickets(); 
        break;
        case 2: clearscreen();
        viewTickets();
        break;
        case 3: enroll();
        studentsInterface();
        break;  
        case 4: clearscreen();
        Messenger();
        studentsInterface();
        break;
        case 5: cout << "Logging out...\n"; 
        clearscreen(); 
        main();
        break;
        default: clearscreen();
        cout << "Invalid input!\n"; 
        studentsInterface(); 
        break;
    }
}

void professorsInterface() {
    string departmentName = user.getDepartment();
    int action;
    cout << "Welcome, professor " << ticket.professor << " of " << departmentName << endl;
    cout << "\n";
    while (true) {
    notifTickets();
    cout << "\n";
    cout << "Option: \n\n";
    cout << " (1) View Ticket\n (2) Resolve Tickets\n (3) View Analytics \n (4) View Schedule \n (5) Message \n (6) Logout\n";
    cout << "\nOption(#): ";
    cin >> action;
    cout << "\n";

    if (cin.fail()) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "\nInvalid input! Please enter a number between 1 and 4.\n";
        } else {
            cin.ignore(); // Ignore the newline character left in the input buffer
            break;
        }
}

    switch (action) {
        case 1: clearscreen();
        viewTickets();
        break;
        case 2: clearscreen();
        resolveTicket();
        break;
        case 3: clearscreen();
        analytics();
        break;
        case 4: clearscreen();
        viewSchedule(ticket.professor);
        professorsInterface();
        break;
        case 5: clearscreen();
        Messenger();
        professorsInterface();
        case 6: clearscreen();
        cout << "Logging out...\n";
        main();
        break;
        default: clearscreen();
        cout << "Invalid input!\n";
        professorsInterface();
        break;
    }
}

void viewTickets() {
    string username = user.getUsername();
    string role = user.getRole();
    string line;

    if (role == "s") {  // Student interface
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
        clearscreen();
        studentsInterface();
    } else if (role == "p") {  // Professor interface
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
        clearscreen();
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
    string concern,  concern1, professor, departmentName;
    
    int concernChoice;
    char back;
    string additionalDetails;
    while (true) {
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
    if (cin.fail() || concernChoice < 1 || concernChoice > 10) {
            cin.clear(); // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Discard invalid input
            cout << "Invalid input! Please enter a number between 1 and 10.\n\n";
        } else {
            cin.ignore(); // Ignore the newline character left in the input buffer
            break;
        }
    }
switch (concernChoice) {
    case 1: concern = "Grades and Assessments"; break;
    case 2: concern = "Course Material and Content"; break;
    case 3: concern = "Assignment Deadlines and Extensions"; break;
    case 4: concern = "Class Schedule and Attendance"; break;
    case 5: concern = "Exam Schedules and Conflicts"; break;
    case 6: concern = "Feedback and Improvement"; break;
    case 7: concern = "Academic Advising"; break;
    case 8: concern = "Personal Issues Affecting Academic Performance"; break;
    case 9: concern = "Technical Issues"; break;
    case 10: concern = "General Inquiries"; break;
    default: cout<< "Invalid Input!";
    addTickets(); break;
}

cout << "Enter additional details about your concern: ";
getline(cin, additionalDetails); 
cout << "Enter the professor's name: ";
getline(cin, ticket.professor);
addSchedule(ticket.professor);





// Continue with the rest of the code...

    // Get the current date and time
    time_t now = time(0);
    tm *ltm = localtime(&now);
    char date[20];
    strftime(date, sizeof(date), "%Y-%m-%d %H:%M:%S", ltm);

    //ticketno
    srand(time(0));
    int ticketno = rand() % 1000 + 1;
    string ticketnoStr = to_string(ticketno);

    if (ticket.studentName.empty() || ticket.studentId.empty()) {
        cout << "Error: Student name or ID is not initialized.\n";
        return;
    }

    string stufile = ticket.studentName + "_tickets.txt";
    ofstream ticketFile(stufile, ios::app);
    if (ticketFile.is_open()) {
        ticketFile << "Department: " << ticket.department << endl;
        ticketFile << "Student: " << ticket.studentName << endl;
        ticketFile << "Student ID: " << ticket.studentId << endl;
        ticketFile << "Ticket ID: " << ticketno << endl;
        ticketFile << "Concern: " << concern << endl;
        ticketFile << "Additional Details: " << additionalDetails << endl;
        ticketFile << "Date added: " << date << endl;
        ticketFile << "Date scheduled: " << schedule.schedule << endl;
        ticketFile << "Professor: " << ticket.professor << endl;
        ticketFile << "Status: open" << endl;
        ticketFile << "----------------------------------------" << endl;
        ticketFile.close();
        cout << "Ticket added successfully...\n";
    } else {
        cout << "Unable to open file.\n";
    }
    
    string profile = professor + "_tickets.txt";
    ofstream proticket(profile, ios::app);
    if (proticket.is_open()) {
        proticket << "Department: " << ticket.department << endl;
        proticket << "Student: " << ticket.studentName << endl;
        proticket << "Student ID: " << ticket.studentId << endl;
        proticket << "Ticket ID: " << ticketno << endl;
        proticket << "Professor: " << professor << endl;
        proticket << "Concern: " << concern << endl;
        proticket << "Additional Details: " << additionalDetails << endl;
        proticket << "Date: " << date << endl;
        proticket << "Status: open" << endl;
        proticket << "----------------------------------------" << endl;
        proticket.close();
        cout << "Ticket sent to professor...\n";
    } else {
        cout << "Unable to open file.\n";
    }
    cout<< "Press Enter to continue...";
    cin.get();
    clearscreen();
    studentsInterface();
}

void resolveTicket() {
    string linya;
    string filename = ticket.professor + "_tickets.txt";
    ifstream printTix(filename);
    if (printTix.is_open()) {
        cout << "\n--- Tickets Assigned to You ---\n";
        cout << "----------------------------------------\n";
        while (getline(printTix, linya)) {
            cout << linya << endl;
        }
        printTix.close();
    } else {
        cout << "Error opening the tickets file.\n";
    }

    cout << "----------------------------------------\n";
    cout << "\n\n";

    string ticketId;
    string studentName;
    cout << "Enter the ticket ID you want to resolve: ";
    cin >> ticketId;
    cout << "Enter the student name: ";
    cin>>studentName;

    ifstream inputFile(ticket.professor + "_tickets.txt");
    ofstream tempFile("temp_tickets.txt");  // Temporary file for modified data
    bool found = false;

    if (inputFile.is_open() && tempFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            if (line.find("Ticket ID: " + ticketId) != string::npos) {  // If the ticket ID matches
                tempFile << line << endl;  // Write the ticket ID line
                getline(inputFile, line);  // Read the next line (Concern)
                tempFile << line << endl;  // Write the Concern line
                getline(inputFile, line);  // Read the next line (Date)
                tempFile << line << endl;  // Write the Date line
                getline(inputFile, line);  // Read the next line (Professor)
                tempFile << line << endl;
                getline(inputFile, line);  // Read the next line (Professor)
                tempFile << line << endl;   // Write the Professor line
                getline(inputFile, line);  // Read the next line (Status)
                line.replace(line.find("open"), 5, "resolved");  // Update the status
                tempFile << line << endl;  // Write the updated Status line
                found = true;
                cout << "Ticket " << ticketId << " resolved successfully!\n";
            } else {
                tempFile << line << endl;  // Write to the temporary file
            }
        }
        inputFile.close();
        tempFile.close();

        if (remove((ticket.professor + "_tickets.txt").c_str()) != 0) {
            perror("Error deleting old file");
        } else if (rename("temp_tickets.txt", (ticket.professor + "_tickets.txt").c_str()) != 0) {
            perror("Error renaming new file");
        } else {
            if (!found) {
                cout << "Ticket ID " << ticketId << " not found.\n";
            }
        }
    } else {
        cout << "Error opening file.\n";
    }

    ifstream resolveStudentfile(studentName + "_tickets.txt");
    ofstream tempoFile("tempo_tickets.txt");  // Temporary file for modified data
    bool count = false;

    if (resolveStudentfile.is_open() && tempoFile.is_open()) {
        string line;
        while (getline(resolveStudentfile, line)) {
            if (line.find("Ticket ID: " + ticketId) != string::npos) {  // If the ticket ID matches
                tempoFile << line << endl;  // Write the ticket ID line
                getline(resolveStudentfile, line);  // Read the next line (Concern)
                tempoFile << line << endl;  // Write the Concern line
                getline(resolveStudentfile, line);  // Read the next line (Date)
                tempoFile << line << endl;  // Write the Date line
                getline(resolveStudentfile, line);  // Read the next line (Professor)
                tempoFile << line << endl; 
                getline(resolveStudentfile, line);  // Read the next line (Professor)
                tempoFile << line << endl;  // Write the Professor line
                getline(resolveStudentfile, line);  // Read the next line (Status)
                line.replace(line.find("open"), 5, "resolved");  // Update the status
                tempoFile << line << endl;  // Write the updated Status line
                count = true;
                cout << "Ticket " << ticketId << " resolved successfully!\n";
            } else {
                tempoFile << line << endl;  // Write to the temporary file
            }
        }
        resolveStudentfile.close();
        tempoFile.close();

        if (remove((studentName + "_tickets.txt").c_str()) != 0) {
            perror("Error deleting old file");
        } else if (rename("tempo_tickets.txt", (studentName + "_tickets.txt").c_str()) != 0) {
            perror("Error renaming new file");
        } else {
            if (!count) {
                cout << "Ticket ID " << ticketId << " not found.\n";
            }
        }
    } else {
        cout << "Error opening file.\n";
    }
    clearscreen();
    professorsInterface();  // Return to the professor interface
}



void notifTickets() {
    string username = user.getUsername();  
    string role = user.getRole(); 
    string line, status;
    status = "Status: open";
    int newTicketCount = 0;

    if (role == "s") { 
        string studentFile = ticket.studentName + "_tickets.txt";
        ifstream stunotif(studentFile);

        if (stunotif.is_open()) {
            while (getline(stunotif, line)) {
                if (line.find("Status: resolved") != string::npos) {
                    newTicketCount++;  
                }
            }
            stunotif.close();
        }
        if (newTicketCount > 0) {
            cout << "\nYou have " << newTicketCount << " resolved ticket(s)!\n";
        } else {
            cout << "\nNo resolved tickets at the moment.\n";
        }
    } else if (role == "p") { 
        string professorFile = ticket.professor + "_tickets.txt";
        ifstream pronotif(professorFile);

        if (pronotif.is_open()) {
            while (getline(pronotif, line)) {
                if (line.find(status) != string::npos) {
                    newTicketCount++;  
                }
            }
            pronotif.close();
        }
        if (newTicketCount > 0) {
            cout << "\nYou have " << newTicketCount << " new tickets to resolve!\n";
        } else {
            cout << "\nNo new tickets at the moment.\n";
        }
    } else {
        cout << "Invalid role!\n";
    }
}


void analytics(){
    int A1=0, A2=0, A3=0, A4=0, A5=0, A6=0, A7=0, A8=0, A9=0, A10=0;
    string professorFile = ticket.professor + "_tickets.txt";
    ifstream analytics(professorFile);
    string line;
    if(analytics.is_open()){
        while(getline(analytics, line)){
            if(line.find("Concern: Grades and Assessments") != string::npos){
                A1++;
            } else if(line.find("Concern: Course Material and Content") != string::npos){
                A2++;
            } else if(line.find("Concern: Assignment Deadlines and Extensions") != string::npos){
                A3++;
            } else if(line.find("Concern: Class Schedule and Attendance") != string::npos){
                A4++;
            } else if(line.find("Concern: Exam Schedules and Conflicts") != string::npos){
                A5++;
            } else if(line.find("Concern: Feedback and Improvement") != string::npos){
                A6++;
            } else if(line.find("Concern: Academic Advising") != string::npos){
                A7++;
            } else if(line.find("Concern: Personal Issues Affecting Academic Performance") != string::npos){
                A8++;
            } else if(line.find("Concern: Technical Issues") != string::npos){
                A9++;
            } else if(line.find("Concern: General Inquiries") != string::npos){
                A10++;
            }
        }
        analytics.close();
    }
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
        float totalTixPercentage = (static_cast<float>(totalTix) / totalTix) * 100;
        cout << "\n--------------------------------------------------------------------------------\n";
        cout << setw(25) << " " << "Concern Analytics\n\n";
        cout << left << setw(40) << "Concern Categories" << setw(10) << "Frequency" << setw(10) << "Percentage" << endl;
        if(A1 > 0){
            cout<< left << setw(44) <<"Grades and Assessments: "<<setw(8)<<A1 << setw(0)<< fixed << setprecision(2) << A1percentage<< "%" <<endl;
        }   
        if(A2 > 0){
            cout << left << setw(44) << "Course Material and Content: " << setw(8) << A2 << setw(0) << fixed << setprecision(2) << A2percentage << "%" << endl;
        }
        if(A3 > 0){
            cout << left << setw(44) << "Assignment Deadlines and Extensions: " << setw(8) << A3 << setw(0) << fixed << setprecision(2) << A3percentage << "%" << endl;
        }
        if(A4 > 0){
            cout << left << setw(44) << "Class Schedule and Attendance: " << setw(8) << A4 << setw(0) << fixed << setprecision(2) << A4percentage << "%" << endl;
        }
        if(A5 > 0){
            cout << left << setw(44) << "Exam Schedules and Conflicts: " << setw(8) << A5 << setw(0) << fixed << setprecision(2) << A5percentage << "%" << endl;
        }
        if(A6 > 0){
            cout << left << setw(44) << "Feedback and Improvement: " << setw(8) << A6 << setw(0) << fixed << setprecision(2) << A6percentage << "%" << endl;
        }
        if(A7 > 0){
            cout << left << setw(44) << "Academic Advising: " << setw(8) << A7 << setw(0) << fixed << setprecision(2) << A7percentage << "%" << endl;
        }
        if(A8 > 0){
            cout << left << setw(44) << "Personal Issues Affecting Academic Performance: " << setw(8) << A8 << setw(0) << fixed << setprecision(2) << A8percentage << "%" << endl;
        }
        if(A9 > 0){
            cout << left << setw(44) << "Technical Issues: " << setw(8) << A9 << setw(0) << fixed << setprecision(2) << A9percentage << "%" << endl;
        }
        if(A10 > 0){
            cout << left << setw(44) << "General Inquiries: " << setw(8) << A10 << setw(0) << fixed << setprecision(2) << A10percentage << "%" << endl;
        }
        cout<< left << setw(44) <<"Total Tickets: "<<setw(8) << totalTix<< fixed << setprecision(2) << totalTixPercentage <<endl;

        cout << "\n--------------------------------------------------------------------------------\n";
        cout << "\nPress Enter to continue...";
        cin.get();
        cout << "\n";
        clearscreen();
        professorsInterface();
    }

    void viewSchedule(string uname){
        uname = ticket.professor;
        ifstream profsched("schedules.txt");
        if(profsched.is_open()){
            string line;
            while(getline(profsched, line)){
                if(line.find("Schedule of Professor, " + uname) != string::npos){;
                cout << "\n-------------------------------------------\n";
                cout<<line<<endl;// line 1
                getline(profsched, line);\
                cout<<"(1) "<<line<<endl; //line 2
                getline(profsched, line);
                cout<<"(2) "<<line<<endl; //line 3
                getline(profsched, line);
                cout<<"(3) "<<line<<endl; // line 4
                getline(profsched, line);
                cout<<"(4) "<<line<<endl; // line 5
                getline(profsched, line);
                cout<<"(5) "<<line<<endl; // line 6
                getline(profsched, line);
                cout<<"(6) "<<line<<endl; // line 7
                getline(profsched, line);
                cout<<"(7) "<<line<<endl; // line 8
                getline(profsched, line);
                cout<<line<<endl; // divider
                }

            }
            profsched.close();
        }
        cout<<"Press Enter to continue...\n";
        cin.get();
        clearscreen();
    }

void enroll(){  
    cout<<"\n" <<setw(3 )<<" "<< "List of the Professor:\n\n";
    ifstream list("accounts.txt");
    string line, user, pass, dep, role, id;
    int count = 0, i =0;

    if(list.is_open()){
        while(list >> user >> pass >> dep >> role >> id){
            if(role == "p"){
                i = 1 + count++;
                cout<<"("<<i <<") " <<user<< endl;
                
            }
        }
    }list.close();
    cout<< "\nEnroll to: ";
    getline(cin, ticket.professor);

    ofstream students("Students of " + ticket.professor, ios::app );
    if(students.is_open()){
        students << ticket.studentName<<endl;
        students.close();
    }
    cout<<"Sucessfuly Enrolled to professor, " <<ticket.professor<<"\n\n";
    cout<<"Press Enter to continue...\n";
    cin.get();
    clearscreen();
    studentsInterface();
}

void Messenger(){
    if(ticket.role == "s"){
        cout<<"Enter professor: "; getline(cin, ticket.professor);
        ifstream convo(ticket.studentName + "_" + ticket.professor +".txt");
        string line;
        if(convo.is_open()){
            while(getline(convo, line)){
                cout<<line<<endl;
            }
        }convo.close();
    cout<<"\nEnter a message: "; getline(cin, message.msg);
    ofstream chat(ticket.studentName + "_" + ticket.professor +".txt", ios::app);
        if(chat.is_open()){
            
                chat<<setw(30)<<" "<<ticket.studentName<<endl;
                chat<<setw(30)<<" " << message.msg<<endl;
            }chat.close();
    }
    else if(ticket.role == "p"){
        cout<<"Enter Student: "; getline(cin, ticket.studentName);
        ifstream pconvo(ticket.studentName + "_" + ticket.professor +".txt");
        string line;
        if(pconvo.is_open()){
            while(getline(pconvo, line)){
                cout<<line;
            }
        }pconvo.close();
        cout<<"Enter a message: "; getline(cin, message.msg);
        ofstream schat(ticket.studentName + "_" + ticket.professor +".txt", ios::app);
        if(schat.is_open()){
            
                schat<<ticket.professor<<endl;
                schat<<message.msg<<endl;
            }schat.close();

    }


}

 void addSchedule(string uname){
        uname = ticket.professor;
        int sched;
        ifstream addsched("schedules.txt");
        if(addsched.is_open()){
            string line, mon, tue, wed, thu, fri, sat, sun;
            while(getline(addsched, line)){
                if(line.find("Schedule of Professor, " + uname) != string::npos){;
                cout << "\n-------------------------------------------\n";
                cout<<line<<endl;// line 1
                getline(addsched, line);\
                cout<<"(1) "<<line<<endl; //line 2
                mon = line;
                getline(addsched, line);
                cout<<"(2) "<<line<<endl; //line 3
                tue = line;
                getline(addsched, line);
                cout<<"(3) "<<line<<endl; // line 4
                wed = line;
                getline(addsched, line);
                cout<<"(4) "<<line<<endl; // line 5
                thu = line;
                getline(addsched, line);
                cout<<"(5) "<<line<<endl; // line 6
                fri = line;
                getline(addsched, line);
                cout<<"(6) "<<line<<endl; // line 7
                sat = line;
                getline(addsched, line);
                cout<<"(7) "<<line<<endl; // line 8
                sun = line;
                getline(addsched, line);
                cout<<line<<endl; // divider
                }

            }
            addsched.close();
        
        cout << "\n\nPress Enter to continue...";
        cin.get();
        cout << "Select Schedule: ";
        cin>>sched;
        cin.ignore();
        switch(sched){
        case 1: schedule.schedule = mon; break;
        case 2: schedule.schedule = tue; break;
        case 3: schedule.schedule = wed; break;
        case 4: schedule.schedule = thu; break;
        case 5: schedule.schedule = fri; break;
        case 6: schedule.schedule = sat; break;
        case 7: schedule.schedule = sun; break;
    }
    }
 }
    
    
