#include "Cheats.h"

// SKULLS
int Cheats::SkullsGet()
{
	return m_manager.ReadInteger(ADDRESS_SKULL.base);
}

bool Cheats::SkullsIncrease(int value)
{
	int current = SkullsGet();
	return m_manager.WriteInteger(ADDRESS_SKULL.base, current + value);
}

// MONEY
int Cheats::MoneyGet()
{
	DWORD_PTR moneyPtrAddress = m_manager.FindDMAAddy(ADDRESS_MONEY.base, ADDRESS_MONEY.offset);

	return m_manager.ReadInteger(moneyPtrAddress, true);
}

bool Cheats::MoneyIncrease(int value)
{
	DWORD_PTR moneyPtrAddress = m_manager.FindDMAAddy(ADDRESS_MONEY.base, ADDRESS_MONEY.offset);

	return m_manager.WriteInteger(moneyPtrAddress, MoneyGet() + value, true);
}