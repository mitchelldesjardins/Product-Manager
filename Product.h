// Milestone 3
// Author: Mitchell Desjardins
// Email: mtdesjardins@myseneca.ca
// Student Number: 059863126
// Section Number: SJJ

#ifndef AMA_PRODUCT_H
#define AMA_PRODUCT_H
#include "ErrorState.h"

namespace ama {
	const int max_length_label = 30;
	const int max_length_sku = 7;
	const int max_length_name = 75;
	const int max_length_unit = 10;
	const int write_condensed = 0;
	const int write_table = 1;
	const int write_human = 2;
	const double tax_rate = 0.13;

	class Product {
		const char pType;
		char pSku[max_length_sku + 1];
		char pUnit[max_length_unit + 1];
		char* pName;
		int pOnHand;
		int pNeeded;
		double pPrice;
		bool pTax;
		ErrorState pObject;

	protected:
		void message(const char* pText);
		bool isClear() const;
		void setName(const char*);
		void shrinkName(char*) const;
		double taxable() const;
	public:
		Product(char type = 'N');
		Product(const char* , const char* , const char* , double = 0.0, int = 0, int = 0, bool = true);
		Product(const Product& copy);
		~Product();
		Product& operator=(const Product& copy);
		int operator+=(int cnt);
		bool operator==(const char* sku) const;
		bool operator>(const char* sku) const;
		bool operator>(const Product&) const;
		int qtyAvailable() const;
		int qtyNeeded() const;
		double total_cost() const;
		bool isEmpty() const; 
		std::istream& read(std::istream& in, bool interractive);
		std::ostream& write(std::ostream& out, int writeMode) const;
	};
	

}
#endif // !AMA_PRODUCT_H
