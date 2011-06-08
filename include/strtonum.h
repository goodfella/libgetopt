#ifndef __STRTONUM_H__
#define __STRTONUM_H__

#include <cstdio>
#include <string>

namespace libgetopt
{
    bool strtonum_result(std::string* err_str,
			 char const * const bad_chars,
			 int errno_val,
			 bool overflow,
			 bool underflow);

    template<class Type>
    struct strtonum_is_float
    {
	    static bool const value = false;
    };

    template<>
    struct strtonum_is_float<float>
    {
	    static bool const value = true;
    };

    template<class Type>
    struct strtonum_is_double
    {
	    static bool const value = false;
    };

    template<>
    struct strtonum_is_double<double>
    {
	    static bool const value = true;
    };

    template<class Return_Type, Return_Type Converter(const char*, char**, int)>
    struct integral_traits
    {
	    typedef Return_Type numeric_t;

	    static numeric_t converter(const char* num, char** end, int base)
	    {
		return Converter(num, end, base);
	    }
    };

    template<class Return_Type, Return_Type Converter(const char*, char**)>
    struct decimal_traits
    {
	    typedef Return_Type numeric_t;
	    static numeric_t converter(const char* num, char** end)
	    {
		return Converter(num, end);
	    }
    };

    template<bool Signed, bool Is_Float, bool Is_Double>
    struct strtonum_traits;

    // signed integral types
    template<>
    struct strtonum_traits<true, false, false>: public integral_traits<long long int, &strtoll>
    {};

    // unsigned integral types
    template<>
    struct strtonum_traits<false, false, false>: public integral_traits<unsigned long long int, &strtoull>
    {};

    template<>
    struct strtonum_traits<true, false, true>: public decimal_traits<long double, &strtold>
    {};

    template<bool Integral, class Traits>
    struct strtonum
    {
	    static bool convert(char const * const num_str, std::string* err_str,
				const typename Traits::numeric_t max,
				const typename Traits::numeric_t min,
				typename Traits::numeric_t *val);
    };


    template<class Traits>
    struct strtonum<true, Traits>
    {
	    static bool convert(char const * const num_str,
				std::string* err_str,
				const typename Traits::numeric_t max,
				const typename Traits::numeric_t min,
				typename Traits::numeric_t *val)
	    {
		assert( val != NULL );

		char* bad_chrs = NULL;

		errno = 0;

		*val = Traits::converter(num_str, &bad_chrs, 10);

		return strtonum_result(err_str, bad_chrs, errno,
				       ( (errno == ERANGE && *val >= max) || (*val > max)),
				       ( (errno == ERANGE && *val <= min) || (*val < min)));
	    }
    };

    template<class Traits>
    struct strtonum<false, Traits>
    {
	    static bool convert(char const * const num_str,
				std::string* err_str,
				const typename Traits::numeric_t max,
				const typename Traits::numeric_t min,
				typename Traits::numeric_t *val)
	    {
		assert( val != NULL );

		char* bad_chrs = NULL;

		errno = 0;

		*val = Traits::converter(num_str, &bad_chrs);

		printf("double val = %Lf\n", *val);

		return strtonum_result(err_str, bad_chrs, errno,
				       ((errno == ERANGE && *val >= max) || (*val > max)),
				       ((errno == ERANGE && *val <= min) || (*val < min)));
	    }
    };
}

#endif
