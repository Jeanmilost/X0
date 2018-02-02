/******************************************************************************
 * ==> E_Rectangle -----------------------------------------------------------*
 ******************************************************************************
 * Description : 2D rectangle                                                 *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#include "E_Rectangle.h"
#include "E_Exception.h"
#include <memory>

//------------------------------------------------------------------------------
// Class E_Rectangle - c++ class
//------------------------------------------------------------------------------
E_Rectangle::E_Rectangle()
{
    m_Left   = 0.0f;
    m_Top    = 0.0f;
    m_Right  = 0.0f;
    m_Bottom = 0.0f;
}
//------------------------------------------------------------------------------
E_Rectangle::E_Rectangle(const float& left,
                         const float& top,
                         const float& right,
                         const float& bottom)
{
    m_Left   = left;
    m_Top    = top;
    m_Right  = right;
    m_Bottom = bottom;
}
//------------------------------------------------------------------------------
E_Rectangle::E_Rectangle(const float& x,
                         const float& y,
                         const float& width,
                         const float& height,
                         bool  fake)
{
    m_Left   = x;
    m_Top    = y;
    m_Right  = m_Left + width;
    m_Bottom = m_Top + height;
}
//------------------------------------------------------------------------------
bool E_Rectangle::Inside(const float& x, const float& y) const
{
    return Inside(E_Vector2D(x, y));
}
//------------------------------------------------------------------------------
bool E_Rectangle::Inside(const E_Vector2D& point) const
{
    return (point.m_X >= m_Left                        &&
            point.m_Y >= m_Top                         &&
            point.m_X <= (m_Left + (m_Right - m_Left)) &&
            point.m_Y <= (m_Top + (m_Bottom - m_Top)));
}
//------------------------------------------------------------------------------
bool E_Rectangle::Intersect(const E_CollidableObject_2D* pOther) const
{
    const E_Rectangle* pRect = dynamic_cast<const E_Rectangle*>(pOther);

    if (!pRect)
        M_THROW_EXCEPTION("Intersect - could not convert other object to rectangle");

    return !(m_Left > pRect->m_Right || m_Right < pRect->m_Left ||
                m_Top > pRect->m_Bottom || m_Bottom < pRect->m_Top);
}
//------------------------------------------------------------------------------
