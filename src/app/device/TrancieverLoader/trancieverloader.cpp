#include "trancieverloader.h"


TrancieverLoader::TrancieverLoader()
{
}

IHardware* TrancieverLoader::GetDevice(QMap<QString, QVariant> configs)
{
    IHardware *tranciever=new Tranceiver;
    tranciever->SetHardware(configs);
    return tranciever;
}

