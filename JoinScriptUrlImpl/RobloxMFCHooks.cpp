#include "pch.h"
#include "RobloxMFCHooks.h"
#include "RobloxMFCClasses.h"

static std::wstring joinScriptUrl;

CRobloxApp__InitInstance_t CRobloxApp__InitInstance = (CRobloxApp__InitInstance_t)0x00452900;

BOOL __fastcall CRobloxApp__InitInstance_hook(CRobloxApp* _this)
{
    if (!CRobloxApp__InitInstance(_this))
        return FALSE;

    if (!joinScriptUrl.empty())
    {
        try
        {
            CRobloxDoc* document = CRobloxApp__CreateDocument(_this);
            CWorkspace__ExecUrlScript(document->workspace, joinScriptUrl.c_str(), VARIANTARG(), VARIANTARG(), VARIANTARG(), VARIANTARG(), nullptr);
        }
        catch (std::runtime_error& exception)
        {
            CWinApp__DoMessageBox(_this, exception.what(), MB_ICONERROR | MB_SETFOREGROUND, 0);
            return FALSE;
        }
    }

    return TRUE;
}

CRobloxCommandLineInfo__ParseParam_t CRobloxCommandLineInfo__ParseParam = (CRobloxCommandLineInfo__ParseParam_t)0x00450AC0;

void __fastcall CRobloxCommandLineInfo__ParseParam_hook(CRobloxCommandLineInfo* _this, void*, const TCHAR* pszParam, BOOL bFlag, BOOL bLast)
{
    static bool joinArgWasLast = false;

    if (joinArgWasLast && !bFlag)
    {
        int size = MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), nullptr, 0);
        joinScriptUrl.resize(size);
        MultiByteToWideChar(CP_ACP, 0, pszParam, strlen(pszParam), &joinScriptUrl[0], size);

        _this->m_bRunAutomated = TRUE;

        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }
    
    joinArgWasLast = false;

    if (bFlag && _stricmp(pszParam, "JoinScriptUrl") == 0)
    {
        joinArgWasLast = true;

        CCommandLineInfo__ParseLast(_this, bLast);
        return;
    }

    CRobloxCommandLineInfo__ParseParam(_this, pszParam, bFlag, bLast);
}
