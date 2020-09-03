#ifndef	_hfdp_cpp_
#define _hfdp_cpp_

#if defined(WIN32)
	#pragma warning (disable : 4100)	// unreferenced formal parameter
	#pragma warning (disable : 4355)	// 'this' used in base member initialize list
	#pragma warning (disable : 4018)	// 'expression' : signed/unsigned mismatch
	#pragma warning (disable : 4067)	//: unexpected tokens following preprocessor directive
#endif

	#if !defined(Hfdp_DECL)
		#if defined(WIN32) && defined(Hfdp_DLL)
			#if defined(Hfdp_EXPORTS)
				#define Hfdp_DECL __declspec(dllexport)
				#define Hfdp_DECL_TEMPL
				#pragma warning (disable : 4018)
			#else
				#define Hfdp_DECL __declspec(dllimport)
				#define Hfdp_DECL_TEMPL extern
				#pragma warning (disable : 4018)
			#endif // Hfdp_EXPORTS
		#else
			#define Hfdp_DECL
			#define Hfdp_DECL_TEMPL
		#endif
	#endif

#endif
