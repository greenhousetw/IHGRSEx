/********************************************************************************************
Copyright (C) YuHua

tomato.js
Purpose:
This js file focuses on tomato, so if you want to use this js, please add this file into:
Algorithm.Simple.Setup.xml

note! if you want to chreate new profile for other stuff~ please follow the format~

Name of function means Sensor type, now we support: Temprature, Humid, Light~

{section:integer, minuteDiff:integer, unitseconds:integer, equipments[{'devicename':'status',..}]
"unitseconds" means sampling value, if this value is 1: check every second, is 60: means that you
do check every 1 minute

@author Yu-Hua Tseng
@version Test.V1 07/02/2014

********************************************************************************************/
function Temprature(value){

    var jsonString="";

    if(parseFloat(value) >= 99 ){
            jsonString="{\"section\": \"1\",\"unitseconds\": \"1\",\"minuteDiff\":\"3\",\"equipments\": [{\"coolingfan\": \"coolingfan.on\"},{\"internalantisun\": \"internalantisun.on\"}]}";
    }
    else if (parseFloat(value)<=50 && parseFloat(value) >= 0)
    {
        jsonString="{\"section\": \"2\",\"unitseconds\": \"1\",\"minuteDiff\":\"5\",\"equipments\": [ {\"coolingfan\": \"coolingfan.off\"},{\"mixer\": \"mixer.off\"}]}";
        //jsonString="{\"section\": \"2\",\"lasttime\": \"" + _currenttime + "\"}";
    }
    else if (parseFloat(value) < 0)
    {
        jsonString="{\"section\": \"3\",\"unitseconds\": \"1\",\"minuteDiff\":\"9\",\"equipments\": [ {\"coolingfan\": \"fan.on\"},{\"mixer\": \"mixer.off\"}]}";
    }

    return jsonString;
};

function Humid(value){
    if(parseFloat(value) > 99){
       jsonString="[{'section':'1'},{'equipment':'fan','status':'on'},{'equipment':'light','status':'off'}]";
    }
};

function Light(value){
    if(parseFloat(value) > 99){
       jsonString="[{'section':'1'},{'equipment':'fan','status':'on'},{'equipment':'light','status':'off'}]";
    }
};

/**
*
*/
function getTimeDiff(startDateFormat, endDateFormat){
    var timeStart = new Date(startDateFormat);
    var timeEnd = new Date(endDateFormat);
    var hourDiff = timeEnd - timeStart; //in ms
    var secDiff = hourDiff / 1000; //in s
    var minDiff = hourDiff / 60 / 1000; //in minutes
    var hDiff = hourDiff / 3600 / 1000; //in hours

    var hours = Math.floor(hDiff);
    var minutes = minDiff - 60 * humanReadable.hours;
    return minutes;
}
