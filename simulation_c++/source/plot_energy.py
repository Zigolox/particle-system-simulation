import matplotlib.pyplot as plt
import numpy as np

def read_data(file):
    with open(file, 'r') as f:
        all_data = f.read()
    EK_list, EP_list, t_list, _ = all_data.split("\n")
    EK_list, EP_list, t_list = EK_list.split("\t")[:-1], EP_list.split("\t")[:-1], t_list.split("\t")[:-1]
    E_list = []
    for EK, EP, t in zip(EK_list, EP_list, t_list):
        try:
            EK, EP, t = float(EK), float(EP), float(t)
            E_list.append(EK + EP)
        except ValueError:
            print("Error:", EK, EP, t)
    return t_list[::1000], EK_list[::1000], EP_list[::1000], E_list[::1000]

mat = read_data("energy_data.txt")

plt.figure(0)
plt.plot(mat[0],mat[1],'g-', label='Kinetic Energy', linewidth=1)
plt.plot(mat[0],mat[2],'r-', label='Potential Energy', linewidth=1)
plt.plot(mat[0],mat[3],'y-', label='Total Energy', linewidth=1)

plt.xlabel("Time")
plt.ylabel("Energy")
plt.title("Energy Plot")
plt.legend()

plt.show()

plt.figure(1)
plt.plot(mat[0],mat[1],'g-', label='Potential Energy', linewidth=1)
plt.show()
