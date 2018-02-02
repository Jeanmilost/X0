/******************************************************************************
 * ==> E_DateAndTimeTools ----------------------------------------------------*
 ******************************************************************************
 * Description : Date and time tools                                          *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#ifndef E_DateAndTime_h
#define E_DateAndTime_h
#include <string>

/**
* Date and time tools
*@author Jean-Milost Reymond
*/
class E_DateAndTimeTools
{
    public:
        /**
        * Get date now as string, using a custom conversion format (dd-mm-yyyy)
        *@param separator - separator
        *@returns date as string
        */
        static std::wstring GetDateNow_Custom(wchar_t separator = L'-');

        /**
        * Get time now as string, using a custom conversion format (hh:mm:ss)
         *@param separator - separator
        *@returns time as string
        */
        static std::wstring GetTimeNow_Custom(wchar_t separator = L':');

        /**
        * Get date and time now as string, using a custom conversion format (dd-mm-yyyy hh:mm:ss)
        *@param dateSeparator - separator to use for date
        *@param timeSeparator - separator to use for time
        *@returns date and time as string
        */
        static std::wstring GetDateTimeNow_Custom(wchar_t dateSeparator = L'-', wchar_t timeSeparator = L':');
};
#endif
