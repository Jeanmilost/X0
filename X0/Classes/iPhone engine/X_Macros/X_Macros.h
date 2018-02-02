/*****************************************************************************
 * ==> X_Macros -------------------------------------------------------------*
 * ***************************************************************************
 * Description : Some useful macros for e.g. exception catching, logging, ...*
 * Developer   : Jean-Milost Reymond                                         *
 *****************************************************************************/

#ifndef X_MACROS_H
#define X_MACROS_H
#include "E_Exception.h"
#include "E_Logger_HTML.h"
#import "X_StringTools.h"
#import "X_MessageBox.h"

#define M_Try\
    @try\
    {\
        try

#define M_CatchTrace\
        catch (const E_Exception& e)\
        {\
            M_LogError(e.Format_HTML());\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
            throw;\
        }\
        catch (const std::exception& e)\
        {\
            M_LogError(M_FORMAT_EXCEPTION_HTML("STD", e.what()));\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
            throw;\
        }\
        catch (...)\
        {\
            M_LogError(M_FORMAT_EXCEPTION_HTML("Runtime", "Runtime exception raised"));\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
            throw;\
        }\
    }\
    @catch (NSException* e)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML("NS", [X_StringTools NSStrToStr:e.reason]));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        @throw;\
    }\
    @catch (id e)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML("ID", [X_StringTools NSStrToStr:(NSString*)e]));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        @throw;\
    }\
    @catch (...)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML("Runtime", "Runtime exception raised"));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        @throw;\
    }

#define M_CatchSilent\
        catch (const E_Exception& e)\
        {\
            M_LogError(e.Format_HTML());\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        }\
        catch (const std::exception& e)\
        {\
            M_LogError(M_FORMAT_EXCEPTION_HTML("STD", e.what()));\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        }\
        catch (...)\
        {\
            M_LogError(M_FORMAT_EXCEPTION_HTML("Runtime", "Runtime exception raised"));\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        }\
    }\
    @catch (NSException* e)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML("NS", [X_StringTools NSStrToStr:e.reason]));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
    }\
    @catch (id e)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML("ID", [X_StringTools NSStrToStr:(NSString*)e]));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
    }\
    @catch (...)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML("Runtime", "Runtime exception raised"));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
    }

#define M_CatchSilentPrivate\
        catch (const E_Exception& e)\
        {\
            M_LogError(e.Format_HTML_Private());\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        }\
        catch (const std::exception& e)\
        {\
            M_LogError(M_FORMAT_EXCEPTION_HTML_PRIVATE("STD", e.what()));\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        }\
        catch (...)\
        {\
            M_LogError(M_FORMAT_EXCEPTION_HTML_PRIVATE("Runtime", "Runtime exception raised"));\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        }\
    }\
    @catch (NSException* e)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML_PRIVATE("NS", [X_StringTools NSStrToStr:e.reason]));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
    }\
    @catch (id e)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML_PRIVATE("ID", [X_StringTools NSStrToStr:(NSString*)e]));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
    }\
    @catch (...)\
    {\
        M_LogError(M_FORMAT_EXCEPTION_HTML_PRIVATE("Runtime", "Runtime exception raised"));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
    }

#define M_CatchShow\
        catch (const E_Exception& e)\
        {\
            M_LogError(e.Format_HTML());\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
            [X_MessageBox DisplayError :@"E_Exception"\
                                       :[X_StringTools StrToNSStr:M_FORMAT_MESSAGE(e.Message())]];\
        }\
        catch (const std::exception& e)\
        {\
            std::string msg = e.what();\
            M_LogError(M_FORMAT_EXCEPTION_HTML("STD", msg));\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
            [X_MessageBox DisplayError :@"STD exception" :[X_StringTools StrToNSStr:M_FORMAT_MESSAGE(msg)]];\
        }\
        catch (...)\
        {\
            std::string msg = "Runtime exception raised";\
            M_LogError(M_FORMAT_EXCEPTION_HTML("Runtime", msg));\
            M_LogError("[Time] " << g_Logger_HTML.GetTime());\
            [X_MessageBox DisplayError :@"Runtime exception"\
                                       :[X_StringTools StrToNSStr:M_FORMAT_MESSAGE(msg)]];\
        }\
    }\
    @catch (NSException* e)\
    {\
        std::string msg = [X_StringTools NSStrToStr:e.reason];\
        M_LogError(M_FORMAT_EXCEPTION_HTML("NS", msg));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        [X_MessageBox DisplayError :e.name :[X_StringTools StrToNSStr:M_FORMAT_MESSAGE(msg)]];\
    }\
    @catch (id e)\
    {\
        std::string msg = [X_StringTools NSStrToStr:(NSString*)e];\
        M_LogError(M_FORMAT_EXCEPTION_HTML("ID", msg));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        [X_MessageBox DisplayError :@"ID exception" :[X_StringTools StrToNSStr:M_FORMAT_MESSAGE(msg)]];\
    }\
    @catch (...)\
    {\
        std::string msg = "Runtime exception raised";\
        M_LogError(M_FORMAT_EXCEPTION_HTML("Runtime", msg));\
        M_LogError("[Time] " << g_Logger_HTML.GetTime());\
        [X_MessageBox DisplayError :@"Runtime exception" :[X_StringTools StrToNSStr:M_FORMAT_MESSAGE(msg)]];\
    }

#endif
