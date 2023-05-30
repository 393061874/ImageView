#ifndef MMPOSEAPI_GLOBAL_H
#define MMPOSEAPI_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MMPOSEAPI_LIBRARY)
#  define MMPOSEAPI_EXPORT Q_DECL_EXPORT
#else
#  define MMPOSEAPI_EXPORT Q_DECL_IMPORT
#endif

#endif // MMPOSEAPI_GLOBAL_H
