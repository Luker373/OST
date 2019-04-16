import sys, math


# $GNOST, (speed), (filtered), (lat), (long), (wind speed), (wind dir), (track), (boom angle), (timestamp), *(checksum) <LF>

# Loop thorugh all files passed by user
for i in range(1,len(sys.argv)):
	f = open(sys.argv[i])
	print("Opened argv number", i, sys.argv[i])
	n = open("parsed_" + str(i) + ".txt", "w+")
	v = open("vecs_" + sys.argv[i], "w+")

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

	# For writing parsed data to a file
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

	# Processing of parsed data
	boatWindVec = [[0 for x in range(2)] for y in range(2)] 
	appWindVec = [[0 for x in range(2)] for y in range(2)]
	trueWindVec = [[0 for x in range(2)] for y in range(2)]
	appWindHeading = -1;
	appWindSpeed = -1;
	XYangle = -1
	trueWindHeading = -1

	# apprent : what the boat sees
	# true : nonmoving vector


	for x in range(0, len(track_arr)):
		if(float(track_arr[x]) < 0 or float(track_arr[x]) > 360):
			continue
		if(float(wind_s_arr[x]) < 0 or float(wind_s_arr[x]) > 30):
			continue

		# setBoatWindVec
		boatWindVec[0][0] = float(speed_arr[x]) * math.sin(math.pi * float(track_arr[x]) / 180)
		boatWindVec[1][0] = float(speed_arr[x]) * math.cos(math.pi * float(track_arr[x]) / 180)

		#setAppWindVec
		appWindHeading = (int(float(track_arr[x])) + int(float(wind_d_arr[x]))) % 360
		appWindVec[0][0] = float(wind_s_arr[x]) * math.sin(math.pi * appWindHeading / 180)
		appWindVec[1][0] = float(wind_s_arr[x]) * math.cos(math.pi * appWindHeading / 180)
		appWindSpeed = math.sqrt(appWindVec[0][0] * appWindVec[0][0] + appWindVec[1][0] * appWindVec[1][0])

		#setTrueWindVec
		trueWindVec[0][0] = appWindVec[0][0] - boatWindVec[0][0]
		trueWindVec[1][0] = appWindVec[1][0] - boatWindVec[1][0]
		trueWindSpeed = math.sqrt(trueWindVec[0][0] * trueWindVec[0][0] + trueWindVec[1][0] * trueWindVec[1][0])
		XYangle = math.atan2(trueWindVec[1][0], trueWindVec[0][0])
		XYangle = 180 * XYangle / math.pi
		if (XYangle >= 0 and XYangle < 90):
			trueWindHeading = (90 - XYangle)
		elif (XYangle > 90 and XYangle < 180):
			trueWindHeading = 360.0 + (90 - XYangle)
		elif (XYangle < 0):
			trueWindHeading = (-1.0 * (XYangle - 90))
		else:
			trueWindHeading = -1

		v.write("boat_s: %s  track: %s\nwind_s: %s  wind_dir: %s\n" % (speed_arr[x], track_arr[x], wind_s_arr[x], wind_d_arr[x]))
		v.write("app_wind_s: %s  app_wind_dir: %s\n" % (appWindSpeed, appWindHeading))
		v.write("true_wind_s: %s  true_wind_dir: %s\n\n" % (trueWindSpeed, trueWindHeading))
    
