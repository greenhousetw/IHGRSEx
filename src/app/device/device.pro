TEMPLATE = subdirs

SUBDIRS += \
    Hardware \
    SensorUnit \
    IDeviceFactory \
    SensorPlugInLoader \
    Tranceiver \
    TrancieverLoader \
    DeviceManager

CONFIG += ordered
