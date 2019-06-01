import sys
import matplotlib.pyplot as plt 
from decimal import Decimal, DecimalException

for j in range(1, len(sys.argv)):
    f = open(sys.argv[j])
    print("Opened argv number", j, sys.argv[j])

    for i, l in enumerate(f):
        pass
    f = open(sys.argv[j])

    gps_lat_arr = [0] * (i + 1)
    gps_long_arr = [0] * (i + 1)

    lineDict = {}

    idx = 0
    for line in f:
        lineDict[idx] = line.split(",")
        gps_lat_arr[idx] = Decimal(lineDict[idx][0])
        gps_long_arr[idx] = Decimal(lineDict[idx][1])
        idx = idx+1

    plt.plot(gps_long_arr, gps_lat_arr);
    plt.xlabel('lat')
    plt.ylabel('long')
    plt.title('lat v long')
    plt.show()