#pragma once
#include <algorithm>
#include <cmath>
#include <iostream>
#include <stdexcept>
#include <string>
#include <sstream>
#include <vector>
using f64 = double;
using i64 = long long;
struct Term;
struct Variable;

f64 gcf(const i64& a, const i64& b) noexcept;

/// \brief A struct representing a mathematical variable
/// 	It can be used like a variable and stores it's own
/// coefficient, exponent and name. It can have an name from A-Z and a-z
/// and when its name is '\0' it is a number literal ex. 11^1 instead of 11x^1.
///
struct Variable
{
	double coefficient = 1;
	double exponent = 1;
	char name = 0;
	Variable() noexcept;
	Variable(const std::string& string) noexcept;
	Variable(const Variable& variable) noexcept;
	Variable(const f64& coefficient, const f64& exponent, const char& name='\0') noexcept;
	Variable operator*(const f64& other) const noexcept;
	Term operator*(const Variable& other) const noexcept;
	Variable operator/(const f64& other) const noexcept;
	Term operator/(const Variable& other) const noexcept;
	Variable operator^(const f64& other) const noexcept;
	void operator*=(const f64& other) noexcept;
	void operator/=(const f64& other) noexcept;
	void operator^=(const f64& other) noexcept;
	bool operator==(const Variable& other) const noexcept;
	bool operator!=(const Variable& other) const noexcept;
	Variable GCF(const Term& other) const noexcept;
	Variable GCF(const Variable& other) const noexcept;
	Variable GCF(const f64& other) const noexcept;
	Variable Reciprocal() const noexcept;
	void Reciprocate() noexcept;
	f64 SubstituteValue(const f64& value) const noexcept;
};
std::ostream& operator<<(std::ostream& os, const Variable& v) noexcept;

/// \brief A struct representing a mathematical term
/// 	It stores an array of variables and they all share a coefficient.
/// Terms can be multiplied divided and raised to an exponent.
struct Term
{
	std::vector<Variable> variables;

	Term();
	Term(const std::string& string);
	Term(const std::vector<Variable>& variables);
	Term(const Term& term);

	const Variable& operator[](char name) const;

	Term operator*(const Term& other) const noexcept;
	Term operator*(const f64& other) const noexcept;
	Term operator*(const Variable& other) const noexcept;

	Term operator/(const Term& other) const noexcept;
	Term operator/(const f64& other) const noexcept;
	Term operator/(const Variable& other) const noexcept;

	Term operator^(const f64& other) const noexcept;

	void AddVariable(const Variable& v) noexcept;
	f64 Coefficient() const noexcept;
	Term GCF(const Term& other) const noexcept;
	Variable GCF(const Variable& other) const noexcept;
	void RemoveVariable(const Variable& v) noexcept;
	Term Simplified() const noexcept;
	void Simplify() noexcept;
};
std::ostream& operator<<(std::ostream& os, const Term& t) noexcept;

/// /brief A struct representing a mathematical polynomial
/// 	It is represented as an array of terms.
struct Polynomial
{
	public:
		std::vector<Term> terms;
		Polynomial() noexcept;
		Polynomial(const std::vector<Term>& terms) noexcept;
		Polynomial(const Polynomial& p) noexcept;
		f64 Degree() const noexcept;
		Term GCF() const noexcept;
};