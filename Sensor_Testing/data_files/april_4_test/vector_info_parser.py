import sys
from decimal import Decimal

# $GNOST, (speed), (filtered), (lat), (long), (wind speed), (wind dir), (track), (boom angle), (timestamp), *(checksum) <LF>

# Loop thorugh all files passed by user
for i in range(1,len(sys.argv)):
	f = open(sys.argv[i])
	print("Opened argv number", i, sys.argv[i])
	n = open("parsed_" + str(i) + ".txt", "w+")

	track_arr = []
	speed_arr = []
	wind_s_arr = []
	wind_d_arr = []

	line_ct = 0
	for line in f:
		if line_ct == 0:
				line_ct+=1
				continue
		line_parsed = line.rstrip('\n').split(",")
		speed_arr.append(line_parsed[1])
		track_arr.append(line_parsed[7])
		wind_s_arr.append(line_parsed[5])
		wind_d_arr.append(line_parsed[6])

		line_ct+=1

	n.write("%s\n\n" % sys.argv[i])
	n.write("TRACK: \n")
	for x in track_arr:
		n.write("%s " % x)

	n.write("\n\nSPEED: \n")
	for x in speed_arr:
		n.write("%s " % x)

	n.write("\n\nWIND DIR: \n")
	for x in wind_d_arr:
		n.write("%s " % x)

	n.write("\n\nWIND SPEED: \n")
	for x in wind_s_arr:
		n.write("%s " % x)
