///////////////////////////////////////////////////////////////////////////////
// Name:        src/msw/dib.cpp
// Purpose:     implements wxDIB class
// Author:      Vadim Zeitlin
// Modified by:
// Created:     03.03.03 (replaces the old file with the same name)
// RCS-ID:      $Id$
// Copyright:   (c) 2003 Vadim Zeitlin <vadim@wxwindows.org>
// License:     wxWindows licence
///////////////////////////////////////////////////////////////////////////////

// ============================================================================
// declarations
// ============================================================================

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

// For compilers that support precompilation, includes "wx.h".
#include "wx/wxprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#ifndef WX_PRECOMP
    #include "wx/string.h"
    #include "wx/log.h"
#endif //WX_PRECOMP

#include "wx/bitmap.h"
#include "wx/intl.h"

#include <stdio.h>
#include <stdlib.h>

#if !defined(__MWERKS__) && !defined(__SALFORDC__)
#include <memory.h>
#endif

#ifdef __GNUWIN32_OLD__
    #include "wx/msw/gnuwin32/extra.h"
#endif

#include "wx/image.h"
#include "wx/msw/dib.h"

// ----------------------------------------------------------------------------
// private functions
// ----------------------------------------------------------------------------

// calculate the number of palette entries needed for the bitmap with this
// number of bits per pixel
static WORD wxGetNumOfBitmapColors(WORD bitsPerPixel)
{
    // only 1, 4 and 8bpp bitmaps use palettes (well, they could be used with
    // 24bpp ones too but we don't support this as I think it's quite uncommon)
    return bitsPerPixel <= 8 ? 1 << bitsPerPixel : 0;
}

// ============================================================================
// implementation
// ============================================================================

// ----------------------------------------------------------------------------
// wxDIB creation
// ----------------------------------------------------------------------------

bool wxDIB::Create(int width, int height, int depth)
{
    // we don't handle the palette yet
    wxASSERT_MSG( depth == 24 || depth == 32,
                    _T("unsupported image depth in wxDIB::Create()") );

    static const int infosize = sizeof(BITMAPINFOHEADER);

    BITMAPINFO *info = (BITMAPINFO *)malloc(infosize);
    wxCHECK_MSG( info, NULL, _T("malloc(BITMAPINFO) failed") );

    memset(info, 0, infosize);

    info->bmiHeader.biSize = infosize;
    info->bmiHeader.biWidth = width;

    // we use positive height here which corresponds to a DIB with normal, i.e.
    // bottom to top, order -- normally using negative height (which means
    // reversed for MS and hence natural for all the normal people top to
    // bottom line scan order) could be used to avoid the need for the image
    // reversal in Create(image) but this doesn't work under NT, only Win9x!
    info->bmiHeader.biHeight = height;

    info->bmiHeader.biPlanes = 1;
    info->bmiHeader.biBitCount = depth;
    info->bmiHeader.biSizeImage = GetLineSize(width, depth)*height;

    m_handle = ::CreateDIBSection
                 (
                    0,              // hdc (unused with DIB_RGB_COLORS)
                    info,           // bitmap description
                    DIB_RGB_COLORS, // use RGB, not palette
                    &m_data,        // [out] DIB bits
                    NULL,           // don't use file mapping
                    0               // file mapping offset (not used here)
                 );

    free(info);

    if ( !m_handle )
    {
        wxLogLastError(wxT("CreateDIBSection"));

        return false;
    }

    m_width = width;
    m_height = height;
    m_depth = depth;

    return true;
}

// ----------------------------------------------------------------------------
// Loading/saving the DIBs
// ----------------------------------------------------------------------------

bool wxDIB::Load(const wxString& filename)
{
    m_handle = (HBITMAP)::LoadImage
                         (
                            wxGetInstance(),
                            filename,
                            IMAGE_BITMAP,
                            0, 0, // don't specify the size
                            LR_CREATEDIBSECTION | LR_LOADFROMFILE
                         );
    if ( !m_handle )
    {
        wxLogLastError(_T("LoadImage(LR_CREATEDIBSECTION | LR_LOADFROMFILE)"));

        return false;
    }

    return true;
}

// ----------------------------------------------------------------------------
// wxDIB accessors
// ----------------------------------------------------------------------------

void wxDIB::DoGetObject() const
{
    // only do something if we have a valid DIB but we don't [yet] have valid
    // data
    if ( m_handle && !m_data )
    {
        // although all the info we need is in BITMAP and so we don't really
        // need DIBSECTION we still ask for it as modifying the bit values only
        // works for the real DIBs and not for the bitmaps and it's better to
        // check for this now rather than trying to find out why it doesn't
        // work later
        DIBSECTION ds;
        if ( !::GetObject(m_handle, sizeof(ds), &ds) )
        {
            wxLogLastError(_T("GetObject(hDIB)"));
            return;
        }

        wxDIB *self = wxConstCast(this, wxDIB);

        self->m_width = ds.dsBm.bmWidth;
        self->m_height = ds.dsBm.bmHeight;
        self->m_depth = ds.dsBm.bmBitsPixel;
        self->m_data = ds.dsBm.bmBits;
    }
}

// ----------------------------------------------------------------------------
// DDB <-> DIB conversions
// ----------------------------------------------------------------------------

HBITMAP wxDIB::CreateDDB(HDC hdc) const
{
    wxCHECK_MSG( m_handle, 0, _T("wxDIB::CreateDDB(): invalid object") );

    DIBSECTION ds;
    if ( !::GetObject(m_handle, sizeof(ds), &ds) )
    {
        wxLogLastError(_T("GetObject(hDIB)"));

        return 0;
    }

    return ConvertToBitmap((BITMAPINFO *)&ds.dsBmih, hdc, ds.dsBm.bmBits);
}

/* static */
HBITMAP wxDIB::ConvertToBitmap(const BITMAPINFO *pbmi, HDC hdc, void *bits)
{
    wxCHECK_MSG( pbmi, 0, _T("invalid DIB in ConvertToBitmap") );

    // here we get BITMAPINFO struct followed by the actual bitmap bits and
    // BITMAPINFO starts with BITMAPINFOHEADER followed by colour info
    const BITMAPINFOHEADER *pbmih = &pbmi->bmiHeader;

    // get the pointer to the start of the real image data if we have a plain
    // DIB and not a DIB section (in the latter case the pointer must be passed
    // to us by the caller)
    if ( !bits )
    {
        // we must skip over the colour table to get to the image data

        // biClrUsed has the number of colors but it may be not initialized at
        // all
        int numColors = pbmih->biClrUsed;
        if ( !numColors )
        {
            numColors = wxGetNumOfBitmapColors(pbmih->biBitCount);
        }

        bits = (char *)pbmih + sizeof(*pbmih) + numColors*sizeof(RGBQUAD);
    }

    HBITMAP hbmp = ::CreateDIBitmap
                     (
                        hdc ? hdc           // create bitmap compatible
                            : ScreenHDC(),  //  with this DC
                        pbmih,              // used to get size &c
                        CBM_INIT,           // initialize bitmap bits too
                        bits,               // ... using this data
                        pbmi,               // this is used for palette only
                        DIB_RGB_COLORS      // direct or indexed palette?
                     );

    if ( !hbmp )
    {
        wxLogLastError(wxT("CreateDIBitmap"));
    }

    return hbmp;
}

/* static */
size_t wxDIB::ConvertFromBitmap(BITMAPINFO *pbi, HBITMAP hbmp)
{
    wxASSERT_MSG( hbmp, wxT("invalid bmp can't be converted to DIB") );

    // prepare all the info we need
    BITMAP bm;
    if ( !::GetObject(hbmp, sizeof(bm), &bm) )
    {
        wxLogLastError(wxT("GetObject(bitmap)"));

        return 0;
    }

    // calculate the number of bits per pixel and the number of items in
    // bmiColors array (whose meaning depends on the bitmap format)
    WORD biBits = bm.bmPlanes * bm.bmBitsPixel;
    WORD biColors = wxGetNumOfBitmapColors(biBits);

    // we need a BITMAPINFO anyhow and if we're not given a pointer to it we
    // use this one
    BITMAPINFO bi2;

    bool wantSizeOnly = pbi == NULL;
    if ( wantSizeOnly )
        pbi = &bi2;

    // just for convenience
    const int h = bm.bmHeight;

    // init the header
    BITMAPINFOHEADER& bi = pbi->bmiHeader;
    wxZeroMemory(bi);
    bi.biSize = sizeof(BITMAPINFOHEADER);
    bi.biWidth = bm.bmWidth;
    bi.biHeight = h;
    bi.biPlanes = 1;
    bi.biBitCount = biBits;

    // memory we need for BITMAPINFO only
    DWORD dwLen = bi.biSize + biColors * sizeof(RGBQUAD);

    // first get the image size
    ScreenHDC hdc;
    if ( !::GetDIBits(hdc, hbmp, 0, h, NULL, pbi, DIB_RGB_COLORS) )
    {
        wxLogLastError(wxT("GetDIBits(NULL)"));

        return 0;
    }

    if ( !wantSizeOnly )
    {
        // and now copy the bits
        void *image = (char *)pbi + dwLen;
        if ( !::GetDIBits(hdc, hbmp, 0, h, image, pbi, DIB_RGB_COLORS) )
        {
            wxLogLastError(wxT("GetDIBits"));

            return 0;
        }
    }

    // return the total size
    return dwLen + bi.biSizeImage;
}

// ----------------------------------------------------------------------------
// palette support
// ----------------------------------------------------------------------------

#if wxUSE_PALETTE

wxPalette *wxDIB::CreatePalette() const
{
    wxCHECK_MSG( m_handle, NULL, _T("wxDIB::CreatePalette(): invalid object") );

    DIBSECTION ds;
    if ( !::GetObject(m_handle, sizeof(ds), &ds) )
    {
        wxLogLastError(_T("GetObject(hDIB)"));

        return 0;
    }

    // how many colours are we going to have in the palette?
    DWORD biClrUsed = ds.dsBmih.biClrUsed;
    if ( !biClrUsed )
    {
        // biClrUsed field might not be set
        biClrUsed = 1 << ds.dsBmih.biBitCount;
    }

    if ( biClrUsed > 256 )
    {
        // only 8bpp bitmaps (and less) have palettes, so we surely don't
        //
        // NB: another possibility would be to return
        //     GetStockObject(DEFAULT_PALETTE) or even CreateHalftonePalette()?
        return NULL;
    }

    // LOGPALETTE struct has only 1 element in palPalEntry array, we're
    // going to have biClrUsed of them so add necessary space
    LOGPALETTE *pPalette = (LOGPALETTE *)
        malloc(sizeof(LOGPALETTE) + (biClrUsed - 1)*sizeof(PALETTEENTRY));
    wxCHECK_MSG( pPalette, NULL, _T("out of memory") );

    // initialize the palette header
    pPalette->palVersion = 0x300;  // magic number, not in docs but works
    pPalette->palNumEntries = biClrUsed;

    // and the colour table (it starts right after the end of the header)
    const RGBQUAD *pRGB = (RGBQUAD *)((char *)&ds.dsBmih + ds.dsBmih.biSize);
    for ( DWORD i = 0; i < biClrUsed; i++, pRGB++ )
    {
        pPalette->palPalEntry[i].peRed = pRGB->rgbRed;
        pPalette->palPalEntry[i].peGreen = pRGB->rgbGreen;
        pPalette->palPalEntry[i].peBlue = pRGB->rgbBlue;
        pPalette->palPalEntry[i].peFlags = 0;
    }

    HPALETTE hPalette = ::CreatePalette(pPalette);

    free(pPalette);

    if ( !hPalette )
    {
        wxLogLastError(_T("CreatePalette"));

        return NULL;
    }

    wxPalette *palette = new wxPalette;
    palette->SetHPALETTE((WXHPALETTE)hPalette);

    return palette;
}

#endif // wxUSE_PALETTE

// ----------------------------------------------------------------------------
// wxImage support
// ----------------------------------------------------------------------------

#if wxUSE_IMAGE

bool wxDIB::Create(const wxImage& image)
{
    wxCHECK_MSG( image.Ok(), false, _T("invalid wxImage in wxDIB ctor") );

    const int h = image.GetHeight();
    const int w = image.GetWidth();

    // if we have alpha channel, we need to create a 32bpp RGBA DIB, otherwise
    // a 24bpp RGB is sufficient
    const bool hasAlpha = image.HasAlpha();
    const int bpp = hasAlpha ? 32 : 24;

    if ( !Create(w, h, bpp) )
        return false;

    // DIBs are stored in bottom to top order (see also the comment above in
    // Create()) so we need to copy bits line by line and starting from the end
    const int srcBytesPerLine = w * 3;
    const int dstBytesPerLine = GetLineSize(w, bpp);
    const unsigned char *src = image.GetData() + ((h - 1) * srcBytesPerLine);
    const unsigned char *alpha = hasAlpha ? image.GetAlpha() + (h - 1)*w : NULL;
    unsigned char *dstLineStart = (unsigned char *)m_data;
    for ( int y = 0; y < h; y++ )
    {
        // copy one DIB line
        unsigned char *dst = dstLineStart;
        for ( int x = 0; x < w; x++ )
        {
            // also, the order of RGB is inversed for DIBs
            *dst++ = src[2];
            *dst++ = src[1];
            *dst++ = src[0];

            src += 3;

            if ( alpha )
                *dst++ = *alpha++;
        }

        // pass to the previous line in the image
        src -= 2*srcBytesPerLine;
        if ( alpha )
            alpha -= 2*w;

        // and to the next one in the DIB
        dstLineStart += dstBytesPerLine;
    }

    return true;
}

#endif // wxUSE_IMAGE

// ============================================================================
// old DIB code, to be integrated in wxDIB class
// ============================================================================

/*
 *  Routines for dealing with Device Independent Bitmaps.
 *
 *                  wxReadDIB()           - Reads a DIB
 *                  wxWriteDIB()            - Writes a global handle in CF_DIB format
 *                                          to a file.
 *                  wxPaletteSize()       - Calculates the palette size in bytes
 *                                          of given DIB
 *                  wxDibNumColors()        - Determines the number of colors in DIB
 *                  wxDibFromBitmap()       - Creates a DIB repr. the DDB passed in.
 *                  lread()               - Private routine to read more than 64k
 *                  lwrite()              - Private routine to write more than 64k
 */

#ifndef SEEK_CUR
/* flags for _lseek */
#define        SEEK_CUR 1
#define        SEEK_END 2
#define        SEEK_SET 0
#endif

#define MAXREAD  32768                                 /* Number of bytes to be read during */
                                                 /* each read operation.                         */

/* Header signatutes for various resources */
#define BFT_ICON         0x4349         /* 'IC' */
#define BFT_BITMAP 0x4d42         /* 'BM' */
#define BFT_CURSOR 0x5450         /* 'PT(' */

/* macro to determine if resource is a DIB */
#define ISDIB(bft) ((bft) == BFT_BITMAP)

/* Macro to align given value to the closest DWORD (unsigned long ) */
#define ALIGNULONG(i)        ((i+3)/4*4)

/* Macro to determine to round off the given value to the closest byte */
#define WIDTHBYTES(i)        ((i+31)/32*4)

#define PALVERSION                0x300
#define MAXPALETTE        256          /* max. # supported palette entries */

static DWORD lread(int fh, VOID FAR *pv, DWORD ul);
static DWORD lwrite(int fh, VOID FAR *pv, DWORD ul);

static bool wxWriteDIB (LPTSTR szFile,HANDLE hdib);
WORD        wxPaletteSize (VOID FAR * pv); // This is non-static as some apps use it externally
static WORD wxDibNumColors (VOID FAR * pv);
static bool wxMakeBitmapAndPalette(HDC,HANDLE,HPALETTE *,HBITMAP *);

/*
 *  FUNCTION   : wxWriteDIB(LPSTR szFile,HANDLE hdib)
 *  PURPOSE    : Write a global handle in CF_DIB format to a file.
 *  RETURNS    : TRUE  - if successful.
 *               FALSE - otherwise
 */

static bool wxWriteDIB(LPTSTR szFile, HANDLE hdib)
{
    BITMAPFILEHEADER        hdr;
    LPBITMAPINFOHEADER  lpbi;
    int                 fh;
    OFSTRUCT            of;

    if (!hdib)
        return FALSE;

    fh = OpenFile(wxConvertWX2MB(szFile), &of, OF_CREATE | OF_READWRITE);
    if (fh == -1)
        return FALSE;

    lpbi = (LPBITMAPINFOHEADER) GlobalLock(hdib);

    /* Fill in the fields of the file header */
    hdr.bfType = BFT_BITMAP;
    hdr.bfSize = GlobalSize(hdib) + sizeof(BITMAPFILEHEADER);
    hdr.bfReserved1 = 0;
    hdr.bfReserved2 = 0;
    hdr.bfOffBits = (DWORD) sizeof(BITMAPFILEHEADER) + lpbi->biSize +
        wxPaletteSize(lpbi);

    /* Write the file header */
    _lwrite(fh, (LPSTR) &hdr, sizeof(BITMAPFILEHEADER));

    /* Write the DIB header and the bits */
    lwrite(fh, (LPSTR) lpbi, GlobalSize(hdib));

    GlobalUnlock(hdib);
    _lclose(fh);
    return TRUE;
}

/*
 *  FUNCTION   :  wxPaletteSize(VOID FAR * pv)
 *  PURPOSE    :  Calculates the palette size in bytes. If the info. block
 *                is of the BITMAPCOREHEADER type, the number of colors is
 *                multiplied by 3 to give the palette size, otherwise the
 *                number of colors is multiplied by 4.
 *  RETURNS    :  Palette size in number of bytes.
 */

WORD wxPaletteSize(VOID FAR * pv)
{
    LPBITMAPINFOHEADER lpbi;
    WORD               NumColors;

    lpbi = (LPBITMAPINFOHEADER) pv;
    NumColors = wxDibNumColors(lpbi);

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
        return (WORD)(NumColors * sizeof(RGBTRIPLE));
    else
        return (WORD)(NumColors * sizeof(RGBQUAD));
}

/*
 *  FUNCTION   : wxDibNumColors(VOID FAR * pv)
 *  PURPOSE    : Determines the number of colors in the DIB by looking at
 *               the BitCount filed in the info block.
 *  RETURNS    : The number of colors in the DIB.                            *
 */

static WORD wxDibNumColors(VOID FAR *pv)
{
    int                 bits;
    BITMAPINFOHEADER        *lpbi;
    BITMAPCOREHEADER        *lpbc;

    lpbi = ((BITMAPINFOHEADER*) pv);
    lpbc = ((BITMAPCOREHEADER*) pv);

    /*        With the BITMAPINFO format headers, the size of the palette
     *        is in biClrUsed, whereas in the BITMAPCORE - style headers, it
     *        is dependent on the bits per pixel ( = 2 raised to the power of
     *        bits/pixel).
     */
    if (lpbi->biSize != sizeof(BITMAPCOREHEADER)) {
        if (lpbi->biClrUsed != 0)
            return (WORD) lpbi->biClrUsed;
        bits = lpbi->biBitCount;
    }
    else
        bits = lpbc->bcBitCount;

    switch (bits) {
    case 1:
        return 2;
    case 4:
        return 16;
    case 8:
        return 256;
    default:
        /* A 24 bitcount DIB has no color table */
        return 0;
    }
}

/*
 *  FUNCTION   : lread(int fh, VOID FAR *pv, DWORD ul)
 *  PURPOSE    : Reads data in steps of 32k till all the data has been read.
 *  RETURNS    : 0 - If read did not proceed correctly.
 *               number of bytes read otherwise.
 */

static DWORD lread(int fh, void far *pv, DWORD ul)
{
    DWORD     ulT = ul;
#if defined(WINNT) || defined(__WIN32__) || defined(__WIN32__)
    BYTE *hp = (BYTE *) pv;
#else
    BYTE huge *hp = (BYTE huge *) pv;
#endif
    while (ul > (DWORD) MAXREAD) {
        if (_lread(fh, (LPSTR) hp, (WORD) MAXREAD) != MAXREAD)
            return 0;
        ul -= MAXREAD;
        hp += MAXREAD;
    }
    if (_lread(fh, (LPSTR) hp, (WXUINT) ul) != (WXUINT) ul)
        return 0;
    return ulT;
}

/*
 *  FUNCTION   : lwrite(int fh, VOID FAR *pv, DWORD ul)
 *  PURPOSE    : Writes data in steps of 32k till all the data is written.
 *  RETURNS    : 0 - If write did not proceed correctly.
 *               number of bytes written otherwise.
 */

static DWORD lwrite(int fh, VOID FAR *pv, DWORD ul)
{
    DWORD     ulT = ul;
#if defined(WINNT) || defined(__WIN32__) || defined(__WIN32__)
    BYTE *hp = (BYTE *) pv;
#else
    BYTE huge *hp = (BYTE huge *) pv;
#endif
    while (ul > MAXREAD) {
        if (_lwrite(fh, (LPSTR) hp, (WORD) MAXREAD) != MAXREAD)
            return 0;
        ul -= MAXREAD;
        hp += MAXREAD;
    }
    if (_lwrite(fh, (LPSTR) hp, (WXUINT) ul) != (WXUINT) ul)
        return 0;
    return ulT;
}

/*
 *  FUNCTION   : wxReadDIB(hWnd)
 *  PURPOSE    : Reads a DIB from a file, obtains a handle to its
 *               BITMAPINFO struct. and loads the DIB.  Once the DIB
 *               is loaded, the function also creates a bitmap and
 *               palette out of the DIB for a device-dependent form.
 *  RETURNS    : TRUE  - DIB loaded and bitmap/palette created
 *                       The DIBINIT structure pointed to by pInfo is
 *                       filled with the appropriate handles.
 *               FALSE - otherwise
 */

bool wxReadDIB(LPTSTR lpFileName, HBITMAP *bitmap, HPALETTE *palette)
{
    int fh;
    LPBITMAPINFOHEADER lpbi;
    OFSTRUCT               of;
    BITMAPFILEHEADER   bf;
    WORD                nNumColors;
    bool result = FALSE;
    WORD offBits;
    HDC hDC;
    bool bCoreHead = FALSE;
    HANDLE hDIB = 0;

    /* Open the file and get a handle to it's BITMAPINFO */

    fh = OpenFile (wxConvertWX2MB(lpFileName), &of, OF_READ);
    if (fh == -1) {
        wxLogError(_("Can't open file '%s'"), lpFileName);
        return (0);
    }

    hDIB = GlobalAlloc(GHND, (DWORD)(sizeof(BITMAPINFOHEADER) +
        256 * sizeof(RGBQUAD)));
    if (!hDIB)
        return(0);

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

    /* read the BITMAPFILEHEADER */
    if (sizeof (bf) != _lread (fh, (LPSTR)&bf, sizeof (bf)))
        goto ErrExit;

    if (bf.bfType != 0x4d42)        /* 'BM' */
        goto ErrExit;

    if (sizeof(BITMAPCOREHEADER) != _lread (fh, (LPSTR)lpbi, sizeof(BITMAPCOREHEADER)))
        goto ErrExit;

    if (lpbi->biSize == sizeof(BITMAPCOREHEADER))
    {
        lpbi->biSize = sizeof(BITMAPINFOHEADER);
        lpbi->biBitCount = ((LPBITMAPCOREHEADER)lpbi)->bcBitCount;
        lpbi->biPlanes = ((LPBITMAPCOREHEADER)lpbi)->bcPlanes;
        lpbi->biHeight = ((LPBITMAPCOREHEADER)lpbi)->bcHeight;
        lpbi->biWidth = ((LPBITMAPCOREHEADER)lpbi)->bcWidth;
        bCoreHead = TRUE;
    }
    else
    {
        // get to the start of the header and read INFOHEADER
        _llseek(fh,sizeof(BITMAPFILEHEADER),SEEK_SET);
        if (sizeof(BITMAPINFOHEADER) != _lread (fh, (LPSTR)lpbi, sizeof(BITMAPINFOHEADER)))
            goto ErrExit;
    }

    nNumColors = (WORD)lpbi->biClrUsed;
    if ( nNumColors == 0 )
    {
        /* no color table for 24-bit, default size otherwise */
        if (lpbi->biBitCount != 24)
            nNumColors = 1 << lpbi->biBitCount;        /* standard size table */
    }

    /* fill in some default values if they are zero */
    if (lpbi->biClrUsed == 0)
        lpbi->biClrUsed = nNumColors;

    if (lpbi->biSizeImage == 0)
    {
        lpbi->biSizeImage = ((((lpbi->biWidth * (DWORD)lpbi->biBitCount) + 31) & ~31) >> 3)
            * lpbi->biHeight;
    }

    /* get a proper-sized buffer for header, color table and bits */
    GlobalUnlock(hDIB);
    hDIB = GlobalReAlloc(hDIB, lpbi->biSize +
        nNumColors * sizeof(RGBQUAD) +
        lpbi->biSizeImage, 0);
    if (!hDIB)        /* can't resize buffer for loading */
        goto ErrExit2;

    lpbi = (LPBITMAPINFOHEADER)GlobalLock(hDIB);

    /* read the color table */
    if (!bCoreHead)
        _lread(fh, (LPSTR)(lpbi) + lpbi->biSize, nNumColors * sizeof(RGBQUAD));
    else
    {
        signed int i;
        RGBQUAD FAR *pQuad;
        RGBTRIPLE FAR *pTriple;

        _lread(fh, (LPSTR)(lpbi) + lpbi->biSize, nNumColors * sizeof(RGBTRIPLE));

        pQuad = (RGBQUAD FAR *)((LPSTR)lpbi + lpbi->biSize);
        pTriple = (RGBTRIPLE FAR *) pQuad;
        for (i = nNumColors - 1; i >= 0; i--)
        {
            pQuad[i].rgbRed = pTriple[i].rgbtRed;
            pQuad[i].rgbBlue = pTriple[i].rgbtBlue;
            pQuad[i].rgbGreen = pTriple[i].rgbtGreen;
            pQuad[i].rgbReserved = 0;
        }
    }

    /* offset to the bits from start of DIB header */
    offBits = (WORD)(lpbi->biSize + nNumColors * sizeof(RGBQUAD));

    if (bf.bfOffBits != 0L)
    {
        _llseek(fh,bf.bfOffBits,SEEK_SET);
    }

    if (lpbi->biSizeImage == lread(fh, (LPSTR)lpbi + offBits, lpbi->biSizeImage))
    {
        GlobalUnlock(hDIB);

        hDC = GetDC(NULL);
        if (!wxMakeBitmapAndPalette(hDC, hDIB, palette,
            bitmap))
        {
            ReleaseDC(NULL,hDC);
            goto ErrExit2;
        }
        else
        {
            ReleaseDC(NULL,hDC);
            GlobalFree(hDIB);
            result = TRUE;
        }
    }
    else
    {
ErrExit:
    GlobalUnlock(hDIB);
ErrExit2:
    GlobalFree(hDIB);
    }

    _lclose(fh);
    return(result);
}

/*
 *  FUNCTION   : wxMakeBitmapAndPalette
 *  PURPOSE    : Given a DIB, creates a bitmap and corresponding palette
 *               to be used for a device-dependent representation of
 *               of the image.
 *  RETURNS    : TRUE  --> success. phPal and phBitmap are filled with
 *                         appropriate handles.  Caller is responsible
 *                         for freeing objects.
 *               FALSE --> unable to create objects.  both pointer are
 *                         not valid
 */

static bool wxMakeBitmapAndPalette(HDC hDC, HANDLE hDIB,
                        HPALETTE * phPal, HBITMAP * phBitmap)
{
    LPBITMAPINFOHEADER lpInfo;
    bool result = FALSE;
    HBITMAP hBitmap;
    HPALETTE hPalette, hOldPal;
    LPSTR lpBits;

    lpInfo = (LPBITMAPINFOHEADER) GlobalLock(hDIB);

    hPalette = wxMakeDIBPalette(lpInfo);
    if ( hPalette )
    {
        // Need to realize palette for converting DIB to bitmap.
        hOldPal = SelectPalette(hDC, hPalette, TRUE);
        RealizePalette(hDC);

        lpBits = (LPSTR)lpInfo + (WORD)lpInfo->biSize +
            (WORD)lpInfo->biClrUsed * sizeof(RGBQUAD);
        hBitmap = CreateDIBitmap(hDC, lpInfo, CBM_INIT, lpBits,
            (LPBITMAPINFO)lpInfo, DIB_RGB_COLORS);

        SelectPalette(hDC, hOldPal, TRUE);
        RealizePalette(hDC);

        if (!hBitmap)
            DeleteObject(hPalette);
        else
        {
            *phBitmap = hBitmap;
            *phPal = hPalette;
            result = TRUE;
        }
    }

    GlobalUnlock (hDIB);  // glt

    return(result);
}

/*
 *  FUNCTION   : wxMakeDIBPalette(lpInfo)
 *  PURPOSE    : Given a BITMAPINFOHEADER, create a palette based on
 *               the color table.
 *  RETURNS    : non-zero - handle of a corresponding palette
 *               zero - unable to create palette
 */

HPALETTE wxMakeDIBPalette(LPBITMAPINFOHEADER lpInfo)
{
    LPLOGPALETTE npPal;
    RGBQUAD far *lpRGB;
    HPALETTE hLogPal;
    WORD i;

    /* since biClrUsed field was filled during the loading of the DIB,
     * we know it contains the number of colors in the color table.
     */
    if (lpInfo->biClrUsed)
    {
        npPal = (LPLOGPALETTE)malloc(sizeof(LOGPALETTE) +
            (WORD)lpInfo->biClrUsed * sizeof(PALETTEENTRY));
        if (!npPal)
            return NULL;

        npPal->palVersion = 0x300;
        npPal->palNumEntries = (WORD)lpInfo->biClrUsed;

        /* get pointer to the color table */
        lpRGB = (RGBQUAD FAR *)((LPSTR)lpInfo + lpInfo->biSize);

        /* copy colors from the color table to the LogPalette structure */
        for (i = 0; (DWORD)i < lpInfo->biClrUsed; i++, lpRGB++)
        {
            npPal->palPalEntry[i].peRed = lpRGB->rgbRed;
            npPal->palPalEntry[i].peGreen = lpRGB->rgbGreen;
            npPal->palPalEntry[i].peBlue = lpRGB->rgbBlue;
            npPal->palPalEntry[i].peFlags = 0;
        }

        hLogPal = CreatePalette((LPLOGPALETTE)npPal);
        free(npPal);

        return(hLogPal);
    }

    /* 24-bit DIB with no color table. Return default palette. Another
     * option would be to create a 256 color "rainbow" palette to provide
     * some good color choices.
     */
    else
        return((HPALETTE) GetStockObject(DEFAULT_PALETTE));
}

/*
 *
 * Function:   InitBitmapInfoHeader
 *
 * Purpose:    Does a "standard" initialization of a BITMAPINFOHEADER,
 *             given the Width, Height, and Bits per Pixel for the
 *             DIB.
 *
 *             By standard, I mean that all the relevant fields are set
 *             to the specified values.  biSizeImage is computed, the
 *             biCompression field is set to "no compression," and all
 *             other fields are 0.
 *
 *             Note that DIBs only allow BitsPixel values of 1, 4, 8, or
 *             24.  This routine makes sure that one of these values is
 *             used (whichever is most appropriate for the specified
 *             nBPP).
 *
 * Parms:      lpBmInfoHdr == Far pointer to a BITMAPINFOHEADER structure
 *                            to be filled in.
 *             dwWidth     == Width of DIB (not in Win 3.0 & 3.1, high
 *                            word MUST be 0).
 *             dwHeight    == Height of DIB (not in Win 3.0 & 3.1, high
 *                            word MUST be 0).
 *             nBPP        == Bits per Pixel for the DIB.
 *
 */

static void InitBitmapInfoHeader (LPBITMAPINFOHEADER lpBmInfoHdr,
                                        DWORD dwWidth,
                                        DWORD dwHeight,
                                          int nBPP)
{
    //   _fmemset (lpBmInfoHdr, 0, sizeof (BITMAPINFOHEADER));
    memset (lpBmInfoHdr, 0, sizeof (BITMAPINFOHEADER));

    lpBmInfoHdr->biSize      = sizeof (BITMAPINFOHEADER);
    lpBmInfoHdr->biWidth     = dwWidth;
    lpBmInfoHdr->biHeight    = dwHeight;
    lpBmInfoHdr->biPlanes    = 1;

    if (nBPP <= 1)
        nBPP = 1;
    else if (nBPP <= 4)
        nBPP = 4;
    else if (nBPP <= 8)
        nBPP = 8;
   /* Doesn't work
        else if (nBPP <= 16)
        nBPP = 16;
    */
    else
        nBPP = 24;

    lpBmInfoHdr->biBitCount  = nBPP;
    lpBmInfoHdr->biSizeImage = WIDTHBYTES (dwWidth * nBPP) * dwHeight;
}

LPSTR wxFindDIBBits (LPSTR lpbi)
{
    return (lpbi + *(LPDWORD)lpbi + wxPaletteSize (lpbi));
}

/*
 * Function:   BitmapToDIB
 *
 * Purpose:    Given a device dependent bitmap and a palette, returns
 *             a handle to global memory with a DIB spec in it.  The
 *             DIB is rendered using the colors of the palette passed in.
 *
 * Parms:      hBitmap == Handle to device dependent bitmap compatible
 *                        with default screen display device.
 *             hPal    == Palette to render the DDB with.  If it's NULL,
 *                        use the default palette.
 */

HANDLE wxBitmapToDIB (HBITMAP hBitmap, HPALETTE hPal)
{
    BITMAP             Bitmap;
    BITMAPINFOHEADER   bmInfoHdr;
    LPBITMAPINFOHEADER lpbmInfoHdr;
    LPSTR              lpBits;
    HDC                hMemDC;
    HANDLE             hDIB;
    HPALETTE           hOldPal = NULL;

    // Do some setup -- make sure the Bitmap passed in is valid,
    //  get info on the bitmap (like its height, width, etc.),
    //  then setup a BITMAPINFOHEADER.

    if (!hBitmap)
        return NULL;

    if (!GetObject (hBitmap, sizeof (Bitmap), (LPSTR) &Bitmap))
        return NULL;

    InitBitmapInfoHeader (&bmInfoHdr,
        Bitmap.bmWidth,
        Bitmap.bmHeight,
        Bitmap.bmPlanes * Bitmap.bmBitsPixel);

    // Now allocate memory for the DIB.  Then, set the BITMAPINFOHEADER
    //  into this memory, and find out where the bitmap bits go.

    hDIB = GlobalAlloc (GHND, sizeof (BITMAPINFOHEADER) +
        wxPaletteSize ((LPSTR) &bmInfoHdr) + bmInfoHdr.biSizeImage);

    if (!hDIB)
        return NULL;

    lpbmInfoHdr  = (LPBITMAPINFOHEADER) GlobalLock (hDIB);

    *lpbmInfoHdr = bmInfoHdr;
    lpBits       = wxFindDIBBits ((LPSTR) lpbmInfoHdr);


    // Now, we need a DC to hold our bitmap.  If the app passed us
    //  a palette, it should be selected into the DC.

    hMemDC = GetDC (NULL);

    if (hPal)
    {
        hOldPal = SelectPalette (hMemDC, hPal, FALSE);
        RealizePalette (hMemDC);
    }

    // We're finally ready to get the DIB.  Call the driver and let
    // it party on our bitmap.  It will fill in the color table,
    // and bitmap bits of our global memory block.

    if (!GetDIBits (hMemDC, hBitmap, 0, Bitmap.bmHeight, lpBits,
            (LPBITMAPINFO) lpbmInfoHdr, DIB_RGB_COLORS))
    {
        GlobalUnlock (hDIB);
        GlobalFree (hDIB);
        hDIB = NULL;
    }
    else
        GlobalUnlock (hDIB);

    // Finally, clean up and return.

    if (hOldPal)
        SelectPalette (hMemDC, hOldPal, FALSE);

    ReleaseDC (NULL, hMemDC);

    return hDIB;
}

bool wxSaveBitmap(wxChar *filename, wxBitmap *bitmap, wxPalette *palette)
{
    HPALETTE hPalette = 0;
#if wxUSE_PALETTE
    if (palette)
        hPalette = (HPALETTE) palette->GetHPALETTE();
#endif // wxUSE_PALETTE

    HANDLE dibHandle = wxBitmapToDIB((HBITMAP) bitmap->GetHBITMAP(), hPalette);
    if (dibHandle)
    {
        bool success = (wxWriteDIB(filename, dibHandle) != 0);
        GlobalFree(dibHandle);
        return success;
    }
    else return FALSE;
}

