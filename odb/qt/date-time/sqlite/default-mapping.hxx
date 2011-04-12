// file      : odb/qt/date-time/sqlite/default-mapping.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_QT_DATE_TIME_SQLITE_DEFAULT_MAPPING_HXX
#define ODB_QT_DATE_TIME_SQLITE_DEFAULT_MAPPING_HXX

#include <QDate>
#include <QTime>
#include <QDateTime>

// Map QDate to SQLite TEXT by default. QDate provides a null representation
// so allow NULL values by default.
//
#pragma db value(QDate) type("TEXT")

// Map QTime to SQLite TEXT by default. QTime provides a null representation
// so allow NULL values by default.
//
#pragma db value(QTime) type("TEXT")

// Map QDateTime to SQLite TEXT by default. QDateTime provides a null
// representation so allow NULL values by default.
//
#pragma db value(QDateTime) type("TEXT")

#endif // ODB_QT_DATE_TIME_SQLITE_DEFAULT_MAPPING_HXX