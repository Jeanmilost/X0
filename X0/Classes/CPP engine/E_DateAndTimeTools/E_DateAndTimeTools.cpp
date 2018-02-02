/******************************************************************************
 * ==> E_DateAndTimeTools ----------------------------------------------------*
 ******************************************************************************
 * Description : Date and time tools                                          *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#include "E_DateAndTimeTools.h"
#include <sstream>

//------------------------------------------------------------------------------
std::wstring E_DateAndTimeTools::GetDateNow_Custom(wchar_t separator)
{
    // get date now
    std::time_t t    = std::time(0);
    std::tm*    pNow = std::localtime(&t);

    std::wostringstream sstr;

    // convert date to string
    sstr << pNow->tm_mday << separator << (pNow->tm_mon + 1) << separator << (pNow->tm_year + 1900);

    return sstr.str();
}
//------------------------------------------------------------------------------
std::wstring E_DateAndTimeTools::GetTimeNow_Custom(wchar_t separator)
{
    // get time now
    std::time_t t    = std::time(0);
    std::tm*    pNow = std::localtime(&t);

    std::wostringstream sstr;

    // convert time to string
    sstr << (pNow->tm_hour) << separator << (pNow->tm_min) << separator << pNow->tm_sec;

    return sstr.str();
}
//------------------------------------------------------------------------------
std::wstring E_DateAndTimeTools::GetDateTimeNow_Custom(wchar_t dateSeparator, wchar_t timeSeparator)
{
    std::wostringstream sstr;

    // convert date and time to string
    sstr << GetDateNow_Custom(dateSeparator) << " " << GetTimeNow_Custom(timeSeparator);

    return sstr.str();
}
//------------------------------------------------------------------------------
