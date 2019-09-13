import matplotlib.pyplot as plt
import numpy as np

def read_data(file):
    with open(file, 'r') as f:
        all_data = f.read()
    EK_list, EP_list, t_list, _ = all_data.split("\n")
    EK_list, EP_list, t_list = EK_list.split("\t"), EP_list.split("\t"), t_list.split("\t")
    E_list = []
    for EK, EP, t in zip(EK_list, EP_list, t_list):
        EK, EP, t = float(EK), float(EP), float(t)
        E_list.append(EK+EP)
    return t_list, EK_list, EP_list, E_list

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
