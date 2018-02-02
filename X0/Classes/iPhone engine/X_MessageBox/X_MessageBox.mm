/*****************************************************************************
 * ==> X_MessageBox ---------------------------------------------------------*
 * ***************************************************************************
 * Description : Some tools to display message to user                       *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

#import "X_MessageBox.h"

//------------------------------------------------------------------------------
// class X_MessageBox - objective c
//------------------------------------------------------------------------------
@implementation X_MessageBox
//------------------------------------------------------------------------------
+ (void)DisplayError :(NSString*)pTitle :(NSString*)pMessage
{
    UIAlertView* pError = [[UIAlertView alloc]initWithTitle:pTitle
                                              message:pMessage
                                              delegate:nil
                                              cancelButtonTitle:@"Ok"
                                              otherButtonTitles:nil];

    [pError show];
    [pError release];
}
//------------------------------------------------------------------------------
+ (void)DisplayErrorAndQuit :(NSString*)pTitle :(NSString*)pMessage
{
    UIAlertView* pError = [[UIAlertView alloc]initWithTitle:pTitle
                                              message:pMessage
                                              delegate:self
                                              cancelButtonTitle:@"Ok"
                                              otherButtonTitles:nil];
    
    [pError show];
    [pError release];
}
//------------------------------------------------------------------------------
+ (void)alertView:(UIAlertView*)pAlertView clickedButtonAtIndex:(NSInteger)buttonIndex
{
    ::exit(0);
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
