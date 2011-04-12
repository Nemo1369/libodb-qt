// file      : odb/qt/basic/sqlite/default-mapping.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_QT_BASIC_SQLITE_DEFAULT_MAPPING_HXX
#define ODB_QT_BASIC_SQLITE_DEFAULT_MAPPING_HXX

#include <QString>
#include <QByteArray>

// Map QString to SQLite TEXT by default. Allow NULL values by default as
// QString provides a null representation.
//
#pragma db value(QString) type("TEXT")

// Map QByteArray to SQLite TEXT by default. Allow NULL values by default as
// QByteArray provides a null representation.
//
#pragma db value(QByteArray) type("BLOB")

#endif // ODB_QT_BASIC_SQLITE_DEFAULT_MAPPING_HXX