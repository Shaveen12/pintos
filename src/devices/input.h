#ifndef DEVICES_INPUT_H
#define DEVICES_INPUT_H

#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

void input_init (void);
void input_putc (uint8_t);
uint8_t input_getc (void);
bool input_full (void);
void input_getline(char *buffer, size_t size);

#endif /* devices/input.h */
