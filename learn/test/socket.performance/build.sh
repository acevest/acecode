gcc server.c -g -I. -o s
gcc client.c -g -I. -lpthread -o c
gcc udp_server.c -g -I. -o ds
gcc udp_client.c -g -I. -lpthread -o dc

