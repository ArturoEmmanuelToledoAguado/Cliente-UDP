/*Cliente UDP  que envia cuatro valores enteros*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8081
#define BUFFER 1024

int main()
{
	int sock, len, n, n1;
	int res = 0;
	struct sockaddr_in server, cli;
	char buffer[BUFFER];
	
	//Creacion del descriptor del socket
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("Fallo en la creacion del socket");
		exit(EXIT_FAILURE);
	}
	//Ponemos a cero la región de memoria correspondientes al servidor y al cliente.
	bzero(&server,sizeof(server));
	//Llenando la información del sevidor
	server.sin_family = AF_INET;//Protocolo (IPv4)
	server.sin_port = htons(PORT);//Puerto
	
	while(res < 500)
	{
		printf("Ingrese el primer numero: ");
		fgets(buffer,BUFFER,stdin);
		n = sendto(sock,buffer,strlen(buffer),0,&server,sizeof(server));
		if (n < 0)
			perror("Error en Sendto 1");
		printf("Ingrese el segundo numero: ");
		fgets(buffer,BUFFER,stdin);
		n = sendto(sock,buffer,strlen(buffer),0,&server,sizeof(server));
		if (n < 0)
			perror("Error en Sendto 2");
		printf("Ingrese el tercer numero: ");
		fgets(buffer,BUFFER,stdin);
		n = sendto(sock,buffer,strlen(buffer),0,&server,sizeof(server));
		if (n < 0)
			perror("Error en Sendto 3");
		printf("Ingrese el cuarto numero: ");
		fgets(buffer,BUFFER,stdin);
		n = sendto(sock,buffer,strlen(buffer),0,&server,sizeof(server));
		if (n < 0)
			perror("Error en Sendto 4");
		//Recibimos el mensaje
		n = recvfrom(sock,buffer,BUFFER,0,&cli, &len);
		if (n < 0)
			perror("Error en recvfrom mensaje");
		printf("%s\n\n",buffer);
		fflush(stdin);
		//Recibimos el dato
		n1 = recvfrom(sock,buffer,BUFFER,0,&cli, &len);
		if (n<0)
			perror("Error en recvfrom dato");
		fflush(stdin);
		res = (int)strtol(buffer,NULL,10);//Convertimos el string a int
		/*fflush(stdin);
		printf("%d\n\n",res);*/
	}
}
