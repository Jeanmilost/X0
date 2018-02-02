/******************************************************************************
 * ==> X_ImageAlphaColorBlender ----------------------------------------------*
 ******************************************************************************
 * Description : Image alpha color blender                                    *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <Foundation/Foundation.h>
#import "X_BasicColorBlender.h"
#include <vector>

/**
* Image alpha color blender
*@author Jean-Milost Reymond
*/
@interface X_ImageAlphaColorBlender : X_BasicColorBlender
{
    @private
        std::vector<UIImageView*> m_Images;
}

/**
* Initializes class
*/
- (id)init;

/**
* Clears all values
*/
- (void) Clear;

/**
* Adds image to modify alpha color
*@param pImage - image
*/
- (void) AddImage :(UIImageView*)pimage;

/**
* Blends image alpha color
*@returns true if next blend cycle begins, otherwise false
*/
- (bool) Blend;

@end
