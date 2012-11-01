/* 
 * A Small Class to Read INI File
 * 
 * Licensed under The Code Project Open License (CPOL). For more information 
 * visit http://www.codeproject.com/info/cpol10.aspx.
 * 
 * Copyright (C) 2005, Xiangxiong Jian.
 * 
 * Link to original source code:
 * http://www.codeproject.com/Articles/10809/A-Small-Class-to-Read-INI-File
 * 
 * Adapted by Ericson Norberto.
 * 
*/
#include "cIni.h"
#include "cDefines.h"

cIni::cIni()
{
}

cIni::~cIni()
{
}

void cIni::Load(const char* szFileName)
{
    memset(m_szFileName, 0x00, 255);
    memcpy(m_szFileName, szFileName, strlen(szFileName));
}

int cIni::ReadInteger(const char* szSection, const char* szKey, int iDefaultValue)
{
    int iResult = GetPrivateProfileInt(szSection,  szKey, iDefaultValue, m_szFileName); 
    
    return iResult;
}

float cIni::ReadFloat(const char* szSection, const char* szKey, float fltDefaultValue)
{
    char  szResult[255];
    char  szDefault[255];
    float fltResult;
    
    sprintf(szDefault, "%f",fltDefaultValue);
    GetPrivateProfileString(szSection,  szKey, szDefault, szResult, 255, m_szFileName);
    fltResult =  atof(szResult);
    
    return fltResult;
}

bool cIni::ReadBoolean(const char* szSection, const char* szKey, bool bolDefaultValue)
{
    char szResult[255];
    char szDefault[255];
    bool bolResult;
    
    sprintf(szDefault, "%s", bolDefaultValue? "True" : "False");
    GetPrivateProfileString(szSection, szKey, szDefault, szResult, 255, m_szFileName); 
    bolResult = (strcmp(szResult, "True") == 0 || strcmp(szResult, "true") == 0) ? true : false;
    
    return bolResult;
}

char* cIni::ReadString(const char* szSection, const char* szKey, const char* szDefaultValue)
{
    char* szResult = new char[255];
    
    memset(szResult, 0x00, 255);
    GetPrivateProfileString(szSection,  szKey, szDefaultValue, szResult, 255, m_szFileName); 
    
    return szResult;
}

void cIni::WriteInteger(const char* szSection, const char* szKey, int iValue)
{
    char szValue[255];
    
    sprintf(szValue, "%d", iValue);
    WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}

void cIni::WriteFloat(const char* szSection, const char* szKey, float fltValue)
{
    char szValue[255];
    
    sprintf(szValue, "%f", fltValue);
    WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}

void cIni::WriteBoolean(const char* szSection, const char* szKey, bool bolValue)
{
    char szValue[255];
    
    sprintf(szValue, "%s", bolValue ? "True" : "False");
    WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName); 
}

void cIni::WriteString(const char* szSection, const char* szKey, const char* szValue)
{
    WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
}