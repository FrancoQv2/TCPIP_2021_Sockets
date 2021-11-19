SERVER = server
CLIENT = client

SERVER_LINUX = server_linux
CLIENT_LINUX = client_linux

DIR_SERVER = app_server/src
DIR_CLIENT = app_client/src

FLGS = -lws2_32 -lwsock32

server: $(DIR_SERVER)/$(SERVER).c
	@gcc -o $(SERVER).exe $(DIR_SERVER)/$(SERVER).c $(FLGS)

client: $(DIR_CLIENT)/$(CLIENT).c
	@gcc -o $(CLIENT).exe $(DIR_CLIENT)/$(CLIENT).c $(FLGS)

server_linux:
	@gcc $(DIR_SERVER)/$(SERVER_LINUX).c -o $(SERVER_LINUX).out

client_linux:
	@gcc $(DIR_CLIENT)/$(CLIENT_LINUX).c -o $(CLIENT_LINUX).out