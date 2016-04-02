//************************************************
//◇作者：CUCKOO0615
//◇日期：2016/03/04
//◇说明：MFC命令行调试工具 实现
//*************************************************

#pragma warning(disable:4996)

#define EXPORT_CKDBGCONSOLE

#define BUFFSIZE_512 512

#include "CKDbgConsole.h"
#include <windows.h>
#include <time.h>
#include <stdarg.h>
#include <stdio.h>

bool g_bInited = false;
bool g_bShowLogTime = true;
HANDLE g_hConsoleHandle = NULL;
CRITICAL_SECTION g_csWriteLock;

namespace CKDbgConsole
{
	/////////////////////////////////////////////////////////////////////////
	// Implements

	bool ShowConsole()
	{
		if (g_bInited)		        return true;
		if (0 == ::AllocConsole())	return false;

		HWND hHwnd = ::GetConsoleWindow();
		if (hHwnd)
		{
			HMENU hMenu = ::GetSystemMenu(hHwnd, FALSE);
			if (hMenu) ::RemoveMenu(hMenu, 0xF060, 0);
			g_hConsoleHandle = ::GetStdHandle(STD_OUTPUT_HANDLE);
		}

		g_bInited = (hHwnd && g_hConsoleHandle);
		if (!g_bInited) ::FreeConsole();
		return g_bInited;
	}

	void ExitConsole()
	{
		if (!g_bInited)	return;
		::FreeConsole();
		::CloseHandle(g_hConsoleHandle);
		g_hConsoleHandle = NULL;
		g_bInited = false;
	}

	void WriteLine(INFO_TYPE emInfoType, const char * pszMsg, ...)
	{
		if (!g_bInited || !pszMsg) return;
		::EnterCriticalSection(&g_csWriteLock);

		DWORD nWriteNum = 0;
		if (g_bShowLogTime)
		{
			char szBuf[30] = { 0 };
			time_t lt;
			::time(&lt);
			::strftime(szBuf, 30, "[%Y/%m/%d %H:%M:%S]", ::localtime(&lt));
			::WriteConsoleA(g_hConsoleHandle, szBuf, ::strlen(szBuf) + 1, &nWriteNum, NULL);
		}

		const char* arrLogTypes[] = { "<INFO> ", "<WARN> ", "<ERROR>" };
		::WriteConsoleA(g_hConsoleHandle, arrLogTypes[emInfoType], 8, &nWriteNum, NULL);

		char buff[BUFFSIZE_512] = { 0 };
		va_list argList;
		va_start(argList, pszMsg);
		::_vsnprintf(buff, BUFFSIZE_512, pszMsg, argList);
		va_end(argList);

		size_t nLen = ::strlen(buff);
		::WriteConsoleA(g_hConsoleHandle, buff, min(nLen, BUFFSIZE_512), &nWriteNum, NULL);
		::WriteConsoleA(g_hConsoleHandle, "\n", 1, &nWriteNum, NULL);

		::LeaveCriticalSection(&g_csWriteLock);
		return;
	}

	void Write(const char * pszMsg, ...)
	{
		if (!g_bInited || !pszMsg) return;
		::EnterCriticalSection(&g_csWriteLock);

		char buff[BUFFSIZE_512] = { 0 };
		va_list argList;
		va_start(argList, pszMsg);
		::_vsnprintf(buff, BUFFSIZE_512, pszMsg, argList);
		va_end(argList);

		size_t nLen = ::strlen(buff);
		DWORD nWriteNum = 0;
		::WriteConsoleA(g_hConsoleHandle, buff, min(nLen, BUFFSIZE_512), &nWriteNum, NULL);

		::LeaveCriticalSection(&g_csWriteLock);
		return;
	}

	void ShowLogTime(bool bShow)
	{
		g_bShowLogTime = bShow;
	}

	void SetTitle(const char* szTitle)
	{
		if (g_bInited && szTitle) ::SetConsoleTitleA(szTitle);
	}
};

//////////////////////////////////////////////////////////////////////////
//AutoUtil Class
class AutoMgr
{
public:
	AutoMgr()
	{
		::InitializeCriticalSectionAndSpinCount(&g_csWriteLock, 8000);
	}
	~AutoMgr()
	{
		::DeleteCriticalSection(&g_csWriteLock);
		CKDbgConsole::ExitConsole();
	}

};
static AutoMgr am;
