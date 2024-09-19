#include "devices/input.h"
#include <debug.h>
#include "devices/intq.h"
#include "devices/serial.h"

/* Stores keys from the keyboard and serial port. */
static struct intq buffer;

/* Initializes the input buffer. */
void
input_init (void) 
{
  intq_init (&buffer);
}

/* Adds a key to the input buffer.
   Interrupts must be off and the buffer must not be full. */
void
input_putc (uint8_t key) 
{
  ASSERT (intr_get_level () == INTR_OFF);
  ASSERT (!intq_full (&buffer));

  intq_putc (&buffer, key);
  serial_notify ();
}

/* Retrieves a key from the input buffer.
   If the buffer is empty, waits for a key to be pressed. */
uint8_t
input_getc (void) 
{
  enum intr_level old_level;
  uint8_t key;

  old_level = intr_disable ();
  key = intq_getc (&buffer);
  serial_notify ();
  intr_set_level (old_level);
  
  return key;
}

/* Returns true if the input buffer is full,
   false otherwise.
   Interrupts must be off. */
bool
input_full (void) 
{
  ASSERT (intr_get_level () == INTR_OFF);
  return intq_full (&buffer);
}

void input_getline(char *buffer, size_t size) {
  size_t i = 0;
  while (i < size - 1) {
    char c = input_getc();
    if (c == '\r' || c == '\n') {
      buffer[i] = '\0';
      printf("\n");
      return;
    } else {
      buffer[i++] = c;
      printf("%c", c);
    }
  }
  buffer[i] = '\0';
}