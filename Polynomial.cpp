#include "Polynomial.hpp"

f64 gcf(const i64& a, const i64& b) noexcept
{
	if (!a)
        return b;
    else if (!b)
        return a;
	return a < b ? gcf(a, b % a) : gcf(b, a % b);
}

Polynomial::Polynomial() noexcept
{
}

Polynomial::Polynomial(const std::vector<Term>& terms) noexcept
: terms(terms)
{
}

Polynomial::Polynomial(const Polynomial& p) noexcept
: terms(p.terms)
{
}

f64 Polynomial::Degree() const noexcept
{
	f64 degree = 1;
	for (Term t: terms)
	{
		for (Variable v: t.variables)
		{
			if (v.exponent > degree)
				degree = v.exponent;
		}
	}
	return degree;
}

Term Polynomial::GCF() const noexcept
{
	f64 gcfCoef;
	if (terms.size())
	{
		gcfCoef = terms[0].Coefficient();
		Term t = terms[0];
		for (Term tmp: terms)
		{
			gcfCoef = gcf(gcfCoef, tmp.Coefficient());
			t = tmp.GCF(t);
		}
		if (t.variables.size())
			t.variables[0].coefficient *= gcfCoef;
		return t;
	}
	return Term();
}