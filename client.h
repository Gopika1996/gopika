/*********************************.FILE_HEADER.*******************************/
/** @file client.h
 *  @brief Contains the header file for client communication.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include <errno.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
/**********************.IMPLICIT_DECLARATION.*********************************/
int ClientCommunication(char* psendMessage,char* preceiveMessage ,unsigned int uPriority);
/*****************************************************************************/
/*! 
   \brief sets the constant integer value for strings.
   \param SOCKET_FAILED as input value   
*/
#define SOCKET_FAILED -1
/*! 
   \brief sets the constant integer value for strings.
   \param CONNECTED_FAILED as input value   
*/
#define CONNECTED_FAILED 1
/*! 
   \brief sets the constant integer value for strings.
   \param SUCCESS as input value   
*/
#define SUCCESS 0
/*! 
   \brief sets the constant integer value for strings.
   \param DATA_SIZE as input value   
*/
#define DATA_SIZE 1024
/*****************************************************************************/
