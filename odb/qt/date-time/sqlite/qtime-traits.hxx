// file      : odb/qt/date-time/sqlite/qtime-traits.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_QT_DATE_TIME_SQLITE_QTIME_TRAITS_HXX
#define ODB_QT_DATE_TIME_SQLITE_QTIME_TRAITS_HXX

#include <odb/pre.hxx>

#include <string>
#include <cstddef>  // std::size_t
#include <cstring>  // std::memcpy

#include <QTime>

#include <odb/details/buffer.hxx>
#include <odb/sqlite/traits.hxx>

namespace odb
{
  namespace sqlite
  {
    template <>
    class default_value_traits<QTime, details::buffer, id_text>
    {
    public:
      typedef QTime value_type;
      typedef QTime query_type;
      typedef details::buffer image_type;

      static void
      set_value (QTime& v,
                 const details::buffer& i,
                 std::size_t n,
                 bool is_null)
      {
        if (is_null)
          // A null QTime value is equivalent to an invalid QTime value.
          // Set v to an invalid time to represent null (hour value of
          // a valid time must be in the range 0-23).
          //
          v.setHMS (24, 0, 0);
        else
          v = QTime::fromString (
            QString::fromAscii (i.data (), static_cast<int> (n)),
            "HH:mm:ss.zzz");
      }

      static void
      set_image (details::buffer& i,
                 std::size_t& n,
                 bool& is_null,
                 const QTime& v)
      {
        if (v.isNull ())
          is_null = true;
        else
        {
          is_null = false;

          std::string s (v.toString ("HH:mm:ss.zzz").toStdString ());

          n = s.size ();
          if (n > i.capacity ())
            i.capacity (n);

          std::memcpy (i.data (), s.data (), n);
        }
      }
    };

    // Implementation of mapping between QTime and SQLite INTEGER. The
    // integer value represents seconds since midnight.
    //
    template <>
    class default_value_traits<QTime, long long, id_integer>
    {
    public:
      typedef QTime value_type;
      typedef QTime query_type;
      typedef long long image_type;

      static void
      set_value (QTime& v, long long i, bool is_null)
      {
        if (is_null)
          // A null QTime value is equivalent to an invalid QTime value.
          // Set v to an invalid time to represent null (hour value of
          // a valid time must be in the range 0-23).
          //
          v.setHMS (24, 0, 0);
        else
          v = QTime (0, 0, 0).addSecs (static_cast<int> (i));
      }

      static void
      set_image (long long& i, bool& is_null, const QTime& v)
      {
        if (v.isNull ())
          is_null = true;
        else
        {
          is_null = false;
          i = static_cast<long long> (QTime (0, 0, 0).secsTo (v));
        }
      }
    };

    template <>
    class default_type_traits<QTime>
    {
      static const database_type_id db_type_id = id_text;
    };
  }
}

#endif // ODB_QT_DATE_TIME_SQLITE_QTIME_TRAITS_HXX