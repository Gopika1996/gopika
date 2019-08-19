/*********************************.FILE_HEADER.*******************************/
/** @file client.c
 *  @brief This program contains the interface for Client communication.
 *  @date 2019/03/06
 *  @copyright 2019 QuEST Global Engineering Services Pvt. Ltd. (Software Division)
 *  @author 
 */
/***********************.INCLUDES********************************************************************************************/
#include "client.h"
/*********************************.FUNCTION_HEADER.*******************************/
/** @brief ClientCommunication
 *  Interface for client communication.
 *  @param psendMessage,preceiveMessage,uPriority 
 *  @return void 
 */
int ClientCommunication(char* psendMessage, char* preceiveMessage,unsigned int uPriority)
{
	int nsock, nresult, nstatus;
	char csendMessage[512]={0}, creceiveMessage1[512]={0},creceiveMessage2[512]={0};
	struct hostent *host;
	struct sockaddr_in serverAdd;	

	host = gethostbyname("192.168.0.6");

	if (-1 == (nsock = socket(AF_INET, SOCK_STREAM, 0)))
	{
		perror("Socket creation failed");
		return SOCKET_FAILED;
	}
	/*----Address family = Internet----*/
	serverAdd.sin_family = AF_INET; 

	/*----Set port number, using htons function to use proper byte order----*/  
	serverAdd.sin_port = htons(6000); 														
	serverAdd.sin_addr = *((struct in_addr *) host->h_addr);
	bzero(&(serverAdd.sin_zero), 8);

	/*----Connect the socket to the server using the address struct----*/
	nstatus = connect(nsock, (struct sockaddr *) &serverAdd, sizeof(struct sockaddr));	
	if ( -1 == nstatus) 																	
	{
		perror("Connection failed");
		return CONNECTED_FAILED;
	}
	if ( 0 == uPriority)	
	{
	strcpy(csendMessage, psendMessage);
	Resend:

	/*----Send message to the server----*/
	send(nsock, csendMessage, strlen(csendMessage), 0); 

	/*----Read the message from the server into the buffer----*/									
	nresult = recv(nsock, creceiveMessage1, DATA_SIZE, 0); 										
	creceiveMessage1[nresult] = '\0';
	printf("\nRecieved Message: %s ", creceiveMessage1);
	if(0 ==strcmp(creceiveMessage1,"NACKNOWLEDGEMENT"))
	{
		goto Resend;
	}
	strcpy(preceiveMessage, creceiveMessage1);
	}
	else 
	{ 	
	printf("\nsecond receive  ");
	sleep(2);

	/*----Read the message from the server into the buffer----*/
	nresult = recv(nsock, creceiveMessage2, DATA_SIZE, 0);										
	printf("\n%d",nresult);
	creceiveMessage2[nresult] = '\0';
	printf("\nRecieved Message: %s ", creceiveMessage2);
	if ( 0 == strlen(creceiveMessage2))
	{
		strcpy(csendMessage, "NACKNOWLEDGEMENT");
	}
	else
	{
		strcpy(csendMessage, "ACKNOWLEDGEMENT");
	}
	send(nstatus, csendMessage, strlen(csendMessage), 0);		
	}
	strcpy(preceiveMessage, creceiveMessage2);
	fflush(stdout);

	/*----close the connection----*/
	close(nstatus);
	
	return SUCCESS;
	
}


