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
    fileName = "/home/archman/workspace/cb/cpp/myCrud/bin/Debug/output.cbp";
    srcFile.clear();
    tfile.Open(fileName);
    while (!tfile.Eof())
    {
        srcFile.Add(tfile.GetNextLine());
    }
    tfile.Write();
    tfile.Close();
}

void cppDemo01Frame::txtToStrArray()
{
    /* srcFile.clear();
    tfile.Open(file);
    str = tfile.GetFirstLine();
    srcFile.Add(str);
    while(!tfile.Eof())
    {
        str = tfile.GetNextLine();
        srcFile.Add(str);
    }
    tfile.Close();
    */

    srcFile.clear();
    tfile.Open(file);
    while (!tfile.Eof())
    {
        srcFile.Add(tfile.GetNextLine());
    }
    tfile.Close();
}

/**
 * @brief Updates a text file by applying a series of string replacements.
 *
 * This function iterates over each line of the source file `srcFile` and performs
 * string replacements based on a collection of replacement pairs `cs`. Each line
 * in `srcFile` is modified by replacing occurrences of a specified substring (`fro`)
 * with another substring (`too`). The modified lines are stored back in `cmd` for
 * further processing.
 *
 * @note This function assumes that `srcFile` is a collection of strings (e.g., a vector),
 * and `cs` is a collection of structs or classes containing `fro` and `too` strings.
 * The `boost::replace_all` function from the Boost library is used to perform the replacements.
 *
 * Example usage:
 * ```
 * struct ChangeString {
 *     std::string fro;
 *     std::string too;
 * };
 *
 * cppDemo01Frame::upDateTxtFile();
 * ```
 */
void cppDemo01Frame::upDateTxtFile()
{
    std::string cmd;
    for (auto& line : srcFile)
    {
        int ii = 0;
        for (const auto& changeStrings : cs)
        {
            std::string cmd;
            cmd = line;
            boost::replace_all(cmd, cs[ii].fro, cs[ii].too);
            line = cmd;
            ii++;
        }
    }
}

/**
 * @brief Joins all strings from a `wxArrayString` into a single `wxString`.
 *
 * This function iterates through all elements of the given `wxArrayString`
 * and concatenates them into a single `wxString`.
 *
 * @param arr The `wxArrayString` containing strings to be joined.
 * @return A `wxString` representing the concatenation of all elements
 *         in the input array.
 */
wxString JoinWxArrayString(const wxArrayString& arr)
{
    wxString result;
    for (const auto& str : arr)
    {
        result += str;
    }
    return result;
}

wxString cppDemo01Frame::SelFile()
{
    wxFileDialog fdlog(this, "Please Select The Desired Text File Now!","/home/archman/workspace/cb/cpp", "", "*.cbp");
    if (fdlog.ShowModal() == wxID_OK)
    {
        file = fdlog.GetPath();
        return file;
    }

}

void cppDemo01Frame::OnvarMenuLCBSelected(wxCommandEvent& event)
{
    SelFile();
//    wxFileDialog fdlog(this, "Please Select The Desired Text File Now!","/home/archman/workspace/cb/cpp", "", "*.cbp");
    if (file > "")
    {
        //file = fdlog.GetPath();
        /* if (boost::filesystem::exists(file.ToStdString()) == true)
        {
            file.Clear();
        }
        */
        txtToStrArray();
//         Record newRecord = {1, "New Record"};
        changeStrings newRecord = {"frs", "New Record"};
        cs.push_back(newRecord);
        cs[0].fro = "YourProjectName";
        cs[0].too = "YoProjName";
        upDateTxtFile();
        strArrToTextFile();
    }
//    fdlog.Destroy();
}
