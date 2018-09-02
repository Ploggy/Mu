#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "emulator.h"
#include "portability.h"
#include "specs/pdiUsbD12Commands.h"


//this is only emulating the commands and USB transfer, the internals of the chip are not documented so any invalid behavior may not match that of the original chip
//running a new command before finishing the previous one will result in corruption


#define PDIUSBD12_TRANSFER_BUFFER_SIZE 130

static uint8_t pdiUsbD12FifoBuffer[PDIUSBD12_TRANSFER_BUFFER_SIZE];
static uint8_t pdiUsbD12ReadIndex;
static uint8_t pdiUsbD12WriteIndex;
//static uint8_t pdiUsbD12WaitForWrites;


static inline uint8_t pdiUsbD12ReadByte(){
   uint8_t data = pdiUsbD12FifoBuffer[pdiUsbD12ReadIndex];
   pdiUsbD12ReadIndex++;
   return data;
}

static inline void pdiUsbD12WriteByte(uint8_t data){
   pdiUsbD12FifoBuffer[pdiUsbD12WriteIndex] = data;
   pdiUsbD12WriteIndex++;
}

void pdiUsbD12Reset(){
   memset(pdiUsbD12FifoBuffer, 0x00, PDIUSBD12_TRANSFER_BUFFER_SIZE);
   pdiUsbD12ReadIndex = 0;
   pdiUsbD12WriteIndex = 0;
}

uint64_t pdiUsbD12StateSize(){
   uint64_t size = 0;

   size += PDIUSBD12_TRANSFER_BUFFER_SIZE;
   size += sizeof(uint8_t) * 2;

   return size;
}

void pdiUsbD12SaveState(uint8_t* data){
   uint64_t offset = 0;

   memcpy(data + offset, pdiUsbD12FifoBuffer, PDIUSBD12_TRANSFER_BUFFER_SIZE);
   offset += PDIUSBD12_TRANSFER_BUFFER_SIZE;
   writeStateValueUint8(data + offset, pdiUsbD12ReadIndex);
   offset += sizeof(uint8_t);
   writeStateValueUint8(data + offset, pdiUsbD12WriteIndex);
   offset += sizeof(uint8_t);
}

void pdiUsbD12LoadState(uint8_t* data){
   uint64_t offset = 0;

   memcpy(pdiUsbD12FifoBuffer, data + offset, PDIUSBD12_TRANSFER_BUFFER_SIZE);
   offset += PDIUSBD12_TRANSFER_BUFFER_SIZE;
   pdiUsbD12ReadIndex = readStateValueUint8(data + offset);
   offset += sizeof(uint8_t);
   pdiUsbD12WriteIndex = readStateValueUint8(data + offset);
   offset += sizeof(uint8_t);
}

uint8_t pdiUsbD12GetRegister(bool address){
   //just log all USB accesses for now
   debugLog("USB read, address:0x%01X\n", address);

   if(!address){
      //0x0 data

   }
   else{
      //0x1 commands

   }

   return 0x00;
}

void pdiUsbD12SetRegister(bool address, uint8_t value){
   //just log all USB accesses for now
   debugLog("USB write, address:0x%01X, value:0x%02X\n", address, value);

   if(!address){
      //0x0 data

   }
   else{
      //0x1 commands
      switch(value){
         case READ_INTERRUPT_REGISTER:

            break;

         default:
            break;
      }
   }
}
