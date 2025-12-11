#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"
#define BLUE    "\033[34m"
#define MAGENTA "\033[35m"
#define CYAN    "\033[36m"
#define WHITE   "\033[37m"

using namespace std;

//MEDICINE CLASS
class Medicine {
private:
    int id;
    string name;
    string category;
    double price;
    int quantity;
    

public:
    Medicine() {}
    Medicine(int id, string name, string category, double price, int quantity ) {
        this->id = id;
        this->name = name;
        this->category = category;
        this->price = price;
        this->quantity = quantity;
        
    }

    // Setters
    void setId(int id) { this->id = id; }
    void setName(string name) { this->name = name; }
    void setCategory(string category) { this->category = category; }
    void setPrice(double price) { this->price = price; }
    void setQuantity(int quantity) { this->quantity = quantity; }
    

    // Getters
    int getId() const { return id; }
    string getName() const { return name; }
    string getCategory() const { return category; }
    double getPrice() const { return price; }
    int getQuantity() const { return quantity; }
    

    void display() const {
        cout << left << setw(5) << id
             << setw(15) << name
             << setw(15) << category
             << setw(10) << price
             << setw(8) << quantity;

        if (quantity <= 5) {
            cout << RED << "  **LOW STOCK!**" << RESET;
        }

        cout << endl;
    }
};

// BILLING CLASS
class Billing {
public:
    void generateBill(vector<Medicine> &medicines) {
        if (medicines.empty()) {
            cout << RED << "\n**Oops!! No medicines available for billing.**\n" << RESET;
            return;
        }

        int id, qty;
        char choice;
        double total = 0.0;

        ofstream out("bill.txt");
        out << "====== PHARMACY BILL ======\n";

        cout << GREEN << "\n~~~ GENERATE BILL ~~~ \n" << RESET;

        do {
            cout << "\nEnter Medicine ID to purchase: ";
            cin >> id;

            bool found = false;
            for (auto &m : medicines) {
                if (m.getId() == id) {

                    if (m.getQuantity() == 0) {
                        cout << RED << "**Medicine is OUT OF STOCK!**\n" << RESET;
                        found = true;
                        break;
                    }

                    cout << "Enter Quantity: ";
                    cin >> qty;

                    if (qty <= m.getQuantity()) {
                        double price = qty * m.getPrice();
                        total += price;
                        m.setQuantity(m.getQuantity() - qty);

                        cout << "--> " << m.getName() << " x " << qty << " = Rs." << price << endl;

                        out << m.getName() << "  x" << qty << "  = Rs." << price << "\n";

                        // Low stock message
                        if (m.getQuantity() <= 5) {
                            cout << RED << "**Low Stock Alert! Only " << m.getQuantity() << " left**\n" << RESET;
                        }

                    } else {
                        cout << RED << "**Oops!! Not enough stock!**\n" << RESET;
                    }
                    found = true;
                    break;
                }
            }
            if (!found)
                cout << RED << "**Oops!! Medicine ID not found!**\n" << RESET;

            cout << "Add another item? (Y/N): ";
            cin >> choice;

        } while (choice == 'y' || choice == 'Y');

        cout << "\n-------------------------------------------\n";
        cout << GREEN << " TOTAL BILL AMOUNT: ₹ " << total << RESET << endl;
        cout << "------------------------------------------\n";
        cout << MAGENTA << "Thank you for shopping!!! Visit Again :) \n" << RESET;

        out << "\nTOTAL AMOUNT = Rs. " << total << "\n";
        out << "=============================\n";
        out.close();

        cout << GREEN << "\nBill saved to bill.txt\n" << RESET;
    }
};

// -------------------- Pharmacy Class --------------------
class Pharmacy {
private:
    vector<Medicine> medicines;
    Billing billing;

public:
    void addMedicine() {
        int id, quantity;
        double price;
        string name, category, expiry;

        cout << "\nEnter medicine ID: "; cin >> id;
        cin.ignore();
        cout << "Enter Name: "; getline(cin, name);
        cout << "Enter Category: "; getline(cin, category);
        cout << "Enter Price: "; cin >> price;
        cout << "Enter Quantity: "; cin >> quantity;
        cin.ignore();
        cout << "Enter Expiry Date (MM/YYYY): "; getline(cin, expiry);

        medicines.push_back(Medicine(id, name, category, price, quantity));
        cout << GREEN << "\n...Medicine added successfully!(Its Done!) :) ...\n" << RESET;
    }

    void showAll() const {
        if (medicines.empty()) {
            cout << RED << "\n**Oops!! No medicines available! :( **\n" << RESET;
            return;
        }

        cout << YELLOW << "\n===========*Available Medicines*===========\n" << RESET;
        cout << left << setw(5) << "ID"
             << setw(15) << "Name"
             << setw(15) << "Category"
             << setw(10) << "Price"
             << setw(8) << "Qty"
             << setw(10) << "Expiry" << endl;
        cout << "---------------------------------------------\n";

        for (const auto &m : medicines)
            m.display();
    }

    void searchMedicine() const {
        if (medicines.empty()) {
            cout << RED << "\n**Oops!! No medicines to search! :( **\n" << RESET;
            return;
        }
        string searchName;
        cin.ignore();
        cout << "\nEnter medicine name to search: ";
        getline(cin, searchName);

        bool found = false;
        for (const auto &m : medicines) {
            if (m.getName() == searchName) {
                cout << GREEN << "\n--> :) Medicine Found: \n" << RESET;
                m.display();
                found = true;
                break;
            }
        }
        if (!found)
            cout << RED << "\n**Oops!! Medicine not found! :( **\n" << RESET;
    }

    void deleteMedicine() {
        if (medicines.empty()) {
            cout << RED << "\n**Oops!! No medicines to delete! :( **\n" << RESET;
            return;
        }
        int id;
        cout << "\nEnter Medicine ID to delete: ";
        cin >> id;

        for (auto it = medicines.begin(); it != medicines.end(); ++it) {
            if (it->getId() == id) {
                medicines.erase(it);
                cout << GREEN << "\n..Medicine deleted successfully!(Its Done!) :) ..\n" << RESET;
                return;
            }
        }
        cout << RED << "\n**Oops!! :( Medicine not found!**\n" << RESET;
    }

    void generateBill() {
        billing.generateBill(medicines);
    }
};

// -------------------- Admin Login --------------------
bool adminLogin() {
    string username, password;
    cin.ignore();
    cout << CYAN << "\n--> Admin Login :) " << RESET << "\nUsername: ";
    getline(cin, username);
    cout << "Password: ";
    getline(cin, password);

    if (username == "admin" && password == "1234") {
        cout << GREEN << "... :) Login Successful!(Here we go)...\n" << RESET;
        return true;
    } else {
        cout << RED << "**Invalid Credentials!**\n" << RESET;
        return false;
    }
}

// -------------------- Main --------------------
int main() {
    Pharmacy pharmacy;
    int mainChoice;

    do {
        cout << YELLOW << "\n****WELCOME TO PHARMACY MANAGEMENT SYSTEM****\n";
        cout<<"---MADE FOR IMPLEMENTING OOPM FEATURES BY SONAKSHI GUPTA---"<<endl;
        cout<<"Enrollment No.-0103AL241402 , Roll. No.- 400 , Section-'F'"<<RESET<<endl;
        cout << "1. Admin Login\n2. Customer Section\n3. Exit\n" << YELLOW << "--> Enter choice: " << RESET;
        cin >> mainChoice;

        if (mainChoice == 1) {
            if (adminLogin()) {
                int choice;
                do {
                    cout << CYAN << "\n----  ADMIN MENU  ----\n" << RESET;
                    cout << "1. Add Medicine\n2. Show Medicines\n3. Search Medicine\n4. Delete Medicine\n5. Logout\n" << CYAN << "--> Enter choice: " << RESET;
                    cin >> choice;

                    switch (choice) {
                        case 1: pharmacy.addMedicine(); break;
                        case 2: pharmacy.showAll(); break;
                        case 3: pharmacy.searchMedicine(); break;
                        case 4: pharmacy.deleteMedicine(); break;
                        case 5: cout << RED << "...Logging out...\n" << RESET; break;
                        default: cout << RED << "**Invalid choice!**\n" << RESET;
                    }
                } while (choice != 5);
            }
        }
        else if (mainChoice == 2) {
            int choice;
            do {
                cout << MAGENTA << "\n----  CUSTOMER MENU  ----\n" << RESET;
                cout << "1. View Medicines\n2. Buy Medicines\n3. Back\n" << MAGENTA << "--> Enter choice: " << RESET;
                cin >> choice;

                switch (choice) {
                    case 1: pharmacy.showAll(); break;
                    case 2: pharmacy.generateBill(); break;
                    case 3: cout << GREEN << "(lets go back!!) Returning...\n" << RESET; break;
                    default: cout << RED << "**Invalid choice!**\n" << RESET;
                }
            } while (choice != 3);
        }
        else if (mainChoice == 3) {
            cout << YELLOW << "**Thank you for using the Pharmacy System! :) **\n" << RESET;
        }
        else {
            cout << RED << "**Invalid choice!**\n" << RESET;
        }

    } while (mainChoice != 3);

    return 0;
}
