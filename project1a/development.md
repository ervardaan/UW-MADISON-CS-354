- copy file decode.c from `/p/course/cs354-deppeler/public/code/p1/decode.c`
#  Preprocessing Phase
- Preprocessing is the first phase of the build process, which prepares a C source file for compiling.
We can just preprocess the decode.c source file and store its result in a file named decode.i
using the command:
- `gcc -E decode.c -Wall -m32 -std=gnu99 -o decode.i`
- try to run decode.c till it compiles with preprocessor stage[USE `man gcc` to look at man page of gcc and find flags like -E OR -S etc]
# Compilation Phase
- The next phase of the build process is the compilation of the preprocessed source code. Compiling
translates this source to assembly language for a specific processor. Let's stop after compilation to
see the generated the assembly file. The option to let gcc know it should stop the build process after
compilation can be discovered in the man page under "compilation proper".
Run one of the following commands at the command prompt:
- `gcc <option> decode.c -Wall -m32 -std=gnu99` 
OR
`gcc <option> decode.i -Wall -m32 -std=gnu99`
- now try to find one good option/flag to run it till compilation stage
