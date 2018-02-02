/******************************************************************************
 * ==> E_Rectangle -----------------------------------------------------------*
 ******************************************************************************
 * Description : 2D rectangle                                                 *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#ifndef E_RECTANGLE_H
#define E_RECTANGLE_H

#include "E_CollidableObject_2D.h"

/**
* Rectangle
*@author Jean-Milost Reymond
*/
class E_Rectangle : public E_CollidableObject_2D
{
    public:
        float m_Left;   // rect left coordinate
        float m_Top;    // rect top coordinate
        float m_Right;  // rect right coordinate
        float m_Bottom; // rect bottom coortinate

        /**
        * Constructor
        */
        E_Rectangle();

        /**
        * Constructor
        *@param left - rectangle left corner
        *@param top - rectangle top corner
        *@param right - rectangle right corner
        *@param bottom - rectangle bottom corner
        */
        E_Rectangle(const float& left,
                    const float& top,
                    const float& right,
                    const float& bottom);

        /**
        * Constructor
        *@param x - x coordinate
        *@param y - y coordinate
        *@param width - rectangle width
        *@param height - rectangle height
        *@param fake - fake value to make difference between constructors
        */
        E_Rectangle(const float& x,
                    const float& y,
                    const float& width,
                    const float& height,
                    bool  fake);

        /**
        * Check if a point is inside rectangle
        *@param x - point x coordinate
        *@param y - point y coordinate
        *@returns true if point is inside rectangle, otherwise false
        */
        virtual bool Inside(const float& x, const float& y) const;

        /**
        * Check if a point is inside rectangle
        *@param point - point coordinate
        *@returns true if point is inside rectangle, otherwise false
        */
        virtual bool Inside(const E_Vector2D& point) const;

        /**
        * Check if rectangle intersects with another rectangle
        *@param other - other rectangle to check
        *@returns true if rectangles intersect, otherwise false
        */
        virtual bool Intersect(const E_CollidableObject_2D* pOther) const;
};

#endif // E_RECTANGLE_H
