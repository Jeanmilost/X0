/******************************************************************************
 * ==> E_Logger_HTML ---------------------------------------------------------*
 ******************************************************************************
 * Description : Write logs in HTML file                                      *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#ifndef E_Logger_HTML_h
#define E_Logger_HTML_h
#include "E_StringTools.h"
#include "E_Logger.h"

class E_Logger_HTML;
extern E_Logger_HTML g_Logger_HTML;

#define M_Log(argument)      g_Logger_HTML << g_Logger_HTML.BeginLn()    << argument << g_Logger_HTML.EndLn()
#define M_LogWarn(argument)  g_Logger_HTML << g_Logger_HTML.BeginWarn()  << argument << g_Logger_HTML.EndWarn()
#define M_LogError(argument) g_Logger_HTML << g_Logger_HTML.BeginError() << argument << g_Logger_HTML.EndError()
#define M_LogInfo(argument)  g_Logger_HTML << g_Logger_HTML.BeginInfo()  << argument << g_Logger_HTML.EndInfo()

#define M_LogT(argument)      M_Log("[" << g_Logger_HTML.GetTime() << "]" << argument)
#define M_LogWarnT(argument)  M_LogWarn("[" << g_Logger_HTML.GetTime() << "]" << argument)
#define M_LogErrorT(argument) M_LogError("[" << g_Logger_HTML.GetTime() << "]" << argument)
#define M_LogInfoT(argument)  M_LogInfo("[" << g_Logger_HTML.GetTime() << "]" << argument)

#define M_LogSeparation(argument)  M_Log(E_StringTools::Fill(argument, '*', 80))

class E_Logger_HTML : public E_Logger
{
    public:
        E_Logger_HTML();
        virtual ~E_Logger_HTML();

        /**
        * Gets log content
        *@returns content
        */
        virtual std::wstring GetContent();

        /**
        * Gets log line start
        *@returns line start
        */
        virtual std::wstring BeginLn();

        /**
        * Gets log line end
        *@returns line end
        */
        virtual std::wstring EndLn();

        // inherited from base
        virtual std::wstring BeginInfo();
        virtual std::wstring EndInfo();
        virtual std::wstring BeginWarn();
        virtual std::wstring EndWarn();
        virtual std::wstring BeginError();
        virtual std::wstring EndError();
};
#endif
