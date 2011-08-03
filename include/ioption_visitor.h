#ifndef __IOPTION_VISITOR_H__
#define __IOPTION_VISITOR_H__

namespace libgetopt
{
    template<class T>
    class option;

    template<class T>
    class ioption_visitor
    {
	public:

	    virtual ~ioption_visitor() {}

	    virtual void visit(option<T>& opt, const std::string& arg) = 0;
    };
};

#endif
