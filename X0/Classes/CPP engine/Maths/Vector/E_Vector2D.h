/******************************************************************************
 * ==> E_Vector2D ------------------------------------------------------------*
 ******************************************************************************
 * Description : Euclidean vector 2D                                          *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#ifndef E_VECTOR2D_H
#define E_VECTOR2D_H

#ifdef USING_DIRECTX
    #include <d3dx9math.h>
#endif

/**
* Vector 2D
*@author Jean-Milost Reymond
*/
class E_Vector2D
{
    public:
        float m_X; // x coordinate for the 2D vector
        float m_Y; // y coordinate for the 2D vector

        /**
		* Constructor
		*/
        E_Vector2D();

        /**
		* Constructor
		*@param x - vector x value
		*@param y - vector y value
		*/
        E_Vector2D(const float& x, const float& y);

        #ifdef USING_DIRECTX
            /**
            * Constructor
            *@param d3dxVector - Direct3D vector
            */
            E_Vector2D(const D3DXVECTOR2& d3dxVector);
        #endif

        /**
		* Operator +
		*@param other - other vector to add
		*@returns resulting added vector
		*/
        E_Vector2D operator + (const E_Vector2D& other) const;

        /**
        * Operator -
        *@returns inverted vector
        */
        E_Vector2D operator - () const;

        /**
		* Operator -
		*@param other - other vector to substract
		*@returns resulting substracted vector
		*/
        E_Vector2D operator - (const E_Vector2D& other) const;

        /**
        * Operator *
        *@param other - other vector to multiply
        *@returns resulting multiplicated vector
        */
        E_Vector2D operator * (const E_Vector2D& other) const;

        /**
        * Operator /
        *@param other - other vector to divide
        *@returns resulting divided vector
        */
        E_Vector2D operator / (const E_Vector2D& other) const;

        /**
		* Operator +=
		*@param other - other vector to add
		*@returns resulting added vector
		*/
        const E_Vector2D& operator += (const E_Vector2D& other);

        /**
		* Operator -=
		*@param other - other vector to substract
		*@returns resulting substracted vector
		*/
        const E_Vector2D& operator -= (const E_Vector2D& other);

        /**
        * Operator *=
        *@param other - other vector to multiply
        *@returns resulting multiplicated vector
        */
        const E_Vector2D& operator *= (const E_Vector2D& other);

        /**
        * Operator -=
        *@param other - other vector to divide
        *@returns resulting divided vector
        */
        const E_Vector2D& operator /= (const E_Vector2D& other);

        /**
		* Operator ==
		*@param other - other vector to compare
		*@returns true if vectors are identical, otherwise false
		*/
        bool operator == (const E_Vector2D& other) const;

        /**
		* Operator !=
		*@param other - other vector to compare
		*@returns true if vectors are not identical, otherwise false
		*/
        bool operator != (const E_Vector2D& other) const;

        /**
        * Gets the vector length
        *@returns the vector length
        */
        float Length() const;

        /**
        * Normalizes the vector
        *@returns normalized vector
        */
        E_Vector2D Normalize() const;

        /**
        * Calculates the cross product between 2 vectors
        *@param vector - vector with which cross product is calculated
        *@returns cross product
        */
        E_Vector2D Cross(const E_Vector2D& vector) const;

        /**
        * Calculates the dot product between 2 vectors
        *@param vector - vector with which dot product is calculated
        *@returns dot product
        */
        float Dot(const E_Vector2D& vector) const;

        #ifdef USING_DIRECTX
            /**
            * Convert to Direct3D vector
            *@returns Direct3D vector
            */
            D3DXVECTOR2 ToD3DXVector2() const;
        #endif
};

#endif // E_VECTOR2D_H
