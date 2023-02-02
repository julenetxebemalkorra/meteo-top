

#define DEFAULT_SLEEP_TIME  10

#include <iostream>
#include <curl/curl.h>
#include <json/json.h>
#include <vector>
#include <string>
#include <unistd.h>


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp){
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}


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

  
  while(1)
  {
    //!  curl_easy_init - create an easy handle 
    curl = curl_easy_init();
  
      if(curl == NULL) {
        fprintf(stderr, "Failed to create CURL connection\n");
        exit(EXIT_FAILURE);
      }
      else {

        res = curl_easy_setopt(curl, CURLOPT_URL, "https://api.open-meteo.com/v1/forecast?latitude=43.12&longitude=-1.98&current_weather=true&hourly=temperature_2m&hourly=relativehumidity_2m&hourly=windspeed_10m");
        
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
        
        std::cout << "temperature" << std::endl;
    	std::cout << weather_value["current_weather"]["temperature_"] << std::endl;
    	std::cout << "relativehumidity_2m" << std::endl;
    	std::cout << weather_value["current_weather"]["windspeed"] << std::endl;

          
        //! curl_easy_cleanup - end a libcurl easy handle 
        curl_easy_cleanup(curl);
      }   
    //! curl_global_cleanup - global libcurl cleanup 
    curl_global_cleanup();

      sleep(DEFAULT_SLEEP_TIME);

  }

  return 0;
}
