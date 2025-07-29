import json
import pandas as pd
import sys

def json_to_excel(json_file, excel_file):
    try:
        with open(json_file, 'r') as f:
            data = json.load(f)

        df = pd.DataFrame(data)
        df.to_excel(excel_file, index=False)
        print(f"✅ Successfully created {excel_file}")
    except Exception as e:
        print(f"❌ Failed to convert {json_file} to Excel: {e}")

if __name__ == "__main__":
    if len(sys.argv) != 3:
        print("Usage: python3 json_to_excel.py <input.json> <output.xlsx>")
        sys.exit(1)

    json_file = sys.argv[1]
    excel_file = sys.argv[2]

    json_to_excel(json_file, excel_file)
