#ifndef DLL1_GLOBAL_H
#define DLL1_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(DLL1_LIBRARY)
#  define DLL1SHARED_EXPORT Q_DECL_EXPORT
#else
#  define DLL1SHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // DLL1_GLOBAL_H
