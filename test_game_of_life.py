import os
import subprocess

def run_test(input_file, output_file, generations):
    """
    Runs the Game of Life program and compares the input and output files.
    """
    # Run the Game of Life executable
    command = f"./gol --load {input_file} --save {output_file} --generations {generations} --measure"
    result = subprocess.run(command, shell=True, capture_output=True, text=True)

    # Check if the program executed successfully
    if result.returncode != 0:
        print(f"Error running the program: {result.stderr}")
        return False

    # Compare the input and output files
    with open(input_file, "r") as f1, open(output_file, "r") as f2:
        input_content = f1.read()
        output_content = f2.read()

    if input_content == output_content:
        print(f"Test passed: {input_file} after {generations} generations.")
        return True
    else:
        print(f"Test failed: {input_file} after {generations} generations.")
        return False


# Test cases
tests = [
    {"input": "oscillators100x100_in.gol", "output": "oscillators100x100_out.gol", "generations": 30},
    {"input": "StillLife100x100_in.gol", "output": "still_life100x100_out.gol", "generations": 30},
]

# Run all tests
for test in tests:
    input_file = test["input"]
    output_file = test["output"]
    generations = test["generations"]

    if not os.path.exists(input_file):
        print(f"Test file {input_file} not found.")
        continue

    run_test(input_file, output_file, generations)
