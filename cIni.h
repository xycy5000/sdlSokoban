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
#ifndef CINI_H
    #define CINI_H

class cIni {
    public:
        cIni();
        virtual ~cIni();
        
        void Load(const char* szFileName);
        
        int   ReadInteger(const char* szSection, const char* szKey, int iDefaultValue);
        float ReadFloat(const char* szSection, const char* szKey, float fltDefaultValue);
        bool  ReadBoolean(const char* szSection, const char* szKey, bool bolDefaultValue);
        char* ReadString(const char* szSection, const char* szKey, const char* szDefaultValue);

        void WriteInteger(const char* szSection, const char* szKey, int iValue);
        void WriteFloat(const char* szSection, const char* szKey, float fltValue);
        void WriteBoolean(const char* szSection, const char* szKey, bool bolValue);
        void WriteString(const char* szSection, const char* szKey, const char* szValue);
        
    private:
        char m_szFileName[255];
};
#endif	/* CINI_H */