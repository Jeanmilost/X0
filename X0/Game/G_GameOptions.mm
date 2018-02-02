/******************************************************************************
 * ==> G_GameOptions ---------------------------------------------------------*
 ******************************************************************************
 * Description : X0 game options                                              *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "G_GameOptions.h"
#import "X_SystemTools.h"
#import "X_MessageBox.h"
#import "X_Macros.h"

//------------------------------------------------------------------------------
@implementation G_GameOptions
//------------------------------------------------------------------------------
@synthesize m_Player1Pawn;
@synthesize m_Player2Pawn;
@synthesize m_PlayAgainstComputer;
@synthesize m_ComputerBegins;
//------------------------------------------------------------------------------
- (id) init
{
    M_Try
    {
        // set default values
        m_Player1Pawn         = G_Gameboard::IE_Pa_Cross;
        m_Player2Pawn         = G_Gameboard::IE_Pa_Round;
        m_PlayAgainstComputer = true;
        m_ComputerBegins      = false;

        if (self = [super init])
        {}

        return self;
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (bool) Load
{
    M_Try
    {
        // get options file name
        std::string fileName  = [X_StringTools NSStrToStr:[self BuildOptionsFileName]];
        NSString*   pFileName = [X_StringTools StrToNSStr:fileName];
        NSError*    pError;

        // file exists?
        if (![X_SystemTools FileExists:pFileName])
            return false;

        // load data from file
        NSString* pData = [[NSString alloc]initWithContentsOfFile :pFileName 
                                                          encoding:NSUTF8StringEncoding 
                                                             error:&pError];

        // get loaded data
        std::string data = [X_StringTools NSStrToStr:pData];

        // iterate through data
        for (unsigned i = 0; i < data.length(); ++i)
            // update options from file data
            switch (i)
            {
                case 0:
                    // update pawns
                    m_Player1Pawn = (data[i] == '0' ? G_Gameboard::IE_Pa_Cross : G_Gameboard::IE_Pa_Round);
                    m_Player2Pawn = (data[i] == '0' ? G_Gameboard::IE_Pa_Round : G_Gameboard::IE_Pa_Cross);
                    break;

                case 1:
                    // update play again value
                    m_PlayAgainstComputer = (data[i] == '1');
                    break;

                case 2:
                    // update computer begins value
                    m_ComputerBegins = (data[i] == '1');
                    break;

                default:
                    break;
            }

        return true;
    }
    M_CatchSilent
    
    return false;
}
//------------------------------------------------------------------------------
- (bool) Save
{
    M_Try
    {
        std::string fileName = [X_StringTools NSStrToStr:[self BuildOptionsFileName]];

        std::ostringstream sstr;
        sstr << (m_Player1Pawn == G_Gameboard::IE_Pa_Round ? "1" : "0");
        sstr << (m_PlayAgainstComputer                     ? "1" : "0");
        sstr << (m_ComputerBegins                          ? "1" : "0");

        // get options file name and contents
        NSString* pFileName = [X_StringTools StrToNSStr:fileName];
        NSString* pData     = [X_StringTools StrToNSStr:sstr.str()];
        NSError*  pError;

        // try to write options file
        if (![pData writeToFile:pFileName atomically:FALSE encoding:NSUTF8StringEncoding error:&pError]) 
        {
            /*
            NSString* pErrorMsg = NSLocalizedString(@"options_save_failed", @"Could not save options");
            pErrorMsg           = [pFileName stringByAppendingString:@"\n"];
            pErrorMsg           = [pFileName stringByAppendingString:[pError localizedFailureReason]];

            [X_MessageBox DisplayError :@"Error" :pErrorMsg];
            */
            return false;
        }

        return true;
    }
    M_CatchSilent

    return false;
}
//------------------------------------------------------------------------------
- (NSString*) BuildOptionsFileName
{
    M_Try
    {
        // build cached file name
        NSString* pDestDir        = [[X_SystemTools GetiOSDocumentDir]stringByAppendingPathComponent:@"Cache"];
        NSString* pFileName       = [X_StringTools StrToNSStr:"Options.bin"];
        NSString* pFileNameAndDir = [pDestDir stringByAppendingPathComponent:pFileName];
        
        // check if cache directory exists, create if not
        if (![X_SystemTools CreateDir:pDestDir :YES])
            return @"";
        
        return pFileNameAndDir;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
