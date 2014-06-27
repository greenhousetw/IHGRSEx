function temprature(value){
    var jsonString="";

    if(parseFloat(value) > 99){
        jsonString="{\"section\": \"1\",\"equipments\": [ {\"fan\": \"fan.on\"},{\"light\": \"light.on\"}]}";
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

function humid(value){
    if(parseFloat(value) > 99){
       jsonString="[{'section':'1'},{'equipment':'fan','status':'on'},{'equipment':'light','status':'off'}]";
    }
};

function light(value){
    if(parseFloat(value) > 99){
       jsonString="[{'section':'1'},{'equipment':'fan','status':'on'},{'equipment':'light','status':'off'}]";
    }
};
