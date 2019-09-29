# particle-system-simulation
Programs for simulating particles with unusual forces

## Animation
Use ```fast_animation.py``` to extract the data from a txt file and save the video. The video will be saved in the ```videos``` folder.

### Required packages
- numpy
- matplotlib

Install these packages using ```pip install numpy``` and ```pip install matplotlib```. If you are using Anaconda, these packages should come pre-installed.

### Customizing the output
All variables that can be changed by the user without breaking the program are located at the top of the ```fast_animation.py``` file. See detailed description about the different variables in the file itself.

### Parallell processing
```fast_animation.py``` also has an option for parallell processing, which makes the program run slightly faster.
This also runs the bash script ```merge_videos.mp4``` in the ```animation``` folder. Make sure to enable this bash script using ```chmod +x merge_videos.mp4``` before running the program.


