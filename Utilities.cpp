#include "ErrorState.h"
#include "Product.h"
#include "Utilities.h"

namespace ama {
	double& operator+=(double& total, const Product& prod) {
		return (total += prod.total_cost());
	}

	std::ostream& operator<<(std::ostream& out, const Product& prod) {
		prod.write(out, 2);
		return out;
	}

	std::istream& operator>>(std::istream& in, Product& prod) {
		prod.read(in, true);
		return in;
	}
}