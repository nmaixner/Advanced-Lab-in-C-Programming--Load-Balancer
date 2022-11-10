#include <arpa/inet.h>  //inet_addr
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <time.h>
#include <unistd.h>  //write

#define BUFFER_SIZE 1024 + 1  // added 1 for null character on maximum read
#define END_OF_MESSAGE "\r\n\r\n"

char *receive_message(int from_socket, int terminator_count);
bool was_terminated(const char *message, const char *terminator, int terminator_count);

bool was_terminated(const char *message, const char *terminator, int terminator_count)
{

  int count = 0;
  int i = 0;
  for (i = 0; i < terminator_count; i++) {
    char *is_appeared = strstr(message, terminator);
    if (NULL == is_appeared) {
      break;
    } else {
      count++;
      message = is_appeared + strlen(terminator);
    }
  }
  return (count >= terminator_count);
}

char *receive_message(int from_socket, int terminator_count)
{
  int bytes_received = 0;
  char *received_message = (char *)malloc(BUFFER_SIZE);

  while (true) {

    bytes_received += recv(from_socket, received_message + bytes_received, BUFFER_SIZE - 1, 0);
    (*(received_message + bytes_received)) = '\0';

    if (was_terminated(received_message, END_OF_MESSAGE, terminator_count)) {

      return received_message;
    } else {
      received_message = (char *)realloc(received_message, bytes_received + BUFFER_SIZE);
    }
  }
}

int receive_and_send_message(int socket_to_receive, int socket_to_send, int terminator_count)
{
  char *received_message = receive_message(socket_to_receive, terminator_count);
  send(socket_to_send, received_message, strlen(received_message), 0);
  free(received_message);
  return 0;
}