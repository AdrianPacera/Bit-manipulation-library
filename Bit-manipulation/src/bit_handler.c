#include "bit_handler.h"
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

/*
    Function desciption:

    -Function responsible for combining 2 nibbles to one combined nibble. 
     The high nibble gets shifted by size of half byte (nibble) to left and compared with low nibble.
     The result is stored into value "resultByte". 
*/
bool combine_nibbles_to_byte(uint8_t low_nibble, uint8_t high_nibble,uint8_t* resultByte){
    uint8_t byte=0x0;

    if((low_nibble >= 16) && (high_nibble >= 16) && (resultByte == NULL)){
        return false;
    }
    byte = high_nibble << 4 | low_nibble;
    *resultByte = byte;
    return true;
}

/*
    Function description:

    -Function is responsible for switching 2 bytes in 16 bit "word".
     Second byte of "word" gets first shifted to position of first byte and saved to empty 16 bit return value called "switchedBytes".
     Afterward, first byte of "word" gets shifted to the position of second byte and gets saved to "switchedBytes" by OR comparison.
*/
bool swap_bytes_in_word(uint16_t word, uint16_t *resultByte){
    uint16_t switchedBytes = 0x0;
    
    if(resultByte != NULL){
        switchedBytes = word<<8 ;
        switchedBytes = word>>8 | switchedBytes;
        
        *resultByte = switchedBytes;
        return true;
    }
    return false;
}

/* 
    Function description:

    -Function is responsible for creating a bit mask of the given size and shift.
     Mask is created by setting the least significant "size" bits to 1 and then shifting the result left by "shift" bits.

    -Loop:
     Iteration of increment in range of provided "size". The for loop adds the amount of ones into mask based of the "size" parameter.

     After the addition of sufficient amount of sets to mask, the mask is shifted to provided "position".
*/
bool create_mask_for_byte (uint8_t size, uint8_t shift,uint8_t* resultByte){
    uint8_t mask = 0x0;
    uint8_t helpMask = 0x01;

    if((size <= 7) && (shift<= 7) && (resultByte != NULL)){
        for(int increment=0; increment<size; increment++){
            mask = helpMask << increment | mask; 
        }

        *resultByte = mask << shift;

        return true;
    }

    return false;
}

/*
    Function description:

    -Function is responsible for applying a type of mask to provide byte based off the provided mode and mask.

    -If conditionals:
     Mode "set", sets the bits to high in byte based of bits which are high in mask.

     Mode "clear", clears the the bits in byte based of bits which are high in mask.

     Mode "flip", inverts the values of bits in byte based of bits which are high in mask.
*/
bool apply_mask_to_byte(char mode[],uint8_t byte, uint8_t mask, uint8_t* resultByte){
    uint8_t masked_byte = 0x0;

    if((resultByte != NULL)){ //test for array as well

        if(strcmp(mode,"set") == 0){
            masked_byte = byte | mask;
            *resultByte = masked_byte;
            return true;
        }
        else if(strcmp(mode,"clear")==0){
            masked_byte = (byte & mask) & ~mask;
            *resultByte = masked_byte;
            return true;
        }
        else if(strcmp(mode,"flip")==0){
            masked_byte = (byte ^ mask) & mask;
            *resultByte = masked_byte;
            return true;
        }
        
    }

    return false;
}

/* 
    Function description:

    -Function is responsible for determining whether a bit in provided "byte" on provided "position" is set or clear.
     The byte is first shifted to right by provided position. A byte "testByte" is copy of shifted provided byte which is set
     on first position.  

    -If conditional:
     If the shifted byte is the same as a copy of shifted byte with set first bit to 1, function returns 1, since the bit on the 
     provided position 1. Otherwise the function returns 0 as the bit on shifted position is different from 1.
*/
uint8_t test_bit_in_byte(uint8_t byte, uint8_t position){
    uint8_t testByte = 0x0;

    if((position <= 7) ){
        byte = byte >> position;
        testByte = 0x01 | byte;

        if(byte == testByte){
            return 1;
        }
    }
    return 0;
    
}

/* 
    Function description:

    -Function is responsible for counting the amount of sets in provided byte.

    -For loop:
     Iteration of position in range from 0-7 (position of each bit), for each iteration function
     "test_bit_in_byte()" is called to test whether the bit on iterrated position in provided byte 
     is set or clear. If the bit on iterrated position in provided byte is set, local variable "countOfSets" increments. 
     The function returns the amount of sets in one byte.
    
*/
uint8_t count_ones_in_byte(uint8_t byte){    
    int countOfSets = 0x0;

    for(int position=7; position>=0; position--){
        bool bitValue = test_bit_in_byte(byte, position);

        if(bitValue == 1){
            countOfSets++;
        }
    }

    return countOfSets;
}

/*
    Function description: 

    -Function responsible for swapping even bits with odd bits in given byte
     by iterating over each bit in the input byte. 

    -Loop:
     The iterated bit gets first shifted to the first bit index, then to the last bit index in order to isolate the iterated bit. 
     The isolated bit is then shifted to the belonging position by desired position. If statement decides whether the bit gets shifted
     by even or odd position. When the isolated bit is in the correct position, it gets "added" to the return value called "swappedBits"
     by comparing the isolated bit with "swappedBits". 

*/
bool swap_bits_in_byte(uint8_t byte,uint8_t* resultByte){
    uint8_t swappedBits = 0x0;
    uint8_t Bit;
    
    if(resultByte != NULL){
        int firstBitPosition = 7;
        int desiredEvenPosition = 6;
        int desiredOddPosition = 7;

        
        for(int bitIndex = 0; bitIndex < 8; bitIndex++){
            if(bitIndex%2 == 0){    
                Bit = byte << bitIndex;                         //first step for isolating interated bit -> shifting the bit to 1st position
                Bit = Bit >> firstBitPosition;                  //second step for isolating interated bit -> shifitng the bit to the last position       
                Bit = Bit << desiredEvenPosition;               //shifting the bit to position where it belongs
                swappedBits = swappedBits | Bit;                //saving the bit into bit which holds the swapped bits
                desiredEvenPosition = desiredEvenPosition-2;    //decrementing shifting value for even positions
            }
            else{
                Bit = byte << bitIndex;                         //first step for isolating interated bit -> shifting the bit to 1st position
                Bit = Bit >> firstBitPosition;                  //second step for isolating interated bit -> shifitng the bit to the last position    
                Bit = Bit << desiredOddPosition;                //shifting the bit to position where it belongs
                swappedBits = swappedBits | Bit;                //saving the bit into bit which holds the swapped bits
                desiredOddPosition = desiredOddPosition-2;      //decrementing shifting value for odd positions
            }
        }

        *resultByte = swappedBits;
        return true;
    }

    return false;
}