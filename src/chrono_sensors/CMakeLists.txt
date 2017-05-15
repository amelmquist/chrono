#=============================================================================
# CMake configuration file for Chrono Sensors module
#
# Cannot be used stand-alone (it is loaded by parent CMake configuration file)
#=============================================================================

option(ENABLE_MODULE_SENSORS "Enable the Chrono senors module" OFF)

# Return now if this module is not enabled
if(NOT ENABLE_MODULE_SENSORS)
   return()
endif()

message(STATUS "==== Chrono Sensors module ====")

# Generate the configuration header file using substitution variables.

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/ChConfigSensors.h.in
               ${PROJECT_BINARY_DIR}/chrono_Sensors/ChConfigSensors.h)

install(FILES "${PROJECT_BINARY_DIR}/chrono_Sensors/ChConfigSensors.h"
        DESTINATION include/chrono_sensors)

# ----------------------------------------------------------------------------
# List the files in the ChronoEngine_sensors library
# ----------------------------------------------------------------------------

# --------------- COMMON FILES

set(CV_BASE_FILES
		ChApiSensors.h
    ChSensor.h
		ChSensor.cpp
		ChRaySensor.h
		ChRaySensor.cpp
		ChRayShape.h
		ChRayShape.cpp
		ChGPS.h
		ChGPS.cpp
		ChIMU.h
		ChIMU.cpp
)
source_group("base" FILES ${CV_BASE_FILES})

# ----------------------------------------------------------------------------
# Add the ChronoEngine_Sensors library
# ----------------------------------------------------------------------------

set(CXX_FLAGS ${CH_CXX_FLAGS})
set(LINK_FLAGS ${CH_LINKERFLAG_SHARED})
set(LIBRARIES "ChronoEngine")

if(ENABLE_MODULE_IRRLICHT)
    set(CXX_FLAGS "${CXX_FLAGS} ${CH_IRRLICHT_CXX_FLAGS}")
    list(APPEND LIBRARIES ChronoEngine_irrlicht)
    list(APPEND LIBRARIES ${CH_IRRKLANGLIB})
    include_directories(${CH_IRRLICHTINC})
endif()

if(ENABLE_MODULE_FEA)
    list(APPEND LIBRARIES ChronoEngine_fea)
endif()

if(MPI_CXX_FOUND)
    set(CXX_FLAGS "${CXX_FLAGS} ${MPI_CXX_COMPILE_FLAGS}")
    set(LINK_FLAGS "${LINK_FLAGS} ${MPI_CXX_LINK_FLAGS}")
    include_directories(${MPI_CXX_INCLUDE_PATH})
    list(APPEND LIBRARIES ${MPI_CXX_LIBRARIES})
endif()

add_library(ChronoEngine_sensors SHARED
#
    ${CV_BASE_FILES}
)

set_target_properties(ChronoEngine_sensors PROPERTIES
                      COMPILE_FLAGS "${CXX_FLAGS}"
                      LINK_FLAGS "${CH_LINKERFLAG_SHARED}"
                      COMPILE_DEFINITIONS "CH_API_COMPILE_SENSORS")

target_link_libraries(ChronoEngine_sensors ${LIBRARIES})

install(TARGETS ChronoEngine_sensors
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib64
        ARCHIVE DESTINATION lib64)

install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/
        DESTINATION include/chrono_sensors
        FILES_MATCHING PATTERN "*.h")
