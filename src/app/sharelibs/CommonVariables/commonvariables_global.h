#ifndef COMMONVARIABLES_GLOBAL_H
#define COMMONVARIABLES_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(COMMONVARIABLES_LIBRARY)
#  define COMMONVARIABLESSHARED_EXPORT Q_DECL_EXPORT
#else
#  define COMMONVARIABLESSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // COMMONVARIABLES_GLOBAL_H
