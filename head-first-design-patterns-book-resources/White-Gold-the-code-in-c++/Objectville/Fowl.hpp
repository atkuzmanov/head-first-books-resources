#ifndef	_hfdp_cpp_objectville_fowl_hpp_
#define _hfdp_cpp_objectville_fowl_hpp_

#include "../Objectville/Hfdp.h"
#include "../Objectville/Object.hpp"
#include "../Objectville/Flight.hpp";
#include "../Objectville/Speech.hpp";

namespace Hfdp
{
	/**
	 *	Universal base class for any of several other, usually gallinaceous birds
	 *	that are barnyard, domesticated, or wild, as the duck, goose or turkey.
	 *
	 *	Book:	The authors suggest adding the ability to change behavior dynamically;
	 *			that its a 'shame' not to. I disagree; rather, I suggest that objects
	 *			should be immutable, when and wherever possible; that behavior, once
	 *			established, should remain invariant -- it promotes type-safety, just
	 *			as judicious usage of the keyword 'const' when and wherever possible. 
	 *
	 *			I suspect, their suggestion	came from a partial description of the
	 *			'Strategy' pattern, whereby	"algorithms can be selected at runtime".
	 *			Here, runtime means construction time, not execution time! Both happen
	 *			at runtime, but one happens	once and only once while the other happens
	 *			continuously.
	 *
	 *	C++:	Immutability + object semantics + smart pointers renders object
	 *			ownership a moot point. Implicitly, this also means deterministic
	 *			behavior in the presence of concurrency. Hence, I omitted the 'set'
	 *			methods that enabled changing either flight or speech behavior.
	 */
		Hfdp_DECL class Fowl : public Object
		{
			/**
			 *	friendship is given to the 'Fowl_factory' class so that it can
			 *	access the 'protected', default constructor. 
			 */
				friend class Fowl_factory;
			/**
			 *	initializes and instance of this class; 'protected' access level
			 *	prohibits direct instantiation, enforcing its intent as an 
			 *	abstract base class that does not have a 'pure virtual' method.
			 *
			 *	Idiom;	Ownership, sources and sinks, here, ownership transfer is 
			 *			implied through the use of auto_ptr parameter types;
			 *			it acts like a sink, whereby this class takes ownership of
			 *			the object referenced in the auto_ptr container and is 
			 *			responsible for its disposal.
			 *
			 *	Idiom;	Dependency Injection (DI): injection via constructor
			 *
			 *	Idiom;	Prefer initialization over assignment in constructors
			 */
				protected: Fowl(std::string type_name, std::auto_ptr<Flight> flight, std::auto_ptr<Speech> speech, float weight = 0.0)
				:	type_name(type_name),
					weight(weight),
					flight(flight.release()),			// inject and take ownership (sink)
					speech(speech.release())			// inject and take ownership (sink)
				{		
				}

				private: Fowl(const Fowl&);				// Disable copy constructor
				private: void operator=(const Fowl&);	// Disable assignment operator
			/**
			 *	overrides base implementation; gets a human-readable string that
			 *	describes this instance of the class
			 */
				private: virtual std::string
				to_string_impl() const
				{
					return type_name;
				}
				private: std::string type_name;
			/**
			 *	gets the weight of the fowl
			 */
				public: float 
				get_weight() 
				{ 
					return weight; 
				}
				private: float weight;
			/**
			 *	Executes (injected) flight behavior
			 */
				public: std::string 
				fly() const
				{
					return flight->execute();
				}
   				private: std::auto_ptr<Flight> flight;	// holds pointer to behavior actuator
			/**
			 *	Executes (injected) speech behavior
			 */
				public: std::string
				speak() const 
				{
					return speech->execute();
				}
   				private: std::auto_ptr<Speech> speech;	// holds pointer to behavior actuator
			/**
			 *	Executes (default) swim behavior
			 */
				public: std::string 
				swim() const 
				{
					return swim_impl();
				}
			/*
			 *	C++: 'private' (accessibility) applies to members, not the virtual call
			 *	mechanism; therefore they can be overridden by a derived class; 'protected'
			 *	would imply/allow derived class to call the base class
			 */
				private: virtual std::string		
				swim_impl() const
				{
					return "Any fowl can swim, even turkeys, but fake ones just float!";
				};
		};
}

#endif
