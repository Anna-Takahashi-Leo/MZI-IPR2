#pragma once

#include <string>

namespace RSA
{
	using Number = uint16_t;

	struct Key
	{
		Number decryption;
		Number encryption;
		Number modulus;
	};

	Key generate_key();

	std::string encrypt(const Key key, const std::string message);
	std::string decrypt(const Key key, const std::string cipher);
};
