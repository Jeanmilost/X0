/******************************************************************************
 * ==> G_GameNotifier --------------------------------------------------------*
 ******************************************************************************
 * Description : Game notifier, used to convert messages from game engine to  *
 *               high level objective-c classes                               *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <Foundation/Foundation.h>
#include "G_Gameboard.h"

/**
* Cpp notifier
*@author Jean-Milost Reymond
*/
struct G_Notifier
{
    static void* m_pGameNotifier;

    /**
    * Called when a player has played
    *@param player - player
    *@param pawn - pawn used by player
    *@param isComputer - if true, player is computer
    *@returns true if game should continue, false if game should be stopped
    */
    static bool OnPlayed(G_Gameboard::IEPlayer player, G_Gameboard::IEPawn pawn, bool isComputer);
};

/**
* OnPlayed function parameters
*@author Jean-Milost Reymond
*/
@interface G_OnPlayedParam : NSObject
{
    @private
        G_Gameboard::IEPlayer m_Player;
        G_Gameboard::IEPawn   m_Pawn;
        bool                  m_IsComputer;
}

@property G_Gameboard::IEPlayer m_Player;
@property G_Gameboard::IEPawn   m_Pawn;
@property bool                  m_IsComputer;

@end

/**
* Objective-c notifier
*@author Jean-Milost Reymond
*/
@interface G_GameNotifier : NSObject
{
    @private
        G_Gameboard* m_pGameboard;
        id           m_pOnPlayedObject;
        SEL          m_pOnPlayedDelegate;
}

/**
* Initializes class
*/
- (id)init;

/**
* Releases class resources
*/
- (void)dealloc;

/**
* Set gameboard
*@param pGameboard - gameboard
*/
- (void) SetGameboard :(G_Gameboard*)pGameboard;

/**
* Sets OnPlayed delegate
*@param pObject - function owner object
*@param pDelegate - function to delegate
*/
- (void)Set_OnPlayed :(id)pObject :(SEL)pDelegate;

/**
* Called when OnPlayed is called from c++
*@param pSelf - self pointer used by c++
*@param player - player
*@param pawn - pawn used by player
*@param isComputer - if true, player is computer
*@returns true if game should continue, false if game should be stopped
*/
bool Call_OnPlayedFrom(void* pSelf, G_Gameboard::IEPlayer player, G_Gameboard::IEPawn pawn, bool isComputer);

/**
* Calls OnPlayed delegate
*@param player - player
*@param pawn - pawn used by player
*@param isComputer - if true, player is computer
*@returns true if game should continue, false if game should be stopped
*/
- (bool) Call_OnPlayed :(G_Gameboard::IEPlayer)player :(G_Gameboard::IEPawn)pawn :(bool)isComputer;

@end
