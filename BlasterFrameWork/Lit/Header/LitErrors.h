#ifndef _BLASTER_LIT_ERRORS_HEADER_
#define _BLASTER_LIT_ERRORS_HEADER_


namespace BF {

	namespace Lit {
		
		//enum containing the types of the error
		typedef enum _LIT_ERRORS {
			UNKNOWN_ERROR = 101,
			NO_MEMORY,
			INVALID_ARGUMENT,
			TYPE_UNKNOWN
		}LIT_ERRORS;
		

		//2d array contaning the messages for the error types
		const char* _LIT_ERROR_MESSAGES[] = {
			"Unknown Error Occured",
			"No Memory available for instantiating",
			"Invalid Argument Type or Value",
			"The type of the image file is unknown"
		};


		/*
		* Function to get the error details
		* Params :
		*	errorType - The type of the error to get the details of.
		* Return :
		*	returns a constant error message situated with the error code
		*/
		const char* getErrorMessage(LIT_ERRORS errorType) {
			return _LIT_ERROR_MESSAGES[(errorType - 100) - 1];
		}
	}

}


#endif
