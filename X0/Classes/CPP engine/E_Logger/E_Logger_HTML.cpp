/******************************************************************************
 * ==> E_Logger_HTML ---------------------------------------------------------*
 ******************************************************************************
 * Description : Write logs in HTML file                                      *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#include "E_Logger_HTML.h"
#include "E_Exception.h"

E_Logger_HTML g_Logger_HTML;

//------------------------------------------------------------------------------
// E_Logger_HTML - c++
//------------------------------------------------------------------------------
E_Logger_HTML::E_Logger_HTML()
{}
//------------------------------------------------------------------------------
E_Logger_HTML::~E_Logger_HTML()
{
    // last chance - close logger and save to file if not already done
    Close(true);
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::GetContent()
{
    std::wostringstream sstr;
    sstr << L"<!DOCTYPE html>" << EndLine();
    sstr << L"<html>" << EndLine();
    sstr << L"<head>" << EndLine();
    sstr << L"<meta http-equiv=\"content-type\" content=\"text/html; charset=UTF-8\">" << EndLine();
    sstr << L"<title>" << GetFileName() << L"</title>" << EndLine();
    sstr << L"<style type=\"text/css\">" << EndLine();
    sstr << L"p {margin:0; padding:0}" << EndLine();
    sstr << L"error {color:red;}" << EndLine();
    sstr << L"warn {color:yellow;}" << EndLine();
    sstr << L"info {color:green;}" << EndLine();
    sstr << L"</style>" << EndLine();
    sstr << L"</head>" << EndLine();
    sstr << L"<body>" << EndLine();
    sstr << m_pStream->str();
    sstr << L"</body>" << EndLine();
    sstr << L"</html>" << EndLine();

    return sstr.str();
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::BeginLn()
{
    return L"<p>";
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::EndLn()
{
    return L"</p>" + EndLine();
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::BeginInfo()
{
    return L"<p><info>";
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::EndInfo()
{
    return L"</info></p>" + EndLine();
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::BeginWarn()
{
    return L"<p><warn>";
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::EndWarn()
{
    return L"</warn></p>" + EndLine();
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::BeginError()
{
    return L"<p><error>";
}
//------------------------------------------------------------------------------
std::wstring E_Logger_HTML::EndError()
{
    return L"</error></p>" + EndLine();
}
//------------------------------------------------------------------------------
