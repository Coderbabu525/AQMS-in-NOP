#pragma once
#define LIBNOP_DISABLE_PARALLEL
#include "libnop/framework.h"
using namespace std;
using namespace NOP;

int cnt = 0;
// Air Quality Sensor
struct AirQualitySensorFBE
{
    // Attributes of Air Quality Sensor FBE
    NOP::SharedAttribute<float> pm25_sensor{NOP::BuildAttribute<float>(0.0)};
    NOP::SharedAttribute<float> pm10_sensor{NOP::BuildAttribute<float>(0.0)};
    NOP::SharedAttribute<bool> isOn{NOP::BuildAttribute<bool>(true)};

    // Methods of Air Quality Sensor FBE
    // NOP::Method turnOn{ METHOD(cnt++; isOn->SetValue(true); endl;) };
    // NOP::Method turnOff{ METHOD(cnt++; isOn->SetValue(false); endl;) };
    NOP::Method turnOn{[&]()
                       { cnt++; isOn->SetValue(true); /*std::endl;*/ }};
    NOP::Method turnOff{[&]()
                        { cnt++; isOn->SetValue(false); /*std::endl;*/ }};
};

// Pollutants Level Observer
struct PollutantsLevelObserverFBE
{
    // Attributes of Pollutants Level Observer FBE
    NOP::SharedAttribute<string> pm25_status{NOP::BuildAttribute<string>("")};
    NOP::SharedAttribute<string> pm10_status{NOP::BuildAttribute<string>("")};

    // Methods of Pollutants Level Observer FBE
    std::function<void(string)> changeStatusPM25 = [=](string s)
    {cnt++; pm25_status->SetValue(s); };
    std::function<void(string)> changeStatusPM10 = [=](string s)
    {cnt++; pm10_status->SetValue(s); };
};

// Spot Air Pollution Informer
struct SpotAirPollutionInformerFBE
{
    // Attributes of Spot Air Pollution Informer FBE
    NOP::SharedAttribute<bool> isOn{NOP::BuildAttribute<bool>(true)};
    NOP::SharedAttribute<string> spotName{NOP::BuildAttribute<string>("")};

    // Methods of Spot Air Pollution Informer FBE
    void pm25Alert(const string &s)
    {
        cnt++;
        cout << "the pm2.5 pollution level in " << spotName->GetValue() << " is " << s << endl;
    };
    void pm10Alert(const string &s)
    {
        cnt++;
        cout << "the pm10 pollution level in " << spotName->GetValue() << " is " << s << endl;
    };
    void pmPollutionAlertOnSpot(const string &s) { cout << "the overall pm pollution level in " << spotName->GetValue() << " is " << s << endl; };
};

// City Air Pollution Informer
struct CityAirPollutionInformerFBE
{
    // Attributes of City Air Pollution Informer FBE
    NOP::SharedAttribute<bool> isOn{NOP::BuildAttribute<bool>(true)};

    // Methods of City Air Pollution Informer FBE
    void pm25AlertCity(const string &s)
    {
        cnt++;
        cout << "the pm2.5 pollution level in the whole city is " << s << " now" << endl;
    };
    void pm10AlertCity(const string &s)
    {
        cnt++;
        cout << "the pm10 pollution level in the whole city is " << s << " now" << endl;
    };
};

struct AirQualityRules
{
    // Premises for on/off status of Air Quality Sensors
    NOP::SharedPremise prAQS_uniOn, prAQS_roadOn, prAQS_centerOn;
    // Premises for on/off status of Spot and City Air Pollution Informers
    NOP::SharedPremise prSAPI_uniOn, prSAPI_roadOn, prSAPI_centerOn, prCAPI_cityOn;
    // Premises for pm2.5 levels of AQS_uni
    NOP::SharedPremise prAQS_uniPM25LessE, prAQS_uniPM25LessF, prAQS_uniPM25GreatF, prAQS_uniPM25LessM, prAQS_uniPM25GreatM,
        prAQS_uniPM25LessP, prAQS_uniPM25GreatP, prAQS_uniPM25LessVP, prAQS_uniPM25GreatVP, prAQS_uniPM25GreatS;
    // Premises for pm2.5 levels of AQS_road
    NOP::SharedPremise prAQS_roadPM25LessE, prAQS_roadPM25LessF, prAQS_roadPM25GreatF, prAQS_roadPM25LessM, prAQS_roadPM25GreatM,
        prAQS_roadPM25LessP, prAQS_roadPM25GreatP, prAQS_roadPM25LessVP, prAQS_roadPM25GreatVP, prAQS_roadPM25GreatS;
    // Premises for pm2.5 levels of AQS_center
    NOP::SharedPremise prAQS_centerPM25LessE, prAQS_centerPM25LessF, prAQS_centerPM25GreatF, prAQS_centerPM25LessM, prAQS_centerPM25GreatM,
        prAQS_centerPM25LessP, prAQS_centerPM25GreatP, prAQS_centerPM25LessVP, prAQS_centerPM25GreatVP, prAQS_centerPM25GreatS;
    // Premises for pm10 levels of AQS_uni
    NOP::SharedPremise prAQS_uniPM10LessE, prAQS_uniPM10LessF, prAQS_uniPM10GreatF, prAQS_uniPM10LessM, prAQS_uniPM10GreatM,
        prAQS_uniPM10LessP, prAQS_uniPM10GreatP, prAQS_uniPM10LessVP, prAQS_uniPM10GreatVP, prAQS_uniPM10GreatS;
    // Premises for pm10 levels of AQS_road
    NOP::SharedPremise prAQS_roadPM10LessE, prAQS_roadPM10LessF, prAQS_roadPM10GreatF, prAQS_roadPM10LessM, prAQS_roadPM10GreatM,
        prAQS_roadPM10LessP, prAQS_roadPM10GreatP, prAQS_roadPM10LessVP, prAQS_roadPM10GreatVP, prAQS_roadPM10GreatS;
    // Premises for pm10 levels of AQS_center
    NOP::SharedPremise prAQS_centerPM10LessE, prAQS_centerPM10LessF, prAQS_centerPM10GreatF, prAQS_centerPM10LessM, prAQS_centerPM10GreatM,
        prAQS_centerPM10LessP, prAQS_centerPM10GreatP, prAQS_centerPM10LessVP, prAQS_centerPM10GreatVP, prAQS_centerPM10GreatS;
    NOP::SharedPremise prPLO_uniPM25E;
    NOP::SharedPremise prPLO_uniPM25nE;
    NOP::SharedPremise prPLO_uniPM10E;
    NOP::SharedPremise prPLO_uniPM10nE;
    NOP::SharedPremise prPLO_uniPM25F;
    NOP::SharedPremise prPLO_uniPM25nF;
    NOP::SharedPremise prPLO_uniPM10F;
    NOP::SharedPremise prPLO_uniPM10nF;
    NOP::SharedPremise prPLO_uniPM25M;
    NOP::SharedPremise prPLO_uniPM25nM;
    NOP::SharedPremise prPLO_uniPM10M;
    NOP::SharedPremise prPLO_uniPM10nM;
    NOP::SharedPremise prPLO_uniPM25P;
    NOP::SharedPremise prPLO_uniPM25nP;
    NOP::SharedPremise prPLO_uniPM10P;
    NOP::SharedPremise prPLO_uniPM10nP;
    NOP::SharedPremise prPLO_uniPM25VP;
    NOP::SharedPremise prPLO_uniPM25nVP;
    NOP::SharedPremise prPLO_uniPM10VP;
    NOP::SharedPremise prPLO_uniPM10nVP;
    NOP::SharedPremise prPLO_uniPM25S;
    NOP::SharedPremise prPLO_uniPM25nS;
    NOP::SharedPremise prPLO_uniPM10S;
    NOP::SharedPremise prPLO_uniPM10nS;
    NOP::SharedPremise prPLO_roadPM25E;
    NOP::SharedPremise prPLO_roadPM25nE;
    NOP::SharedPremise prPLO_roadPM10E;
    NOP::SharedPremise prPLO_roadPM10nE;
    NOP::SharedPremise prPLO_roadPM25F;
    NOP::SharedPremise prPLO_roadPM25nF;
    NOP::SharedPremise prPLO_roadPM10F;
    NOP::SharedPremise prPLO_roadPM10nF;
    NOP::SharedPremise prPLO_roadPM25M;
    NOP::SharedPremise prPLO_roadPM25nM;
    NOP::SharedPremise prPLO_roadPM10M;
    NOP::SharedPremise prPLO_roadPM10nM;
    NOP::SharedPremise prPLO_roadPM25P;
    NOP::SharedPremise prPLO_roadPM25nP;
    NOP::SharedPremise prPLO_roadPM10P;
    NOP::SharedPremise prPLO_roadPM10nP;
    NOP::SharedPremise prPLO_roadPM25VP;
    NOP::SharedPremise prPLO_roadPM25nVP;
    NOP::SharedPremise prPLO_roadPM10VP;
    NOP::SharedPremise prPLO_roadPM10nVP;
    NOP::SharedPremise prPLO_roadPM25S;
    NOP::SharedPremise prPLO_roadPM25nS;
    NOP::SharedPremise prPLO_roadPM10S;
    NOP::SharedPremise prPLO_roadPM10nS;
    NOP::SharedPremise prPLO_centerPM25E;
    NOP::SharedPremise prPLO_centerPM25nE;
    NOP::SharedPremise prPLO_centerPM10E;
    NOP::SharedPremise prPLO_centerPM10nE;
    NOP::SharedPremise prPLO_centerPM25F;
    NOP::SharedPremise prPLO_centerPM25nF;
    NOP::SharedPremise prPLO_centerPM10F;
    NOP::SharedPremise prPLO_centerPM10nF;
    NOP::SharedPremise prPLO_centerPM25M;
    NOP::SharedPremise prPLO_centerPM25nM;
    NOP::SharedPremise prPLO_centerPM10M;
    NOP::SharedPremise prPLO_centerPM10nM;
    NOP::SharedPremise prPLO_centerPM25P;
    NOP::SharedPremise prPLO_centerPM25nP;
    NOP::SharedPremise prPLO_centerPM10P;
    NOP::SharedPremise prPLO_centerPM10nP;
    NOP::SharedPremise prPLO_centerPM25VP;
    NOP::SharedPremise prPLO_centerPM25nVP;
    NOP::SharedPremise prPLO_centerPM10VP;
    NOP::SharedPremise prPLO_centerPM10nVP;
    NOP::SharedPremise prPLO_centerPM25S;
    NOP::SharedPremise prPLO_centerPM25nS;
    NOP::SharedPremise prPLO_centerPM10S;
    NOP::SharedPremise prPLO_centerPM10nS;
    NOP::SharedCondition cnUniPM25E;
    NOP::SharedCondition cnUniPM25F;
    NOP::SharedCondition cnUniPM25M;
    NOP::SharedCondition cnUniPM25P;
    NOP::SharedCondition cnUniPM25VP;
    NOP::SharedCondition cnUniPM25S;
    NOP::SharedCondition cnUniPM10E;
    NOP::SharedCondition cnUniPM10F;
    NOP::SharedCondition cnUniPM10M;
    NOP::SharedCondition cnUniPM10P;
    NOP::SharedCondition cnUniPM10VP;
    NOP::SharedCondition cnUniPM10S;
    NOP::SharedCondition cnRoadPM25E;
    NOP::SharedCondition cnRoadPM25F;
    NOP::SharedCondition cnRoadPM25M;
    NOP::SharedCondition cnRoadPM25P;
    NOP::SharedCondition cnRoadPM25VP;
    NOP::SharedCondition cnRoadPM25S;
    NOP::SharedCondition cnRoadPM10E;
    NOP::SharedCondition cnRoadPM10F;
    NOP::SharedCondition cnRoadPM10M;
    NOP::SharedCondition cnRoadPM10P;
    NOP::SharedCondition cnRoadPM10VP;
    NOP::SharedCondition cnRoadPM10S;
    NOP::SharedCondition cnCenterPM25E;
    NOP::SharedCondition cnCenterPM25F;
    NOP::SharedCondition cnCenterPM25M;
    NOP::SharedCondition cnCenterPM25P;
    NOP::SharedCondition cnCenterPM25VP;
    NOP::SharedCondition cnCenterPM25S;
    NOP::SharedCondition cnCenterPM10E;
    NOP::SharedCondition cnCenterPM10F;
    NOP::SharedCondition cnCenterPM10M;
    NOP::SharedCondition cnCenterPM10P;
    NOP::SharedCondition cnCenterPM10VP;
    NOP::SharedCondition cnCenterPM10S;
    NOP::SharedCondition cnCityPM25E;
    NOP::SharedCondition cnCityPM10E;
    NOP::SharedCondition cnCityPM25F;
    NOP::SharedCondition cnCityPM10F;
    NOP::SharedCondition cnCityPM25M;
    NOP::SharedCondition cnCityPM10M;
    NOP::SharedCondition cnCityPM25P;
    NOP::SharedCondition cnCityPM10P;
    NOP::SharedCondition cnCityPM25VP;
    NOP::SharedCondition cnCityPM10VP;
    NOP::SharedCondition cnCityPM25S;
    NOP::SharedCondition cnCityPM10S;
    NOP::SharedCondition cnUniPME;
    NOP::SharedCondition cnUniPMF;
    NOP::SharedCondition cnUniPMM;
    NOP::SharedCondition cnUniPMP;
    NOP::SharedCondition cnUniPMVP;
    NOP::SharedCondition cnUniPMS;
    NOP::SharedCondition cnRoadPME;
    NOP::SharedCondition cnRoadPMF;
    NOP::SharedCondition cnRoadPMM;
    NOP::SharedCondition cnRoadPMP;
    NOP::SharedCondition cnRoadPMVP;
    NOP::SharedCondition cnRoadPMS;
    NOP::SharedCondition cnCenterPME;
    NOP::SharedCondition cnCenterPMF;
    NOP::SharedCondition cnCenterPMM;
    NOP::SharedCondition cnCenterPMP;
    NOP::SharedCondition cnCenterPMVP;
    NOP::SharedCondition cnCenterPMS;
    NOP::SharedInstigation inUniPM25E;
    NOP::SharedInstigation inUniPM10E;
    NOP::SharedInstigation inUniPM25F;
    NOP::SharedInstigation inUniPM10F;
    NOP::SharedInstigation inUniPM25M;
    NOP::SharedInstigation inUniPM10M;
    NOP::SharedInstigation inUniPM25P;
    NOP::SharedInstigation inUniPM10P;
    NOP::SharedInstigation inUniPM25VP;
    NOP::SharedInstigation inUniPM10VP;
    NOP::SharedInstigation inUniPM25S;
    NOP::SharedInstigation inUniPM10S;
    NOP::SharedInstigation inRoadPM25E;
    NOP::SharedInstigation inRoadPM10E;
    NOP::SharedInstigation inRoadPM25F;
    NOP::SharedInstigation inRoadPM10F;
    NOP::SharedInstigation inRoadPM25M;
    NOP::SharedInstigation inRoadPM10M;
    NOP::SharedInstigation inRoadPM25P;
    NOP::SharedInstigation inRoadPM10P;
    NOP::SharedInstigation inRoadPM25VP;
    NOP::SharedInstigation inRoadPM10VP;
    NOP::SharedInstigation inRoadPM25S;
    NOP::SharedInstigation inRoadPM10S;
    NOP::SharedInstigation inCenterPM25E;
    NOP::SharedInstigation inCenterPM10E;
    NOP::SharedInstigation inCenterPM25F;
    NOP::SharedInstigation inCenterPM10F;
    NOP::SharedInstigation inCenterPM25M;
    NOP::SharedInstigation inCenterPM10M;
    NOP::SharedInstigation inCenterPM25P;
    NOP::SharedInstigation inCenterPM10P;
    NOP::SharedInstigation inCenterPM25VP;
    NOP::SharedInstigation inCenterPM10VP;
    NOP::SharedInstigation inCenterPM25S;
    NOP::SharedInstigation inCenterPM10S;
    NOP::SharedInstigation inPLO_UniPM25E;
    NOP::SharedInstigation inPLO_UniPM10E;
    NOP::SharedInstigation inPLO_UniPM25F;
    NOP::SharedInstigation inPLO_UniPM10F;
    NOP::SharedInstigation inPLO_UniPM25M;
    NOP::SharedInstigation inPLO_UniPM10M;
    NOP::SharedInstigation inPLO_UniPM25P;
    NOP::SharedInstigation inPLO_UniPM10P;
    NOP::SharedInstigation inPLO_UniPM25VP;
    NOP::SharedInstigation inPLO_UniPM10VP;
    NOP::SharedInstigation inPLO_UniPM25S;
    NOP::SharedInstigation inPLO_UniPM10S;
    NOP::SharedInstigation inPLO_RoadPM25E;
    NOP::SharedInstigation inPLO_RoadPM10E;
    NOP::SharedInstigation inPLO_RoadPM25F;
    NOP::SharedInstigation inPLO_RoadPM10F;
    NOP::SharedInstigation inPLO_RoadPM25M;
    NOP::SharedInstigation inPLO_RoadPM10M;
    NOP::SharedInstigation inPLO_RoadPM25P;
    NOP::SharedInstigation inPLO_RoadPM10P;
    NOP::SharedInstigation inPLO_RoadPM25VP;
    NOP::SharedInstigation inPLO_RoadPM10VP;
    NOP::SharedInstigation inPLO_RoadPM25S;
    NOP::SharedInstigation inPLO_RoadPM10S;
    NOP::SharedInstigation inPLO_CenterPM25E;
    NOP::SharedInstigation inPLO_CenterPM10E;
    NOP::SharedInstigation inPLO_CenterPM25F;
    NOP::SharedInstigation inPLO_CenterPM10F;
    NOP::SharedInstigation inPLO_CenterPM25M;
    NOP::SharedInstigation inPLO_CenterPM10M;
    NOP::SharedInstigation inPLO_CenterPM25P;
    NOP::SharedInstigation inPLO_CenterPM10P;
    NOP::SharedInstigation inPLO_CenterPM25VP;
    NOP::SharedInstigation inPLO_CenterPM10VP;
    NOP::SharedInstigation inPLO_CenterPM25S;
    NOP::SharedInstigation inPLO_CenterPM10S;
    NOP::SharedInstigation inCityPM25E;
    NOP::SharedInstigation inCityPM10E;
    NOP::SharedInstigation inCityPM25F;
    NOP::SharedInstigation inCityPM10F;
    NOP::SharedInstigation inCityPM25M;
    NOP::SharedInstigation inCityPM10M;
    NOP::SharedInstigation inCityPM25P;
    NOP::SharedInstigation inCityPM10P;
    NOP::SharedInstigation inCityPM25VP;
    NOP::SharedInstigation inCityPM10VP;
    NOP::SharedInstigation inCityPM25S;
    NOP::SharedInstigation inCityPM10S;
    NOP::SharedInstigation inUniPME;
    NOP::SharedInstigation inUniPMF;
    NOP::SharedInstigation inUniPMM;
    NOP::SharedInstigation inUniPMP;
    NOP::SharedInstigation inUniPMVP;
    NOP::SharedInstigation inUniPMS;
    NOP::SharedInstigation inRoadPME;
    NOP::SharedInstigation inRoadPMF;
    NOP::SharedInstigation inRoadPMM;
    NOP::SharedInstigation inRoadPMP;
    NOP::SharedInstigation inRoadPMVP;
    NOP::SharedInstigation inRoadPMS;
    NOP::SharedInstigation inCenterPME;
    NOP::SharedInstigation inCenterPMF;
    NOP::SharedInstigation inCenterPMM;
    NOP::SharedInstigation inCenterPMP;
    NOP::SharedInstigation inCenterPMVP;
    NOP::SharedInstigation inCenterPMS;
    NOP::SharedAction acUniPM25E;
    NOP::SharedAction acUniPM10E;
    NOP::SharedAction acUniPM25F;
    NOP::SharedAction acUniPM10F;
    NOP::SharedAction acUniPM25M;
    NOP::SharedAction acUniPM10M;
    NOP::SharedAction acUniPM25P;
    NOP::SharedAction acUniPM10P;
    NOP::SharedAction acUniPM25VP;
    NOP::SharedAction acUniPM10VP;
    NOP::SharedAction acUniPM25S;
    NOP::SharedAction acUniPM10S;
    NOP::SharedAction acRoadPM25E;
    NOP::SharedAction acRoadPM10E;
    NOP::SharedAction acRoadPM25F;
    NOP::SharedAction acRoadPM10F;
    NOP::SharedAction acRoadPM25M;
    NOP::SharedAction acRoadPM10M;
    NOP::SharedAction acRoadPM25P;
    NOP::SharedAction acRoadPM10P;
    NOP::SharedAction acRoadPM25VP;
    NOP::SharedAction acRoadPM10VP;
    NOP::SharedAction acRoadPM25S;
    NOP::SharedAction acRoadPM10S;
    NOP::SharedAction acCenterPM25E;
    NOP::SharedAction acCenterPM10E;
    NOP::SharedAction acCenterPM25F;
    NOP::SharedAction acCenterPM10F;
    NOP::SharedAction acCenterPM25M;
    NOP::SharedAction acCenterPM10M;
    NOP::SharedAction acCenterPM25P;
    NOP::SharedAction acCenterPM10P;
    NOP::SharedAction acCenterPM25VP;
    NOP::SharedAction acCenterPM10VP;
    NOP::SharedAction acCenterPM25S;
    NOP::SharedAction acCenterPM10S;
    NOP::SharedAction acCityPM25E;
    NOP::SharedAction acCityPM10E;
    NOP::SharedAction acCityPM25F;
    NOP::SharedAction acCityPM10F;
    NOP::SharedAction acCityPM25M;
    NOP::SharedAction acCityPM10M;
    NOP::SharedAction acCityPM25P;
    NOP::SharedAction acCityPM10P;
    NOP::SharedAction acCityPM25VP;
    NOP::SharedAction acCityPM10VP;
    NOP::SharedAction acCityPM25S;
    NOP::SharedAction acCityPM10S;
    NOP::SharedAction acUniPME;
    NOP::SharedAction acUniPMF;
    NOP::SharedAction acUniPMM;
    NOP::SharedAction acUniPMP;
    NOP::SharedAction acUniPMVP;
    NOP::SharedAction acUniPMS;
    NOP::SharedAction acRoadPME;
    NOP::SharedAction acRoadPMF;
    NOP::SharedAction acRoadPMM;
    NOP::SharedAction acRoadPMP;
    NOP::SharedAction acRoadPMVP;
    NOP::SharedAction acRoadPMS;
    NOP::SharedAction acCenterPME;
    NOP::SharedAction acCenterPMF;
    NOP::SharedAction acCenterPMM;
    NOP::SharedAction acCenterPMP;
    NOP::SharedAction acCenterPMVP;
    NOP::SharedAction acCenterPMS;
    NOP::SharedRule rlUniPM25E;
    NOP::SharedRule rlUniPM10E;
    NOP::SharedRule rlUniPM25F;
    NOP::SharedRule rlUniPM10F;
    NOP::SharedRule rlUniPM25M;
    NOP::SharedRule rlUniPM10M;
    NOP::SharedRule rlUniPM25P;
    NOP::SharedRule rlUniPM10P;
    NOP::SharedRule rlUniPM25VP;
    NOP::SharedRule rlUniPM10VP;
    NOP::SharedRule rlUniPM25S;
    NOP::SharedRule rlUniPM10S;
    NOP::SharedRule rlRoadPM25E;
    NOP::SharedRule rlRoadPM10E;
    NOP::SharedRule rlRoadPM25F;
    NOP::SharedRule rlRoadPM10F;
    NOP::SharedRule rlRoadPM25M;
    NOP::SharedRule rlRoadPM10M;
    NOP::SharedRule rlRoadPM25P;
    NOP::SharedRule rlRoadPM10P;
    NOP::SharedRule rlRoadPM25VP;
    NOP::SharedRule rlRoadPM10VP;
    NOP::SharedRule rlRoadPM25S;
    NOP::SharedRule rlRoadPM10S;
    NOP::SharedRule rlCenterPM25E;
    NOP::SharedRule rlCenterPM10E;
    NOP::SharedRule rlCenterPM25F;
    NOP::SharedRule rlCenterPM10F;
    NOP::SharedRule rlCenterPM25M;
    NOP::SharedRule rlCenterPM10M;
    NOP::SharedRule rlCenterPM25P;
    NOP::SharedRule rlCenterPM10P;
    NOP::SharedRule rlCenterPM25VP;
    NOP::SharedRule rlCenterPM10VP;
    NOP::SharedRule rlCenterPM25S;
    NOP::SharedRule rlCenterPM10S;
    NOP::SharedRule rlCityPM25E;
    NOP::SharedRule rlCityPM10E;
    NOP::SharedRule rlCityPM25F;
    NOP::SharedRule rlCityPM10F;
    NOP::SharedRule rlCityPM25M;
    NOP::SharedRule rlCityPM10M;
    NOP::SharedRule rlCityPM25P;
    NOP::SharedRule rlCityPM10P;
    NOP::SharedRule rlCityPM25VP;
    NOP::SharedRule rlCityPM10VP;
    NOP::SharedRule rlCityPM25S;
    NOP::SharedRule rlCityPM10S;
    NOP::SharedRule rlUniPME;
    NOP::SharedRule rlUniPMF;
    NOP::SharedRule rlUniPMM;
    NOP::SharedRule rlUniPMP;
    NOP::SharedRule rlUniPMVP;
    NOP::SharedRule rlUniPMS;
    NOP::SharedRule rlRoadPME;
    NOP::SharedRule rlRoadPMF;
    NOP::SharedRule rlRoadPMM;
    NOP::SharedRule rlRoadPMP;
    NOP::SharedRule rlRoadPMVP;
    NOP::SharedRule rlRoadPMS;
    NOP::SharedRule rlCenterPME;
    NOP::SharedRule rlCenterPMF;
    NOP::SharedRule rlCenterPMM;
    NOP::SharedRule rlCenterPMP;
    NOP::SharedRule rlCenterPMVP;
    NOP::SharedRule rlCenterPMS;
    AirQualityRules(AirQualitySensorFBE &AQS_uni, AirQualitySensorFBE &AQS_road, AirQualitySensorFBE &AQS_center,
                    PollutantsLevelObserverFBE &PLO_uni, PollutantsLevelObserverFBE &PLO_road, PollutantsLevelObserverFBE &PLO_center,
                    SpotAirPollutionInformerFBE &SAPI_uni, SpotAirPollutionInformerFBE &SAPI_road, SpotAirPollutionInformerFBE &SAPI_center,
                    CityAirPollutionInformerFBE &CAPI_city)
    {
        // All Premises here
        // Premises for on/off status of Air Quality Sensors
        prAQS_uniOn = NOP::BuildPremise<bool>(AQS_uni.isOn, true, NOP::Equal());
        prAQS_roadOn = NOP::BuildPremise<bool>(AQS_road.isOn, true, NOP::Equal());
        prAQS_centerOn = NOP::BuildPremise<bool>(AQS_center.isOn, true, NOP::Equal());

        // Premises for on/off status of Spot Air Pollution Informers
        prSAPI_uniOn = NOP::BuildPremise<bool>(SAPI_uni.isOn, true, NOP::Equal());
        prSAPI_roadOn = NOP::BuildPremise<bool>(SAPI_road.isOn, true, NOP::Equal());
        prSAPI_centerOn = NOP::BuildPremise<bool>(SAPI_center.isOn, true, NOP::Equal());

        // Premise for on/off status of City Air Pollution Informer
        prCAPI_cityOn = NOP::BuildPremise<bool>(CAPI_city.isOn, true, NOP::Equal());

        // Premises for pm2.5 levels of AQS_uni
        prAQS_uniPM25LessE = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 5.0, NOP::LessEqual());

        prAQS_uniPM25LessF = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 10.0, NOP::LessEqual());
        prAQS_uniPM25GreatF = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 5.0, NOP::Greater());

        prAQS_uniPM25LessM = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 20.0, NOP::LessEqual());
        prAQS_uniPM25GreatM = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 10.0, NOP::Greater());

        prAQS_uniPM25LessP = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 25.0, NOP::LessEqual());
        prAQS_uniPM25GreatP = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 20.0, NOP::Greater());

        prAQS_uniPM25LessVP = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 60.0, NOP::LessEqual());
        prAQS_uniPM25GreatVP = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 25.0, NOP::Greater());

        prAQS_uniPM25GreatS = NOP::BuildPremise<float>(AQS_uni.pm25_sensor, 60.0, NOP::Greater());

        // Premises for pm2.5 levels of AQS_road
        prAQS_roadPM25LessE = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 5.0, NOP::LessEqual());

        prAQS_roadPM25LessF = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 10.0, NOP::LessEqual());
        prAQS_roadPM25GreatF = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 5.0, NOP::Greater());

        prAQS_roadPM25LessM = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 20.0, NOP::LessEqual());
        prAQS_roadPM25GreatM = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 10.0, NOP::Greater());

        prAQS_roadPM25LessP = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 25.0, NOP::LessEqual());
        prAQS_roadPM25GreatP = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 20.0, NOP::Greater());

        prAQS_roadPM25LessVP = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 60.0, NOP::LessEqual());
        prAQS_roadPM25GreatVP = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 25.0, NOP::Greater());

        prAQS_roadPM25GreatS = NOP::BuildPremise<float>(AQS_road.pm25_sensor, 60.0, NOP::Greater());

        // Premises for pm2.5 levels of AQS_center
        prAQS_centerPM25LessE = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 5.0, NOP::LessEqual());

        prAQS_centerPM25LessF = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 10.0, NOP::LessEqual());
        prAQS_centerPM25GreatF = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 5.0, NOP::Greater());

        prAQS_centerPM25LessM = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 20.0, NOP::LessEqual());
        prAQS_centerPM25GreatM = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 10.0, NOP::Greater());

        prAQS_centerPM25LessP = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 25.0, NOP::LessEqual());
        prAQS_centerPM25GreatP = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 20.0, NOP::Greater());

        prAQS_centerPM25LessVP = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 60.0, NOP::LessEqual());
        prAQS_centerPM25GreatVP = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 25.0, NOP::Greater());

        prAQS_centerPM25GreatS = NOP::BuildPremise<float>(AQS_center.pm25_sensor, 60.0, NOP::Greater());

        // Premises for pm10 levels of AQS_uni
        prAQS_uniPM10LessE = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 10.0, NOP::LessEqual());

        prAQS_uniPM10LessF = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 20.0, NOP::LessEqual());
        prAQS_uniPM10GreatF = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 10.0, NOP::Greater());

        prAQS_uniPM10LessM = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 35.0, NOP::LessEqual());
        prAQS_uniPM10GreatM = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 20.0, NOP::Greater());

        prAQS_uniPM10LessP = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 50.0, NOP::LessEqual());
        prAQS_uniPM10GreatP = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 35.0, NOP::Greater());

        prAQS_uniPM10LessVP = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 100.0, NOP::LessEqual());
        prAQS_uniPM10GreatVP = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 50.0, NOP::Greater());

        prAQS_uniPM10GreatS = NOP::BuildPremise<float>(AQS_uni.pm10_sensor, 100.0, NOP::Greater());

        // Premises for pm10 levels of AQS_road
        prAQS_roadPM10LessE = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 10.0, NOP::LessEqual());

        prAQS_roadPM10LessF = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 20.0, NOP::LessEqual());
        prAQS_roadPM10GreatF = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 10.0, NOP::Greater());

        prAQS_roadPM10LessM = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 35.0, NOP::LessEqual());
        prAQS_roadPM10GreatM = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 20.0, NOP::Greater());

        prAQS_roadPM10LessP = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 50.0, NOP::LessEqual());
        prAQS_roadPM10GreatP = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 35.0, NOP::Greater());

        prAQS_roadPM10LessVP = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 100.0, NOP::LessEqual());
        prAQS_roadPM10GreatVP = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 50.0, NOP::Greater());

        prAQS_roadPM10GreatS = NOP::BuildPremise<float>(AQS_road.pm10_sensor, 100.0, NOP::Greater());

        // Premises for pm10 levels of AQS_center
        prAQS_centerPM10LessE = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 10.0, NOP::LessEqual());

        prAQS_centerPM10LessF = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 20.0, NOP::LessEqual());
        prAQS_centerPM10GreatF = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 10.0, NOP::Greater());

        prAQS_centerPM10LessM = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 35.0, NOP::LessEqual());
        prAQS_centerPM10GreatM = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 20.0, NOP::Greater());

        prAQS_centerPM10LessP = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 50.0, NOP::LessEqual());
        prAQS_centerPM10GreatP = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 35.0, NOP::Greater());

        prAQS_centerPM10LessVP = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 100.0, NOP::LessEqual());
        prAQS_centerPM10GreatVP = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 50.0, NOP::Greater());

        prAQS_centerPM10GreatS = NOP::BuildPremise<float>(AQS_center.pm10_sensor, 100.0, NOP::Greater());

        // Premises for PLO_uni pm2.5 and pm10 status
        prPLO_uniPM25E = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Excellent", NOP::Equal());
        prPLO_uniPM25nE = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Excellent", NOP::Different());
        prPLO_uniPM10E = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Excellent", NOP::Equal());
        prPLO_uniPM10nE = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Excellent", NOP::Different());

        prPLO_uniPM25F = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Fine", NOP::Equal());
        prPLO_uniPM25nF = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Fine", NOP::Different());
        prPLO_uniPM10F = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Fine", NOP::Equal());
        prPLO_uniPM10nF = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Fine", NOP::Different());

        prPLO_uniPM25M = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Moderate", NOP::Equal());
        prPLO_uniPM25nM = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Moderate", NOP::Different());
        prPLO_uniPM10M = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Moderate", NOP::Equal());
        prPLO_uniPM10nM = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Moderate", NOP::Different());

        prPLO_uniPM25P = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Poor", NOP::Equal());
        prPLO_uniPM25nP = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Poor", NOP::Different());
        prPLO_uniPM10P = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Poor", NOP::Equal());
        prPLO_uniPM10nP = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Poor", NOP::Different());

        prPLO_uniPM25VP = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Very Poor", NOP::Equal());
        prPLO_uniPM25nVP = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Very Poor", NOP::Different());
        prPLO_uniPM10VP = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Very Poor", NOP::Equal());
        prPLO_uniPM10nVP = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Very Poor", NOP::Different());

        prPLO_uniPM25S = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Severe", NOP::Equal());
        prPLO_uniPM25nS = NOP::BuildPremise<string>(PLO_uni.pm25_status, "Severe", NOP::Different());
        prPLO_uniPM10S = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Severe", NOP::Equal());
        prPLO_uniPM10nS = NOP::BuildPremise<string>(PLO_uni.pm10_status, "Severe", NOP::Different());

        // Premises for PLO_road pm2.5 and pm10 status
        prPLO_roadPM25E = NOP::BuildPremise<string>(PLO_road.pm25_status, "Excellent", NOP::Equal());
        prPLO_roadPM25nE = NOP::BuildPremise<string>(PLO_road.pm25_status, "Excellent", NOP::Different());
        prPLO_roadPM10E = NOP::BuildPremise<string>(PLO_road.pm10_status, "Excellent", NOP::Equal());
        prPLO_roadPM10nE = NOP::BuildPremise<string>(PLO_road.pm10_status, "Excellent", NOP::Different());

        prPLO_roadPM25F = NOP::BuildPremise<string>(PLO_road.pm25_status, "Fine", NOP::Equal());
        prPLO_roadPM25nF = NOP::BuildPremise<string>(PLO_road.pm25_status, "Fine", NOP::Different());
        prPLO_roadPM10F = NOP::BuildPremise<string>(PLO_road.pm10_status, "Fine", NOP::Equal());
        prPLO_roadPM10nF = NOP::BuildPremise<string>(PLO_road.pm10_status, "Fine", NOP::Different());

        prPLO_roadPM25M = NOP::BuildPremise<string>(PLO_road.pm25_status, "Moderate", NOP::Equal());
        prPLO_roadPM25nM = NOP::BuildPremise<string>(PLO_road.pm25_status, "Moderate", NOP::Different());
        prPLO_roadPM10M = NOP::BuildPremise<string>(PLO_road.pm10_status, "Moderate", NOP::Equal());
        prPLO_roadPM10nM = NOP::BuildPremise<string>(PLO_road.pm10_status, "Moderate", NOP::Different());

        prPLO_roadPM25P = NOP::BuildPremise<string>(PLO_road.pm25_status, "Poor", NOP::Equal());
        prPLO_roadPM25nP = NOP::BuildPremise<string>(PLO_road.pm25_status, "Poor", NOP::Different());
        prPLO_roadPM10P = NOP::BuildPremise<string>(PLO_road.pm10_status, "Poor", NOP::Equal());
        prPLO_roadPM10nP = NOP::BuildPremise<string>(PLO_road.pm10_status, "Poor", NOP::Different());

        prPLO_roadPM25VP = NOP::BuildPremise<string>(PLO_road.pm25_status, "Very Poor", NOP::Equal());
        prPLO_roadPM25nVP = NOP::BuildPremise<string>(PLO_road.pm25_status, "Very Poor", NOP::Different());
        prPLO_roadPM10VP = NOP::BuildPremise<string>(PLO_road.pm10_status, "Very Poor", NOP::Equal());
        prPLO_roadPM10nVP = NOP::BuildPremise<string>(PLO_road.pm10_status, "Very Poor", NOP::Different());

        prPLO_roadPM25S = NOP::BuildPremise<string>(PLO_road.pm25_status, "Severe", NOP::Equal());
        prPLO_roadPM25nS = NOP::BuildPremise<string>(PLO_road.pm25_status, "Severe", NOP::Different());
        prPLO_roadPM10S = NOP::BuildPremise<string>(PLO_road.pm10_status, "Severe", NOP::Equal());
        prPLO_roadPM10nS = NOP::BuildPremise<string>(PLO_road.pm10_status, "Severe", NOP::Different());

        // Premises for PLO_center pm2.5 and pm10 status
        prPLO_centerPM25E = NOP::BuildPremise<string>(PLO_center.pm25_status, "Excellent", NOP::Equal());
        prPLO_centerPM25nE = NOP::BuildPremise<string>(PLO_center.pm25_status, "Excellent", NOP::Different());
        prPLO_centerPM10E = NOP::BuildPremise<string>(PLO_center.pm10_status, "Excellent", NOP::Equal());
        prPLO_centerPM10nE = NOP::BuildPremise<string>(PLO_center.pm10_status, "Excellent", NOP::Different());

        prPLO_centerPM25F = NOP::BuildPremise<string>(PLO_center.pm25_status, "Fine", NOP::Equal());
        prPLO_centerPM25nF = NOP::BuildPremise<string>(PLO_center.pm25_status, "Fine", NOP::Different());
        prPLO_centerPM10F = NOP::BuildPremise<string>(PLO_center.pm10_status, "Fine", NOP::Equal());
        prPLO_centerPM10nF = NOP::BuildPremise<string>(PLO_center.pm10_status, "Fine", NOP::Different());

        prPLO_centerPM25M = NOP::BuildPremise<string>(PLO_center.pm25_status, "Moderate", NOP::Equal());
        prPLO_centerPM25nM = NOP::BuildPremise<string>(PLO_center.pm25_status, "Moderate", NOP::Different());
        prPLO_centerPM10M = NOP::BuildPremise<string>(PLO_center.pm10_status, "Moderate", NOP::Equal());
        prPLO_centerPM10nM = NOP::BuildPremise<string>(PLO_center.pm10_status, "Moderate", NOP::Different());

        prPLO_centerPM25P = NOP::BuildPremise<string>(PLO_center.pm25_status, "Poor", NOP::Equal());
        prPLO_centerPM25nP = NOP::BuildPremise<string>(PLO_center.pm25_status, "Poor", NOP::Different());
        prPLO_centerPM10P = NOP::BuildPremise<string>(PLO_center.pm10_status, "Poor", NOP::Equal());
        prPLO_centerPM10nP = NOP::BuildPremise<string>(PLO_center.pm10_status, "Poor", NOP::Different());

        prPLO_centerPM25VP = NOP::BuildPremise<string>(PLO_center.pm25_status, "Very Poor", NOP::Equal());
        prPLO_centerPM25nVP = NOP::BuildPremise<string>(PLO_center.pm25_status, "Very Poor", NOP::Different());
        prPLO_centerPM10VP = NOP::BuildPremise<string>(PLO_center.pm10_status, "Very Poor", NOP::Equal());
        prPLO_centerPM10nVP = NOP::BuildPremise<string>(PLO_center.pm10_status, "Very Poor", NOP::Different());

        prPLO_centerPM25S = NOP::BuildPremise<string>(PLO_center.pm25_status, "Severe", NOP::Equal());
        prPLO_centerPM25nS = NOP::BuildPremise<string>(PLO_center.pm25_status, "Severe", NOP::Different());
        prPLO_centerPM10S = NOP::BuildPremise<string>(PLO_center.pm10_status, "Severe", NOP::Equal());
        prPLO_centerPM10nS = NOP::BuildPremise<string>(PLO_center.pm10_status, "Severe", NOP::Different());

        // Conditions of the Rule with the Premise
        // COonditions for pm2.5 and pm10 in University
        cnUniPM25E = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM25LessE, prPLO_uniPM25nE, prSAPI_uniOn);
        cnUniPM25F = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM25LessF, prAQS_uniPM25GreatF, prPLO_uniPM25nF, prSAPI_uniOn);
        cnUniPM25M = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM25LessM, prAQS_uniPM25GreatM, prPLO_uniPM25nM, prSAPI_uniOn);
        cnUniPM25P = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM25LessP, prAQS_uniPM25GreatP, prPLO_uniPM25nP, prSAPI_uniOn);
        cnUniPM25VP = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM25LessVP, prAQS_uniPM25GreatVP, prPLO_uniPM25nVP, prSAPI_uniOn);
        cnUniPM25S = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM25GreatS, prPLO_uniPM25nS, prSAPI_uniOn);

        cnUniPM10E = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM10LessE, prPLO_uniPM10nE, prSAPI_uniOn);
        cnUniPM10F = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM10LessF, prAQS_uniPM10GreatF, prPLO_uniPM10nF, prSAPI_uniOn);
        cnUniPM10M = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM10LessM, prAQS_uniPM10GreatM, prPLO_uniPM10nM, prSAPI_uniOn);
        cnUniPM10P = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM10LessP, prAQS_uniPM10GreatP, prPLO_uniPM10nP, prSAPI_uniOn);
        cnUniPM10VP = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM10LessVP, prAQS_uniPM10GreatVP, prPLO_uniPM10nVP, prSAPI_uniOn);
        cnUniPM10S = NOP::BuildCondition<NOP::Conjunction>(prAQS_uniOn, prAQS_uniPM10GreatS, prPLO_uniPM10nS, prSAPI_uniOn);

        // Conditions for pm2.5 and pm10 in RoadSide
        cnRoadPM25E = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM25LessE, prPLO_roadPM25nE, prSAPI_roadOn);
        cnRoadPM25F = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM25LessF, prAQS_roadPM25GreatF, prPLO_roadPM25nF, prSAPI_roadOn);
        cnRoadPM25M = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM25LessM, prAQS_roadPM25GreatM, prPLO_roadPM25nM, prSAPI_roadOn);
        cnRoadPM25P = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM25LessP, prAQS_roadPM25GreatP, prPLO_roadPM25nP, prSAPI_roadOn);
        cnRoadPM25VP = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM25LessVP, prAQS_roadPM25GreatVP, prPLO_roadPM25nVP, prSAPI_roadOn);
        cnRoadPM25S = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM25GreatS, prPLO_roadPM25nS, prSAPI_roadOn);

        cnRoadPM10E = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM10LessE, prPLO_roadPM10nE, prSAPI_roadOn);
        cnRoadPM10F = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM10LessF, prAQS_roadPM10GreatF, prPLO_roadPM10nF, prSAPI_roadOn);
        cnRoadPM10M = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM10LessM, prAQS_roadPM10GreatM, prPLO_roadPM10nM, prSAPI_roadOn);
        cnRoadPM10P = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM10LessP, prAQS_roadPM10GreatP, prPLO_roadPM10nP, prSAPI_roadOn);
        cnRoadPM10VP = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM10LessVP, prAQS_roadPM10GreatVP, prPLO_roadPM10nVP, prSAPI_roadOn);
        cnRoadPM10S = NOP::BuildCondition<NOP::Conjunction>(prAQS_roadOn, prAQS_roadPM10GreatS, prPLO_roadPM10nS, prSAPI_roadOn);

        // Conditions for pm2.5 and pm10 in CityCenter
        cnCenterPM25E = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM25LessE, prPLO_centerPM25nE, prSAPI_centerOn);
        cnCenterPM25F = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM25LessF, prAQS_centerPM25GreatF, prPLO_centerPM25nF, prSAPI_centerOn);
        cnCenterPM25M = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM25LessM, prAQS_centerPM25GreatM, prPLO_centerPM25nM, prSAPI_centerOn);
        cnCenterPM25P = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM25LessP, prAQS_centerPM25GreatP, prPLO_centerPM25nP, prSAPI_centerOn);
        cnCenterPM25VP = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM25LessVP, prAQS_centerPM25GreatVP, prPLO_centerPM25nVP, prSAPI_centerOn);
        cnCenterPM25S = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM25GreatS, prPLO_centerPM25nS, prSAPI_centerOn);

        cnCenterPM10E = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM10LessE, prPLO_centerPM10nE, prSAPI_centerOn);
        cnCenterPM10F = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM10LessF, prAQS_centerPM10GreatF, prPLO_centerPM10nF, prSAPI_centerOn);
        cnCenterPM10M = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM10LessM, prAQS_centerPM10GreatM, prPLO_centerPM10nM, prSAPI_centerOn);
        cnCenterPM10P = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM10LessP, prAQS_centerPM10GreatP, prPLO_centerPM10nP, prSAPI_centerOn);
        cnCenterPM10VP = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM10LessVP, prAQS_centerPM10GreatVP, prPLO_centerPM10nVP, prSAPI_centerOn);
        cnCenterPM10S = NOP::BuildCondition<NOP::Conjunction>(prAQS_centerOn, prAQS_centerPM10GreatS, prPLO_centerPM10nS, prSAPI_centerOn);

        // Conditions for same pm2.5 and pm10 status in the whole city
        cnCityPM25E = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM25E, prPLO_roadPM25E, prPLO_centerPM25E);
        cnCityPM10E = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM10E, prPLO_roadPM10E, prPLO_centerPM10E);

        cnCityPM25F = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM25F, prPLO_roadPM25F, prPLO_centerPM25F);
        cnCityPM10F = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM10F, prPLO_roadPM10F, prPLO_centerPM10F);

        cnCityPM25M = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM25M, prPLO_roadPM25M, prPLO_centerPM25M);
        cnCityPM10M = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM10M, prPLO_roadPM10M, prPLO_centerPM10M);

        cnCityPM25P = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM25P, prPLO_roadPM25P, prPLO_centerPM25P);
        cnCityPM10P = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM10P, prPLO_roadPM10P, prPLO_centerPM10P);

        cnCityPM25VP = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM25VP, prPLO_roadPM25VP, prPLO_centerPM25VP);
        cnCityPM10VP = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM10VP, prPLO_roadPM10VP, prPLO_centerPM10VP);

        cnCityPM25S = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM25S, prPLO_roadPM25S, prPLO_centerPM25S);
        cnCityPM10S = NOP::BuildCondition<NOP::Conjunction>(prCAPI_cityOn, prPLO_uniPM10S, prPLO_roadPM10S, prPLO_centerPM10S);

        // Conditions for same pm2.5 and pm10 status in a particular spot
        cnUniPME = NOP::BuildCondition<NOP::Conjunction>(prSAPI_uniOn, prPLO_uniPM25E, prPLO_uniPM10E);
        cnUniPMF = NOP::BuildCondition<NOP::Conjunction>(prSAPI_uniOn, prPLO_uniPM25E, prPLO_uniPM10E);
        cnUniPMM = NOP::BuildCondition<NOP::Conjunction>(prSAPI_uniOn, prPLO_uniPM25M, prPLO_uniPM10M);
        cnUniPMP = NOP::BuildCondition<NOP::Conjunction>(prSAPI_uniOn, prPLO_uniPM25P, prPLO_uniPM10P);
        cnUniPMVP = NOP::BuildCondition<NOP::Conjunction>(prSAPI_uniOn, prPLO_uniPM25VP, prPLO_uniPM10VP);
        cnUniPMS = NOP::BuildCondition<NOP::Conjunction>(prSAPI_uniOn, prPLO_uniPM25S, prPLO_uniPM10S);

        cnRoadPME = NOP::BuildCondition<NOP::Conjunction>(prSAPI_roadOn, prPLO_roadPM25E, prPLO_roadPM10E);
        cnRoadPMF = NOP::BuildCondition<NOP::Conjunction>(prSAPI_roadOn, prPLO_roadPM25E, prPLO_roadPM10E);
        cnRoadPMM = NOP::BuildCondition<NOP::Conjunction>(prSAPI_roadOn, prPLO_roadPM25M, prPLO_roadPM10M);
        cnRoadPMP = NOP::BuildCondition<NOP::Conjunction>(prSAPI_roadOn, prPLO_roadPM25P, prPLO_roadPM10P);
        cnRoadPMVP = NOP::BuildCondition<NOP::Conjunction>(prSAPI_roadOn, prPLO_roadPM25VP, prPLO_roadPM10VP);
        cnRoadPMS = NOP::BuildCondition<NOP::Conjunction>(prSAPI_roadOn, prPLO_roadPM25S, prPLO_roadPM10S);

        cnCenterPME = NOP::BuildCondition<NOP::Conjunction>(prSAPI_centerOn, prPLO_centerPM25E, prPLO_centerPM10E);
        cnCenterPMF = NOP::BuildCondition<NOP::Conjunction>(prSAPI_centerOn, prPLO_centerPM25E, prPLO_centerPM10E);
        cnCenterPMM = NOP::BuildCondition<NOP::Conjunction>(prSAPI_centerOn, prPLO_centerPM25M, prPLO_centerPM10M);
        cnCenterPMP = NOP::BuildCondition<NOP::Conjunction>(prSAPI_centerOn, prPLO_centerPM25P, prPLO_centerPM10P);
        cnCenterPMVP = NOP::BuildCondition<NOP::Conjunction>(prSAPI_centerOn, prPLO_centerPM25VP, prPLO_centerPM10VP);
        cnCenterPMS = NOP::BuildCondition<NOP::Conjunction>(prSAPI_centerOn, prPLO_centerPM25S, prPLO_centerPM10S);

        // Actions with the Instigations
        // Instigations for pm2.5 and pm10 Spot Alert
        inUniPM25E = NOP::BuildInstigation(METHOD(SAPI_uni.pm25Alert("Excellent");));
        inUniPM10E = NOP::BuildInstigation(METHOD(SAPI_uni.pm10Alert("Excellent");));
        inUniPM25F = NOP::BuildInstigation(METHOD(SAPI_uni.pm25Alert("Fine");));
        inUniPM10F = NOP::BuildInstigation(METHOD(SAPI_uni.pm10Alert("Fine");));
        inUniPM25M = NOP::BuildInstigation(METHOD(SAPI_uni.pm25Alert("Moderate");));
        inUniPM10M = NOP::BuildInstigation(METHOD(SAPI_uni.pm10Alert("Moderate");));
        inUniPM25P = NOP::BuildInstigation(METHOD(SAPI_uni.pm25Alert("Poor");));
        inUniPM10P = NOP::BuildInstigation(METHOD(SAPI_uni.pm10Alert("Poor");));
        inUniPM25VP = NOP::BuildInstigation(METHOD(SAPI_uni.pm25Alert("Very Poor");));
        inUniPM10VP = NOP::BuildInstigation(METHOD(SAPI_uni.pm10Alert("Very Poor");));
        inUniPM25S = NOP::BuildInstigation(METHOD(SAPI_uni.pm25Alert("Severe");));
        inUniPM10S = NOP::BuildInstigation(METHOD(SAPI_uni.pm10Alert("Severe");));

        inRoadPM25E = NOP::BuildInstigation(METHOD(SAPI_road.pm25Alert("Excellent");));
        inRoadPM10E = NOP::BuildInstigation(METHOD(SAPI_road.pm10Alert("Excellent");));
        inRoadPM25F = NOP::BuildInstigation(METHOD(SAPI_road.pm25Alert("Fine");));
        inRoadPM10F = NOP::BuildInstigation(METHOD(SAPI_road.pm10Alert("Fine");));
        inRoadPM25M = NOP::BuildInstigation(METHOD(SAPI_road.pm25Alert("Moderate");));
        inRoadPM10M = NOP::BuildInstigation(METHOD(SAPI_road.pm10Alert("Moderate");));
        inRoadPM25P = NOP::BuildInstigation(METHOD(SAPI_road.pm25Alert("Poor");));
        inRoadPM10P = NOP::BuildInstigation(METHOD(SAPI_road.pm10Alert("Poor");));
        inRoadPM25VP = NOP::BuildInstigation(METHOD(SAPI_road.pm25Alert("Very Poor");));
        inRoadPM10VP = NOP::BuildInstigation(METHOD(SAPI_road.pm10Alert("Very Poor");));
        inRoadPM25S = NOP::BuildInstigation(METHOD(SAPI_road.pm25Alert("Severe");));
        inRoadPM10S = NOP::BuildInstigation(METHOD(SAPI_road.pm10Alert("Severe");));

        inCenterPM25E = NOP::BuildInstigation(METHOD(SAPI_center.pm25Alert("Excellent");));
        inCenterPM10E = NOP::BuildInstigation(METHOD(SAPI_center.pm10Alert("Excellent");));
        inCenterPM25F = NOP::BuildInstigation(METHOD(SAPI_center.pm25Alert("Fine");));
        inCenterPM10F = NOP::BuildInstigation(METHOD(SAPI_center.pm10Alert("Fine");));
        inCenterPM25M = NOP::BuildInstigation(METHOD(SAPI_center.pm25Alert("Moderate");));
        inCenterPM10M = NOP::BuildInstigation(METHOD(SAPI_center.pm10Alert("Moderate");));
        inCenterPM25P = NOP::BuildInstigation(METHOD(SAPI_center.pm25Alert("Poor");));
        inCenterPM10P = NOP::BuildInstigation(METHOD(SAPI_center.pm10Alert("Poor");));
        inCenterPM25VP = NOP::BuildInstigation(METHOD(SAPI_center.pm25Alert("Very Poor");));
        inCenterPM10VP = NOP::BuildInstigation(METHOD(SAPI_center.pm10Alert("Very Poor");));
        inCenterPM25S = NOP::BuildInstigation(METHOD(SAPI_center.pm25Alert("Severe");));
        inCenterPM10S = NOP::BuildInstigation(METHOD(SAPI_center.pm10Alert("Severe");));

        // Instigations for pm2.5 and pm10 status changing
        inPLO_UniPM25E = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM25("Excellent");));
        inPLO_UniPM10E = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM10("Excellent");));
        inPLO_UniPM25F = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM25("Fine");));
        inPLO_UniPM10F = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM10("Fine");));
        inPLO_UniPM25M = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM25("Moderate");));
        inPLO_UniPM10M = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM10("Moderate");));
        inPLO_UniPM25P = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM25("Poor");));
        inPLO_UniPM10P = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM10("Poor");));
        inPLO_UniPM25VP = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM25("Very Poor");));
        inPLO_UniPM10VP = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM10("Very Poor");));
        inPLO_UniPM25S = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM25("Severe");));
        inPLO_UniPM10S = NOP::BuildInstigation(METHOD(PLO_uni.changeStatusPM10("Severe");));

        inPLO_RoadPM25E = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM25("Excellent");));
        inPLO_RoadPM10E = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM10("Excellent");));
        inPLO_RoadPM25F = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM25("Fine");));
        inPLO_RoadPM10F = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM10("Fine");));
        inPLO_RoadPM25M = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM25("Moderate");));
        inPLO_RoadPM10M = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM10("Moderate");));
        inPLO_RoadPM25P = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM25("Poor");));
        inPLO_RoadPM10P = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM10("Poor");));
        inPLO_RoadPM25VP = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM25("Very Poor");));
        inPLO_RoadPM10VP = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM10("Very Poor");));
        inPLO_RoadPM25S = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM25("Severe");));
        inPLO_RoadPM10S = NOP::BuildInstigation(METHOD(PLO_road.changeStatusPM10("Severe");));

        inPLO_CenterPM25E = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM25("Excellent");));
        inPLO_CenterPM10E = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM10("Excellent");));
        inPLO_CenterPM25F = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM25("Fine");));
        inPLO_CenterPM10F = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM10("Fine");));
        inPLO_CenterPM25M = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM25("Moderate");));
        inPLO_CenterPM10M = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM10("Moderate");));
        inPLO_CenterPM25P = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM25("Poor");));
        inPLO_CenterPM10P = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM10("Poor");));
        inPLO_CenterPM25VP = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM25("Very Poor");));
        inPLO_CenterPM10VP = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM10("Very Poor");));
        inPLO_CenterPM25S = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM25("Severe");));
        inPLO_CenterPM10S = NOP::BuildInstigation(METHOD(PLO_center.changeStatusPM10("Severe");));

        // Instigations for alerting same status of pm2.5 and pm10 in the whole city
        inCityPM25E = NOP::BuildInstigation(METHOD(CAPI_city.pm25AlertCity("Excellent");));
        inCityPM10E = NOP::BuildInstigation(METHOD(CAPI_city.pm10AlertCity("Excellent");));
        inCityPM25F = NOP::BuildInstigation(METHOD(CAPI_city.pm25AlertCity("Fine");));
        inCityPM10F = NOP::BuildInstigation(METHOD(CAPI_city.pm10AlertCity("Fine");));
        inCityPM25M = NOP::BuildInstigation(METHOD(CAPI_city.pm25AlertCity("Moderate");));
        inCityPM10M = NOP::BuildInstigation(METHOD(CAPI_city.pm10AlertCity("Moderate");));
        inCityPM25P = NOP::BuildInstigation(METHOD(CAPI_city.pm25AlertCity("Poor");));
        inCityPM10P = NOP::BuildInstigation(METHOD(CAPI_city.pm10AlertCity("Poor");));
        inCityPM25VP = NOP::BuildInstigation(METHOD(CAPI_city.pm25AlertCity("Very Poor");));
        inCityPM10VP = NOP::BuildInstigation(METHOD(CAPI_city.pm10AlertCity("Very Poor");));
        inCityPM25S = NOP::BuildInstigation(METHOD(CAPI_city.pm25AlertCity("Severe");));
        inCityPM10S = NOP::BuildInstigation(METHOD(CAPI_city.pm10AlertCity("Severe");));

        // Instigations for pm pollution in a particular spot
        inUniPME = NOP::BuildInstigation(METHOD(SAPI_uni.pmPollutionAlertOnSpot("Excellent");));
        inUniPMF = NOP::BuildInstigation(METHOD(SAPI_uni.pmPollutionAlertOnSpot("Fine");));
        inUniPMM = NOP::BuildInstigation(METHOD(SAPI_uni.pmPollutionAlertOnSpot("Moderate");));
        inUniPMP = NOP::BuildInstigation(METHOD(SAPI_uni.pmPollutionAlertOnSpot("Poor");));
        inUniPMVP = NOP::BuildInstigation(METHOD(SAPI_uni.pmPollutionAlertOnSpot("Very Poor");));
        inUniPMS = NOP::BuildInstigation(METHOD(SAPI_uni.pmPollutionAlertOnSpot("Severe");));

        inRoadPME = NOP::BuildInstigation(METHOD(SAPI_road.pmPollutionAlertOnSpot("Excellent");));
        inRoadPMF = NOP::BuildInstigation(METHOD(SAPI_road.pmPollutionAlertOnSpot("Fine");));
        inRoadPMM = NOP::BuildInstigation(METHOD(SAPI_road.pmPollutionAlertOnSpot("Moderate");));
        inRoadPMP = NOP::BuildInstigation(METHOD(SAPI_road.pmPollutionAlertOnSpot("Poor");));
        inRoadPMVP = NOP::BuildInstigation(METHOD(SAPI_road.pmPollutionAlertOnSpot("Very Poor");));
        inRoadPMS = NOP::BuildInstigation(METHOD(SAPI_road.pmPollutionAlertOnSpot("Severe");));

        inCenterPME = NOP::BuildInstigation(METHOD(SAPI_center.pmPollutionAlertOnSpot("Excellent");));
        inCenterPMF = NOP::BuildInstigation(METHOD(SAPI_center.pmPollutionAlertOnSpot("Fine");));
        inCenterPMM = NOP::BuildInstigation(METHOD(SAPI_center.pmPollutionAlertOnSpot("Moderate");));
        inCenterPMP = NOP::BuildInstigation(METHOD(SAPI_center.pmPollutionAlertOnSpot("Poor");));
        inCenterPMVP = NOP::BuildInstigation(METHOD(SAPI_center.pmPollutionAlertOnSpot("Very Poor");));
        inCenterPMS = NOP::BuildInstigation(METHOD(SAPI_center.pmPollutionAlertOnSpot("Severe");));

        // Actions
        // Actions for pm2.5 and pm10 in University
        acUniPM25E = NOP::BuildAction(inUniPM25E, inPLO_UniPM25E);
        acUniPM10E = NOP::BuildAction(inUniPM10E, inPLO_UniPM10E);
        acUniPM25F = NOP::BuildAction(inUniPM25F, inPLO_UniPM25F);
        acUniPM10F = NOP::BuildAction(inUniPM10F, inPLO_UniPM10F);
        acUniPM25M = NOP::BuildAction(inUniPM25M, inPLO_UniPM25M);
        acUniPM10M = NOP::BuildAction(inUniPM10M, inPLO_UniPM10M);
        acUniPM25P = NOP::BuildAction(inUniPM25P, inPLO_UniPM25P);
        acUniPM10P = NOP::BuildAction(inUniPM10P, inPLO_UniPM10P);
        acUniPM25VP = NOP::BuildAction(inUniPM25VP, inPLO_UniPM25VP);
        acUniPM10VP = NOP::BuildAction(inUniPM10VP, inPLO_UniPM10VP);
        acUniPM25S = NOP::BuildAction(inUniPM25S, inPLO_UniPM25S);
        acUniPM10S = NOP::BuildAction(inUniPM10S, inPLO_UniPM10S);

        // Actions for pm2.5 and pm10 in RoadSide
        acRoadPM25E = NOP::BuildAction(inRoadPM25E, inPLO_RoadPM25E);
        acRoadPM10E = NOP::BuildAction(inRoadPM10E, inPLO_RoadPM10E);
        acRoadPM25F = NOP::BuildAction(inRoadPM25F, inPLO_RoadPM25F);
        acRoadPM10F = NOP::BuildAction(inRoadPM10F, inPLO_RoadPM10F);
        acRoadPM25M = NOP::BuildAction(inRoadPM25M, inPLO_RoadPM25M);
        acRoadPM10M = NOP::BuildAction(inRoadPM10M, inPLO_RoadPM10M);
        acRoadPM25P = NOP::BuildAction(inRoadPM25P, inPLO_RoadPM25P);
        acRoadPM10P = NOP::BuildAction(inRoadPM10P, inPLO_RoadPM10P);
        acRoadPM25VP = NOP::BuildAction(inRoadPM25VP, inPLO_RoadPM25VP);
        acRoadPM10VP = NOP::BuildAction(inRoadPM10VP, inPLO_RoadPM10VP);
        acRoadPM25S = NOP::BuildAction(inRoadPM25S, inPLO_RoadPM25S);
        acRoadPM10S = NOP::BuildAction(inRoadPM10S, inPLO_RoadPM10S);

        // Actions for pm2.5 and pm10 in CityCenter
        acCenterPM25E = NOP::BuildAction(inCenterPM25E, inPLO_CenterPM25E);
        acCenterPM10E = NOP::BuildAction(inCenterPM10E, inPLO_CenterPM10E);
        acCenterPM25F = NOP::BuildAction(inCenterPM25F, inPLO_CenterPM25F);
        acCenterPM10F = NOP::BuildAction(inCenterPM10F, inPLO_CenterPM10F);
        acCenterPM25M = NOP::BuildAction(inCenterPM25M, inPLO_CenterPM25M);
        acCenterPM10M = NOP::BuildAction(inCenterPM10M, inPLO_CenterPM10M);
        acCenterPM25P = NOP::BuildAction(inCenterPM25P, inPLO_CenterPM25P);
        acCenterPM10P = NOP::BuildAction(inCenterPM10P, inPLO_CenterPM10P);
        acCenterPM25VP = NOP::BuildAction(inCenterPM25VP, inPLO_CenterPM25VP);
        acCenterPM10VP = NOP::BuildAction(inCenterPM10VP, inPLO_CenterPM10VP);
        acCenterPM25S = NOP::BuildAction(inCenterPM25S, inPLO_CenterPM25S);
        acCenterPM10S = NOP::BuildAction(inCenterPM10S, inPLO_CenterPM10S);

        // Actions for same pm2.5 and pm10 status in the whole city
        acCityPM25E = NOP::BuildAction(inCityPM25E);
        acCityPM10E = NOP::BuildAction(inCityPM10E);
        acCityPM25F = NOP::BuildAction(inCityPM25F);
        acCityPM10F = NOP::BuildAction(inCityPM10F);
        acCityPM25M = NOP::BuildAction(inCityPM25M);
        acCityPM10M = NOP::BuildAction(inCityPM10M);
        acCityPM25P = NOP::BuildAction(inCityPM25P);
        acCityPM10P = NOP::BuildAction(inCityPM10P);
        acCityPM25VP = NOP::BuildAction(inCityPM25VP);
        acCityPM10VP = NOP::BuildAction(inCityPM10VP);
        acCityPM25S = NOP::BuildAction(inCityPM25S);
        acCityPM10S = NOP::BuildAction(inCityPM10S);

        // Actions for same pm2.5 and pm10 status in a particular spot
        acUniPME = NOP::BuildAction(inUniPME);
        acUniPMF = NOP::BuildAction(inUniPMF);
        acUniPMM = NOP::BuildAction(inUniPMM);
        acUniPMP = NOP::BuildAction(inUniPMP);
        acUniPMVP = NOP::BuildAction(inUniPMVP);
        acUniPMS = NOP::BuildAction(inUniPMS);

        acRoadPME = NOP::BuildAction(inRoadPME);
        acRoadPMF = NOP::BuildAction(inRoadPMF);
        acRoadPMM = NOP::BuildAction(inRoadPMM);
        acRoadPMP = NOP::BuildAction(inRoadPMP);
        acRoadPMVP = NOP::BuildAction(inRoadPMVP);
        acRoadPMS = NOP::BuildAction(inRoadPMS);

        acCenterPME = NOP::BuildAction(inCenterPME);
        acCenterPMF = NOP::BuildAction(inCenterPMF);
        acCenterPMM = NOP::BuildAction(inCenterPMM);
        acCenterPMP = NOP::BuildAction(inCenterPMP);
        acCenterPMVP = NOP::BuildAction(inCenterPMVP);
        acCenterPMS = NOP::BuildAction(inCenterPMS);

        // Rules
        // Rules for pm2.5 and pm10 in University
        rlUniPM25E = NOP::BuildRule(cnUniPM25E, acUniPM25E);
        rlUniPM10E = NOP::BuildRule(cnUniPM10E, acUniPM10E);
        rlUniPM25F = NOP::BuildRule(cnUniPM25F, acUniPM25F);
        rlUniPM10F = NOP::BuildRule(cnUniPM10F, acUniPM10F);
        rlUniPM25M = NOP::BuildRule(cnUniPM25M, acUniPM25M);
        rlUniPM10M = NOP::BuildRule(cnUniPM10M, acUniPM10M);
        rlUniPM25P = NOP::BuildRule(cnUniPM25P, acUniPM25P);
        rlUniPM10P = NOP::BuildRule(cnUniPM10P, acUniPM10P);
        rlUniPM25VP = NOP::BuildRule(cnUniPM25VP, acUniPM25VP);
        rlUniPM10VP = NOP::BuildRule(cnUniPM10VP, acUniPM10VP);
        rlUniPM25S = NOP::BuildRule(cnUniPM25S, acUniPM25S);
        rlUniPM10S = NOP::BuildRule(cnUniPM10S, acUniPM10S);

        // Rules for pm2.5 and pm10 in RoadSide
        rlRoadPM25E = NOP::BuildRule(cnRoadPM25E, acRoadPM25E);
        rlRoadPM10E = NOP::BuildRule(cnRoadPM10E, acRoadPM10E);
        rlRoadPM25F = NOP::BuildRule(cnRoadPM25F, acRoadPM25F);
        rlRoadPM10F = NOP::BuildRule(cnRoadPM10F, acRoadPM10F);
        rlRoadPM25M = NOP::BuildRule(cnRoadPM25M, acRoadPM25M);
        rlRoadPM10M = NOP::BuildRule(cnRoadPM10M, acRoadPM10M);
        rlRoadPM25P = NOP::BuildRule(cnRoadPM25P, acRoadPM25P);
        rlRoadPM10P = NOP::BuildRule(cnRoadPM10P, acRoadPM10P);
        rlRoadPM25VP = NOP::BuildRule(cnRoadPM25VP, acRoadPM25VP);
        rlRoadPM10VP = NOP::BuildRule(cnRoadPM10VP, acRoadPM10VP);
        rlRoadPM25S = NOP::BuildRule(cnRoadPM25S, acRoadPM25S);
        rlRoadPM10S = NOP::BuildRule(cnRoadPM10S, acRoadPM10S);

        // Rules for pm2.5 and pm10 in CityCenter
        rlCenterPM25E = NOP::BuildRule(cnCenterPM25E, acCenterPM25E);
        rlCenterPM10E = NOP::BuildRule(cnCenterPM10E, acCenterPM10E);
        rlCenterPM25F = NOP::BuildRule(cnCenterPM25F, acCenterPM25F);
        rlCenterPM10F = NOP::BuildRule(cnCenterPM10F, acCenterPM10F);
        rlCenterPM25M = NOP::BuildRule(cnCenterPM25M, acCenterPM25M);
        rlCenterPM10M = NOP::BuildRule(cnCenterPM10M, acCenterPM10M);
        rlCenterPM25P = NOP::BuildRule(cnCenterPM25P, acCenterPM25P);
        rlCenterPM10P = NOP::BuildRule(cnCenterPM10P, acCenterPM10P);
        rlCenterPM25VP = NOP::BuildRule(cnCenterPM25VP, acCenterPM25VP);
        rlCenterPM10VP = NOP::BuildRule(cnCenterPM10VP, acCenterPM10VP);
        rlCenterPM25S = NOP::BuildRule(cnCenterPM25S, acCenterPM25S);
        rlCenterPM10S = NOP::BuildRule(cnCenterPM10S, acCenterPM10S);

        // Rules same pm2.5 and pm10 status in the whole city
        rlCityPM25E = NOP::BuildRule(cnCityPM25E, acCityPM25E);
        rlCityPM10E = NOP::BuildRule(cnCityPM10E, acCityPM10E);
        rlCityPM25F = NOP::BuildRule(cnCityPM25F, acCityPM25F);
        rlCityPM10F = NOP::BuildRule(cnCityPM10F, acCityPM10F);
        rlCityPM25M = NOP::BuildRule(cnCityPM25M, acCityPM25M);
        rlCityPM10M = NOP::BuildRule(cnCityPM10M, acCityPM10M);
        rlCityPM25P = NOP::BuildRule(cnCityPM25P, acCityPM25P);
        rlCityPM10P = NOP::BuildRule(cnCityPM10P, acCityPM10P);
        rlCityPM25VP = NOP::BuildRule(cnCityPM25VP, acCityPM25VP);
        rlCityPM10VP = NOP::BuildRule(cnCityPM10VP, acCityPM10VP);
        rlCityPM25S = NOP::BuildRule(cnCityPM25S, acCityPM25S);
        rlCityPM10S = NOP::BuildRule(cnCityPM10S, acCityPM10S);

        // Rules for same pm2.5 and pm10 status in a particular spot
        rlUniPME = NOP::BuildRule(cnUniPME, acUniPME);
        rlUniPMF = NOP::BuildRule(cnUniPMF, acUniPMF);
        rlUniPMM = NOP::BuildRule(cnUniPMM, acUniPMM);
        rlUniPMP = NOP::BuildRule(cnUniPMP, acUniPMP);
        rlUniPMVP = NOP::BuildRule(cnUniPMVP, acUniPMVP);
        rlUniPMS = NOP::BuildRule(cnUniPMS, acUniPMS);

        rlRoadPME = NOP::BuildRule(cnRoadPME, acRoadPME);
        rlRoadPMF = NOP::BuildRule(cnRoadPMF, acRoadPMF);
        rlRoadPMM = NOP::BuildRule(cnRoadPMM, acRoadPMM);
        rlRoadPMP = NOP::BuildRule(cnRoadPMP, acRoadPMP);
        rlRoadPMVP = NOP::BuildRule(cnRoadPMVP, acRoadPMVP);
        rlRoadPMS = NOP::BuildRule(cnRoadPMS, acRoadPMS);

        rlCenterPME = NOP::BuildRule(cnCenterPME, acCenterPME);
        rlCenterPMF = NOP::BuildRule(cnCenterPMF, acCenterPMF);
        rlCenterPMM = NOP::BuildRule(cnCenterPMM, acCenterPMM);
        rlCenterPMP = NOP::BuildRule(cnCenterPMP, acCenterPMP);
        rlCenterPMVP = NOP::BuildRule(cnCenterPMVP, acCenterPMVP);
        rlCenterPMS = NOP::BuildRule(cnCenterPMS, acCenterPMS);
    }
};
