import time
import csv
import seaborn as sns
import matplotlib.pyplot as plt

SIZE = 4000
start = time.time()

MODE = 'slope'  # 'height' or 'slope'
output = {'height': 'elevation', 'slope': 'slope'}

with open(f'../data/{MODE}.csv', 'r') as file:
    reader = csv.reader(file)
    arr = [[float(i) for i in row] for row in reader]

ax = sns.heatmap(arr, square=True, cbar=False, xticklabels=False,
                 yticklabels=False, cmap="gist_rainbow_r")
print(f"heatmap generation time: {time.time() - start}")
plt.savefig(f'../data/{output[MODE]}map.png', dpi=4800, transparent=True)
