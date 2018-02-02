/******************************************************************************
 * ==> X_LabelColorBlender ---------------------------------------------------*
 ******************************************************************************
 * Description : Color blender for label controls                             *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "X_LabelColorBlender.h"
#import "X_Macros.h"
#include <complex>

//------------------------------------------------------------------------------
@implementation X_LabelColorBlender
//------------------------------------------------------------------------------
- (id)init
{
    m_Index = 0;

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

        m_Index = 0;
        m_Labels.clear();
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) AddLabel :(UILabel*)pLabel
{
    M_Try
    {
        m_Labels.push_back(pLabel);
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (UILabel*) GetLabel
{
    M_Try
    {
        // labels to blend?
        if (!m_Labels.size())
            return nil;

        // label index is out of bounds?
        if (m_Index >= m_Labels.size())
            return nil;

        // get current label
        return m_Labels[m_Index];
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (bool) Blend
{
    M_Try
    {
        // labels to blend?
        if (!m_Labels.size())
            return false;

        bool nextCycle = false;

        // blend color and check if next cycle began
        if ([super Blend])
        {
            nextCycle = true;

            // get next lable
            ++m_Index;
        }

        // is index out of bounds?
        if (m_Index >= m_Labels.size())
            // reinitialize
            m_Index = 0;

        // get label to blend
        UILabel* pLabel = m_Labels[m_Index];
        M_ASSERT(pLabel);

        // change label color
        pLabel.textColor = [self GetColor];

        return nextCycle;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
