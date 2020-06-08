/*
 * Created with the H3Plugin Template
 * A HoMM III plugin using the H3API library.
 */
#include "Hooks.hpp"
#include "INIReader.h"
#include "Localization.hpp"
#include "Config.hpp"

#include <string>
#include "shlwapi.h"

std::string GetOptionsFilePath()
{
    std::string filename = "options.ini";

    HMODULE hModule = NULL;
    if (!GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS, (LPCTSTR)GetOptionsFilePath, &hModule))
    {
        return filename;
    }

    CHAR path[MAX_PATH]{ 0 };
    if (GetModuleFileNameA(hModule, path, sizeof(path)) <= 0 || GetLastError() == ERROR_INSUFFICIENT_BUFFER)
    {
        return filename;
    }

    PathRemoveFileSpecA(path);
    filename.insert(0, "\\");
    filename.insert(0, path);

    return filename;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    static BOOL pluginOn = FALSE;
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        if (!pluginOn)
        {
            pluginOn = TRUE;

            INIReader options(GetOptionsFilePath().c_str());

            // TODO: check hash

            Config::Initialize(options);
            Localization::Initialize(options);

            Patcher *p = _P = GetPatcher();
            if (!p)
            {
                MessageBoxA(nullptr, "Error", "Patcher not found. Prolably Version mismatch or patcher_x86.dll missing", MB_OK | MB_ICONERROR );
                break;
            }

            // * make sure this plugin only installs once
            if (!p->GetInstance(PLUGIN_NAME))
            {
                _PI = p->CreateInstance(PLUGIN_NAME);
                PatcherInstance *pi = _PI;
                if (!pi)
                {
                    MessageBoxA(nullptr, "Error", "Can't create pacther instance.", MB_OK | MB_ICONERROR);
                    break;
                }

                hooks_init(pi);
            }
        }
        break;
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
    default:
        break;
    }
    return TRUE;
}