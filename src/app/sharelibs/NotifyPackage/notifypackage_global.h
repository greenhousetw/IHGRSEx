#ifndef NOTIFYPACKAGE_GLOBAL_H
#define NOTIFYPACKAGE_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(NOTIFYPACKAGE_LIBRARY)
#  define NOTIFYPACKAGESHARED_EXPORT Q_DECL_EXPORT
#else
#  define NOTIFYPACKAGESHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // NOTIFYPACKAGE_GLOBAL_H
