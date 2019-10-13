import matplotlib.pyplot as plt
import numpy as np

def read_data(file):
    with open(file, 'r') as f:
        all_data = f.read()
    *_, kinetic_energy, potential_energy, _  = all_data.split("\n")

    kinetic_energy = kinetic_energy.split('\t')
    kinetic_energy = kinetic_energy[:-1]
    max_energy = float(kinetic_energy[-1])
    print("Kinetic:", kinetic_energy[-5:])
    print("Potential:", potential_energy[-5:])
    print("Max energy:",max_energy)
    N = 10
    distribution_EK = [0]*(N+2)


    for EK in kinetic_energy:
        try:
            EK = float(EK)
            i = int(N*EK/max_energy)
            print(i)
            distribution_EK[i] += 1

        except ValueError:
            print("Error:", EK)

    potential_energy = potential_energy.split('\t')
    potential_energy = potential_energy[:-1]
    min_energy = float(potential_energy[0])
    print("Min energy:",min_energy)
    N = 10
    distribution_EP = [0]*(N+2)


    for EP in potential_energy:
        try:
            EP= float(EP)
            i = int(N*EP/min_energy)
            print(i)
            distribution_EP[i] += 1

        except ValueError:
            print("Error:", EP)

    return distribution_EK, distribution_EP

dist_EK, dist_EP = read_data("Data/Force3/energy_data.txt")

plt.figure(0)


plt.xlabel("Energy")

#plt.plot([i for i in range(len(dist_EK))],dist_EK,'g-',
#label='Kinetic Energy', linewidth=1)

plt.plot([i for i in range(len(dist_EP))],dist_EP,'g-',
label='Potential Energy', linewidth=1)
plt.ylabel("dE/dn")
plt.title("Energy Plot")
plt.legend()
plt.show()
