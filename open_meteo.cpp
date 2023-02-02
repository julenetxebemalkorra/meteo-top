//!  PROJECT: meteo-top
//!
//!  NAME: open_meteo.cpp
//!
//!  AUTHOR: $Author: julenetxebemalkorra $


#include "open_meteo.h"

//! FUNCTION: find_actual_time_index
//!
//! INPUTS:
//!  Json::Value weather_value
//!
//! OUTPUTS:
//!  int  index if found correctly
//!       -1 if not found any
//!
//! COMMENTS:
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!   find_actual_time_index

int find_actual_time_index(Json::Value weather_value){
    for ( unsigned int index = 0; index < weather_value["hourly"]["time"].size(); ++index )  
    {
        if (weather_value["hourly"]["time"][index] == weather_value["current_weather"]["time"])
        return index;
    }
return -1;
}

//! FUNCTION: stdout_weather_info
//!
//! INPUTS:
//!  Json::Value weather_value
//!  int index
//!  std::vector<float> current_weather_display
//!
//! OUTPUTS:
//!  int  rturns 0
//!
//! COMMENTS:
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!   stdout_weather_info

int stdout_weather_info(Json::Value weather_value, int index, std::vector<float> current_weather_display){

    std::cout << "temperature_2m" << std::endl;
    current_weather_display.insert(current_weather_display.begin(), weather_value["hourly"]["temperature_2m"][index].asFloat());
    std::cout << current_weather_display.front()<< std::endl;
    std::cout << "relativehumidity_2m" << std::endl;
    current_weather_display.insert(current_weather_display.begin() + 1, weather_value["hourly"]["relativehumidity_2m"][index].asFloat());
    std::cout << current_weather_display.at(1) << std::endl;
    std::cout << "windspeed_10m" << std::endl;
    current_weather_display.insert(current_weather_display.end(), weather_value["hourly"]["windspeed_10m"][index].asFloat());
    std::cout << current_weather_display.back()<< std::endl;

    return 0;
}


//! FUNCTION: stdin_enter_location
//!
//! INPUTS:
//!  std::string * latitude
//!  std::string * longitude
//!
//! OUTPUTS:
//!  int  rturns 0
//!
//! COMMENTS:
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!   stdin_enter_location, standard input asking for coordenates, provided by the user, otherwise they are choosen by default 

int stdin_enter_location(std::string * latitude, std::string * longitude){

  std::string s;  
  std::vector <std::pair <std::string , std::string > > pairs;
  std::cout << "Prueba de programación C++ Sistema de captura de datos meteorológicos" << std::endl;
  std::cout << "Enter a value for latituide and longitude, they are pairs of float which represent the location where you want to monitorize the weather, one pair per line, as\n  1 2\n"
          "Press ENTER on a blank line to finish" << std::endl;;

  // While there is input and the user has not simply pressed ENTER
  while (getline( std::cin, s ) && !s.empty())
    {
    std::stringstream ss( s );
    ss >> *latitude >> *longitude;
    if (!ss)
      std::cout << "Invalid pair. Try again";
    else
      pairs.push_back( std::make_pair( *latitude, *longitude ));
    std::cout << "> ";
    }

    if ((*latitude == "0.00") && (*longitude == "0.00")) {
      *latitude = "43.12";
      *longitude = "-1.98";
    }

  return 0;
}
