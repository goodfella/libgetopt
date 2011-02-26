#ifndef __IPARAMETER_H__
#define __IPARAMETER_H__

namespace libgetopt
{
    class iparameter
    {
	public:

	    virtual ~iparameter();

	    virtual const bool is_present() const = 0;
    };
}

#endif
