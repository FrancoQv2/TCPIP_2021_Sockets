#server: 
#	@gcc servidor.c -o servidor.out

#client: 
#	@gcc cliente.c -o cliente.out

tcp:
	@gcc servidor.c -o servidor.out

udp:
	@gcc servidor_udp.c -o servidor_udp.out

udp_ej:
	@gcc ejemplos/udp_servidor.c -o ejemplos/udp_servidor.out

run_ej:
	@./ejemplos/udp_servidor.out 2500