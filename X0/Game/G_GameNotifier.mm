/******************************************************************************
 * ==> G_GameNotifier --------------------------------------------------------*
 ******************************************************************************
 * Description : Game notifier, used to convert messages from game engine to  *
 *               high level objective-c classes                               *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "G_GameNotifier.h"
#include "G_Gameboard.h"

//------------------------------------------------------------------------------
// class G_Notifier - c++
//------------------------------------------------------------------------------
void* G_Notifier::m_pGameNotifier = NULL;
//------------------------------------------------------------------------------
bool G_Notifier::OnPlayed(G_Gameboard::IEPlayer player, G_Gameboard::IEPawn pawn, bool isComputer)
{
    // call objective-c wrapper method
    return Call_OnPlayedFrom(m_pGameNotifier, player, pawn, isComputer);
}
//------------------------------------------------------------------------------
// class G_OnPlayedParam - objective c
//------------------------------------------------------------------------------
@implementation G_OnPlayedParam
//------------------------------------------------------------------------------
@synthesize m_Player;
@synthesize m_Pawn;
@synthesize m_IsComputer;
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
// class G_GameNotifier - objective c
//------------------------------------------------------------------------------
@implementation G_GameNotifier
//------------------------------------------------------------------------------
- (id)init
{
    m_pGameboard        = NULL;
    m_pOnPlayedObject   = nil;
    m_pOnPlayedDelegate = nil;

    if (self = [super init])
        // set objective-c notifier in c++ notifier
        G_Notifier::m_pGameNotifier = self;

    return self;
}
//------------------------------------------------------------------------------
- (void)dealloc
{
    [super dealloc];
}
//------------------------------------------------------------------------------
- (void) SetGameboard :(G_Gameboard*)pGameboard
{
    m_pGameboard = pGameboard;
}
//------------------------------------------------------------------------------
- (void)Set_OnPlayed :(id)pObject :(SEL)pDelegate
{
    // no gameboard defined?
    if (!m_pGameboard)
        return;

    // set delegate callback
    m_pOnPlayedObject   = pObject;
    m_pOnPlayedDelegate = pDelegate;

    // set gameboard callback function
    m_pGameboard->Set_OnPlayed(G_Notifier::OnPlayed);
}
//------------------------------------------------------------------------------
bool Call_OnPlayedFrom(void* pSelf, G_Gameboard::IEPlayer player, G_Gameboard::IEPawn pawn, bool isComputer)
{
    // no notifier defined?
    if (!pSelf)
        return false;

    // call objective-c method using objective-c syntax
    return [(id)pSelf Call_OnPlayed :player :pawn :isComputer];
}
//------------------------------------------------------------------------------
- (bool) Call_OnPlayed :(G_Gameboard::IEPlayer)player :(G_Gameboard::IEPawn)pawn :(bool)isComputer
{
    // are callback objects correctly initialized?
    if (!m_pOnPlayedObject || !m_pOnPlayedDelegate)
        return false;

    // populate callback parameters
    G_OnPlayedParam* pParam = [[[G_OnPlayedParam alloc]init]autorelease];
    pParam.m_Player         = player;
    pParam.m_Pawn           = pawn;
    pParam.m_IsComputer     = isComputer;

    // call OnPlayed callback
    return [m_pOnPlayedObject performSelector:m_pOnPlayedDelegate withObject:pParam];
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
