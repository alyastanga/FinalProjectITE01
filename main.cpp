#include <iostream>
#include <string>
#include <vector>

// Base class representing a User
class User {
protected:
    std::string name;
    std::string role;

public:
    User(const std::string& name, const std::string& role) : name(name), role(role) {}
    virtual void displayInfo() const {
        std::cout << "Name: " << name << "\nRole: " << role << std::endl;
    }
    std::string getName() const { return name; }
    std::string getRole() const { return role; }
    virtual ~User() = default;
};

// Derived classes for different types of users
class Parent : public User {
public:
    Parent(const std::string& name) : User(name, "Parent") {}
};

class Student : public User {
public:
    Student(const std::string& name) : User(name, "Student") {}
};

class Teacher : public User {
public:
    Teacher(const std::string& name) : User(name, "Teacher") {}
};

// Class representing a Ticket
class Ticket {
private:
    int id;
    std::string concern;
    std::string department;
    User* createdBy;

public:
    Ticket(int id, const std::string& concern, const std::string& department, User* createdBy)
        : id(id), concern(concern), department(department), createdBy(createdBy) {}

    void displayTicket() const {
        std::cout << "Ticket ID: " << id
                  << "\nConcern: " << concern
                  << "\nDepartment: " << department
                  << "\nCreated by: " << createdBy->getName()
                  << " (" << createdBy->getRole() << ")\n"
                  << std::endl;
    }
};

// Class to manage multiple tickets
class TicketingSystem {
private:
    std::vector<Ticket> tickets;
    int ticketCounter = 0;

public:
    // Function to create a new ticket with inputs
    void createTicket(const std::string& concern, const std::string& department, User* user) {
        ticketCounter++;
        Ticket newTicket(ticketCounter, concern, department, user);
        tickets.push_back(newTicket);
        std::cout << "\nTicket Created Successfully!\nTicket ID: " << ticketCounter << "\n" << std::endl;
    }

    // Function to display all tickets
    void displayAllTickets() const {
        std::cout << "Displaying All Tickets:\n";
        for (const auto& ticket : tickets) {
            ticket.displayTicket();
        }
    }
};

// Function to get input for creating a new ticket
void inputTicket(TicketingSystem& system, std::vector<User*>& users) {
    std::string concern, department;
    int userChoice;
    char createMore;

    do {
        std::cout << "\nEnter concern: ";
        std::getline(std::cin, concern);

        std::cout << "Enter department (e.g., Academic, Discipline, Administration): ";
        std::getline(std::cin, department);

        std::cout << "Select the creator of the ticket:\n";
        for (size_t i = 0; i < users.size(); ++i) {
            std::cout << i + 1 << ". " << users[i]->getName() << " (" << users[i]->getRole() << ")\n";
        }
        std::cout << "Choice: ";
        std::cin >> userChoice;
        std::cin.ignore();  // Ignore remaining newline character

        if (userChoice >= 1 && userChoice <= static_cast<int>(users.size())) {
            system.createTicket(concern, department, users[userChoice - 1]);
        } else {
            std::cout << "Invalid choice. Ticket not created.\n";
        }

        std::cout << "Do you want to create another ticket? (y/n): ";
        std::cin >> createMore;
        std::cin.ignore();  // Ignore remaining newline character

    } while (createMore == 'y' || createMore == 'Y');
}

int main() {
    TicketingSystem system;

    // Creating some user objects
    Parent parent1("John Doe");
    Student student1("Jane Smith");
    Teacher teacher1("Mr. Brown");

    // Store users in a vector for easy access
    std::vector<User*> users = { &parent1, &student1, &teacher1 };

    char choice;
    do {
        std::cout << "\n--- Ticketing System ---\n";
        std::cout << "1. Create a new ticket\n";
        std::cout << "2. Display all tickets\n";
        std::cout << "3. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cin.ignore();  // Ignore remaining newline character

        switch (choice) {
            case '1':
                inputTicket(system, users);  // Allows multiple tickets to be created without going back to menu
                break;
            case '2':
                system.displayAllTickets();
                break;
            case '3':
                std::cout << "Exiting the program.\n";
                break;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != '3');

    return 0;
}
