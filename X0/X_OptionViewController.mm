/******************************************************************************
 * ==> X_OptionViewController ------------------------------------------------*
 ******************************************************************************
 * Description : X0 game options controller                                   *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "X_OptionViewController.h"
#import "X_MessageBox.h"
#import "X_Macros.h"

//------------------------------------------------------------------------------
@implementation X_OptionViewController
//------------------------------------------------------------------------------
@synthesize m_pPlayer1Cross;
@synthesize m_pPlayer1Round;
@synthesize m_pPlayer2Cross;
@synthesize m_pPlayer2Round;
@synthesize m_pCancel;
@synthesize m_pSave;
@synthesize m_pPlayAgainstComputer;
@synthesize m_pComputerBegins;
@synthesize m_pDifficulty;
//------------------------------------------------------------------------------
- (id)initWithNibName:(NSString*)nibNameOrNil bundle:(NSBundle*)nibBundleOrNil
{
    M_Try
    {
        m_pOnOptionsChangedDelegate = nil;
        m_pOptions                  = nil;

        self = [super initWithNibName:nibNameOrNil bundle:nibBundleOrNil];

        if (self)
        {}

        return self;
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void)didReceiveMemoryWarning
{
    M_Try
    {
        [super didReceiveMemoryWarning];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void)viewDidLoad
{
    M_Try
    {
        [super viewDidLoad];

        // are options defined?
        if (m_pOptions)
        {
            // apply loaded options to interface
            m_pPlayer1Cross.selected           = (m_pOptions.m_Player1Pawn == G_Gameboard::IE_Pa_Cross);
            m_pPlayer1Round.selected           = !m_pPlayer1Cross.selected;
            m_pPlayer2Cross.selected           = !m_pPlayer1Cross.selected;
            m_pPlayer2Round.selected           = !m_pPlayer2Cross.selected;
            m_pPlayAgainstComputer.on          = m_pOptions.m_PlayAgainstComputer;
            m_pComputerBegins.on               = m_pOptions.m_ComputerBegins;
            m_pDifficulty.selectedSegmentIndex = m_pOptions.m_AILevel;
        }
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void)viewDidUnload
{
    M_Try
    {
        [super viewDidUnload];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (BOOL)shouldAutorotateToInterfaceOrientation:(UIInterfaceOrientation)interfaceOrientation
{
    M_Try
    {
        // allow only portrait orientations
        return (interfaceOrientation == UIInterfaceOrientationPortrait);
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) SetGameOptions :(G_GameOptions*)pOptions
{
    m_pOptions = pOptions;
}
//------------------------------------------------------------------------------
- (void) Set_OnOptionsChanged_Delegate :(id)pObject :(SEL)pDelegate
{
    M_Try
    {
        // create delegate to call OnQRCodeEntered event on parent
        m_pOnOptionsChangedDelegate = [[X_Delegate alloc]init];
        [m_pOnOptionsChangedDelegate Set :pObject :pDelegate];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (IBAction) OnPlayer1CrossClicked :(id)sender
{
    M_Try
    {
        m_pPlayer1Cross.selected = YES;
        m_pPlayer1Round.selected = NO;
        m_pPlayer2Cross.selected = NO;
        m_pPlayer2Round.selected = YES;

        // options are defined?
        if (m_pOptions)
        {
            // update options to save
            m_pOptions.m_Player1Pawn = G_Gameboard::IE_Pa_Cross;
            m_pOptions.m_Player2Pawn = G_Gameboard::IE_Pa_Round;
        }
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (IBAction) OnPlayer1RoundClicked :(id)sender
{
    M_Try
    {
        m_pPlayer1Cross.selected = NO;
        m_pPlayer1Round.selected = YES;
        m_pPlayer2Cross.selected = YES;
        m_pPlayer2Round.selected = NO;

        // options are defined?
        if (m_pOptions)
        {
            // update options to save
            m_pOptions.m_Player1Pawn = G_Gameboard::IE_Pa_Round;
            m_pOptions.m_Player2Pawn = G_Gameboard::IE_Pa_Cross;
        }
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (IBAction) OnPlayer2CrossClicked :(id)sender
{
    M_Try
    {
        m_pPlayer1Cross.selected = NO;
        m_pPlayer1Round.selected = YES;
        m_pPlayer2Cross.selected = YES;
        m_pPlayer2Round.selected = NO;

        // options are defined?
        if (m_pOptions)
        {
            // update options to save
            m_pOptions.m_Player1Pawn = G_Gameboard::IE_Pa_Round;
            m_pOptions.m_Player2Pawn = G_Gameboard::IE_Pa_Cross;
        }
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (IBAction) OnPlayer2RoundClicked :(id)sender
{
    M_Try
    {
        m_pPlayer1Cross.selected = YES;
        m_pPlayer1Round.selected = NO;
        m_pPlayer2Cross.selected = NO;
        m_pPlayer2Round.selected = YES;

        // options are defined?
        if (m_pOptions)
        {
            // update options to save
            m_pOptions.m_Player1Pawn = G_Gameboard::IE_Pa_Cross;
            m_pOptions.m_Player2Pawn = G_Gameboard::IE_Pa_Round;
        }
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (IBAction) OnCancelClicked :(id)sender
{
    M_Try
    {
        // close login view
        [self dismissModalViewControllerAnimated:YES];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (IBAction) OnSaveClicked :(id)sender
{
    M_Try
    {
        // options are defined?
        if (m_pOptions)
        {
            // update options to save
            m_pOptions.m_PlayAgainstComputer = m_pPlayAgainstComputer.on;
            m_pOptions.m_ComputerBegins      = m_pComputerBegins.on;
            m_pOptions.m_AILevel             = m_pDifficulty.selectedSegmentIndex;

            // save user options
            if (![m_pOptions Save])
                [X_MessageBox DisplayError :@"Error" :NSLocalizedString(@"option_save_failed", 
                                                                        @"Failed to save options")];
        }

        // call OnQRCodeEntered delegate
        if (m_pOnOptionsChangedDelegate)
            [m_pOnOptionsChangedDelegate Call];

        // close login view
        [self dismissModalViewControllerAnimated:YES];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
