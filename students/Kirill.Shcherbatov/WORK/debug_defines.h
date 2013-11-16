//{==================================================================================================
//! @file "defines.h"
//! @date 2013-11-09
//! @mainpage Header with important deffines declaration
//! @author Kirill Shcherbatov <kshcherbatov@gmail.com>
//! @version 2.0
//}===================================================================================================

//****************************************************************************************************
#include <assert.h>
#include <stdio.h>
//****************************************************************************************************

//****************************************************************************************************
#ifdef DEBUG
    #define OUT printf
    #define RETURN_ASSERT( conditional, ret_value ) assert (conditional);
#else
    #define OUT if (0) printf
    #define RETURN_ASSERT( conditional, ret_value ) if (!(conditional)) return ret_value;
#endif
//****************************************************************************************************
