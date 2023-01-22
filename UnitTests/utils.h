#pragma once
#include <iomanip>
#include <sstream>

template<typename T>
bool is_prime(T value)
{
	if (value == 1)
	{
		return false;
	}

	if ((value & 1) == 0)
	{
		return value == 2;
	}

	if (value % 3 == 0)
	{
		return value == 3;
	}

	T p = 5;

	while (p * p <= value)
	{
		if (value % p == 0)
		{
			return false;
		}

		p += 2;

		if (value % p == 0)
		{
			return false;
		}

		p += 4;
	}

	return true;
}

inline std::string as_hex(const std::string& str)
{
	std::stringstream ss;
	ss << std::hex << std::setfill('0');

	for (size_t i = 0; str.length() > i; ++i)
	{
		ss << std::setw(2) << static_cast<uint32_t>(static_cast<uint8_t>(str[i]));
	}

	return ss.str();
}
