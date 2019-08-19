/*********************************.FILE_HEADER.*******************************/
/** @file operations.h
 *  @brief Contains the header file for server communication.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES****************************************/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
/**********************.IMPLICIT_DECLARATION.****************************/
int ServerCommunicate(char* psendMessage,char* preceiveMessage , unsigned int uPriority);

/*********************************CONSTANTS_DECLARATION*******************************/
/*!< Assigning integer values to Identifier names for return values */
#define SOCKET_FAILED -1 /*!< set return value if socket creation failed */
#define SET_SOCKET_OPTIONS_FAILED 1/*!< set return value if socket set options failed */
#define BIND_FAILED 2 /*!< set return value if bind failed */
#define LISTEN_FAILED 3 /*!< set return value if listen failed */
#define SUCCESS 0 /*!< set return value if communication succeeded */
/************************************************************************/
