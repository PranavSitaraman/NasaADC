"""
File: colormaps.py
Team Ad Lunam
NASA ADC 2022-2023
"""


import math
import time
import csv
import seaborn as sns
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt
from PIL import Image

# height, slope, elevation, azimuth
MODE = "all"
CBAR = True
CMAP = mpl.colormaps['gist_rainbow_r']
CMAP.set_bad('white')
SIZE = 4000
start = time.time()

longitude = []
latitude = []
height = []
slope = []
lunarRadius = 1737.4e3

# read from CSV datasets
with open('data/longitude.csv') as file:
    reader = csv.reader(file)
    longitude = [[float(j) for j in i] for i in reader]

with open('data/latitude.csv') as file:
    reader = csv.reader(file)
    latitude = [[float(j) for j in i] for i in reader]

with open('data/height.csv') as file:
    reader = csv.reader(file)
    height = [[float(j) for j in i] for i in reader]

with open('data/slope.csv') as file:
    reader = csv.reader(file)
    slope = [[float(j) for j in i] for i in reader]

# height
if MODE == 'height' or MODE == 'all':
    print('HEIGHT:')
    print('MAX', np.amax(height))
    print('MIN', np.amin(height))
    print('CALCULATION:', time.time() - start)

    # generate heatmap with seaborn
    ax = sns.heatmap(height, square=True, cbar=CBAR, xticklabels=False,
                    yticklabels=False, cmap=CMAP)
    print('HEATMAP:', time.time() - start)
    # plt.show()
    plt.savefig(f'height.png', dpi=2048,
                transparent=True, format='png', bbox_inches='tight')

    # crop extra border, make it square
    size = SIZE, SIZE
    png = Image.open('height.png')
    cropped = png.crop(png.getbbox())
    cropped.thumbnail(size, Image.Resampling.LANCZOS)
    cropped.save('height.png')

# slope
if MODE == 'slope' or MODE == 'all':
    print('SLOPE:')
    print('MAX', np.amax(slope))
    print('MIN', np.amin(slope))
    print('CALCULATION:', time.time() - start)

    # generate heatmap with seaborn
    ax = sns.heatmap(slope, square=True, cbar=CBAR, xticklabels=False,
                    yticklabels=False, cmap=CMAP)
    print('HEATMAP:', time.time() - start)
    # plt.show()
    plt.savefig(f'slope.png', dpi=2048,
                transparent=True, format='png', bbox_inches='tight')

    # crop extra border, make it square
    size = SIZE, SIZE
    png = Image.open('slope.png')
    cropped = png.crop(png.getbbox())
    cropped.thumbnail(size, Image.Resampling.LANCZOS)
    cropped.save('slope.png')

# elevation angle
if MODE == 'elevation' or MODE == 'all':
    target = np.array([361000e3, 0, -42100e3])
    elevation = []
    for i in range(SIZE):
        row = []
        for j in range(SIZE):
            long = longitude[i][j]
            lat = latitude[i][j]
            radius = lunarRadius + height[i][j]
            x = radius * math.cos(math.radians(lat)) * math.cos(math.radians(long))
            y = radius * math.cos(math.radians(lat)) * math.sin(math.radians(long))
            z = radius * math.sin(math.radians(lat))
            reference = np.array([x, y, z])
            result = target - reference
            X, Y, Z = result
            range_ = math.sqrt(X**2 + Y**2 + Z**2)
            rz = X * math.cos(math.radians(lat)) * math.cos(math.radians(long)) + Y * math.cos(
                math.radians(lat)) * math.sin(math.radians(long)) + Z * math.sin(math.radians(lat))
            row.append(math.degrees(math.asin(rz/range_)))
        elevation.append(row)

    print('ELEVATION:')
    print('MAX', np.amax(elevation))
    print('MIN', np.amin(elevation))
    print('CALCULATION:', time.time() - start)
    np.savetxt("elevation.csv", elevation, delimiter=",")

    c = mpl.colormaps['gist_rainbow_r']

    # generate heatmap with seaborn
    ax = sns.heatmap(elevation, square=True, cbar=CBAR, xticklabels=False,
                    yticklabels=False, cmap=CMAP)
    print('HEATMAP:', time.time() - start)
    # plt.show()
    plt.savefig(f'elevation.png', dpi=2048,
                transparent=True, format='png', bbox_inches='tight')

    # crop extra border, make it square
    size = SIZE, SIZE
    png = Image.open('elevation.png')
    cropped = png.crop(png.getbbox())
    cropped.thumbnail(size, Image.Resampling.LANCZOS)
    cropped.save('elevation.png')

# azimuth angle
if MODE == 'azimuth' or MODE == 'all':
    azimuth = []
    for i in range(SIZE):
        row = []
        for j in range(SIZE):
            long = longitude[i][j]
            lat = latitude[i][j]
            a = math.sin(math.radians(long)) * math.cos(math.radians(lat))
            b = math.cos(math.radians(lat)) * math.cos(math.radians(long))
            row.append(math.degrees(math.atan2(b, a)))
        azimuth.append(row)

    print('AZIMUTH:')
    print('MAX', np.amax(azimuth))
    print('MIN', np.amin(azimuth))
    print('CALCULATION:', time.time() - start)
    np.savetxt("azimuth.csv", azimuth, delimiter=",")

    # generate heatmap with seaborn
    ax = sns.heatmap(azimuth, square=True, cbar=CBAR, xticklabels=False,
                    yticklabels=False, cmap=CMAP)
    print('HEATMAP:', time.time() - start)
    # plt.show()
    plt.savefig(f'azimuth.png', dpi=2048,
                transparent=True, format='png', bbox_inches='tight')

    # crop extra border, make it square
    size = SIZE, SIZE
    png = Image.open('azimuth.png')
    cropped = png.crop(png.getbbox())
    cropped.thumbnail(size, Image.Resampling.LANCZOS)
    cropped.save('azimuth.png')