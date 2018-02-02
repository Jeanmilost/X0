/******************************************************************************
 * ==> X_AppDelegate ---------------------------------------------------------*
 ******************************************************************************
 * Description : X0 application delegate                                      *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "X_AppDelegate.h"
#import "X_ViewController.h"

//------------------------------------------------------------------------------
@implementation X_AppDelegate
//------------------------------------------------------------------------------
@synthesize m_pWindow         = _window;
@synthesize m_pViewController = _viewController;
//------------------------------------------------------------------------------
- (void)dealloc
{
    [_window release];
    [_viewController release];
    [super dealloc];
}
//------------------------------------------------------------------------------
- (BOOL) application :(UIApplication*)application didFinishLaunchingWithOptions:(NSDictionary*)pLaunchOptions
{
    #ifdef DEBUG
        // open logger as soon as possible
        [X_Logger_HTML_iPhone Open];
    #endif

    // create windows object
    self.m_pWindow = [[[UIWindow alloc] initWithFrame:[[UIScreen mainScreen] bounds]] autorelease];

    // create view controller
    self.m_pViewController = [[[X_ViewController alloc] initWithNibName:@"X_ViewController"
                                                                 bundle:nil] autorelease];

    // assign view controller to window
    self.m_pWindow.rootViewController = self.m_pViewController;
    [self.m_pWindow makeKeyAndVisible];

    return YES;
}
//------------------------------------------------------------------------------
- (void) applicationWillResignActive :(UIApplication*)pApplication
{
    /*
    Sent when the application is about to move from active to inactive state. This can occur for certain types 
    of temporary interruptions (such as an incoming phone call or SMS message) or when the user quits the 
    application and it begins the transition to the background state. Use this method to pause ongoing tasks, 
    disable timers, and throttle down OpenGL ES frame rates. Games should use this method to pause the game.
    */
    #ifdef DEBUG
        [X_Logger_HTML_iPhone Save];
    #endif
}
//------------------------------------------------------------------------------
- (void) applicationDidEnterBackground :(UIApplication*)pApplication
{
    /*
    Use this method to release shared resources, save user data, invalidate timers, and store enough
    application state information to restore your application to its current state in case it is terminated 
    later. If your application supports background execution, this method is called instead of 
    applicationWillTerminate: when the user quits.
    */
    #ifdef DEBUG
        [X_Logger_HTML_iPhone Save];
    #endif
}
//------------------------------------------------------------------------------
- (void) applicationWillEnterForeground :(UIApplication*)pApplication
{
    /*
    Called as part of the transition from the background to the inactive state; here you can undo many of
    the changes made on entering the background.
    */
    #ifdef DEBUG
        [X_Logger_HTML_iPhone Open];
    #endif
}
//------------------------------------------------------------------------------
- (void) applicationDidBecomeActive :(UIApplication*)pApplication
{
    /*
    Restart any tasks that were paused (or not yet started) while the application was inactive.
    If the application was previously in the background, optionally refresh the user interface.
    */
    #ifdef DEBUG
        [X_Logger_HTML_iPhone Open];
    #endif
}
//------------------------------------------------------------------------------
- (void) applicationWillTerminate:(UIApplication*)pApplication
{
    /*
    Called when the application is about to terminate.
    Save data if appropriate.
    See also applicationDidEnterBackground:.
    */
    #ifdef DEBUG
        [X_Logger_HTML_iPhone Save];
    #endif
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
