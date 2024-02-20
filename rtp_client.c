#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <errno.h>

int main(void)
{
	int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

 	struct sockaddr_in addr;
 	addr.sin_family = AF_INET;
 	addr.sin_port = htons(36464);
 	addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	/* After rtsp play option, rtp packet will send to 36464 port */
 	int ret = bind(sockfd, (struct sockaddr*)&addr, sizeof(addr));
 	if(ret) {
 	    printf("bind failed errno: %d\n", errno);
 	    return -1;
 	}

 	struct sockaddr_in cli;
 	socklen_t len = sizeof(cli);

 	printf("start listening\n");
 	while(1) {
		char buf[4096];
		int n = recvfrom(sockfd, buf, sizeof(buf), 0, (struct sockaddr*)&cli, &len);
		if (n > 0) {
			printf("recvfrom %s:%d bytes: %d\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port), n);
			/* print rtp header */
//			for (int i = 0; i < n; i++) {
//				printf("%02x ", (unsigned char)buf[i]);
//			}
//			printf("\n");
			printf("timestamp:");
			for (int i = 4; i < 8; i++) {
				printf("%02x ", (unsigned char)buf[i]);
			}
			printf("\n");
		} else {
			printf("recvfrom failed errno: %d\n", errno);
		}
	}
	close(sockfd);

	return 0;
}
