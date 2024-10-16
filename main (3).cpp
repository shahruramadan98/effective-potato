
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

//superclass user for vendor and customer 
//inheritance
class User {
    protected:
        string name;
        string address;
    
    public:
        User(const string& n, const string& a) : name(n), address(a) {}

        void setName(const string& n) 
        {
            name = n;
        }

        string getName() const {
            return name;
        }

        void setAddress(const string& a) {
            address = a;
        }

        string getAddress() const {
            return address;
        }

        //polymorphism concept
        virtual void displayInfo() const = 0; 
};

class Item {
    private:
        string itemName;
        float itemPrice;
    public:
        void setName(const string& name) {
            itemName = name;
        }

        string getName() const {
            return itemName;
        }

        void setPrice(float price) {
            itemPrice = price;
        }

        float getPrice() const {
            return itemPrice;
        }

        void displayItem() const {
            cout << "Item: " << itemName << "\nPrice: RM" << itemPrice << endl;
        }
};

class Menu {
    private:
        string menuName;
        vector<Item> items;
    public:
        void setMenuName(const string& name) {
            menuName = name;
        }

        string getMenuName() const {
            return menuName;
        }

        void addOrderItem(const Item& newItem) {
            items.push_back(newItem);
        }

        void displayMenu() const {
            cout << "------------------------------------------------\n";
            cout << "Menu '" << menuName << "' Items:\n";

            //using iomanip format
            // Set the width for the item number column
            const int itemNumberWidth = 4;

            for (size_t i = 0; i < items.size(); ++i) {
                cout << setw(itemNumberWidth) << right << i + 1 << ". ";

                // Set the width for item name and price columns
                const int itemNameWidth = 20;
                const int itemPriceWidth = 10;

                // Display item name and price with proper alignment
                cout << left << setw(itemNameWidth) << items[i].getName();
                cout << right << setw(itemPriceWidth) << fixed << setprecision(2) << "RM" << items[i].getPrice() << endl;
            }
            cout << "------------------------------------------------\n";
        }

        void inputItem() {
            Item newItem;
            string name;
            float price;

            cout << "Enter item name: ";
            getline(cin, name);
            newItem.setName(name);

            cout << "Enter item price: RM";
            cin >> price;
            cin.ignore(); 
            newItem.setPrice(price);

            addOrderItem(newItem);
            cout << "\nItem added to the menu...\n";
        }

        void removeOrderItem(const string& itemName) {
            for (auto it = items.begin(); it != items.end(); ++it) {
                if (it->getName() == itemName) {
                    it = items.erase(it);
                    cout << "\nItem '" << itemName << "' removed from the menu.\n";
                    return;
                }
            }
            cout << "Item '" << itemName << "' not found in the menu.\n";
        }

        Item getItemAtIndex(int index) const {
            if (index >= 0 && index < items.size()) {
                return items[index];
            } else {
                
                return Item();
            }
        }

        size_t getMenuSize() const {
            return items.size();
        }
};

//subclass vendor inherited from user class
class Vendor : public User {
    private:
        vector<Menu> menus;
    public:
        Vendor() : User("", "") {}
        Vendor(const string& n, const string& a) : User(n, a) {}

        void addMenu(const Menu& newMenu) {
            menus.push_back(newMenu);
        }
        
        void displayAllMenus() const {
            cout << "This is your summary =>" << endl;
            cout << "Vendor: " << getName() << " - Location: " << getAddress() << endl;
            for (size_t i = 0; i < menus.size(); ++i) {
                cout << "Menu " << i + 1 << ": " << menus[i].getMenuName() << endl;
                menus[i].displayMenu();
                cout << endl;
            }
        }

        vector<Menu> getMenus() const {
            return menus;
        }

        //polymorphism concept
        void displayInfo() const override {
            cout << "\n*******************************\n";
            cout << "Hello, " << getName() << "!" << endl;
            cout << "Location: " << getAddress() << endl;
            cout << "*******************************\n\n";
        }
};

class Order {
    private:
        vector<Item> orderItems;
        vector<int> quantities;
        float deliveryFee;
    public:
        Order() : deliveryFee(0.0f) {}

        void addOrderItem(const Item &item, int quantity) {
            orderItems.push_back(item);
            quantities.push_back(quantity);
        }

        void setDeliveryFee(float fee) {
            deliveryFee = fee;
        }

        void displayOrder() const {
            if (orderItems.empty())
            {
                cout << "order empty. \n";
                return;
            }

            cout << "\nYour final order details: \n";
            float totalCost = 0.0f;
            for (size_t i = 0; i < orderItems.size(); ++i)
            {
                orderItems[i].displayItem();
                cout << "Quantity: " << quantities[i] << "\n";
                cout << "----------------------------\n";
                totalCost += (orderItems[i].getPrice() * quantities[i]);
            }
            
        }

        float getTotalCost() const {
            float totalCost = 0.0f;
            for (size_t i = 0; i < orderItems.size(); ++i)
            {
                totalCost += (orderItems[i].getPrice() * quantities[i]);
            }
            totalCost += deliveryFee;
            return totalCost;
        }
};

class Payment {
    private:
        float amount;
        string paymentMethod;
    public:
        void setAmount(float amt) {
            amount = amt;
        }

        float getAmount() const {
            return amount;
        }

        void setPaymentMethod(string method) {
            paymentMethod = method;
        }

        string getPaymentMethod() const {
            return paymentMethod;
        }

        void processPayment(const Order &order) const {
            cout << "processing payment...\n";
            cout << "Payment of RM" << order.getTotalCost() << " using " << paymentMethod << " is successful. \n";
        }

        void generateReceipt(string message) const {
            cout << "----------------------------\n";
            cout << "RECEIPT\n";
            cout << "Amount: RM" << amount << "\n";
            cout << "Payment Method: " << paymentMethod << "\n";
            cout << message << "\n";
        }
};

//subclass customer inherited from user class
class Customer : public User {
    private:
        string emailAddress;
        string paymentMethod;
        string phoneNumber;
        const int MAX_ITEMS = 100;
    public:
        Customer() : User("", ""), emailAddress(""), phoneNumber(""), paymentMethod("") {} 

        Customer(const string& n, const string& a, const string& e, const string& p, const string& m)
        : User(n, a), emailAddress(e), phoneNumber(p), paymentMethod(m) {}


        void setEmailAddress(const string& email) {
            emailAddress = email;
        }

        string getEmailAddress() const{
            return emailAddress;
        }

        void setPhoneNumber(const string& phone) {
            phoneNumber = phone;
        }

        string getPhoneNumber() const {
            return phoneNumber;
        }

        void setPaymentMethod(const string& method) {
            paymentMethod = method;
        }

        string getPaymentMethod() const {
            return paymentMethod;
        }


        void viewMenuWithSelection(vector<Menu>& menus, Item orderItems[], int quantities[], int& numItems) {
            int menuChoice;
            cout << "\nAvailable Menus:\n";
            for (size_t i = 0; i < menus.size(); ++i) {
                cout << i + 1 << ". " << menus[i].getMenuName() << endl;
            }
            cout << "Choose a menu (1-" << menus.size() << "): ";
            cin >> menuChoice;
            cin.ignore();

            if (menuChoice >= 1 && menuChoice <= menus.size()) {
                Menu selectedMenu = menus[menuChoice - 1];

                int choice;
                do {
                    selectedMenu.displayMenu();
                    cout << "Enter the item number to add to your order (0 to exit): ";
                    cin >> choice; 
                    cin.ignore();

                    if (choice == 0 || numItems >= MAX_ITEMS) {
                        break;
                    }

                    if (choice > 0 && choice <= selectedMenu.getMenuSize()) {
                        Item selectedItem = selectedMenu.getItemAtIndex(choice - 1);

                        cout << "Enter the quantity for " << selectedItem.getName() << ": ";
                        int quantity;
                        cin >> quantity;
                        cin.ignore();

                        orderItems[numItems] = selectedItem;
                        quantities[numItems] = quantity;
                        ++numItems;

                        cout << "\nItem added to your order.\n\n";
                    } else {
                        cout << "Invalid item number. Please enter a valid item number (0 to exit): ";
                    }
                } while (choice != 0);
            } else {
                cout << "Invalid menu choice. Please choose a valid menu.\n";
            }
        }

        void displayOrder(const Item orderItems[], const int quantities[], int numItems) const {
            if (numItems == 0) {
                cout << "Your order is empty.\n";
                return;
            }

            cout << "\nYour Order:\n";
            cout << "----------------------------\n";
            for (int i = 0; i < numItems; ++i) {
                cout << "\nItem: " << orderItems[i].getName() << "\nQuantity: " << quantities[i] << "\n";
            }
            cout << "\n----------------------------\n";
        }

        //polymorphism concept
        void displayInfo() const override 
        {
            cout << "\n*******************************\n";
            cout << "Hello, " << getName() << "!" << endl;
            cout << "Phone Number: " << getPhoneNumber() << endl;
            cout << "Email: " << getEmailAddress() << endl;
            if (!address.empty()) {
                cout << "Address:  " << getAddress() << endl;
            }
            cout << "You choose to pay by: " << getPaymentMethod() << endl;
            cout << "*******************************\n";
        }

        void removeOrderItem(Item orderItems[], int quantities[], int& numItems) {
            if (numItems == 0) {
                cout << "Your order is empty.\n";
                return;
            }

            cout << "\nCurrent Order:\n";
            for (int i = 0; i < numItems; ++i) {
                cout << i + 1 << ". " << orderItems[i].getName() << " - Quantity: " << quantities[i] << endl;
            }

            int choice;
            do {
                cout << "Enter the item number to remove from your order (0 to exit): ";
                cin >> choice;
                cin.ignore();

                if (choice == 0 || numItems <= 0) {
                    break;
                }

                if (choice > 0 && choice <= numItems) {
                    
                    for (int i = choice - 1; i < numItems - 1; ++i) {
                        orderItems[i] = orderItems[i + 1];
                        quantities[i] = quantities[i + 1];
                    }
                    --numItems;
                    cout << "Item removed from your order.\n";
                } else {
                    cout << "Invalid item number. Please enter a valid item number (0 to exit): ";
                }
            } while (choice != 0);
        }
};

// Process payment
void makePayment(const Order &order, const Payment &payment) {
    cout << "Total amount to pay: RM" << order.getTotalCost() << "\n";

    // Validate payment method and amount
    if (payment.getAmount() >= order.getTotalCost())
    {
        
        payment.processPayment(order);
    }
            
};

void displayTitle(const string& title) {
    int width = 100; // Fixed width
    cout << string(width, '-') << endl;
    cout << string((width - title.length()) / 2, ' ') << title << endl;
    cout << string(width, '-') << endl;
    cout << endl;
}

void displayMainMenu() {
    cout << "Please choose the role: " << endl;
    cout << "[1] Vendor Administrator" << endl;
    cout << "[2] Customer" << endl;
    cout << "[0] Exit" << endl;
    cout << "Enter your choice: ";
}

int main() {
    Vendor vendor;
    Item orderItems[100];
    int quantities[100];
    int numItems = 0;
    int role;
    const float DELIVERY_FEE = 5.0f; // delivery fee for delivery selection

    do {
            displayTitle("Welcome to EatnGo Ordering System");
            displayMainMenu();
            cin >> role;

            switch (role) {
            //Role: Vendor Administrator
            case 1: {
                displayTitle("Vendor Menu");
                string name, location;
                cout << "Enter your Vendor name: ";
                cin.ignore();
                getline(cin, name);
                cout << "Enter your Vendor location: ";
                getline(cin, location);

                vendor.setName(name);
                vendor.setAddress(location);
                vendor.displayInfo();

                int numMenus;
                cout << "How many menus do you want to create: ";
                cin >> numMenus;
                cin.ignore();

                for (int i = 0; i < numMenus; ++i) {
                    Menu newMenu;
                    string menuName;
                    cout << "Enter name for Menu " << i + 1 << ": ";
                    getline(cin, menuName);
                    newMenu.setMenuName(menuName);

                    int choice;
                    do {
                        cout << "\n1. Display Menu\n2. Add Item to Menu\n3. Remove Item from Menu\n0. Exit\n\n";
                        cout << "Enter your choice: ";
                        cin >> choice;
                        cin.ignore(); // Clear the newline from the input buffer

                        switch (choice) {
                            case 1:
                                newMenu.displayMenu();
                                break;
                            case 2:
                                newMenu.inputItem();
                                break;
                            case 3: {
                                string itemName;
                                cout << "Enter the name of the item to remove: ";
                                getline(cin, itemName);
                                newMenu.removeOrderItem(itemName);
                                break;
                            }
                            case 0:
                                cout << "Exiting Menu Creation...\n\n";
                                break;
                            default:
                                cout << "Invalid choice. Try again.\n";
                        }
                    } while (choice != 0);
                    vendor.addMenu(newMenu);
                }
                vendor.displayAllMenus();
                break; // Exit the vendor role section
            }

            //Role: Customer
            case 2: {
                displayTitle("Customer Menu");
                int choice;

                cout << "Please select your order method" << endl;
                cout << "[1] Pick-up" << endl;
                cout << "[2] Delivery" << endl;
                cout << "Enter your choice: ";
                cin >> choice;

                switch (choice)
                {
                //pickup selection
                case 1: {
                    Customer customer;
                    string name, email, phone;
                    int paymentChoice;

                    cout << "\nYou've choosen Pick-up." << endl;
                    cout << "Enter your name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter your contact number: ";
                    getline(cin, phone);
                    cout << "Enter your email address: ";
                    getline(cin, email);
                    cout << "Payment Options:\n[1] Cash\n[2] Credit/Debit Card\nEnter your payment method: ";
                    cin >> paymentChoice;
            
                    if (paymentChoice == 1) {
                    customer.setPaymentMethod("Cash");
                    } else if (paymentChoice == 2) {
                    customer.setPaymentMethod("Credit/Debit Card");
                    } else {
                    cout << "Invalid payment choice. Defaulting to Cash.\n";
                    customer.setPaymentMethod("Cash"); // Defaulting to Cash for invalid input
                    }
                    
                    customer.setName(name);
                    customer.setPhoneNumber(phone);
                    customer.setEmailAddress(email);
                    customer.displayInfo();
                    
                    int customerChoice;
                    do {
                        vector<Menu> vendorMenus = vendor.getMenus();
                        cout << "\n[1] Add Item to Order." << endl;
                        cout << "[2] Display Your Order" << endl;
                        cout << "[3] Remove Item from Order" << endl;
                        cout << "[0] Done Ordering" << endl;
                        cout << "Enter your choice: ";
                        cin >> customerChoice;
                        cin.ignore();

                        switch (customerChoice) {
                            case 1:
                                customer.viewMenuWithSelection(vendorMenus, orderItems, quantities, numItems);
                                break;
                            case 2:
                                customer.displayOrder(orderItems, quantities, numItems); // Display order
                                break;
                            case 3:
                                customer.removeOrderItem(orderItems, quantities, numItems);
                                break;    
                            case 0:
                                cout << "Exiting..." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Try again" << endl;
                        }
                    } while (customerChoice !=0);
                    
                    // Display the final order
                    Order customerOrder;
                    for (int i = 0; i < numItems; ++i) {
                        customerOrder.addOrderItem(orderItems[i], quantities[i]);
                    }
                    customerOrder.displayOrder();

                    // Payment
                    Payment customerPayment;
                    customerPayment.setAmount(customerOrder.getTotalCost());
                    customerPayment.setPaymentMethod(customer.getPaymentMethod()); // Use the customer's selected method
                    makePayment(customerOrder, customerPayment);
                    customerPayment.generateReceipt("Thank you for your order! Your order will be processed.\n\n");
                    
                    break;
                }
                
                //delivery selection
                case 2: {
                    Customer customer;
                    string name, address, phone, email;
                    int paymentChoice;

                    cout << "\nYou've choosen Delivery." << endl;
                    cout << "Enter your name: ";
                    cin.ignore();
                    getline(cin, name);
                    cout << "Enter delivery address: ";
                    getline(cin, address);
                    cout << "Enter your contact number: ";
                    getline(cin, phone);
                    cout << "Enter your email address: ";
                    getline(cin, email);
                    cout << "Payment Options:\n[1] Cash on Delivery\n[2] Credit/Debit Card\nEnter your payment method (1 or 2): ";
                    cin >> paymentChoice;
            
                    if (paymentChoice == 1) {
                    customer.setPaymentMethod("Cash on Delivery");
                    } else if (paymentChoice == 2) {
                    customer.setPaymentMethod("Credit/Debit Card");
                    } else {
                    cout << "Invalid payment choice. Defaulting to Cash.\n";
                    customer.setPaymentMethod("Cash on Delivery"); // Defaulting to Cash on Delivery for invalid input
                    }
                    
                    customer.setName(name);
                    customer.setAddress(address);
                    customer.setPhoneNumber(phone);
                    customer.setEmailAddress(email);
                    customer.displayInfo();
                    
                    int customerChoice;
                    do {
                        vector<Menu> vendorMenus = vendor.getMenus();
                        cout << "\n[1] Add Item to Order." << endl;
                        cout << "[2] Display Your Order" << endl; 
                        cout << "[3] Remove Item from Order" << endl;
                        cout << "[0] Done Ordering" << endl;
                        cout << "Enter your choice: ";
                        cin >> customerChoice;
                        cin.ignore();

                        switch (customerChoice) {
                            case 1:
                                customer.viewMenuWithSelection(vendorMenus, orderItems, quantities, numItems);
                                break;
                            case 2:
                                customer.displayOrder(orderItems, quantities, numItems); 
                                break;
                            case 3:
                                customer.removeOrderItem(orderItems, quantities, numItems);
                                break;  
                            case 0:
                                cout << "Exiting..." << endl;
                                break;
                            default:
                                cout << "Invalid choice. Try again" << endl;
                        }
                    } while (customerChoice !=0);
                    
                    // Display the final order
                    Order customerOrder;
                    for (int i = 0; i < numItems; ++i) {
                        customerOrder.addOrderItem(orderItems[i], quantities[i]);
                    }

                    customerOrder.displayOrder();
                    cout << "Total cost: RM" << customerOrder.getTotalCost() << endl; //total cost without delivery fee
                    cout << "Delivery Fee: RM" << DELIVERY_FEE << endl;

                    // Set delivery fee
                    customerOrder.setDeliveryFee(DELIVERY_FEE);
                    
                    // Payment
                    Payment customerPayment;
                    customerPayment.setAmount(customerOrder.getTotalCost());
                    customerPayment.setPaymentMethod(customer.getPaymentMethod()); // Use the customer's selected method
                    makePayment(customerOrder, customerPayment);
                    customerPayment.generateReceipt("Thank you for your order! Your order will be deliver soon!\n\n");
                    
                    break;
                }
                    
                default:
                    cout << "Invalid choice. Please select a number between 1 and 2." << endl;
                    break;
                }

                break; // Exit the customer role section
            }
        
            case 0:
                cout << "\nThank you for using this system!\n" << "Exiting the program..." << endl;
                break;

            default:
                cout << "Invalid role selected. Please try again.\n";
            }

        } while (role != 0);

    return 0;
}