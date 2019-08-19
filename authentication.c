/*********************************.FILE_HEADER.*******************************/
/** @file authentication.c
 *  @brief This program contains program authentication of user credentials.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES**************************************************************/
#include "authentication.h"
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Authenticate
 *  This function is used for authentication of user credentials.
 *  @param pcArg1 hold the PIN number received from the user.
 *  @param pcArg2 hold the PIN number fetched from the database.  
 *  @return true if the function is successful, otherwise returns false.
 */
bool Authenticate(char* pcArg1 , char* pcArg2)
{
/*----Compare the value received PIN and Actual PIN----*/
	if ( 0 == strcmp(pcArg1,pcArg2) ) 													
	{
	/*----If PIN are matching returns true----*/
		return true;														
	}
	else
	{
	/*----If PINs are not matching then return false----*/
		return false;																	
	}
}
