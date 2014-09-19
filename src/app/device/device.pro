TEMPLATE = subdirs

SUBDIRS += \
    Hardware \
    SensorUnit \
    IDeviceFactory \
    SensorPlugInLoader \
    Tranceiver \
    TrancieverLoader

CONFIG += ordered
