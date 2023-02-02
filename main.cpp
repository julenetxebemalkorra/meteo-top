//!  PROJECT: meteo-top
//!
//!  NAME: main.cpp
//!
//!  AUTHOR: $Author: julenetxebemalkorra $

/*************************************************************************
** INCLUDES
*************************************************************************/

#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <vector>
#include <string>
#include <unistd.h>

/******************************************************************************
** LOCAL FUNCTIONS
******************************************************************************/

#include "open_meteo.h"

/******************************************************************************
** EXPORTED FUNCTIONS
******************************************************************************/



//! FUNCTION: WriteCallback
//!
//! INPUTS:
//!  argc: number of inputs for main function.
//!  argv: double pointer to input data variables.
//!
//! OUTPUTS:
//!  co_int32_t: 0 if Ok and -1 if error.
//!
//! COMMENTS:
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!   Main function of meteo-top project
static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

//! FUNCTION: main
//!
//! INPUTS:
//!  argc: number of inputs for main function.
//!  argv: double pointer to input data variables.
//!
//! OUTPUTS:
//!  co_int32_t: 0 if Ok and -1 if error.
//!
//! COMMENTS:
//! ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
//!   Main function of meteo-top project.

int main(int argc, char** argv){

  //! Curl variables
  CURL * curl;
  CURLcode res;
  std::string readBuffer;
  //! Json variables
  Json::Reader weather_reader;
  Json::Value weather_value;
  //! variables
  std::vector<float> current_weather_display;
  int index;
  std::string  latitude = "0.00";
  std::string  longitude = "0.00";

  //!   stdin_enter_location function of meteo-top to enter coordenates of the location
  stdin_enter_location(&latitude, &longitude);

  std::cout << "The location choosen is:" << std::endl;

  std::cout << latitude<< std::endl;
  std::cout << longitude<< std::endl;
  
  while(1)
  {
    //!  curl_easy_init - create an easy handle 
    curl = curl_easy_init();
  
      if(curl == NULL) {
        fprintf(stderr, "Failed to create CURL connection\n");
        exit(EXIT_FAILURE);
      }
      else {

        std::string url_a = "https://api.open-meteo.com/v1/forecast?latitude=";
        std::string url_b = "&longitude=";
        std::string url_c = "&current_weather=true&hourly=temperature_2m&hourly=relativehumidity_2m&hourly=windspeed_10m";
        std::string url_result = url_a + latitude + url_b + longitude + url_c;

        // combert string to * to be able to send as valid url
        char *cstr = new char[url_result.length() + 1];
        strcpy(cstr, url_result.c_str());
        
        //!curl_easy_setopt - set options for a curl easy handle 
        //! CURLcode curl_easy_setopt(CURL *handle, CURLoption option, parameter);
        //! Network options: CURLOPT_URL: URL to work on. See CURLOPT_URL 
        res = curl_easy_setopt(curl, CURLOPT_URL, cstr);

        // remove char
        delete [] cstr;
        
        //! Callback options CURLOPT_WRITEFUNCTION Callback for writing data.
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        //! Callback options CURLOPT_WRITEDATA Data pointer to pass to the write callback.
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        //!  curl_easy_perform - perform a file transfer synchronously 
        res = curl_easy_perform(curl);
  
        /* Check for errors */
        if(res != CURLE_OK){
          fprintf(stderr, "curl_easy_perform() failed: %s\n",
          curl_easy_strerror(res));
          exit(EXIT_FAILURE);
        }
        
        //!  parse buffer to json type
        if(!weather_reader.parse(readBuffer, weather_value)) {
          fprintf(stderr, "weather_reader.getFormattedErrorMessages() failed: %s\n",
          weather_reader.getFormattedErrorMessages());
        }
          
        //!  find_actual_time_index in the JSOn structure
        index = find_actual_time_index(weather_value);
        if (index < 0){
            fprintf(stderr, "Failed to find valid index\n");
            exit(EXIT_FAILURE);
        }
  
        //!  stdout_weather_info 
        stdout_weather_info(weather_value, index, current_weather_display);
  
        //! curl_easy_cleanup - end a libcurl easy handle 
        curl_easy_cleanup(curl);
      }   
    //! curl_global_cleanup - global libcurl cleanup 
    curl_global_cleanup();

    //!  go to sleep mode, period given by user or default
    if (argv[1] == NULL ){
      sleep(DEFAULT_SLEEP_TIME);
    }
    else{
      sleep(std::stoi(argv[1]));
    }

  }

  return 0;
}
