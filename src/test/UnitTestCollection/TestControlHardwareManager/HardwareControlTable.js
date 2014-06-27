function gethardwareCtype(machinestatus){

    var controltable=
    {
       "coolingfan.on": {
               "address": "03",
               "code": "301"
           },
        "coolingfan.off": {
               "address": "03",
               "code": "301"
           },
        "exhaustfan.on": {
                "address": "03",
                "code": "303"
            },
         "exhaustfan.off": {
                "address": "03",
                "code": "304"
            },
        "exhaustfanlv1.on": {
                "address": "03",
                "code": "305"
            },
        "exhaustfanlv2.on": {
                "address": "03",
                "code": "306"
            },
        "exhaustfanlv3.on": {
                "address": "03",
                "code": "307"
            },
        "exhaustfanlv4.on": {
                "address": "03",
                "code": "308"
            },
        "exhaustfanlv5.on": {
                "address": "03",
                "code": "309"
            },
        "exhaustfan.lvoff.on": {
                "address": "03",
                "code": "310"
            },
        "pump.on": {
                "address": "05",
                "code": "351"
            },
         "pump.off": {
                "address": "05",
                "code": "352"
            },
        "internalantisun.on": {
                "address": "05",
                "code": "353"
            },
         "internalantisun.off": {
                "address": "05",
                "code": "354"
            },
        "externalantisun.on": {
                "address": "05",
                "code": "355"
            },
         "externalantisun.off": {
                "address": "05",
                "code": "356"
            },
        "warmingmahcine.on": {
                "address": "05",
                "code": "357"
            },
         "warmingmahcine.off": {
                "address": "05",
                "code": "358"
            },
        "dehumid.on": {
                "address": "05",
                "code": "359"
            },
         "dehumid.off": {
                "address": "05",
                "code": "360"
            },
        "ultrasonic.on": {
                "address": "05",
                "code": "361"
            },
         "ultrasonic.off": {
                "address": "05",
                "code": "362"
            },
        "lightingall.on": {
               "address": "05",
               "code": "401"
           },
        "lightingno1no2.on": {
               "address": "05",
               "code": "402"
           },
        "lightingno3no4.on": {
               "address": "05",
               "code": "403"
           },
        "lightingno1no3.on": {
               "address": "05",
               "code": "404"
           },
        "lightingno2no4.on": {
               "address": "05",
               "code": "405"
           },
        "lightingall.off": {
               "address": "05",
               "code": "406"
           },
        "waterprovider.on": {
               "address": "05",
               "code": "451"
           },
        "waterprovider.off": {
               "address": "05",
               "code": "452"
           },
        "condensedliquid.on": {
               "address": "05",
               "code": "453"
           },
        "condensedliquid.off": {
               "address": "05",
               "code": "454"
           },
        "nutrient.on": {
               "address": "05",
               "code": "455"
           },
        "nutrient.off": {
               "address": "05",
               "code": "456"
           },
        "mixer.on": {
               "address": "05",
               "code": "457"
           },
        "mixer.off": {
               "address": "05",
               "code": "458"
           },
    };

    return "C"+controltable[machinestatus].address + controltable[machinestatus].code;
}

function gethardwareQtype(nodeid, target){

    var controltable={
        "room.temprature":"001",
        "room.humid":"002",
        "room.light":"003",
        "room.all":"004",
        "room.co2":"005",
        "liquid.ec":"006",
        "liquid.ph":"007",
        "liquid.do":"008",
        "liquid.temprature":"009",
        "liquid.all":"010",
        "room.C":"011",
        "room.F":"012",
        "room.humid%":"013",
        "room.C%":"014",
        "room.F%":"015"
    };

    return "Q" + nodeid + controltable[target];
}

function gethardwareRtype(nodeid, target){

    var controltable={
        "config":"851",
    };

    return "R" + nodeid + controltable[target];
}

function gethardwareStype(nodeid, target){

    var controltable={
        "setC":"901",
        "setF":"902",
        "LutronA":"903",
        "LutronB":"904",
        "LutronC":"905",
    };

    return "S" + nodeid + controltable[target];
}
