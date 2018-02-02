/******************************************************************************
 * ==> X_BasicColorBlender ---------------------------------------------------*
 ******************************************************************************
 * Description : Basic Color blender (iterate through min and max color)      *
 * Developer   : Jean-Milost Reymond                                          *
 ******************************************************************************/

#import <Foundation/Foundation.h>

/**
* Basic color blender, used to iterate through a min and a max color
*@author Jean-Milost Reymond
*/
@interface X_BasicColorBlender : NSObject
{
    @private
        float m_MinR;
        float m_MinG;
        float m_MinB;
        float m_MinA;
        float m_MaxR;
        float m_MaxG;
        float m_MaxB;
        float m_MaxA;
        float m_ColorR;
        float m_ColorG;
        float m_ColorB;
        float m_ColorA;
        float m_Offset;
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
* Sets initial color
*@param red - red value in percent (from 0.0f to 1.0f)
*@param green - green value in percent (from 0.0f to 1.0f)
*@param blue - blue value in percent (from 0.0f to 1.0f)
*@param alpha - alpha value in percent (from 0.0f to 1.0f)
*/
- (void) SetInitialColor :(const float&)red :(const float&)green :(const float&)blue :(const float&)alpha;

/**
* Sets minimum color
*@param red - red value in percent (from 0.0f to 1.0f)
*@param green - green value in percent (from 0.0f to 1.0f)
*@param blue - blue value in percent (from 0.0f to 1.0f)
*@param alpha - alpha value in percent (from 0.0f to 1.0f)
*/
- (void) SetMin :(const float&)red :(const float&)green :(const float&)blue :(const float&)alpha;

/**
* Sets maximum color
*@param red - red value in percent (from 0.0f to 1.0f)
*@param green - green value in percent (from 0.0f to 1.0f)
*@param blue - blue value in percent (from 0.0f to 1.0f)
*@param alpha - alpha value in percent (from 0.0f to 1.0f)
*/
- (void) SetMax :(const float&)red :(const float&)green :(const float&)blue :(const float&)alpha;

/**
* Sets offset (i.e. blend velocity and direction)
*@param value - offset value, from min to max if positive, from max to min if negative
*/
- (void) SetOffset :(const float&)value;

/**
* Gets current color
*@returns color
*/
- (UIColor*) GetColor;

/**
* Gets current color alpha value
*@returns alpha
*/
- (float) GetAlpha;

/**
* Blends color
*@returns true if next blend cycle begins, otherwise false
*/
- (bool) Blend;

@end
