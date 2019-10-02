import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import matplotlib.animation as animation
import time
from multiprocessing import Pool
import subprocess


save_video = False
fps = 60                    # Frames per second
#color = 'b'                 # Color of particles
dpi = 300                   # Dots per inch (i.e. resolution)
boxsize = 100      # Length of each side of the box
particlesize = 40            # Size of particles (not the same coordinates as the box)
filename = "../Optimized_program/source/position_data_electric_new.txt"    # Insert file name here (must be txt format)
videoname = "test_animation"    # Name of the video. Without file format
if save_video:
    multiprocessing = True  # Enable this for parallell processing
    if multiprocessing:
        cpus = 4            # number of cores in computer
else:
    multiprocessing = False


def test_datagen(nparticles, nframes, filename):
    """Function that generates random data and saves in a file. Used for testing the program."""
    a = np.random.uniform(0, 10, size=(nparticles, 3))
    with open(filename, 'w') as txt:
        for i in range(nframes):
            a += 0.1
            for col in a:
                for i in col:
                    txt.write(str(i) + " ")
                txt.write("\t")
            txt.write("\n")


def data_extract(filename):
    """Function that extracts data from the file that stores data.
    Returns: numpy array with location of all particles for each frame"""

    simulation = []
    with open(filename) as txtdata:
        for frame in txtdata.readlines()[1::1000]:
            frame_arr = []
            for particle in frame.split('\t')[:-1]:
                frame_arr.append(np.array([coord for coord in particle.split(' ')][:], dtype=float))
            simulation.append(frame_arr)

    simulation = np.array(simulation)
    print("Number of frames:", simulation.shape[0],
          "\nNumber of particles:", simulation.shape[1],
          "\nNumber of dimensions:", simulation.shape[2])

    return simulation


def animate(data, index):
    """Function that animates all particles in 3D.
    NOTE: This function is rather slow. Improvements might be possible.
    Returns: None but creates an mp4 file with the animation."""

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

    color = np.arange(data.shape[1])

    if save_video:
        writer = animation.FFMpegWriter(fps=fps, bitrate=fps*100, extra_args=['-vcodec', 'libx264', '-preset', 'ultrafast'])
        tbefore = time.time()
        plot = ax.plot([], [], [], '.', ms=particlesize, c=color, cmap="jet")[0]

        with writer.saving(fig, f"../videos/{index if index >= 0 else ''}{videoname}.mp4", dpi=dpi):
            for frame in data:
                plot.set_data(frame[:, 0], frame[:, 1])
                plot.set_3d_properties(frame[:, 2])
                # grab_frame takes time
                writer.grab_frame()
        tafter = time.time()
        print("time taken to save video:", tafter - tbefore, "s")
    else:
        video = []
        for frame in data:
            plot = ax.scatter(frame[:, 0], frame[:, 1], frame[:, 2], s=particlesize, c=['k', 'r'], animated=True)
            video.append([plot])

        animation.ArtistAnimation(fig, video, interval=1000/fps, blit=True, repeat_delay=1000)
        plt.show()


if __name__ == "__main__":
    print("extracting data...")
    data = data_extract(filename)

    print("animating...")
    if multiprocessing and save_video:
        tf = [int(i/cpus*data.shape[0]) for i in range(cpus+1)]
        print(tf)
        with Pool(cpus) as p:
            p.starmap(animate, [(data[tf[i]:tf[i+1],:,:], i) for i in range(len(tf)-1)])
        subprocess.call(["./merge_videos.sh", videoname])
    else:
        animate(data, -1)
