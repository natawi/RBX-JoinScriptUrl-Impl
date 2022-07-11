#pragma once

#include <oaidl.h>

// CWorkspace

class CWorkspace;

const auto CWorkspace__ExecUrlScript = (HRESULT(__stdcall*)(CWorkspace* workspace, LPCWSTR, VARIANTARG, VARIANTARG, VARIANTARG, VARIANTARG, LPSAFEARRAY*))0x0047EC10;

// CRobloxDoc

class CRobloxDoc
{
private:
	void* padding1[40];
public:
	CWorkspace* workspace;
};

// CWinApp

class CWinApp {};

const auto CWinApp__DoMessageBox = (int(__thiscall*)(CWinApp* _this, LPCTSTR lpszPrompt, UINT nType, UINT nIDPrompt))0x007A805E;

// CRobloxApp

class CRobloxApp : public CWinApp {};

typedef BOOL(__thiscall* CRobloxApp__InitInstance_t)(CRobloxApp* _this);
extern CRobloxApp__InitInstance_t CRobloxApp__InitInstance;

const auto CRobloxApp__CreateDocument = (CRobloxDoc*(__thiscall*)(CRobloxApp* _this))0x0044F6E0;

// CCommandLineInfo

class CCommandLineInfo
{
private:
	void* padding1[3];
public:
	BOOL m_bRunAutomated;
};

const auto CCommandLineInfo__ParseLast = (void(__thiscall*)(CCommandLineInfo* _this, BOOL bLast))0x007A80A0;

// CRobloxCommandLineInfo

class CRobloxCommandLineInfo : public CCommandLineInfo {};

typedef void(__thiscall* CRobloxCommandLineInfo__ParseParam_t)(CRobloxCommandLineInfo* _this, const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
extern CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam;
