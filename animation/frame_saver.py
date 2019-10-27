from fast_animation import data_extract, get_userargs
import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits import mplot3d


def save_frame(data, frame_index=-1):
    fig = plt.figure()
    ax = plt.axes(projection='3d')
    boxsize = np.nanmax(data[np.isfinite(data)])
    ax.set_xlim(0, boxsize)
    ax.set_ylim(0, boxsize)
    ax.set_zlim(0, boxsize)
    ax.set_axis_off()
    fig.subplots_adjust(left=0, bottom=0, right=1, top=1, wspace=None, hspace=None)
    fig.set_size_inches((5, 5), forward=True)

    color = np.arange(data.shape[1])
    frame = data[frame_index]

    ax.scatter(frame[:, 0], frame[:, 1], frame[:, 2], s=args['particlesize'], c=color, cmap="jet")
    if args['videoname'][-3:] != 'pdf':
        plt.savefig(f"./videos/{args['videoname']}", dpi=args['dpi'])
    else:
        plt.savefig(f"./videos/{args['videoname']}", dpi=args['dpi'])

if __name__ == "__main__":
    args = get_userargs()
    data = data_extract(args['filename'], args['step'])
    save_frame(data, frame_index=-1)
