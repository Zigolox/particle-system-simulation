import matplotlib.pyplot as plt
import numpy as np

def read_data(file):
    with open(file, 'r') as f:
        all_data = f.read()
    _, _, energy  = all_data.split("\n")
    energy = energy.split('\t')
    energy = energy[:-1]
    max_energy = float(energy[-1])
    print("Max energy:",max_energy)
    N = 10
    distribution = [0]*(N+2)


    for E in energy:
        try:
            E = float(E)
            i = int(N*E/max_energy)
            print(i)
            distribution[i] += 1

        except ValueError:
            print("Error:", E)
    return distribution

dist = read_data("energy_distribution.txt")

plt.figure(0)


plt.xlabel("Time")
plt.plot([i for i in range(len(dist))],dist,'g-', label='Energy', linewidth=1)
plt.ylabel("Energy/n")
plt.title("Energy Plot")
plt.legend()
plt.show()
