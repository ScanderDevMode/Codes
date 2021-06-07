#ifndef _BLASTER_LIT_COMMON_HEADER
#define _BLASTER_LIT_COMMON_HEADER

//includes
#include <stdlib.h>
#include <stdio.h>
#include <map>


//Platform Dependency Check
#define XXWINDOWSXX 0001000
#define XXLINUXXX	0001001


//later in the rest of the code we will be checking for the Tag XXPLATFORM 
//to see which one it is set to

//windows includes
#ifdef _WIN32

#include <Shlwapi.h>
#define XXPLATFORM XXWINDOWSXX

#elif __LINUX__ //Linux Includes
	//Linux parts are to be implemented later to be implemented later
#define XXPLATFORM XXLINUXXX
#endif

//platform wise running utility
#define RUN_PLATFORM switch(XXPLATFORM) {
#define CASE_WIN case XXWINDOWSXX: {
#define CASE_LIN case XXLINUXXX: {
#define CASE_END }break;
#define RUN_PLATFORM_END };
#define RUN_ON_WIN if(XXPLATFORM == XXWINDOWSXX) {
#define RUN_ON_LIN if(XXPLATFORM == XXLINUXXX) {
#define RUN_ON_END RUN_PLATFORM_END


#endif
