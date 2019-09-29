import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import matplotlib.animation as animation
import time
from multiprocessing import Pool
import subprocess


save_video = True
fps = 60    # Frames per second
color = 'b'
dpi = 300   # Dots per inch (i.e. resolution)
boxsize = [20, 20, 20]   # Length of each side of the box
particlesize = 1            # Size of particles
filename = "test123.txt"    # Insert file name here (must be txt format)
videoname = "test_animation.mp4"    # Name of the rendered video. Must include file format
multiprocessing = True


def data_extract(filename):
    simulation = []
    with open(filename) as txtdata:
        for frame in txtdata.readlines():
            frame_arr = []
            for particle in frame.split('\t')[:-1]:
                frame_arr.append(np.array([coord for coord in particle.split(' ')][:-1], dtype=float))
            simulation.append(frame_arr)

    simulation = np.array(simulation)
    print("Number of frames:", simulation.shape[0],
          "\nNumber of particles:", simulation.shape[1],
          "\nNumber of dimensions:", simulation.shape[2])

    return simulation


def animate(data, index):
    frames = []
    fig = plt.figure()
    ax = plt.axes(projection='3d')

    # Settings
    if isinstance(boxsize, list) or isinstance(boxsize, tuple):
        ax.set_xlim(0, boxsize[0])
        ax.set_ylim(0, boxsize[1])
        ax.set_zlim(0, boxsize[2])
    else:
        ax.set_xlim(0, boxsize)
        ax.set_ylim(0, boxsize)
        ax.set_zlim(0, boxsize)

    ax.set_axis_off()
    fig.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=None, hspace=None)
    fig.set_size_inches((5, 5), forward=True)

    writer = animation.FFMpegWriter(fps=fps, bitrate=fps*100, extra_args=['-vcodec', 'libx264', '-preset', 'ultrafast'])

    plot = ax.plot([], [], [], '.', ms=particlesize, c=color)[0]

    tbefore = time.time()
    with writer.saving(fig, f"../videos/{index if index > 0 else ""}{videoname}", dpi=dpi):
        for frame in data:
            plot.set_data(frame[:, 0], frame[:, 1])
            plot.set_3d_properties(frame[:, 2])
            #writer._frame_sink().write(writer.fig.canvas.tostring_argb())
            # This is the part that takes time
            writer.grab_frame()
    tafter = time.time()
    print("time taken to render video:", tafter - tbefore, "s")


if __name__ == "__main__":
    print("extracting data...")
    data = data_extract(filename)

    print("animating...")
    if multiprocessing:
        cpus = 4
        tf = [int(i/cpus*data.shape[0]) for i in range(cpus+1)]
        print(tf)
        with Pool(cpus) as p:
            p.starmap(animate, [(data[tf[i]:tf[i+1],:,:], i) for i in range(len(tf)-1)])
        subprocess.call("./merge_videos.sh")
    else:
        animate(data, -1)
