#include <stdio.h>
#include <stdlib.h>

void write_port_to_file(const char *file_name, const int port_num)
{
  FILE *port_file_pointer = NULL;
  port_file_pointer = fopen(file_name, "w");
  if (port_file_pointer == NULL) {
    printf("Can't open file!!");
    return;
  }
  fprintf(port_file_pointer, "%d\n", port_num);
  fclose(port_file_pointer);
  return;
}
