#include <cstdio>
#include <cstdlib>	//exit()
#include <cstring>	//memset()

#include <vector>
using std::vector;

#include <unistd.h>	//close()
#include <sys/socket.h>	//for socket
#include <arpa/inet.h>	//inet_pton()
#include <netinet/in.h>	//struct sockaddr

#include <pthread.h>

#define BUFFER_SIZE 1024

void HandleTCPClient(int socket_fd, int id);

struct ThreadArgs{
	int id;
	int client_socket_fd;
};

struct WarUser{
	int id;
	int skill;
	int huihe;
	int id2;	//team2

	bool ready;

	WarUser(int id) : id(id), skill(0), huihe(0), id2(-1), ready(false) { }
	void getfilename_self(char * buf)
	{
		sprintf(buf, "%d.txt", id);
	}
	void getfilename_enemy(char * buf)
	{
		sprintf(buf, "%d.txt", id2);
	}
};

pthread_mutex_t mutex_user_number;
int user_number = 0;

vector<WarUser> g_war_user;

#define MAX_USER 20
pthread_mutex_t mutex_war_user[20];


int findEnemy(int id)
{
	for (;;)
	{
		for (int i = 1; i < g_war_user.size(); i += 2)
		{
			if (i == id)
				continue;
			if (g_war_user[i].id2 == id)
				return i;
			if (g_war_user[i].ready == true)
				return i;
		}
		
	}
	
}

void * threadMain(void *arg)
{
	pthread_detach(pthread_self());

	int client_socket_fd = ((struct ThreadArgs *)arg)->client_socket_fd;
	int id = ((struct ThreadArgs *)arg)->id;

	HandleTCPClient(client_socket_fd, id);
}

void error(const char * s)
{
	puts(s);
	exit(-1);
}

int processMsg(char *input, char *output)
{
	if (strcmp(input, "quit") == 0)
		return -1;
	if (strcmp(input, "skill") == 0)
	{
		int r = rand() % 4;
		sprintf(output, "%d", r);
		return strlen(output);
	}
	if (strcmp(input, "change") == 0)
	{
		int r = rand() % 6 + 100;
		sprintf(output, "%d", r);
		return strlen(output);
	}

	if (strcmp(input, "sendfile") == 0)
	{
		strcpy(output, "ok for receive");
		return strlen(output);
	}

	if (strcmp(input, "askfile") == 0)
	{
		strcpy(output, "ok for askfile");
		return strlen(output);
	}

	strcpy(output, "default");
	return strlen(output);
}

int getFileSize(const char * strFileName)
{
	FILE * fp = fopen(strFileName, "r");
	fseek(fp, 0L, SEEK_END);
	int size = ftell(fp);
	fclose(fp);
	return size;
}

void sendFile(int socket_fd, const char *filename, int id)
{
	char buff[BUFFER_SIZE];
	int file_size = getFileSize(filename);
	sprintf(buff, "%d", file_size);
	int len = strlen(buff);
	int number_byte_send = send(socket_fd, buff, len, 0);
	if (number_byte_send < 0)
		error("send() failed");
	else if (number_byte_send != len)
		error("send number of bytes error");
	printf("send:*%s*\n", buff);

	int n = recv(socket_fd, buff, 511, 0);
	buff[n] = '\0';
	printf("receive:*%s*\n", buff);

	FILE *stream;
	if((stream = fopen(filename, "r"))==NULL)
	{
		printf("The file was not opened! \n");
		exit(1);
	}
	memset(buff, 0, sizeof(buff));

	int lengsize = 0;
	while((lengsize = fread(buff, 1, BUFFER_SIZE, stream)) > 0)
	{
		printf("lengsize = %d\n",lengsize);
		if(send(socket_fd, buff, lengsize, 0) < 0)
		{
			printf("Send File is Failed\n");
			break;
		}
		memset(buff, 0, sizeof(buff));
	}
	if(fclose(stream))
		printf("The file 'data' was not closed! \n");

	printf("send file finished\n");

}
void receiveFile(int socket_fd, const char * filename, int id)
{	
	printf("file mode start...\n");
	FILE * stream;
	if((stream = fopen(filename, "w")) == NULL)
	{
		printf("The file 'data.txt' was not opened! \n");
	}

	char buff2[BUFFER_SIZE];
	memset(buff2, 0, sizeof(buff2));


	int n = recv(socket_fd, buff2, 511, 0);
	buff2[n] = '\0';
	printf("receive:*%s*\n", buff2);
	int file_size = atoi(buff2);
	printf("file size = %d\n", file_size);
	int len = strlen(buff2);

	int number_byte_send = send(socket_fd, buff2, len, 0);
	if (number_byte_send < 0)
		error("send() failed");
	else if (number_byte_send != len)
		error("send number of bytes error");
	printf("send:*%s*\n", buff2);


	
	

	int length = 0;
	int total_recieved = 0;
	while( total_recieved < file_size)
	{
		length = recv(socket_fd, buff2, BUFFER_SIZE, 0);
		total_recieved += length;

		if(length < 0)
		{
			printf("recv Failed!\n");
			break;
		}
		int write_length = fwrite(buff2,sizeof(char),length,stream);
		if (write_length<length)
		{
			printf("File is Write Failed\n");
			break;
		}
		memset(buff2, 0, sizeof(buff2));
	}
	printf("Recieve File From Server Finished\n");
	//关闭 文件
	fclose(stream);

	g_war_user[id].ready = true;
	g_war_user[id].id2 = findEnemy(id);


}

void HandleTCPClient(int socket_fd, int id)
{	
	char buffer[512];
	char send_buffer[512];

	for (;;)
	{
		//接收客户端消息
		int n = recv(socket_fd, buffer, 511, 0);
		if (n < 0)
			error("recv() failed");
		if (n == 0)
			break;
		buffer[n] = '\0';
		printf("receive:*%s*\n", buffer);

		int len = processMsg(buffer, send_buffer);
		if (len == -1)
			break;

		

		int number_byte_send = send(socket_fd, send_buffer, len, 0);
		if (number_byte_send < 0)
			error("send() failed");
		else if (number_byte_send != len)
			error("send number of bytes error");
		printf("send:*%s*\n", send_buffer);


		if (strcmp(buffer, "sendfile") == 0)
		{
			char buf[128];
			g_war_user[id].getfilename_self(buf);
			receiveFile(socket_fd, buf, id);
		}
		if (strcmp(buffer, "askfile") == 0)
		{
			char buf[128];
			g_war_user[id].getfilename_enemy(buf);
			sendFile(socket_fd, buf, id);
		}

	}
	


	//关闭socket
	close(socket_fd);

	pthread_mutex_lock(&mutex_user_number);
	--user_number;
	pthread_mutex_unlock(&mutex_user_number);
}


int main(void)
{
	//创建一个socket
	int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fd < 0)
		error("socket() failed");

	//设置要连接的服务端地址，使用结构体addr表示
	struct sockaddr_in server_addr;
	memset(&server_addr, 0, sizeof(server_addr));
	//设置ipv4协议族
	server_addr.sin_family = AF_INET;
	//设置ip地址
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	//设置端口号
	server_addr.sin_port = htons(8000);

	//绑定端口
	if (bind(socket_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
		error("bind() error");

	//监听端口
	if (listen(socket_fd, 5) < 0)
		error("listen() error");
	printf("listening ...\n");

	for (;;)
	{
		struct sockaddr_in client_addr;	//用来保存客户端地址
		socklen_t client_addr_len = sizeof(client_addr);

		int client_socket_fd = accept(socket_fd, (struct sockaddr *) &client_addr, &client_addr_len);
		if (client_socket_fd < 0)
			error("accept() error");

		//显示客户端地址
		char client_buffer[512];
		if (inet_ntop(AF_INET, &client_addr.sin_addr.s_addr, client_buffer, sizeof(client_buffer)) != NULL)
		{
			printf("accept client : %s:%d\n", client_buffer, ntohs(client_addr.sin_port));
		}
		else
			error("client address error");

		
		WarUser user(0);
		g_war_user.push_back(user);
		
		//应答客户端
		//HandleTCPClient(client_socket_fd);
		ThreadArgs threadargs;
		threadargs.id = user_number;
		threadargs.client_socket_fd = client_socket_fd;


		++user_number;
		pthread_t threadID;
		int ret = pthread_create(&threadID, NULL, &threadMain, (&threadargs));
		if (ret != 0)
			error("create thread failed");
	}


	return 0;
}