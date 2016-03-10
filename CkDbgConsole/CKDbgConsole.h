//************************************************
//�����ߣ�CUCKOO0615
//�����ڣ�2015/01/26 16:37:16
//��˵����MFC�����е��Թ���, �����ڻ���MFC�ĳ�����ʹ��
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

	//��ȡ����
    static CKDbgConsole & GetInstance();

	/*
	** �򿪿���̨����
	*/
	bool ShowConsole();
	/*
	** �����̨���һ���ı�
	** @Param pszMsg: �ı��ַ���,֧�ֱ�θ�ʽ��
	*/
	void WriteLine(INFO_TYPE emInfoType, const char * pszMsg, ...);
	/*
	** �����̨����ı�
	** @Param pszMsg: �ı��ַ���, ֧�ֱ�θ�ʽ��
	*/
	void Write(const char * pszMsg, ...);
	/*
	** �رտ���̨����
	*/
	void ExitConsole();
	/*
	** ��־ʱ����ʾ/����
	** @Param bShow: true��ʾ,false����
	*/
	void ShowLogTime(bool bShow = true);
    /*
    ** ���������д������
    ** @Param szTitle: �����д������
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

