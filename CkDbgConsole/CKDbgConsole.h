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

#define CKDBGCONSOLE_WRITELINE(szStr) CKDbgConsole::GetInstance().WriteLine(szStr);

class CK_API CKDbgConsole
{
public:
	//获取单例
    static CKDbgConsole & GetInstance();

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
	/*
	** 打开控制台窗体
	*/
	bool ShowConsole();
	/*
	** 关闭控制台窗体
	*/
	void ExitConsole();
    /*
    ** 向控制台输出一行文本
    ** @Param pBuff: 包含文本的缓冲区
    ** @Param nBuffSize: 缓冲区大小
    */
    void WriteLine(char * pBuff, size_t nBuffSize);
    /*
    ** 向控制台输出一行文本
    ** @Param pszMsg: 文本字符串
    */
    void WriteLine(const char * pszMsg);
    /*
    ** 向控制台输出一行文本
    ** @Param strMsg: 文本字符串
    */
    void Write(char* pBuff, size_t nBuffSize);
    /*
    ** 向控制台输出文本
    ** @Param pszMsg: 文本字符串
    */
    void Write(const char * pszMsg);


private:
    CKDbgConsole();
    bool m_bInited;
    bool m_bShowLogTime;
    HANDLE m_hConsoleHandle;
	CRITICAL_SECTION m_csWriteLock;
public:
    ~CKDbgConsole();
};

