#include   <stdio.h>
#include   <stdlib.h>
#include   <unistd.h>
#include   <string.h>
#include   <ctype.h>
#include   <sys/types.h>
#include   <sys/socket.h>
#include   <netinet/in.h>
#define MAXLENGTH 80
#define SERVER_PORT 1313

int main () {
	int sockfd;
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);
	server.sin_addr.s_addr = htonl(INADDR_ANY);
	int len;
	char buf[MAXLENGTH];

	if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
		perror("chiamata alla system call socket fallita");
		exit(1);
	}

	/* connessione al server */
	if (connect(sockfd, (struct sockaddr *) &server, sizeof server) == -1) {
		perror("connessione al server fallita");
		exit(2);
	}

	/* ricezione e stampa a video del messaggio di benvenuto del server */
	if (recv(sockfd, buf, 27, 0) > 0) {
		printf("%s", buf);
	} else {
		perror("Connessione al server interrotta");
		exit(3);
	}

	printf("\nInvio al server un pathname\n");
	//pathnname da inviare
	//NB: inizializzare len con grandezza stringa pathname
	/* invio e ricezione della stringa */
	if (send(sockfd, buf, len, 0) == -1) {
		perror("Errore nell'invio della stringa al server");
		exit(4);
	}
	
	//Ricezione risposta
	if (recv(sockfd, buf, len, 0) > 0) {
      printf("Ho ricevuto la risposta: %s\n", buf);
      //stampo a video i vari dati ricevuti
	} else {
		perror("Connessione al server interrotta");
		exit(3);
	}
	
	//chiudo la connessione con il server
	if (send(sockfd, "+FINE+", 6, 0) == -1) {
		perror("Errore nell'invio della stringa al server");
		exit(4);
	}
	

	/* chiusura della connessione */
	close(sockfd);
	exit(0);
}
