# Theory of Algorithms - MD5 Message-Digest Algorithm
###### David Gallagher
## Project Specs
Write a program in the C programming language that calculates the MD5 hash digest of an input.
The algorithm is specified in the [Request For Comments 1321](https://tools.ietf.org/html/rfc1321) document supplied by the Internet Engineering Task Force.

## Instructions for use
For command line interactions on any OS see this [Cheat Sheet](https://gist.github.com/jonlabelle/e8ba94cd29b8f63fd7dd3c4f95c1d210).  
You will need Git [installed locally](https://git-scm.com/book/en/v2/Getting-Started-Installing-Git).  

``` 
git clone https://github.com/d-gallagher/TheoryOfAlgorithms.git
cd TheoryOfAlgorithms/Md5
```
Follow the guides below for Windows or Linux environments.
##### Windows
[Walkthrough: Compile a C program on the command line](https://docs.microsoft.com/en-us/cpp/build/walkthrough-compile-a-c-program-on-the-command-line?view=vs-2019).  
Windows development suggestions:  
[Clion](https://www.jetbrains.com/clion/download/#section=windows) Jetbrains c development environment, does a lot of work for you.  
[Visual Studio Code](https://code.visualstudio.com/) a lightweight and prominent cross-platform IDE for development.  
Use [Cmder](https://cmder.net/) instead of cmd prompt on windows. It's a better console/terminal and uses linux commands.  
```
cl main.c 
main "filename"
```
##### Linux
[How to Write and Run a C Program in Linux](https://vitux.com/how-to-write-and-run-a-c-program-in-linux/).  
[Visual Studio Code](https://code.visualstudio.com/) a lightweight and prominent cross-platform IDE for development.  
[VIM](https://www.linux.com/training-tutorials/vim-101-beginners-guide-vim/) is more challenging to learn but provides a 
lot of functionality and is worth learning if you will be terminal bound for certain projects.  
```
make main
./main "file name"
```
## Project Overview
### Encryption Overview
In [cryptography](https://en.wikipedia.org/wiki/Cryptography), encryption is the process of encoding a message or data 
in such a way that only authorized parties can access it and those who are not authorized cannot. It is also used as a means 
to store sensitive information, for example user passwords, such as to keep the passwords obfuscated and protected from malicious attacks. 
This means that a database of user names and passwords if it became public, would be useless to an attacker. 
The protection however, even for encrypted data, is highly dependant upon the encryption used. 
 
Key features to consider regarding hashing algorithms:
- __Speed__:  
The algorithm reads the whole file, performs some mathematical functions and generates a hash.   
A very computationally expensive algorithm may slow down the process.
- __Security__:  
The probability of two files having the same hash is called collision and can be very bad for our purposes,  
so it should be as near to zero as possible.
- __Generated hash length__:  
This will save some space in the generated data stored, for example in a database, or in memory during runtime.

__MD5__ is one such encryption algorithm that was used in the past to safeguard against such attacks but in the last 20-30 
years it has been found to be vulnerable to certain attacks which can lead to security breaches.   
### MD5 Encryption
MD5 was initially designed by Ronald Rivest in 1992, to be used as a cryptographic hash function, suitable for use in cryptography.
The purpose of the MD5 is to take an input of a fixed arbitrary size and compute a hash of 128 bits, described as a 'fingerprint' 
or 'message digest'.  
As of 1996, and subsequently in 2004, MD5 was found to be vulnerable to collision attacks and pre-image attacks, and deemed 
> ["cryptographically broken and unsuitable for further use"](https://en.wikipedia.org/wiki/MD5).

This vulnerability is explored further by Jacob Neyole in his paper 
[Vulnerability of data security using MD5 function in php database design ](hhttps://www.researchgate.net/publication/280926128_Vulnerability_of_data_security_using_MD5_function_in_php_database_design),
stating that 
> "The security of the MD5 hash function is severely compromised" 

and that through the use of hash collisions, (Detailed paper on collision attacks: 
[Some thoughts on Collision Attacks in the Hash Functions MD5,SHA-0 and SHA-1](https://eprint.iacr.org/2005/391.pdf)) 
it is possible to produce two files with the same hash which in turn compromises the integrity of an MD5-hashed message.  
Today, the MD5 hash algorithm is still in use as a checksum to verify the integrity of a file but is no longer used as a 
means to store cryptographically secure passwords or other sensitive data. 

### MD5 Algorithm
MD5 takes a message or input of arbitrary length and outputs a 128-bit digest or hash of that input.  
The algorithm can be broken into 5 Steps: 
* Appending Padding Bits:
```
The input is broken into 512-bit blocks.  
The message is then padded such that the message length is divisible by 512, 
the final block in the message will be padded with zero's so that its length (in bits) 
is congruent to 448, modulo 512.  
Padding will always be performed on any input, even if the input already meets the expected 
congruency of 448 modulo 512.  
Padding is performed as follows: 
* A single "1" bit is appended to the message. 
* "0" bits are appended such that the length in bits of the padded message becomes 
  congruent to 448, modulo 512. 
* A minimum total of one bit and maximum of 512 bits are appended.
```
* Appending Length:
```
A 64-bit representation of the input is appended to the result of step 1. 
The resulting message has a length that is an exact multiple of 512 bits.  
Equivalently, this message has a length that is an exact multiple of 16 (32-bit) words.
```
* Initialize MD Buffer:
```
A four-word buffer (A,B,C,D) is used to compute the message digest.  
Here each of A, B, C, D is a 32-bit register.  
These registers are initialized to the following values in hexadecimal, low-order bytes first:  

word A: 01 23 45 67
word B: 89 ab cd ef
word C: fe dc ba 98
word D: 76 54 32 10
```
* Process input in 16-Word blocks:
```
Processing Message in 512-bit Blocks.  
Loop through the padded and appended message in blocks of 512 bits each.   
For each input block, 4 rounds of operations are performed with 16 operations in each round.
```
* Output 128-bit message digest:
```
The contents in buffer words A, B, C, D are returned in sequence with low-order byte first.
```

### Some thoughts on [Request For Comments 1321](https://tools.ietf.org/html/rfc1321)
RFC 1321 describes the MD5 message-digest algorithm.
As with any one way hash algorithm, it postulates that it is computationally infeasible to reverse this hash. Similarly 
it is infeasible to produce two messages having the same message digest. 
Key points to note about the MD5 algorithm:
- The speed of the algorithm is described as "conservative". The argument is that while it should not be cumbersome to 
compute the hash of the target input, it should also not be too fast as this would lend its'self to brute force attacks. 
- It should also be noted that given even any input, it would require 2^128 operations to generate every possible 
output for that input, hence the reference to computational infeasibility.

#### Integer Literals
The implementation of MD5 in C, uses integer literals for padding blocks of data.
```c
static unsigned char PADDING[64] = {
  0x80, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
};
```
The use of 0x80 in C99 refers to a hexadecimal integer literal for decimal 128.  
Given that 0x80 is a hexadecimal number we can convert it to decimal as follows:   
Decimal Calculation:
```
(80)₁₆ = (8 × 16¹) + (0 × 16⁰) = (128)₁₀
```
The binary representation of 0x80, and decimal 128 is:
```
10000000
```
It's use here is simply to pad the first "single "1" bit", as mentioned in the RFC documentation Step 1 for padding the 
message. The following 0's are then appended to fill out the message length to modulo 512 bits in total.
  
Hexadecimal 0x80 [explained in a little more detail](https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.2.0/com.ibm.zos.v2r2.cbclx01/lit_integer.htm#lit_integer__hexintlit) 
> "A hexadecimal integer literal begins with the 0 digit followed by either an x or X, 
> followed by any combination of the digits 0 through 9 and the letters a through f or A through F.  
> The letters A (or a) through F (or f) represent the values 10 through 15, respectively."  
 
#### *Why* use the sin function in step 4?
The sine function is used to construct the 64 element table. This is referred to as 
[nothing-up-my-slieve numbers](https://en.wikipedia.org/wiki/Nothing-up-my-sleeve_number), which are an agreed upon 
standard in cryptography, and verify that there are no malicious intentions involved in the algorithm. If everyone can see 
the operations being performed, and everyone can test the algorithm, try to break it, and can not find a vulnerability, then
it is deemed that the algorithm is robust and safe for use. It is important that there is a consensus on why a constant 
is used, to defend the integrity of the algorithm.
#### Independent and Unbiased bits
Step 4. Process Message in 16-Word Blocks:
> "It is interesting to note that if the bits of X, Y, and Z are independent and unbiased,  
> the each bit of F(X,Y,Z) will be independent and unbiased." 

Independent means each bit of the output does not depend on any other bit.   
Unbiased means equal probability of getting a 1 or a 0.  
This is a profound feature of the algorithm. It ensures that the highest degree of collision mitigation is applied.
Collisions are the death of any hashing algorithm, as producing duplicate hashes for different inputs leads to 
vulnerabilities (discussed earlier).  
MD5 produces a 16 byte hash (128 bits). The chance of a given hash output/digest showing up is 1/(2^128).  
[This](http://bugcharmer.blogspot.com/2012/06/how-big-is-2128.html) blog explains a little more detail about the size of
2^128, it's a big number, 1/(2^128) is tiny.

#### Endianness
Are your significant bits on the left or the right..?  

#####__Big Endian Byte Order:__   
The most significant byte (the "big end") of the data is placed at the byte with the lowest address.  
The rest of the data is placed in order in the next three bytes in memory.  
#####__Little Endian Byte Order:__   
The least significant byte (the "little end") of the data is placed at the byte with the lowest address. 
The rest of the data is placed in order in the next three bytes in memory.

I am developing this on windows using [Clion](https://www.jetbrains.com/clion/) rather than in a Linux environment. 
I will not be using the [<byteswap.h>](https://sites.uclouvain.be/SystInfo/usr/include/bits/byteswap.h.html) library for 
flipping the bits to accommodate endianness. 

[MINGW](http://mingw.5.n7.nabble.com/byteswap-h-included-in-mingw-td12385.html) does not facilitate the byteswap.h library. 
Fortunately flipping bits from big to little, or little to big endian is a well documented topic and solutions are abundant. 
I have included functions
[swap-endianness](https://github.com/d-gallagher/TheoryOfAlgorithms/blob/dcc3798f79ecd054fd5359dcdad27d8eba1bf906/MD5/main.c#L73), 
and [bswap_32](https://github.com/d-gallagher/TheoryOfAlgorithms/blob/2900f564e15ef756bd8442136a8bba5dc1571cf3/MD5/main.c#L112) 
to work around the functionality provided in byteswap.h.

#### Conclusion
In conclusion, MD5 fulfills the requirements of a hashing algorithm with one exception, and is no longer considered safe 
for use with passwords. It is possible for a third party to [generate 2 messages](https://www.mscs.dal.ca/~selinger/md5collision/), 
that both hash to the same value.  

__MD5 fulfills:__
- __Preimage Resistance:__  
Given a hash, how hard is it to find another message that hashes the same?  
Also known as a one way hash function.
- __Second Pre-image Resistance:__  
Given a message, find another message that hashes the same.

__MD5 fails:__
- __Collision Resistance:__  
How hard is it for someone to find two messages (any two messages) that hash the same.

### References
[Request For Comments 1321](https://tools.ietf.org/html/rfc1321)  
[Wikipedia - Cryptography](https://en.wikipedia.org/wiki/Cryptography)  
[Wikipedia - MD5 Message Digest](https://en.wikipedia.org/wiki/MD5)  
[Vulnerability of data security using MD5 function in php database design ](https://www.researchgate.net/publication/280926128_Vulnerability_of_data_security_using_MD5_function_in_php_database_design)  
[Some thoughts on Collision Attacks in the Hash Functions MD5,SHA-0 and SHA-1](https://eprint.iacr.org/2005/391.pdf)  
[IBM - Integer literals in C](https://www.ibm.com/support/knowledgecenter/en/SSLTBW_2.2.0/com.ibm.zos.v2r2.cbclx01/lit_integer.htm#lit_integer__hexintlit)  
[Wikipedia - Nothing-up-my-slieve numbers](https://en.wikipedia.org/wiki/Nothing-up-my-sleeve_number)  
[How big is 2**128? - Blog about how big the bits get!](http://bugcharmer.blogspot.com/2012/06/how-big-is-2128.html)  
[Clion - IDE](https://www.jetbrains.com/clion/)  
[Endian lib in C <byteswap.h>](https://sites.uclouvain.be/SystInfo/usr/include/bits/byteswap.h.html)  
[Wikipedia - Endianness](https://en.wikipedia.org/wiki/Endianness)  
[StackOverflow - Big vs Little Endian](https://stackoverflow.com/a/701644)  
[MINGW - Windows compiler for C](http://mingw.5.n7.nabble.com/byteswap-h-included-in-mingw-td12385.html)  
[MD5 Collision Demo](https://www.mscs.dal.ca/~selinger/md5collision/)  
