#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <signal.h>
#include <ctype.h>          
#include <arpa/inet.h>
#include <netdb.h>

#define LENGTH 512 


void error(const char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
    /* Variable Definition */
    int sockfd; 
    int nsockfd;
    char revbuf[LENGTH]; 
    struct sockaddr_in remote_addr;


    /* Get the Socket file descriptor */
    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to obtain Socket Descriptor! (errno = %d)\n",errno);
        exit(1);
    }



    /* Fill the socket address struct */
    remote_addr.sin_family = AF_INET; 
    remote_addr.sin_port = htons(atoi(argv[2])); 
    inet_pton(AF_INET, argv[1], &remote_addr.sin_addr); 
    bzero(&(remote_addr.sin_zero), 8);

    /* Try to connect the remote */
    if (connect(sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1)
    {
        fprintf(stderr, "ERROR: Failed to connect to the host! (errno = %d)\n",errno);
        exit(1);
    }
    else 
        printf("[Client] Connected to server at port %d...ok!\n", atoi(argv[2]));

    

    /* Receive File from Server */
    printf("[Client] Receiveing file from Server and saving it as final.txt...");
    char* fr_name = "/home/rainer/Desktop/lab PAD-DP/gitStuff/ccc";
    FILE *fr = fopen(fr_name, "w");
    if(fr == NULL)
        printf("File %s Cannot be opened.\n", fr_name);
    else
    {	int fr_block_sz = recv(sockfd, revbuf, LENGTH, 0);
	if(fr_block_sz<=0)
		exit(1);
	fwrite(revbuf, sizeof(char), fr_block_sz, fr);
	
	
	int i=0;
        bzero(revbuf, LENGTH); 
        fr_block_sz = 0;
        while((fr_block_sz = recv(sockfd, revbuf, LENGTH, 0)) > 0)
        {
            int write_sz = fwrite(revbuf, sizeof(char), fr_block_sz, fr);
            if(write_sz < fr_block_sz)
            {
                error("File write failed.\n");
            }
            bzero(revbuf, LENGTH);
            if (fr_block_sz == 0 || fr_block_sz != 512) 
            {
                break;
            }
        }
        if(fr_block_sz < 0)
        {
            if (errno == EAGAIN)
            {
                printf("recv() timed out.\n");
            }
            else
            {
                fprintf(stderr, "recv() failed due to errno = %d\n", errno);
            }
        }
        printf("Ok received from server!\n");
        fclose(fr);
    }
    close (sockfd);
    printf("[Client] Connection lost.\n");
    return (0);
}
