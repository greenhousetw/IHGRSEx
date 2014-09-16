#ifndef HARDWARE_GLOBAL_H
#define HARDWARE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(HARDWARE_LIBRARY)
#  define HARDWARESHARED_EXPORT Q_DECL_EXPORT
#else
#  define HARDWARESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // HARDWARE_GLOBAL_H