#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <chrono>
#include <sys/time.h>
#include <sys/resource.h>
using namespace std;
using namespace std::chrono;
#define LIBNOP_DISABLE_PARALLEL
#include "AirQualitySensor 2.h"

double getMemoryUsage() 
{
  struct rusage usage;
  if(0 == getrusage(RUSAGE_SELF, &usage))
    return usage.ru_maxrss; // bytes
  else
    return 0;
}

int main()
{
    AirQualitySensorFBE AQS_uni, AQS_road, AQS_center;
    PollutantsLevelObserverFBE PLO_uni, PLO_road, PLO_center;
    SpotAirPollutionInformerFBE SAPI_uni, SAPI_road, SAPI_center;
    CityAirPollutionInformerFBE CAPI_city;

    SAPI_uni.spotName->SetValue("University");
    SAPI_road.spotName->SetValue("RoadSide");
    SAPI_center.spotName->SetValue("CityCenter");
    //cout << SAPI_center.spotName->GetValue() << endl;

    AirQualityRules AQ_rules(AQS_uni, AQS_road, AQS_center, PLO_uni, PLO_road, PLO_center, SAPI_uni, SAPI_road, SAPI_center, CAPI_city);
    double exec_time = 0;
    // File pointer
    fstream fin_u, fin_c, fin_r;
  
    // Open an existing file
    /*fin_c.open("CityCenter.csv");
    fin_r.open("RoadSide.csv");
    fin_u.open("University.csv");*/
    fin_c.open("data1.csv");
    fin_r.open("data2.csv");
    fin_u.open("data3.csv");
    //cout << fin_r.is_open() << endl;
    // Read the Data from the file
    // as String Vector
    vector<string> row_c, row_r, row_u;
    string line_c, line_u, line_r, word_c, word_r, word_u, temp_c, temp_u, temp_r;
    getline(fin_c, line_c);
    getline(fin_u, line_u);
    getline(fin_r, line_r);
    int cnt = 0;
    while (fin_c >> temp_c && fin_r >> temp_r && fin_u >> temp_u){
        //cout << "inside first while" << endl;
        cnt++;
        row_c.clear();
        row_r.clear();
        row_u.clear();

        stringstream c(temp_c), r(temp_r), u(temp_u);
        //cout << line_c << endl;
        // read every column data of a row and
        // store it in a string variable, 'word'
        // for(int j = 0; j <= 7; j++)
        while (getline(r, word_r, ';')) {
            getline(c, word_c, ';');
            getline(u, word_u, ';');

            //cout << "inside second while" << endl;
            //cout << word_c << endl;
            // add all the column data
            // of a row to a vector
            row_c.push_back(word_c);
            row_r.push_back(word_r);
            row_u.push_back(word_u);
        }
        string p10 = row_c.at(3), p25 = row_c.at(8);
        //cout << "before conversion" << endl;
        //cout << p25 << endl;
        //cout << typeid(p10).name() << typeid(p25).name() << endl;
        float pm10_c = stof(p10), pm25_c = stof(p25);
        
        p10 = row_r.at(3), p25 = row_r.at(8);
        float pm10_r = stof(p10), pm25_r = stof(p25);

        p10 = row_u.at(3), p25 = row_u.at(8);
        float pm10_u = stof(p10), pm25_u = stof(p25);
        
        auto start = high_resolution_clock::now();
        AQS_center.pm25_sensor->SetValue(pm25_c);
        AQS_center.pm10_sensor->SetValue(pm10_c);

        AQS_road.pm25_sensor->SetValue(pm25_r);
        AQS_road.pm10_sensor->SetValue(pm10_r);
        //cout << AQS_road.pm10_sensor ->GetValue() << endl;
        AQS_uni.pm25_sensor->SetValue(pm25_u);
        AQS_uni.pm10_sensor->SetValue(pm10_u);
        //cout << AQS_uni.pm25_sensor ->GetValue() << endl;
        //cout << PLO_center.pm25_status ->GetValue() << PLO_road.pm25_status ->GetValue() << PLO_uni.pm25_status->GetValue() << endl;

        auto stop = high_resolution_clock::now();
        auto duration = duration_cast<milliseconds>(stop - start);
  
        exec_time += (double)duration.count();
        //cout << "Time taken by function: "<< duration.count() << " microseconds" << endl;
    }
    cout << "Total Time taken by NOP: "<< exec_time << " milliseconds" << endl;
    fin_c.close();
    fin_r.close();
    fin_u.close();
    double mem = getMemoryUsage()/(1024.0 * 1024.0);
    cout << "Total Memory taken by NOP: "<< mem << " megabytes" << endl;
}