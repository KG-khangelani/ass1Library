#pragma once
#include <QtGlobal>

#if defined(LIBRARYUTILS_LIBRARY)
#define LIBUTILS_EXPORT Q_DECL_EXPORT
#else
#define LIBUTILS_EXPORT Q_DECL_IMPORT
#endif
