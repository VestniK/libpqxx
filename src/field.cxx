/** Implementation of the pqxx::field class.
 *
 * pqxx::field refers to a field in a query result.
 *
 * Copyright (c) 2001-2017, Jeroen T. Vermeulen <jtv@xs4all.nl>
 *
 * See COPYING for copyright license.  If you did not receive a file called
 * COPYING with this source code, please notify the distributor of this mistake,
 * or contact the author.
 */
#include "pqxx/compiler-internal.hxx"

#include "pqxx/internal/libpq-forward.hxx"

#include "pqxx/field"
#include "pqxx/result"
#include "pqxx/row"


pqxx::field::field(const pqxx::row &R, pqxx::row::size_type C) noexcept :
  m_col(C),
  m_home(&R.m_result),
  m_row(R.m_Index)
{
}


bool pqxx::field::operator==(const field &rhs) const
{
  if (is_null() != rhs.is_null()) return false;
  // TODO: Verify null handling decision
  const size_type s = size();
  if (s != rhs.size()) return false;
  const char *const l(c_str()), *const r(rhs.c_str());
  for (size_type i = 0; i < s; ++i) if (l[i] != r[i]) return false;
  return true;
}


const char *pqxx::field::name() const
{
  return home()->column_name(col());
}


pqxx::oid pqxx::field::type() const
{
  return home()->column_type(col());
}


pqxx::oid pqxx::field::table() const
{
  return home()->column_table(col());
}


pqxx::row::size_type pqxx::field::table_column() const
{
  return home()->table_column(col());
}


const char *pqxx::field::c_str() const
{
  return home()->GetValue(idx(), col());
}


bool pqxx::field::is_null() const noexcept
{
  return home()->GetIsNull(idx(), col());
}


pqxx::field::size_type pqxx::field::size() const noexcept
{
  return home()->GetLength(idx(), col());
}
