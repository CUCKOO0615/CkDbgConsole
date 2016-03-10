//************************************************
//◇作者：CUCKOO0615
//◇日期：2015/01/26 16:37:16
//◇说明：MFC命令行调试工具, 仅限在基于MFC的程序中使用
//************************************************
#pragma once

#ifdef EXPORT_CKDBGCONSOLE
#define CK_API __declspec(dllexport)
#else 
#define CK_API __declspec(dllimport)
#endif

#include <windows.h>

#if _MSC_VER<1600
#define CKDBGCONSOLE_INFO(szStr)  CKDbgConsole::GetInstance().WriteLine(CKDbgConsole::CDCLOG_INFO, szStr);
#define CKDBGCONSOLE_WARN(szStr)  CKDbgConsole::GetInstance().WriteLine(CKDbgConsole::CDCLOG_WARNING, szStr);
#define CKDBGCONSOLE_ERROR(szStr) CKDbgConsole::GetInstance().WriteLine(CKDbgConsole::CDCLOG_ERROR, szStr);
#else
#define CKDBGCONSOLE_INFO(szStr,...)  CKDbgConsole::GetInstance().WriteLine(CKDbgConsole::CDCLOG_INFO, szStr, __VA_ARGS__);
#define CKDBGCONSOLE_WARN(szStr,...)  CKDbgConsole::GetInstance().WriteLine(CKDbgConsole::CDCLOG_WARNING, szStr, __VA_ARGS__);
#define CKDBGCONSOLE_ERROR(szStr,...) CKDbgConsole::GetInstance().WriteLine(CKDbgConsole::CDCLOG_ERROR, szStr, __VA_ARGS__);
#endif

class CK_API CKDbgConsole
{
public:
	typedef enum emCKDbgConsoleInfoType
	{
		CDCLOG_INFO, CDCLOG_WARNING, CDCLOG_ERROR
	}INFO_TYPE;

	//获取单例
    static CKDbgConsole & GetInstance();

	/*
	** 打开控制台窗体
	*/
	bool ShowConsole();
	/*
	** 向控制台输出一行文本
	** @Param pszMsg: 文本字符串,支持变参格式化
	*/
	void WriteLine(INFO_TYPE emInfoType, const char * pszMsg, ...);
	/*
	** 向控制台输出文本
	** @Param pszMsg: 文本字符串, 支持变参格式化
	*/
	void Write(const char * pszMsg, ...);
	/*
	** 关闭控制台窗体
	*/
	void ExitConsole();
	/*
	** 日志时间显示/隐藏
	** @Param bShow: true显示,false隐藏
	*/
	void ShowLogTime(bool bShow = true);
    /*
    ** 设置命令行窗体标题
    ** @Param szTitle: 命令行窗体标题
    */
	void SetTitle(const char* szTitle);

private:
    CKDbgConsole();
    bool m_bInited;
    bool m_bShowLogTime;
    HANDLE m_hConsoleHandle;
	CRITICAL_SECTION m_csWriteLock;
public:
    ~CKDbgConsole();
};

