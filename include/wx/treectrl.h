#ifndef _WX_TREECTRL_H_BASE_
#define _WX_TREECTRL_H_BASE_

#if defined(__WXMSW__)
#ifdef __WIN16__
#include "wx/generic/treectrl.h"
#else
#include "wx/msw/treectrl.h"
#endif
#elif defined(__WXMOTIF__)
#include "wx/generic/treectrl.h"
#elif defined(__WXGTK__)
#include "wx/generic/treectrl.h"
#elif defined(__WXQT__)
#include "wx/qt/treectrl.h"
#elif defined(__WXMAC__)
#include "wx/generic/treectrl.h"
#elif defined(__WXSTUBS__)
#include "wx/generic/treectrl.h"
#endif

#endif
    // _WX_TREECTRL_H_BASE_
