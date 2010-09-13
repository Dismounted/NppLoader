// Notepad++ Loader
// -- Using the Image File Execution Options Method
// Created By Hanson Wong (http://bbcreatives.com/)

#include <windows.h>
#include <winreg.h>

using namespace std;

int main(int argc, char *argv[])
{
    // Set Necessary Variables
    STARTUPINFO si = { sizeof(si) };
    PROCESS_INFORMATION pi;

    // Notepad++ Default Location
    char szExe[1024] = "\"C:\\Program Files\\Notepad++\\notepad++.exe\"";

    // Get Notepad++ Location From Registry
    HKEY hKey;

    if (RegOpenKeyEx(HKEY_LOCAL_MACHINE, "SOFTWARE\\Notepad++", 0, KEY_QUERY_VALUE, &hKey) == ERROR_SUCCESS)
    {
        DWORD iType;
        unsigned char sData[1024];
        DWORD iDataSize = 1024;

        if (RegQueryValueEx(hKey, "", NULL, &iType, sData, &iDataSize) == ERROR_SUCCESS)
        {
            strcpy(szExe, "\"");
            strcat(szExe, (char*)sData);
            strcat(szExe, "\\notepad++.exe\"");
        }

        RegCloseKey(hKey);
    }

    // Add File Reference
    if (argc > 2)
    {
        strcat(szExe, " \"");

        for (int i = 2; i < argc; i++)
        {
            strcat(szExe, argv[i]);
            
            if (i != (argc - 1))
            {
                strcat(szExe, " ");
            }
        }

        strcat(szExe, "\"");
    }

    // Debugging!
    //MessageBox(NULL, szExe, "Command", 0);

    // Start Notepad++
    CreateProcess(0, szExe, 0, 0, FALSE, 0, 0, 0, &si, &pi);

    // Clean Up
    CloseHandle(pi.hProcess);
    CloseHandle(pi.hThread);

    // Exit Application
    return 0;
}
