#include "Polynomial.hpp"

Term::Term()
{
}

Term::Term(const std::string& string)
{
	std::vector<std::string> strs;
	std::stringstream ss;
	for (char c: string)
	{
		if (c != ' ')
			ss << c;
		else
		{
			strs.push_back(ss.str());
			ss.str("");
		}
	}
	if (ss.str() != "")
	{
		strs.push_back(ss.str());
		ss.str("");	
	}
	for (std::string s: strs)
		AddVariable(Variable(s));
}

Term::Term(const Term& term)
: variables(term.variables)
{
}

Term::Term(const std::vector<Variable>& variables)
: variables(variables)
{
}

const Variable& Term::operator[](char name) const
{
	for (const Variable& v: variables)
	{
		if (v.name == name)
			return v;
	}
	throw std::runtime_error("Invalid name");
}

f64 Term::Coefficient() const noexcept
{
	f64 c(1);
	for (Variable var: variables)
		c *= var.coefficient;
	return c;
}


Term Term::operator*(const Term& other) const noexcept
{
	Term result(variables);
	result.variables.insert(result.variables.end(), other.variables.begin(), other.variables.end());
	return result.Simplified();
}

Term Term::operator*(const f64& other) const noexcept
{
	Term result(*this);
	for (Variable& var: result.variables)
		var *= other;
	return result.Simplified();
}

Term Term::operator*(const Variable& other) const noexcept
{
	Term result(*this);
	result.AddVariable(other);
	return result.Simplified();
}

Term Term::operator/(const Term& other) const noexcept
{
	Term result(*this);
	for (Variable var: other.variables)
		result.AddVariable(var.Reciprocal());
	return result.Simplified();
}

Term Term::operator/(const Variable& other) const noexcept
{
	Term result(*this);
	result.AddVariable(other.Reciprocal());
	return result.Simplified();
}

Term Term::operator/(const f64& other) const noexcept
{
	Term result(*this);
	for (Variable& var: result.variables)
	{
		var /= other;
	}
	return result.Simplified();
}

Term Term::operator^(const f64& other) const noexcept
{
	Term result(*this);
	for (Variable& var: result.variables)
	{
		var ^= other;
	}
	return result.Simplified();
}


// fix coefficient not working
Term Term::GCF(const Term& other) const noexcept
{
	Term result;
	auto varInTerm = [&](Term t, char name) {
		for (auto v: t.variables)
		{
			if (v.name == name)
				return true;
		}
		return false;
	};
	for (const Variable& var: variables)
	{
		if (varInTerm(other, var.name))
			result.AddVariable(var.GCF(other[var.name]));
	}
	return result.Simplified();
}

Variable Term::GCF(const Variable& other) const noexcept
{
	Variable result;
	result.coefficient = gcf(other.coefficient, Coefficient());
	auto varInTerm = [&](Term t, char name) {
		for (auto v: t.variables)
		{
			if (v.name == name)
				return true;
		}
		return false;
	};
	if (varInTerm(*this, other.name))
	{
		result.name = other.name;
		result.exponent = result.exponent < other.exponent ? result.exponent : other.exponent;
	}
	return result;
}

Term Term::Simplified() const noexcept
{
	Term t(*this);
	t.Simplify();
	return t;
}

void Term::Simplify() noexcept
{
	if (variables.size() < 2) return;
	std::vector<size_t> indexes;
	std::vector<char> chars;
	for (size_t i = 0; i < variables.size(); i++)
	{
		if (std::find(chars.begin(), chars.end(), variables[i].name) != chars.end())
			continue;
		else
			chars.push_back(variables[i].name);
		Variable& a = variables[i];
		for (size_t j = 0; j < variables.size(); j++)
		{
			if (i != j)
			{
				Variable& b = variables[j];
				if (b.name == a.name)
				{
					a.exponent += b.exponent;
					a.coefficient *= b.coefficient;
					indexes.push_back(j);
				}
			}
		}
	}
	for (auto ptr = indexes.rbegin(); ptr < indexes.rend(); ptr++)
	{
		variables.erase(variables.begin() + *ptr);
	}
}

void Term::AddVariable(const Variable& v) noexcept
{
	variables.push_back(v);
	Simplify();
}

void Term::RemoveVariable(const Variable& v) noexcept
{
	for (size_t i = 0; i < variables.size(); i++)
	{
		if (variables[i] == v)
		{
			variables.erase(variables.begin() + i);
			break;
		}
	}
	Simplify();
}

std::ostream& operator<<(std::ostream& os, const Term& t) noexcept
{
	auto varInTerm = [&](Term term, char name) {
		for (auto v: term.variables)
		{
			if (v.name == name)
				return true;
		}
		return false;
	};
	os << t.Coefficient();
	for (char c = 'A'; c < '['; c++)
	{
		if (varInTerm(t, c))
			os << t[c].name << '^' << '(' << t[c].exponent << ')';
	}
	for (char c = 'a'; c < '{'; c++)
	{
		if (varInTerm(t, c))
			os << t[c].name << '^' << '(' << t[c].exponent << ')';
	}
	return os;
}