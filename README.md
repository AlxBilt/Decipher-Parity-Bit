# XORbit Tool (Parity Bit Code Analysis)

Disclaimer: 

I am by no means a programmer. My notes below might be totally incorrect. In fact, it is a culmination of piecing together many separate source sights as a map for my own personal understanding. My notes are not my own original interpretation of the code. I am not a programmer, all though my desire says otherwise. I only started tinkering with programming in an effort to understand what my 2006 Ram 5.9 Cummins engine ECM require to detect the vehicle speed signal. This is because I swapped the motor into my 2001 Ford F550 which is pre-CANbus. One year later, here I am trying to wrap my head around C/C++ and Python for Everyone. Thanks Dr. Chuck Severance.....I think??? 

Below are my notes in regards to my attempt to understand the requirement of the Cummins CAN bus and/or 
vehicle speed data, 0x215[7]  = {0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0xFF}, parity being byte 6.
TEST
TEST
TEST


**Parity Bit Code Analysis**

1.	What is Bitwise?

Bitwise is a level of operation that involves working with individual bits which are the smallest units of data in a computing system. Each bit has single binary value of 0 or 1. Most programming languages manipulate groups of 8, 16 or 32 bits.
In electronics, "bitwise" refers to operations performed on individual bits within a binary number, meaning that each digit (0 or 1) in the binary representation of a value is manipulated separately, rather than treating the number as a whole; essentially, it's a way to work with the most fundamental unit of data in a computer system. 

Key points about bitwise operations. 

Individual bits. 

Unlike typical arithmetic operations that work on entire numbers, bitwise operations focus on manipulating each bit within a binary number. 

Logical operators. 

Common bitwise operators include AND (&), OR (|), XOR (^), and NOT (~), which perform logical operations on corresponding bits between two numbers. 

Efficiency. 

Bitwise operations are often used in low-level programming because they are directly supported by the processor, making them very fast. 

Example. 

Imagine you have two binary numbers: 0101 (decimal 5) and 1011 (decimal 11). 
Performing a bitwise AND operation would compare each corresponding bit.

0 & 1 = 0.
1 & 0 = 0.
1 & 1 = 1.

This results in a new binary number 0001 (decimal 1). 

2.	Determining vss Parity Bit Calculation for Cummins Common Rail ECM.

vss ^= vss >> 8 .
vss ^= vss >> 4 .          
vss &= 0xf .

**(See Code for Custom VSS Module ) Not yet uploaded due to imperfections)**

This series of operations reduces vss to a 4-bit value that effectively represents the parity of the original vss value. 
Here's what each line does.

vss ^= vss >> 8;: This XORs vss with itself shifted right by 8 bits, mixing up its bits.
In C++, the bitwise XOR and assign operator (^=) performs a bitwise XOR operation between two operands and assigns the result to the left operand. 

Here's how it works.

**Bitwise XOR (^).** 
This operator compares each bit of the two operands. If the bits are different (one is 0 and the other is 1), the result bit is 1. If the bits are the same (both 0 or both 1), the result bit is 0. 

**Assignment (=).** 
The assignment operator takes the result of the XOR operation and stores it back in the left operand.
 
Explanation. 

•	x is initially 5 (binary 0101). 
•	y is 3 (binary 0011). 
•	The bitwise XOR operation compares each bit.

0 ^ 0 = 0 . 
1 ^ 0 = 1 . 
0 ^ 1 = 1 . 
1 ^ 1 = 0 . 

•	The result of the XOR operation is 0110 (decimal 6). 
•	This result is then assigned back to x. 
•	vss ^= vss >> 4;: This further XORs the result with itself shifted right by 4 bits.

Example: Same as above vss ^= vss >>8 only by 4. 

•	vss &= 0xf;: This masks vss to keep only the lowest 4 bits (0–15), so vss becomes a number between 0 and 15.

Explanation. 

•	The binary representation of x (5) is 0101. 
•	The binary representation of 3 is 0011. 
•	The bitwise AND operation compares each corresponding bit of the two operands.

0 & 0 = 0 .
1 & 0 = 0 .
0 & 1 = 0 .
1 & 1 = 1 .

•	The result of the bitwise AND operation is 0001 (binary), which is equal to 1 (decimal). 
•	This result is assigned back to x or vss.

**Calculating the parity_bit.**

•  parity_bit = (0x6996 >> vss) & 1;
•	This shifts 0x6996 by vss bits to the right and then & with 1 to isolate the least significant bit of the shifted result.
•	If the least significant bit is 1, then parity_bit = 1 (odd), and if it’s 0, then parity_bit = 0 (even).

Explanation. 

In C++, & is the bitwise AND operator. When used with the number 1, it is a common way to check if a number is odd or even. 


How it works. 

•	Bitwise AND: The & operator performs a bitwise AND operation between the binary representations of two numbers. 
•	Checking for odd/even: The least significant bit (LSB) of a binary number determines whether it is odd or even. If the LSB is 1, the number is odd; if it's 0, the number is even. 
•	& 1: By performing a bitwise AND with 1, we isolate the LSB of the number. 
 
Explanation.

•	The binary representation of 5 is 101. 
•	5 & 1 performs a bitwise AND operation between 101 and 001, resulting in 001 (which is 1 in decimal). 
•	Since the result is 1, the condition num & 1 is true, indicating that the number is odd.

3.	Toggling, What is it?

In C++ programming, toggling a bit involves changing the value of a specific bit in a binary number. This operation is useful in various applications such as cryptography, data compression, hardware control. i.e CAN bus ACKnowledment. 
Bit toggling is used to control hardware settings at a very low level, such as setting or clearing specific flags in a control register

Toggling data215[6] Based on parity_bit and toggle.

The parity_bit and toggle control the value assigned to data215[6] in a repeating pattern.

•	If parity_bit == 1 (odd parity).

When toggle is 0 or 1, data215[6] is set to 0x01 or 0x04, depending on ECM.
When toggle is 2 or 3, data215[6] is set to 0x02 or 0x07, depending on ECM.
Toggle is incremented with each execution and cycles back to 0 after reaching 4.

•	If parity_bit == 0 (even parity).

When toggle is 0 or 1, data215[6] is set to 0x00 or 0x05, depending on ECM.
When toggle is 2 or 3, data215[6] is set to 0x03 or 0x06, depending on ECM.
Toggle increments in the same way as above.

Cycle Control with toggle Reset.

4.	if (toggle > 3) toggle = 0;
5.	This line ensures that toggle cycles back to 0 after it reaches 4, allowing the pattern to repeat indefinitely.

Example Walkthrough. 

Suppose we start with a specific value for vss. Here’s how it would work:

1.	Initial vss value: Assume some arbitrary initial value, say vss = 0x1234.
2.	Calculate the modified vss.
3.	
vss ^= vss >> 8;
and
vss ^= vss >> 4;

will transform vss into a value between 0 and 15.

Let’s say this results in vss = 7 after these operations.

5.	Determine parity_bit.
   
parity_bit = (0x6996 >> 7) & 1;

Shifting 0x6996 (binary 0110 1001 1001 0110) right by 7 bits gives 0000 0000 1101 0011.
The least significant bit of 0000 0000 1101 0011 is 1, so parity_bit = 1 (odd).

4.	Toggle Behavior for Odd Parity.

If toggle starts at 0 or 1, data215[6] = 0x01.
If toggle reaches 2 or 3, data215[6] = 0x02.
After toggle increments through 0, 1, 2, and 3, it resets to 0, repeating the cycle.

**Summary of Output Patterns.**

This code creates a specific pattern in data215[6] based on the parity of vss and the toggle counter.

•	Odd Parity (parity_bit = 1): data215[6] alternates as 0x01 -> 0x01 -> 0x02 -> 0x02. (Version dependant  0x04 or 0x01, 0x07 or 0x02).
•	Even Parity (parity_bit = 0): data215[6] alternates as 0x00 -> 0x00 -> 0x03 -> 0x03.(Version dependant 0x05 or 0x00, 0x06 or 0x03).

The toggle counter ensures that this alternation (toggle) continues in a loop, providing a predictable pattern. 

