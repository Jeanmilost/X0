/******************************************************************************
 * ==> E_StringTools ---------------------------------------------------------*
 ******************************************************************************
 * Description : Tools for string manipulation                                *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#include "E_StringTools.h"
#include "ConvertUTF.h"
#include "E_Exception.h"

//------------------------------------------------------------------------------
// E_StringTools - c++
//------------------------------------------------------------------------------
std::wstring E_StringTools::StrToWStr(const std::string& str)
{
    std::wstring wstr(str.length(), L' ');
    std::copy(str.begin(), str.end(), wstr.begin());
    return wstr;
}
//------------------------------------------------------------------------------
std::string E_StringTools::WStrToStr(const std::wstring& wstr)
{
    std::string str(wstr.length(), ' ');
    std::copy(wstr.begin(), wstr.end(), str.begin());
    return str;
}
//------------------------------------------------------------------------------
std::wstring E_StringTools::UTF8ToUTF16(const std::string& str)
{
    // source code from:
    // http://www.codeproject.com/Articles/17573/Convert-Between-std-string-and-std-wstring-UTF-8-a

    size_t wideSize = str.length();

    // search for system char length (can be different on Windows, Linux, OSX or other systems)
    if (sizeof(wchar_t) == 2)
    {
        // calculate utf16 size, prepare utf16 container and calculate source and dest offsets
        wchar_t*    pWideStringNative = new wchar_t[wideSize + 1];
        const UTF8* pSourceStart      = reinterpret_cast<const UTF8*>(str.c_str());
        const UTF8* pSourceEnd        = pSourceStart + wideSize;
        UTF16*      pTargetStart      = reinterpret_cast<UTF16*>(pWideStringNative);
        UTF16*      pTargetEnd        = pTargetStart + wideSize + 1;

        // try to convert to utf16
        ConversionResult res = ConvertUTF8toUTF16(&pSourceStart,
                                                  pSourceEnd,
                                                  &pTargetStart,
                                                  pTargetEnd,
                                                  lenientConversion);

        // conversion failed?
        if (res != conversionOK)
        {
            delete[] pWideStringNative;
            M_THROW_EXCEPTION("Conversion failed - wchar_t length - 2");
        }

        // get and return utf16 converted string
        *pTargetStart = 0;
        std::wstring resultString(pWideStringNative);
        delete[] pWideStringNative;
        return resultString;
    }
    else
    if (sizeof(wchar_t) == 4)
    {
        // calculate utf16 size, prepare utf16 container and calculate source and dest offsets
        wchar_t*    pWideStringNative = new wchar_t[wideSize + 1];
        const UTF8* pSourceStart      = reinterpret_cast<const UTF8*>(str.c_str());
        const UTF8* pSourceEnd        = pSourceStart + wideSize;
        UTF32*      pTargetStart      = reinterpret_cast<UTF32*>(pWideStringNative);
        UTF32*      pTargetEnd        = pTargetStart + wideSize;

        // try to convert to utf16
        ConversionResult res = ConvertUTF8toUTF32(&pSourceStart,
                                                  pSourceEnd,
                                                  &pTargetStart,
                                                  pTargetEnd,
                                                  lenientConversion);

        // conversion failed?
        if (res != conversionOK)
        {
            delete[] pWideStringNative;
            M_THROW_EXCEPTION("Conversion failed - wchar_t length - 4");
        }

        // get and return utf16 converted string
        *pTargetStart = 0;
        std::wstring resultString(pWideStringNative);
        delete[] pWideStringNative;
        return resultString;
    }
    else
        M_THROW_EXCEPTION("Conversion failed - unknown wchar_t length");
}
//------------------------------------------------------------------------------
std::string E_StringTools::UTF16ToUTF8(const std::wstring& wstr)
{
    // source code from:
    // http://www.codeproject.com/Articles/17573/Convert-Between-std-string-and-std-wstring-UTF-8-a

    size_t wideSize = wstr.length();

    // search for system char length (can be different on Windows, Linux, OSX or other systems)
    if (sizeof(wchar_t) == 2)
    {
        // calculate utf8 size, prepare utf8 container and calculate source and dest offsets
        size_t       utf8Size          = 2 * wideSize + 1;
        char*        pUtf8StringNative = new char[utf8Size];
        const UTF16* pSourceStart      = reinterpret_cast<const UTF16*>(wstr.c_str());
        const UTF16* pSourceEnd        = pSourceStart + wideSize;
        UTF8*        pTargetStart      = reinterpret_cast<UTF8*>(pUtf8StringNative);
        UTF8*        pTargetEnd        = pTargetStart + utf8Size;

        // try to convert to utf8
        ConversionResult res = ConvertUTF16toUTF8(&pSourceStart,
                                                  pSourceEnd,
                                                  &pTargetStart,
                                                  pTargetEnd,
                                                  lenientConversion);

        // conversion failed?
        if (res != conversionOK)
        {
            delete [] pUtf8StringNative;
            M_THROW_EXCEPTION("Conversion failed - wchar_t length - 2");
        }

        // get and return utf8 converted string
        *pTargetStart = 0;
        std::string resultString(pUtf8StringNative);
        delete [] pUtf8StringNative;
        return resultString;
    }
    else
    if (sizeof(wchar_t) == 4)
    {
        // calculate utf8 size, prepare utf8 container and calculate source and dest offsets
        size_t       utf8Size          = 4 * wideSize + 1;
        char*        pUtf8StringNative = new char[utf8Size];
        const UTF32* pSourceStart      = reinterpret_cast<const UTF32*>(wstr.c_str());
        const UTF32* pSourceEnd        = pSourceStart + wideSize;
        UTF8*        pTargetStart      = reinterpret_cast<UTF8*>(pUtf8StringNative);
        UTF8*        pTargetEnd        = pTargetStart + utf8Size;

        // try to convert to utf8
        ConversionResult res = ConvertUTF32toUTF8(&pSourceStart,
                                                  pSourceEnd,
                                                  &pTargetStart,
                                                  pTargetEnd,
                                                  lenientConversion);

        // conversion failed?
        if (res != conversionOK)
        {
            delete [] pUtf8StringNative;
            M_THROW_EXCEPTION("Conversion failed - wchar_t length - 4");
        }

        // get and return utf8 converted string
        *pTargetStart = 0;
        std::string resultString(pUtf8StringNative);
        delete [] pUtf8StringNative;
        return resultString;
    }
    else
        M_THROW_EXCEPTION("Conversion failed - unknown wchar_t length");
}
//------------------------------------------------------------------------------
std::string E_StringTools::Fill(const std::string& text, char fillChar, unsigned lineLength)
{
    if (text.length() >= lineLength)
        return text;

    std::string rawLine(lineLength, fillChar);

    unsigned startPos = ((lineLength - text.length()) / 2);

    rawLine.replace(startPos, text.length(), text);
    return rawLine;
}
//------------------------------------------------------------------------------
std::wstring E_StringTools::Fill(const std::wstring& text, wchar_t fillChar, unsigned lineLength)
{
    if (text.length() + 2 >= lineLength)
        return text;

    std::wstring rawLine(lineLength, fillChar);

    unsigned startPos = ((lineLength - text.length()) / 2);

    rawLine.replace(startPos, text.length(), text);
    return rawLine;
}
//------------------------------------------------------------------------------
std::string E_StringTools::Trim(const std::string& value)
{
    // value is empty?
    if (!value.length())
        return value;

    unsigned startPos = 0;

    // search for first non space char
    for (unsigned i = 0; i < value.length(); ++i)
        if (value[i] != ' ')
        {
            startPos = i;
            break;
        }

    unsigned endPos = value.length();

    // search for last non space char
    for (int i = value.length() - 1; i >= 0; --i)
        if (value[i] != ' ')
        {
            endPos = i + 1;
            break;
        }

    // is start and end position identical or invalid?
    if (startPos >= endPos - 1)
        return "";

    // return trimmed string
    return value.substr(startPos, endPos - startPos);
}
//------------------------------------------------------------------------------
std::wstring E_StringTools::Trim(const std::wstring& value)
{
    // value is empty?
    if (!value.length())
        return value;

    unsigned startPos = 0;

    // search for first non space char
    for (unsigned i = 0; i < value.length(); ++i)
        if (value[i] != ' ')
        {
            startPos = i;
            break;
        }

    unsigned endPos = value.length();

    // search for last non space char
    for (int i = value.length() - 1; i >= 0; --i)
        if (value[i] != ' ')
        {
            endPos = i + 1;
            break;
        }

    // is start and end position identical or invalid?
    if (startPos >= endPos - 1)
        return L"";

    // return trimmed string
    return value.substr(startPos, endPos - startPos);
}
//------------------------------------------------------------------------------
