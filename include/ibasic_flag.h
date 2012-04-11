#ifndef __BASIC_FLAG__
#define __BASIC_FLAG__

namespace libgetopt
{
    class ibasic_flag
    {
	public:

	virtual ~ibasic_flag();

	/** Sets whether the flag parameter is present
	 *
	 * @param present A true value means the flag is present, a
	 * false value means the parameter is not present.
	*/
	virtual void present(const bool present) = 0;
    };
}

#endif
