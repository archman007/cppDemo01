/***************************************************************
 * Name:      cppDemo01Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2024-08-19
 * Copyright: Mr. Arch Brooks (https://archman.us)
 * License:
 **************************************************************/

#include "cppDemo01Main.h"
#include <wx/msgdlg.h>
#include <wx/textfile.h>
#include <wx/filedlg.h>
#include <boost/filesystem.hpp>
#include <boost/algorithm/string.hpp>


//(*InternalHeaders(cppDemo01Frame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat
{
    short_f, long_f
};

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(cppDemo01Frame)
const long cppDemo01Frame::idMenuFCP = wxNewId();
const long cppDemo01Frame::idMenuQuit = wxNewId();
const long cppDemo01Frame::idMenuAbout = wxNewId();
const long cppDemo01Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(cppDemo01Frame,wxFrame)
    //(*EventTable(cppDemo01Frame)
    //*)
END_EVENT_TABLE()

cppDemo01Frame::cppDemo01Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(cppDemo01Frame)
    wxMenu* Menu1;
    wxMenu* Menu2;
    wxMenuBar* MenuBar1;
    wxMenuItem* MenuItem1;
    wxMenuItem* MenuItem2;

    Create(parent, id, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    varMenuLCB = new wxMenuItem(Menu1, idMenuFCP, _("Copy File To Clipboard"), _("Load File To Clipboard"), wxITEM_NORMAL);
    Menu1->Append(varMenuLCB);
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("Quit\tAlt-F4"), _("Quit the application"), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("About\tF1"), _("Show info about this application"), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);

    Connect(idMenuFCP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cppDemo01Frame::OnvarMenuLCBSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cppDemo01Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cppDemo01Frame::OnAbout);
    //*)
}

cppDemo01Frame::~cppDemo01Frame()
{
    //(*Destroy(cppDemo01Frame)
    //*)
}

void cppDemo01Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void cppDemo01Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

void cppDemo01Frame::strArrToTextFile()
{
//    fileName = "/home/archman/workspace/cb/cpp/cppDemo01/bin/Debug/output.cbp";
    fileName = "/home/archman/workspace/cb/cpp/myCrud/bin/Debug/output.cbp";
    tfile.Open(fileName);
    // Clear the file content if it already exists
    tfile.Clear();
    for (int ii = 0; ii < srcFile.Count(); ii++)
    {
        tfile.AddLine(srcFile[ii].ToStdString());
    }
    tfile.Write();
    tfile.Close();
}

void cppDemo01Frame::txtToStrArray()
{
    srcFile.clear();
    tfile.Open(file);
    str = tfile.GetFirstLine();
    srcFile.Add(str);
    while(!tfile.Eof())
    {
        str = tfile.GetNextLine();
        srcFile.Add(str);
    }
    tfile.Close();
}

void cppDemo01Frame::upDateTxtFile()
{
    std::string cmd;
    boost::replace_all(cmd, "/archman/", "/archbrooks/");

}

void cppDemo01Frame::OnvarMenuLCBSelected(wxCommandEvent& event)
{
    wxFileDialog    fdlog(this, "Please Select The Desired Text File Now!","/home/archman/workspace/cb/cpp", "", "*.cbp");
    if (fdlog.ShowModal() == wxID_OK)
    {
        file = fdlog.GetPath();
        /* if (boost::filesystem::exists(file.ToStdString()) == true)
        {
            file.Clear();
        }
        */
        txtToStrArray();
        cs[0].fro = "YourProjectName";
        cs[0].too = "YoProjName";
        upDateTxtFile();
        strArrToTextFile();
    }
    fdlog.Destroy();
}
