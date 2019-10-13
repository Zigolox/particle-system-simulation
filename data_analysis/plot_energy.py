import matplotlib.pyplot as plt
import numpy as np

import sys

def avg(L):
    return sum(L)/len(L)


def read_data(file):
    with open(file, 'r') as f:
        all_data = f.read()
    EK_list, EP_list, t_list, *_ = all_data.split("\n")
    EK_list, EP_list, t_list = EK_list.split("\t")[:-1], EP_list.split("\t")[:-1], t_list.split("\t")[:-1]
    t_out = []
    EK_out = []
    EP_out = []
    E_out = []
    for EK, EP, t in zip(EK_list, EP_list, t_list):
        try:
            EK, EP, t = float(EK), float(EP), float(t)
            t_out.append(t)
            EK_out.append(EK)
            EP_out.append(EP)
            E_out.append(EK + EP)
        except ValueError:
            print("Error:", EK, EP, t)
    return t_out, EK_out, EP_out, E_out

def read_data_EK(file):
    with open(file, 'r') as f:
        all_data = f.read()
    EK_list, t_list, _ = all_data.split("\n")
    EK_list, t_list = EK_list.split("\t")[:-1], t_list.split("\t")[:-1]

    for EK, t in zip(EK_list, t_list):
        try:
            EK, t = float(EK), float(t)

        except ValueError:
            print("Error:", EK, t)
    return t_list, EK_list

flags = {"-f" : "filename"}

args = dict(filename = "energy_data.txt")

# TODO: bad code
for i, flag in enumerate(sys.argv[1:]):
    if flag[0] == '-':
        try:
            args[flags[flag]] = int(sys.argv[i+2])
        except ValueError:
            args[flags[flag]] = sys.argv[i+2]


mat = read_data(args['filename'])

print("Ratio:")
for i in range(100,len(mat[1])-1,500):
    try:
        print(avg(mat[2][i:i+100])/avg(mat[1][i:i+100]),end =", ")
    except TypeError:
        print("Error:",i)
print("")

plt.figure(0)
plt.plot(mat[0],mat[1],'g-', label='Kinetic Energy', linewidth=1)
plt.plot(mat[0],mat[2],'r-', label='Potential Energy', linewidth=1)
plt.plot(mat[0],mat[3],'y-', label='Total Energy', linewidth=1)

plt.xlabel("Time")
plt.ylabel("Energy")
plt.title("Energy Plot")
plt.legend()

plt.show()
