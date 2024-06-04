#include "RMS_headers.h"
#include "orderProcessing.cpp"


using namespace std;



 
class BillingPayment
{
    private:
     const string restaurantName = "ZAMATA";
    Validation validator; 

    double calculateTotalBill(const vector<string>& orderList) {
        double totalBill = 0.0;
        ifstream menuFile("menu.csv");

        if (!menuFile.is_open()) {
            cerr << "Error: Unable to open menu file!" << endl;
            return 0.0;
        }

        string line;
        while (getline(menuFile, line)) {
            stringstream ss(line);
            string itemName;
            double itemPrice;

            getline(ss, itemName, ',');
            ss >> itemPrice;

            for (const string& item : orderList) {
                if (itemName == item) {
                    totalBill += itemPrice;
                    break;
                }
            }
        }

        menuFile.close();
        return totalBill;
    }

public:
    void GenerateBill(const vector<pair<string, int>>& orderList) 
{
    double totalBill = 0.0;
    for (const auto& item : orderList) {
        string itemName = item.first;
        int quantity = item.second;

        ifstream menuFile("menu.csv");
        if (!menuFile.is_open()) {
            cerr << "Error: Unable to open menu file!" << endl;
            return;
        }

        string line;
        while (getline(menuFile, line)) {
            stringstream ss(line);
            string itemNameFromFile;
            double itemPrice;

            getline(ss, itemNameFromFile, ',');
            ss >> itemPrice;

            if (itemName == itemNameFromFile) {
                totalBill += itemPrice * quantity;
                cout << setw(20) << left << itemName << setw(10) << right << "x" << quantity << setw(10) << right << itemPrice * quantity << endl;
                break;
            }
        }

        menuFile.close();
    }

    if (totalBill == 0.0) {
        cout << "Error: Unable to calculate total bill!" << endl;
        return;
    }

    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::tm* localTime = std::localtime(&now_time);

    cout << "----------------------------------------------" << endl;
    cout << setw(30) << left << restaurantName << "Date: " << std::put_time(localTime, "%d %b %Y") << endl;
    cout << "----------------------------------------------" << endl;

    ofstream salesReport("SalesReport.txt", ios::app);
    if (!salesReport.is_open()) {
        cerr << "Error: Unable to open SalesReport file!" << endl;
        return;
    }   

    salesReport << std::put_time(localTime, "%d %b %Y") << "," << totalBill << endl;
    salesReport.close();    

    ifstream menuFile("menu.csv");
    if (!menuFile.is_open()) {
        cerr << "Error: Unable to open menu file!" << endl;
        return;
    }

    string line;
    while (getline(menuFile, line)) {
        stringstream ss(line);
        string itemName;
        double itemPrice;

        getline(ss, itemName, ',');
        ss >> itemPrice;

        for (const auto& item : orderList) {
            if (itemName == item.first) {
                cout << setw(20) << left << itemName << setw(10) << right << "x" << item.second << setw(10) << right << itemPrice * item.second << endl;
                break;
            }
        }
    }

    menuFile.close();

    cout << "----------------------------------------------" << endl;

    double tip;
    cout << "Would you like to give a tip? (Enter tip amount or 0 if not): ";
    cin >> tip;

    double gst = totalBill * 0.13;
    double serviceTax = totalBill * 0.02;
    totalBill += tip + gst + serviceTax;

    cout << setw(20) << left << "GST (13%)" << setw(10) << right << gst << endl;
    cout << setw(20) << left << "Service Tax (2%)" << setw(10) << right << serviceTax << endl;
    cout << setw(20) << left << "Tip" << setw(10) << right << tip << endl;
    cout << "----------------------------------------------" << endl;
    cout << setw(20) << left << "Total Bill" << setw(10) << right << totalBill << endl;

    cout << "----------------------------------------------" << endl;
    cout << "Thank you for dining with us. We appreciate your patronage!" << endl;
}

    
    void CalculateProfit(const vector<string>& orderList)
    {
        double totalRevenue = 0.0;
        double totalCost = 0.0;

        totalRevenue = calculateTotalBill(orderList);

        ifstream menuFile("menu.csv");
        if (!menuFile.is_open()) {
            cerr << "Error: Unable to open menu file!" << endl;
            return;
        }

        string line;
        while (getline(menuFile, line)) {
            stringstream ss(line);
            string itemName;
            double costPrice, sellingPrice;

            getline(ss, itemName, ',');
            ss >> costPrice >> sellingPrice;

            totalCost += costPrice;
        }

        menuFile.close();

        double profit = totalRevenue - totalCost;

        cout << "Total Revenue: " << totalRevenue << endl;
        cout << "Total Cost: " << totalCost << endl;
        cout << "Profit: " << profit << endl;


    }
   
void CustomerFeedback() 
{
    try {
        string comment;
        cout << "Do you have any comments? (Enter 'none' if you don't have any): ";
        getline(cin, comment);

        float rating;
        cout << "Please provide a rating (from 0 to 5): ";
        cin >> rating;

        if (rating < 0 || rating > 5) {
            throw invalid_argument("Invalid rating! Please provide a rating between 0 and 5.");
        }

        auto now = chrono::system_clock::now();
        time_t now_time = chrono::system_clock::to_time_t(now);
        tm* localTime = localtime(&now_time);

        ofstream feedbackReport("CustomerFeedback.txt", ios::app);

        if (!feedbackReport.is_open()) {
            throw runtime_error("Error: Unable to open CustomerFeedback file!");
        }

        feedbackReport << put_time(localTime, "%d %b %Y") << "," << rating << "," << comment << endl;

        feedbackReport.close();

        cout << "Thank you for your feedback!" << endl;
    } catch (const exception& e) {
        cerr << "Error: " << e.what() << endl;
    }
}

    
};








class Reporting:public Validation
{
       struct YearData {
        int year;
        double totalRevenue;
        int numEntries;
    };


      struct FeedbackData {
        int year;
        float rating;
        string comment;
    };

    vector<FeedbackData> feedbackData;

    vector<YearData> yearlyData;

    double maxRevenue = -1;
    double minRevenue = numeric_limits<double>::max();
    int yearWithMaxRevenue = 0;
    int yearWithMinRevenue = 0;



    public:

    Reporting(){}


   void GenerateSalesReport() {
        try {
            ifstream salesReport("SalesReport.txt");
            if (!salesReport.is_open()) {
                throw runtime_error("Error: Unable to open SalesReport file!");
            }

            string line;
            while (getline(salesReport, line)) {
                string dateString;
                double revenue;

                size_t pos = line.find_first_of(",");
                dateString = line.substr(0, pos);
                revenue = stod(line.substr(pos + 1));

                size_t lastSpacePos = dateString.find_last_of(" ");
                string yearStr = dateString.substr(lastSpacePos + 1);
                int year = stoi(yearStr);

                if (!validYear(year)) {
                    throw invalid_argument("Invalid year in sales report.");
                }

                bool found = false;
                for (auto& data : yearlyData) {
                    if (data.year == year) {
                        data.totalRevenue += revenue;
                        data.numEntries++;
                        found = true;
                        break;
                    }
                }

                if (!found) {
                    yearlyData.push_back({year, revenue, 1});
                }

                if (revenue > maxRevenue) {
                    maxRevenue = revenue;
                    yearWithMaxRevenue = year;
                }
                if (revenue < minRevenue) {
                    minRevenue = revenue;
                    yearWithMinRevenue = year;
                }
            }

            cout << "Sales Report (Average Revenue for Every Year):" << endl;
            for (const auto& data : yearlyData) {
                double averageRevenue = data.totalRevenue / data.numEntries;
                cout << data.year << "\tRs" << fixed << setprecision(2) << data.totalRevenue << "\tAverage: Rs" << averageRevenue << endl;
            }

            cout << "Maximum revenue was generated in - " << yearWithMaxRevenue << endl;
            cout << "Minimum revenue was generated in - " << yearWithMinRevenue << endl;

            salesReport.close();
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }

      void GenerateCustomerFeedbackReports() {
        try {
            ifstream feedbackFile("CustomerFeedback.txt");
            if (!feedbackFile.is_open()) {
                throw runtime_error("Error: Unable to open CustomerFeedback file!");
            }

            string line;
            while (getline(feedbackFile, line)) {
                int year;
                float rating;
                string comment;

                stringstream ss(line);
                ss >> year;
                ss.ignore();
                ss >> rating;
                ss.ignore();
                getline(ss, comment);

                if (!validYear(year)) {
                    throw invalid_argument("Invalid year in feedback data.");
                }

                feedbackData.push_back({year, rating, comment});
            }

            feedbackFile.close();

            vector<pair<int, float>> averageRatings;
            for (const auto& feedback : feedbackData) {
                bool yearFound = false;
                for (auto& avgRating : averageRatings) {
                    if (avgRating.first == feedback.year) {
                        avgRating.second = (avgRating.second * avgRating.first + feedback.rating) / (avgRating.first + 1);
                        yearFound = true;
                        break;
                    }
                }
                if (!yearFound) {
                    averageRatings.push_back({feedback.year, feedback.rating});
                }
            }

            cout << "Average Ratings for Each Year:" << endl;
            for (const auto& avgRating : averageRatings) {
                cout << avgRating.first << ": " << fixed << setprecision(2) << avgRating.second << endl;
            }

            int yearToSeeReviews;
            cout << "Enter the year you want to see reviews for: ";
            cin >> yearToSeeReviews;

            bool reviewsFound = false;
            for (const auto& feedback : feedbackData) {
                if (feedback.year == yearToSeeReviews) {
                    cout << "Date: " << feedback.year << ", Rating: " << feedback.rating << ", Comment: " << feedback.comment << endl;
                    reviewsFound = true;
                }
            }

            if (!reviewsFound) {
                cout << "No comments stored for this year." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error: " << e.what() << endl;
        }
    }
   

};
int main(){
    BillingPayment p;
    //p.CalculateProfit();
    p.CustomerFeedback();
    //p.GenerateBill();
    Reporting r;
    r.GenerateCustomerFeedbackReports();
    r.GenerateSalesReport();

}





// *Inventory Management Class:*
// 1. UpdateInventory(): Updates the inventory stock (e.g., add new items, adjust quantities).
// 2. TrackInventoryUsage(): Tracks the usage of ingredients/items for orders.
// 3. GenerateInventoryReport(): Generates reports on inventory usage and stock levels.

// *Billing and Payment Class:*
// 1. GenerateBill(): Generates a bill for orders.
// 2. AcceptPayment(): Accepts payment from customers (cash, card, etc.).
// 3. CalculateTotalRevenue(): Calculates total revenue for a specified time period.

// *Reporting Class:*
// 1. GenerateSalesReport(): Generates reports on sales for a specified time period.
// 2. GenerateCustomerFeedbackReport(): Generates reports on customer feedback and ratings.
// 3. GeneratePerformanceReport(): Generates reports on employee performance and productivity.
