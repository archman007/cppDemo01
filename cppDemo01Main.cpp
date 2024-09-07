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
#include <wx/dir.h>
#include <wx/filename.h>

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
const long cppDemo01Frame::idMenuCP = wxNewId();
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

    Create(parent, id, _("Brooks Computng Systems, LLC CodeBlocks Project"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_FRAME_STYLE, _T("id"));
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    menClone1 = new wxMenuItem(Menu1, idMenuCP, _("Clone Project"), _("Clone A Project"), wxITEM_NORMAL);
    Menu1->Append(menClone1);
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
    Center();

    Connect(idMenuCP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cppDemo01Frame::OnmenClone1Selected);
    Connect(idMenuFCP,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cppDemo01Frame::OnvarMenuLCBSelected);
    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cppDemo01Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&cppDemo01Frame::OnAbout);
    //*)
}

/**
 * Destructor for the cppDemo01Frame class.
 *
 * This destructor is responsible for cleaning up any resources or performing any necessary
 * cleanup tasks when an instance of cppDemo01Frame is destroyed.
 *
 * Note: The destructor currently does not perform any specific actions as the implementation
 *       is commented out.
 */
cppDemo01Frame::~cppDemo01Frame()
{
    //(*Destroy(cppDemo01Frame)
    //*)
}

/**
 * @brief Handles the "Quit" command event.
 *
 * This method is triggered when a "Quit" command event occurs. It closes the current
 * window or application by calling the `Close` method.
 *
 * @param event The event object containing information about the command event.
 */
void cppDemo01Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

/**
 * @brief Event handler for the "About" command in the cppDemo01Frame class.
 *
 * This method is invoked when the "About" menu item or button is clicked.
 * It displays a message box with build information about the application.
 *
 * @param event The wxCommandEvent object containing event information.
 */
void cppDemo01Frame::OnAbout(wxCommandEvent& event)
{
    wxString msg = wxbuildinfo(long_f);
    wxMessageBox(msg, _("Welcome to..."));
}

/**
 * @brief Retrieves the current date and time in ISO 8601 format.
 *
 * This function captures the current date and time using wxDateTime::Now()
 * and formats it as an ISO 8601 combined string with a space as the separator
 * between the date and time.
 *
 * @return wxString containing the formatted current date and time.
 */
wxString GetCurrentDateTime()
{
    wxDateTime now = wxDateTime::Now();
    return now.FormatISOCombined(' ');
}

/**
 * @brief Formats and returns the current date and time as a wxString.
 *
 * This function retrieves the current date and time using GetCurrentDateTime()
 * and returns it as a formatted wxString.
 *
 * @return wxString The current date and time.
 */

wxString cppDemo01Frame::formatTime()
{
    wxString dateTime = GetCurrentDateTime();
    return dateTime;
}

/**
 * @brief Writes the contents of the `srcFile` string array to a text file.
 *
 * This function takes a file path as an argument, checks if the file exists,
 * and either creates a new file or opens the existing one. It then clears
 * the current contents of the file and writes the contents of the `srcFile`
 * array, line by line, to the file. Finally, the function writes the changes
 * to the file and closes it.
 *
 * @param fileName The path to the file to be written to.
 */
void cppDemo01Frame::strArrToTextFile(wxString fileName)
{
    // fileName = "/home/archman/workspace/cb/cpp/cppDemo01/bin/Debug/output.cbp";
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

/**
 * @brief Converts the contents of a text file into a string array.
 *
 * This function reads a text file line by line and stores each line
 * as a string in the `srcFile` array. It starts by clearing the
 * `srcFile` array, opens the file, and adds the first line to the array.
 * It then continues to read and add each subsequent line until the end
 * of the file is reached. Finally, the file is closed.
 *
 * @note The `tfile` is expected to be an object that handles file
 * operations, and `srcFile` is a container for storing the lines of the file.
 */
void cppDemo01Frame::txtToStrArray()
{
    srcFile.clear();      // Clear the current content of the srcFile array
    tfile.Open(file);     // Open the text file for reading
    srcFile.Add(tfile.GetFirstLine());  // Add the first line of the file to srcFile
    while (!tfile.Eof())  // Continue until the end of the file is reached
    {
        srcFile.Add(tfile.GetNextLine());  // Add each subsequent line to srcFile
    }
    tfile.Close();        // Close the file
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

/**
 * @brief Opens a file dialog to select a text file.
 *
 * This function creates a wxFileDialog for selecting a text file within a specified directory.
 * If the user selects a file and clicks OK, the file path is returned.
 *
 * @return wxString The file path of the selected file.
 */
wxString cppDemo01Frame::SelFile()
{
    wxFileDialog fdlog(
        this,                                 // Parent window
        "Please Select The Desired Text File Now!",  // Dialog title
        "/home/archman/workspace/cb/cpp",     // Default directory
        "",                                   // Default file
        "*.cbp"                               // File filter (only .cbp files)
    );

    if (fdlog.ShowModal() == wxID_OK)
    {
        file = fdlog.GetPath();  // Get the selected file path
        return file;             // Return the file path
    }

    return "";  // Return an empty string if no file was selected
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

/**
 * @brief Establishes a connection to a MariaDB database using MySQL++.
 *
 * This function attempts to connect to the specified MariaDB database using the provided
 * credentials (database name, server, username, and password). Upon successful connection,
 * it outputs a success message. If the connection fails, it outputs a failure message.
 * Any exceptions thrown by MySQL++ during the connection attempt are caught and logged.
 *
 * @note Database details:
 *  - Database: bcswebtools
 *  - Server: localhost
 *  - User: bcs
 *  - Password: YoPassword
 *
 * @throws mysqlpp::Exception if there is an issue with the database connection.
 */

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

// This method is an event handler that gets triggered when an item is selected from a menu with an ID corresponding to varMenuLCB.
// The method first appears to be calling a commented-out function, `mariaBase()`, and then calls the `prodProjFile()` method.
// wxCommandEvent& event: Reference to the event object associated with the menu selection.
void cppDemo01Frame::OnvarMenuLCBSelected(wxCommandEvent& event)
{
    // Uncomment this function call if `mariaBase()` needs to be executed upon selection.
    // mariaBase();

    // Process the project file after the menu selection.
    prodProjFile();
}

// Function: GetFamID
// Class: cppDemo01Frame
// Description: Displays a modal dialog prompting the user to input a Family ID.
// If the user confirms their input, the function returns the entered Family ID as a wxString.
// If the dialog is canceled, the function returns an empty wxString.
//
// Returns:
// - wxString: The user-provided Family ID or an empty string if the dialog is canceled.
wxString cppDemo01Frame::GetFamID()
{
    wxTextEntryDialog dialog(this, "Select Family Id Now:", "Get Family ID");
    if (dialog.ShowModal() == wxID_OK)
    {
        wxString text = dialog.GetValue();
        return text;
    }
    return wxEmptyString;  // Return empty string if the dialog is canceled
}

/**
 * @brief Checks if a directory exists at the specified path.
 *
 * This function determines whether the given directory path exists
 * and whether it is a directory.
 *
 * @param dirPath The path of the directory to check.
 * @return true if the directory exists and is a directory, false otherwise.
 */
bool dirExists(const std::string& dirPath)
{
    return boost::filesystem::exists(dirPath) && boost::filesystem::is_directory(dirPath);
}

/**
 * Creates the directory structure specified by the given path.
 *
 * This function ensures that all directories in the specified path are created.
 * It iterates through each segment of the path, creating directories as needed.
 *
 * @param path The directory path to create. This can be a nested path with multiple directories.
 * @return Returns true if all directories were successfully created or already exist.
 *         Returns false if any directory could not be created and errno is not EEXIST.
 *
 * Note: This function assumes that the path is a valid directory path and that
 *       the mkdir function call is available.
 */
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

/**
 * @brief Formats a given time_t value into a human-readable string.
 *
 * @param t The time_t value to be formatted.
 * @return A string representing the formatted time in the format "Weekday, Month Day, Year".
 *
 * This function converts a `time_t` value to a local time representation and formats it into a string
 * with the format "Weekday, Month Day, Year" (e.g., "Sunday, September 02, 2024").
 *
 * @note The buffer size is set to 100, which should be sufficient for the specified format.
 */
std::string formatTime(time_t t)
{
    char buffer[100];
    std::tm* tm_info = std::localtime(&t);
    strftime(buffer, sizeof(buffer), "%A, %B %d, %Y", tm_info);
    return std::string(buffer);
}

/**
 * Formats the current local date and time into a human-readable string.
 * The resulting string is stored in the `buffer` member variable of the `cppDemo01Frame` class.
 *
 * The format of the date and time is:
 * "DayOfWeek, Day Month Year Hour:Minute:Second"
 * e.g., "Sunday, 01 September 2024 15:30:00"
 *
 * This function uses the C++ standard library's time functions to get the current local time
 * and formats it using the strftime function.
 *
 * @note The buffer used for formatting must be large enough to hold the resulting string.
 */
void cppDemo01Frame::FmtDateTime()
{
    std::time_t now = std::time(nullptr);
    std::tm* localTime = std::localtime(&now);
    std::strftime(buffer, sizeof(buffer), "%A, %d %B %Y %H:%M:%S", localTime);
}
/**
 * Handles the event triggered when the menu item for cloning a project is selected.
 *
 * This method performs the following steps:
 * 1. Sets `contProcess` to false and retrieves the family ID using `GetFamID()`.
 * 2. Constructs a path `rPath` based on the retrieved family ID and checks if the directory exists.
 * 3. If the directory does not exist:
 *    - Creates the directory and its subdirectories (`bin/Debug` and `bin/Release`).
 *    - Prompts the user with a dialog asking if they want to change the project destination.
 *    - If the user chooses to change the destination, opens a directory dialog for user selection.
 *    - Updates the project files with the new location and date/time information.
 *    - Creates a new Code::Blocks project by copying and modifying template files.
 *    - If the `wxsmith` directory does not exist, creates it and copies a template file.
 * 4. If the directory already exists, notifies the user that the project already exists.
 *
 * @param event The wxCommandEvent that triggered this handler.
 */
void cppDemo01Frame::OnmenClone1Selected(wxCommandEvent& event)
{
    // Flag to continue processing
    contProcess = false;
    // Retrieve family ID and set project path
    famID = GetFamID();
    rPath = "/home/archman/workspace/cb/cpp/" + famID;

    // Check if project directory exists
    if (!dirExists(rPath.ToStdString()))
    {
        contProcess = true;
        // Create project directories
        boost::filesystem::create_directory(rPath.ToStdString());
        ForceDirectories(rPath.ToStdString() + "/bin/Debug");
        ForceDirectories(rPath.ToStdString() + "/bin/Release");

        // Ask user to change project destination
        int result = wxMessageBox("Would You Like To Change Project Destination?", "New Destination Confirmation", wxYES_NO | wxICON_QUESTION);
        if (result == wxYES)
        {
            wxDirDialog dirDlg(this, "Select a directory", "/home/archman/", wxDD_DEFAULT_STYLE);
            if (dirDlg.ShowModal() == wxID_OK)
            {
                rPath = dirDlg.GetPath();
            }
        }

        // Proceed with file operations
        if (contProcess)
        {
            // Process and update project files
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

            // Create wxsmith directory and process its file
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

            // Notify user of successful project creation
            wxMessageBox("You have just created a new Code Blocks project " + famID + ".",
                         "BCS Code Blocks Project Generator", wxOK | wxICON_INFORMATION);
        }
    }
    else
    {
        // Notify user that the project already exists
        wxMessageBox("The project you are attempting to create already exists.",
                     "BCS Code Blocks Project Generator", wxOK | wxICON_INFORMATION);
    }
}
/**
 * @brief Recursively traverses a directory and collects all files with a specified extension.
 *
 * This function opens the given directory and iterates through its contents. If a subdirectory
 * is encountered, the function recursively traverses that subdirectory. Files with the specified
 * extension are added to the result vector.
 *
 * @param directory The starting directory to traverse.
 * @param extension The file extension to filter by (e.g., ".txt").
 * @param result A vector to store the paths of the files that match the specified extension.
 */
 void TraverseDirectory(const wxString& directory, const wxString& extension, std::vector<wxString>& result)
{
    wxDir dir(directory);
    if (!dir.IsOpened())
    {
        return;
    }

    wxString filename;
    bool cont = dir.GetFirst(&filename);
    while (cont)
    {
        wxString filepath = directory + wxFileName::GetPathSeparator() + filename;
        if (wxDirExists(filepath))
        {
            TraverseDirectory(filepath, extension, result);
        }
        else if (filepath.EndsWith(extension))
        {
            result.push_back(filepath);
        }
        cont = dir.GetNext(&filename);
    }
}

/**
 * @brief Traverse a directory to find files with a specific extension.
 *
 * This function traverses a given directory and searches for files with the specified extension.
 * The matching files are collected in a vector and printed out.
 *
 * @note This example uses the wxWidgets library.
 *
 * @param None
 * @return void
 */
void TravDir()
{
    // Vector to store the result of matching files
    std::vector<wxString> result;

    // Directory to search
    wxString directory = "/home/archman/workspace";

    // File extension to search for
    wxString extension = ".cbl";

    // Traverse the directory and populate the result vector with matching files
    TraverseDirectory(directory, extension, result);

    // Print the results
    for (const auto& file : result)
    {
        wxPuts(file);  // Print each file path to the console
    }
}
