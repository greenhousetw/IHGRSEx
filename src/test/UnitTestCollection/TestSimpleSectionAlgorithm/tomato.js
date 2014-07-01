function Temprature(lastTime, value){
    var jsonString="";

    var timeDiff=0;

    if(parseFloat(value) > 99 ){

        if(timeDiff ==0 || timeDiff < 0 )
        {
            jsonString="{\"section\": \"1\",\"equipments\": [ {\"fan\": \"fan.on\"},{\"light\": \"light.on\"}]}";
        }
        else
        {
            jsonString="{\"section\": \"1\",\"lasttime\": \"Time\"}";
        }
    }
    else if (parseFloat(value)<50 && parseFloat(value) > 0)
    {
        jsonString="{\"section\": \"2\",\"equipments\": [ {\"fan\": \"on\"},{\"light\": \"off\"}]}";
    }
    else if (parseFloat(value) < 0)
    {
        jsonString="{\"section\": \"3\",\"equipments\": [ {\"fan\": \"off\"},{\"light\": \"off\"}]}";
    }

    return jsonString;
};

function Humid(lastTime, value){
    if(parseFloat(value) > 99){
       jsonString="[{'section':'1'},{'equipment':'fan','status':'on'},{'equipment':'light','status':'off'}]";
    }
};

function Light(lastTime, value){
    if(parseFloat(value) > 99){
       jsonString="[{'section':'1'},{'equipment':'fan','status':'on'},{'equipment':'light','status':'off'}]";
    }
};
