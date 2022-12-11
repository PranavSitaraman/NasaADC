import time
import csv
import seaborn as sns
import matplotlib.pyplot as plt
from PIL import Image

SIZE = 4000
start = time.time()

MODE = 'height'  # 'height' or 'slope'

# read data from csv
with open(f'../data/{MODE}.csv', 'r') as file:
    reader = csv.reader(file)
    arr = [[float(i) for i in row] for row in reader]

# generate heatmap with seaborn
ax = sns.heatmap(arr, square=True, cbar=False, xticklabels=False,
                 yticklabels=False, cmap="gist_rainbow_r")
print(f"heatmap generation time: {time.time() - start}")
plt.savefig(f'../data/{MODE}.png', dpi=2048,
            transparent=True, format='png', bbox_inches='tight')

# # crop extra border, make it square
size = 4096, 4096
png = Image.open(f'../data/{MODE}.png')
cropped = png.crop(png.getbbox())
cropped.thumbnail(size, Image.Resampling.LANCZOS)
cropped.save(f'../data/{MODE}.png')
