# base_converter
A command-line interface to convert numbers from one base to another.

## Features:
* The following bases are supported:
  Name | Base
  ---- | ----
  Hexadecimal | 16
  Decimal | 10
  Octal | 8
  Binary | 2
* Convert a number from one base to another easily.

## How to compile:
Make sure to have the following installed on your system:
* [GCC](https://gcc.gnu.org/)
* [Make](https://www.gnu.org/software/make/)

Then, follow the instructions below to compile and run *base_converter*:

  1. Open a terminal and run the following command: `make all`.
  2. Then, go into the newly created `/bin` folder.
  3. Inside, you will see a new file named `base_converter`. If you are on Windows, rename this file to `base_converter.exe`.
  4. To run *base_converter*, change your terminal directory to `/bin`. Then, run the command that coincides with your operating system:
     Operating system | Terminal command
     ---------------- | ----------------
     Linux / MacOS | `./base_converter`
     Windows | `.\base_converter.exe`

## Images:
![Initial interface](/images/1.png)
![Help interface](/images/2.png)
![Example showing a decimal number converted into hexadecimal, octal, and binary](/images/3.png)
![Example showing a hexadecimal number converted into decimal, octal, and binary](/images/4.png)
![Example showing invalid input being handled by *base_converter*](/images/5.png)
