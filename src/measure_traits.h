#ifndef NEUROSTR_MEASURES_MEASURE_TRAITS_H_
#define NEUROSTR_MEASURES_MEASURE_TRAITS_H_

#include <neurostr/core/traits.h>

namespace neurostr {
namespace measure {
namespace detail{
  
/**
* @struct type_chooser
* @brief Extracts the measure type. The first template parameter is a set indicator. If true, T is assumed to be an iterator
*/
template <bool, typename T>
  struct type_chooser {
    using type = T; // False, is a reference
  };

  template <typename T>
  struct type_chooser<true,T> {
    using type = typename T::value_type::type; // True: Is an iterator to a wrapped reference
  };    

} // Namepsace detail


/**
 * @struct measure_func_traits
 * @file measure_traits.h
 * @brief Measure function traits. Extracts input type, input arity and output type.
 */
template <typename F> struct measure_func_traits {  
  using base_traits = neurostr::traits::function_traits<F>;

  constexpr static bool in_set = (base_traits::arity > 1);
  using out_type = typename base_traits::result_type;
  
  using base_in_type = typename std::remove_reference_t<
                          typename base_traits::template arg<0>>;
  using in_type = typename detail::type_chooser<in_set, base_in_type>::type;
};

namespace detail{
  
   template <typename Fn,
            std::enable_if_t<!measure_func_traits<Fn>::in_set>* = nullptr >
  using measure_fn_reference = std::reference_wrapper<
                                    const typename measure_func_traits<Fn>::in_type>;
                                    
} // Namespace detail

} // Measure
} // Neurostr


#endif
