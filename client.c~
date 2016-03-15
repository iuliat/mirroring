#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>


#define SERVER_ADDRESS "192.168.1.135"
#define SERVER_PORT 2222
 
struct file_descriptor {
	char *file_path;
	char *last_date_modified;
	int isDirectory;
}; 
 

void set_file_descriptor(struct file_descriptor *des, char *buf){
	char *b = &buf;
	char *token;
	
	token = strtok(b, ";");
	int counter = 0;
	while( token != NULL ) 
    {
    	switch(counter){
    		case 0:
    			des->file_path = token;
    			break;
    		case 1:
    			des->last_date_modified = token;
    			break;
    		case 2:
    			des->isDirectory = atoi(token);
    			break;
    		default:
    			break;	
		}    
		counter++;
    	token = strtok(NULL, ";");
    }
	
}
 
int set_addr(struct sockaddr_in *addr, 
		char *name,
		u_int32_t inaddr, 
		short sin_port){
	struct hostent *h ;
	memset((void *)addr, 0, sizeof(*addr));
	addr->sin_family = AF_INET;

	if (name != NULL){
		h = gethostbyname(name);
		if(h == NULL)
			return -1;
		addr->sin_addr.s_addr =
			*(u_int32_t *)h->h_addr_list[0];
	}else
		addr->sin_addr.s_addr = htonl(inaddr);
	addr->sin_addr.s_addr = htons(sin_port);
	return 0;
}

int stream_read(int sockfd, char *buf, int len){
	int nread;
	int remaining = len;
	
	while(remaining > 0){
		if((nread = read(sockfd, buf, remaining))
			== -1)
			return -1;
		if(nread == 0)
			break;
		remaining -= nread;
		buf += nread;
	}
	return len-remaining;
}

int stream_write(int sockfd, char *buf, int len){
	int nwr;
	int remaining = len;

	while(remaining > 0){
		if((nwr = write(sockfd, buf, remaining))
			== -1)
			return -1;
		remaining -= nwr;
		buf += nwr;
	}
	return len - remaining;
}


int main(int argc, char *argv[]) {
	int fd, sockfd;
	char buf[1024] ;
	struct sockaddr_in client_addr, server_addr;
	int nread;
	
	struct file_descriptor file_des;
	
	/*if (argc != 2) {
		printf("Folosire : %s <f i s i e r >\n" , argv[0]);
		exit(1);
	}*/

	//fd = open(argv[1], O_RDONLY);
	sockfd = socket(PF_INET, SOCK_STREAM, 0);
	set_addr( &client_addr , NULL, INADDR_ANY, 0);
	bind(sockfd, (struct sock_addr *)&client_addr,
		sizeof( client_addr));
	set_addr(&server_addr, SERVER_ADDRESS, 0, SERVER_PORT);
	connect( sockfd , (struct sock_addr *)&server_addr, sizeof(server_addr));
	
	//read the file descriptor comming from server
	
	if((nread = stream_read(sockfd, (void *)buf, 1024)) == -1){
		printf("error reading file descriptor");
		exit(1);
	}
	printf("%s", buf);
	set_file_descriptor(&file_des, buf);
	
	//decide if you want the file or not
	
	//treat different depending it is file or directory
	if(file_des.isDirectory == 1){
		mkdir(file_des.file_path, S_IRUSR | S_IWUSR | S_IXUSR);
	}
	else{
		int update_needed = 0;
		struct stat st;
		int status = stat(file_des.file_path, &st);
		
		if(status == 0){
			//file exists
			//check if it needs update 
		}else{
			//file does not exist
			update_needed = 1;
		}
		
		if(update_needed == 1){
			//ask file from server
		}
	}
	
	/* t r i m i t e f i s i e r u l */
	/*while ( 0 < ( nread = read( fd, (void *)buf ,1024))) {
		stream_write( sockfd, (void *)buf, nread);
	}
	
	if ( nread < 0 ) {
		printf("Eroare la citirea din fisier \n" ) ;
		exit(1);
	}

	close(fd);*/
	close(sockfd);
	printf("Fisierul a fost trimis cu succes \n") ;
	exit(0);
}
