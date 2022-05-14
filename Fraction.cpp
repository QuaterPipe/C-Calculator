#include "Fraction.hpp"
#include <iostream>

Fraction::Fraction() noexcept
: numerator(0), denominator(1)
{
}

Fraction::Fraction(const f64& num) noexcept
{
	f64 integral = std::floor(num);
	const f64 frac = num - integral;
	const i64 precision = 1000000000;
	const i64 gcd = Fraction::GCD(round(frac * precision), precision);
	const i64 denom = precision / gcd;
	const i64 numer = round(frac * precision) / gcd;
	numerator = numer + floor(num) * denom;
	denominator = denom;
}

Fraction::Fraction(const Fraction& f) noexcept
: numerator(f.numerator), denominator(f.denominator)
{
}

Fraction::Fraction(const i64& numerator, const i64& denominator) noexcept
: numerator(numerator), denominator(denominator)
{
}

Fraction& Fraction::operator=(const f64& value) noexcept
{
	numerator = value;
	denominator = 1;
	return *this;
}

Fraction& Fraction::operator=(const Fraction& value) noexcept
{
	numerator = value.numerator;
	denominator = value.denominator;
	return *this;
}

Fraction::operator f64() const noexcept
{
	return (f64)numerator / (f64)denominator;
}

Fraction Fraction::operator*(const Fraction& other) const noexcept
{
	return Fraction(numerator * other.numerator, denominator * other.denominator);
}

Fraction Fraction::operator/(const Fraction& other) const noexcept
{
	return *this * other.Reciprocal();
}

Fraction Fraction::operator-(const Fraction& other) const noexcept
{
	if (denominator == other.denominator)
		return Fraction(numerator - other.numerator, denominator);
	else
	{
		Fraction a(*this);
		Fraction b(other);
		a.numerator *= b.denominator;
		b.numerator += a.denominator;
		return Fraction(a.numerator + b.numerator, a.denominator * b.denominator);
	}
}

Fraction Fraction::operator+(const Fraction& other) const noexcept
{
	if (denominator == other.denominator)
		return Fraction(numerator + other.numerator, denominator);
	else
	{
		Fraction a(*this);
		Fraction b(other);
		a.numerator *= b.denominator;
		b.numerator += a.denominator;
		return Fraction(a.numerator + b.numerator, a.denominator * b.denominator);
	}
}

Fraction Fraction::operator^(const Fraction& other) const noexcept
{
	Fraction f(*this);
	f.Simplify();
	Fraction simple = other.Simplified();
	if (simple.denominator == 1)
	{
		i64 n = f.numerator;
		i64 d = f.denominator;
		std::cout<<n<<" "<<d<<"\n";
		for (i64 i = 0; i < other.numerator - 1; i++)
		{
			std::cout<<"f: "<<f<<"\n";
			f.numerator *= n;
			f.denominator *= d;
			f.Simplify();
		}
	}
	else
	{
		Fraction a(pow(f.numerator, 1 / (double)other.denominator));
		Fraction b(pow(f.denominator, 1 / (double)other.denominator));
		std::cout<<a<<" "<<b<<"\n";
		std::cout<<(f64)a<<" "<<(f64)b<<"\n";
		f = (a / b).Simplified();
		std::cout<<"f: "<<f<<"\n";
		f = f ^ Fraction(numerator);
	}
	return f;
}

Fraction Fraction::operator*(const f64& other) const noexcept
{
	return this->operator*(Fraction(other));
}

Fraction Fraction::operator/(const f64& other) const noexcept
{
	return this->operator/(Fraction(other));
}

Fraction Fraction::operator-(const f64& other) const noexcept
{
	return this->operator-(Fraction(other));
}

Fraction Fraction::operator+(const f64& other) const noexcept
{
	return this->operator+(Fraction(other));
}

void Fraction::operator*=(const Fraction& other) noexcept
{
	*this = *this * other;
}

void Fraction::operator/=(const Fraction& other) noexcept
{
	*this = *this / other;
}

void Fraction::operator+=(const Fraction& other) noexcept
{
	*this = *this + other;
}

void Fraction::operator-=(const Fraction& other) noexcept
{
	*this = *this - other;
}

void Fraction::operator*=(const f64& other) noexcept
{
	*this = *this * other;
}

void Fraction::operator/=(const f64& other) noexcept
{
	*this = *this / other;
}

void Fraction::operator+=(const f64& other) noexcept
{
	*this = *this + other;
}

void Fraction::operator-=(const f64& other) noexcept
{
	*this = *this - other;
}

std::ostream& operator<<(std::ostream& os, const Fraction& f) noexcept
{
	return os << f.numerator << "/" << f.denominator;
}


f64 Fraction::GCD(const i64& a, const i64& b) noexcept
{
	if (!a)
        return b;
    else if (!b)
        return a;
    if (a < b)
        return GCD(a, b % a);
    else
        return GCD(b, a % b);
}

Fraction Fraction::Reciprocal() const noexcept
{
	return Fraction(denominator, numerator);
}

void Fraction::Reciprocate() noexcept
{
	f64 tmp = denominator;
	denominator = numerator;
	numerator = tmp;
}

Fraction Fraction::Simplified() const noexcept
{
	Fraction f(*this);
	f.Simplify();
	return f;
}

void Fraction::Simplify() noexcept
{
	if (!(numerator % denominator))
	{
		f64 denom = GCD(numerator, denominator);
		numerator /= denom;
		denominator /= denom;
	}
}