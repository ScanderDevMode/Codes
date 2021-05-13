#ifndef _BLASTER_LIT_ERRORS_HEADER_
#define _BLASTER_LIT_ERRORS_HEADER_


namespace BF {

	namespace LIT {
		
		//enum containing the types of the error
		typedef enum _LIT_ERRORS {
			UNKNOWN_ERROR = 101,
			NO_MEMORY,
			INVALID_ARGUMENT
		}LIT_ERRORS;
		


		




		/*
		* Function to get the error details
		* Params :
		*	errorType - The type of the error to get the details of.
		*	
		*/
		void getError(LIT_ERRORS errorType, );
	}

}


#endif
