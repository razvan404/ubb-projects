import sys
import pandas as pd


if __name__ == "__main__":
    if len(sys.argv) != 2:
      print(f"Usage: {sys.argv[0]} <csv file>")
      exit(1)

    csv_file = sys.argv[1]
    df = pd.read_csv(csv_file)
    print(df.to_markdown(index=False))