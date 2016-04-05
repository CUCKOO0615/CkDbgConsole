//************************************************
//�����ߣ�CUCKOO0615
//�����ڣ�2015/01/26 16:37:16
//��˵����MFC�����е��Թ���, �����ڻ���MFC�ĳ�����ʹ�� (��̬����)
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

	// �򿪿���̨����
	CK_API bool ShowConsole();

	// �رտ���̨����
	CK_API void ExitConsole();

	/*
	** �����̨���һ���ı�
	** @Param emInfoType: ��־����,��� INFO_TYPE
	** @Param pszMsg: �ı��ַ���,֧�ֱ�θ�ʽ��, ÿ��������512���ַ�
	*/
	CK_API void WriteLine(INFO_TYPE emInfoType, const char * pszMsg, ...);
	/*
	** �����̨����ı�
	** @Param pszMsg: �ı��ַ���, ֧�ֱ�θ�ʽ��, ÿ��������512���ַ�
	*/
	CK_API void Write(const char * pszMsg, ...);

	/*
	** ��־ʱ����ʾ/����
	** @Param bShow: true��ʾ,false����
	*/
	CK_API void ShowLogTime(bool bShow = true);
	/*
	** ���������д������
	** @Param szTitle: �����д������
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
