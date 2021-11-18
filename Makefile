SERVER = server
CLIENT = client

SERVER_WIN = server_win
CLIENT_WIN = client_win

DIR_SERVER = app_server/src
DIR_CLIENT = app_client/src

IMP = dependencies/implementations
LIB = dependencies/libraries

FLGS = -lws2_32 -lwsock32

server:
	@gcc $(DIR_SERVER)/$(SERVER).c -o $(SERVER).out

server_win: $(DIR_SERVER)/$(SERVER_WIN).c
	@gcc -o $(SERVER_WIN).exe $(DIR_SERVER)/$(SERVER_WIN).c $(IMP)/*.c $(FLGS) -I $(LIB)

client:
	@gcc $(DIR_CLIENT)/$(CLIENT).c -o $(CLIENT).out

client_win: $(DIR_CLIENT)/$(CLIENT_WIN).c
	@gcc -o $(CLIENT_WIN).exe $(DIR_CLIENT)/$(CLIENT_WIN).c $(IMP)/*.c $(FLGS) -I $(LIB)