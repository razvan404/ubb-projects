import sys
import subprocess

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Invalid number of arguments!")
        print("Usage:", sys.argv[0], "<lex file>")
        sys.exit(1)

    file_name = sys.argv[1]
    lex_compiled = "lex.yy.c"
    other_files = ["btree.c"]
    subprocess.run(f"flex {file_name}", shell=True, check=True)
    subprocess.run(
        f"gcc {lex_compiled} {' '.join(other_files)}", shell=True, check=True
    )
