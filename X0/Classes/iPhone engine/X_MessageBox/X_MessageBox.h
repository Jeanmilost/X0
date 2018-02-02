/*****************************************************************************
 * ==> X_MessageBox ---------------------------------------------------------*
 * ***************************************************************************
 * Description : Some tools to display message to user                       *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

#import <Foundation/Foundation.h>

/**
* Some tools to display message to user
*@author Jean-Milost Reymond
*/
@interface X_MessageBox : UIViewController<UIAlertViewDelegate>
{}

/**
* Displays a message box to the user
*@param pTitle - title of the box
*@param pMessage - message to display to user
*/
+ (void)DisplayError :(NSString*)pTitle :(NSString*)pMessage;

/**
* Displays a message box to the user, quit application when user clicks on OK
*@param pTitle - title of the box
*@param pMessage - message to display to user
*/
+ (void)DisplayErrorAndQuit :(NSString*)pTitle :(NSString*)pMessage;

@end
