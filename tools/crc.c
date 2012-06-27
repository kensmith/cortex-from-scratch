#include <stdio.h>

int crc_calc(const char frame_no_fcs[], int frame_len) {
int i; // iterator
int j; // another iterator
char byte; // current byte
int crc; // CRC result
int q0, q1, q2, q3; // temporary variables
crc = 0xFFFFFFFF;
for (i = 0; i < frame_len; i++) {
byte = *frame_no_fcs++;
for (j = 0; j < 2; j++) {
if (((crc >> 28) ^ (byte >> 3)) & 0x00000001) {
q3 = 0x04C11DB7;
} else {
q3 = 0x00000000;
}
if (((crc >> 29) ^ (byte >> 2)) & 0x00000001) {
q2 = 0x09823B6E;
} else {
q2 = 0x00000000;
}
if (((crc >> 30) ^ (byte >> 1)) & 0x00000001) {
q1 = 0x130476DC;
} else {
q1 = 0x00000000;
}
if (((crc >> 31) ^ (byte >> 0)) & 0x00000001) {
q0 = 0x2608EDB8;
} else {
q0 = 0x00000000;
}
crc = (crc << 4) ^ q3 ^ q2 ^ q1 ^ q0;
byte >>= 4;
}
}
return crc;
}

// 0000000: f07f 0010 9905 0000 9905 0000 9905 0000  ................
// 0000010: 9905 0000 9905 0000 9905 0000 a95a 372a  .............Z7*
int main()
{
   const char buf[] = {
      0xf0,0x7f,0x00,0x10,
      0x99,0x05,0x00,0x00,
      0x99,0x05,0x00,0x00,
      0x99,0x05,0x00,0x00,
      0x99,0x05,0x00,0x00,
      0x99,0x05,0x00,0x00,
      0x99,0x05,0x00,0x00,
   };

   printf("0x08%x\n", crc_calc(buf, sizeof(buf)/sizeof(buf[0])));
   printf("0x08%x\n", -crc_calc(buf, sizeof(buf)/sizeof(buf[0])));

   return 0;
}
