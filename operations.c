/*********************************.FILE_HEADER.*******************************/
/** @file operations.c
 *  @brief  A communication interface for server.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */

/***********************.INCLUDES**************************************************************/
#include "operations.h"
/*! 
   \brief sets the constant integer value for strings.
   \param BUFFER_SIZE input value  
 */
#define BUFFERSIZE 1024
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief ServerCommunicate 
    *  This is the ServerCommunicate function used to establish a socket between client and server and to transfer data.
    *  @param pSendMessage is used to hold the message to be send.
    *  @param pReceiveMessage is used to hold the received message.
    *  @param uPriority is used to set the priority
    *  @return zero if the function is successful, otherwise return one.
    */
int ServerCommunicate(char* pSendMessage, char* pReceiveMessage,unsigned int uPriority)
{
    char sendMessage[BUFFERSIZE], receiveMessage[BUFFERSIZE];
	static int nSock =0, nConnected =0, nResult = 0;
	struct sockaddr_in serverAdd, clientAdd;
	int nLength = 0;
    if ( 0 == uPriority)
    {
		if(nSock<=0)
        {
        /*----Create a socket for communication----*/
			if ( -1 == (nSock = socket(AF_INET, SOCK_STREAM, 0)))                                 
			{
				perror("Socket creation is failed");
				return SOCKET_FAILED;
			}
			if ( -1 == setsockopt(nSock, SOL_SOCKET, SO_REUSEADDR, &(int ) { 1 }, sizeof(int)))
			{
				perror("Set socket option");
				return SET_SOCKET_OPTIONS_FAILED;
			}
			serverAdd.sin_family = AF_INET;
			serverAdd.sin_port = htons(6000);                                                        
			serverAdd.sin_addr.s_addr = INADDR_ANY;
			bzero(&(serverAdd.sin_zero), 8);        
			/*----Bind the local port and connection address----*/
			if ( -1 == bind(nSock, (struct sockaddr *) &serverAdd, sizeof(struct sockaddr)))
			{
				perror("Unable to bind");
				return BIND_FAILED;
			}
			/*----Listen for client connection----*/    
			if (-1 == listen(nSock, 3))
			{
				perror("Listen");
				return LISTEN_FAILED;
			}
		}
		printf("TCPServer Waiting for client connection\n");
		fflush(stdout);
		printf(" Starting...\n");
		nLength = sizeof(struct sockaddr_in);       
		/*----Accept connection from client----*/
		nConnected = accept(nSock, (struct sockaddr *)&clientAdd,(socklen_t *)&nLength);
		printf("\n%d",nConnected);		
		nResult = recv(nConnected, receiveMessage, 512, 0);
		receiveMessage[nResult] = '\0';		  
		if ( 0 == strlen(receiveMessage))
		{
			strcpy(sendMessage, "NACKNOWLEDGEMENT");
		}
		else
		{
			strcpy(sendMessage, "ACKNOWLEDGEMENT");
		}
		send(nConnected, sendMessage, strlen(sendMessage), 0);
		fflush(stdout);        
	}
    else 
    {
        nConnected = accept(nSock, (struct sockaddr *)&clientAdd,(socklen_t *)&nLength);
        strcpy(sendMessage, pSendMessage);
        nResult=send(nConnected, pSendMessage, strlen(pSendMessage), 0);         
    }
    strcpy(pReceiveMessage, receiveMessage);
    printf(" end of loop...\n");    
    close(nConnected);
    return SUCCESS;    
}

