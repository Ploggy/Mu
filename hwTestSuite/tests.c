#include "testSuite.h"
#include "viewer.h"
#include "ugui.h"


var hexRamBrowser(){
   static Boolean  clearScreen = true;
   static uint32_t nibble = 0;/*what column to change with up/down keys*/
   static uint32_t pointerValue = UINT32_C(0x77777777);/*in the middle of everything*/
   static char     hexString[100];
   
   if(getButtonPressed(buttonUp)){
      pointerValue += 0x1 << (4 * (7 - nibble));
   }
   
   if(getButtonPressed(buttonDown)){
      pointerValue -= 0x1 << (4 * (7 - nibble));
   }
   
   if(getButtonPressed(buttonLeft)){
      if(nibble > 0)
         nibble--;
   }
   
   if(getButtonPressed(buttonRight)){
      if(nibble < 7)
         nibble++;
   }
   
   if(getButtonPressed(buttonSelect)){
      /*open hex viewer*/
      nibble = 0;
      clearScreen = true;
      setSubprogramArgs(makeVar(LENGTH_ANY, TYPE_PTR, pointerValue));/*length doesnt matter*/
      execSubprogram(hexViewer);
   }
   
   if(getButtonPressed(buttonBack)){
      nibble = 0;
      clearScreen = true;
      exitSubprogram();
   }
   
   /*Palm OS sprintf only supports 16 bit ints*/
   StrPrintF(hexString, "Open Hex Viewer At:\n0x%04X%04X", (uint16_t)(pointerValue >> 16), (uint16_t)pointerValue);
   
   if(clearScreen){
      UG_FillScreen(C_WHITE);
      clearScreen = false;
   }
   
   UG_PutString(0, 0, hexString);
}