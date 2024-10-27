#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void registerUser();
void login();
void retrievePassword();
void userInterface();


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
            case 4: cout<<"Thank you for using our system!\n";
            exit(0);
            break;
            default: cout<<"Invalid input!\n";
        }
    }
    while(choice != 4);
    return 0;
}


class User
{
    private: 
        string username, password, role;
    public:
        User(): username(""), password(""), role(""){}
        User(string id, string pass, string r) : username(id), password(pass), role(r){}
        string getUsername() const{return username;}
        string getPassword() const{return password;}
        string getRole() const{return role;}

        void setUsername(){
            cin>>username;
        }
        void setPassword(){
            cin>>password;
        }
        void setRole(){
            cin>>role;
        }

};

User user;
void registerUser()
{
    cout<<"Enter username: "; user.setUsername();
    cout<<"Enter password: "; user.setPassword();
    cout<<"Enter role((s)student/(p)professor): "; user.setRole();

    ofstream reg("accounts.txt", ios::app);
    if(reg.is_open()){
        reg << user.getUsername()<< "\t"<< user.getPassword()<<"\t"<<user.getRole();
        reg.close();
        cout<<"Registration Successful!\n";
        system("clear");
    }
}

void login()
{    
    int count = 0;
    string id, pass;
    string luser, lpass, lrole;
    cout<<"Enter username: "; cin>> id;
    cout<<"Enter Password: "; cin>> pass;

    ifstream input("accounts.txt");
    if(input.is_open())
    {   
        while(input>>luser>>lpass>>lrole)
        {
            if(luser == id && lpass == pass)
            {
                count = 1;
                system("clear");
                break;

            }
        }
        input.close();
        if(count == 1)
        {
            cout<<"Login Successful!\n";
            userInterface();
        }
        else
        {
            cout<<"Invalid username or password!\n";
        }
    } 
}
void retrievePassword()
{
    //kaemehan
}
void userInterface()
{
    cout<<"Welcome"<<user.getUsername()<<endl;
    cout<<"1. Create Ticket\n2. View Tickets\n3. Resolve Ticket\n4. Logout\n";
}
