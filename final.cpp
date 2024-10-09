#include <iostream>
#include <string>
#include <vector>
#include <map>

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
        std::cout << "Ticket ID: " << id << "\nConcern: " << concern
                  << "\nDepartment: " << department << "\nCreated by: " << createdBy->getName()
                  << " (" << createdBy->getRole() << ")\n" << std::endl;
    }

    int getId() const { return id; }
    std::string getCreatorName() const { return createdBy->getName(); }
};

// Class to manage multiple tickets
class TicketingSystem {
private:
    std::vector<Ticket> tickets;
    int ticketCounter = 0;
    std::map<int, User*> ticketOwners;  // Maps ticket ID to the user who created it

public:
    // Creates a new ticket and assigns a unique ID
    void createTicket(const std::string& concern, const std::string& department, User* user) {
        ticketCounter++;
        Ticket newTicket(ticketCounter, concern, department, user);
        tickets.push_back(newTicket);
        ticketOwners[ticketCounter] = user;  // Store who created the ticket
        std::cout << "Ticket Created Successfully! Ticket ID: " << ticketCounter << std::endl;
    }

    // Displays all tickets in the system
    void displayAllTickets() const {
        std::cout << "Displaying All Tickets:\n";
        for (const auto& ticket : tickets) {
            ticket.displayTicket();
        }
    }

    // Displays the creator of a specific ticket by ID
    void displayTicketCreator(int ticketId) const {
        auto it = ticketOwners.find(ticketId);
        if (it != ticketOwners.end()) {
            std::cout << "Ticket ID: " << ticketId << " was created by: " 
                      << it->second->getName() << " (" << it->second->getRole() << ")\n";
        } else {
            std::cout << "Ticket ID: " << ticketId << " not found.\n";
        }
    }
};

int main() {
    TicketingSystem sysstem;

    // Creating some users
    Parent parent1("John Doe");
    Student student1("Jane Smith");
    Teacher teacher1("Mr. Brown");

    // Creating tickets for different concerns
    system.createTicket("Grade issue", "Academic", &student1);
    system.createTicket("Bullying incident", "Discipline", &parent1);
    system.createTicket("Classroom resources request", "Administration", &teacher1);

    // Display all tickets
    system.displayAllTickets();

    // Display the creator of a specific ticket by ticket ID
    system.displayTicketCreator(1);
    system.displayTicketCreator(2);

    return 0;
}
