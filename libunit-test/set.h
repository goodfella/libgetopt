#ifndef __SET_H__
#define __SET_H__

#include <vector>
#include <iterator>
#include <cstring>
#include <algorithm>

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
			typedef typename set_t::const_reference const_reference;
			typedef typename set_t::reference reference;

			typedef typename powerset_t::iterator powerset_iterator;
			typedef typename powerset_t::const_iterator const_powerset_iterator;

			set();
			set(const T& val);

			void add_element(const T& e);
			iterator insert(iterator position, const T& val);

			size_t size() const;

			T& operator [] (typename set_t::size_type i);
			const T& operator [] (typename set_t::size_type i) const;

			iterator begin();
			const_iterator begin() const;

			iterator end();
			const_iterator end() const;

			static const powerset_t powerset(const set<T>& source_set);

		    template <class F>
		    void foreach_elem(F op);

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
		typename set<T>::iterator set<T>::insert(iterator position, const T& val)
		{
			return m_set.insert(position, val);
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
		inline typename set<T>::const_iterator set<T>::begin() const
		{
			return m_set.begin();
		}

		template<class T>
		inline typename set<T>::iterator set<T>::end()
		{
			return m_set.end();
		}

		template<class T>
		inline typename set<T>::const_iterator set<T>::end() const
		{
			return m_set.end();
		}

		// copied from roseta code powerset

		/* This algorithm is not recursive, it works backwards
		 * from the empty set.  The algorithm works by
		 * tracking elements to put in a set through a vector
		 * of iterators.  The first set added is the empty
		 * set, the next set added is the full set with all
		 * the elements.  Then the algorithm works backward
		 * from there.
		 */

		/* Three operations are used to manipulate the element
		 * vector:  
		 *
		 * If the element vector is not empty, and the last
		 * iterator in the element vector points to the last
		 * element in the set, then the last iterator in the
		 * element vector is removed, and the algorithm moves
		 * to starts the loop over.
		 *
		 * if the element vector is not empty, and the last
		 * iterator in the element vector does not point to
		 * the last element in the set, the last iterator in
		 * the element vector is set to the next element in
		 * the set (see ++elements.back()).  Then, iterators
		 * pointing to the remaining elements in the set
		 * (elements.back() + 1 through source_set.end()) are
		 * added to the element vector.
		 *
		 * if the element vector is empty, then add all the
		 * elements from source_set to the element vector.
		 */
		template<class T>
		const typename set<T>::powerset_t set<T>::powerset(const set<T>& source_set)
		{
			typedef typename set<T>::const_iterator set_iter;
			typedef std::vector<set_iter> vec;
			typedef typename vec::iterator vec_iter;
 
			struct local
			{
				static const T& dereference(set_iter v) { return *v; }
			};
 
			typename set<T>::powerset_t result;
 
			vec elements;
			do
			{
				set<T> subset;
				std::transform(elements.begin(), elements.end(),
					       std::inserter(subset, subset.end()),
					       local::dereference);

				result.insert(result.end(), subset);

				/* Be mindfull of the
				 * ++elements.back() which moves the
				 * iterator at elements.back() to the
				 * next element in the set */
				if (!elements.empty() && ++elements.back() == source_set.end())
				{
					elements.pop_back();
				}
				else
				{
					set_iter iter;

					// if elements is empty, add all the elements
					if (elements.empty())
					{
						iter = source_set.begin();
					}
					// add all elements after the element referenced by elements.back()
					else
					{
						iter = elements.back();
						++iter;
					}
					for (; iter != source_set.end(); ++iter)
					{
						elements.push_back(iter);
					}
				}
			} while (!elements.empty());
 
			return result;
		}

	    template<class T>
	    template<class F>
	    void set<T>::foreach_elem(F op)
	    {
		std::for_each(m_set.begin(), m_set.end(), op);
	    }
	}
}

#endif
