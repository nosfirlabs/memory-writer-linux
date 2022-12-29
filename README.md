# memory-writer-linux
a little utility made for https://coding.global discord - writing and reading memory on linux


This program takes a PID and an offset as command line arguments, and either reads or writes a value from the specified location in the process's memory, depending on whether a value is provided as an additional command line argument.

To read a value from memory, run the program with just the PID and offset:
>./mem_read_write 123456 0x7ff000

To write a value to memory, provide the value as an additional argument:

>./mem_read_write 123456 0x7ff000 "hello world"

Keep in mind that reading and writing memory can be a risky operation, and can potentially cause a process to crash or behave unexpectedly. You should use caution when using this functionality, and only do so if you have a good understanding of what you are doing and the potential consequences.
