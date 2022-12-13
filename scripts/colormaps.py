import math
import time
import csv
import seaborn as sns
import numpy as np
import matplotlib.pyplot as plt
from PIL import Image

SIZE = 4000
start = time.time()
def sigmoid(z):
    return 1.0/(1 + np.exp(-z))

MODE = 'azimuth'  # 'height' or 'slope' or 'elevation'

def elevation(lat, long, height):
    radius = 1737.4 * 1000 + height
    x = radius * math.cos(math.radians(lat)) * math.cos(math.radians(long))
    y = radius * math.cos(math.radians(lat)) * math.sin(math.radians(long))
    z = radius * math.sin(math.radians(lat))
    vec = [x - 361000000, y, z + 42100000]
    dist = math.sqrt(vec[0]**2 + vec[1]**2 + vec[2]**2)
    rz = float(vec[0] * math.cos(math.radians(lat)) * math.cos(math.radians(long)) + vec[1] *
               math.cos(math.radians(lat)) * math.sin(math.radians(long)) + vec[2] * math.sin(math.radians(lat)))
    return math.degrees(math.asin(rz/dist))

def azimuth(lat, long):
    return math.degrees(math.atan2((math.sin(long)*math.cos(lat)), math.sin(lat)))

# read data from csv
# with open(f'../data/{MODE}.csv', 'r') as file:
#     reader = csv.reader(file)
#     arr = [[float(i) for i in row] for row in reader]


with open(f'../data/longitude.csv', 'r') as file:
    reader = csv.reader(file)
    longitude = [[float(i) for i in row] for row in reader]

with open(f'../data/latitude.csv', 'r') as file:
    reader = csv.reader(file)
    latitude = [[float(i) for i in row] for row in reader]

# with open(f'../data/height.csv', 'r') as file:
#     reader = csv.reader(file)
#     height = [[float(i) for i in row] for row in reader]

arr = [[azimuth(latitude[i][j], longitude[i][j]) for j in range(SIZE)] for i in range(SIZE)]
avg = np.sum(arr)/(SIZE * SIZE)
stddev = ((sum((arr[i][j] - avg)**2 for i in range(SIZE) for j in range(SIZE)))/(SIZE * SIZE))**0.5
arr = [[math.log(sigmoid((arr[i][j] - avg)/stddev)) for j in range(SIZE)] for i in range(SIZE)]
# arr = [[elevation(latitude[i][j], longitude[i][j], height[i][j]) for j in range(SIZE)] for i in range(SIZE)]

print('MAX', MODE, np.amax(arr))
print('MIN', MODE, np.amin(arr))


with open(f'../data/{MODE}.csv', 'w') as file:
    writer = csv.writer(file)
    for row in arr:
        writer.writerow(row)

print(True)

# generate heatmap with seaborn
ax = sns.heatmap(arr, square=True, cbar=False, xticklabels=False,
                 yticklabels=False, cmap="gist_rainbow_r")
print(f"heatmap generation time: {time.time() - start}")
plt.savefig(f'../data/{MODE}.png', dpi=2048,
            transparent=True, format='png', bbox_inches='tight')

# crop extra border, make it square
size = 4096, 4096
png = Image.open(f'../data/{MODE}.png')
cropped = png.crop(png.getbbox())
cropped.thumbnail(size, Image.Resampling.LANCZOS)
cropped.save(f'../data/{MODE}.png')
