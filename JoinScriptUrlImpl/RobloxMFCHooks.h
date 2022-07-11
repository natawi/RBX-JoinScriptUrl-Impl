#pragma once

// CRobloxApp

BOOL __fastcall CRobloxApp__InitInstance_hook(class CRobloxApp* _this);

// CRobloxCommandLineInfo

void __fastcall CRobloxCommandLineInfo__ParseParam_hook(class CRobloxCommandLineInfo* _this, void*, const TCHAR* pszParam, BOOL bFlag, BOOL bLast);
