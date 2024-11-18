/*  Program to find parity for 2006 Dodge Ram 5.9 Common Rail Cummins Vehicle Speed on CAN bus ID:[0x215, 0, 1, 7 ] (Byte 6)
 *                               November 14, 2024     by YouTuber: AlxBilt
 * 
 * Dodge vss math -> HEX 0x3200 = DEC 12,800 / 128 = 100km/h
 *                -> HEX 0x2580 = DEC  9,600 / 128 =  75km/h
 *                -> HEX 0x1900 = DEC  6,400 / 128 =  50km/h
 *                -> HEX 0x0C80 = DEC  3,200 / 128 =  25km/h
 *                -> HEX 0x0000 = DEC      0 / 128 =   0km/h 
 *
 */

#include <string.h>
#include <stdio.h>
#include<bits/stdc++.h>
#define bool int

using namespace std;



  void printBinary(int num) {
    std::bitset<sizeof(int) * 8> bits(num);
    std::cout << bits << std::endl;
}
  void loop(){
    int x = 0;      
    int kph = 128;
    char choice[10];                              // To store user input for "dec" or "hex"


  printf("Dec or Hex ?: ");
    scanf("%s", choice);
  if (strcmp(choice, "dec") == 0)  {
   printf("Enter Dec Value :");                   // Enter Dec Value         
    scanf("%d" , &x);                             // Initial Dec Value: 1444  
   printf("Hex Value: %x\n", x);
}
else if(strcmp(choice, "hex") == 0) {
 	printf("Enter Hex Value :");                    // Enter Dec Value        
    scanf("%x", &x);                              // Initial Hex Value: 0x05a4 to Dec: 1444   
  printf("Dec Value: %d\n", x);
	
}
else {
  printf("Invalid choice! Please enter 'dec' or 'hex'.\n");
}
    
    int speed = x / kph;
//  x = ("%x", 0x5ae4) / 128;                     // Hex: 0x05a4 to Dec: 1444

  printf("KPH: %d\n", speed);
  printf("KPH Binary: ");
  printBinary(speed);

    x ^= x >> 8;                                  // Binary: 10110100001 Dec: 1441
    
  printf("8 bit Value Shift: %d\n", x);
  printf("8 bit Binary Value: ");
  printBinary(x);

    x ^= x >> 4;                                  // Binary: 10111111011 Dec: 1531

  printf("4 bit Value Shift: %d\n", x);
  printf("4 bit Binary Value: ");
  printBinary(x);

    x &= 0xf;                                     // This keep the lowest 4 bits (0�15), vss a number between 0 -15   

  printf("XOR Lowest Bit: %d\n", x);              // Result: x = 11 in dec  (binary: 1011) or odd parity 
  printf("XOR Lowest Bit Binary: "); 
  printBinary(x);

    bool parity_bit=(0x6996 >> x) & 1;            // Constant formula parity_bit=(0x6996 >> x) & 1;

  printf("Parity Bit: %d\n", parity_bit);
//  printf("Parity Bit Binary: ");
  printBinary(parity_bit);

if (parity_bit) {
  printf("Parity is Odd.\n");
}
else {
  printf("Parity is Even.\n");
    
}
}
  int main(){
    char yes[5];
do{
 	loop();
	
	printf("Do you want to calculate again? (y/n): ");
    scanf("%s", yes);
}
while (strcmp(yes, "y") == 0);
  printf("Goodbye!\n");
return 0;
} 
  
    



