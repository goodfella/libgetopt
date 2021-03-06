#ifndef __IPARAMETER_H__
#define __IPARAMETER_H__

namespace libgetopt
{
    class iparameter
    {
	public:

	    virtual ~iparameter();

	    virtual const bool present() const = 0;
	    virtual void clear_present() = 0;
    };
}

#endif
