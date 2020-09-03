#ifndef	_hfdp_cpp_objectville_singleton_hpp_
#define _hfdp_cpp_objectville_singleton_hpp_

#include "../Objectville/Hfdp.h"

namespace Hfdp {
	/**
	 *	This is a simplistic yet insidious implementation of the 'singleton' pattern;
	 *	it ignores lifetime management and it is not thread-safe. To do so, would
	 *	pollute the code unnecessarily and obscure the intent of depicting the pattern. 
	 */
		template<class T> 
		class Singleton
		{
			/**
			 *	A 'static' object is created if and when encountered thereby adhering
			 *	to C++ philosophy of not paying for what you don't use.
			 */
				public: static T&
				instance()
				{
					static T instance;
					return instance;
				}
			/**
			 *	default ctor, declared protected to disable direct instantiation
			 */
				protected: Singleton() 
				{
				}
			/**
			 *	dtor, although this is a polymorphic base class, a protected dtor 
			 *	prohibits explicit deletion thereby rendering 'virtual' keyword
			 *	unnecessary. Omitting this keyword implies that deletion of a class
			 *	via its base pointer is not supported
			 */
				protected: ~Singleton() 
				{
				}
			/**
			 *	copy ctor, declared to inhibit implicit compiler generation, undefined
			 *	to prohibit copying 
			 */
				private: Singleton(const Singleton&);
			/**
			 *	assignment operator, declared to inhibit implicit compiler generation,
			 *	undefined to prohibit assignment
			 */
				private: Singleton& operator=(const Singleton&);
		};
}

#endif	
