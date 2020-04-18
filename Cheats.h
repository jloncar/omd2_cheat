#pragma once
#include "Manager.h"
#include "Offsets.h"

// Glue between Manager & Offsets + Business logic
class Cheats
{
private:
	Manager& m_manager;

public:
	Cheats(Manager& manager) : m_manager(manager) {};

	int SkullsGet();
	bool SkullsIncrease(int value);

	int MoneyGet();
	bool MoneyIncrease(int value);
};