#ifndef CH_APISUBSYS_H
#define CH_APISUBSYS_H

#include "chrono/core/ChPlatform.h"

// When compiling this library, remember to define CH_API_COMPILE_VEHICLE
// (so that the symbols with 'CH_VEHICLE_API' in front of them will be marked as
// exported). Otherwise, just do not define it if you link the library to your
// code, and the symbols will be imported.

#if defined(CH_API_COMPILE_SENSORS)
#define CH_SENSORS_API ChApiEXPORT
#else
#define CH_SENSORS_API ChApiIMPORT
#endif


/**
    @defgroup sensors SENSOR module
    @brief Ground sensor modeling

    This module introduces sensor models to generate synthetic data.

*/


namespace chrono {

/// @addtogroup vehicle
/// @{

/// Namespace with classes for the SENSOR module.
namespace sensors {}

/// @}

}

#endif
