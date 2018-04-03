void savetoEEPROM (unsigned long latitude,unsigned long longitude,unsigned long ellTime,int altitude,int ReceiverValue){
   
   addrEEPROM = writetoEEPROM(addrEEPROM,latitude,4);
   addrEEPROM = writetoEEPROM(addrEEPROM,longitude,4);
   addrEEPROM = writetoEEPROM(addrEEPROM,ellTime,4);
   addrEEPROM = writetoEEPROM(addrEEPROM,altitude,2);
   addrEEPROM = writetoEEPROM(addrEEPROM,ReceiverValue,2);
   
  }
int writetoEEPROM(int addr,unsigned long val, int bytes){
  //Uses bytes Space
    int sizeBuff = bytes;
    unsigned char buff[sizeBuff];
    for (int i = 0; i<sizeBuff;i++){
        buff[i] = (byte) (val >> (i*8));
      }
    
    for (int i =0; i<sizeBuff;i++ ){
//      DEBUG_PORT.print("@");
//      DEBUG_PORT.print(addr);
//      DEBUG_PORT.print(", ");
//      DEBUG_PORT.println(buff[i],BIN);
      EEPROM.write(addr, buff[i]);
      addr = addr + 1;
      }
    return addr;
  }
