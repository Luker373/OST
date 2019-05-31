import sys

f = open(sys.argv[1])
print("Opened argv number", 1, sys.argv[1])

boat_s_arr = {}
boat_d_arr = {}
wind_s_arr = {}
wind_d_arr = {}
timstamp_arr = {}

lineDict = {}

idx = 0
for line in f:
    line = line.translate({ord(c): None for c in '\''})
    lineDict[idx] = line.split(",")
    boat_s_arr[idx] = lineDict[idx][6]
    boat_d_arr[idx] = lineDict[idx][7]
    wind_s_arr[idx] = lineDict[idx][4]
    wind_d_arr[idx] = lineDict[idx][5]
    timstamp_arr[idx] = lineDict[idx][9].split("*")[0]
    idx = idx + 1

f.close()

path = "matparse_" + sys.argv[1]
f = open(path, "w+")

f.write("\n%s = [" % "boatSpeed")
for i in boat_s_arr:
    f.write("%s\n" % (boat_s_arr[i]))

f.write("];\n%s = [" % "track")
for i in boat_d_arr:
    f.write("%s\n" % (boat_d_arr[i]))

f.write("];\n%s = [" % "windSpeed")
for i in wind_s_arr:
    f.write("%s\n" % (wind_s_arr[i]))

f.write("];\n%s = [" % "windDeg")
for i in wind_d_arr:
    f.write("%s\n" % (wind_d_arr[i]))

f.write("];\n%s = [" % "ts_gnost")
for i in timstamp_arr:
    f.write("%s\n" % (timstamp_arr[i]))

f.write("];")

f.close()