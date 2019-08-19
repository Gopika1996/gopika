/*********************************.FILE_HEADER.*******************************/
/** @file serveroperations.c
 *  @brief Perofrms concatenation and parsing.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include "serveroperations.h"
/*! 
   \brief sets the constant integer value for strings.
   \param SUCCESS input value  
 */
#define SUCCESS 0
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Concatenate
 *  Concatinating the user credentials and a string which notify the operation to be performed at server side.
 *  @param ucStr1, ucStr2
 *  @return Concatenated string.
 */
char* Concatenate(char* ucStr1, char* ucStr2) 
{		
    strcat(ucStr1,ucStr2);
    return SUCCESS;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief Parsing
 *  This function is used for parsing.
 *  @param cstr1 hold the parsed string
 *  @param cstr2 hold the string to be parse
 *  @param nIndex hold the index value
 *  @param nLength hold the length of the string
 *  @return true if the function is successful, otherwise returns false.
 */
bool Parsing(char cstr1[], char cstr2[], int nIndex, int nLength) 
{
	int nInc = 0;
	if ( 0 <= nIndex)
	{
		while (nInc < nLength) 
		{
			cstr2[nInc] = cstr1[(nIndex + nInc)];
			nInc++;
		}
		cstr2[nInc] = '\0';
		return true;
	}
	else 
	{
		printf("Error condition occured");
		return false;
	}
}

