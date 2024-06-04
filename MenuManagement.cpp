#include "InventoryFile.cpp"
#include <iomanip> // For std::setw

struct menu_item
{
    string name;
    float price;
    string category;
    float sellprice;
};
struct inventory_item
{
    string name;
    float price;
    int quantity;
    char status;
};

class MenuManagement:public Inventory{
private:
    vector<menu_item> items;
    vector<string> categories = {"appetizer", "entree", "dessert",
                                 "beverage", "pizza", "pasta", "burger"};

public:
    MenuManagement() {}
    bool isInstock(string ingredientName)
    {
        ifstream inFile("inventory.txt");
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string name, price, quantity, status;
            getline(ss, name, ',');
            getline(ss, price, ',');
            getline(ss, quantity, ',');
            getline(ss, status, ',');
            if (name == ingredientName && status == "Y")
            {
                inFile.close();
                return true;
            }
        }
        inFile.close();
        return false;
    }
    
    void displayInventory()
    {
        ifstream inFile("inventory.txt");
        string line;
        int i;
         i = 0;
        while (getline(inFile, line))
        {
           
            stringstream ss(line);
            string name;
            getline(ss, name, ',');
            cout << i + 1 << ")" << name << endl;
            i++;
        }
        inFile.close();
    }

    float getPrice(string ingredientName)
    {
        ifstream inFile("inventory.txt");
        string line;
        while (getline(inFile, line))
        {
            stringstream ss(line);
            string name, priceStr, quantityStr, status;
            getline(ss, name, ',');
            getline(ss, quantityStr, ',');
            getline(ss, priceStr, ',');
            getline(ss, status, ',');
            if (name == ingredientName)
            {
                inFile.close();
                return stof(priceStr);
            }
        }
        inFile.close();
        return 0.0;
    }

void additems()
    {
        try
        {
            ifstream inFile("menu.csv");
            string text;
            set<string> names;
            vector<float> price_of_item;
                string ingredientName;
            while (getline(inFile, text))
            {
                stringstream ss(text);
                string name;
                getline(ss, name, ',');
                names.insert(name);
            }
            inFile.close();

            cout << "How many items do you want to add?" << endl;
            int n;
            cin >> n;
            cin.ignore();

            for (int i = 0; i < n; i++)
            {
                menu_item newItem;

                while (true)
                {
                    cout << "Enter the name: " << endl;
                    getline(cin, newItem.name);
                    if (names.find(newItem.name) != names.end())
                    {
                        cout << "Item already exists" << endl;
                        continue;
                    }
                    if (Valid(newItem.name))
                    {
                        break;
                    }
                    else
                    {
                        cout << "Invalid, please enter again :)" << endl;
                    }
                }

                vector<string> ingredients;
                while (true)
                {
                    displayInventory();
                    cout << "Choose the ingredient please: " << endl;

                    cin >> ingredientName;
                    cin.ignore();

                    if (!validateIngredients(ingredientName))
                    {
                        cout << "Invalid ingredient. Please choose a valid ingredient." << endl;
                        continue;
                    }

                    if (!isInstock(ingredientName))
                    {
                        string answer;
                        cout << "The ingredient is out of stock. Please choose another ingredient." << endl;
                        cout<<"do you want to restock?(yes/no)"<<endl;
                        cin>>answer;
                        if(answer=="yes"){
                            restock();
                        }
                        continue;
                    }

                    ifstream inventoryFile("inventory.txt");
                    vector<inventory_item> inventory;
                    string line;

                    while (getline(inventoryFile, line))
                    {
                        stringstream ss(line);
                        string token;
                        vector<string> tokens;

                        while (getline(ss, token, ','))
                        {
                            tokens.push_back(token);
                        }

                        inventory_item item;
                        item.name = tokens[0];
                        item.quantity = stoi(tokens[1]);
                        item.price = stof(tokens[2]);
                        item.status = tokens[3][0];

                        inventory.push_back(item);
                    }

                    inventoryFile.close();

                    for (inventory_item &item : inventory)
                    {
                        if (item.name == ingredientName)
                        {
                            item.quantity--;
                            if (item.quantity == 0)
                            {
                                item.status = 'N';
                            }
                            break;
                        }
                    }

                    ofstream inventoryFileOut("inventory.txt");

                    for (const auto &item : inventory)
                    {
                        inventoryFileOut << item.name << "," << item.quantity << "," << item.price << "," << item.status << "\n";
                    }

                    inventoryFileOut.close();

                    float price = getPrice(ingredientName);
                    price_of_item.push_back(price);
                    ingredients.push_back(ingredientName);

                    cout << "Do you want to add more ingredients? (yes/no)" << endl;
                    string answer;
                    getline(cin, answer);
                    if (answer == "no")
                    {
                        break;
                    }
                }

                float total = 0.0;
                for (float price : price_of_item)
                {
                    total += price;
                }
                float profit = total + 1.05;
                newItem.sellprice=profit;
            
                  

                string total_str_price = to_string(total);
                string profit_str = to_string(profit);
                for ( auto &category : categories) {
                     cout << category << endl;
                }
                while (true)
                {   
                    cout << "Enter the category: " << endl;
                    getline(cin, newItem.category);
                    if (find(categories.begin(), categories.end(), newItem.category) != categories.end())
                    {
                        cout << "Adding: " << newItem.name << " with price " << total << endl;
                        ofstream outFile("menu.csv", ios::app);
                        outFile << newItem.name << "," << total_str_price << "," << newItem.category<<","<< profit_str<< endl;
                        outFile.close();
                        names.insert(newItem.name);
                        break;
                    }
                    else
                    {
                        cout << "Invalid, please enter valid category :)" << endl;
                    }
                }
            }
        }
        catch (const exception &e)
        {
            cerr << "Exception caught: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Unknown exception caught" << endl;
        }
    }

    void RemoveItems()
    {
        try
        {
            cout << "How many items do you want to remove?" << endl;
            int n;
            cin >> n;
            vector<string> Removed_items;
            string thing;

            for (int i = 0; i < n; i++)
            {
                cout << "Enter name of item to be removed " << i + 1 << ": " << endl;
                cin >> thing;
                Removed_items.push_back(thing);
            }

            ifstream file("menu.csv");
            if (!file)
            {
                cerr << "Unable to open file :(" << endl;
                return;
            }

            ofstream newFile("newMenu.csv");

            string line, item;
            while (getline(file, line))
            {
                istringstream ss(line);
                getline(ss, item, ',');
                if (find(Removed_items.begin(), Removed_items.end(), item) == Removed_items.end())
                {
                    newFile << line << endl;
                }
            }

            file.close();
            newFile.close();
            remove("menu.csv");
            rename("newMenu.csv", "menu.csv");
        }
        catch (const exception &e)
        {
            cerr << "Exception caught: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Unknown exception caught" << endl;
        }
    }

    void UpdateItem()
    {
        try
        {
            ifstream inFile("menu.csv");
            if (!inFile)
            {
                throw runtime_error("Error opening file for reading");
            }

            string line;
            while (getline(inFile, line))
            {
                istringstream ss(line);
                string itemName, itemPrice, itemCategory,itemsellprice;

                getline(ss, itemName, ',');
                getline(ss, itemPrice, ',');
                getline(ss, itemCategory, ',');
                getline(ss,itemsellprice,',');

                menu_item item;
                item.name = itemName;
                item.price = stof(itemPrice);
                item.category = itemCategory;
                item.sellprice=stof(itemsellprice);
                

                items.push_back(item);
            }
            inFile.close();

            string ans;
            cout << "do you want to update item(yes/no)" << endl;
            cin >> ans;
            if (ans == "yes")
            {
                cout << "Enter the name of the item you want to update: " << endl;
                string itemName;
                cin.ignore();
                getline(cin, itemName);

                bool flag = false;
                for (menu_item &item : items)
                {
                    if (item.name == itemName)
                    {
                        flag = true;
                        bool validChoice = false;
                        while (!validChoice)
                        {
                            cout << "1. Name\n2. Price\n3. Category\nEnter your choice: ";
                            int choice;
                            cin >> choice;
                            cin.ignore();

                            if (choice == 1)
                            {
                                cout << "Enter the new name: ";
                                string newName;
                                getline(cin, newName);
                                item.name = newName;
                                cout << "Item name updated successfully!" << endl;
                                validChoice = true;
                            }
                            else if (choice == 2)
                            {
                                cout << "Enter the new price: ";
                                float newPrice;
                                cin >> newPrice;
                                item.sellprice = newPrice;
                                cout << "Item price updated successfully!" << endl;
                                validChoice = true;
                            }
                            else if (choice == 3)
                            {
                                cout << "Enter the new category: ";
                                string newCategory;
                                getline(cin, newCategory);
                                item.category = newCategory;
                                cout << "Item category updated successfully!" << endl;
                                validChoice = true;
                            }
                            else
                            {
                                cout << "Invalid choice! Please enter a valid choice." << endl;
                            }
                        }
                        break;
                    }
                }

                if (!flag)
                {
                    cout << "Item not found!" << endl;
                }
            }

            ofstream outFile("menu.csv");
            if (!outFile)
            {
                throw runtime_error("Error opening items.txt for writing");
            }

            for (const menu_item &item : items)
            {
                outFile << item.name << "," << item.price << "," << item.category <<","<<item.sellprice<< endl;
            }
            outFile.close();
        }
        catch (const exception &e)
        {
            cerr << "Exception caught: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Unknown exception caught" << endl;
        }
    }
    void displayMenu()
    {
        try
        {
            ifstream inFile("menu.csv");
            if (!inFile)
            {
                throw runtime_error("Error opening file for reading");
            }

            vector<menu_item> items;
            string line;
            while (getline(inFile, line))
            {
                istringstream ss(line);
                string itemName, itemPrice, itemCategory,itemsellprice;

                getline(ss, itemName, ',');
                getline(ss, itemPrice, ',');
                getline(ss, itemCategory, ',');
                getline(ss,itemsellprice,',');

                menu_item item;
                item.name = itemName;
                item.price = stof(itemPrice);
                item.category = itemCategory;
                item.sellprice=stof(itemsellprice);

                items.push_back(item);
            }
            inFile.close();

            
         cout << left << setw(20) << "Category" << setw(30) << "Item Name" << setw(15) << "Price" << endl;
            cout << string(65, '-') << endl; // Print a line for separation

            for (const string &category : categories) {
                bool categoryPrinted = false;
                for (const menu_item &item : items) {
                    if (item.category == category) {
                        if (!categoryPrinted) {
                            cout << setw(20) << category;
                            categoryPrinted = true;
                        } else {
                            cout << setw(20) << "";
                        }
                        cout << setw(30) << item.name << setw(15) << fixed << setprecision(2) << item.sellprice << endl;
                    }
                }
            }
        } 
        catch (const exception &e)
        {
            cerr << "Exception caught: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Unknown exception caught" << endl;
        }
    }
};



