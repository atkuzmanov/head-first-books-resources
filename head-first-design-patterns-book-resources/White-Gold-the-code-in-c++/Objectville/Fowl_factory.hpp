#ifndef	_hfdp_cpp_objectville_fowl_factory_hpp_
#define _hfdp_cpp_objectville_fowl_factory_hpp_

#include <ctime>
#include <map>

#include "../Objectville/Hfdp.h"
#include "../Objectville/Object.hpp"
#include "../Objectville/Singleton.hpp";
#include "../Objectville/Flight.hpp";
#include "../Objectville/Speech.hpp";
#include "../Objectville/Fowl.hpp";
#include "../Objectville/Fowl_factory.hpp";

namespace Hfdp
{
	/*
	 *	gets a random number between minimum and maximum; used to establish the
	 *	weight of a newly created fowl.
	 *
	 *	Idiom:	non-member because it can be implemented via C's public interface
	 */
		float weight(float minimum, float maximum) 
		{ 
			float value = ((float) std::rand()) / (float) RAND_MAX; 
			float range = std::max(minimum, maximum) - std::min(minimum, maximum);

			return (value * range) +  std::min(minimum, maximum);
		};
	
	/**
	 *	A fowl factory 'is a' singleton abstract factory that makes (creates)
	 *	one of several (preconfigured) types of fowls.
	 *
	 *	Book:	Several types of birds and behaviors are mentioned; however, four
	 *			types are sufficient to illustrate the pattern(s); specifically, 
	 *			Wild turkey, Mallard, Rubber and Decoy ducks. Other fowl and
	 *			behaviors were omitted for brevity and clarity.
	 */
		Hfdp_DECL class Fowl_factory : public Singleton<Fowl_factory>, public Object
		{
			/**
			 *	friendship is given to the 'singleton' class so that it can
			 *	access the 'protected', default constructor. 
			 */
				friend class Singleton<Fowl_factory>;
			/**
			 *	Initializes and instance of this class; constructors & assignment
			 */
				protected: Fowl_factory()
				{
					srand((unsigned)time(0));					// seeds random 'weight' method
				}

				private: Fowl_factory(const Fowl_factory&);		// Disable copy constructor
				private: void operator=(const Fowl_factory&);	// Disable assignment operator
			/**
			 *	Implements winged flight behavior
			 */
				private: class Winged_flight : public Flight 
				{
					public: virtual std::string
					execute() const
					{
						return "I'm flying with wings!!";		// TODO: make this a resource
					}
				};
			/**
			 *	Implements flightless behavior
			 */
				private: class Negated_flight : public Flight 
				{
					public: virtual std::string
					execute() const
					{
						return "I can't fly!";					// TODO: make this a resource
					}
				};
			/**
			 *	Implements gobble speech behavior
			 */
				private: class Gobble_speech : public Speech 
				{
					public: virtual std::string
					execute() const
					{
						return "Gobble, Gobble";				// TODO: make this a resource
					}
				};
			/**
			 *	Implements quack speech behavior
			 */
				private: class Quack_speech : public Speech 
				{
					public: virtual std::string
					execute() const
					{
						return "Quack!";						// TODO: make this a resource
					}
				};
			/**
			 *	Implements squeak speech behavior
			 */
				private: class Squeak_speech : public Speech 
				{
					public: virtual std::string
						execute() const
					{
						return "Squeak!";						// TODO: make this a resource
					}
				};
			/**
			 *	Implements speechless behavior
			 */
				private: class Negated_speech : public Speech 
				{
					public: virtual std::string
					execute() const
					{
						return "<< silence >>";					// TODO: make this a resource
					}
				};

			///	The following class declarations define and expose supported factory
			///	types. That is, the types that this factory can create. In this
			/// regard, they are implicitly part of the interface. Their purpose is
			///	to provide an explicit, type-safe identifier used to make an 
			///	instance of a 'Fowl'; see specialized 'make' methods below. 
			///
			///	They are declared such that they cannot be instantiated, copied or
			/// assigned to. In effect, they are an empty, do-nothing class. Since
			/// each contains only a 'static' string, kept elsewhere in C++'s memory
			/// management, they have a size of one (1), afforded by the compilers
			/// "empty base class optimization"; they represent very simple concepts
			///	without overhead; type names -- Stroustrup 

			/**
			 *	The Mallard, or wild duck is the ancestor of most domestic ducks and
			 *	lives in wetlands, eats water plants, and is gregarious. Males have
			 *	a bright green or blue head, while the female's is light brown.
			 *
			 *	C++:	Defining a copy-constructor inhibits the compiler generated
			 *			default	constructor; effectively inhibiting its instantiation
			 */
				public: class Mallard_duck
				{
					public: static std::string 
					type_name()
					{
						static std::string value("Fowl_factory::Mallard_duck");
						return value;
					}

		 			private: Mallard_duck(const Mallard_duck&);		// Disable copy constructor
					private: void operator=(const Mallard_duck&);	// Disable assignment operator
				};
			/**
			 *	The Turkey or wild turkey is native to the forests of North America. Males
			 *	of both species have a distinctive fleshy wattle or protuberance that hangs
			 *	from the top of the beak—called a snood in the Wild Turkey and its domestic
			 *	descendants.
			 *
			 *	C++:	Defining a copy-constructor inhibits the compiler generated
			 *			default	constructor; effectively inhibiting its instantiation
			 */
				public: class Wild_turkey
				{
					public: static std::string 
					type_name()
					{
						static std::string value("Fowl_factory::Wild_turkey");
						return value;
					}

		 			private: Wild_turkey(const Wild_turkey&);		// Disable copy constructor
					private: void operator=(const Wild_turkey&);	// Disable assignment operator
				};
			/**
			 *	The decoy duck is an artificial duck that exhibits no behavior
			 *
			 *	C++:	Defining a copy-constructor inhibits the compiler generated
			 *			default	constructor; effectively inhibiting its instantiation
			 */
				public: class Decoy_duck
				{
					public: static std::string
					type_name()
					{
						static std::string value("Fowl_factory::Decoy_duck");
						return value;
					}

		 			private: Decoy_duck(const Decoy_duck&);			// Disable copy constructor
					private: void operator=(const Decoy_duck&);		// Disable assignment operator
				};
			/**
			 *	The decoy duck is an artificial duck that exhibits no behavior
			 *
			 *	C++:	Defining a copy-constructor inhibits the compiler generated
			 *			default	constructor; effectively inhibiting its instantiation
			 */
				public: class Rubber_duck
				{
					public: static std::string
					type_name()
					{
						static std::string value("Fowl_factory::Rubber_duck");
						return value;
					}

		 			private: Rubber_duck(const Rubber_duck&);		// Disable copy constructor
					private: void operator=(const Rubber_duck&);	// Disable assignment operator
				};

			///
			///	The following template declarations expose methods to create different
			///	types of fowls; class types provide a type-safe way to identify which
			/// type of fowl to create. I believe this is superior to using enum's or
			/// strings that impose some sort of comparison operation.
			///

			/**
			 *	makes an empty (null) instance of a fowl; it is used as a base template
			 *	definition that supports specializations (shown below)
			 */
				public: template <typename T> std::auto_ptr<Fowl>
				make() const
				{
					return std::auto_ptr<Fowl>(0);					// A 'null' auto_ptr
				}
			/**
			 *	makes an instance of a 'Decoy_duck'.
			 *
			 *	Idiom;	Ownership, sources and sinks, here, ownership transfer is 
			 *			implied through the use of auto_ptr return value;
			 *			it acts like a source, whereby the caller takes ownership
			 *			of the object referenced in the auto_ptr container and is 
			 *			responsible for its disposal.
			 *
			 *	C++;	Template Specialization, empty class type identifier affords
			 *			method overriding based on type
			 */
				public: template<> std::auto_ptr<Fowl>
				make<Decoy_duck>() const
				{
					Fowl* fowl = new Fowl (	Decoy_duck::type_name(),
						std::auto_ptr<Flight>(new Negated_flight),	// is flightless,
						std::auto_ptr<Speech>(new Negated_speech),	// speechless, and
						weight(0.1f, 0.9f));						// weighs under 1 pound

					return std::auto_ptr<Fowl>(fowl);
				}
			/**
			 *	makes an instance of a 'Rubber_duck'.
			 *
			 *	Idiom;	Ownership, sources and sinks, here, ownership transfer is 
			 *			implied through the use of auto_ptr return value;
			 *			it acts like a source, whereby the caller takes ownership
			 *			of the object referenced in the auto_ptr container and is 
			 *			responsible for its disposal.
			 *
			 *	C++;	Template Specialization, empty class type identifier affords
			 *			method overriding based on type
			 */
				public: template<> std::auto_ptr<Fowl>
				make<Rubber_duck>() const
				{
					Fowl* fowl = new Fowl (Rubber_duck::type_name(),
						std::auto_ptr<Flight>(new Negated_flight),	// is flightless,
						std::auto_ptr<Speech>(new Squeak_speech),	// squeaks, and
						weight(0.01f, 0.1f));						// weighs under 1/10 pound

					return std::auto_ptr<Fowl>(fowl);
				}
			/**
			 *	makes an instance of a 'Mallard_duck'.
			 *
			 *	Idiom;	Ownership, sources and sinks, here, ownership transfer is 
			 *			implied through the use of auto_ptr return value;
			 *			it acts like a source, whereby the caller takes ownership
			 *			of the object referenced in the auto_ptr container and is 
			 *			responsible for its disposal.
			 *
			 *	C++;	Template Specialization, empty class type identifier affords
			 *			method overriding based on type
			 */
				public: template<> std::auto_ptr<Fowl>
				make<Mallard_duck>() const
				{
					Fowl* fowl = new Fowl (Mallard_duck::type_name(),
						std::auto_ptr<Flight>(new Winged_flight),	// flies on wings,
						std::auto_ptr<Speech>(new Quack_speech),	// quacks, and
						weight(1.0f, 3.0f));						// weighs between 1 & 3 pounds

					return std::auto_ptr<Fowl>(fowl);
				}
			/**
			 *	makes an instance of a 'Wild_turkey'.
			 *
			 *	Idiom;	Ownership, sources and sinks, here, ownership transfer is 
			 *			implied through the use of auto_ptr return value;
			 *			it acts like a source, whereby the caller takes ownership
			 *			of the object referenced in the auto_ptr container and is 
			 *			responsible for its disposal.
			 *
			 *	C++;	Template Specialization, empty class type identifier affords
			 *			method overriding based on type
			 */
				public: template<> std::auto_ptr<Fowl>
				make<Wild_turkey>() const
				{
					Fowl* fowl = new Fowl (Wild_turkey::type_name(),
						std::auto_ptr<Flight>(new Winged_flight),	// flies on wings,
						std::auto_ptr<Speech>(new Gobble_speech),	// gobbles, and
						weight(10.0f, 20.0f));						// weighs between 10 & 20 pounds

					return std::auto_ptr<Fowl>(fowl);
				}
		};
}

#endif

