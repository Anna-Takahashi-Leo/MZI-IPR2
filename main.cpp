#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "RSA.h"

std::string hex(const std::string& str)
{
    std::stringstream ss;
    ss << std::hex << std::setfill('0');

    for (size_t i = 0; str.length() > i; ++i)
    {
        ss << std::setw(2) << static_cast<uint32_t>(static_cast<uint8_t>(str[i]));
    }

    return ss.str();
}

int main()
{
    RSA::Key key = RSA::generate_key();

    std::cout << "Key: " << std::endl;
    std::cout << "Encrypt = " << key.encryption << std::endl;
    std::cout << "Decrypt = " << key.decryption << std::endl;
    std::cout << "Modulus = " << key.modulus << std::endl;
    std::cout << std::endl;

    std::string message;
    std::string cipher;

    {
        std::ifstream input("input.txt");
        std::stringstream buffer;
        buffer << input.rdbuf();
        message = buffer.str();
    }

    std::cout << "Input: " << std::endl;
    std::cout << message << std::endl;
    std::cout << std::endl;

    {
        cipher = RSA::encrypt(key, message);
        std::ofstream output("output-enc.txt", std::ios_base::binary);
        output << cipher;

        std::cout << "Encrypred (hex):" << std::endl;
        std::cout << hex(cipher) << std::endl;
        std::cout << std::endl;
    }

    {
        message = RSA::decrypt(key, cipher);
        std::ofstream output("output-dec.txt", std::ios_base::binary);
        output << message;

        std::cout << "Decrypted:" << std::endl;
        std::cout << message << std::endl;
        std::cout << std::endl;
    }

    std::cin.get();
}
