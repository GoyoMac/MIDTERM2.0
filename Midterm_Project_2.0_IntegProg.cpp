#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

class Item {
private:
    int id;
    string name;
    int quantity;
    double price;

public:
    Item(int id, string name, int quantity, double price) {
        this->id = id;
        this->name = name;
        this->quantity = quantity;
        this->price = price;
    }

    int getID() const { return id; }
    string getName() const { return name; }
    int getQuantity() const { return quantity; }
    double getPrice() const { return price; }

    void setQuantity(int newQty) { quantity = newQty; }
    void setPrice(double newPrice) { price = newPrice; }
};

void displayHeader() {
    cout << left << setw(10) << "ID"
         << setw(20) << "Name"
         << setw(10) << "Quantity"
         << setw(10) << "Price" << endl;
}

void displayItem(const Item& item) {
    cout << left << setw(10) << item.getID()
         << setw(20) << item.getName()
         << setw(10) << item.getQuantity()
         << setw(10) << fixed << setprecision(2) << item.getPrice() << endl;
}

int main() {
    vector<Item> inventory;
    int nextID = 1;
    int choice;

    while (true) {
        cout << "\nMenu\n";
        cout << "1 - Add Item\n";
        cout << "2 - Update Item\n";
        cout << "3 - Remove Item\n";
        cout << "4 - Display All Items\n";
        cout << "5 - Search Item\n";
        cout << "6 - Sort Items\n";
        cout << "7 - Display Low Stock Items\n";
        cout << "8 - Exit\n";
        cout << "\nEnter choice: ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        if (choice == 1) {
            string name;
            int quantity;
            double price;
            cin.ignore();

            cout << "\nEnter item name: ";
            getline(cin, name);
            cout << "Enter quantity: ";
            cin >> quantity;
            cout << "Enter price: ";
            cin >> price;

            inventory.push_back(Item(nextID++, name, quantity, price));
            cout << "Item added successfully!\n";
        }

        else if (choice == 2) {
            int id;
            cout << "\nEnter product ID to update: ";
            cin >> id;

            bool found = false;
            for (auto& item : inventory) {
                if (item.getID() == id) {
                    found = true;
                    int updateChoice;
                    cout << "Update (1) Quantity or (2) Price?: ";
                    cin >> updateChoice;

                    if (updateChoice == 1) {
                        int oldQty = item.getQuantity(), newQty;
                        cout << "Enter new quantity: ";
                        cin >> newQty;
                        item.setQuantity(newQty);
                        cout << "Quantity of Item " << item.getName()
                             << " is updated from " << oldQty << " to " << newQty << "\n";
                    } else {
                        double oldPrice = item.getPrice(), newPrice;
                        cout << "Enter new price: ";
                        cin >> newPrice;
                        item.setPrice(newPrice);
                        cout << "Price of Item " << item.getName()
                             << " is updated from " << oldPrice << " to " << newPrice << "\n";
                    }
                    break;
                }
            }
            if (!found) {
                cout << "Item not found!\n";
            }
        }

        else if (choice == 3) {
            int id;
            cout << "Enter item ID to remove: ";
            cin >> id;

            bool found = false;
            for (int i = 0; i < inventory.size(); i++) {
                if (inventory[i].getID() == id) {
                    found = true;
                    cout << "Item " << inventory[i].getName() << " has been removed from the inventory\n";
                    inventory.erase(inventory.begin() + i);
                    break;
                }
            }
            if (!found) {
                cout << "Item not found!\n";
            }
        }

        else if (choice == 4) {
            if (inventory.empty()) {
                cout << "No items in inventory.\n";
            } else {
                cout << "\nAll Items:\n";
                displayHeader();
                for (const auto& item : inventory) {
                    displayItem(item);
                }
            }
        }

        else if (choice == 5) {
            int id;
            cout << "\nEnter product ID to search: ";
            cin >> id;

            bool found = false;
            for (const auto& item : inventory) {
                if (item.getID() == id) {
                    cout << "\nItem found:\n";
                    displayHeader();
                    displayItem(item);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Item not found!\n";
            }
        }

        else if (choice == 6) {
            int sortField, sortOrder;
            cout << "\nSort by (1) Quantity or (2) Price? ";
            cin >> sortField;
            cout << "Sort (1) Ascending or (2) Descending? ";
            cin >> sortOrder;

            if (sortField == 1) {
                if (sortOrder == 1) {
                    sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
                        return a.getQuantity() < b.getQuantity();
                    });
                } else {
                    sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
                        return a.getQuantity() > b.getQuantity();
                    });
                }
            } else {
                if (sortOrder == 1) {
                    sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
                        return a.getPrice() < b.getPrice();
                    });
                } else {
                    sort(inventory.begin(), inventory.end(), [](const Item& a, const Item& b) {
                        return a.getPrice() > b.getPrice();
                    });
                }
            }

            cout << "\nSorted Items:\n";
            displayHeader();
            for (const auto& item : inventory) {
                displayItem(item);
            }
        }

        else if (choice == 7) {
            cout << "\nLow Stock Items (quantity ≤ 5):\n";
            displayHeader();
            bool hasLowStock = false;
            for (const auto& item : inventory) {
                if (item.getQuantity() <= 5) {
                    displayItem(item);
                    hasLowStock = true;
                }
            }
            if (!hasLowStock) {
                cout << "No low stock items found.\n";
            }
        }

        else if (choice == 8) {
            cout << "Exiting program.\n";
            break;
        }

        else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
