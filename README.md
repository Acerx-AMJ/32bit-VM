# 32bit VM
32bit virtual machine based off LC-3. Guide for creating an LC-3 VM: https://www.jmeiners.com/lc3-vm/, LC-3 16bit opcode documentation: https://www.jmeiners.com/lc3-vm/supplies/lc3-isa.pdf.

This virtual machine has memory and a CPU that is capable of executing some basic instructions. It reads a file, turns the characters into words (tokens) and then parses the tokens into intructions and stores them into memory and executes the instructions one by one. The commands can be found in [include/opcodes.hpp](include/opcodes.hpp), where they are documented.

## Building
This project only depends on C++17 and can be built using your favorite compiler:
```bash
g++ -std=c++17 -Iinclude src/vm32bit.cpp -o vm
```

## Usage
Simply run the executable and you'll be presented with a REPL interface. To run a file, type:
```bash
> run file.asx
```
There are no traps at the moment, meaning you cannot output anything. This is why the first 5 registers are printed to the console when the program halts. You can try out the VM using this program:
```bash
ADD R0, R0, 1
ADD R1, R1, 2
ADD R2, R2, 3
ADD R3, R3, 4
ADD R4, R4, 5
```
It will simply output numbers 1-5.

## Credits
This project was made by Daniel Vishnevsky and is licensed under MIT License. It was made in March of 2025 and published on October 2026 as an effort to make all of my projects open-source.
