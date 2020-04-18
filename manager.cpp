#include "Manager.h"

Manager::Manager(std::wstring processName)
{
	m_processName = processName;
	m_processId = FindProcessId();
	m_handle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, m_processId);
	m_moduleAddress = (DWORD)GetModule();
}

Manager::~Manager()
{
	CloseHandle(m_handle);
}

DWORD Manager::FindProcessId()
{
	PROCESSENTRY32 processInfo;
	processInfo.dwSize = sizeof(processInfo);

	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
	if (processesSnapshot == INVALID_HANDLE_VALUE) {
		return 0;
	}

	Process32First(processesSnapshot, &processInfo);
	if (!m_processName.compare(processInfo.szExeFile))
	{
		CloseHandle(processesSnapshot);
		return processInfo.th32ProcessID;
	}

	while (Process32Next(processesSnapshot, &processInfo))
	{
		if (!m_processName.compare(processInfo.szExeFile))
		{
			CloseHandle(processesSnapshot);
			return processInfo.th32ProcessID;
		}
	}

	CloseHandle(processesSnapshot);
	return 0;
}

HMODULE Manager::GetModule()
{
	HMODULE hMods[1024];
	DWORD cbNeeded;
	unsigned int i;

	if (EnumProcessModules(m_handle, hMods, sizeof(hMods), &cbNeeded))
	{
		for (i = 0; i < (cbNeeded / sizeof(HMODULE)); i++)
		{
			TCHAR szModName[MAX_PATH];
			if (GetModuleFileNameEx(m_handle, hMods[i], szModName, sizeof(szModName) / sizeof(TCHAR)))
			{
				std::wstring wstrModName = szModName;
				//you will need to change this to the name of the exe of the foreign process
				std::wstring wstrModContain = L"OrcsMustDie2.exe";
				if (wstrModName.find(wstrModContain) != std::string::npos)
				{
					return hMods[i];
				}
			}
		}
	}
	return nullptr;
}

int Manager::ReadInteger(DWORD address, bool skipBase)
{
	int buffer;
	DWORD realAddress = (skipBase) ? address : (m_moduleAddress + address);
	ReadProcessMemory(m_handle, (LPVOID)realAddress, &buffer, sizeof(buffer), NULL);
	return buffer;
}

bool Manager::WriteInteger(DWORD address, int value, bool skipBase)
{
	m_moduleAddress = (DWORD)GetModule();
	DWORD realAddress = (skipBase) ? address : (m_moduleAddress + address);
	return WriteProcessMemory(m_handle, (LPVOID)realAddress, &value, sizeof(value), NULL);
}

DWORD Manager::FindDMAAddy(DWORD ptr, std::vector<unsigned int> offsets)
{
	DWORD addr = m_moduleAddress + ptr;

	for (unsigned int i = 0; i < offsets.size(); ++i)
	{
		ReadProcessMemory(m_handle, (LPVOID)addr, &addr, sizeof(addr), 0);
		addr += offsets[i];
	}
	return addr;
}