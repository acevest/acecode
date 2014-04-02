/*
 *--------------------------------------------------------------------------
 *   File Name:	client.c
 * 
 *      Author:	Zhao Yanbai [zhaoyanbai@126.com]
 * 			Fri Jun 10 15:06:48 2011
 * 
 * Description:	none
 * 
 *--------------------------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <openssl/ssl.h>
#include <openssl/err.h>


int main() {

	int fd, ret;
	struct sockaddr_in addr;
	SSL	*ssl;
	SSL_CTX *ctx;

	if((fd=socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("socket\n");
		exit(EXIT_FAILURE);
	}

	memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_port	= htons(4321);
	inet_pton(AF_INET, "192.168.101.112", &addr.sin_addr.s_addr);
	if((ret=connect(fd, (struct sockaddr*)&addr, sizeof(addr))) == -1) {
		perror("connect");
		exit(EXIT_FAILURE);
	}

	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	ctx = SSL_CTX_new(SSLv23_client_method());
	if(ctx == NULL) {
		ERR_print_errors_fp(stdout);
		exit(EXIT_FAILURE);
	}

	ssl = SSL_new(ctx);
	if(ssl == NULL) {
		ERR_print_errors_fp(stdout);
		exit(EXIT_FAILURE);
	}
	SSL_set_fd(ssl, fd);
	if(SSL_connect(ssl) == -1) {
		ERR_print_errors_fp(stdout);
		exit(EXIT_FAILURE);
	}

	char *str = "baby, this is the message from client...\n";
	int len  = SSL_write(ssl, str, strlen(str));
	if(len <= 0) {
		printf("send msg failed...\n");
		exit(EXIT_FAILURE);
	}


	SSL_shutdown(ssl);
	SSL_free(ssl);
	close(fd);
	SSL_CTX_free(ctx);

	return 0;
}
