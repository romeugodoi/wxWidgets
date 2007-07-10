/////////////////////////////////////////////////////////////////////////////
// Name:        src/common/odcombocmn.cpp
// Purpose:     wxOwnerDrawnComboBox common code
// Author:      Jaakko Salli
// Modified by:
// Created:     Apr-30-2006
// RCS-ID:      $Id: odcombo.cpp 45397 2007-04-11 10:32:01Z MBN $
// Copyright:   (c) 2005 Jaakko Salli
// Licence:     wxWindows licence
/////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#if wxUSE_ODCOMBOBOX

#include "wx/odcombo.h"

#ifndef WX_PRECOMP
    #include "wx/log.h"
    #include "wx/combobox.h"
    #include "wx/dcclient.h"
    #include "wx/settings.h"
    #include "wx/dialog.h"
#endif

#include "wx/combo.h"

// ----------------------------------------------------------------------------
// XTI
// ----------------------------------------------------------------------------

#if wxUSE_EXTENDED_RTTI
IMPLEMENT_DYNAMIC_CLASS2_XTI(wxOwnerDrawnComboBox, wxComboCtrl, \
                             wxControlWithItems, "wx/odcombo.h")

wxBEGIN_PROPERTIES_TABLE(wxOwnerDrawnComboBox)
wxEND_PROPERTIES_TABLE()

wxBEGIN_HANDLERS_TABLE(wxOwnerDrawnComboBox)
wxEND_HANDLERS_TABLE()

wxCONSTRUCTOR_5( wxOwnerDrawnComboBox , wxWindow* , Parent , wxWindowID , \
                 Id , wxString , Value , wxPoint , Position , wxSize , Size )
#else
IMPLEMENT_DYNAMIC_CLASS2(wxOwnerDrawnComboBox, wxComboCtrl, wxControlWithItems)
#endif

#endif // wxUSE_ODCOMBOBOX
