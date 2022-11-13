import csv
import numpy as np
import matplotlib.pyplot as plt
import seaborn as sns
import scipy.interpolate as sci

NAME = 'faustini_rim_a'
STEP = (5, 5)
points = []
values = []

# read from .xyz file
with open(f'../{NAME}/{NAME}_points.xyz', 'r') as pointFile:
    pointReader = csv.reader(pointFile, delimiter=' ')
    for row in pointReader:
        points.append((float(row[0]), float(row[1])))
        values.append(float(row[2]))

# convert to numpy types
pts = np.array(points, dtype=np.double)
max = np.amax(pts.transpose()[0]), np.amax(pts.transpose()[1])
print('MAX:', max)
min = np.amin(pts.transpose()[0]), np.amin(pts.transpose()[1])
print('MIN:', min)
vals = np.array(values, dtype=np.double)

# interpolate values
xi_x, xi_y = np.mgrid[min[0]:max[0]:STEP[0], min[1]:max[1]:STEP[1]]
data = sci.griddata(pts, vals, (xi_x, xi_y), method='linear', fill_value=0)
print('SHAPE:', data.shape)

# create heatmap plot
mask = data == 0
heatmap = sns.heatmap(data, square=True, mask=mask, cbar=False, cmap='gist_yarg', xticklabels=False, yticklabels=False)
plt.savefig('../heightmap.png', dpi=4800, transparent=True)
print('DONE')