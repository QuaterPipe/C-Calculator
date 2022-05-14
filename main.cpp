#include "Polynomial.hpp"
#include <iostream>
#include <cmath>

int main()
{
	Term t("2x^5 5y^6 1y^6");
	Term t2("1x^5 2y^6 14z^7");
	Term t3("1x^54y^6 10z^7");
	std::cout<<t<<"  "<<t2<<"  "<<t3<<"\n";
	Polynomial p;
	p.terms.push_back(t);
	p.terms.push_back(t2);
	p.terms.push_back(t3);
	std::cout<<p.GCF()<<"\n";
	return 0;
}