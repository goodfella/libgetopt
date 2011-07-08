#ifndef __LIBGETOPT_STRING_H__
#define __LIBGETOPT_STRING_H__

#include <cstddef>
#include <cstring>

namespace libgetopt
{
    /** Creates a new C string of size length
     *
     *  @param length should not include the null character
     */
    char* new_cstring(size_t length);

    /// Duplicates the cstring parameter
    char* duplicate_cstring(char const * const cstring);

    /// Frees the cstring created by new_cstring or duplicate_cstring
    char* delete_cstring(char const * cstring);

    /// Works likes auto_ptr but explicitly for cstrings
    class auto_cstring_ptr
    {
	public:
	    auto_cstring_ptr(char* cstring);
	    auto_cstring_ptr(auto_cstring_ptr& ptr);
	    auto_cstring_ptr& operator= (auto_cstring_ptr& ptr);

	    ~auto_cstring_ptr();

	    /// Releases the pointer preventing its memory from being deallocated
	    void release();

	    /// Releases the memory pointed to by the internal pointer
	    void reset();

	    /// Returns the internal cstring
	    char* get() const;

	private:

	    void take_ownership(auto_cstring_ptr& ptr);

	    char* m_cstring;
    };

    inline char* new_cstring(size_t length)
    {
	return new char[length + 1];
    }

    inline char* duplicate_cstring(char const * const cstring)
    {
	char* dup_cstring = new_cstring(strlen(cstring));
	strcpy(dup_cstring, cstring);
	return dup_cstring;
    }

    inline char* delete_cstring(char const * cstring)
    {
	delete[] cstring;
	return NULL;
    }

    inline auto_cstring_ptr::auto_cstring_ptr(char* cstring):
	m_cstring(cstring)
    {}

    inline auto_cstring_ptr::auto_cstring_ptr(auto_cstring_ptr& ptr)
    {
	*this = ptr;
    }

    inline void auto_cstring_ptr::take_ownership(auto_cstring_ptr& ptr)
    {
	m_cstring = ptr.m_cstring;
	ptr.release();
    }

    inline auto_cstring_ptr& auto_cstring_ptr::operator= (auto_cstring_ptr& ptr)
    {
	if( this != &ptr )
	{
	    take_ownership(ptr);
	}

	return *this;
    }

    inline auto_cstring_ptr::~auto_cstring_ptr()
    {
	reset();
    }

    inline void auto_cstring_ptr::release()
    {
	m_cstring = 0;
    }

    inline void auto_cstring_ptr::reset()
    {
	m_cstring = delete_cstring(m_cstring);
    }

    inline char* auto_cstring_ptr::get() const
    {
	return m_cstring;
    }
}

#endif
