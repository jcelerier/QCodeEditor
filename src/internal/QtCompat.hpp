#pragma once
#include <qobjectdefs.h>

#if QT_VERSION < QT_VERSION_CHECK(5, 10, 0)
#include <QString>
#include <QStringRef>

inline bool operator==(const QString& lhs, const char16_t* rhs) {
  return lhs == QString::fromUtf16(reinterpret_cast<const ushort *>(rhs));
}
inline bool operator==(const QStringRef& lhs, const char16_t* rhs) {
  return lhs == QString::fromUtf16(reinterpret_cast<const ushort *>(rhs));
}
#endif
