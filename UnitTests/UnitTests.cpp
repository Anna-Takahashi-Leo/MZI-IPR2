#include "pch.h"
#include "CppUnitTest.h"
#include "../RSA.h"
#include <numeric>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTests
{
	TEST_CLASS(UnitTests)
	{
	public:
		
		TEST_METHOD(TestKeys)
		{
			RSA::Key key = RSA::generate_key();

			Assert::IsTrue(std::gcd(key.encryption, key.modulus) == 1);
		}

		TEST_METHOD(TestEncryption)
		{
			RSA::Key key;
			key.decryption = 251;
			key.encryption = 755;
			key.modulus = 2147;

			std::string message = "Original Message";
			std::string encrypred = RSA::encrypt(key, message);

			Assert::IsTrue(as_hex(encrypred) == "f20272005a05c2035a055e08170703008105f800f6042b082b081707c203f604");
		}

		TEST_METHOD(TestDecryption)
		{
			RSA::Key key = RSA::generate_key();

			std::string message = "Original Message";
			std::string encrypred = RSA::encrypt(key, message);
			std::string decrypred = RSA::decrypt(key, encrypred);

			Assert::IsTrue(message == decrypred);
		}
	};
}
