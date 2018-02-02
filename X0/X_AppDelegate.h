/******************************************************************************
 * ==> X_AppDelegate ---------------------------------------------------------*
 ******************************************************************************
 * Description : X0 application delegate                                      *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <UIKit/UIKit.h>
#import "X_Logger_HTML_iPhone.h"

@class X_ViewController;

/**
* X0 application delegate
*@author Jean-Milost Reymond
*/
@interface X_AppDelegate : UIResponder <UIApplicationDelegate>
{}

@property (strong, nonatomic) UIWindow*         m_pWindow;
@property (strong, nonatomic) X_ViewController* m_pViewController;

@end
