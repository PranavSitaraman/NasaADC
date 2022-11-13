import csv
import math

long = []
lat = []
height = []
name = 'faustini_rim_a'

print('reading longitude')
with open(f'../{name}/{name}_longitude.csv', 'r') as lonFile:
    lonReader = csv.reader(lonFile)
    for row in lonReader:
        for i in row:
            long.append(float(i))
            
print('reading latitude')
with open(f'../{name}/{name}_latitude.csv', 'r') as latFile:
    latReader = csv.reader(latFile)
    for row in latReader:
        for i in row:
            lat.append(float(i))

print('reading height')
with open(f'../{name}/{name}_height.csv', 'r') as heightFile:
    heightReader = csv.reader(heightFile)
    for row in heightReader:
        for i in row:
            height.append(float(i))

print('writing values')
lunarRadius = 1737.4 * 1000
with open(f'../{name}/{name}_points.xyz', 'w', newline='',) as pointFile:
    pointWriter = csv.writer(pointFile, delimiter=' ')
    for i in range(len(lat)):
        radius = lunarRadius + height[i]
        x = radius * math.cos(math.radians(lat[i])) * math.cos(math.radians(long[i]))
        y = radius * math.cos(math.radians(lat[i])) * math.sin(math.radians(long[i]))
        z = radius * math.sin(math.radians(lat[i]))
        pointWriter.writerow([x, y, z])
