# Nand2tetris Project 

In the Nand2tetris project, I built a computer from scratch beginning with logical gates, RAM, registers, and other chips up to the CPU. Along with these, I wrote the assembler and some parts of the virtual machine.<br />
<br />
Thanks to all the tools and necessary files found on the official website, I  learned how to write code using Assembly language, and then translate that code into binary using my assembler.<br />

---
### Logic Gates

Wrote the logic for each different logic gate using a Hardware Definition Language, also used to create the CPU and RAM: these include basic gates such:

- And
- Not
- Or

---

### CPU

I integrated the chips built into a computer architecture capable of executing programs written in the machine language, the topmost chip within the CPU is the ALU (Arithmetic Logical Unit) which computes a given function on its two given data inputs and outputs the result.

---

### Assembler 

The assembler program I wrote translates symbolic machine language (assembly) to binary code that can be executed by the CPU.
just like the following:
<pre>
@16                      0000000000010000<br />
M=1                      1110111111001000<br />
@17        ------>       0000000000010001<br />
M=0                      1110101010001000<br />
@16                      0000000000010000<br />
D=M                      1111110000010000<br />
</pre>

---

### Virtual machine

The VM translates virtual machine commands such as "push constant 2" or "push local 1" into assembly code, which later will be run trought the assembler to generate the equivalent binary code of each VM command. This file is missing some functionalities.


  * For more information please refer to the official https://www.nand2tetris.org/ website.
  * These files were written by Giovanny Quimbayo.
