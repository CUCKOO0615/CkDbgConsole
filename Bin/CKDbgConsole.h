//************************************************
//◇作者：CUCKOO0615
//◇日期：2015/01/26 16:37:16
//◇说明：MFC命令行调试工具, 仅限在基于MFC的程序中使用 (静态链接)
//************************************************
#pragma once

//#define CKDBGCONSOLE_STATICLIB
#ifdef CKDBGCONSOLE_STATICLIB
#define CK_API 
#else
#ifdef EXPORT_CKDBGCONSOLE
#define CK_API extern "C" __declspec(dllexport)
#else 
#define CK_API extern "C" __declspec(dllimport)
#endif
#endif // CKDBGCONSOLE_STATICLIB


#if _MSC_VER<1600
void CKDBGCONSOLE_INFO(const char* szStr, ...);
void CKDBGCONSOLE_WARN(const char* szStr, ...);
void CKDBGCONSOLE_ERROR(const char* szStr, ...);
#else
#define CKDBGCONSOLE_INFO(szStr,...)  \
	CKDbgConsole::WriteLine(CKDbgConsole::CDCLOG_INFO, szStr, __VA_ARGS__);
#define CKDBGCONSOLE_WARN(szStr,...)  \
	CKDbgConsole::WriteLine(CKDbgConsole::CDCLOG_WARNING, szStr, __VA_ARGS__);
#define CKDBGCONSOLE_ERROR(szStr,...) \
	CKDbgConsole::WriteLine(CKDbgConsole::CDCLOG_ERROR, szStr, __VA_ARGS__);
#endif

namespace CKDbgConsole
{
	enum INFO_TYPE
	{
		CDCLOG_INFO,
		CDCLOG_WARNING,
		CDCLOG_ERROR
	};

	// 打开控制台窗体
	CK_API bool ShowConsole();

	// 关闭控制台窗体
	CK_API void ExitConsole();

	/*
	** 向控制台输出一行文本
	** @Param emInfoType: 日志类型,详见 INFO_TYPE
	** @Param pszMsg: 文本字符串,支持变参格式化, 每次最多输出512个字符
	*/
	CK_API void WriteLine(INFO_TYPE emInfoType, const char * pszMsg, ...);
	/*
	** 向控制台输出文本
	** @Param pszMsg: 文本字符串, 支持变参格式化, 每次最多输出512个字符
	*/
	CK_API void Write(const char * pszMsg, ...);

	/*
	** 日志时间显示/隐藏
	** @Param bShow: true显示,false隐藏
	*/
	CK_API void ShowLogTime(bool bShow = true);
	/*
	** 设置命令行窗体标题
	** @Param szTitle: 命令行窗体标题
	*/
	CK_API void SetTitle(const char* szTitle);

};

//////////////////////////////////////////////////////////////////////////
#if _MSC_VER<1600
#include <stdarg.h>

void CKDBGCONSOLE_INFO(const char* szStr, ...)
{
    va_list argList;
    va_start(argList, szStr);
    char buff[512] = { 0 };
    ::vsprintf(buff, szStr, argList);
    CKDbgConsole::WriteLine(CKDbgConsole::CDCLOG_INFO, buff);
    va_end(argList);
}
void CKDBGCONSOLE_WARN(const char* szStr, ...)
{
    va_list argList;
    va_start(argList, szStr);
    char buff[512] = { 0 };
    ::vsprintf(buff, szStr, argList);
    CKDbgConsole::WriteLine(CKDbgConsole::CDCLOG_WARNING, buff);
    va_end(argList);
}
void CKDBGCONSOLE_ERROR(const char* szStr, ...)
{
    va_list argList;
    va_start(argList, szStr);
    char buff[512] = { 0 };
    ::vsprintf(buff, szStr, argList);
    CKDbgConsole::WriteLine(CKDbgConsole::CDCLOG_ERROR, buff);
    va_end(argList);
}
#endif
