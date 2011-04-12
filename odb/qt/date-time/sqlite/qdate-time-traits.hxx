// file      : odb/qt/date-time/sqlite/qdatetime-traits.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_QT_DATE_TIME_SQLITE_QDATETIME_TRAITS_HXX
#define ODB_QT_DATE_TIME_SQLITE_QDATETIME_TRAITS_HXX

#include <odb/pre.hxx>

#include <string>
#include <cstddef>  // std::size_t
#include <cstring>  // std::memcpy

#include <QDateTime>

#include <odb/details/buffer.hxx>
#include <odb/sqlite/traits.hxx>
#include <odb/qt/date-time/exceptions.hxx>

namespace odb
{
  namespace sqlite
  {
    template <>
    class default_value_traits<QDateTime, details::buffer, id_text>
    {
    public:
      typedef QDateTime value_type;
      typedef QDateTime query_type;
      typedef details::buffer image_type;

      static void
      set_value (QDateTime& v,
                 const details::buffer& i,
                 std::size_t n,
                 bool is_null)
      {
        if (is_null)
          // Default constructor creates a null QDateTime.
          //
          v = QDateTime ();
        else
          v = QDateTime::fromString (
            QString::fromAscii (i.data (), static_cast<int> (n)),
            "yyyy-MM-ddTHH:mm:ss.zzz");
      }

      static void
      set_image (details::buffer& i,
                 std::size_t& n,
                 bool& is_null,
                 const QDateTime& v)
      {
        if (v.isNull ())
          is_null = true;
        else
        {
          is_null = false;

          std::string s (
            v.toString ("yyyy-MM-ddTHH:mm:ss.zzz").toStdString ());

          n = s.size ();
          if (n > i.capacity ())
            i.capacity (n);

          std::memcpy (i.data (), s.data (), n);
        }
      }
    };

    // Implementation of mapping between QDateTime and SQLite INTEGER.
    // The integer value represents UNIX time.
    //
    template <>
    class default_value_traits<QDateTime, long long, id_integer>
    {
    public:
      typedef QDateTime value_type;
      typedef QDateTime query_type;
      typedef long long image_type;

      static void
      set_value (QDateTime& v, long long i, bool is_null)
      {
        if (is_null)
          // Default constructor creates a null QDateTime.
          //
          v = QDateTime ();
        else
        {
          v.setTimeSpec (Qt::UTC);
          v.setTime_t (static_cast <uint> (i));
        }
      }

      static void
      set_image (long long& i, bool& is_null, const QDateTime& v)
      {
        if (v.isNull ())
          is_null = true;
        else if (v < QDateTime (QDate (1970, 1, 1),
                                QTime (0, 0, 0),
                                Qt::UTC))
          throw odb::qt::date_time::value_out_of_range ();
        else
        {
          is_null = false;
          i = static_cast<long long> (v.toTime_t ());
        }
      }
    };

    template <>
    class default_type_traits<QDateTime>
    {
      static const database_type_id db_type_id = id_text;
    };
  }
}

#endif // ODB_QT_DATE_TIME_SQLITE_QDATETIME_TRAITS_HXX