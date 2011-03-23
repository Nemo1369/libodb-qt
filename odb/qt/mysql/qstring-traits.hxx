// file      : odb/qt/mysql/qstring-traits.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_QT_MYSQL_QSTRING_TRAITS_HXX
#define ODB_QT_MYSQL_QSTRING_TRAITS_HXX

#include <odb/pre.hxx>

#include <cstddef> // std::size_t

#include <odb/mysql/traits.hxx>
#include <odb/details/buffer.hxx>

#include <QString>

namespace odb
{
  namespace mysql
  {
    class LIBODB_MYSQL_EXPORT qstring_value_traits
    {
    public:
      typedef QString value_type;
      typedef QString query_type;
      typedef details::buffer image_type;

      static void
      set_value (QString& v,
                 const details::buffer& b,
                 std::size_t n,
                 bool is_null)
      {
        if (!is_null)
          v = QString::fromLocal8Bit (b.data (), n);
        else
          v.clear ();
      }

      static void
      set_image (details::buffer& b,
                 std::size_t& n,
                 bool& is_null,
                 const QString& v)
      {
        is_null = false;

        const std::string& s (v.toStdString ());
        n = s.size ();

        if (n > b.capacity ())
          b.capacity (n);

        if (n != 0)
          memcpy (b.data (), s.data (), n);
      }
    };

    template <>
    struct LIBODB_MYSQL_EXPORT default_value_traits<
      QString, details::buffer, id_string>: qstring_value_traits
    {
    };

    template <>
    struct LIBODB_MYSQL_EXPORT default_value_traits<
      QString, details::buffer, id_decimal>: qstring_value_traits
    {
    };

    template <>
    struct LIBODB_MYSQL_EXPORT default_value_traits<
      QString, details::buffer, id_enum>: qstring_value_traits
    {
    };

    template <>
    struct LIBODB_MYSQL_EXPORT default_value_traits<
      QString, details::buffer, id_set>: qstring_value_traits
    {
    };

    template <>
    struct default_type_traits<QString>
    {
      static const database_type_id db_type_id = id_string;
    };
  }
}

#include <odb/post.hxx>

#endif // ODB_QT_MYSQL_QSTRING_TRAITS_HXX