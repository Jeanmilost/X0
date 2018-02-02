/******************************************************************************
 * ==> X_Logger_HTML ---------------------------------------------------------*
 ******************************************************************************
 * Description : Write logs in HTML file, wrapper around C++ HTML logger      *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "X_Logger_HTML_iPhone.h"
#import "X_StringTools.h"
#import "X_SystemTools.h"
#import "X_MessageBox.h"

#include "E_DateAndTimeTools.h"

//------------------------------------------------------------------------------
// class X_Logger_HTML - objective c
//------------------------------------------------------------------------------
@implementation X_Logger_HTML_iPhone
//------------------------------------------------------------------------------
+ (void)Open
{
    // is logger already open?
    if (g_Logger_HTML.IsOpen())
        return;

    // build log file name
    NSString* pFileName    = [X_Logger_HTML_iPhone BuildFileName];
    NSString* pDestDir     = [[X_SystemTools GetiOSDocumentDir]stringByAppendingPathComponent:@"Logs"];
    NSString* pLeafName    = [pFileName stringByAppendingString:@".html"];
    NSString* pFileNameStr = [pDestDir stringByAppendingPathComponent:pLeafName];    

    // check if log directory exists, create if not
    if (![X_SystemTools CreateDir:pDestDir :YES])
        return;

    // open logger
    g_Logger_HTML.Open([X_StringTools NSStrToWStr:pFileNameStr]);

    // log basic target iPhone stats (OS type and version, memory ,...)
    M_LogSeparation(" Target application info ");
    M_Log("[start on]" << g_Logger_HTML.GetDateTime());
    M_Log("[bundle name] " << [X_StringTools NSStrToWStr:[X_SystemTools GetAppName]]);
    M_Log("[bundle version] " << [X_StringTools NSStrToWStr:[X_SystemTools GetAppVersionStr]]);
    //M_Log("[target system name] " << [X_StringTools NSStrToWStr:[X_SystemTools GetOSName]]);
    //M_Log("[target system version] " << [X_StringTools NSStrToWStr:[X_SystemTools GetOSVersionStr]]);
    M_Log("[iPhone name] " << [X_StringTools NSStrToWStr:[[UIDevice currentDevice]name]]);
    M_Log("[iPhone model] " << [X_StringTools NSStrToWStr:[[UIDevice currentDevice]model]]);
    M_Log("[iPhone localized model] " << [X_StringTools NSStrToWStr:[[UIDevice currentDevice]localizedModel]]);
    M_Log("[iPhone system name] " << [X_StringTools NSStrToWStr:[[UIDevice currentDevice]systemName]]);
    //M_Log("[iPhone system version] " << [X_StringTools NSStrToWStr:[[UIDevice currentDevice]systemVersion]]);
    M_Log("[iPhone system version] " << [X_StringTools NSStrToWStr:[X_SystemTools GetOSVersionStr]]);
    M_Log("[iPhone type] " << [X_StringTools NSStrToWStr:[X_SystemTools GetPlatform]]);
    M_Log("[memory] " << [X_StringTools NSStrToWStr:[X_SystemTools GetMemoryStr]]);
    M_Log("[IP address] " << [X_StringTools NSStrToWStr:[X_SystemTools GetIPAddress]]);
    M_Log("<br>");

    M_LogSeparation(" Runtime events ");
}
//------------------------------------------------------------------------------
+ (void)Save
{
    // is logger previously opened?
    if (!g_Logger_HTML.IsOpen())
        return;

    // get log file name and contents
    NSString* pFileName = [X_StringTools WStrToNSStr:g_Logger_HTML.GetFileName()];
    NSString* pData     = [X_StringTools WStrToNSStr:g_Logger_HTML.GetContent()];
    NSError*  pError;

    // close logger, but don't save file internally (native objective-c functions will be used instead)
    g_Logger_HTML.Close(false);

    // try to write HTML file
    if (![pData writeToFile:pFileName atomically:FALSE encoding:NSUTF8StringEncoding error:&pError]) 
    {
        NSString* pErrorMsg = @"Could not save log file\n";
        pErrorMsg = [pFileName stringByAppendingString:[pError localizedFailureReason]];

        [X_MessageBox DisplayError :@"Error" :pErrorMsg];
        return;
    }
}
//------------------------------------------------------------------------------
+ (NSString*) BuildFileName
{
    // build file name (formatted as follow: AppName vX.XX [dd-mm-yyyy hh.mm.ss])
    NSString* pFileName = [X_SystemTools GetAppName];
    pFileName = [pFileName stringByAppendingString:@" v"];
    pFileName = [pFileName stringByAppendingString:[X_SystemTools GetAppVersionStr]];
    pFileName = [pFileName stringByAppendingString:@" ["];
    pFileName = [pFileName stringByAppendingString:
                 [X_StringTools WStrToNSStr:E_DateAndTimeTools::GetDateTimeNow_Custom(L'-', L'.')]];
    pFileName = [pFileName stringByAppendingString:@"]"];
    
    return pFileName;
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
