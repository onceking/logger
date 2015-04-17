#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>

void dupfd(int df, int dt){
	char buffer[1<<13];

	struct iovec iov[1];
	iov[0].iov_base = buffer;
	iov[0].iov_len = sizeof(buffer);

	struct msghdr message;
	memset(&message, 0, sizeof(message));
	message.msg_iov = iov;
	message.msg_iovlen = 1;
	message.msg_control = 0;
	message.msg_controllen = 0;

	ssize_t count = recvmsg(df, &message, 0);
	if(count==-1) {
		printf("recvmsg: %s",strerror(errno));
	} else if (message.msg_flags&MSG_TRUNC) {
		printf("datagram too large for buffer: truncated");
	} else {
		write(dt, buffer, count);
	}
}

int main(){
	int udp = socket(AF_INET, SOCK_DGRAM, 0);
	struct sockaddr_in sa;
	sa.sin_family = AF_INET;
	sa.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	sa.sin_port = htons(10514);

	bind(udp, (struct sockaddr *)&sa, sizeof(sa));
	while(1){
		dupfd(udp, STDOUT_FILENO);
	}
	return 0;
}
