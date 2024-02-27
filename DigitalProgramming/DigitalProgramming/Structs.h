#pragma once

#include<iostream>

struct Color
{
	unsigned char values[3];

	void	operator+=(const Color& other);
	Color	operator+(const Color& other) const;
	Color	operator-(const Color& other) const;
	Color	operator*(const double koef) const;
	Color	operator/(const double koef) const;
};

union HiColor
{
	std::uint16_t val;
	unsigned char bytes[sizeof(std::uint16_t)];
};

inline void Color::operator+=(const Color& other)
{
	for (size_t i = 0; i < 3; i++)
		this->values[i] += other.values[i];
}

inline Color Color::operator+(const Color& other) const
{
	auto color = Color();
	for (size_t i = 0; i < 3; i++)
		color.values[i] = this->values[i] + other.values[i];

	return color;
}

inline Color Color::operator-(const Color& other) const
{
	auto color = Color();
	for (size_t i = 0; i < 3; i++)
		color.values[i] = this->values[i] - other.values[i];

	return color;
}

inline Color Color::operator*(const double koef) const
{
	auto color = Color();
	for (size_t i = 0; i < 3; i++)
		color.values[i] = static_cast<unsigned char>(static_cast<double>(this->values[i]) * koef);

	return color;
}

inline Color Color::operator/(const double koef) const
{
	auto color = Color();
	for (size_t i = 0; i < 3; i++)
		color.values[i] = static_cast<unsigned char>(static_cast<double>(this->values[i]) / koef);

	return color;
}