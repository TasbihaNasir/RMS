// isko barae mehrbani beghair chere kam karyega
#include "MenuManagement.cpp"
class OrderProcessing:public MenuManagement{
    public:
    vector<pair<string, int>> OrderedItems;  
    OrderProcessing(){}
    
    void printOrder() {
        cout << "Current Order:" << endl;
        for(const auto &item : OrderedItems) {
            cout << "Item: " << item.first << ", Quantity: " << item.second << endl;
        }
    }
    
    vector<pair<string, int>> placeOrder(){
        try{ 
            displayMenu();
            cout<<"How many orders do you want to place?"<<endl;
            int n;
            cin>>n;
            string order;
            int quantity;
            for(int i=0;i<n;i++){
                while(true){
                    cout<<"Order Please:)"<<endl;
                    cin>>order;
                    cout<<"Quantity:"<<endl;
                    cin>>quantity;
                    if(validateMenu(order) && validQuantity(quantity)){
                        OrderedItems.push_back(make_pair(order, quantity));
                        cout << "Item added successfully." << endl;
                        break;
                    }
                    else{
                        cout<<"Invalid item name or quantity-Please choose from menu."<<endl<< "Quantity range is 1 to 10"<<endl;
                    }
                }
            }
            printOrder();
        }
        catch (const exception &e)
        {
            cerr << "Exception caught: " << e.what() << endl;
        }
        catch (...)
        {
            cerr << "Unknown exception caught" << endl;
        }
        return OrderedItems;
    }

   vector<pair<string, int>> modifyOrder(){
    try{
        string choice, itemName;
        int option;
        do {
            cout << "Enter your choice: "<<endl<<"1) Add"<<endl <<"2) Update"<<endl <<"3) Remove" << endl;
            cin >> option;
        } while(option < 1 || option > 3);

        
        if(option == 1){
            string newItemName;
            int quantity;
            cout << "Enter the name for the new item:" << endl;
            while(true){
                cin >> newItemName;
                if(validateMenu(newItemName)){
                    break;
                }
                else{
                    cout << "Invalid item name. Please enter again:" << endl;
                }
            }
            cout << "Enter the quantity for the new item:" << endl;
            cin >> quantity;
            while(!validQuantity(quantity)){
                cout << "Invalid quantity. Please enter again:" << endl;
                cin >> quantity;
            }
            OrderedItems.push_back(make_pair(newItemName, quantity));
            cout << "Item added successfully." << endl;
        }
        else if(option == 2){
            string newName;
            cout << "Enter the new name for the item:" << endl;
            cin >> newName;

            if(!validateMenu(newName)){
                cout << "Invalid new item name. Please enter again." << endl;
            }
            else{
                for(auto &order : OrderedItems){
                    if(order.first == itemName){
                        order.first = newName;
                        cout << "Order updated successfully." << endl;
                    }
                }
            }
        }
        else if(option == 3){
            for(auto it = OrderedItems.begin(); it != OrderedItems.end(); ++it){
                if(it->first == itemName){
                    OrderedItems.erase(it);
                    cout << "Order removed successfully." << endl;
                    break;
                }
            }
        }
        printOrder();
    }
    catch (const exception &e)
    {
        cerr << "Exception caught: " << e.what() << endl;
    }
    catch (...)
    {
        cerr << "Unknown exception caught" << endl;
    }
    return OrderedItems;
}
void cancelOrder() {
    OrderedItems.clear();
    cout << "Order has been cancelled successfully." << endl;
}
friend class BillingPayment;
};





