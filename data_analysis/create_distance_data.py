import numpy as np
INPUT_FILE = "./Data/force2/position_data.txt"
OUTPUT_FILE = "./Data/force2/distance_data.txt"

def distance(p1, p2):
    return np.linalg.norm(p1 - p2)

def read_data(file):
    """Read input data from file"""
    with open(file, 'r') as f:
        raw_input = f.read()
    output = []
    for row in raw_input.split('\n')[1:-1]:
        output_row = []
        for pos in row.split('\t')[:-1]:
            pos = pos.split(" ")
            x = float(pos[0])
            y = float(pos[1])
            z = float(pos[2])
            output_row.append(np.array([[x,y,z]]))
        output.append(output_row)
    return output

def get_distances(positions):
    """Return a list of ordered pairs of elements in a list"""
    distances = []
    for i, p1 in enumerate(positions[:-1]):
        for p2 in positions[i+1:]:
            distances.append(distance(p1,p2))
    return distances

def main():
    all_data = read_data(INPUT_FILE)
    with open(OUTPUT_FILE,'w') as f:
        for row in all_data[-10:]:

            f.write(str(get_distances(row)) + "\n")


main()
