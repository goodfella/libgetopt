#ifndef __INVALID_NUMERIC_TEST_H__
#define __INVALID_NUMERIC_TEST_H__

namespace libgetopt
{
    namespace unit_tests
    {
	template<class T>
	class invalid_numeric_test
	{
	    public:

		invalid_numeric_test(char* arg0);
		~invalid_numeric_test();

		template<class Arg>
		bool run(Arg arg);

	    private:

		cmdline_args m_args;
		option_base* m_opt;
		cmdline_parser m_parser;
	};

	template<class T>
	invalid_numeric_test<T>::invalid_numeric_test(char* arg0):
	    m_args(arg0),
	    m_opt(NULL)
	{
	    option<T> *opt = new option<T>("opt",'o');
	    m_opt = opt;

	    m_args.add(m_opt);
	    m_parser.add_option(opt);
	}

	template<class T>
	invalid_numeric_test<T>::~invalid_numeric_test()
	{
	    delete m_opt;
	}

	template<class T>
	template<class Arg>
	bool invalid_numeric_test<T>::run(Arg arg)
	{
	    m_args.add(arg);

	    unit_test tester("invalid numeric test",
			     m_args.count(),
			     m_args,
			     m_parser,
			     cmdline_parser::parse_result::result_invalid_arg);

	    return tester.run();
	}
    }
}

#endif
