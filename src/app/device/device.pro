TEMPLATE = subdirs

SUBDIRS += \
    Hardware \
    SensorUnit \
    IDeviceFactory \
    SensorPlugInLoader \
    Tranceiver \
    TrancieverLoader \
    DeviceManager \
    qextserialport

CONFIG += ordered
