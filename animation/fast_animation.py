import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import matplotlib.animation as animation
from matplotlib.animation import FFMpegWriter
import time


save_video = True
fps = 20    # Frames per second
color = 'b'
dpi = 300   # Dots per inch (i.e. resolution)
boxsize = [20, 20, 20]   # Length of each side of the box
particlesize = 1            # Size of particles
filename = "test123.txt"    # Insert file name here (must be txt format)
videoname = "test_animation.mp4"    # Name of the rendered video. Must include file format


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

def timecalc(func, *args):
    before = time.time()
    rets = func(*args)
    after = time.time()

    return after - before, rets

def animate(data):
    frames = []
    fig = plt.figure()
    ax = plt.axes(projection='3d')

    writer = animation.FFMpegWriter(fps=fps, extra_args=['-vcodec', 'libx264', '-preset', 'ultrafast'])

    # Settings
    ax.set_xlim(0, boxsize[0])
    # ax.set_xlabel('X')
    ax.set_ylim(0, boxsize[1])
    # ax.set_ylabel('Y')
    ax.set_zlim(0, boxsize[2])
    # ax.set_zlabel('Z')
    ax.set_axis_off()
    fig.set_size_inches((5, 5), forward=True)
    # plt.tight_layout()

    plot = ax.plot([], [], [], '.', ms=particlesize, c=color)[0]

    tbefore = time.time()
    with writer.saving(fig, "../videos/" + videoname, dpi=dpi):
        for frame in data:
            plot.set_data(frame[:, 0], frame[:, 1])
            plot.set_3d_properties(frame[:, 2], 'Z')
            #writer._frame_sink().write(writer.fig.canvas.tostring_argb())
            # This is the part that takes time
            writer.grab_frame()
    tafter = time.time()
    print("time taken to render video:", tafter - tbefore, "s")


if __name__ == "__main__":
    print("extracting data...")
    data = data_extract(filename)
    print("animating...")
    animate(data)
