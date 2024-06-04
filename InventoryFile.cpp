#include "validationFile.cpp"
class Inventory:public Validation
{
    string name;
    string quantity;
    string price;
    string stock;
    public:
    
   void addItems(const Inventory& item)
    {
    ofstream out("Inventory.txt", ios::app|ios::out);

    if (!out) 
    {
        cout << "Error: Unable to open file." << endl;
        return;
    }

   
    out << item.name << "," << item.quantity << "," << item.price << "," << item.stock << endl;

    out.close(); 
   }
    void restock()
    {
        const string additionalQuantity = "15"; 

        ifstream in("Inventory.txt");
        ofstream temp("temp.txt");

        if (!in || !temp) {
            cout << "Error: Unable to open file." << endl;
            return;
        }

        string st;

        while (getline(in, st)) {
            stringstream ss(st);

            getline(ss, name, ',');
            getline(ss, quantity, ',');
            getline(ss, price, ',');
            getline(ss, stock, ',');

            if (stock == "N") {
                stringstream convert(quantity);
                int currentQuantity;
                convert >> currentQuantity;
                currentQuantity += stoi(additionalQuantity); 
                stringstream newQuantity;
                newQuantity << currentQuantity;

                temp << name << "," << newQuantity.str() << "," << price << ",Y" << endl;
            } else {
               
                temp << st << endl;
            }
        }

        in.close();
        temp.close();

        remove("Inventory.txt");
        
        rename("temp.txt", "Inventory.txt");

        cout << "Restocking completed." << endl;
        


    }

    void view() {
    ifstream in("Inventory.txt");

    if (!in) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string st;
    while (getline(in, st)) {
        stringstream ss(st);
        string word;

        
        getline(ss, word, ',');
        cout << " Name: " << word;

        getline(ss, word, ',');
        cout << " Quantity(KG): " << word;

        getline(ss, word, ',');
        cout << " Price: " << word;

        getline(ss, word, ',');
        cout << " Restock?: " << word;

        cout << endl;
    }

    in.close();
}

  void show()//show items that need to be restocked the one with n
    //restock price kesay chnge krunga
   {
    ifstream in("Inventory.txt");

    if (!in) {
        cout << "Error: Unable to open file." << endl;
        return;
    }

    string st;
    string name, quantity, price, restock;

    while (getline(in, st)) {
        stringstream ss(st);
        getline(ss, name, ',');
        getline(ss, quantity, ',');
        getline(ss, price, ',');
        getline(ss, restock, ',');

        if (restock == "Y") {
            cout << "Name: " << name << ", Quantity(KG): " << quantity << ", Price: " << price << endl;
        }
    }
    in.close();
}
};



