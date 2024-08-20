/***************************************************************
 * Name:      cppDemo01Main.h
 * Purpose:   Defines Application Frame
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2024-08-19
 * Copyright: Mr. Arch Brooks (https://archman.us)
 * License:
 **************************************************************/

#ifndef CPPDEMO01MAIN_H
#define CPPDEMO01MAIN_H
#include <wx/arrstr.h>
#include <wx/textfile.h>

//(*Headers(cppDemo01Frame)
#include <wx/frame.h>
#include <wx/menu.h>
#include <wx/statusbr.h>
//*)

struct changeStrings
{
    std::string fro;
    std::string too;
};

class cppDemo01Frame: public wxFrame
{
public:

    cppDemo01Frame(wxWindow* parent,wxWindowID id = -1);
    virtual ~cppDemo01Frame();
    wxArrayString srcFile;
    wxString        file;
    wxString        fileName;
    wxTextFile      tfile;
    void strArrToTextFile();
    wxString        str;
    void txtToStrArray();
    void upDateTxtFile();

    std::vector<changeStrings> cs;

private:

    //(*Handlers(cppDemo01Frame)
    void OnQuit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);
    void OnvarMenuLCBSelected(wxCommandEvent& event);
    //*)

    //(*Identifiers(cppDemo01Frame)
    static const long idMenuFCP;
    static const long idMenuQuit;
    static const long idMenuAbout;
    static const long ID_STATUSBAR1;
    //*)

    //(*Declarations(cppDemo01Frame)
    wxMenuItem* varMenuLCB;
    wxStatusBar* StatusBar1;
    //*)

    DECLARE_EVENT_TABLE()
};

#endif // CPPDEMO01MAIN_H
