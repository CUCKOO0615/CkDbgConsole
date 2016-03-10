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

#define CKDBGCONSOLE_INFO(szStr)  CKDbgConsole::GetInstance().WriteLine(szStr, CKDbgConsole::CDCLOG_INFO);
#define CKDBGCONSOLE_WARN(szStr)  CKDbgConsole::GetInstance().WriteLine(szStr, CKDbgConsole::CDCLOG_WARNING);
#define CKDBGCONSOLE_ERROR(szStr) CKDbgConsole::GetInstance().WriteLine(szStrm, CKDbgConsole::CDCLOG_ERROR);

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
    ** ��־ʱ����ʾ/���� 
    ** @Param bShow: true��ʾ,false����
    */
	void ShowLogTime(bool bShow = true);
    /*
    ** ���������д������
    ** @Param szTitle: �����д������
    */
	void SetTitle(const char* szTitle);
	/*
	** �򿪿���̨����
	*/
	bool ShowConsole();
	/*
	** �رտ���̨����
	*/
	void ExitConsole();
    /*
    ** �����̨���һ���ı�
    ** @Param pBuff: �����ı��Ļ�����
    ** @Param nBuffSize: ��������С
    */
	void WriteLine(char * pBuff, size_t nBuffSize, INFO_TYPE emInfoType);
    /*
    ** �����̨���һ���ı�
    ** @Param pszMsg: �ı��ַ���
    */
	void WriteLine(const char * pszMsg, INFO_TYPE emInfoType = CDCLOG_INFO);
    /*
    ** �����̨���һ���ı�
    ** @Param strMsg: �ı��ַ���
    */
    void Write(char* pBuff, size_t nBuffSize);
    /*
    ** �����̨����ı�
    ** @Param pszMsg: �ı��ַ���
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

