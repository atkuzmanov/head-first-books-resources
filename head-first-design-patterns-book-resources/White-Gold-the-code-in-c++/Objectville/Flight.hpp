#ifndef	_hfdp_cpp_objectville_flight_hpp_
#define _hfdp_cpp_objectville_flight_hpp_

#include "../Objectville/Hfdp.h"

namespace Hfdp 
{
	/**
	 *	Defines an interface contract that exposes a method or methods that
	 *	implement 'flight' behavior.
	 *
	 *	Idiom:	An interface describes behavior of a class without committing to
	 *			a particular implementation. It is a contract between a provider
	 *			and its users, defining what's required from each implementer. 
	 *
	 *	C++:	This is accomplished by defining an abstract 'struct' that 
	 *			contains 'only' pure virtual public methods; 'struct' is used
	 *			because its members are 'public' by default.
	 *
	 *	C++:	Interfaces should 'only' derive from other interfaces, and contain
	 *			no data members.
	 */
		Hfdp_DECL struct Flight
		{
			/**
			 *	Idiom: 'Declare destructor virtual if and only if that class or struct
			 *			contains at least one virtual method.
			 */	
				virtual ~Flight()
				{
				}
			/**
			 *	Defines a contract that exposes behavioral execution
			 */
				virtual std::string execute() const = 0;
		};

}

#endif
