#ifndef CREATE_SOCKET_CONNECTION_H
#define CREATE_SOCKET_CONNECTION_H

#define NUM_OF_SERVERS 3

void bind_to_random_port(int socket, const char *port_filename);
void connect_servers(int socket, int *server_array);
int connect_client(int client_socket);

#endif  // !CREATE_SOCKET_CONNECTION_H
