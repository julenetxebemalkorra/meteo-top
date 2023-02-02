//!  PROJECT: meteo-top
//!
//!  NAME: open_meteo.h
//!
//!  AUTHOR: $Author: julenetxebemalkorra $

#ifndef OPEN_METEO_H
#define OPEN_METEO_H

/*************************************************************************
** INCLUDES
*************************************************************************/

#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <vector>
#include <string>
#include <unistd.h>

/*************************************************************************
 * ** DEFINITIONS AND MACROS*********************
*************************************************************************/

#define DEFAULT_SLEEP_TIME  60

/******************************************************************************
** EXPORTED FUNCTIONS
******************************************************************************/

//! find actual time weather index value
//! \return int: index value if Ok and -1 if error. */
int find_actual_time_index(Json::Value weather_value);

//! standard output of the weather info
//! \return int: 0 if Ok*/
int stdout_weather_info(Json::Value weather_value, int index, std::vector<float> current_weather_display);

//! input to choose location
//! \return int: 0 if Ok */
int stdin_enter_location(std::string * latitude, std::string * longitude);

#endif /* OPEN_METEO_H */
