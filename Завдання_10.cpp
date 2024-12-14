#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <windows.h>

using namespace std;

// Абстрактний клас для фільмів
class Movie {
protected:
    string title;
    string director;
    int duration; // у хвилинах
public:
    Movie(const string& title, const string& director, int duration)
        : title(title), director(director), duration(duration) {}

    virtual void displayInfo() const = 0; // чисто віртуальний метод
    virtual ~Movie() {}
};

// Наслідувані класи для жанрів фільмів
class ActionMovie : public Movie {
public:
    ActionMovie(const string& title, const string& director, int duration)
        : Movie(title, director, duration) {}

    void displayInfo() const override {
        cout << "Action Movie: " << title << ", directed by " << director
            << ", duration: " << duration << " minutes." << endl;
    }
};

class ComedyMovie : public Movie {
public:
    ComedyMovie(const string& title, const string& director, int duration)
        : Movie(title, director, duration) {}

    void displayInfo() const override {
        cout << "Comedy Movie: " << title << ", directed by " << director
            << ", duration: " << duration << " minutes." << endl;
    }
};

// Інтерфейс для білетів
class Ticket {
public:
    virtual double getPrice() const = 0;
    virtual void displayTicketInfo() const = 0;
    virtual ~Ticket() {}
};

// Наслідувані класи для типів білетів
class StandardTicket : public Ticket {
private:
    double price;
public:
    StandardTicket(double price) : price(price) {}

    double getPrice() const override {
        return price;
    }

    void displayTicketInfo() const override {
        cout << "Standard Ticket, price: " << price << " USD." << endl;
    }
};

class PremiumTicket : public Ticket {
private:
    double price;
public:
    PremiumTicket(double price) : price(price) {}

    double getPrice() const override {
        return price;
    }

    void displayTicketInfo() const override {
        cout << "Premium Ticket, price: " << price << " USD." << endl;
    }
};

// Клас для клієнтів
class Customer {
private:
    string name;
    vector<shared_ptr<Ticket>> tickets;
public:
    Customer(const string& name) : name(name) {}

    void buyTicket(const shared_ptr<Ticket>& ticket) {
        tickets.push_back(ticket);
    }

    double calculateTotalSpent() const {
        double total = 0;
        for (const auto& ticket : tickets) {
            total += ticket->getPrice();
        }
        return total;
    }

    void displayCustomerInfo() const {
        cout << "Customer: " << name << endl;
        cout << "Tickets bought:" << endl;
        for (const auto& ticket : tickets) {
            ticket->displayTicketInfo();
        }
        cout << "Total spent: " << calculateTotalSpent() << " USD." << endl;
    }
};

int main() {
    SetConsoleOutputCP(1251);
    SetConsoleCP(1251);

    // Створення фільмів
    ActionMovie actionMovie("Fast X", " Louis Leterrier", 140);
    ComedyMovie comedyMovie("Deadpool & Wolverine", "Shawn Levy", 129);

    actionMovie.displayInfo();
    comedyMovie.displayInfo();

    // Створення білетів
    auto standardTicket = make_shared<StandardTicket>(10.0);
    auto premiumTicket = make_shared<PremiumTicket>(20.0);

    // Створення клієнта
    Customer customer("John Doe");
    customer.buyTicket(standardTicket);
    customer.buyTicket(premiumTicket);

    customer.displayCustomerInfo();

    return 0;
}
