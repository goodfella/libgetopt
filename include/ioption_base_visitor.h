#ifndef __IOPTION_BASE_VISITOR_H__
#define __IOPTION_BASE_VISITOR_H__

namespace libgetopt
{
    class option_base;

    class ioption_base_visitor
    {
	public:

	    virtual ~ioption_base_visitor() {}

	    virtual void visit(option_base& opt, const std::string& arg) = 0;
    };
}

#endif
