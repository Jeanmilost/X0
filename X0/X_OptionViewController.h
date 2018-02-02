/******************************************************************************
 * ==> X_OptionViewController ------------------------------------------------*
 ******************************************************************************
 * Description : X0 game options controller                                   *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <UIKit/UIKit.h>
#import "X_Delegate.h"
#import "G_GameOptions.h"

@interface X_OptionViewController : UIViewController
{
    @private
        UIButton*      m_pPlayer1Cross;
        UIButton*      m_pPlayer1Round;
        UIButton*      m_pPlayer2Cross;
        UIButton*      m_pPlayer2Round;
        UIButton*      m_pCancel;
        UIButton*      m_pSave;
        UISwitch*      m_pPlayAgainstComputer;
        UISwitch*      m_pComputerBegins;
        UISlider*      m_pDifficulty;
        X_Delegate*    m_pOnOptionsChangedDelegate;
        G_GameOptions* m_pOptions;
}

@property (nonatomic, retain) IBOutlet UIButton* m_pPlayer1Cross;
@property (nonatomic, retain) IBOutlet UIButton* m_pPlayer1Round;
@property (nonatomic, retain) IBOutlet UIButton* m_pPlayer2Cross;
@property (nonatomic, retain) IBOutlet UIButton* m_pPlayer2Round;
@property (nonatomic, retain) IBOutlet UIButton* m_pCancel;
@property (nonatomic, retain) IBOutlet UIButton* m_pSave;
@property (nonatomic, retain) IBOutlet UISwitch* m_pPlayAgainstComputer;
@property (nonatomic, retain) IBOutlet UISwitch* m_pComputerBegins;
@property (nonatomic, retain) IBOutlet UISlider* m_pDifficulty;

/**
* Set game options
*@param pOptions - game options
*/
- (void) SetGameOptions :(G_GameOptions*)pOptions;

/**
* Set OnOptionsChanged delegate
*@param pObject - target object
*@param pDelegate - target function to callback
*/
- (void) Set_OnOptionsChanged_Delegate :(id)pObject :(SEL)pDelegate;

/**
* Called when player 1 uses cross button is clicked
*@sender - event sender
*/
- (IBAction) OnPlayer1CrossClicked :(id)sender;

/**
* Called when player 1 uses round button is clicked
*@sender - event sender
*/
- (IBAction) OnPlayer1RoundClicked :(id)sender;

/**
* Called when player 2 uses cross button is clicked
*@sender - event sender
*/
- (IBAction) OnPlayer2CrossClicked :(id)sender;

/**
* Called when player 2 uses round button is clicked
*@sender - event sender
*/
- (IBAction) OnPlayer2RoundClicked :(id)sender;

/**
* Called when cancel button is clicked
*@sender - event sender
*/
- (IBAction) OnCancelClicked :(id)sender;

/**
* Called when save button is clicked
*@sender - event sender
*/
- (IBAction) OnSaveClicked :(id)sender;

@end
