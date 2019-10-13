import numpy as np
import matplotlib.pyplot as plt

INPUT_FILE = "./Data/force5/distance_data.txt"

def read_data(file):
    with open(file, 'r') as f:
        input_data = f.read()
    data = []
    for row in input_data.split("\n")[:-1]:
        data.append(eval(row))
    return data

def count_data(data, step = 1, amount = None, sizes = 10, maximum = 1):
    if not amount:
        amount = len(data)

    radii = [maximum*i/sizes for i in range(sizes)]
    out_data = np.array([0]*sizes)
    total = 0
    for row in data[-amount::step]:
        for r in row:
            index = min(int(sizes*r/maximum),sizes-1)
            out_data[index] += 1
            total += 1
    outdata = out_data/total
    return radii, outdata

def main():
    data = read_data(INPUT_FILE)
    X, Y = count_data(data, sizes = 50,  maximum = 15 )

    plt.plot(X, Y, '-r')
    plt.xlabel("Distance")
    plt.ylabel("Percentage")
    plt.show()

main()
