import numpy as np
import matplotlib.pyplot as plt

INPUT_FILE = "./Data/force2/distance_data.txt"

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
    avg = 0
    for row in data[-amount::step]:
        for r in row:
            avg += 1/r
            index = min(int(sizes*r/maximum),sizes-1)
            out_data[index] += 1
            total += 1
    outdata = out_data/(total*maximum/sizes)
    avg /= total
    return radii, outdata, 1/avg

def _main():
    data = read_data(INPUT_FILE)
    X, Y, avg = count_data(data, sizes = 100,  maximum = 15 )

    print("Average:", avg)

    plt.plot(X, Y, '-r')
    plt.title("Distance Plot")
    plt.xlabel("Distance")
    plt.ylabel("Probability")
    plt.show()



def main():
    switch = {2: '-r', 3: '-b', 4: '-g', 5: '-y'}
    for i in range(2,5):
        data = read_data("./Data/force"+ str(i) +"/distance_data.txt")
        X,Y, avg = count_data(data, sizes = 100,  maximum = 15 )
        print("Average ",i,": ", avg, sep = "")
        plt.plot(X, Y, switch[i], label = "n: -" + str(i-1))
        plt.title("Distance Plot")
        plt.xlabel("Distance")
        plt.ylabel("Probability")
    plt.legend()
    plt.show()
_main()
