- copy file decode.c from `/p/course/cs354-deppeler/public/code/p1/decode.c`
#  Preprocessing Phase(-E)
- Preprocessing is the first phase of the build process, which prepares a C source file for compiling.
We can just preprocess the decode.c source file and store its result in a file named decode.i
using the command:
- `gcc -E decode.c -Wall -m32 -std=gnu99 -o decode.i`
- try to run decode.c till it compiles with preprocessor stage[USE `man gcc` to look at man page of gcc and find flags like -E OR -S etc]
# Compilation Phase(-S)
- The next phase of the build process is the compilation of the preprocessed source code. Compiling
translates this source to assembly language for a specific processor. Let's stop after compilation to
see the generated the assembly file. The option to let gcc know it should stop the build process after
compilation can be discovered in the man page under "compilation proper".
Run one of the following commands at the command prompt:
- `gcc <option> decode.c -Wall -m32 -std=gnu99` 
OR
`gcc <option> decode.i -Wall -m32 -std=gnu99`
- now try to find one good option/flag to run it till compilation stage
#  Assembling Phase(-c)
- Computers can only understand machine-level code (in binary), which requires an assembler to
convert the assembly code into machine code that the computer can execute.
- Let's now stop the build process after the assembling phase by entering one of the following
commands to create the object file decode.o:
- `gcc -c decode.c -Wall -m32 -std=gnu99`
OR
`gcc -c decode.s -Wall -m32 -std=gnu99`
- Note that the input to gcc can either be the C source file (decode.c) or the Assembly Code file
(decode.s) that was generated from the previous step. If you use the source file then all the prior
phases will be repeated.
- You can view the contents of an object file (decode.o) using a tool named objdump (object dump)
as shown below:
`objdump -d decode.o`
- objdump is a disassembler that converts the machine code to assembly code, which is the inverse
operation of the assembler. Understand the use of the command objdump and the meaning of the
option "-d" by looking at its man page or by typing `objdump --help` at the Linux prompt.
# Linking Phase
- The last phase of the build process combines your object file with other object files such as those in
the standard C library to create the executable file. Execute one of the following commands to create
the executable file.
- `gcc decode.c -Wall -m32 -std=gnu99 -o decode`
OR
`gcc decode.o -Wall -m32 -std=gnu99 -o decode`
- Use objdump to view the disassembled contents of the executable file, which is also a binary file, as
we did for the object file decode.o.
- Redirect the disassembled output that you got to a file named execfile_contents.txt. This file
should be much larger than the disassembled output of the decode.o file since it's an executable
file, which has information combined from decode.o and library functions like printf.
# Submission
- We've now seen the steps of the build process and generated intermediate files for each. You'll find that
the two files that you'll most often use are:
- 1. C Source File (decode.c)
- 2. Executable File (decode)
- In most cases, you would compile the source file directly to the executable file using the command in this
form:
`gcc <source-file-name> -Wall -m32 -std=gnu99 -o <executable-name>`
- EXECUTING C Programs (executables)
- Next we'll run the executable file to decode your encoded fortune.
- First, copy the file cipher.txt from the location:
`/p/course/cs354-deppeler/public/students/<your-cs-login>/p1/`
to your p1 directory. This file contains the fortune encoded using your CS login. The cipher.txt and
the executable decode must both be present in the same directory at this point.
- Run the decode executable file and you will be prompted for your CS login. Correctly enter your CS
login to get your decoded fortune, which should be a valid phrase in English.
- Create a new file named myfortune.txt and save your decoded fortune output string as the first and
only line of this file.
- Make sure that the contents of myfortune.txt are exactly the same as the decoded string and
nothing else. We'll use a script to automatically match this string with our answer key to grade your
submission. Include all the punctuation marks that are present in the plaintext output (including the
trailing period, exclamation or question mark). Copy the output from the terminal instead of retyping, to
avoid trivial spelling mistakes
