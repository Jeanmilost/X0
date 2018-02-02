/******************************************************************************
 * ==> X_Logger_HTML ---------------------------------------------------------*
 ******************************************************************************
 * Description : Write logs in HTML file, wrapper around C++ HTML logger      *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <Foundation/Foundation.h>
#include "E_Logger_HTML.h"

/**
* Log application events to HTML file, wrapper around C++ E_Logger_HTML class
*@author Jean-Milost Reymond
*/
@interface X_Logger_HTML_iPhone : NSObject
{}

/**
* Opens logger
*/
+ (void)Open;

/**
* Save log content to HTML file
*/
+ (void)Save;

/**
* Builds log file name
*@returns name
 */
+ (NSString*) BuildFileName;

@end
