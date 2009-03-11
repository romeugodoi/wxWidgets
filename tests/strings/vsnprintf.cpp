///////////////////////////////////////////////////////////////////////////////
// Name:        tests/strings/vsnprintf.cpp
// Purpose:     wxVsnprintf unit test
// Author:      Francesco Montorsi
//              (part of this file was taken from CMP.c of TRIO package
//               written by Bjorn Reese and Daniel Stenberg)
// Created:     2006-04-01
// RCS-ID:      $Id$
// Copyright:   (c) 2006 Francesco Montorsi, Bjorn Reese and Daniel Stenberg
///////////////////////////////////////////////////////////////////////////////

// ----------------------------------------------------------------------------
// headers
// ----------------------------------------------------------------------------

#include "testprec.h"

#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "wx/crt.h"

#if wxUSE_WXVSNPRINTF

#ifndef WX_PRECOMP
    #include "wx/wx.h"
    #include "wx/wxchar.h"
#endif // WX_PRECOMP


// NOTE: for more info about the specification of wxVsnprintf() behaviour you can
//       refer to the following page of the GNU libc manual:
//             http://www.gnu.org/software/libc/manual/html_node/Formatted-Output.html



// ----------------------------------------------------------------------------
// global utilities for testing
// ----------------------------------------------------------------------------

#define MAX_TEST_LEN        1024

// temporary buffers
static wxChar buf[MAX_TEST_LEN];
int r;

// these macros makes it possible to write all tests without repeating a lot
// of times the wxT() macro
// NOTE: you should use expected strings with these macros which do not exceed
//       MAX_TEST_LEN as these macro do check if the return value is == (int)wxStrlen(buf)

#define ASSERT_STR_EQUAL( a, b ) \
    CPPUNIT_ASSERT_EQUAL( wxString(a), wxString(b) );

#define CMP6(expected, fmt, y, z, w, t)                    \
    r=wxSnprintf(buf, MAX_TEST_LEN, wxT(fmt), y, z, w, t); \
    CPPUNIT_ASSERT( r == (int)wxStrlen(buf) );             \
    ASSERT_STR_EQUAL( wxT(expected), buf );

#define CMP5(expected, fmt, y, z, w)                    \
    r=wxSnprintf(buf, MAX_TEST_LEN, wxT(fmt), y, z, w); \
    CPPUNIT_ASSERT( r == (int)wxStrlen(buf) );          \
    ASSERT_STR_EQUAL( wxT(expected), buf );

#define CMP4(expected, fmt, y, z)                     \
    r=wxSnprintf(buf, MAX_TEST_LEN, wxT(fmt), y, z);  \
    CPPUNIT_ASSERT( r == (int)wxStrlen(buf) );        \
    ASSERT_STR_EQUAL( wxT(expected), buf );

#define CMP3(expected, fmt, y)                        \
    r=wxSnprintf(buf, MAX_TEST_LEN, wxT(fmt), y);     \
    CPPUNIT_ASSERT( r == (int)wxStrlen(buf) );        \
    ASSERT_STR_EQUAL( wxT(expected), buf );

#define CMP2(expected, fmt)                           \
    r=wxSnprintf(buf, MAX_TEST_LEN, wxT(fmt));        \
    CPPUNIT_ASSERT( r == (int)wxStrlen(buf) );        \
    ASSERT_STR_EQUAL( wxT(expected), buf );

// NOTE: this macro is used also with too-small buffers (see Miscellaneous())
//       test function, thus the return value can be > size and thus we
//       cannot check if r == (int)wxStrlen(buf)
#define CMPTOSIZE(buffer, size, failuremsg, expected, fmt, x, y, z, w)  \
    r=wxSnprintf(buffer, size, wxT(fmt), x, y, z, w);                   \
    CPPUNIT_ASSERT( r > 0 );                                            \
    CPPUNIT_ASSERT_EQUAL_MESSAGE(                                       \
        failuremsg,                                                     \
        wxString(wxT(expected)).Left(size - 1),                         \
        wxString(buffer))

// this is the same as wxSnprintf() but it passes the format string to
// wxVsnprintf() without using WX_ATTRIBUTE_PRINTF and thus suppresses the gcc
// checks (and resulting warnings) for the format string
//
// use with extreme care and only when you're really sure the warnings must be
// suppressed!
template<typename T>
static int
wxUnsafeSnprintf(T *buf, size_t len, const wxChar *fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    int rc = wxVsnprintf(buf, len, fmt, args);

    va_end(args);

    return rc;
}

// ----------------------------------------------------------------------------
// test class
// ----------------------------------------------------------------------------

class VsnprintfTestCase : public CppUnit::TestCase
{
public:
    VsnprintfTestCase();

private:
    CPPUNIT_TEST_SUITE( VsnprintfTestCase );
        CPPUNIT_TEST( C );
        CPPUNIT_TEST( D );
        CPPUNIT_TEST( X );
        CPPUNIT_TEST( O );
        CPPUNIT_TEST( P );
        CPPUNIT_TEST( N );
        CPPUNIT_TEST( E );
        CPPUNIT_TEST( F );
        CPPUNIT_TEST( G );
        CPPUNIT_TEST( S );
        CPPUNIT_TEST( Asterisk );
        CPPUNIT_TEST( Percent );
#ifdef wxLongLong_t
        CPPUNIT_TEST( LongLong );
#endif

        CPPUNIT_TEST( BigToSmallBuffer );
#if wxUSE_WXVSNPRINTF
        CPPUNIT_TEST( WrongFormatStrings );
#endif // wxUSE_WXVSNPRINTF
        CPPUNIT_TEST( Miscellaneous );
    CPPUNIT_TEST_SUITE_END();

    void C();
    void D();
    void X();
    void O();
    void P();
    void N();
    void E();
    void F();
    void G();
    void S();
    void Asterisk();
    void Percent();
#ifdef wxLongLong_t
    void LongLong();
#endif
    void Unicode();

    template<typename T> 
        void DoBigToSmallBuffer(T *buffer, int size);
    void BigToSmallBuffer();

#if wxUSE_WXVSNPRINTF
    void WrongFormatStrings();
#endif // wxUSE_WXVSNPRINTF

    // compares the expectedString and the result of wxVsnprintf() char by char
    // for all its lenght (not only for first expectedLen chars) and also
    // checks the return value
    void DoMisc(int expectedLen, const wxString& expectedString,
                size_t max, const wxChar *format, ...);
    void Miscellaneous();

    DECLARE_NO_COPY_CLASS(VsnprintfTestCase)
};

// register in the unnamed registry so that these tests are run by default
CPPUNIT_TEST_SUITE_REGISTRATION( VsnprintfTestCase );

// also include in it's own registry so that these tests can be run alone
CPPUNIT_TEST_SUITE_NAMED_REGISTRATION( VsnprintfTestCase, "VsnprintfTestCase" );

VsnprintfTestCase::VsnprintfTestCase()
{
    // this call is required to avoid check failures when running on machines
    // with a locale where the decimal point is not '.'
    wxSetlocale(LC_NUMERIC, "English");
}

void VsnprintfTestCase::C()
{
    CMP5("hi!", "%c%c%c", wxT('h'), wxT('i'), wxT('!'));

    // NOTE:
    // the NULL characters _can_ be passed to %c to e.g. create strings
    // with embedded NULs (because strings are not always supposed to be
    // NUL-terminated).

    DoMisc(14, wxT("Hello \0 World!"), 16, wxT("Hello %c World!"), wxT('\0'));
}

void VsnprintfTestCase::D()
{
    CMP3("+123456", "%+d", 123456);
    CMP3("-123456", "%d", -123456);
    CMP3(" 123456", "% d", 123456);
    CMP3("    123456", "%10d", 123456);
    CMP3("0000123456", "%010d", 123456);
    CMP3("-123456   ", "%-10d", -123456);
}

void VsnprintfTestCase::X()
{
    CMP3("ABCD", "%X", 0xABCD);
    CMP3("0XABCD", "%#X", 0xABCD);
    CMP3("0xabcd", "%#x", 0xABCD);
}

void VsnprintfTestCase::O()
{
    CMP3("1234567", "%o", 01234567);
    CMP3("01234567", "%#o", 01234567);
}

void VsnprintfTestCase::P()
{
    // WARNING: printing of pointers is not fully standard.
    //          GNU prints them as %#x except for NULL pointers which are
    //          printed as '(nil)'.
    //          MSVC always print them as %8X on 32 bit systems and as %16X
    //          on 64 bit systems
#ifdef __VISUALC__
    #if SIZEOF_VOID_P == 4
        CMP3("00ABCDEF", "%p", (void*)0xABCDEF);
        CMP3("00000000", "%p", (void*)NULL);
    #elif SIZEOF_VOID_P == 8
        CMP3("0000ABCDEFABCDEF", "%p", (void*)0xABCDEFABCDEF);
        CMP3("0000000000000000", "%p", (void*)NULL);
    #endif
#elif defined(__GNUG__)
    CMP3("0xabcdef", "%p", (void*)0xABCDEF);
    CMP3("(nil)", "%p", (void*)NULL);
#endif
}

void VsnprintfTestCase::N()
{
    int nchar;

    wxSnprintf(buf, MAX_TEST_LEN, _T("%d %s%n\n"), 3, _T("bears"), &nchar);
    CPPUNIT_ASSERT_EQUAL( 7, nchar );
}

void VsnprintfTestCase::E()
{
    // NB: there are no standards about the minimum exponent width
    //     (and the width of the %e conversion specifier refers to the
    //      mantissa, not to the exponent).
    //     Since newer MSVC versions use 3 digits as minimum exponent
    //     width while GNU libc uses 2 digits as minimum width, here we
    //     workaround this problem using for the exponent values with at
    //     least three digits.
    //     Some examples:
    //       printf("%e",2.342E+02);
    //     -> under MSVC7.1 prints:      2.342000e+002
    //     -> under GNU libc 2.4 prints: 2.342000e+02
    CMP3("2.342000e+112", "%e",2.342E+112);
    CMP3("-2.3420e-112", "%10.4e",-2.342E-112);
    CMP3("-2.3420e-112", "%11.4e",-2.342E-112);
    CMP3("   -2.3420e-112", "%15.4e",-2.342E-112);

    CMP3("-0.02342", "%G",-2.342E-02);
    CMP3("3.1415E-116", "%G",3.1415e-116);
    CMP3("0003.141500e+103", "%016e", 3141.5e100);
    CMP3("   3.141500e+103", "%16e", 3141.5e100);
    CMP3("3.141500e+103   ", "%-16e", 3141.5e100);
    CMP3("3.142e+103", "%010.3e", 3141.5e100);
}

void VsnprintfTestCase::F()
{
    CMP3("3.300000", "%5f", 3.3);
    CMP3("3.000000", "%5f", 3.0);
    CMP3("0.000100", "%5f", .999999E-4);
    CMP3("0.000990", "%5f", .99E-3);
    CMP3("3333.000000", "%5f", 3333.0);
}

void VsnprintfTestCase::G()
{
    // NOTE: the same about E() testcase applies here...

    CMP3("  3.3", "%5g", 3.3);
    CMP3("    3", "%5g", 3.0);
    CMP3("9.99999e-115", "%5g", .999999E-114);
    CMP3("0.00099", "%5g", .99E-3);
    CMP3(" 3333", "%5g", 3333.0);
    CMP3(" 0.01", "%5g", 0.01);

    CMP3("    3", "%5.g", 3.3);
    CMP3("    3", "%5.g", 3.0);
    CMP3("1e-114", "%5.g", .999999E-114);
    CMP3("0.0001", "%5.g", 1.0E-4);
    CMP3("0.001", "%5.g", .99E-3);
    CMP3("3e+103", "%5.g", 3333.0E100);
    CMP3(" 0.01", "%5.g", 0.01);

    CMP3("  3.3", "%5.2g", 3.3);
    CMP3("    3", "%5.2g", 3.0);
    CMP3("1e-114", "%5.2g", .999999E-114);
    CMP3("0.00099", "%5.2g", .99E-3);
    CMP3("3.3e+103", "%5.2g", 3333.0E100);
    CMP3(" 0.01", "%5.2g", 0.01);
}

void VsnprintfTestCase::S()
{
    CMP3("  abc", "%5s", wxT("abc"));
    CMP3("    a", "%5s", wxT("a"));
    CMP3("abcdefghi", "%5s", wxT("abcdefghi"));
    CMP3("abc  ", "%-5s", wxT("abc"));
    CMP3("abcdefghi", "%-5s", wxT("abcdefghi"));

    CMP3("abcde", "%.5s", wxT("abcdefghi"));

    // do the same tests but with Unicode characters:
#if wxUSE_UNICODE

    // Unicode code points from U+03B1 to U+03B9 are the greek letters alpha-iota;
    // UTF8 encoding of such code points is 0xCEB1 to 0xCEB9

#define ALPHA       "\xCE\xB1"
        // alpha
#define ABC         "\xCE\xB1\xCE\xB2\xCE\xB3"
        // alpha+beta+gamma
#define ABCDE       "\xCE\xB1\xCE\xB2\xCE\xB3\xCE\xB4\xCE\xB5"
        // alpha+beta+gamma+delta+epsilon
#define ABCDEFGHI   "\xCE\xB1\xCE\xB2\xCE\xB3\xCE\xB4\xCE\xB5\xCE\xB6\xCE\xB7\xCE\xB8\xCE\xB9"
        // alpha+beta+gamma+delta+epsilon+zeta+eta+theta+iota

#define ALPHA_w     wxT(ALPHA)
#define ABC_w       wxT(ABC)
#define ABCDE_w     wxT(ABCDE)
#define ABCDEFGHI_w wxT(ABCDEFGHI)

    // CMP3 uses wxT() on the first argument so we need to be careful
    // when using string concatenation that all parts of the string after
    // the first explicitely use wxT():
    CMP3("  " ABC_w,     "%5s",  ABC);
    CMP3("    " ALPHA_w, "%5s",  ALPHA);
    CMP3(ABCDEFGHI,      "%5s",  ABCDEFGHI);
    CMP3(ABC L"  ",      "%-5s", ABC);
    CMP3(ABCDEFGHI,      "%-5s", ABCDEFGHI);
    CMP3(ABCDE,          "%.5s", ABCDEFGHI);
#endif

    // test a string which has a NULL character after "ab";
    // obviously it should be handled exactly like just as "ab"
    CMP3("   ab", "%5s", wxT("ab\0cdefghi"));
}

void VsnprintfTestCase::Asterisk()
{
    CMP5("       0.1", "%*.*f", 10, 1, 0.123);
    CMP5("    0.1230", "%*.*f", 10, 4, 0.123);
    CMP5("0.1", "%*.*f", 3, 1, 0.123);

    CMP4("%0.002", "%%%.*f", 3, 0.0023456789);

    CMP4("       a", "%*c", 8, 'a');
    CMP4("    four", "%*s", 8, "four");
    CMP6("    four   four", "%*s %*s", 8, "four", 6, "four");
}

void VsnprintfTestCase::Percent()
{
    // some tests without any argument passed through ...
    CMP2("%", "%%");
    CMP2("%%%", "%%%%%%");

    CMP3("%  abc", "%%%5s", wxT("abc"));
    CMP3("%  abc%", "%%%5s%%", wxT("abc"));

    // do not test odd number of '%' symbols as different implementations
    // of snprintf() give different outputs as this situation is not considered
    // by any standard (in fact, GCC will also warn you about a spurious % if
    // you write %%% as argument of some *printf function !)
    // Compare(wxT("%"), wxT("%%%"));
}

#ifdef wxLongLong_t
void VsnprintfTestCase::LongLong()
{
    CMP3("123456789", "%lld", (wxLongLong_t)123456789);
    CMP3("-123456789", "%lld", (wxLongLong_t)-123456789);

    CMP3("123456789", "%llu", (wxULongLong_t)123456789);

#ifdef __WXMSW__
    CMP3("123456789", "%I64d", (wxLongLong_t)123456789);
    CMP3("123456789abcdef", "%I64x", wxLL(0x123456789abcdef));
#endif
}
#endif

// this test is only for our own implementation, the system implementation
// doesn't always give errors for invalid format strings (e.g. glibc doesn't)
// and as it's not required too (the behaviour is "undefined" according to the
// spec), there is really no sense in testing for it
#if wxUSE_WXVSNPRINTF

void VsnprintfTestCase::WrongFormatStrings()
{
    // test how wxVsnprintf() behaves with wrong format string:

#if 0
    // NB: the next 2 tests currently return an error but it would be nice
    //     if they didn't (see ticket #9367)

    // two positionals with the same index:
    r = wxSnprintf(buf, MAX_TEST_LEN, wxT("%1$s %1$s"), "hello");
    CPPUNIT_ASSERT(r != -1);

    // three positionals with the same index mixed with other pos args:
    r = wxSnprintf(buf, MAX_TEST_LEN, wxT("%4$d %2$f %1$s %2$s %3$d"), "hello", "world", 3, 4);
    CPPUNIT_ASSERT(r != -1);
#endif

    // a missing positional arg: this should result in an error but not all
    // implementations detect it (e.g. glibc doesn't)
    r = wxSnprintf(buf, MAX_TEST_LEN, wxT("%1$d %3$d"), 1, 2, 3);
    CPPUNIT_ASSERT_EQUAL(-1, r);

    // positional and non-positionals in the same format string:
    r = wxSnprintf(buf, MAX_TEST_LEN, wxT("%1$d %d %3$d"), 1, 2, 3);
    CPPUNIT_ASSERT_EQUAL(-1, r);
}

#endif // wxUSE_WXVSNPRINTF

// BigToSmallBuffer() test case helper:
template<typename T>
void VsnprintfTestCase::DoBigToSmallBuffer(T *buffer, int size)
{
    // Remember that wx*printf could be mapped either to system
    // implementation or to wx implementation.
    // In the first case, when the output buffer is too small, the returned
    // value can be the number of characters required for the output buffer
    // (conforming to ISO C99; implemented in e.g. GNU libc >= 2.1), or
    // just a negative number, usually -1; (this is how e.g. MSVC's
    // *printf() behaves). Luckily, in all implementations, when the
    // output buffer is too small, it's nonetheless filled up to its max size.
    //
    // Note that in the second case (i.e. when we're using our own implementation),
    // wxVsnprintf() will return the number of characters written in the standard
    // output or
    //   -1         if there was an error in the format string
    //   maxSize+1  if the output buffer is too small

    wxString errStr;
    errStr << "The size of the buffer was " << size;
    std::string errMsg(errStr.mb_str());

    // test without positionals
    CMPTOSIZE(buffer, size, errMsg,
              "123456789012 - test - 123 -4.567",
              "%i%li - test - %d %.3f",
              123, (long int)456789012, 123, -4.567);

#if wxUSE_PRINTF_POS_PARAMS
    // test with positional
    CMPTOSIZE(buffer, size, errMsg,
              "-4.567 123 - test - 456789012 123",
              "%4$.3f %1$i - test - %2$li %3$d",
              123, (long int)456789012, 123, -4.567);
#endif

    // test unicode/ansi conversion specifiers
    //
    // NB: we use wxUnsafeSnprintf() as %hs and %hc are invalid in printf
    //     format and gcc would warn about this otherwise

    r = wxUnsafeSnprintf(buffer, size,
                         _T("unicode string/char: %ls/%lc -- ansi string/char: %hs/%hc"),
                         L"unicode", L'U', "ansi", 'A');
    wxString expected =
        wxString(wxT("unicode string/char: unicode/U -- ansi string/char: ansi/A")).Left(size - 1);

    CPPUNIT_ASSERT( r != -1 );
    CPPUNIT_ASSERT_EQUAL(
        expected,
        wxString(buffer)
    );
}

void VsnprintfTestCase::BigToSmallBuffer()
{
    // VC6 can't compile this code
#if !defined(__VISUALC__) || (__VISUALC__ >= 1310)
#if wxUSE_UNICODE
    wchar_t bufw[1024], bufw2[16], bufw3[4], bufw4;
    DoBigToSmallBuffer(bufw, 1024);
    DoBigToSmallBuffer(bufw2, 16);
    DoBigToSmallBuffer(bufw3, 4);
    DoBigToSmallBuffer(&bufw4, 1);
#endif // wxUSE_UNICODE

    char bufa[1024], bufa2[16], bufa3[4], bufa4;
    DoBigToSmallBuffer(bufa, 1024);
    DoBigToSmallBuffer(bufa2, 16);
    DoBigToSmallBuffer(bufa3, 4);
    DoBigToSmallBuffer(&bufa4, 1);
#endif // !VC6
}

// Miscellaneous() test case helper:
void VsnprintfTestCase::DoMisc(
        int expectedLen,
        const wxString& expectedString,
        size_t max,
        const wxChar *format, ...)
{
    const size_t BUFSIZE = MAX_TEST_LEN - 1;
    size_t i;
    static int count = 0;

    wxASSERT(max <= BUFSIZE);

    for (i = 0; i < BUFSIZE; i++)
        buf[i] = '*';
    buf[BUFSIZE] = 0;

    va_list ap;
    va_start(ap, format);

    int n = wxVsnprintf(buf, max, format, ap);

    va_end(ap);

    // Prepare messages so that it is possible to see from the error which
    // test was running.
    wxString errStr, overflowStr;
    errStr << _T("No.: ") << ++count << _T(", expected: ") << expectedLen
           << _T(" '") << expectedString << _T("', result: ");
    overflowStr << errStr << _T("buffer overflow");
    errStr << n << _T(" '") << buf << _T("'");

    // turn them into std::strings
    std::string errMsg(errStr.mb_str());
    std::string overflowMsg(overflowStr.mb_str());

    CPPUNIT_ASSERT_MESSAGE(errMsg,
            (expectedLen == -1 && size_t(n) >= max) || expectedLen == n);

    CPPUNIT_ASSERT_MESSAGE(errMsg, expectedString == buf);

    for (i = max; i < BUFSIZE; i++)
        CPPUNIT_ASSERT_MESSAGE(overflowMsg, buf[i] == '*');
}

void VsnprintfTestCase::Miscellaneous()
{
    // expectedLen, expectedString, max, format, ...
    DoMisc(5,  wxT("-1234"),   8, wxT("%d"), -1234);
    DoMisc(7,  wxT("1234567"), 8, wxT("%d"), 1234567);
    DoMisc(-1, wxT("1234567"), 8, wxT("%d"), 12345678);
    DoMisc(-1, wxT("-123456"), 8, wxT("%d"), -1234567890);

    DoMisc(6,  wxT("123456"),  8, wxT("123456"));
    DoMisc(7,  wxT("1234567"), 8, wxT("1234567"));
    DoMisc(-1, wxT("1234567"), 8, wxT("12345678"));

    DoMisc(6,  wxT("123450"),  8, wxT("12345%d"), 0);
    DoMisc(7,  wxT("1234560"), 8, wxT("123456%d"), 0);
    DoMisc(-1, wxT("1234567"), 8, wxT("1234567%d"), 0);
    DoMisc(-1, wxT("1234567"), 8, wxT("12345678%d"), 0);

    DoMisc(6,  wxT("12%45%"),  8, wxT("12%%45%%"));
    DoMisc(7,  wxT("12%45%7"), 8, wxT("12%%45%%7"));
    DoMisc(-1, wxT("12%45%7"), 8, wxT("12%%45%%78"));

    DoMisc(5,  wxT("%%%%%"),   6, wxT("%%%%%%%%%%"));
    DoMisc(6,  wxT("%%%%12"),  7, wxT("%%%%%%%%%d"), 12);
}

#endif // wxUSE_WXVSNPRINTF
