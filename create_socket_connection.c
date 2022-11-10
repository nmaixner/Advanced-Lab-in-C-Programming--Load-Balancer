#include "create_socket_connection.h"

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#include <string.h>
#include <time.h>

#include "print_to_file.h"

#define CONNECT_TO_IP "127.0.0.1"
#define LOW_PORT 1024
#define HIGH_PORT 64000

int get_random_num();

int get_random_num()
{
  int rand_number;
  rand_number = (rand() % (HIGH_PORT - LOW_PORT + 1)) + LOW_PORT;
  return rand_number;
}

void bind_to_random_port(int socket, const char *port_filename)
{
  int port_num = -1;
  int bind_unsuccessful = 1;
  struct sockaddr_in socket_address_struct;
  socket_address_struct.sin_family = AF_INET;
  socket_address_struct.sin_addr.s_addr = inet_addr(CONNECT_TO_IP);

  while (bind_unsuccessful) {
    port_num = get_random_num();
    socket_address_struct.sin_port = htons(port_num);
    bind_unsuccessful = bind(socket, (struct sockaddr *)&socket_address_struct, sizeof(socket_address_struct));
  }
  write_port_to_file(port_filename, port_num);
}

void connect_servers(int socket, int *servers_sockets_array)
{
  int server_num;
  for (server_num = 0; server_num < NUM_OF_SERVERS; server_num++) {
    servers_sockets_array[server_num] = accept(socket, NULL, NULL);
  }
  return;
}

int connect_client(int client_socket)
{
  int connected_client_socket;
  connected_client_socket = accept(client_socket, NULL, NULL);
  return connected_client_socket;
}