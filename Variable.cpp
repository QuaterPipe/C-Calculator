#include "Polynomial.hpp"
#include <iostream>

Variable::Variable() noexcept
{
}

Variable::Variable(const std::string& string) noexcept
{
	size_t i = 0;
	std::stringstream ss;
	for (i = 0; i < string.length(); i++)
	{
		char c = string[i];
		if ((48 <= c && c <= 57) || (c == '.') || (c == '+') || (c == '-'))
			ss << c;
		else
		{
			try
			{
				coefficient = stod(std::string(ss.str()));
			}
			catch(std::invalid_argument& e)
			{
				return;
			}
			break;
		}
		if (c == ' ')
			return;
	}
	coefficient = stod(std::string(ss.str()));
	ss.str("");
	for (i = i; i < string.length(); i++)
	{
		char c = string[i];
		if (c == ' ')
			return;
		if (c == '*')
			continue;
		if (c == '^')
		{
			i++;
			break;
		}
		if ((65 <= c && c <= 90) || (91 <= c && c <= 122))
		{
			name = c;
		}
		else
			return;
	}
	for (i = i; i < string.length(); i++)
	{
		char c = string[i];
		if (c == ' ')
			return;
		if (48 <= c && c <= 57)
			ss << c;
		else
		{
			try
			{
				exponent = stod(ss.str());
			}
			catch (std::invalid_argument& e)
			{
				return;
			}
			break;
		}
	}
	try
	{
		exponent = stod(ss.str());
	}
	catch (std::invalid_argument& e)
	{
		return;
	}
}

Variable::Variable(const f64& coefficient, const f64& exponent, const char& name) noexcept
: coefficient(coefficient), exponent(exponent), name(name)
{
}

Variable::Variable(const Variable& variable) noexcept
: coefficient(variable.coefficient), exponent(variable.exponent), name(variable.name)
{
}

Variable Variable::operator*(const f64& other) const noexcept
{
	Variable var(*this);
	var.coefficient *= other;
	return var;
}

Term Variable::operator*(const Variable& other) const noexcept
{
	Term t;
	t.AddVariable(*this);
	t.AddVariable(other);
	t.Simplify();
	return t;
}

Variable Variable::operator/(const f64& other) const noexcept
{
	Variable var(*this);
	var.coefficient /= other;
	return var;
}

Term Variable::operator/(const Variable& other) const noexcept
{
	Term t;
	t.AddVariable(*this);
	t.AddVariable(other.Reciprocal());
	t.Simplify();
	return t;
}

Variable Variable::operator^(const f64& other) const noexcept
{
	Variable var(*this);
	var.coefficient = pow(var.coefficient, other);
	var.exponent += other;
	return var;
}

void Variable::operator*=(const f64& other) noexcept
{
	*this = *this * other;
}

void Variable::operator/=(const f64& other) noexcept
{
	*this = *this / other;
}

void Variable::operator^=(const f64& other) noexcept
{
	*this = *this ^ other;
}

bool Variable::operator==(const Variable& other) const noexcept
{
	return coefficient == other.coefficient && name == other.name &&
		exponent == other.exponent;
}

bool Variable::operator!=(const Variable& other) const noexcept
{
	return coefficient != other.coefficient || name != other.name ||
		exponent != other.exponent;
}

Variable Variable::GCF(const Term& other) const noexcept
{
	Variable v(1, 1, name);
	v.coefficient = gcf(coefficient, other.Coefficient());
	for (Variable var: other.Simplified().variables)
	{
		if (var.name == v.name)
			v.exponent = v.exponent < var.exponent ? v.exponent : var.exponent;
	}
	return v;
}

Variable Variable::GCF(const f64& other) const noexcept
{
	Variable v(1, 1);
	v.coefficient = gcf(coefficient, other);
	return v;
}

Variable Variable::GCF(const Variable& other) const noexcept
{
	Variable v(1, 1);
	v.coefficient = gcf(coefficient, other.coefficient);
	if (name == other.name)
	{
		v.name = name;
		v.exponent = exponent < other.exponent ? exponent : other.exponent;
	}
	return v;
}

Variable Variable::Reciprocal() const noexcept
{
	Variable v(*this);
	v.Reciprocate();
	return v;
}

void Variable::Reciprocate() noexcept
{
	exponent = -exponent;
}

f64 Variable::SubstituteValue(const f64& value) const noexcept
{
	return pow(coefficient * value, exponent);
}

std::ostream& operator<<(std::ostream& os, const Variable& v) noexcept
{
	return os << v.coefficient << v.name << '^' << v.exponent;
}