/******************************************************************************
 * ==> X_BasicColorBlender ---------------------------------------------------*
 ******************************************************************************
 * Description : Basic Color blender (iterate through min and max color)      *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import "X_BasicColorBlender.h"
#import "X_Macros.h"

//------------------------------------------------------------------------------
@implementation X_BasicColorBlender
//------------------------------------------------------------------------------
- (id)init
{
    m_MinR   = 0.0f;
    m_MinG   = 0.0f;
    m_MinB   = 0.0f;
    m_MinA   = 0.0f;
    m_MaxR   = 0.0f;
    m_MaxG   = 0.0f;
    m_MaxB   = 0.0f;
    m_MaxA   = 0.0f;
    m_ColorR = 0.0f;
    m_ColorG = 0.0f;
    m_ColorB = 0.0f;
    m_ColorA = 0.0f;
    m_Offset = 0.0f;

    if (self = [super init])
	{}
    
    return self;
}
//------------------------------------------------------------------------------
- (void) Clear
{
    M_Try
    {
        m_MinR   = 0.0f;
        m_MinG   = 0.0f;
        m_MinB   = 0.0f;
        m_MinA   = 0.0f;
        m_MaxR   = 0.0f;
        m_MaxG   = 0.0f;
        m_MaxB   = 0.0f;
        m_MaxA   = 0.0f;
        m_ColorR = 0.0f;
        m_ColorG = 0.0f;
        m_ColorB = 0.0f;
        m_ColorA = 0.0f;
        m_Offset = 0.0f;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) SetInitialColor :(const float&)red :(const float&)green :(const float&)blue :(const float&)alpha
{
    M_Try
    {
        m_ColorR = red;
        m_ColorG = green;
        m_ColorB = blue;
        m_ColorA = alpha;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) SetMin :(const float&)red :(const float&)green :(const float&)blue :(const float&)alpha
{
    M_Try
    {
        m_MinR = red;
        m_MinG = green;
        m_MinB = blue;
        m_MinA = alpha;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) SetMax :(const float&)red :(const float&)green :(const float&)blue :(const float&)alpha
{
    M_Try
    {
        m_MaxR = red;
        m_MaxG = green;
        m_MaxB = blue;
        m_MaxA = alpha;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (void) SetOffset :(const float&)value
{
    M_Try
    {
        m_Offset = value;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (UIColor*) GetColor
{
    M_Try
    {
        // get current color
        return [UIColor colorWithRed:m_ColorR green:m_ColorG blue:m_ColorB alpha:m_ColorA];
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (float) GetAlpha
{
    M_Try
    {
        // get current color
        return m_ColorA;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
- (bool) Blend
{
    M_Try
    {
        // calculate next label color components
        m_ColorR += m_Offset * (m_MaxR - m_MinR);
        m_ColorG += m_Offset * (m_MaxG - m_MinG);
        m_ColorB += m_Offset * (m_MaxB - m_MinB);
        m_ColorA += m_Offset * (m_MaxA - m_MinA);

        // is blend limit reached?
        if ((m_ColorR < std::min(m_MinR, m_MaxR)  ||
             m_ColorG < std::min(m_MinG, m_MaxG)  ||
             m_ColorB < std::min(m_MinB, m_MaxB)  ||
             m_ColorA < std::min(m_MinA, m_MaxA)) ||
            (m_ColorR > std::max(m_MinR, m_MaxR)  ||
             m_ColorG > std::max(m_MinG, m_MaxG)  ||
             m_ColorB > std::max(m_MinB, m_MaxB)  ||
             m_ColorA > std::max(m_MinA, m_MaxA)))
        {
            // is min or max color reached?
            if (m_Offset < 0.0f)
            {
                // min reached, update colors and invert offset
                m_ColorR = m_MinR;
                m_ColorG = m_MinG;
                m_ColorB = m_MinB;
                m_ColorA = m_MinA;
                m_Offset = -m_Offset;

                // next cycle begins
                return true;
            }
            else
            {
                // max reached, update colors and invert offset
                m_ColorR = m_MaxR;
                m_ColorG = m_MaxG;
                m_ColorB = m_MaxB;
                m_ColorA = m_MaxA;
                m_Offset = -m_Offset;
            }
        }

        return false;
    }
    M_CatchTrace
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------
