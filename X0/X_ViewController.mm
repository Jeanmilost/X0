/******************************************************************************
 * ==> X_ViewController ------------------------------------------------------*
 ******************************************************************************
 * Description : X0 application controller                                    *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "X_ViewController.h"
#import "X_OptionViewController.h"
#import "X_Macros.h"
#include <string>

//------------------------------------------------------------------------------
@implementation X_ViewController
//------------------------------------------------------------------------------
@synthesize m_pCell11;
@synthesize m_pCell12;
@synthesize m_pCell13;
@synthesize m_pCell21;
@synthesize m_pCell22;
@synthesize m_pCell23;
@synthesize m_pCell31;
@synthesize m_pCell32;
@synthesize m_pCell33;
@synthesize m_pGameResult;
@synthesize m_pReplayButton;
@synthesize m_pOptionsButton;
//------------------------------------------------------------------------------
- (void) didReceiveMemoryWarning
{
    M_Try
    {
        [super didReceiveMemoryWarning];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void) viewDidLoad
{
    M_Try
    {
        m_pOptions           = nil;
        m_pNotifier          = nil;
        m_pImageBlender      = nil;
        m_pGestureRecognizer = nil;
        m_pTimer             = nil;

        [super viewDidLoad];

        // initialize random number generator
        std::srand((unsigned)std::time(0));

        // initialize game notifier
        m_pNotifier = [[G_GameNotifier alloc]init];
        [m_pNotifier SetGameboard :&m_Gameboard];
        [m_pNotifier Set_OnPlayed:self :@selector(OnPlayed:)];

        // initialize image blender
        m_pImageBlender = [[X_ImageAlphaColorBlender alloc]init];

        // initialize game options
        m_pOptions = [[G_GameOptions alloc]init];
        [m_pOptions Load];

        self.view.UserInteractionEnabled = YES;

        // initialize gameboard
        [self ResetGameboard];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void) viewDidUnload
{
    M_Try
    {
        [super viewDidUnload];

        // timer was running?
        if (m_pTimer)
        {
            // stop it
            [m_pTimer invalidate];
            m_pTimer = nil;
        }

        // delete game options
        if (m_pOptions)
        {
            [m_pOptions release];
            m_pOptions = nil;
        }

        // is gesture recognizer defined?
        if (m_pGestureRecognizer)
        {
            // remove gesture from view
            [[self view] removeGestureRecognizer:m_pGestureRecognizer];

            // release gesture recognizer object
            [m_pGestureRecognizer release];
            m_pGestureRecognizer = nil;
        }

        // delete game notifier
        if (m_pNotifier)
        {
            [m_pNotifier release];
            m_pNotifier = nil;
        }

        // delete image blender
        if (m_pImageBlender)
        {
            [m_pImageBlender release];
            m_pImageBlender = nil;
        }
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void) viewWillAppear :(BOOL)animated
{
    M_Try
    {
        [super viewWillAppear:animated];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void) viewDidAppear :(BOOL)animated
{
    M_Try
    {
        [super viewDidAppear:animated];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void) viewWillDisappear :(BOOL)animated
{
    M_Try
    {
        [super viewWillDisappear:animated];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (void) viewDidDisappear :(BOOL)animated
{
    M_Try
    {
        [super viewDidDisappear:animated];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (BOOL) shouldAutorotateToInterfaceOrientation :(UIInterfaceOrientation)interfaceOrientation
{
    M_Try
    {
        // allow only portrait orientations
        return (interfaceOrientation == UIInterfaceOrientationPortrait);
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) RegisterGameGestureRecognizer
{
    M_Try
    {
        // is gesture recognizer defined?
        if (m_pGestureRecognizer)
        {
            // remove gesture from view
            [[self view] removeGestureRecognizer:m_pGestureRecognizer];

            // release gesture recognizer object
            [m_pGestureRecognizer release];
            m_pGestureRecognizer = nil;
        }

        // create long press gesture recognizer
        m_pGestureRecognizer = [[UILongPressGestureRecognizer alloc]initWithTarget:self
                                                                            action:@selector(OnLongPress:)];

        m_pGestureRecognizer.minimumPressDuration = 0;

        // add gesture recognizer to view
        [self.view addGestureRecognizer: m_pGestureRecognizer];
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
- (E_Rectangle) GetSensibleRect :(UIImageView*)pImageView
{
    M_Try
    {
        M_ASSERT(pImageView);

        CGRect imageFrame = pImageView.frame;

        E_Rectangle sensibleRect;
        sensibleRect.m_Left   = imageFrame.origin.x;
        sensibleRect.m_Top    = imageFrame.origin.y;
        sensibleRect.m_Right  = sensibleRect.m_Left + imageFrame.size.width;
        sensibleRect.m_Bottom = sensibleRect.m_Top  + imageFrame.size.height;

        return sensibleRect;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) ResetGameboard
{
    M_Try
    {
        // todo -cBug -oJean: when timer is stopped then reenabled, he ticks 2x mor quickly each time
        /*
        // timer was running?
        if (m_pTimer)
        {
            // stop it
            [m_pTimer invalidate];
            m_pTimer = nil;
        }
         */

        // reset gameboard object
        m_Gameboard.Reset();

        // are options available?
        if (m_pOptions)
        {
            // update game options
            m_Gameboard.SetPlayer1Pawn(m_pOptions.m_Player1Pawn);
            m_Gameboard.SetPlayer2IsComputer(m_pOptions.m_PlayAgainstComputer);
        }

        // release all images
        m_pCell11.image = nil;
        m_pCell12.image = nil;
        m_pCell13.image = nil;
        m_pCell21.image = nil;
        m_pCell22.image = nil;
        m_pCell23.image = nil;
        m_pCell31.image = nil;
        m_pCell32.image = nil;
        m_pCell33.image = nil;

        // reset image blender
        [m_pImageBlender Clear];

        // reset image alpha color
        m_pCell11.alpha = 1.0f;
        m_pCell12.alpha = 1.0f;
        m_pCell13.alpha = 1.0f;
        m_pCell21.alpha = 1.0f;
        m_pCell22.alpha = 1.0f;
        m_pCell23.alpha = 1.0f;
        m_pCell31.alpha = 1.0f;
        m_pCell32.alpha = 1.0f;
        m_pCell33.alpha = 1.0f;

        // hide game controls
        m_pGameResult.hidden    = YES;
        m_pReplayButton.hidden  = YES;
        m_pOptionsButton.hidden = YES;

        // register game gesture recognizer
        [self RegisterGameGestureRecognizer];

        // computer should begin?
        if (m_pOptions && m_pOptions.m_PlayAgainstComputer && m_pOptions.m_ComputerBegins)
            // let computer begin
            m_Gameboard.ComputerBegins();
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) RedrawGameboard
{
    M_Try
    {
        // iterate through gameboard cells
        for (unsigned i = 0; i < m_Gameboard.GetCellCount(); ++i)
        {
            // get cell
            G_Gameboard::ICell* pCell = m_Gameboard.GetCell(i);

            // found it?
            if (!pCell)
                continue;

            UIImageView* pImageView;

            // get cell to draw into
            switch (pCell->m_Y * 10 + pCell->m_X)
            {
                case 0:
                    pImageView = m_pCell11;
                    break;

                case 1:
                    pImageView = m_pCell12;
                    break;

                case 2:
                    pImageView = m_pCell13;
                    break;

                case 10:
                    pImageView = m_pCell21;
                    break;

                case 11:
                    pImageView = m_pCell22;
                    break;

                case 12:
                    pImageView = m_pCell23;
                    break;

                case 20:
                    pImageView = m_pCell31;
                    break;

                case 21:
                    pImageView = m_pCell32;
                    break;

                case 22:
                    pImageView = m_pCell33;
                    break;

                default:
                    // unknown cell
                    continue;
            }

            // draw pawn in cell
            if (pCell->m_Pawn == G_Gameboard::IE_Pa_Cross)
                [self ShowCrossPawn :pImageView];
            else
            if (pCell->m_Pawn == G_Gameboard::IE_Pa_Round)
                [self ShowRoundPawn :pImageView];
        }
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (bool) CheckGameOver
{
    M_Try
    {
        // get game result
        G_Gameboard::IEPlayer result = m_Gameboard.HasWin();

        // check if game is over
        if (!m_Gameboard.IsGameOver() && result == G_Gameboard::IE_Pl_None)
            return false;

        // call OnWin event
        [self OnShowGameResult :result];

        return true;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) ShowCrossPawn :(UIImageView*)pImageView
{
    M_Try
    {
        // load cross image from resources and show in image view
        [pImageView setImage:[UIImage imageNamed:@"cross.png"]];
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) ShowRoundPawn :(UIImageView*)pImageView
{
    M_Try
    {
        // load round image from resources and show in image view
        [pImageView setImage:[UIImage imageNamed:@"round.png"]];
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (bool) OnPlayed :(G_OnPlayedParam*)pParam
{
    [self RedrawGameboard];

    // game is over?
    if ([self CheckGameOver])
        return false;

    try
    {
        m_LockInterface = true;

        // calculate time to wait
        float time = (20.0f + (float)(std::rand() % 80)) / 100.0f;

        // wait a little time to simulate computer reflexion
        [[NSRunLoop currentRunLoop] runUntilDate:[NSDate dateWithTimeIntervalSinceNow:time]];
    }
    catch (...)
    {
        m_LockInterface = false;
        throw;
    }

    m_LockInterface = false;

    // check if game is over
    return true;
}
//------------------------------------------------------------------------------
- (void) OnShowGameResult :(G_Gameboard::IEPlayer)player;
{
    M_Try
    {
        // is gesture recognizer defined?
        if (m_pGestureRecognizer)
        {
            // remove gesture from view
            [[self view] removeGestureRecognizer:m_pGestureRecognizer];

            // release gesture recognizer object
            [m_pGestureRecognizer release];
            m_pGestureRecognizer = nil;
        }

        // search for player that wins
        switch (player)
        {
            case G_Gameboard::IE_Pl_Player1:
                m_pGameResult.text = NSLocalizedString(@"player_1_wins", @"Player 1 wins");
                break;

            case G_Gameboard::IE_Pl_Player2:
                // is player 2 computer?
                if (m_Gameboard.IsPlayer2Computer())
                    m_pGameResult.text = NSLocalizedString(@"computer_wins", @"Computer wins");
                else
                    m_pGameResult.text = NSLocalizedString(@"player_2_wins", @"Player 2 wins");

                break;

            case G_Gameboard::IE_Pl_None:
            default:
                m_pGameResult.text = NSLocalizedString(@"nobody_wins", @"Nobody wins");
                break;
        }

        // show game controls
        m_pGameResult.hidden    = NO;
        m_pReplayButton.hidden  = NO;
        m_pOptionsButton.hidden = NO;

        // clear previous result
        [m_pImageBlender Clear];

        // initialize blender colors
        [m_pImageBlender SetInitialColor :0.0f :0.0f :0.0f :1.0f];
        [m_pImageBlender SetMin :0.0f :0.0f :0.0f :0.0f];
        [m_pImageBlender SetMax :0.0f :0.0f :0.0f :1.0f];
        [m_pImageBlender SetOffset :-0.01f];

        // get win cells
        G_Gameboard::ICells winCells = m_Gameboard.GetWinCells();

        for (unsigned i = 0; i < winCells.size(); ++i)
            // get cell to draw into
            switch (winCells[i].m_Y * 10 + winCells[i].m_X)
            {
                case 0:
                    [m_pImageBlender AddImage :m_pCell11];
                    break;

                case 1:
                    [m_pImageBlender AddImage :m_pCell12];
                    break;

                case 2:
                    [m_pImageBlender AddImage :m_pCell13];
                    break;

                case 10:
                    [m_pImageBlender AddImage :m_pCell21];
                    break;

                case 11:
                    [m_pImageBlender AddImage :m_pCell22];
                    break;

                case 12:
                    [m_pImageBlender AddImage :m_pCell23];
                    break;

                case 20:
                    [m_pImageBlender AddImage :m_pCell31];
                    break;

                case 21:
                    [m_pImageBlender AddImage :m_pCell32];
                    break;

                case 22:
                    [m_pImageBlender AddImage :m_pCell33];
                    break;

                default:
                    // unknown cell
                    continue;
            }

        // todo -cBug -oJean: when timer is stopped then reenabled, he ticks 2x mor quickly each time
        if (!m_pTimer)
            // start blender animation timer
            m_pTimer = [NSTimer scheduledTimerWithTimeInterval:0.01f
                                                        target:self
                                                      selector:@selector(OnTimerTicked:)
                                                      userInfo:nil
                                                       repeats:YES];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnTimerTicked :(NSTimer*)pSender
{
    M_Try
    {
        // blender not initialized?
        if (!m_pImageBlender)
            return;

        // blend images
        [m_pImageBlender Blend];
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) OnLongPress :(UIGestureRecognizer*)pSender
{
    M_Try
    {
        // is interface locked?
        if (m_LockInterface)
            return;

        // get finger location
        CGPoint tapPoint = [pSender locationInView :nil];
        // get cell 1/1 sensible rectangle
        E_Rectangle sensibleRect = [self GetSensibleRect :m_pCell11];

        // check if finger touches cell 1/1
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell11Clicked];
            return;
        }

        // get cell 1/2 sensible rectangle
        sensibleRect = [self GetSensibleRect :m_pCell12];

        // check if finger touches cell 1/2
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell12Clicked];
            return;
        }

        // get cell 1/3 sensible rectangle
        sensibleRect = [self GetSensibleRect :m_pCell13];

        // check if finger touches cell 1/3
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell13Clicked];
            return;
        }

        // get cell 2/1 sensible rectangle
        sensibleRect = [self GetSensibleRect :m_pCell21];

        // check if finger touches cell 2/1
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell21Clicked];
            return;
        }

        // get cell 2/2 sensible rectangle
        sensibleRect = [self GetSensibleRect :m_pCell22];

        // check if finger touches cell 2/2
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell22Clicked];
            return;
        }

        // get cell 2/3 sensible rectangle
        sensibleRect = [self GetSensibleRect :m_pCell23];

        // check if finger touches cell 2/3
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell23Clicked];
            return;
        }

        // get cell 3/1 sensible rectangle
        sensibleRect = [self GetSensibleRect :m_pCell31];

        // check if finger touches cell 3/1
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell31Clicked];
            return;
        }

        // get cell 3/2 sensible rectangle
        sensibleRect = [self GetSensibleRect :m_pCell32];

        // check if finger touches cell 3/2
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell32Clicked];
            return;
        }

        // get cell 3/3 sensible rectangle
        sensibleRect = [self GetSensibleRect :m_pCell33];

        // check if finger touches cell 3/3
        if (sensibleRect.Inside(tapPoint.x, tapPoint.y))
        {
            [self OnCell33Clicked];
            return;
        }
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell11Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(0, 0);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell12Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(1, 0);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell13Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(2, 0);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell21Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(0, 1);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell22Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(1, 1);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell23Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(2, 1);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell31Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(0, 2);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell32Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(1, 2);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnCell33Clicked
{
    M_Try
    {
        m_Gameboard.SetUserMove(2, 2);
        [self RedrawGameboard];
        [self CheckGameOver];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (IBAction) OnReplayClicked :(id)sender
{
    M_Try
    {
        // reset gameboard
        [self ResetGameboard];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (IBAction) OnOptionsClicked :(id)sender
{
    M_Try
    {
        // open manual query view
        X_OptionViewController* pOptions = [[[X_OptionViewController alloc]init]autorelease];
        [pOptions SetGameOptions:m_pOptions];
        [self presentModalViewController:pOptions animated:YES];
        [pOptions Set_OnOptionsChanged_Delegate :self :@selector(OnOptionsChanged)];
    }
    M_CatchShow
}
//------------------------------------------------------------------------------
- (void) OnOptionsChanged
{
    M_Try
    {
        // are options available?
        if (m_pOptions)
        {
            // update game options
            m_Gameboard.SetPlayer1Pawn(m_pOptions.m_Player1Pawn);
            m_Gameboard.SetPlayer2IsComputer(m_pOptions.m_PlayAgainstComputer);
        }
    }
    M_CatchSilent
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
