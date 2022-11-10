#include <arpa/inet.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>

#include "create_socket_connection.h"
#include "handle_data_transport.h"

#define SERVER_PORT_FILE "server_port"
#define BROWSER_PORT_FILE "http_port"
#define NUM_OF_CLIENTS 1

int main()
{
  int server_socket, browser_socket;
  int accepted_browser_socket;
  int servers_sockets_array[NUM_OF_SERVERS];
  time_t t;

  srand((unsigned)time(&t));
  server_socket = socket(AF_INET, SOCK_STREAM, 0);
  browser_socket = socket(AF_INET, SOCK_STREAM, 0);
  bind_to_random_port(server_socket, SERVER_PORT_FILE);
  bind_to_random_port(browser_socket, BROWSER_PORT_FILE);

  listen(server_socket, NUM_OF_SERVERS);
  listen(browser_socket, NUM_OF_CLIENTS);

  connect_servers(server_socket, servers_sockets_array);

  int servers_turn = 0;
  while (true) {
    accepted_browser_socket = connect_client(browser_socket);
    servers_turn = servers_turn % NUM_OF_SERVERS;
    receive_and_send_message(accepted_browser_socket, servers_sockets_array[servers_turn], 1);
    receive_and_send_message(servers_sockets_array[servers_turn], accepted_browser_socket, 2);

    servers_turn++;
  }

  return 0;
}
