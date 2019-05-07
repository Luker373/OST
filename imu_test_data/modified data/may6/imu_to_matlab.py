import sys, re

f = open(sys.argv[1])
print("Opened argv number", 1, sys.argv[1])

roll_arr = {}
pitch_arr = {}
yaw_arr = {}
timstamp_arr = {}

lineDict = {}

idx = 0
for line in f:
    line = line.translate({ord(c): None for c in '\''})
    lineDict[idx] = re.split(':| r| p| y|\n', line)
    roll_arr[idx] = lineDict[idx][2]
    pitch_arr[idx] = lineDict[idx][3]
    yaw_arr[idx] = lineDict[idx][4]
    timstamp_arr[idx] = lineDict[idx][1]
    idx = idx + 1

f.close()

path = "matparse_" + sys.argv[1]
f = open(path, "w+")

f.write("\n%s = [" % "roll")
for i in roll_arr:
    f.write("%s\n" % (roll_arr[i]))

f.write("];\n%s = [" % "pitch")
for i in pitch_arr:
    f.write("%s\n" % (pitch_arr[i]))

f.write("];\n%s = [" % "yaw")
for i in yaw_arr:
    f.write("%s\n" % (yaw_arr[i]))

f.write("];\n%s = [" % "ts_imu")
for i in timstamp_arr:
    f.write("%s\n" % (timstamp_arr[i]))

f.write("];")

f.close()