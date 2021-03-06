/*
 *  limited_ap_test.ino - GS2200(WiFi Module) test sample application without libraries
 *  Copyright 2018 Sony Semiconductor Solutions Corporation
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#include <SPI.h>
  
/*---------------------------------------------------------------------*/
void recv_atcommand(void){
  char buf[0x400];

  memset(buf,'\0', 1024);

  buf[0] = 0xA5;
  buf[1] = 0x02;
  buf[2] = 0x00;
  buf[3] = 0x00;
  buf[4] = 0x00;
  buf[5] = 0x00;
  buf[6] = 0x04;
  buf[7] = 0xf9;

  while(digitalRead(PIN_D27) == LOW);

  SPI5.transfer(buf, 8);
/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/
  
  memset(buf,0xf5,8);
  
  while(digitalRead(PIN_D27) == LOW);
  
  SPI5.transfer(buf, 8);
  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");

  int len = (buf[6]<<8)|buf[5];
  
  memset(buf,0xf5,8);

  while(digitalRead(PIN_D27) == LOW);

  SPI5.transfer(buf, (len+8));
/*  for(int i=0; i<(len+8) ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/
  puts(buf+8);
  
  /*data = digitalRead(PIN_D27); 
  printf("data=%x\n", data);*/
  
}
/*---------------------------------------------------------------------*/
void send_bcommand(String cmd,String ip,String port,uint8_t cid){
  int len = cmd.length()+ip.length()+1+port.length()+1+7;
  char buf[0x400];
  
  buf[0] = 0xA5;
  buf[1] = 0x01;
  buf[2] = 0x00;
  buf[3] = 0x00;
  buf[4] = 0x00;
  buf[5] = (len&0xff);
  buf[6] = ((len&0xff00)>>8);
  buf[7] = (0xfff-buf[1]-buf[5]-buf[6])&0xff;

/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/

  SPI5.transfer(buf, 8);
/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/

/*  data = digitalRead(PIN_D27); 
  printf("data=%x\n", data);*/

  memset(buf,0xf5,8);

  while(digitalRead(PIN_D27) == LOW);
  
  SPI5.transfer(buf, 8);
  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");

  buf[0] = 0xA5;
  buf[1] = 0x03;
  buf[2] = 0x00;
  buf[3] = 0x00;
  buf[4] = 0x00;
  buf[5] = (len&0xff);
  buf[6] = ((len&0xff00)>>8);
  buf[7] = (0xfff-buf[1]-buf[5]-buf[6])&0xff;
  
/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/

  while(digitalRead(PIN_D27) == LOW);

  SPI5.transfer(buf, 8);
/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/


  char header[8];
 
  header[0] = '\e';
  header[1] = 'Y';
  header[2] = cid+'0';
  header[3] = '\0';

  String bcmd(header);
  bcmd += ip;
  bcmd += ":";
  bcmd += port;
  bcmd += ":";

  header[0] = (cmd.length()/1000)%10+'0';
  header[1] = (cmd.length()/100)%10+'0';
  header[2] = (cmd.length()/10)%10+'0';
  header[3] = cmd.length()%10+'0';
  header[4] = '\0';

  bcmd += header;
  bcmd += cmd;

  memset(buf,'\r', 1024);
  memcpy(buf, bcmd.c_str(), len);

  for(int i=0; i<len ; i++) { printf("%x ", buf[i]); };
  puts(" ");
  for(int i=0; i<len ; i++) { printf("%c ", buf[i]); };
  puts(" ");

  SPI5.transfer(buf, len+3);

//  recv_atcommand();
  
}

/*---------------------------------------------------------------------*/
void send_atcommand(String cmd){
  int len = cmd.length()+1;
  char buf[0x400];
  
  buf[0] = 0xA5;
  buf[1] = 0x01;
  buf[2] = 0x00;
  buf[3] = 0x00;
  buf[4] = 0x00;
  buf[5] = (len&0xff);
  buf[6] = ((len&0xff00)>>8);
  buf[7] = (0xfff-buf[1]-buf[5]-buf[6])&0xff;

/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/

  SPI5.transfer(buf, 8);
/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/

/*  data = digitalRead(PIN_D27); 
  printf("data=%x\n", data);*/

  memset(buf,0xf5,8);

  while(digitalRead(PIN_D27) == LOW);
  
  SPI5.transfer(buf, 8);
  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");

  buf[0] = 0xA5;
  buf[1] = 0x03;
  buf[2] = 0x00;
  buf[3] = 0x00;
  buf[4] = 0x00;
  buf[5] = (len&0xff);
  buf[6] = ((len&0xff00)>>8);
  buf[7] = (0xfff-buf[1]-buf[5]-buf[6])&0xff;
  
/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/

  while(digitalRead(PIN_D27) == LOW);

  SPI5.transfer(buf, 8);
/*  for(int i=0; i<8 ; i++) { printf("%x ", buf[i]); };
  puts(" ");*/

  memset(buf,'\r', 1024);
  memcpy(buf, cmd.c_str(), len-1);

/*  for(int i=0; i<len ; i++) { printf("%x ", buf[i]); };
  for(int i=0; i<len ; i++) { printf("%c ", buf[i]); };
  puts(" ");*/

  SPI5.transfer(buf, len);

  recv_atcommand();
  
}

/*---------------------------------------------------------------------*/
void setup(void) {
  
  puts("GS2200 Test");
    
  pinMode(PIN_D27, INPUT);

  SPI5.begin();
  SPI5.beginTransaction(SPISettings(1000000, MSBFIRST, SPI_MODE1));

  recv_atcommand();
  puts("Started");
  sleep(1);
}
/*---------------------------------------------------------------------*/
void loop(void) {
  String string;

  string ="AT+VER=?";
  send_atcommand(string);

  string ="AT+WM=2";
  send_atcommand(string);

  string ="AT+NSET=192.168.8.1, 255.255.255.0, 192.168.8.1";
  send_atcommand(string);

  string ="AT+WA=SPESENSE,, 11";
  send_atcommand(string);

  string ="AT+DHCPSRVR=1";
  send_atcommand(string);

  string ="AT+NSTAT=?";
  send_atcommand(string);

  string ="AT+NSUDP=9000";
//  string ="AT+NSTCP=9000";
  send_atcommand(string);

  string ="AT+BDATA=1";
  send_atcommand(string);

  while(1){

  sleep(20);

  string ="AT+CID=?";
  send_atcommand(string);

  string ="AT+APCLIENTINFO=?";
  send_atcommand(string);

 string ="HELLO";
  String ip("192.168.8.2");
  String port("60136");
  send_bcommand(string,ip,port,0);
 
//  sleep(10);
  }
  puts("end");
  puts("-------------------------------------------------------------------------------");

  while(1);
  
}


