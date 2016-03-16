/* to compile me in Linux, type:   gcc -o concurrentserver concurrentserver.c -lpthread */

/* server.c - code for example server program that uses TCP */
/* From Computer Networks and Internets by Douglas F. Comer */

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include <stdlib.h>
#include <errno.h>
#include <sys/wait.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>

#include <pthread.h>
#include <stdio.h>
#include <string.h>

#define LENGTH 512 

void * serverthread(void * parm);       /* thread function prototype    */

pthread_mutex_t  mut;

#define PROTOPORT         5193          /* default protocol port number */
#define QLEN              6             /* size of request queue        */

int visits =  0;                        /* counts client connections     */

/*************************************************************************
 Program:        concurrent server

 Purpose:        allocate a socket and then repeatedly execute the folllowing:
                          (1) wait for the next connection from a client
                          (2) create a thread to handle the connection
                          (3) go back to step (1)

                 The server thread will
                          (1) update a global variable in a mutex
                          (2) send a short message to the client
                          (3) close the connection

 Syntax:         server [ port ]

                            port  - protocol port number to use

 Note:           The port argument is optional. If no port is specified,
                        the server uses the default given by PROTOPORT.

**************************************************************************
*/



struct myDirectory{
	char name[20];
	char path[100];
};


int main (int argc, char *argv[])
{
     struct   hostent   *ptrh;     /* pointer to a host table entry */
     struct   protoent  *ptrp;     /* pointer to a protocol table entry */
     struct   sockaddr_in sad;     /* structure to hold server's address */
     struct   sockaddr_in cad;     /* structure to hold client's address */
     int      sd, sd2;             /* socket descriptors */
     int      port;                /* protocol port number */
     int      alen;                /* length of address */
     pthread_t  tid;             /* variable to hold thread ID */

     pthread_mutex_init(&mut, NULL);
     memset((char  *)&sad,0,sizeof(sad)); /* clear sockaddr structure   */
     sad.sin_family = AF_INET;            /* set family to Internet     */
     sad.sin_addr.s_addr = INADDR_ANY;    /* set the local IP address */

     /* Check  command-line argument for protocol port and extract      */
     /* port number if one is specfied.  Otherwise, use the default     */
     /* port value given by constant PROTOPORT                          */
    
     if (argc > 1) {                        /* if argument specified     */
                     port = atoi (argv[1]); /* convert argument to binary*/
     } else {
                      port = PROTOPORT;     /* use default port number   */
     }
     if (port > 0)                          /* test for illegal value    */
                      sad.sin_port = htons((u_short)port);
     else {                                /* print error message and exit */
                      fprintf (stderr, "bad port number %s/n",argv[1]);
                      exit (1);
     }

     /* Map TCP transport protocol name to protocol number */
     
     if ( ((int)(ptrp = getprotobyname("tcp"))) == 0)  {
                     fprintf(stderr, "cannot map \"tcp\" to protocol number");
                     exit (1);
     }

     /* Create a socket */
     sd = socket (PF_INET, SOCK_STREAM, ptrp->p_proto);
     if (sd < 0) {
                       fprintf(stderr, "socket creation failed\n");
                       exit(1);
     }

     /* Bind a local address to the socket */
     if (bind(sd, (struct sockaddr *)&sad, sizeof (sad)) < 0) {
                        fprintf(stderr,"bind failed\n");
                        exit(1);
     }

     /* Specify a size of request queue */
     if (listen(sd, QLEN) < 0) {
                        fprintf(stderr,"listen failed\n");
                         exit(1);
     }

     alen = sizeof(cad);

     /* Main server loop - accept and handle requests */
     fprintf( stderr, "Server up and running.\n");
     while (1) {

         printf("SERVER: Waiting for contact ...\n");
         
         if (  (sd2=accept(sd, (struct sockaddr *)&cad, &alen)) < 0) {
	                      fprintf(stderr, "accept failed\n");
                              exit (1);
	 }
	 pthread_create(&tid, NULL, serverthread, (void *) sd2 );
     }
     close(sd);
return 0;
}


void * serverthread(void * parm)
{
   int tsd, tvisits;
   char     buf[100];           /* buffer for string the server sends */

   tsd = (int) parm;

   pthread_mutex_lock(&mut);
        tvisits = ++visits;
   pthread_mutex_unlock(&mut);

   sprintf(buf,"This server has been contacted %d time%s\n",
	   tvisits, tvisits==1?".":"s.");

   printf("SERVER thread: %s", buf);
   send(tsd,buf,strlen(buf),0);
   char* fs_name = "/home/rainer/Desktop/lab PAD-DP/gitStuff/mirroring/client";
   char sdbuf[LENGTH]; // Send buffer
   printf("[Server] Sending %s to the Client...", fs_name);
   FILE *fs = fopen(fs_name, "r");
   if(fs == NULL){
        fprintf(stderr, "ERROR: File %s not found on server. (errno = %d)\n", fs_name, errno);
        exit(1);
   }

	int i=0;

   bzero(sdbuf, LENGTH); 
   int fs_block_sz; 
   while((fs_block_sz = fread(sdbuf, sizeof(char), LENGTH, fs))>0){
	++i;
      if(send(tsd, sdbuf, fs_block_sz, 0) < 0){
             fprintf(stderr, "ERROR: Failed to send file %s. (errno = %d)\n", fs_name, errno);
             exit(1);
      }
      bzero(sdbuf, LENGTH);
   }
   printf("Ok sent to client! We sent  %d times the number of bytes\n",i);


	
	struct myDirectory directories[200];
	int actual, length;


	DIR* current_dir = opendir(current_path);
	char* path = (char*)malloc(strlen(current_path) * sizeof(char));
	struct stat entity_info;
	struct dirent *dir_entity;

	directories[1].name="\0";
	directories[1].path="\0";
	actual=1;length=1;
	
	char *caleaActuala;

	while(actual<=length){
		caleaActuala=(char*)malloc(sizeof(char)*(strlen(currentPath)+strlen(directories[actual].path)));

		current_dir=opendir(current_path+dir[actual]);

	while((dir_entity = readdir(current_dir)) != 0){	
		counter++;	
		strcpy(path, current_path);
		
		char* name = (char*)malloc((strlen(path) + strlen(dir_entity->d_name) + 1) * sizeof(char));
		if(path[strlen(path) - 1] != '/')
			name = strcat(path, "/");
		name = strcat(path, dir_entity->d_name);






   close(tsd);
   pthread_exit(0);
}    
