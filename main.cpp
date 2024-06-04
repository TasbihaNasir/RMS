#include "MenuManagement.cpp"
#include "orderProcessing.cpp"
#include "employee.cpp"
#include "BillingAndReport.cpp"
//no need to include inventory it will be called from menuManagement
//whatever functions of inventory are do it usually make an obj of inventory than call functions 
//dont include one class/file twice it will cause errors 
//zains file need to be updated
 
int main()
{   MenuManagement m;
    m.additems();
    m.RemoveItems();
    m.UpdateItem();
    m.displayMenu();
    OrderProcessing o;
    o.placeOrder();
    o.modifyOrder();
    Employee e;
    e.addEmployee();
    e.removeEmployee();

    //e.removeEmployee();
    e.display_EmployeeData();
    Cashier c;
    c.add_details_of_customer();
    c.display_CustomerData();
    c.display_EmployeeData();

    return 0;
}

