#pragma once
#include <windows.h>

struct Address
{
	DWORD base;
	std::vector<unsigned int> offset;
};

const Address ADDRESS_SKULL = { 0x7B830C };
const Address ADDRESS_MONEY = { 0x7A445C, { 0x0, 0xC, 0x7C } };