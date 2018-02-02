/******************************************************************************
 * ==> E_CollidableObject_2D -------------------------------------------------*
 ******************************************************************************
 * Description : basic 2D collidable object                                   *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#ifndef E_COLLIDABLEOBJECT_2D_H
#define E_COLLIDABLEOBJECT_2D_H

#include "E_Vector2D.h"

/**
* Basic 2D collidable object
*@author Jean-Milost Reymond
*/
class E_CollidableObject_2D
{
    public:
        /**
        * Constructor
        */
        E_CollidableObject_2D();

        /**
        * Destructor
        */
        virtual ~E_CollidableObject_2D();

        /**
        * Check if a point is inside object
        *@param x - point x coordinate
        *@param y - point y coordinate
        *@returns true if point is inside object, otherwise false
        */
        virtual bool Inside(const float& x, const float& y) const = 0;

        /**
        * Check if a point is inside object
        *@param point - point coordinate
        *@returns true if point is inside object, otherwise false
        */
        virtual bool Inside(const E_Vector2D& point) const = 0;

        /**
        * Check if object intersects with another object
        *@param other - other object to check
        *@returns true if objects intersect, otherwise false
        */
        virtual bool Intersect(const E_CollidableObject_2D* pOther) const = 0;
};

#endif // E_COLLIDABLEOBJECT_2D_H
