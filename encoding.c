/*********************************.FILE_HEADER.*******************************/
/** @file encoding.c
 *  @brief This program contains program for encryption and decryption.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */

/***********************.INCLUDES*************************************************************************/

#include "encoding.h"

/*! 
   \brief sets the constant integer value for strings.
   \param KEYVALUE input value  
 */
#define KEYVALUE 4 
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief encrypt
 *  This function is used to encrypt the data.
 *  @param pBuf hold the data to be encrypted is stored as a character pointer type.
 *  @param nMaxSize hold maximum size of the pointer data.  
 *  @return the encrypted data.
 */
char * Encrypt(char *pBuf,int nMaxSize)
{
	unsigned int uInc;
	for (uInc = 0; (uInc < nMaxSize && pBuf[uInc] != '\0'); uInc++)
	{
		/*----the key for encryption is 3 that is subtracted to ASCII value----*/
		pBuf[uInc] = pBuf[uInc] + KEYVALUE;											 
	}
	return pBuf;
}
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief encrypt
 *  This function is used to decrypt the data.
 *  @param pBuf hold the data to be decrypted is stored as a character pointer type.  
 *  @param nMaxSize hold maximum size of the pointer data. 
 *  @return the decrypted data.
 */
char * Decrypt(char *pBuf,int nMaxSize) 
{
	unsigned int uInc;
	for (uInc = 0; (uInc < nMaxSize && pBuf[uInc] != '\0'); uInc++)
	{
		/*----the key for encryption is 3 that is subtracted to ASCII value----*/
		pBuf[uInc] = pBuf[uInc] - KEYVALUE; 											
	}
	return pBuf;
}

