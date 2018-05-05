// chgfldt.cpp : Defines the entry point for the console application.
//
#ifndef _MINGW
#include "stdafx.h"
#endif

#include <stdio.h>
#include <Windows.h>

#define MAX_DATETIME 24

void ParseTime(SYSTEMTIME *in_st, char *out_string) {

    const char *DayOfWeek[] = {"Sun", "Mon", "Tue","Wed","Thu","Fri","Sat"};
    // yyyy-mm-dd XXX hh:mm:ss
    wsprintf(out_string, "%04d-%02d-%02d %s %02d:%02d:%02d", in_st->wYear, in_st->wMonth, in_st->wDay, \
        DayOfWeek[in_st->wDayOfWeek], in_st->wHour, in_st->wMinute, in_st->wSecond);
}

int FileTimeToLocalSystemTime(const FILETIME *pFileTime , SYSTEMTIME *pLocSystemTime) {
    int result = 0;
    SYSTEMTIME tmpSystemTime;

    result = FileTimeToSystemTime(pFileTime, &tmpSystemTime);
    if (result != 0) {
        result = SystemTimeToTzSpecificLocalTime(NULL, &tmpSystemTime, pLocSystemTime);
    }
    return result;
}

int LocalSystemTimeToFileTime(const SYSTEMTIME *pLocSystemTime, FILETIME *pFileTime) {
    int result = 0;
    FILETIME tmpFileTime;

    result=SystemTimeToFileTime(pLocSystemTime, &tmpFileTime);
    if (result != 0) {
        result = LocalFileTimeToFileTime(&tmpFileTime, pFileTime);
    }
    return result;
}

int ShowDateTime(HANDLE hFile) {
    if (hFile == NULL) {
        printf("file is null.\n");
        return -2;
    }

    FILETIME ftCreTime, ftAccTime, ftWriTime;

    //get file time
    if ( GetFileTime(hFile, &ftCreTime, &ftAccTime, &ftWriTime) ) {
        SYSTEMTIME stLOCCreTime, stLOCAccTime, stLOCWriTime;

        FileTimeToLocalSystemTime(&ftCreTime, &stLOCCreTime);
        FileTimeToLocalSystemTime(&ftAccTime, &stLOCAccTime);
        FileTimeToLocalSystemTime(&ftWriTime, &stLOCWriTime);

        //Build a string to show time and date.
        char CreTime[MAX_DATETIME];
        char AccTime[MAX_DATETIME];
        char WriTime[MAX_DATETIME];
        ParseTime(&stLOCCreTime, CreTime);
        ParseTime(&stLOCAccTime, AccTime);
        ParseTime(&stLOCWriTime, WriTime);

        //print result
        printf("===== The information of the target file's date time =====\n");
        printf("Created : %s\n", CreTime);
        printf("Modified: %s\n", WriTime);
        printf("Accessed: %s\n", AccTime);
        return 0;
    } else {
        printf("GetFileTime error.\n");
        return -3;
    }
}

int SetDateTime(HANDLE hFile, char *pCDate, char *pCTime, char *pADate, char *pATime, char *pMDate, char *pMTime) {
    int result = 0;
    if (hFile == NULL) {
        printf("file is null.\n");
        result = -2;
        return result;
    }

    if ((pCDate == NULL || strlen(pCDate) <= 0) && 
        (pCTime == NULL || strlen(pCTime) <= 0) && 
        (pADate == NULL || strlen(pADate) <= 0) && 
        (pATime == NULL || strlen(pATime) <= 0) && 
        (pMDate == NULL || strlen(pMDate) <= 0) && 
        (pMTime == NULL || strlen(pMTime) <= 0)) {
        return result;
    }

    FILETIME ftCreTime, ftAccTime, ftWriTime;
    // get file time
    result = GetFileTime(hFile, &ftCreTime, &ftAccTime, &ftWriTime);
    if (result == 0) {
        printf("GetFileTime error.\n");
        return -3;
    }

    SYSTEMTIME stLOCCreTime, stLOCAccTime, stLOCWriTime;
    FileTimeToLocalSystemTime(&ftCreTime, &stLOCCreTime);
    FileTimeToLocalSystemTime(&ftAccTime, &stLOCAccTime);
    FileTimeToLocalSystemTime(&ftWriTime, &stLOCWriTime);

    int wYear=-1, wMonth=13, wDay=32, wHour=25, wMinute=61, wSecond=61;
    if (pCDate != NULL && strlen(pCDate) > 0) {
    #ifdef _DEBUG
        printf("pCDate=[%s]\n", pCDate);
    #endif
        sscanf(pCDate, "%d-%d-%d", &wYear, &wMonth, &wDay);

    #ifdef _DEBUG
        printf("Year:%dMonth:%dDay:%d\n", wYear, wMonth, wDay);
    #endif

        stLOCCreTime.wYear = wYear;
        stLOCCreTime.wMonth= wMonth;
        stLOCCreTime.wDay  = wDay;
    }

    if (pADate != NULL && strlen(pADate) > 0) {
    #ifdef _DEBUG
        printf("pADate=[%s]\n", pADate);
    #endif
        sscanf(pADate, "%d-%d-%d", &wYear, &wMonth, &wDay);

    #ifdef _DEBUG
        printf("Year:%dMonth:%dDay:%d\n", wYear, wMonth, wDay);
    #endif

        stLOCAccTime.wYear = wYear;
        stLOCAccTime.wMonth= wMonth;
        stLOCAccTime.wDay  = wDay;
    }

    if (pMDate != NULL && strlen(pMDate) > 0) {
    #ifdef _DEBUG
        printf("pMDate=[%s]\n", pMDate);
    #endif
        sscanf(pMDate, "%d-%d-%d", &wYear, &wMonth, &wDay);

    #ifdef _DEBUG
        printf("Year:%dMonth:%dDay:%d\n", wYear, wMonth, wDay);
    #endif

        stLOCWriTime.wYear = wYear;
        stLOCWriTime.wMonth= wMonth;
        stLOCWriTime.wDay  = wDay;
    }

    if (pCTime != NULL && strlen(pCTime) > 0) {
    #ifdef _DEBUG
        printf("pCTime=[%s]\n", pCTime);
    #endif
        sscanf(pCTime, "%d:%d:%d", &wHour, &wMinute, &wSecond);

    #ifdef _DEBUG
        printf("Hour:%dMinute:%dSecond:%d\n", wHour, wMinute, wSecond);
    #endif

        stLOCCreTime.wHour  =wHour;
        stLOCCreTime.wMinute=wMinute;
        stLOCCreTime.wSecond=wSecond;
    }

    if (pATime != NULL && strlen(pATime) > 0) {
    #ifdef _DEBUG
        printf("pATime=[%s]\n", pATime);
    #endif
        sscanf(pATime, "%d:%d:%d", &wHour, &wMinute, &wSecond);

    #ifdef _DEBUG
        printf("Hour:%dMinute:%dSecond:%d\n", wHour, wMinute, wSecond);
    #endif

        stLOCAccTime.wHour  =wHour;
        stLOCAccTime.wMinute=wMinute;
        stLOCAccTime.wSecond=wSecond;
    }

    if (pMTime != NULL && strlen(pMTime) > 0) {
    #ifdef _DEBUG
        printf("pMTime=[%s]\n", pMTime);
    #endif
        sscanf(pMTime, "%d:%d:%d", &wHour, &wMinute, &wSecond);

    #ifdef _DEBUG
        printf("Hour:%dMinute:%dSecond:%d\n", wHour, wMinute, wSecond);
    #endif

        stLOCWriTime.wHour  =wHour;
        stLOCWriTime.wMinute=wMinute;
        stLOCWriTime.wSecond=wSecond;
    }

    #ifdef _DEBUG
    printf("Created :%04d/%02d/%02d %02d:%02d:%02d\n", stLOCCreTime.wYear, stLOCCreTime.wMonth, stLOCCreTime.wDay, stLOCCreTime.wHour, stLOCCreTime.wMinute, stLOCCreTime.wSecond);
    #endif
    result = LocalSystemTimeToFileTime(&stLOCCreTime, &ftCreTime);
    if (result == 0) {
        printf("Created error.\n");
        return -4;
    }
    #ifdef _DEBUG
    printf("Modified:%04d/%02d/%02d %02d:%02d:%02d\n", stLOCWriTime.wYear, stLOCWriTime.wMonth, stLOCWriTime.wDay, stLOCWriTime.wHour, stLOCWriTime.wMinute, stLOCWriTime.wSecond);
    #endif
    result = LocalSystemTimeToFileTime(&stLOCWriTime, &ftWriTime);
    if (result == 0) {
        printf("Modified error.\n");
        return -5;
    }
    #ifdef _DEBUG
    printf("Accessed:%04d/%02d/%02d %02d:%02d:%02d\n", stLOCAccTime.wYear, stLOCAccTime.wMonth, stLOCAccTime.wDay, stLOCAccTime.wHour, stLOCAccTime.wMinute, stLOCAccTime.wSecond);
    #endif
    result = LocalSystemTimeToFileTime(&stLOCAccTime, &ftAccTime);
    if (result == 0) {
        printf("Accessed error.\n");
        return -6;
    }

    // If the function succeeds, the return value is nonzero.
    // If the function fails, the return value is zero. To get extended error information, call GetLastError.
    result = SetFileTime(hFile, &ftCreTime, &ftAccTime, &ftWriTime);
    if (result == 0) {
        printf("SetFileTime error.\n");
        return -7;
    }
    return 0;
}

void ShowUsage() {
    printf("Usage:\n");
    printf("  chgfldt [/D | /H] /F:filename [options]\n\n");
    printf("    /D:sisplay the file's datetime informations.\n");
    printf("    /H:show this.\n");
    printf("    /F:the targer file.\n\n");
    printf("    options:\n");
    printf("        /CD: Created date(format:yyyy-mm-dd).\n");
    printf("        /AD:Accessed date(format:yyyy-mm-dd).\n");
    printf("        /MD:Modified date(format:yyyy-mm-dd).\n");
    printf("        /CT: Created time(format:hh:mi:ss).\n");
    printf("        /AT:Accessed time(format:hh:mi:ss).\n");
    printf("        /MT:Modified time(format:hh:mi:ss).\n\n");
    printf("  return code:\n");
    printf("    0:Normal end.\n");
    printf("   -1:file open error.\n");
    printf("   -2:file is null.\n");
    printf("   -3:GetFileTime error.\n");
    printf("   -4:Created error.\n");
    printf("   -5:Modified error.\n");
    printf("   -6:Accessed error.\n");
    printf("   -7:SetFileTime error.\n");
}

/*
 * chgfldt [/D | /H] /F:filename options
 * [/D | /Help] 
 *  /F:filename 
 * [/CD:yyy-mm-dd]
 * [/CT:hh:mm:ss]
 * [/AD:yyy-mm-dd]
 * [/AT:hh:mm:ss]
 * [/MD:yyy-mm-dd]
 * [/MT:hh:mm:ss]
 
 0:Normal end.
-1:file open error.
-2:file is null.
-3:GetFileTime error.
-4:Created error.
-5:Modified error.
-6:Accessed error.
-7:SetFileTime error.

 */
int main(int argc, char* argv[]) {

    char pFileName[MAX_PATH];
    char pCDate[11]; // yyyy-mm-dd
    char pCTime[9];  // hh:mm:ss
    char pADate[11]; // yyyy-mm-dd
    char pATime[9];  // hh:mm:ss
    char pMDate[11]; // yyyy-mm-dd
    char pMTime[9];  // hh:mm:ss
    int i;
    int flag = 0;
    HANDLE hFile;
    int result = 0;

    printf("Change File Date Time Version 0.0.2 Compiled on May 6 2018 for Windows\n");
    printf("Copyright (C) 2017-2018 Dubenju(dubenju@126.com). All rights reserved.\n\n");

    memset(pFileName, 0, sizeof(pFileName));
    memset(pCDate, 0, sizeof(pCDate));
    memset(pCTime, 0, sizeof(pCTime));
    memset(pADate, 0, sizeof(pADate));
    memset(pATime, 0, sizeof(pATime));
    memset(pMDate, 0, sizeof(pMDate));
    memset(pMTime, 0, sizeof(pMTime));

    #ifdef _DEBUG
    printf("parameters:\n");
    #endif
    for (i = 0; i < argc; i ++) {
    #ifdef _DEBUG
        printf("%s\n", argv[i]);
    #endif

        if (memcmp("/D", argv[i], 2) == 0) {
            flag = 1;
        }
        if (memcmp("/H", argv[i], 2) == 0) {
            ShowUsage();
            return result;
        }
        if (memcmp("/F:", argv[i], 3) == 0) {
            wsprintf(pFileName, "%s", argv[i] + 3);
        }
        if (memcmp("/CD:", argv[i], 4) == 0) {
            wsprintf(pCDate, "%s", argv[i] + 4);
        }
        if (memcmp("/CT:", argv[i], 4) == 0) {
            wsprintf(pCTime, "%s", argv[i] + 4);
        }
        if (memcmp("/AD:", argv[i], 4) == 0) {
            wsprintf(pADate, "%s", argv[i] + 4);
        }
        if (memcmp("/AT:", argv[i], 4) == 0) {
            wsprintf(pATime, "%s", argv[i] + 4);
        }
        if (memcmp("/MD:", argv[i], 4) == 0) {
            wsprintf(pMDate, "%s", argv[i] + 4);
        }
        if (memcmp("/MT:", argv[i], 4) == 0) {
            wsprintf(pMTime, "%s", argv[i] + 4);
        }
    }

#ifdef _DEBUG
    printf("\npFileName=[%s].\n", pFileName);
    printf("pCDate=[%s].\n", pCDate);
    printf("pCTime=[%s].\n", pCTime);
    printf("pADate=[%s].\n", pADate);
    printf("pATime=[%s].\n", pATime);
    printf("pMDate=[%s].\n", pMDate);
    printf("pMTime=[%s].\n", pMTime);
#endif

    hFile = CreateFile(pFileName, 
                    GENERIC_WRITE, // GENERIC_READ,
                    FILE_SHARE_WRITE,
                    (LPSECURITY_ATTRIBUTES) NULL,
                    OPEN_EXISTING,
                    FILE_FLAG_BACKUP_SEMANTICS, // FILE_ATTRIBUTE_NORMAL || 
                    (HANDLE) NULL);
    if (hFile == INVALID_HANDLE_VALUE) {
        printf("%s open error.\n", pFileName);
        return -1;
    }

    printf("Target File: %s\n", pFileName);
    result = ShowDateTime(hFile);
    if (flag == 1) {
        goto end_main;
    }

    result = SetDateTime(hFile, pCDate, pCTime, pADate, pATime, pMDate, pMTime);
    if (result == 0) {
        result = ShowDateTime(hFile);
    }

err_main:
end_main:
    CloseHandle(hFile);
    hFile = NULL;
    return result;
}
