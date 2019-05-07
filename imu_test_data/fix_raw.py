import sys
from decimal import Decimal


f = open(sys.argv[1])
print("Opened argv number", 1, sys.argv[1])

gnostLineDict = {}
imuLineDict = {}

# get file size and print to user for stats purposes
i_idx = 0
g_idx = 0
timestamp = ""
for line in f:
    if line.find("*") == -1 and line.find("$") == -1:
        imuLineDict[i_idx] = timestamp + " " + line
        i_idx = i_idx + 1
        continue
    if line[line.find("*") + 1].isnumeric() and line[line.find("*") + 3] == '\n':
        gnostLineDict[g_idx] = line.split(",")
        timestamp = gnostLineDict[g_idx][9].split("*")[0]
        g_idx = g_idx + 1
print("Raw file size:", i_idx+g_idx, "lines")
f.close()

path = "gnost_" + sys.argv[1]
f = open(path, "w+")
for i in gnostLineDict:
    f.write("%s:%s\n" % (i, gnostLineDict[i]))
f.close()

path = "imu_" + sys.argv[1]
f = open(path, "w+")
for i in imuLineDict:
    f.write("%s:%s" % (i, imuLineDict[i]))
f.close()