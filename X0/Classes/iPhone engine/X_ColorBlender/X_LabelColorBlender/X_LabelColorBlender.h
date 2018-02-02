/******************************************************************************
 * ==> X_LabelColorBlender ---------------------------------------------------*
 ******************************************************************************
 * Description : Color blender for label controls                             *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <Foundation/Foundation.h>
#import "X_BasicColorBlender.h"
#include <vector>

/**
* Label text color blender
*@author Jean-Milost Reymond
*/
@interface X_LabelColorBlender : X_BasicColorBlender
{
    @private
        unsigned              m_Index;
        std::vector<UILabel*> m_Labels;
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
* Adds label to modify text color
*@param pLabel - label
*@note Each added label will be blended one by one, from min to max color, then from max to min color,
*      then next label. When last label is reached, loop back to first label and run again
*/
- (void) AddLabel :(UILabel*)pLabel;

/**
* Gets currently blended label
*@returns label
*/
- (UILabel*) GetLabel;

/**
* Blends label text color
*@returns true if next blend cycle begins, otherwise false
*/
- (bool) Blend;

@end
