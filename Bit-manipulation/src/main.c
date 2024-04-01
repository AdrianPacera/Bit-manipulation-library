#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include "bit_handler.h"
#include <string.h>

/*
    Testing function for "combine_nibbles_to_byte()" 
    - tests done with border values, invalid inputs, test values.
*/ 
void test_combination_of_nibbles(){
    char testForBorderValues[10] = "";
    char testForInvalidValues[10] = "";
    char testForNormalValues[10] = "";
    uint8_t resultByte=0x0;

    //testing border values 
    uint8_t     lowBorderValue = 0x00;
    uint8_t     topBorderValue = 0x0F;
    uint8_t     expectedByteFromBorderValues= 0xF0;
    bool        valFromBorderValues = combine_nibbles_to_byte(lowBorderValue, topBorderValue, &resultByte);
    if((resultByte == expectedByteFromBorderValues) && (valFromBorderValues == true)){
        strcpy(testForBorderValues,"Passed");
    }
    else{
        strcpy(testForBorderValues,"Failed");
    }

    //testing invalid inputs 
    uint8_t     inValidValue1 = 0xAB;
    uint8_t     inValidValue2 = 0xCD;
    uint8_t     expectedByteFromInvalidValues = resultByte;
    bool        valFromInvalidValues = combine_nibbles_to_byte(inValidValue1, inValidValue2, &resultByte);
    if((resultByte == expectedByteFromInvalidValues) && (valFromInvalidValues == false)){
        strcpy(testForInvalidValues, "Passed");
    }
    else{
        strcpy(testForInvalidValues, "Failed");
    }

    //testing "normal values", aka values in expected format and range
    uint8_t     low_nibble = 0x0D;
    uint8_t     high_nibble = 0x08;
    uint8_t     expectedByteFromNormalValues = 0x8D;
    bool        valFromNormalNibbles = combine_nibbles_to_byte(low_nibble, high_nibble, &resultByte);
    if((resultByte == expectedByteFromNormalValues) && (valFromNormalNibbles == true)){
        strcpy(testForNormalValues,"Passed");
    }
    else{
        strcpy(testForNormalValues, "Failed");
    }

    printf("Outcome of 1st Function:\n");
    printf("Test results:\n Test1: %s \n Test2: %s \n Test3: %s\n", testForBorderValues, testForInvalidValues, testForNormalValues);
    printf("=>Combination of low and high nibbles:%X, %X is: %X \n\n", low_nibble, high_nibble, resultByte);

}

/*
    Test function for "swap_bytes_in_word()"
    - tests done with border values, invalid inputs, test values.   
*/
void test_swapping_bytes(){
    char testForBorderValues[10] = "";;
    char testForInvalidValues[10] = "";;
    char testForNormalValues[10] = "";;
    uint16_t resultByte=0x0;

    //testing border values
    uint16_t    highBorderValue = 0xFFFF;
    uint16_t    expectedSwappedBytesFromBorderValue = 0xFFFF;
    bool    valFromHighBorderValue = swap_bytes_in_word(highBorderValue, &resultByte);
    if((resultByte == expectedSwappedBytesFromBorderValue) && (valFromHighBorderValue == true)){
        strcpy(testForBorderValues, "Passed");
    }
    else{
        strcpy(testForBorderValues, "Failed");
    }
    
    //testing invalid inputs
    uint32_t    invalidValue = 0xFFFF0000;
    uint16_t    expectedSwappedBytesFromInvalidValue = 0x0;
    bool    valFromInvalidValue = swap_bytes_in_word(invalidValue, &resultByte);
    if((resultByte == expectedSwappedBytesFromInvalidValue) && (valFromInvalidValue == true)){
        strcpy(testForInvalidValues,  "Passed");
    }
    else{
        strcpy(testForInvalidValues,"Failed");
    }

    //testing "normal values", aka values in expected format and range
    uint16_t    word = 0xABCD;
    uint16_t     expectedSwappedBytesFromWord = 0xCDAB;
    bool    valFromWord = swap_bytes_in_word(word, &resultByte);
    if((resultByte == expectedSwappedBytesFromWord) && (valFromWord == true)){
        strcpy(testForNormalValues, "Passed");
    }
    else{
        strcpy(testForNormalValues, "Failed");
    }

    printf("Outcome of 2nd Function:\n");
    printf("Test results:\n Test1: %s \n Test2: %s \n Test3: %s\n", testForBorderValues, testForInvalidValues, testForNormalValues);
    printf("=>Result of swapping bytes in word:%X is: %X \n\n", word, resultByte);
}

/*
    Test function for "create_mask_for_byte()"
    - tests done with border values, invalid inputs, test values.  
*/
void test_creating_mask(){
    char testForBorderValues[10] = "";;
    char testForInvalidValues[10] = "";;
    char testForNormalValues[10] = "";;
    uint8_t resultByte=0x0;

    //testing border values
    uint8_t     sizeBorderValue = 7;
    uint8_t     shiftBorderValue = 7;
    uint8_t     expectedBorderMask = 0b10000000;
    bool     maskFromBorderValues = create_mask_for_byte (sizeBorderValue, shiftBorderValue, &resultByte);
    if((resultByte == expectedBorderMask) && (maskFromBorderValues == true)){
        strcpy(testForBorderValues , "Passed");
    }
    else{
        strcpy(testForBorderValues , "Failed");
    }

    //testing invalid values
    uint8_t     invalidSize = 8;
    uint8_t     invalidShift = 8;
    uint8_t     expectedInvalidMask = resultByte;
    bool     maskFromInvalidValues = create_mask_for_byte(invalidSize, invalidShift, &resultByte);
    if((resultByte == expectedInvalidMask) && (maskFromInvalidValues == false)){
        strcpy(testForInvalidValues , "Passed");
    }
    else{
        strcpy(testForInvalidValues , "Failed");
    }

    //testing "normal values", aka values in expected format and range
    uint8_t     size=3; 
    uint8_t     shift=1;
    uint8_t     expectedMaskFromTestValues = 0b00001110;
    bool     maskFromTestValues = create_mask_for_byte (size, shift, &resultByte);
    if((resultByte == expectedMaskFromTestValues) && (maskFromTestValues == true)){
        strcpy(testForNormalValues , "Passed");
    }
    else{
        strcpy(testForNormalValues , "Failed");
    }
    printf("Outcome of 3rd Function:\n");
    printf("Test results:\n Test1: %s \n Test2: %s \n Test3: %s\n", testForBorderValues, testForInvalidValues, testForNormalValues);
    printf("=>Mask created by provided size and shift:%X,%X is: %X \n\n", size, shift, resultByte);
}

/*
    Testing function for "apply_mask_to_byte()" 
    - tests done with invalid mode, border byte value, border mask value, test values.
*/ 
void test_of_mask_application(){
    char testForInvalidMode[10] = "";
    char testForBorderByte[10] = "";
    char testforBorderMask[10] = "";
    char testForNormalValues[10] = "";
    uint8_t resultByte=0x0;


    //testing border byte
    char        modeForBorderByteTest[] = "flip";
    uint8_t     borderByte = 0x0; 
    uint8_t     maskForBorderByteTest= 0b00110110;
    uint8_t     expectedMaskFromBorderByte = 0b00110110;
    bool     maskedByteFromBorderByte = apply_mask_to_byte(modeForBorderByteTest, borderByte, maskForBorderByteTest, &resultByte);
    if((resultByte == expectedMaskFromBorderByte) && (maskedByteFromBorderByte == true)){
        strcpy(testForBorderByte , "Passed");
    }
    else{
        strcpy(testForBorderByte , "Failed");
    }   

    //testing invalid mode
    char        invalidMode[] = "invalid";
    uint8_t     byteForInvalidMode = 0b00100011; 
    uint8_t     maskForInvalidMode = 0b00110110;
    uint8_t     expectedMaskFromInvalidMode = resultByte;
    bool     maskedByteFromInvalidInput = apply_mask_to_byte(invalidMode, byteForInvalidMode, maskForInvalidMode, &resultByte);
    if((resultByte == expectedMaskFromInvalidMode) && (maskedByteFromInvalidInput == false)){
        strcpy(testForInvalidMode , "Passed");
    }
    else{
        strcpy(testForInvalidMode , "Failed");
    }

    //testing border mask value
    char        modeForBorderMaskTest[] = "clear";
    uint8_t     byteForBorderMaskTest = 0b00100011;  
    uint8_t     borderMask = 0x0;   
    uint8_t     expectedMaskFromBorderMask = 0x0; 
    bool     maskedByteFromborderMask = apply_mask_to_byte(modeForBorderMaskTest, byteForBorderMaskTest, borderMask, &resultByte);
    if((resultByte == expectedMaskFromBorderMask) && (maskedByteFromborderMask == true)){
        strcpy(testforBorderMask , "Passed");
    }
    else{
        strcpy(testforBorderMask , "Failed");
    } 

    //testing "normal values", aka values in expected format and range
    char        mode[] = "set";
    uint8_t     byte = 0b00100011; 
    uint8_t     mask = 0b00110110;
    uint8_t     expectedMaskFromTestValues = 0b00110111; 
    bool     maskedByteFromTestValues = apply_mask_to_byte(mode, byte, mask, &resultByte);
    if((resultByte == expectedMaskFromTestValues) && (maskedByteFromTestValues == true)){
        strcpy(testForNormalValues , "Passed");
    }
    else{
        strcpy(testForNormalValues , "Failed");
    } 
    printf("Outcome of 4th Function:\n");
    printf("Test results:\n Test1: %s \n Test2: %s \n Test3: %s \n Test4: %s\n", testForBorderByte, testForInvalidMode, testforBorderMask, testForNormalValues);
    printf("=>Mask applied with mode:%s to byte:%X is: %X\n\n", mode, byte, resultByte);
}

/*
    Testing function for "test_bit_in_byte()" 
    - tests done with border values, invalid values, test values / normal values.    
*/
void test_if_bit_is_set(){
    char testForBorderValues[10] = "";
    char testForInvalidValues[10] = "";
    char testForNormalValues[10] = "";
    
    
    //testing border values
    uint8_t     byteForBorderTest = 0b11111111;
    uint8_t     positionForBorderTest = 7;
    uint8_t     expectedValuesFromBorderValues = 1;
    uint8_t     valueFromBorderValues = test_bit_in_byte(byteForBorderTest, positionForBorderTest);
    if(valueFromBorderValues == expectedValuesFromBorderValues){
        strcpy(testForBorderValues , "Passed");
    }
    else{
        strcpy(testForBorderValues , "Failed");
    }

    //testing invalid values
    uint8_t     byteForInvalidTest= 0b00100011;
    uint8_t     positionForInvalidTest = 9;
    uint8_t     expectedValuesFromInvalidValues = 0;
    uint8_t     valueFromInvalidValues = test_bit_in_byte(byteForInvalidTest, positionForInvalidTest);
    if(valueFromInvalidValues == expectedValuesFromInvalidValues){
        strcpy(testForInvalidValues , "Passed");
    }
    else{
        strcpy(testForInvalidValues , "Failed");
    }

    //testing "normal values", aka values in expected format and range
    uint8_t     byte = 0b00100011;
    uint8_t     position = 1;
    uint8_t     expectedValuesFromTestValues = 1;
    uint8_t     valueFromTestValues = test_bit_in_byte(byte, position);
    if(valueFromTestValues == expectedValuesFromTestValues){
        strcpy(testForNormalValues , "Passed");
    }
    else{
        strcpy(testForNormalValues , "Failed");
    }

    printf("Outcome of 5th Function:\n");
    printf("Test results:\n Test1: %s \n Test2: %s \n Test3: %s\n", testForBorderValues, testForInvalidValues, testForNormalValues);
    printf("=>The bit in byte:%X on position:%d is: %X \n\n", byte, position, valueFromTestValues);    
}

/*
    Testing function for "count_ones_in_byte()" 
    - tests done with border values, test values / normal values.   
*/
void test_num_of_sets(){
    char testForBorderValueSet[10] = "";
    char testForBorderValueClear[10] = "";
    char testForNormalValues[10] = "";

    //testing for border case of sets
    uint8_t     byteForBorderTestOfSets = 0b11111111;
    uint8_t     expectedNumberOfSets = 8;
    uint8_t     valueFromBorderTestOfSets = count_ones_in_byte(byteForBorderTestOfSets);
    if(valueFromBorderTestOfSets == expectedNumberOfSets){
        strcpy(testForBorderValueSet , "Passed");
    }
    else{
        strcpy(testForBorderValueSet , "Failed");
    }

    //testing for border case of clears
    uint8_t     byteForBorderTestOfClears = 0x0;
    uint8_t     expectedNumberOfClears = 0;
    uint8_t     valueFromBorderTestOfClears = count_ones_in_byte(byteForBorderTestOfClears); 
    if(valueFromBorderTestOfClears == expectedNumberOfClears){
        strcpy(testForBorderValueClear , "Passed");
    }
    else{
        strcpy(testForBorderValueClear , "Failed");
    }

    //testing "normal values", aka values in expected format and range    
    uint8_t     byte = 0b01101010;
    uint8_t     expectedSets = 4;
    uint8_t     valueFromTestValues = count_ones_in_byte(byte); 
    if(valueFromTestValues == expectedSets){
        strcpy(testForNormalValues , "Passed");
    }
    else{
        strcpy(testForNormalValues , "Failed");
    }

    printf("Outcome of 6th Function:\n");
    printf("Test results:\n Test1: %s \n Test2: %s \n Test3: %s\n", testForBorderValueSet, testForBorderValueClear, testForNormalValues);
    printf("=>The number of sets in byte:%X is: %X \n\n", byte, valueFromTestValues);
}

/*
    Testing function for "swap_bits_in_byte()" 
    - tests done with border values, test values / normal values.   
*/
void test_swapping_of_even_and_odd_bits(){
    char testForHighestBorderValue[10] = "";
    char testForLowestBorderValue[10] = "";
    char testForNormalValues[10] = "";
    uint8_t resultByte=0x0;

    //testing with highest border value
    uint8_t     byteForHighestBorderTest = 0b11111111;
    uint8_t     expectedByteFromHighestBorderTest = 0b11111111;
    bool     valueOfByteFromHighestBorderTest = swap_bits_in_byte(byteForHighestBorderTest, &resultByte);
    if((resultByte == expectedByteFromHighestBorderTest) && (valueOfByteFromHighestBorderTest == true)){
        strcpy(testForHighestBorderValue , "Passed");
    }
    else{
        strcpy(testForHighestBorderValue , "Failed");
    } 

    //testing with lowest border value
    uint8_t     byteForLowestBorderTest = 0b00000000;
    uint8_t     expectedByteFromLowestBorderTest = 0b00000000;
    uint8_t     valueOfByteFromLowestBorderTest = swap_bits_in_byte(byteForLowestBorderTest, &resultByte);
    if((resultByte == expectedByteFromLowestBorderTest) && (valueOfByteFromLowestBorderTest == true)){
        strcpy(testForLowestBorderValue , "Passed");
    }
    else{
        strcpy(testForLowestBorderValue , "Failed");
    }

    //testing "normal values", aka values in expected format and range        
    uint8_t     byte = 0b01101011;
    uint8_t     expectedByte = 0b10010111;
    uint8_t     valueOfByte = swap_bits_in_byte(byte, &resultByte);
    if((resultByte == expectedByte) && (valueOfByte == true)){
        strcpy(testForNormalValues , "Passed");
    }
    else{
        strcpy(testForNormalValues , "Failed");
    }

    printf("Outcome of 7th Function:\n");
    printf("Test results:\n Test1: %s \n Test2: %s \n Test3: %s\n", testForHighestBorderValue, testForLowestBorderValue, testForNormalValues);
    printf("=>Result of swapping even with odd bits in byte:%X is: %X \n", byte, resultByte);
}

int main()
{
    //calling test functions
    printf("-------------------------------Assignment 1---------------------------------\n");
    test_combination_of_nibbles();
    test_swapping_bytes();
    test_creating_mask();
    test_of_mask_application();
    test_if_bit_is_set();
    test_num_of_sets();
    test_swapping_of_even_and_odd_bits();
    printf("----------------------------------------------------------------------------\n");
    
    return 0;
}