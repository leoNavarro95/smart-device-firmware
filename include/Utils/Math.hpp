#pragma once

#include <Arduino.h>
#include "../SmartDevice_Model.hpp"

void remove_element(UsedGpio * arrUsedGpio, uint8_t index, uint8_t arrLength){
    
    for(uint8_t i = index; i < arrLength - 1; i++){
      arrUsedGpio[i] = arrUsedGpio[i + 1];
      // re asign all ids in order with array index
      arrUsedGpio[i].set_id(i);
    } 
}
