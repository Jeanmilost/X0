/******************************************************************************
 * ==> E_Logger --------------------------------------------------------------*
 ******************************************************************************
 * Description : Base class for logging                                       *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#include "E_Logger.h"
#include "E_StringTools.h"
#include "E_DateAndTimeTools.h"

//------------------------------------------------------------------------------
#define M_EndLine L"\r\n";
//------------------------------------------------------------------------------
// E_Logger - c++
//------------------------------------------------------------------------------
E_Logger::E_Logger()
{
    m_pStream.reset(new std::wostringstream);
}
//------------------------------------------------------------------------------
E_Logger::~E_Logger()
{
    // last chance - close logger and save to file if not already done
    Close(true);
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const char* argument)
{
    if (IsOpen())
        try
        {
            // first, try to convert using UTF specifications
            *m_pStream << E_StringTools::UTF8ToUTF16(argument);
        }
        catch (...)
        {
            // on error, try to convert using ASCII
            *m_pStream << E_StringTools::StrToWStr(argument);
        }

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const wchar_t* argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const std::string& argument)
{
    if (IsOpen())
        try
        {
            // first, try to convert using UTF specifications
            *m_pStream << E_StringTools::UTF8ToUTF16(argument);
        }
        catch (...)
        {
            // on error, try to convert using ASCII
            *m_pStream << E_StringTools::StrToWStr(argument);
        }

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const std::wstring& argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (char argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (wchar_t argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (short argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (unsigned short argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (int argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (unsigned argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const long& argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const unsigned long& argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const long long& argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const unsigned long long& argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const float& argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
E_Logger& E_Logger::operator << (const double& argument)
{
    if (IsOpen())
        *m_pStream << argument;

    return *this;
}
//------------------------------------------------------------------------------
void E_Logger::Open(const std::wstring& fileName)
{
    if (IsOpen())
        return;

    m_FileName = fileName;
}
//------------------------------------------------------------------------------
bool E_Logger::IsOpen()
{
    return !m_FileName.empty();
}
//------------------------------------------------------------------------------
void E_Logger::Close(bool save)
{
    // logger already open?
    if (!IsOpen())
        return;

    // do save log file?
    if (save)
        Save();

    // cleanup previous log
    Clear();
}
//------------------------------------------------------------------------------
void E_Logger::Clear()
{
    m_FileName.clear();
    m_pStream.reset(new std::wostringstream);
}
//------------------------------------------------------------------------------
std::wstring E_Logger::GetFileName()
{
    return m_FileName;
}
//------------------------------------------------------------------------------
std::wstring E_Logger::GetContent()
{
    return m_pStream->str();
}
//------------------------------------------------------------------------------
std::wstring E_Logger::GetDate()
{
    return E_DateAndTimeTools::GetDateNow_Custom();
}
//------------------------------------------------------------------------------
std::wstring E_Logger::GetTime()
{
    return E_DateAndTimeTools::GetTimeNow_Custom();
}
//------------------------------------------------------------------------------
std::wstring E_Logger::GetDateTime()
{
    return E_DateAndTimeTools::GetDateTimeNow_Custom();
}
//------------------------------------------------------------------------------
std::wstring E_Logger::EndLine()
{
    return M_EndLine;
}
//------------------------------------------------------------------------------
bool E_Logger::Save()
{
    try
    {
        if (!IsOpen())
            return false;

        std::string fileName;

        // try to convert file name to string
        try
        {
            fileName = E_StringTools::UTF16ToUTF8(m_FileName);
        }
        catch (...)
        {
            fileName = E_StringTools::WStrToStr(m_FileName);
        }

        FILE* pFile;

        // open file for write
        pFile = std::fopen(fileName.c_str(), "w");

        // file is open?
        if (pFile == NULL)
            return false;

        std::ostringstream sstr;

        // try to convert log content to string
        try
        {
            sstr << E_StringTools::UTF16ToUTF8(GetContent());
        }
        catch (...)
        {
            try
            {
                sstr << E_StringTools::WStrToStr(GetContent());
            }
            catch (...)
            {
                // could not convert, close file and return result
                std::fclose(pFile);
                return false;
            }
        }

        // write log and close file
        std::fputs(sstr.str().c_str(), pFile);
        std::fclose(pFile);

        return true;
    }
    catch (...)
    {
        return false;
    }
}
//------------------------------------------------------------------------------
