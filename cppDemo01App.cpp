/***************************************************************
 * Name:      cppDemo01App.cpp
 * Purpose:   Code for Application Class
 * Author:    Mr. Arch Brooks (arch@archbrooks.com)
 * Created:   2024-08-19
 * Copyright: Mr. Arch Brooks (https://archman.us)
 * License:
 **************************************************************/

#include "cppDemo01App.h"

//(*AppHeaders
#include "cppDemo01Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(cppDemo01App);

bool cppDemo01App::OnInit()
{
    //(*AppInitialize
    bool wxsOK = true;
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	cppDemo01Frame* Frame = new cppDemo01Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}
