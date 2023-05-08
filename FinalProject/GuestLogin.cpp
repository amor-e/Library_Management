#include "GuestLogin.h"

GuestLogin::GuestLogin() {}
GuestLogin::~GuestLogin() {}

bool GuestLogin::isGuest(bool guest) {
	if (guest == true) {
		return true;
	}
	else {
		return false;
	}
}
void GuestLogin::buy() {

	
		string name;
		cout << "Enter 0 to return\n" << endl;
		cout << "Enter Name:\t";
		cin.ignore();
		getline(cin, name);
		if (name == "0") {
			system("cls");
			return;
		}
			system("cls");
			ifstream purchase;
			purchase.open("PurchaseList.txt", ios::in | ios::out);
			if (!purchase.is_open()) {
				cout << "PurchaseList not opened successfully." << endl;
			}
			string mediaName;
			string line;
			vector<double> priceList;
			vector<string> nameList;
			string priceStr;
			double price;
			double sum = 0.0;
			while (getline(purchase, line)) {
				auto lastSpace = line.find_last_of(" ");
				mediaName = line.substr(0, lastSpace);
				priceStr = line.substr(lastSpace + 1);
				price = stod(priceStr);

				nameList.push_back(mediaName);
				priceList.push_back(price);

			}
			for (int i = 0; i < priceList.size(); i++) {
				sum += priceList.at(i);
			}
			double taxRate = 0.05;
			double tax = sum * 0.05;

			double total = sum + tax;
			Date date;
			date.printDate();


			cout << setfill(' ') << left << setw(25) << name << endl;
			cout << setfill(' ') << setw(30) << "Thank you for you Purchase!" << endl;

			cout << setfill(' ') << setw(35) << left << "Item" << "Price" << endl;
			for (int i = 0; i < nameList.size(); i++) {
				cout << setfill(' ') << fixed << setprecision(2) << setw(10) << left << nameList.at(i);
				cout << setw(24) << fixed << right << priceList.at(i) << endl;

			}
			cout << endl;

			cout << setfill('-') << setw(40) << "" << endl;
			cout << setfill(' ') << fixed << setprecision(2) << setw(10) << left << "Subtotal: ";
			cout << setw(30) << right << sum << endl;
			cout << setfill(' ') << fixed << setprecision(2) << setw(10) << left << "Taxes: ";
			cout << setw(30) << right << tax << endl;
			cout << setfill(' ') << fixed << setprecision(2) << setw(10) << left << "Total: ";
			cout << setw(30) << right << total << endl;
		
			ofstream clearBuyList("PurchaseList.txt", ios::trunc);//open file to clear it and then close
			clearBuyList.close();
	
}


