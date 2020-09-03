Welcome to the 'white-gold' version of Head First Design Patterns in C++. It is
called 'white-gold', an alloy of 'silver' and 'gold' because it is just that, a
combination of the 'silver' and (forthcoming) 'gold' version. Regrettably, I am
not satisfied with the 'silver' version and I intend to replace it with this one
once it has been vetted.

Discussion and comments regarding this release are available and encouraged at:
	http://hfdpcpp.wordpress.com/white-gold/

Conventions and terms used throughout documentation blocks in this code-base:

	Book:	In direct reference to the book "Head First Design Patterns", whereby
			comments, concerns are stated that may or may not alter the example.

	Idiom:	A distinct style, either implicitly or explicitly for implementing
			or ensuring some software or language behavior, principles,	patterns
			or practices

	C++:	A side-effect, or some other language specific factoid


Interestingly, in the book "Head First Design Patterns", there is no 'Objectville'
library; however, I couldn't resist creating one because it seems only fitting 
that there is one and its name too cool to pass-up :-)

Disclaimer and rules-of-engagement; I do not claim to be a C++ guru; rather, a
disciple of the language. If you are here, then you too are on a journey through
a jungle of design patterns, practices, principles and idioms, which strangely 
reminds me of the Disney Jungle Cruise ride. :-) The Jungle Cruise is of course,
a whimsical and controlled boat ride through the world’s most exotic rivers.
Along the way, the captain makes pun-y remarks about various audio-animatronics 
systematically positioned on its predetermined route. For a short time, passengers
surrender their conception of reality and enjoy the ride; they seem to embrace and
enjoy the suggestions, between conventional wisdom and artistic expression. At the
end of the ride, when the boat returns to the dock, the captain says his final
goodbye…

	“If you enjoyed the ride, my name is Glenn and this has been the world famous
	 Jungle Cruise. And if you had a lousy ride... well, then my name is Ryan and
	 this has been Space Mountain.”

Whimsically, of course, the jungle cruise is Head First Design Patterns in C++.
And, of course, if you find errors, omissions or otherwise think I completely
missed the boat, let me know. If you find the coding-style (explained below) or
any other syntactical-sugar nauseating, well, then your going to have a lousy ride.

First stop, The seemingly redundant access modifiers (public, protected & private).
Being explicit as possible is desirable -- even at the cost of a few keystrokes. 
Most apparent is the adoption of Java and C# access modifier syntax.

For example:

	Class Foo 
	{
		public: Foo();
		public: ~Foo();

		private: int _Bar;
		private: void Bar() { }
	}

Feedback has suggested that this syntax looks verbose. Yep; however, there is a
certain quality about a self-contained definition; one does not have to scan up
the class definition looking for its access modifier block. If the code is terse,
block style, access modifiers are effective; however, if the code is verbose,
contains documentation or in the case of templates, contains the implementation
of a method as well, block modifiers are less effective; their definition is not
in close proximity to the members definition. 

The intent is to be as explicit as possible without sacrificing clarity. It is a
style choice that I have grown to appreciate in practice.I never understood the
complaint of a few extra keystrokes at the expense of clarity. It is probably a
cultural carry-over of the C axiom of not paying for what you do not use; apparently,
this extends to writing code as well. Frankly, I don't care how long it takes a 
compiler to parse my code! I care how long it takes someone to read, understand
and most importantly, maintain my code!

	“Programs must be written for people to read, 
		and only incidentally for machines to execute.”		~ Hal Abelson,

Next stop, the naming convention. In the spirit of axiom "Programs must be written
for people to read", and because it is well known that lower-case letters are easier
to read than UPPER_CASE letters and for the sake of consistency because I make heavy
use of the C standard library (STL). I mimic the their naming convention and use
mostly lower-case letters with one exception, nouns such as class names begin with
an upper-case letter, as suggested by English grammar. 
	
Next, and perhaps most controversial, are multi_word identifiers. Here, more than
anywhere else conventions diverge. In the STL, an underscore is used as a word
separator (e.g. out_of_range). To this extent, class names begin with an uppercase
letter, and multi-word identifiers are separated by an underscore, for example,
'Fowl_factory', 'Winged_flight' and 'Quack_speech'.

Next is the indentation style of method declarations, syntactical-sugar, whereby
the method name appears on a subsequent (indented) line. 

For example:

		public: const std::type_info& 
			get_type_info() const
			{
				return get_type_info_impl();
			}

Here you see the declaration of 'public' and return type appear on the first line,
whereas, the name of the method appears on the subsequent (indented) line. This is
in contrast to the common convention of placing everything on a single line:

For example:

		public: const std::type_info& get_type_info() const
			{
				return get_type_info_impl();
			}

It is a matter of style and esthetics, the experience C++ developer might object;
however, and because I adopted the STL naming convention, I find it tedious to
visually scan this line, picking out the method name from its declarations. It is
argued that adopting a camelCase convention would make it easier; however, the 
intent of this library is to demonstrate design patterns, not debate naming 
conventions -- this, like many things, is a style choice, I like it because it
makes it easier (for me) to pick out the method name and it keeps the line shorter,
especially if you have many parameters. Where the curly-brace '{' is positioned is
syntactical-sugar and irrelevant (to me) as long as it is consistent.

	“The nicest thing about standards is
		 that there are so many to choose from”		~ Andres Tannenbaum

An effective standard is essential to ensure consistency and comprehension. Yet,
violations, or worse, complete disregard is often the rule rather than the exception.
Enforcement of standards is difficult; it demands regulation by some policy, individual
or group of individuals. Often, an individual’s personal affinity to another style
hinders compliance. Plausibly, due to the artistic nature of writing software; 
developers, like artists, have adopted their own style and are reluctant to abandon
them to conform to another. One culprit is that many coding standards focus primarily
on syntactical sugar. Since the human audience is the focus of writing software,
there is merit in embracing the grammatical rules of English – the de facto vocabulary
of both software developers and languages. If applied correctly, it resolves many 
afflictions other standards try to regulate.

	Noun – Class, Interfaces, Structure & Namespace

In English a noun is a person, place, thing or idea; common or proper. A proper noun
tells what something is and has two distinctive traits 1) it will name a specific
[usually a one-of-a-kind] item, and 2) it will begin with a capital letter. In
software, a proper noun is a class, interface or structure. When creating a class
(noun), it is important to limit work in a constructor to capturing parameters and
setting members such that, immediately after creation, an instance can cause no harm;
it should throw no exceptions and return plausible values – the law of least astonishment.

Too much work in the constructor inhibits instantiation and prevents altering 
collaborators during testing. Constructors should ask for collaborators rather than
trying to create or initialize them. Pragmatically, it does not make sense for a
car to know how to create its engine; it should be given one, not figure out how
to make one; nor should it be given a reference to the factory that can create it.
In the same way, some constructors reach out to resources that are not directly needed;
only what the resource creates is needed; it violates the Law of Demeter (LoD). 

Suggesting a method only needs a string, then secretly looking for some other resource,
is a violation of its contractual agreement – to do so is deceitful. Its name should
clearly communicate intent and purpose – its role. When you can name something accurately
and completely, you are better able to isolate responsibilities. If you can’t
express what something is or does in a single sentence, without using the word ‘and’,
then it probably has more than one responsibility and needs to be multiple objects. 
 
	Syntax & Grammar

Linguistically, syntax is the grammatical arrangement of words in a sentence; it
is primarily concerned with the structure of the sentence. Most software languages
dictate syntax and grammar; however, there is freedom in naming components. 

Name properties and variables using a noun, noun phrase or adjective.

For example:

	[Adjective,…]_noun;

	Fowl is a noun
	Fowl_factory is an adjective + noun

Use helping verbs (“is”, “can”, or “has”) with Boolean properties; Boolean properties
imply state. Methods imply behavior, which implies action. Name methods using a
verb-object pair, for example: to_string(), get_type_name. The following is the
suggested pattern:

	[{<conjunction> | adverb …}] verb <conjunction> adjective … noun;

	Conjunctions: do, in, on, for

	connect					// is a verb
	asynchronously_connect	// is an adverb + verb
	compare_string			// is a verb + noun
	compare_unicode_string	// is a verb + adjective + noun
	put_at_end				// is a verb + conjunction + noun
	on_start				// is a conjunction + verbal noun
	is_visible				// is a verb + adjective

Finally, the combining of declaration and definitions in a single (.hpp) file,
giving 'true' meaning to the extension '.hpp' -- it is a header that contains code.
I do this for convenience to the reader who is trying to understand the pattern
or idiom; I am not trying to build an industrial-strength enterprise library. 
Still, this is not unheard of, templates require you to do so. ;-)

You will find the word 'Idiom' throughout the code-base. These phrases are not mine,
they came from one of several sources; however, to avoid verbose citations, code
clutter and the possibility that they exist in more than one source, I adopted
for the solitary word: 'Idiom' and list any/all possible sources here:

	Effective STL [Scott Meyers]
	Effective C++ Third Addition [Scott Meyers]
	More Effective C++ [Scott Meyers]
	Modern C++ Design [Andrei Alexandrescu]
	C++ Coding Standards [Herb Sutter, Andrei Alexandrescu]
	Exceptional and More Exceptional C++ [Herb Sutter]

To this extent, function definitions and declarations adhere to Scott Meyers axiom,
that I shamelessly copied here: 

Let 'f' be the function, and 'C', the class:

	"if (f needs to be virtual)
	   make f a member function of C;
	else if (f is operator>> or operator<<)
	   {
		make f a non-member function;
		if (f needs access to non-public members of C)
			make f a friend of C;
	   }
	else if (f needs type conversions on its left-most argument)
	   {
		make f a non-member function;
		if (f needs access to non-public members of C)
			make f a friend of C;
	   }
	else if (f can be implemented via C's public interface)
	   make f a non-member function;
	else
	   make f a member function of C"

