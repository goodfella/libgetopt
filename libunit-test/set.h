#ifndef __SET_H__
#define __SET_H__

#include <vector>
#include <iterator>
#include <cstring>

namespace libgetopt
{
	namespace unit_tests
	{

		unsigned int factorial(unsigned int);

		template<class T>
		class set
		{
		    public:

			typedef std::vector<T> set_t;
			typedef std::vector<set<T> > powerset_t;
			typedef typename std::vector<T>::size_type size_type;

			typedef typename set_t::iterator iterator;
			typedef typename set_t::const_iterator const_iterator;

			typedef typename powerset_t::iterator powerset_iterator;
			typedef typename powerset_t::const_iterator const_powerset_iterator;

			set();
			set(const T& val);

			void add_element(const T& e);
			size_t size() const;

			T& operator [] (typename set_t::size_type i);
			const T& operator [] (typename set_t::size_type i) const;

			typename set_t::iterator begin();
			const typename set_t::iterator begin() const;

			typename set_t::iterator end();
			const typename set_t::iterator end() const;

			static const powerset_t powerset(const set<T>& source_set);

		    private:

			set_t m_set;
		};

		template<class T>
		set<T>::set() {}

		template<class T>
		set<T>::set(const T& val):
			m_set(1, val)
		{}

		template<class T>
		inline void set<T>::add_element(const T& e)
		{
			m_set.push_back(e);
		}

		template<class T>
		inline size_t set<T>::size() const
		{
			return m_set.size();
		}

		template<class T>
		inline T& set<T>::operator[] (typename set_t::size_type i)
		{
			return m_set[i];
		}

		template<class T>
		inline const T& set<T>::operator[] (typename set_t::size_type i) const
		{
			return m_set[i];
		}

		template<class T>
		inline typename set<T>::iterator set<T>::begin()
		{
			return m_set.begin();
		}

		template<class T>
		inline const typename set<T>::iterator set<T>::begin() const
		{
			return m_set.begin();
		}

		template<class T>
		inline typename set<T>::iterator set<T>::end()
		{
			return m_set.end();
		}

		template<class T>
		inline const typename set<T>::iterator set<T>::end() const
		{
			return m_set.end();
		}

		template<class T>
		const typename set<T>::powerset_t set<T>::powerset(const set<T>& source_set)
		{
			powerset_t power_set;
			size_t source_set_size = source_set.size();

			for(int subset_size = 1; subset_size <= source_set_size; ++subset_size)
			{
				// set of each element
				if( subset_size == 1 )
				{
					for(int j = 0; j < source_set_size; ++j)
					{
						power_set.push_back(set<T>(source_set[j]));
					}
				}
				else if( subset_size == source_set_size )
				{
					power_set.push_back(source_set);
				}
				else
				{
					for(int first_elem = 0;
					    first_elem + subset_size <= source_set_size;
					    ++first_elem)
					{
						for(int next_elem = first_elem + 1;
						    next_elem + (subset_size - 1) <= source_set_size;
						    ++next_elem)
						{
							set<T> subset(source_set[first_elem]);
							subset.add_element(source_set[next_elem]);

							for(int elem_count = 2;
							    elem_count < subset_size;
							    ++elem_count)
							{
								subset.add_element(source_set[next_elem + (elem_count - 1)]);
							}

							power_set.push_back(subset);
						}
					}
				}
			}

			return power_set;
		}
	}
}

#endif
