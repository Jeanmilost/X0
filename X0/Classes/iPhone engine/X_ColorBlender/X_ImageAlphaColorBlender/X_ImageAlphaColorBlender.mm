/******************************************************************************
 * ==> X_ImageAlphaColorBlender ----------------------------------------------*
 ******************************************************************************
 * Description : Image alpha color blender                                    *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "X_ImageAlphaColorBlender.h"
#import "X_Macros.h"
#include <complex>

//------------------------------------------------------------------------------
@implementation X_ImageAlphaColorBlender
//------------------------------------------------------------------------------
- (id)init
{
    if (self = [super init])
	{}
    
    return self;
}
//------------------------------------------------------------------------------
- (void) Clear
{
    M_Try
    {
        // clear parent class content
        [super Clear];

        m_Images.clear();
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) AddImage :(UIImageView*)pImage
{
    M_Try
    {
        m_Images.push_back(pImage);
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (bool) Blend
{
    M_Try
    {
        // images to blend?
        if (!m_Images.size())
            return false;

        // blend color and check if next cycle began
        bool nextCycle = [super Blend];

        // iterate through images
        for (unsigned i = 0; i < m_Images.size(); ++i)
            // set image alpha value
            m_Images[i].alpha = [self GetAlpha];

        return nextCycle;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
