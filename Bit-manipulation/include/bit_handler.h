#ifndef BIT_HANDLER_H
#define BIT_HANDLER_H
#include <stdbool.h>
#include <stdint.h>

//Declaration of functions used for bit handling
bool        combine_nibbles_to_byte(uint8_t, uint8_t, uint8_t*);
bool        swap_bytes_in_word(uint16_t, uint16_t*);
bool        create_mask_for_byte (uint8_t, uint8_t, uint8_t*);
bool        apply_mask_to_byte(char[],uint8_t, uint8_t, uint8_t*);
uint8_t     test_bit_in_byte(uint8_t, uint8_t);
uint8_t     count_ones_in_byte(uint8_t);
bool        swap_bits_in_byte(uint8_t, uint8_t*);

#endif