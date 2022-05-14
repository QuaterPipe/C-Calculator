#include "Factoring.hpp"

bool isPrime(const Polynomial& poly) noexcept
{
	Term t;
	t.AddVariable(Variable(1, 1));
	return false;// poly.GCF() == t;
}