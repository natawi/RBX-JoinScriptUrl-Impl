#include "pch.h"
#include "Patches.h"
#include "RobloxMFCHooks.h"
#include "RobloxMFCClasses.h"

START_PATCH_LIST()

    ADD_PATCH(CRobloxApp__InitInstance, CRobloxApp__InitInstance_hook)
    ADD_PATCH(CRobloxCommandLineInfo__ParseParam, CRobloxCommandLineInfo__ParseParam_hook)

END_PATCH_LIST()

// To be added to game imports
void __declspec(dllexport) doNothing() {}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    if (ul_reason_for_call == DLL_PROCESS_ATTACH)
    {
        try
        {
            Patches::Apply();
        }
        catch (const std::runtime_error& error)
        {
#ifdef _DEBUG
            MessageBox(nullptr, error.what(), "Patch Failed", MB_ICONERROR);
#endif

            ExitProcess(EXIT_FAILURE);
        }
    }

    return TRUE;
}
