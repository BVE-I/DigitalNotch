//
// Generated on 2024/08/05 by inimoni 
//

/*
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
Documentation
  Struct = Section name, Field = Key name.
  The function used is only a declaration, load(), and save().
  The constructor automatically reads initialization file [initFileName].
  Please rewrite [initFileName] in the source freely.
  It becomes Windows folder when there is not path. The relative path can be used.

Example
#include "SampleIni.h"
void CTestDlg::OnButton1()
{
    //initFileName = "./sample.ini";
    SampleIni data1;                   // Open ./sample.ini
    int v = data1.Sample.value;        // [Sample]-value Get
    data1.Sample.value = v+1;          // [Sample]-value Modify
    data1.save();                      // Save ./Sample.ini (Opened file)

    SampleIni data2("sample.ini");     // Open C:/WINDOWS/Sample.ini
    data2.load("./sample.ini");        // Open Specified file.
    data2.save();                      // Save Opened file (Making at not being)
}

Supplementation
  Reading and writing becomes the unit of the file.
  [initFileName] is the same as the argument of GetPrivateProfileString() of SDK.
- - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - 
*/

#ifndef DIGITALNOTCHINI_H
#define DIGITALNOTCHINI_H

#include <string>
using namespace std;

#include <windows.h>
#include <tchar.h>
#include <stdio.h>

#ifdef _UNICODE
	typedef std::wstring string_t;
#else
	typedef std::string string_t;
#endif

namespace inimoni{
    template<class T>
    static bool inirw(int is_read, string_t& fname, string_t sec, string_t key, T& val_t);
};

/**
    DigitalNotch.ini input output class.
*/
class DigitalNotchIni
{
public:                                                                 
                                                                        
    DigitalNotchIni(string_t fname=_T(""))                          
    {                                                                   
        initFileName = _T("./DigitalNotch.ini"); //Default file.    
        init();                                                         
        load(fname);                                                    
    }                                                                   
                                                                        
    /**                                                                 
        INI file is read.                                               
        @param fname Filename                                           
        When there is not a file, It becomes initFileName.              
        When there is not a pass, It becomes Windows folder.            
    */                                                                  
    bool load(string_t fname=_T(""))                                  
    {                                                                   
        if(fname.empty()){                                              
            fname = initFileName;                                       
        }                                                               
        loadFileName = fname;                                           
        WIN32_FIND_DATA fd;                                             
        HANDLE h = ::FindFirstFile(fname.c_str(), &fd);                 
        if (h != INVALID_HANDLE_VALUE) {                                
            iniRW(fname,1);                                             
        }                                                               
        return (h != INVALID_HANDLE_VALUE);                             
    }                                                                   
                                                                        
    /**                                                                 
        It writes it in the INI file.                                   
        @param fname Filename                                           
        When there is not a file, It becomes open file.                 
        When there is not a pass, It becomes Windows folder.            
    */                                                                  
    bool save(string_t fname=_T(""))                                  
    {                                                                   
        if(fname.empty()){                                              
            fname = loadFileName;                                       
        }                                                               
        iniRW(fname,0);                                                 
        return true;                                                    
    }                                                                   

public:                                                                 

    // NotchValue
    struct _NotchValue
    {
        int      PowerIndex;
        int      PowerSaveDataNumber;
        int      BrakeIndex;
        int      BrakeSaveDataNumber;
        int      Delay;
        int      Interval;
    } NotchValue;

    // FirstPanelValue
    struct _FirstPanelValue
    {
        int      InputIndex;
        int      OutputIndex;
        int      SaveDataNumber;
        int      Delay;
        int      Interval;
    } FirstPanelValue;

    // SecondPanelValue
    struct _SecondPanelValue
    {
        int      InputIndex;
        int      OutputIndex;
        int      SaveDataNumber;
        int      Delay;
        int      Interval;
    } SecondPanelValue;

protected:

    string_t initFileName;
    string_t loadFileName;

    bool iniRW(string_t f, int r)    
    {                                
        string_t s;                  

        s = _T("NotchValue");
        inimoni::inirw( r,f,s, _T("PowerIndex       "), NotchValue.PowerIndex );
        inimoni::inirw( r,f,s, _T("PowerSaveDataNumber"), NotchValue.PowerSaveDataNumber );
        inimoni::inirw( r,f,s, _T("BrakeIndex       "), NotchValue.BrakeIndex );
        inimoni::inirw( r,f,s, _T("BrakeSaveDataNumber"), NotchValue.BrakeSaveDataNumber );
        inimoni::inirw( r,f,s, _T("Delay            "), NotchValue.Delay   );
        inimoni::inirw( r,f,s, _T("Interval         "), NotchValue.Interval );

        s = _T("FirstPanelValue");
        inimoni::inirw( r,f,s, _T("InputIndex       "), FirstPanelValue.InputIndex );
        inimoni::inirw( r,f,s, _T("OutputIndex      "), FirstPanelValue.OutputIndex );
        inimoni::inirw( r,f,s, _T("SaveDataNumber   "), FirstPanelValue.SaveDataNumber );
        inimoni::inirw( r,f,s, _T("Delay            "), FirstPanelValue.Delay );
        inimoni::inirw( r,f,s, _T("Interval         "), FirstPanelValue.Interval );

        s = _T("SecondPanelValue");
        inimoni::inirw( r,f,s, _T("InputIndex       "), SecondPanelValue.InputIndex );
        inimoni::inirw( r,f,s, _T("OutputIndex      "), SecondPanelValue.OutputIndex );
        inimoni::inirw( r,f,s, _T("SaveDataNumber   "), SecondPanelValue.SaveDataNumber );
        inimoni::inirw( r,f,s, _T("Delay            "), SecondPanelValue.Delay );
        inimoni::inirw( r,f,s, _T("Interval         "), SecondPanelValue.Interval );
        return true;                                                    
    }                                                                   

    void init()                                                         
    {                                                                   
        NotchValue.PowerIndex        = 999;
        NotchValue.PowerSaveDataNumber = 6;
        NotchValue.BrakeIndex        = 999;
        NotchValue.BrakeSaveDataNumber = 9;
        NotchValue.Delay             = 750;
        NotchValue.Interval          = 150;
        FirstPanelValue.InputIndex   = 999;
        FirstPanelValue.OutputIndex  = 999;
        FirstPanelValue.SaveDataNumber = 4;
        FirstPanelValue.Delay        = 750;
        FirstPanelValue.Interval     = 150;
        SecondPanelValue.InputIndex  = 999;
        SecondPanelValue.OutputIndex = 999;
        SecondPanelValue.SaveDataNumber = 4;
        SecondPanelValue.Delay       = 750;
        SecondPanelValue.Interval    = 150;
    }                                                                   
};
typedef DigitalNotchIni DigitalNotchFile; //�V���݊�

//---------------------------------------------------------------------------
// Common method                                                             
//---------------------------------------------------------------------------
#ifndef INIMONI_INIRW                                                        
#define INIMONI_INIRW                                                        
namespace inimoni                                                            
{                                                                            
    /*                                                                       
    Read and Write INI file                                                  
      int     is_read  1=Read mode, 0=Write mode                             
      string  fname    Filename (The Windows folder when there is not path)  
      string  sec      Section name                                          
      string  key      Key name                                              
      T       val_t    [Read]Init+Output, [Write]Input                       
    */                                                                       
    template<class T>                                                        
    bool inirw(int is_read, string_t& fname, string_t sec, string_t key, T& val_t)
	{                                                                        
		if(is_read){                                                         
            inimoni::read(fname.c_str(), sec.c_str(), key.c_str(), val_t);   
        }                                                                    
        else{                                                                
			inimoni::write(fname.c_str(), sec.c_str(), key.c_str(), val_t);  
        }                                                                    
		return true;                                                         
    }                                                                        
                                                                             
    bool read(string_t ifn, string_t sec, string_t key, int& dst)            
    {                                                                        
        dst = GetPrivateProfileInt( sec.c_str(), key.c_str(), dst, ifn.c_str() );
        return true;                                                         
    }                                                                        
                                                                             
    bool read(string_t ifn, string_t sec, string_t key, basic_string<TCHAR>& dst)
    {                                                                        
        TCHAR buf[256];                                                      
        GetPrivateProfileString(                                             
            sec.c_str(),                                                     
            key.c_str(),                                                     
            dst.c_str(),                                                     
            buf,                                                             
            sizeof(buf),                                                     
            ifn.c_str() );                                                   
        dst = buf;                                                           
        return true;                                                         
    }                                                                        
                                                                             
    bool read(string_t ifn, string_t sec, string_t key, double& dst)         
    {                                                                        
        string_t s;                                                          
        inimoni::read(ifn, sec, key, s);                                     
                                                                             
        TCHAR* e;                                                            
        double x = _tcstod(s.c_str(), &e);                                   
                                                                             
        dst = 0.0;                                                           
        if (!*e) {                                                           
            dst = x;                                                         
        }                                                                    
        return true;                                                         
    }                                                                        
                                                                             
    template<class T>                                                        
    bool write(string_t ifn, string_t sec, string_t key, T val_t)            
    {                                                                        
        TCHAR val[1024];                                                     
        inimoni::to_string(val, val_t);                                      
        WritePrivateProfileString( sec.c_str(), key.c_str(), val, ifn.c_str() );
		return true;                                                    
	}                                                                   
                                                                        
    void to_string(TCHAR* str, int val)                                 
    {                                                                   
        _stprintf( str, _T("%d"), val );                                
    }                                                                   
                                                                        
    void to_string(TCHAR* str, double val)                              
    {                                                                   
        _stprintf( str, _T("%f"), val );                                
    }                                                                   
                                                                        
    void to_string(TCHAR* str, basic_string<TCHAR> val)                 
    {                                                                   
        _stprintf( str, _T("%s"), val.c_str() );                        
    }                                                                   
};                                                                      
                                                                        
#endif                                                                  
#endif                                                                  

