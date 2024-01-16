import os
import sys
import subprocess

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage:", sys.argv[0], "<flex file>", "<bison file>")
        exit(1)

    flex_file = sys.argv[1]
    flex_compiled = "lex.yy.c"
    bison_file = sys.argv[2]
    bison_compiled = "yacc.tab.c"
    bison_header = "yacc.tab.h"

    other_files = []
    subprocess.run(f"bison -d {bison_file}", shell=True, check=True)
    subprocess.run(f"flex {flex_file}", shell=True, check=True)
    subprocess.run(f"gcc {flex_compiled} {bison_compiled} {' '.join(other_files)}", shell=True, check=True)
    os.remove(flex_compiled)
    os.remove(bison_compiled)
    os.remove(bison_header)