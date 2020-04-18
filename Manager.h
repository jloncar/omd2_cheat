#pragma once
#include <iostream>
#include <Windows.h>
#include <tlhelp32.h>
#include <psapi.h>
#include <string>
#include <vector>

class Manager
{

private:
	std::wstring m_processName;
	DWORD m_processId;
	HANDLE m_handle;
	DWORD m_moduleAddress;

	DWORD FindProcessId();
	HMODULE GetModule();

public:
	Manager(std::wstring processName);
	~Manager();

	int ReadInteger(DWORD address, bool skipBase = false);
	bool WriteInteger(DWORD address, int value, bool skipBase = false);

	// https://stackoverflow.com/questions/45262003/pointer-from-cheat-engine-to-c
	DWORD FindDMAAddy(DWORD ptr, std::vector<unsigned int> offsets);
};

