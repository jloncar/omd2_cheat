#include <iostream>
#include "Manager.h"
#include "Cheats.h"

int main()
{
	// Instantiate memory manager
	Manager manager{ L"OrcsMustDie2.exe" };
	Cheats cheats{ manager };

	// Setup
	char option;
	int skullsIncrement = 1000;
	int moneyIncrement = 1000;

	// REPL
	std::cout << "Please select an option. " << std::endl;
	std::cout << "1) Read skulls" << std::endl;
	std::cout << "2) Increase skulls by " << skullsIncrement << std::endl;
	std::cout << "3) Increase money by " << moneyIncrement << std::endl;
	std::cout << "0) Exit" << std::endl;

	// REPL: Loop
	while (true)
	{
		std::cin >> option;

		switch (option)
		{
			// Read skulls
			case '1':
				std::cout << "Skulls count: " << cheats.SkullsGet() << std::endl;
			continue;

			// Increase skulls
			case '2':
				cheats.SkullsIncrease(skullsIncrement);
				std::cout << "Increased skulls by " << skullsIncrement << ", skulls count: " << cheats.SkullsGet() << std::endl;
				continue;

			// Increase money
			case '3':
				cheats.MoneyIncrease(moneyIncrement);
				std::cout << "Increased money by " << moneyIncrement << ", money count: " << cheats.MoneyGet() << std::endl;
				continue;

			// Exit app
			case '0':
			return 0;

			// Loop
			default:
			continue;
		}
	}
	

}
