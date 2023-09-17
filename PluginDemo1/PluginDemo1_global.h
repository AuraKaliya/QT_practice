#ifndef PLUGINDEMO1_GLOBAL_H
#define PLUGINDEMO1_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PLUGINDEMO1_LIBRARY)
#  define PLUGINDEMO1_EXPORT Q_DECL_EXPORT
#else
#  define PLUGINDEMO1_EXPORT Q_DECL_IMPORT
#endif

#endif // PLUGINDEMO1_GLOBAL_H
