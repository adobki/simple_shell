# ReadMe

# ___Simple Shell (hsh) by @adobki___
**hsh** is a simple UNIX command interpreter that replicates the basic functions of the inbuilt sh in UNIX.
It was created as part of the requirements for completing the Foundations part of the Software Engineering course at ALX (ALX SE). Tested on Ubuntu 20.04.

## Languages and Technologies Used
 * C Language.

## Simple Shell v1.0
> Usage: hsh [COMMAND] [ARGUMENTS...]

Simple shell can work in interactive mode:
```
$ ./hsh
($) ls -a
. .. hsh simple_shell.c simple_shell.h
($) me
./hsh: 0: me: not found
($) exit
$
```
 
or in non-interactive mode:
```
$ echo "ls -a" | ./hsh
. .. hsh simple_shell.c simple_shell.h
```
```
$ ./hsh ls -a
. .. hsh simple_shell.c simple_shell.h
```

## Bugs
No known bugs at this time. 

## Authors
[Donald Ajaps](https://github.com/adobki)

## License
Public Domain. No copyright protection. 
