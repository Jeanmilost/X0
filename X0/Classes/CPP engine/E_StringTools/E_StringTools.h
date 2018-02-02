/******************************************************************************
 * ==> E_StringTools ---------------------------------------------------------*
 ******************************************************************************
 * Description : Tools for string manipulation                                *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#ifndef E_StringTools_h
#define E_StringTools_h
#include <string>

class E_StringTools
{
    public:
        /**
        * Converts string to wstring
        *@param wstr - string to convert
        *@returns converted string
        */
        static std::wstring StrToWStr(const std::string& str);

        /**
        * Converts wstring to string
        *@param wstr - string to convert
        *@returns converted string
        */
        static std::string WStrToStr(const std::wstring& wstr);

        /**
        * Converts utf8 to utf16
        *@param str - string to convert
        *@returns converted string
        */
        static std::wstring UTF8ToUTF16(const std::string& str);

        /**
        * Converts utf16 to utf8
        *@param wstr - string to convert
        *@returns converted string
        */
        static std::string UTF16ToUTF8(const std::wstring& wstr);

        /**
        * Fill line
        *@param text - text
        *@param fillChar - fill char
        *@param lineLength - line length
        *@returns filled line
        */
        static std::string  Fill(const std::string& text, char fillChar, unsigned lineLength);
        static std::wstring Fill(const std::wstring& text, wchar_t fillChar, unsigned lineLength);

        /**
        * Trim text (i.e. remove spaces before and after text)
        *@param value - value to trim
        *@returns trimmed value
        */
        static std::string  Trim(const std::string& value);
        static std::wstring Trim(const std::wstring& value);
};
#endif
