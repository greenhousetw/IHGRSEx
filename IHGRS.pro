TEMPLATE=subdirs

SUBDIRS += \
    src/app/sharelibs \    
    src/app/core/Core \
    src/app/Repository \
    src/app/algorithms \
    src/app/device \        
    src/app/console \
    src/test/TestSharelibs \
    src/test/UnitTestCollection

CONFIG += ordered

