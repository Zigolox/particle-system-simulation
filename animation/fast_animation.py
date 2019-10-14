import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d
import matplotlib.animation as animation
import time
from multiprocessing import Pool
import subprocess
import sys

flags = {'-v':'save_video', '-s': 'step', '-f': 'fps', '-q': 'dpi', '-r':'particlesize', '-d': 'filename', '-o': 'videoname', '-c': 'cpus'}

args = dict(save_video = False,
            step = 1,
            fps = 60,                    # Frames per second
            dpi = 300,                   # Dots per inch (i.e. resolution)
            particlesize = 20,            # Size of particles (not the same coordinates as the box)
            filename = "./Data/force3/position_data.txt",
            videoname = 'test_animation',
            cpus=4)

# TODO: bad code
for i, flag in enumerate(sys.argv[1:]):
    if flag[0] == '-':
        try:
            args[flags[flag]] = int(sys.argv[i+2])
        except ValueError:
            args[flags[flag]] = sys.argv[i+2]

if args['save_video']:
    if isinstance(args['cpus'], int) and args['cpus'] > 1:
        multiprocessing = True
    else:
        multiprocessing = False
else:
    multiprocessing = False
# End of bad code

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


def data_extract(filename, step=0):
    """Function that extracts data from the file that stores data.
    Returns: numpy array with location of all particles for each frame"""

    simulation = []
    with open(filename) as txtdata:
        for frame in txtdata.readlines()[1::step]:
            frame_arr = []
            for particle in frame.split('\t')[:-1]:
                frame_arr.append(np.array([coord for coord in particle.split(' ')], dtype=float))
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
    boxsize = np.nanmax(data[np.isfinite(data)])
    ax.set_xlim(0, boxsize)
    ax.set_ylim(0, boxsize)
    ax.set_zlim(0, boxsize)

    ax.set_axis_off()
    fig.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=None, hspace=None)
    fig.set_size_inches((5, 5), forward=True)

    color = np.arange(data.shape[1])

    if args['save_video']:
        # TOOO: This cannot have different color for different particles yet.
        writer = animation.FFMpegWriter(fps=args['fps'], bitrate=args['fps']*100, extra_args=['-vcodec', 'libx264', '-preset', 'ultrafast'])
        tbefore = time.time()
        bcoord = np.zeros(data.shape[1])
        plot = ax.scatter(bcoord, bcoord, bcoord, s=args['particlesize'], c=np.arange(data.shape[1]), cmap="jet")

        with writer.saving(fig, f"../videos/{index if index >= 0 else ''}{args['videoname']}.mp4", dpi=args['dpi']):
            for frame in data:
                plot._offsets3d = (frame[:, 0], frame[:, 1], frame[:, 2])
                # grab_frame takes time
                writer.grab_frame()
        tafter = time.time()
        print("time taken to save video:", tafter - tbefore, "s")
    else:
        video = []
        for frame in data:
            plot = ax.scatter(frame[:, 0], frame[:, 1], frame[:, 2], s=args['particlesize'], c=np.arange(data.shape[1]), cmap="jet", animated=True)
            video.append([plot])

        animation.ArtistAnimation(fig, video, interval=1000/args['fps'], blit=True, repeat_delay=1000)
        plt.show()


if __name__ == "__main__":
    print("extracting data...")
    data = data_extract(args['filename'], args['step'])

    print("animating...")
    if multiprocessing and args['save_video']:
        tf = [int(i/args['cpus']*data.shape[0]) for i in range(args['cpus']+1)]
        print(tf)
        with Pool(args['cpus']) as p:
            p.starmap(animate, [(data[tf[i]:tf[i+1],:,:], i) for i in range(len(tf)-1)])
        subprocess.call(["./merge_videos.sh", args['videoname']])
    else:
        animate(data, -1)
