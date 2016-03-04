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

#define CKDBGCONSOLE_WRITELINE(szStr) CKDbgConsole::GetInstance().WriteLine(szStr);

class CK_API CKDbgConsole
{
public:
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
    void WriteLine(char * pBuff, size_t nBuffSize);
    /*
    ** �����̨���һ���ı�
    ** @Param pszMsg: �ı��ַ���
    */
    void WriteLine(const char * pszMsg);
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

