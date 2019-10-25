// Milestone 3
// Author: Mitchell Desjardins
// Email: mtdesjardins@myseneca.ca
// Student Number: 059863126 
// Section Number: SJJ

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstring>
#include <string>
#include "Product.h"
#include "ErrorState.h"
using namespace std;

namespace ama {
	//protected functions
	void Product::message(const char* pText) {
		pObject.message(pText);
	}

	bool Product::isClear() const {
		return !pObject;
	}

	void Product::setName(const char* argName) {
		if (argName != nullptr) {
			delete[] pName;
			pName = new char[max_length_name + 1];
			strncpy(pName, argName, max_length_name);
		}
		else {
			pName = nullptr;
		}
	}

	void Product::shrinkName(char*  name) const {
		int length;

		for (length = 0; pName[length] != '\0'; length++);

		if (length < 17) {
			strncpy(name, pName, 17);
		}
		else {
			strncpy(name, pName, 13);
			name[13] = '.';
			name[14] = '.';
			name[15] = '.';
			name[16] = '\0';
		}
	}

	double Product::taxable() const {
		if (pTax == true) {
			double temp = pPrice * (1 + tax_rate);
			return temp;
		}
		else {
			return pPrice;
		}
	}
	//constructors
	//takes type and sets that to pType and the rest are set to the empty state
	Product::Product(char type) : pType(type) {
		pSku[0] = '\0';
		pUnit[0] = '\0';
		pName = nullptr;
		pOnHand = 0;
		pNeeded = 0;
		pPrice = 0.0;
		pTax = false;
	}

	Product::Product(const char* sku, const char* name, const char* unit, double price, int quantNeeded, int quantHave, bool taxable) : pType('N') {
		if (name == nullptr) {
			*this = Product();
		}
		else {
			strncpy(pSku, sku, max_length_sku);
			pName = new char[max_length_name + 1];
			strncpy(pName, name, max_length_name);
			strncpy(pUnit, unit, max_length_unit);
			pPrice = price;
			pNeeded = quantNeeded;
			pOnHand = quantHave;
			pTax = taxable;
		}
	}

	Product::Product(const Product& copy) :Product('N'){
		pName = nullptr;
		*this = copy;
	}

	Product::~Product() {
		delete[] pName;
		pName = nullptr;
	}

	Product &Product::operator=(const Product &copy) {
		if (this != &copy) {
			strncpy(pSku, copy.pSku, max_length_sku);
			strncpy(pUnit, copy.pUnit, max_length_unit);
			pPrice = copy.pPrice;
			pOnHand = copy.pOnHand;
			pNeeded = copy.pNeeded;
			pTax = copy.pTax;
			message(copy.pObject.message());
			if (copy.pName != nullptr) {
				delete[] pName;
				pName = new char[max_length_name + 1];
				strncpy(pName, copy.pName, max_length_name);
			}
			else {
				pName = nullptr;
			}
		}
		return *this;
	}

	int Product::operator+=(int cnt) {
		return cnt > 0 ? pOnHand += cnt : pOnHand;
	}

	bool Product::operator==(const char* sku) const {
		return strcmp(pSku, sku) == 0;
	}

	bool Product::operator>(const char* sku) const {
		return strcmp(pSku, sku) > 0;
	}

	bool Product::operator>(const Product& temp) const {
		return strcmp(pName, temp.pName) > 0;
	}

	int Product::qtyAvailable() const {
		return pOnHand;
	}

	int Product::qtyNeeded() const {
		return pNeeded;
	}

	double Product::total_cost() const {
		return pTax ? pPrice * pOnHand * (1 + tax_rate) : pPrice * pOnHand;
	}

	bool Product::isEmpty() const {
		if ((pSku[0] == '\0') && (pUnit[0] == '\0') && (pName == nullptr) && (pOnHand == 0) && (pNeeded == 0) && (pPrice == 0.0) && (pTax == false)) {
			return true;
		}
		else {
			return false; 
		}
	}

	std::istream& Product::read(std::istream& in, bool interractive) {
		
		string t_sku, t_name, t_unit, t_taxable, t_price, t_QOH, t_QNeeded;
		char delim = ',';
		if (!interractive) {
			getline(in, t_sku, delim);
			getline(in, t_name, delim);
			getline(in, t_unit, delim);
			getline(in, t_price, delim);
			getline(in, t_taxable, delim);
			getline(in, t_QOH, delim);
			getline(in, t_QNeeded, delim);
		}
		else {
			int i_QOH = 0, i_QNeeded;
			double d_price = 0.00;
			cout << setw(max_length_label) << right << "Sku: "; cin >> t_sku;
			cout << setw(max_length_label) << right << "Name (no spaces): "; cin >> t_name;
			cout << setw(max_length_label) << right << "Unit: ";  cin >> t_unit;
			cout << setw(max_length_label) << right << "Taxed? (y/n): "; cin >> t_taxable;
			if (in.fail() || (t_taxable[0] != 'y' && t_taxable[0] != 'n'))
			{
				message("Only (Y)es or (N)o are acceptable!");
				in.setstate(ios::failbit);
			}

			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Price: "; cin >> d_price;
				if (!cin) {
					message(("Invalid Price Entry!"));
					in.setstate(ios::failbit);
				}
				else t_price = to_string(d_price);
			}
			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Quantity on hand: "; cin >> i_QOH;
				if (!cin) {
					message("Invalid Quantity Available Entry!");
					in.setstate(ios::failbit);
				}
				else t_QOH = to_string(i_QOH);
			}
			if (!in.fail()) {
				cout << setw(max_length_label) << right << "Quantity needed: ";  cin >> i_QNeeded;
				if (!cin) {
					message("Invalid Quantity Needed Entry!");
					in.setstate(ios::failbit);
				}
				else t_QNeeded = to_string(i_QNeeded);
			}
		}
		if (!in.fail()) {

			bool b_taxable = false;

			strncpy(pSku, t_sku.c_str(), max_length_sku);
			pSku[max_length_sku] = '\0';

			setName(t_name.c_str());

			strncpy(pUnit, t_unit.c_str(), max_length_unit);
			pUnit[max_length_unit] = '\0';

			b_taxable = (tolower(t_taxable.c_str()[0]) == 'y' || t_taxable.c_str()[0] == '1');

			pTax = b_taxable;
			pPrice = stod(t_price);
			pOnHand = atoi(t_QOH.c_str());
			pNeeded = atoi(t_QNeeded.c_str());

		}
		
		return in;
		
	}

	std::ostream& Product::write(std::ostream& out, int writeMode) const {
		if (!isClear()) {
			out << pObject.message();
		}
		else if (!isEmpty()) {

			const int print_length_sku = max_length_sku;
			const int print_length_name = 16;
			const int print_length_unit = 10;
			const int print_length_price = 7;
			const int print_length_tax = 3;
			const int print_length_QOH = 6;
			const int print_length_QNeeded = 6;

			char s_taxable[4] = { '\0' };

			if (pTax) {
				strncpy(s_taxable, "yes", 3);
				s_taxable[3] = '\0';
			}
			else {
				strncpy(s_taxable, "no", 3);
				s_taxable[2] = '\0';
			}
			switch (writeMode) {
			case write_condensed:
				out << pType << "," << pSku << "," << pName << "," << pUnit << ",";
				out.precision(2);
				out << fixed << pPrice << ",";
				out << pTax << "," << pOnHand << "," << pNeeded;
				break;
			case write_table:

				char name[17];
				shrinkName(name);
				out << " " << std::right << setw(print_length_sku) << pSku << " | " 
					<< std::left << setw(print_length_name) << name << " | " 
					<< std::left << setw(print_length_unit) << pUnit << " | "
					<< std::right << setw(print_length_price) << pPrice << " | "
					<< std::right << setw(print_length_tax) << s_taxable << " | "
					<< std::right << setw(print_length_QOH) << pOnHand << " | "
					<< std::right << setw(print_length_QNeeded) << pNeeded << " |";
				break;
			case write_human:
				out << setw(max_length_label) << right << "Sku: " << pSku << endl;
				out << setw(max_length_label) << right << "Name: " << pName << endl;
				out.precision(2);
				out << setw(max_length_label) << right << "Price: " << fixed << pPrice << endl;
				out << setw(max_length_label) << right << "Price after Tax: " << fixed << taxable() << endl;
				out << setw(max_length_label) << right << "Quantity Available: " << pOnHand << " " << pUnit << endl;
				out << setw(max_length_label) << right << "Quantity Needed: " << pNeeded << " " << pUnit << endl;

				break;
			}
		}
		return out;
	}
	//End Of Public Member Functions
}

