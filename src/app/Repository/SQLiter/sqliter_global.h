#ifndef SQLITER_GLOBAL_H
#define SQLITER_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(SQLITER_LIBRARY)
#  define SQLITERSHARED_EXPORT Q_DECL_EXPORT
#else
#  define SQLITERSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // SQLITER_GLOBAL_H
