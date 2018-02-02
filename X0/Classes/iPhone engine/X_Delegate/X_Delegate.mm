/*****************************************************************************
 * ==> X_Delegate -----------------------------------------------------------*
 * ***************************************************************************
 * Description : Basic delegate class                                        *
 * Developper  : Jean-Milost Reymond                                         *
 *****************************************************************************/

#import "X_Delegate.h"

//------------------------------------------------------------------------------
// class X_Delegate - objective c
//------------------------------------------------------------------------------
@implementation X_Delegate
//------------------------------------------------------------------------------
- (id)init
{
    m_pObject   = nil;
    m_pDelegate = nil;

    if (self = [super init])
	{}

    return self;
}
//------------------------------------------------------------------------------
- (void)dealloc
{
    [super dealloc];
}
//------------------------------------------------------------------------------
- (void)Set :(id)pObject :(SEL)pDelegate
{
    m_pObject   = pObject;
    m_pDelegate = pDelegate;
}
//------------------------------------------------------------------------------
- (void)Call
{
    if (m_pObject && m_pDelegate)
        [m_pObject performSelector:m_pDelegate];
}
//------------------------------------------------------------------------------
@end
//------------------------------------------------------------------------------