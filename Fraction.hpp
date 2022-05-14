#pragma once
#include <cmath>
#include <string>
#include <iostream>
using f64 = double;
using i64 = long long;

struct Fraction
{
	i64 numerator = 0;
	i64 denominator = 1;
	Fraction() noexcept;
	Fraction(const Fraction& f) noexcept;
	Fraction(const f64& num) noexcept;
	Fraction(const i64& numerator, const i64& denominator) noexcept;
	Fraction& operator=(const f64& value) noexcept;
	Fraction& operator=(const Fraction& value) noexcept;
	explicit operator f64() const noexcept;
	Fraction operator*(const Fraction& other) const noexcept;
	Fraction operator/(const Fraction& other) const noexcept;
	Fraction operator-(const Fraction& other) const noexcept;
	Fraction operator+(const Fraction& other) const noexcept;
	Fraction operator^(const Fraction& other) const noexcept;
	Fraction operator*(const f64& other) const noexcept;
	Fraction operator/(const f64& other) const noexcept;
	Fraction operator-(const f64& other) const noexcept;
	Fraction operator+(const f64& other) const noexcept;
	Fraction operator^(const f64& other) const noexcept;
	void operator*=(const Fraction& other) noexcept;
	void operator/=(const Fraction& other) noexcept;
	void operator+=(const Fraction& other) noexcept;
	void operator-=(const Fraction& other) noexcept;
	void operator^=(const Fraction& other) noexcept;
	void operator*=(const f64& other) noexcept;
	void operator/=(const f64& other) noexcept;
	void operator+=(const f64& other) noexcept;
	void operator-=(const f64& other) noexcept;
	void operator^=(const f64& other) noexcept;
	static f64 GCD(const i64& a, const i64& b) noexcept;
	Fraction Reciprocal() const noexcept;
	void Reciprocate() noexcept;
	Fraction Simplified() const noexcept;
	void Simplify() noexcept;
};
std::ostream& operator<<(std::ostream& os, const Fraction& f) noexcept;