#include "RSA.h"
#include <cstdint>
#include <ctime>
#include <numeric>

namespace
{
bool is_prime(RSA::Number value)
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

	RSA::Number p = 5;

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

RSA::Number random_prime(RSA::Number lower, RSA::Number upper)
{
	RSA::Number value;
	RSA::Number spread = upper - lower + 1;

	while (true)
	{
		value = 1 | (lower + std::rand() % spread);
		
		if (is_prime(value))
		{
			break;
		}
	}

	return value;
}

RSA::Number mod_inverse(RSA::Number a, RSA::Number m)
{
	for (RSA::Number x = 1; x < m; x++)
	{
		if (((a % m) * (x % m)) % m == 1)
		{
			return x;
		}
	}
}

RSA::Number mod_exponentiation(RSA::Number base, RSA::Number exponent, RSA::Number modulus)
{
	RSA::Number x = 1;
	RSA::Number power = fmod(base, modulus);

	while (exponent > 0)
	{
		if (exponent & 1)
		{
			x = fmod(power * x, modulus);
		}

		power = fmod(power * power, modulus);
		exponent >>= 1;
	}

	return x;
}
};

RSA::Key RSA::generate_key()
{
	std::srand(std::time(nullptr));

	RSA::Number p = random_prime(1, 255);
	RSA::Number q = random_prime(1, 255);

	while (q == p)
	{
		q = random_prime(1, 255);
	}
	
	RSA::Number n = p * q;
	RSA::Number l = std::lcm(p - 1, q - 1);
	RSA::Number e = random_prime(1, l);

	while (std::gcd(e, l) != 1)
	{
		e = random_prime(1, l);
	}

	RSA::Number d = mod_inverse(e, l);
	
	return { d, e, n };
}

std::string RSA::encrypt(const RSA::Key key, const std::string message)
{
	std::string cipher;
	cipher.reserve(message.length() * 2);

	for (std::string::const_iterator it = message.begin(); it != message.end(); it++)
	{
		RSA::Number m = *it;
		RSA::Number c = mod_exponentiation(*it, key.encryption, key.modulus);

		cipher.push_back(*reinterpret_cast<char*>(&c));
		cipher.push_back(*(reinterpret_cast<char*>(&c) + 1));
	}

	return cipher;
}

std::string RSA::decrypt(const RSA::Key key, const std::string cipher)
{
	std::string message;
	message.reserve(cipher.length() / 2);

	for (std::string::const_iterator it = cipher.begin(); it != cipher.end(); it += 2)
	{
		RSA::Number c = *reinterpret_cast<const RSA::Number*>(&(*it));
		RSA::Number m = mod_exponentiation(c, key.decryption, key.modulus);

		message.push_back(static_cast<char>(m));
	}

	return message;
}
