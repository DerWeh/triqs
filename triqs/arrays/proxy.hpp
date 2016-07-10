//****************************************
// GENERATED BY MAKO : DO NOT EDIT
//****************************************
/*******************************************************************************
 *
 * TRIQS: a Toolbox for Research in Interacting Quantum Systems
 *
 * Copyright (C) 2013-2016 by O. Parcollet
 *
 * TRIQS is free software: you can redistribute it and/or modify it under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 * TRIQS is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
 * details.
 *
 * You should have received a copy of the GNU General Public License along with
 * TRIQS. If not, see <http://www.gnu.org/licenses/>.
 *
 ******************************************************************************/
#pragma
#include <triqs/arrays.hpp>

namespace triqs {
namespace arrays {

 template <class T> struct _rm_rvalue_impl { using type = T; };
 template <class T> struct _rm_rvalue_impl<T &&> { using type = T; };
 template <class T> using _rm_rvalue = typename _rm_rvalue_impl<T>::type;


 template <typename A> struct array_const_proxy : TRIQS_CONCEPT_TAG_NAME(ImmutableArray) {

  using A_t = std14::remove_reference_t<A>;
  static constexpr int rank = A_t::rank;

  A a;
  long n;

  using value_type = typename A_t::value_type;
  using traversal_order_t = typename A_t::traversal_order_t;
  using slicer_t = indexmaps::slicer<typename A_t::indexmap_type, long, ellipsis>;
  using indexmap_type = typename slicer_t::r_type;
  using domain_type = typename indexmap_type::domain_type;

  using view_type = array_const_view<value_type, domain_type::rank>;
  using const_view_type = array_const_view<value_type, domain_type::rank>;

  using call_rt = value_type const &;
  static constexpr bool is_const = true;

  template <typename AA> array_const_proxy(AA &&a_, long n_) : a(std::forward<AA>(a_)), n(n_) {}

  indexmap_type indexmap() const { return slicer_t::invoke(a.indexmap(), n, ellipsis()); }
  domain_type domain() const { return indexmap().domain(); }

  auto storage() const { return a.storage(); }
  value_type const *restrict data_start() const { return &storage()[indexmap().start_shift()]; }
  value_type *restrict data_start() { return &storage()[indexmap().start_shift()]; }

  view_type operator()() const { return *this; }

  friend auto get_shape(array_const_proxy const &x) { return get_shape(x.a).front_pop(); } // FIXME  nvar

  template <typename... Args>
  std::c14::enable_if_t<!triqs::clef::is_any_lazy<Args...>::value, call_rt> operator()(Args &&... args) const {
   return a(n, std::forward<Args>(args)...);
  }
  TRIQS_CLEF_IMPLEMENT_LAZY_CALL();


  template <typename RHS> array_const_proxy &operator=(const RHS &X) = delete; // cannot assign to a const
  TRIQS_DELETE_COMPOUND_OPERATORS(array_const_proxy);


  friend std::ostream &operator<<(std::ostream &out, array_const_proxy const &x) { return out << view_type(x); }
 };


 template <typename A> struct array_proxy : TRIQS_CONCEPT_TAG_NAME(MutableArray) {

  using A_t = std14::remove_reference_t<A>;
  static constexpr int rank = A_t::rank;

  A a;
  long n;

  using value_type = typename A_t::value_type;
  using traversal_order_t = typename A_t::traversal_order_t;
  using slicer_t = indexmaps::slicer<typename A_t::indexmap_type, long, ellipsis>;
  using indexmap_type = typename slicer_t::r_type;
  using domain_type = typename indexmap_type::domain_type;

  using view_type = array_view<value_type, domain_type::rank>;
  using const_view_type = array_const_view<value_type, domain_type::rank>;

  using call_rt = value_type &;
  static constexpr bool is_const = false;

  template <typename AA> array_proxy(AA &&a_, long n_) : a(std::forward<AA>(a_)), n(n_) {}

  indexmap_type indexmap() const { return slicer_t::invoke(a.indexmap(), n, ellipsis()); }
  domain_type domain() const { return indexmap().domain(); }

  auto storage() const { return a.storage(); }
  value_type const *restrict data_start() const { return &storage()[indexmap().start_shift()]; }
  value_type *restrict data_start() { return &storage()[indexmap().start_shift()]; }

  view_type operator()() const { return *this; }

  friend auto get_shape(array_proxy const &x) { return get_shape(x.a).front_pop(); } // FIXME  nvar

  template <typename... Args>
  std::c14::enable_if_t<!triqs::clef::is_any_lazy<Args...>::value, call_rt> operator()(Args &&... args) const {
   return a(n, std::forward<Args>(args)...);
  }
  TRIQS_CLEF_IMPLEMENT_LAZY_CALL();


  template <typename RHS> array_proxy &operator=(const RHS &X) {
   triqs_arrays_assign_delegation(*this, X);
   return *this;
  }
  // same for the same class (not captured by the template).
  array_proxy &operator=(array_proxy const &X) {
   triqs_arrays_assign_delegation(*this, X);
   return *this;
  }

  TRIQS_DEFINE_COMPOUND_OPERATORS(array_proxy);

  // auto_assign like the main classes
  template <typename F> friend void triqs_clef_auto_assign(array_proxy x, F &&f) {
   foreach (x, array_auto_assign_worker<array_proxy, F>{x, f})
    ;
  }


  friend std::ostream &operator<<(std::ostream &out, array_proxy const &x) { return out << view_type(x); }
 };


 // if A is a const_view or A is passed by const &, then the proxy is const, otherwise it is not.
 template <typename A>
 std14::conditional_t<std14::decay_t<A>::is_const || std::is_const<std14::remove_reference_t<A>>::value,
                      array_const_proxy<_rm_rvalue<A>>, array_proxy<_rm_rvalue<A>>>
 make_array_proxy(A &&a, long n) {
  return {std::forward<A>(a), n};
 }
 /*

  // factory
  template <typename A> array_const_proxy<_rm_rvalue<A>> make_const_tensor_proxy(A &&a, long n) {
   return {std::forward<A>(a), n};
  }
  template <typename A> array_proxy<_rm_rvalue<A>> make_tensor_proxy(A &&a, long n) { return {std::forward<A>(a), n}; }


  template <typename A> const_matrix_tensor_proxy<_rm_rvalue<A>> make_const_matrix_proxy(A &&a, long n) {
   return {std::forward<A>(a), n};
  }


  // factory
  template <typename A> matrix_tensor_proxy<_rm_rvalue<A>> make_matrix_proxy(A &&a, long n) { return {std::forward<A>(a), n}; }
 */


 template <typename A> struct matrix_const_proxy : TRIQS_CONCEPT_TAG_NAME(ImmutableMatrix) {

  using A_t = std14::remove_reference_t<A>;
  static constexpr int rank = A_t::rank;

  A a;
  long n;

  using value_type = typename A_t::value_type;
  using traversal_order_t = typename A_t::traversal_order_t;
  using slicer_t = indexmaps::slicer<typename A_t::indexmap_type, long, ellipsis>;
  using indexmap_type = typename slicer_t::r_type;
  using domain_type = typename indexmap_type::domain_type;

  using view_type = matrix_const_view<value_type>;
  using const_view_type = matrix_const_view<value_type>;

  using call_rt = value_type const &;
  static constexpr bool is_const = true;

  template <typename AA> matrix_const_proxy(AA &&a_, long n_) : a(std::forward<AA>(a_)), n(n_) {}

  indexmap_type indexmap() const { return slicer_t::invoke(a.indexmap(), n, ellipsis()); }
  domain_type domain() const { return indexmap().domain(); }

  auto storage() const { return a.storage(); }
  value_type const *restrict data_start() const { return &storage()[indexmap().start_shift()]; }
  value_type *restrict data_start() { return &storage()[indexmap().start_shift()]; }

  view_type operator()() const { return *this; }

  friend auto get_shape(matrix_const_proxy const &x) { return get_shape(x.a).front_pop(); } // FIXME  nvar

  template <typename... Args>
  std::c14::enable_if_t<!triqs::clef::is_any_lazy<Args...>::value, call_rt> operator()(Args &&... args) const {
   return a(n, std::forward<Args>(args)...);
  }
  TRIQS_CLEF_IMPLEMENT_LAZY_CALL();


  template <typename RHS> matrix_const_proxy &operator=(const RHS &X) = delete; // cannot assign to a const
  TRIQS_DELETE_COMPOUND_OPERATORS(matrix_const_proxy);


  friend std::ostream &operator<<(std::ostream &out, matrix_const_proxy const &x) { return out << view_type(x); }
 };


 template <typename A> struct matrix_proxy : TRIQS_CONCEPT_TAG_NAME(MutableMatrix) {

  using A_t = std14::remove_reference_t<A>;
  static constexpr int rank = A_t::rank;

  A a;
  long n;

  using value_type = typename A_t::value_type;
  using traversal_order_t = typename A_t::traversal_order_t;
  using slicer_t = indexmaps::slicer<typename A_t::indexmap_type, long, ellipsis>;
  using indexmap_type = typename slicer_t::r_type;
  using domain_type = typename indexmap_type::domain_type;

  using view_type = matrix_view<value_type>;
  using const_view_type = matrix_const_view<value_type>;

  using call_rt = value_type &;
  static constexpr bool is_const = false;

  template <typename AA> matrix_proxy(AA &&a_, long n_) : a(std::forward<AA>(a_)), n(n_) {}

  indexmap_type indexmap() const { return slicer_t::invoke(a.indexmap(), n, ellipsis()); }
  domain_type domain() const { return indexmap().domain(); }

  auto storage() const { return a.storage(); }
  value_type const *restrict data_start() const { return &storage()[indexmap().start_shift()]; }
  value_type *restrict data_start() { return &storage()[indexmap().start_shift()]; }

  view_type operator()() const { return *this; }

  friend auto get_shape(matrix_proxy const &x) { return get_shape(x.a).front_pop(); } // FIXME  nvar

  template <typename... Args>
  std::c14::enable_if_t<!triqs::clef::is_any_lazy<Args...>::value, call_rt> operator()(Args &&... args) const {
   return a(n, std::forward<Args>(args)...);
  }
  TRIQS_CLEF_IMPLEMENT_LAZY_CALL();


  template <typename RHS> matrix_proxy &operator=(const RHS &X) {
   triqs_arrays_assign_delegation(*this, X);
   return *this;
  }
  // same for the same class (not captured by the template).
  matrix_proxy &operator=(matrix_proxy const &X) {
   triqs_arrays_assign_delegation(*this, X);
   return *this;
  }

  TRIQS_DEFINE_COMPOUND_OPERATORS(matrix_proxy);

  // auto_assign like the main classes
  template <typename F> friend void triqs_clef_auto_assign(matrix_proxy x, F &&f) {
   foreach (x, array_auto_assign_worker<matrix_proxy, F>{x, f})
    ;
  }


  friend std::ostream &operator<<(std::ostream &out, matrix_proxy const &x) { return out << view_type(x); }
 };


 // if A is a const_view or A is passed by const &, then the proxy is const, otherwise it is not.
 template <typename A>
 std14::conditional_t<std14::decay_t<A>::is_const || std::is_const<std14::remove_reference_t<A>>::value,
                      matrix_const_proxy<_rm_rvalue<A>>, matrix_proxy<_rm_rvalue<A>>>
 make_matrix_proxy(A &&a, long n) {
  return {std::forward<A>(a), n};
 }
 /*

  // factory
  template <typename A> matrix_const_proxy<_rm_rvalue<A>> make_const_tensor_proxy(A &&a, long n) {
   return {std::forward<A>(a), n};
  }
  template <typename A> matrix_proxy<_rm_rvalue<A>> make_tensor_proxy(A &&a, long n) { return {std::forward<A>(a), n}; }


  template <typename A> const_matrix_tensor_proxy<_rm_rvalue<A>> make_const_matrix_proxy(A &&a, long n) {
   return {std::forward<A>(a), n};
  }


  // factory
  template <typename A> matrix_tensor_proxy<_rm_rvalue<A>> make_matrix_proxy(A &&a, long n) { return {std::forward<A>(a), n}; }
 */
}
}