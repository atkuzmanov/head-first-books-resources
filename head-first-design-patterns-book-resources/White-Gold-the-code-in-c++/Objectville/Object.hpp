#ifndef	_hfdp_cpp_objectville_object_hpp_
#define _hfdp_cpp_objectville_object_hpp_

#include <memory>
#include <string>

#include "../Objectville/Hfdp.h"

namespace Hfdp
{ 
	/**
	 *	This is the ultimate base class of all classes in (Hfdp) 'Objectville';
	 *	it is the root of the type hierarchy and exhibits the 'NVI (non-virtual interface)
	 *	idiom, "prefer to make interfaces non-virtual, using a private virtual
	 *	template method"; it separates that which varies from that which does not;
	 *	its invariant and variant parts. The invariant part, its interface is
	 *	defined as 'public' whereas the variant	parts, its implementation is 
	 *	defined by 'private virtual' functions that may or may not be overridden
	 *	in derived classes.
	 */
		Hfdp_DECL class Object 
		{
			/**
			 *	a numeric value used to identify an object during equality testing,
			 *	or as an index for an object in a collection, or for hashing algorithms
			 *	in data structures such as a hash table.
			 */
				private: size_t hash_code;
			/**
			 *	Initializes and instance of this class. Specifically, a hash code
			 *	using Knuth's Multiplicative Method in Knuth's
			 *	"The Art of Computer Programming", section 6.4, a multiplicative
			 *	hashing scheme is introduced as a way to write hash function. The
			 *	key is multiplied by the golden	ratio of 2^32 (2654435761) to produce
			 *	a hash result
			 */
				public: Object()
				{
					hash_code = reinterpret_cast<size_t>(this) * 2654435761U;
				}
			/**
			 *	Idiom: 'Declare destructor virtual in polymorphic base classes'.
			 *	Idiom: 'Declare destructor virtual if and only if that class contains
			 *			at least one virtual function'.
			 */	
				public: virtual ~Object()
				{
				}
			/**
			 *	operator override; returns 'true' if 'this' instance is considered
			 *	equal to the 'other' instance; otherwise, 'false'
			 */
				public: bool 
				operator== (const Object &other) const
				{
					return get_hash_code() == other.get_hash_code();
				}
			/**
			 *	operator override; returns 'true' if 'this' instance is considered
			 *	not equal to the 'other' instance; otherwise, 'false'
			 */
				public: bool 
				operator!= (const Object &other) const
				{
					return !(*this == other);
				}
			/**
			 *	operator override; returns 'true' if 'this' instance is considered
			 *	less than to the 'other' instance; otherwise, 'false'
			 */
				public: bool 
				operator< (const Object& other) const	
				{
					return get_hash_code() < other.get_hash_code();
				}
			/**
			 *	operator override; returns 'true' if 'this' instance is considered
			 *	less-than or equal to the 'other' instance; otherwise, 'false'
			 */
				public: bool 
				operator<= (const Object& other) const	
				{
					return get_hash_code() <= other.get_hash_code();
				}
			/**
			 *	operator override; returns 'true' if 'this' instance is considered
			 *	greater-than to the 'other' instance; otherwise, 'false'
			 */
				public: bool
				operator> (const Object& other) const	
				{
					return get_hash_code() > other.get_hash_code();
				}
			/**
			 *	operator override; returns 'true' if 'this' instance is considered
			 *	greater-than or equal to the 'other' instance; otherwise, 'false'
			 */
				public: bool 
				operator>= (const Object& other) const	
				{
					return get_hash_code() >= other.get_hash_code();
				}
			/**
			 *	to_string; gets a textual description of this class. 
			 *
			 *	Idiom: 'NVI (non-virtual interface); prefer to make interfaces non-virtual,
			 *	using a private virtual template method'
			 */
				public: std::string	
				to_string() const
				{
					return to_string_impl();			// call private, virtual implementation
				}
			/**
			 *	to_string_impl; implements creating a textual description
			 *
			 *	C++: 'private' (accessibility) applies to members, not the virtual call
			 *	mechanism; therefore they can be overridden by a derived class; 'protected'
			 *	would imply/allow derived class to call the base class
			 */
				private: virtual std::string
				to_string_impl() const
				{
					return std::string(typeid(this).name());
				}
			/**
			 *	get_hash_code; gets a numeric value used to identify an object during
			 *	equality testing, or as an index for an object in a collection, or for
			 *	hashing algorithms in data structures such as a hash table. The default
			 *	implementation does not guarantee uniqueness. Once determined, the value
			 *	of the hash code must remain exactly the same regardless of any changes
			 *	that are made to the object.
			 *
			 *	Idiom: 'NVI (non-virtual interface); prefer to make interfaces non-virtual,
			 *	using a private virtual template method'.
			 */
				public: size_t 
				get_hash_code() const
				{
					return get_hash_code_impl();	// call private, virtual implementation
				};
			/**
			 *	get_hash_code_impl; gets a hash code using Knuth's Multiplicative Method
			 *	in Knuth's "The Art of Computer Programming", section 6.4, a multiplicative
			 *	hashing scheme is introduced as a way to write hash function. The key is
			 *	multiplied by the golden ratio of 2^32 (2654435761) to produce a hash result.
			 *
			 *	C++: 'private' (accessibility) applies to members, not the virtual call
			 *	mechanism; therefore they can be overridden by a derived class; 'protected'
			 *	would imply/allow derived class to call the base class
			 */
				private: virtual size_t		
				get_hash_code_impl() const
				{
					return hash_code;
				};
			};
	/**
	 *	operator<<; insertion: Idiom; 'make operator<< non-member & non-friend if
	 *	access to private members is not required (see readme)'
	 */
		inline std::ostream& 
		operator<<(std::ostream& stream, const Object& subject)
		{
			return stream << subject.to_string().c_str();
		}
}

#endif
