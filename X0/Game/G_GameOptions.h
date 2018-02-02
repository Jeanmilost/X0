/******************************************************************************
 * ==> G_GameOptions ---------------------------------------------------------*
 ******************************************************************************
 * Description : X0 game options                                              *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <Foundation/Foundation.h>
#include "G_Gameboard.h"

@interface G_GameOptions : NSObject
{
    @private
        G_Gameboard::IEPawn m_Player1Pawn;
        G_Gameboard::IEPawn m_Player2Pawn;
        bool                m_PlayAgainstComputer;
        bool                m_ComputerBegins;
}

@property (nonatomic, assign) G_Gameboard::IEPawn m_Player1Pawn;
@property (nonatomic, assign) G_Gameboard::IEPawn m_Player2Pawn;
@property (nonatomic, assign) bool                m_PlayAgainstComputer;
@property (nonatomic, assign) bool                m_ComputerBegins;

/**
* Initialize class
*/
- (id) init;

/**
* Load options from file
*@returns true on success, otherwise false
*/
- (bool) Load;

/**
* Save options to file
*@returns true on success, otherwise false
*/
- (bool) Save;

/**
* Build options file name
*@returns options file name
*/
- (NSString*) BuildOptionsFileName;

@end
