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
#include <mysql++.h>
#include <wx/wx.h>
#include <ctime>

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
const long cppDemo01Frame::idMenuCP = wxNewId();
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
    menClone1 = new wxMenuItem(Menu1, idMenuCP, _("Clone Project"), _("Clone A Project"), wxITEM_NORMAL);
    Menu1->Append(menClone1);
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
    Connect(idMenuCP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cppDemo01Frame::OnmenClone1Selected);
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

wxString GetCurrentDateTime()
{
    wxDateTime now = wxDateTime::Now();
    return now.FormatISOCombined(' ');
}

wxString cppDemo01Frame::formatTime()
{
    wxString dateTime = GetCurrentDateTime();
    return dateTime;
}

void cppDemo01Frame::strArrToTextFile(wxString fileName)
{
//    fileName = "/home/archman/workspace/cb/cpp/cppDemo01/bin/Debug/output.cbp";
    wxTextFile file(fileName);
    if (!file.Exists())
    {
        file.Create();
    }
    else
    {
        file.Open();
    }

    file.Clear(); // Clear existing content
    for (const auto& line : srcFile)
    {
        file.AddLine(line);
    }

    file.Write();
    file.Close();
}

void cppDemo01Frame::txtToStrArray()
{
    srcFile.clear();
    tfile.Open(file);
    srcFile.Add(tfile.GetFirstLine());
    while (!tfile.Eof())
    {
        srcFile.Add(tfile.GetNextLine());
    }
    tfile.Close();
}

void cppDemo01Frame::upDateTxtFile()
{
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
     */    std::string cmd;
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

void cppDemo01Frame::prodProjFile()
{
    /*
     * Functionality:
     * 1. Calls SelFile() to select a file.
     * 2. Checks if a file was successfully selected.
     * 3. Converts text to a string array using txtToStrArray().
     * 4. Creates a new `changeStrings` record with the values "frs" and "New Record".
     * 5. Appends the new record to the `cs` vector.
     * 6. Updates the first record in the `cs` vector, setting `fro` to "YourProjectName" and `too` to "YoProjName".
     * 7. Updates the text file using upDateTxtFile().
     * 8. Writes the string array back to the text file with strArrToTextFile().
     */
    SelFile();
    if (file > "")
    {
        txtToStrArray();
//       changeStrings newRecord = {"cppDemo01", "cppDemo02"};
        changeStrings newRecord = {"cppDemo01", "cppMySkel1"};
        cs.push_back(newRecord);
        upDateTxtFile();
        strArrToTextFile("");
    }
}

void cppDemo01Frame::mariaBase()
{
    const char* db = "bcswebtools";
    const char* server = "localhost";
    const char* user = "bcs";
    const char* password = "YoPassword";

    try
    {
        mysqlpp::Connection conn(db, server, user, password);

        if (conn.connected())
        {
            std::cout << "Database connection successful!" << std::endl;
        }
        else
        {
            std::cout << "Database connection failed!" << std::endl;
        }
    }
    catch (const mysqlpp::Exception& ex)
    {
        std::cerr << "MySQL++ error: " << ex.what() << std::endl;
    }
}

void cppDemo01Frame::OnvarMenuLCBSelected(wxCommandEvent& event)
{
    // mariaBase();

    prodProjFile();
}

wxString cppDemo01Frame::GetFamID()
{
    wxTextEntryDialog dialog(this, "Select Family Id Now:", "Get Family ID");
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString text = dialog.GetValue();
        return text;
    }
}

bool dirExists(const std::string& dirPath)
{
    return boost::filesystem::exists(dirPath) && boost::filesystem::is_directory(dirPath);
}

bool ForceDirectories(const std::string& path)
{
    size_t pos = 0;
    do
    {
        pos = path.find_first_of("/\\", pos + 1);
        std::string subdir = path.substr(0, pos);
        if (mkdir(subdir.c_str(), 0755) && errno != EEXIST)
        {
            return false;
        }
    }
    while (pos != std::string::npos);
    return true;
}

std::string formatTime(time_t t)
{
    char buffer[100];
    std::tm* tm_info = std::localtime(&t);
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", tm_info);
    return std::string(buffer);
}

void cppDemo01Frame::FmtDateTime()
{
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::strftime(buffer, sizeof(buffer), "%A, %d %B %Y %H:%M:%S", localTime);
}

void cppDemo01Frame::OnmenClone1Selected(wxCommandEvent& event)
{
    famID = GetFamID();
    rPath = "/home/archman/workspace/cb/cpp/" + famID;
    if (!dirExists(rPath.ToStdString()))
    {
        boost::filesystem::create_directory(rPath.ToStdString());

        std::string cmd;
        cmd = rPath.ToStdString() + "/bin/Debug";
        ForceDirectories(cmd);
        cmd = rPath.ToStdString() + "/bin/Release";
        ForceDirectories(cmd);

        file = inPath + "cppMySkel1.cbp";
        txtToStrArray();
        changeStrings newRecord = {"cppMySkel1", famID.ToStdString()};
        cs.push_back(newRecord);
        FmtDateTime();
        changeStrings newRecord2 = {"2024-08-24", buffer};
        cs.push_back(newRecord2);
        upDateTxtFile();
        strArrToTextFile(rPath + "/" + famID + ".cbp");

        file = inPath + "cppMySkel1App.cpp";
        txtToStrArray();
        FmtDateTime();
        cs[1].too = buffer;
        upDateTxtFile();
        strArrToTextFile(rPath  + "/" + famID +  "App.cpp");


        file = inPath + "cppMySkel1App.h";
        txtToStrArray();
        FmtDateTime();
        cs[1].too = buffer;
        upDateTxtFile();
        strArrToTextFile(rPath + "/" + famID + "App.h");

        file = inPath + "cppMySkel1Main.cpp";
        txtToStrArray();
        FmtDateTime();
        cs[1].too = buffer;
        upDateTxtFile();
        strArrToTextFile(rPath + "/" +  famID + "Main.cpp");

        file = inPath + "cppMySkel1Main.h";
        txtToStrArray();
        FmtDateTime();
        cs[1].too = buffer;
        upDateTxtFile();
        strArrToTextFile(rPath  + "/" +  famID + "Main.h");

        if (!dirExists(rPath.ToStdString() + "wxsmith"))
        {
            boost::filesystem::create_directory(rPath.ToStdString() + "/wxsmith");
            file = inPath + "/wxsmith/" + "cppMySkel1frame.wxs";
            txtToStrArray();
            FmtDateTime();
            cs[1].too = buffer;
            upDateTxtFile();
            strArrToTextFile(rPath + "/wxsmith/" + famID + "frame.wxs");
        }
        wxMessageBox("You have just created a new Code Blocks project " + famID + ".",
                     "BCS Code Blocks Project Generator", wxOK | wxICON_INFORMATION);
    }
    else
    {
        wxMessageBox("The project you are attempting to create alrealdy exists.",
                     "BCS Code Blocks Project Generator", wxOK | wxICON_INFORMATION);

    }
}
