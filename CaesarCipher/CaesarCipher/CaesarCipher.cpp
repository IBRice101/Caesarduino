// Caesar Cipher implementation in C++
//

//Begin
#include <iostream>
#include <string>

int main()
{
	int cae = 0;
	std::string sar;

	std::cout << "Welcome to my implementation of Caesar's Cipher" << std::endl;
	std::cout << "How many places would you like to shift your message by?" << std::endl;
	std::cin >> cae;
	std::cout << "What would you like your message to be? (maximum of 21 characters)" << std::endl;
	std::cin >> sar;
	std::cout << "Okay! Shifting \"" << sar << "\" by " << cae << " places" << std::endl;

//   For i = 0 to msg[i] != '\0'
	for (int i = 0; sar[i] != '\0'; i++)
	{
		char ch;
		ch = sar[i];
		//encrypt for lowercase letter
		if (ch >= 'a' && ch <= 'z')
		{
			ch += cae;
			if (ch > 'z')
			{
				ch = ch - 'z' + 'a' - 1;
			}
			sar[i] = ch;
		}
		else if (ch >= 'A' && ch <= 'Z')
		{
			ch += cae;
			if (ch > 'Z')
			{
				ch = ch - 'Z' + 'A' - 1;
			}
			sar[i] = ch;
		}
	}
	std::cout << "The message is now as follows: " << sar << std::endl;
}
