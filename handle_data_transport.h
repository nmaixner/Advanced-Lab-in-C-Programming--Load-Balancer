#ifndef HANDLE_DATA_TRANSPORT_H
#define HANDLE_DATA_TRANSPORT_H

int receive_and_send_message(int socket_to_receive, int socket_to_send, int terminator_count);

#endif  // !HANDLE_DATA_TRANSPORT_H
