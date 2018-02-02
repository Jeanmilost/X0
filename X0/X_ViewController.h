/******************************************************************************
 * ==> X_ViewController ------------------------------------------------------*
 ******************************************************************************
 * Description : X0 application controller                                    *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <UIKit/UIKit.h>
#import "X_ImageAlphaColorBlender.h"
#import "G_GameNotifier.h"
#include "E_Rectangle.h"
#include "G_Gameboard.h"
#include "G_GameOptions.h"

@interface X_ViewController : UIViewController
{
    @private
        G_Gameboard                   m_Gameboard;
        G_GameOptions*                m_pOptions;
        G_GameNotifier*               m_pNotifier;
        X_ImageAlphaColorBlender*     m_pImageBlender;
        UILongPressGestureRecognizer* m_pGestureRecognizer;
        UIImageView*                  m_pCell11;
        UIImageView*                  m_pCell12;
        UIImageView*                  m_pCell13;
        UIImageView*                  m_pCell21;
        UIImageView*                  m_pCell22;
        UIImageView*                  m_pCell23;
        UIImageView*                  m_pCell31;
        UIImageView*                  m_pCell32;
        UIImageView*                  m_pCell33;
        UILabel*                      m_pGameResult;
        UIButton*                     m_pReplayButton;
        UIButton*                     m_pOptionsButton;
        NSTimer*                      m_pTimer;
        bool                          m_LockInterface;
}

@property (nonatomic, retain) IBOutlet UIImageView* m_pCell11;
@property (nonatomic, retain) IBOutlet UIImageView* m_pCell12;
@property (nonatomic, retain) IBOutlet UIImageView* m_pCell13;
@property (nonatomic, retain) IBOutlet UIImageView* m_pCell21;
@property (nonatomic, retain) IBOutlet UIImageView* m_pCell22;
@property (nonatomic, retain) IBOutlet UIImageView* m_pCell23;
@property (nonatomic, retain) IBOutlet UIImageView* m_pCell31;
@property (nonatomic, retain) IBOutlet UIImageView* m_pCell32;
@property (nonatomic, retain) IBOutlet UIImageView* m_pCell33;
@property (nonatomic, retain) IBOutlet UILabel*     m_pGameResult;
@property (nonatomic, retain) IBOutlet UIButton*    m_pReplayButton;
@property (nonatomic, retain) IBOutlet UIButton*    m_pOptionsButton;

/**
* Registers gesture recognizer used during game
*/
- (void) RegisterGameGestureRecognizer;

/**
* Get sensible rectangle from an image view
*@param pImageView - image view
*@returns sensible rectangle
*/
- (E_Rectangle) GetSensibleRect :(UIImageView*)pImageView;

/**
* Reset gameboard to default
*/
- (void) ResetGameboard;

/**
* Redraw gameboard
*/
- (void) RedrawGameboard;

/**
* Check if game is over, show result if yes
*@returns true if game is over, otherwise false
*/
- (bool) CheckGameOver;

/**
* Show cross pawn in image view
*@param pImageView - image view
*/
- (void) ShowCrossPawn :(UIImageView*)pImageView;

/**
* Show round pawn in image view
*@param pImageView - image view
*/
- (void) ShowRoundPawn :(UIImageView*)pImageView;

/**
* Called when a player has played
*@param pParam - callback parameters
*@returns true if game should continue, false if game should be stopped
*/
- (bool) OnPlayed :(G_OnPlayedParam*)pParam;

/**
* Called when game result should be shown
*@param player - player who has won, IE_Pl_None if nobody won
*/
- (void) OnShowGameResult :(G_Gameboard::IEPlayer)player;

/**
* Called when timer has ticked
*@param pSender - event sender
*/
- (void) OnTimerTicked :(NSTimer*)pSender;

/**
* Called when user has pressed the screen
*@param pSender - event sender
*/
- (void) OnLongPress :(UIGestureRecognizer*)pSender;

/**
* Called when gameboard cell is pressed
*/
- (void) OnCell11Clicked;
- (void) OnCell12Clicked;
- (void) OnCell13Clicked;
- (void) OnCell21Clicked;
- (void) OnCell22Clicked;
- (void) OnCell23Clicked;
- (void) OnCell31Clicked;
- (void) OnCell32Clicked;
- (void) OnCell33Clicked;

/**
* Called when replay button is clicked
*@sender - event sender
*/
- (IBAction) OnReplayClicked :(id)sender;

/**
* Called when options button is clicked
*@sender - event sender
*/
- (IBAction) OnOptionsClicked :(id)sender;

/**
* Called when options were changed
*/
- (void) OnOptionsChanged;

@end
