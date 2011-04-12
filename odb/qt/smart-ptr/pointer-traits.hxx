// file      : odb/qt/smart-ptr/pointer-traits.hxx
// author    : Constantin Michael <constantin@codesynthesis.com>
// copyright : Copyright (c) 2009-2011 Code Synthesis Tools CC
// license   : GNU GPL v2; see accompanying LICENSE file

#ifndef ODB_QT_SMART_PTR_POINTER_TRAITS_HXX
#define ODB_QT_SMART_PTR_POINTER_TRAITS_HXX

#include <odb/pre.hxx>

#include <QSharedPointer>
#include <QWeakPointer>

#include <odb/pointer-traits.hxx>

namespace odb
{
  // Specialization for QSharedPointer.
  //
  template <typename T>
  class pointer_traits<QSharedPointer<T> >
  {
  public:
    static const pointer_kind kind = pk_shared;
    static const bool lazy = false;

    typedef T element_type;
    typedef QSharedPointer<element_type> pointer_type;
    typedef QSharedPointer<const element_type> const_pointer_type;
    typedef smart_ptr_guard<pointer_type> guard;

    static element_type*
    get_ptr (const pointer_type& p)
    {
      return p.data ();
    }

    static element_type&
    get_ref (const pointer_type& p)
    {
      return *p;
    }

    static bool
    null_ptr (const pointer_type& p)
    {
      return !p;
    }

  public:
    static void*
    allocate (std::size_t n)
    {
      return operator new (n);
    }

    static void
    free (void* p)
    {
      operator delete (p);
    }
  };

  // Specialization for QWeakPointer.
  //
  template <typename T>
  class pointer_traits<QWeakPointer<T> >
  {
  public:
    static const pointer_kind kind = pk_weak;
    static const bool lazy = false;

    typedef T element_type;
    typedef QWeakPointer<element_type> pointer_type;
    typedef QSharedPointer<element_type> strong_pointer_type;

    static strong_pointer_type
    lock (const pointer_type& p)
    {
      return p.toStrongRef ();
    }
  };
}

#include <odb/post.hxx>

#endif // ODB_QT_SMART_PTR_POINTER_TRAITS_HXX