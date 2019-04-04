import sys
from decimal import Decimal

# $GNTST, (speed), (wind speed), (wind dir), (heading), (boom angle), (timestamp), *(checksum) <CR><LF>

# $GNOST, (speed), (filtered), (lat), (long), (wind speed), (wind dir), (track), (boom angle), (timestamp), *(checksum) <LF>
# 2 -> 5
# 3 -> 6
# track: 7

# Loop thorugh all files passed by user
for i in range(1,len(sys.argv)):
	f = open(sys.argv[i])
	print("Opened argv number", i, sys.argv[i])

	lineDict = {}
	there = {}
	back = {}

	# get file size and print to user for stats purposes
	t = 0
	for line in f:
		if t == 0:
			t+=1
			continue
		lineDict[t] = line.rstrip('\n').split(",")
		t+=1
	print("File size:", len(lineDict), "lines")

	# Add unique (defined by windSpeed) items to "there" array until turnaround point detected
	# after turnaround point detected, add unique items to "back" array instead
	midVal = "-1"
	for x in range(20, len(lineDict)-40):
		if midVal == "-1":
			midVal = lineDict[x][5]
			for y in range(x, x+20):
				if lineDict[x][5] != lineDict[y][5]:
					midVal = "-1"
					break;
		if lineDict[x][5] == midVal:
			continue
		if midVal == "-1":
			#there[lineDict[x][1]] = lineDict[x][2]
			hold = lineDict[x][1]
			tempT = 0
			tempC = 0
			while lineDict[x][1] == hold:
				if x+1 in lineDict and lineDict[x+1][1] == hold:
					x+=1
					tempC += 1
					tempT += Decimal(lineDict[x][5])
				else:
					tempC += 1
					tempT += Decimal(lineDict[x][5])
					there[lineDict[x][1]] = str(tempT / tempC)
					break
			continue
		else:
			#back[lineDict[x][1]] = lineDict[x][2]
			hold = lineDict[x][1]
			tempT = 0
			tempC = 0
			while lineDict[x][1] == hold:
				if x+1 in lineDict and lineDict[x+1][1] == hold:
					x+=1
					tempC += 1
					tempT += Decimal(lineDict[x][5])
				else:
					tempC += 1
					tempT += Decimal(lineDict[x][5])
					back[lineDict[x][1]] = str(tempT / tempC)
					break
			continue

	avgd = {}
	found = 0
	# loop through all items in "there"
	# for each, find all items in "back" within 0.1 gpsSpeed
	# if none within 0.1, try within 0.2, and then 0.3
	# after stuff is found, take average of all things found within tolerance to get average windSpeed for given gpsSpeed
	for keyT in there:
		found = 0
		numFound = 0
		tracking = 0
		for keyB in back:
			if abs(Decimal(keyT) - Decimal(keyB)) < 0.1:
				found = 1
				if tracking == 0:
					tracking = str((Decimal(keyT) + Decimal(keyB))/2)
				if tracking not in avgd:
					avgd[tracking] = 0
				avgd[tracking] += ((Decimal(there[keyT]) + Decimal(back[keyB])) / 2) / Decimal(1.15)
				numFound += 1
		if numFound > 0:
			avgd[tracking] /= numFound
		if found == 1:
			continue;
		numFound = 0
		tracking = 0
		for keyB in back:
			if abs(Decimal(keyT) - Decimal(keyB)) < 0.2:
				found = 1
				if tracking == 0:
					tracking = str((Decimal(keyT) + Decimal(keyB))/2)
				if tracking not in avgd:
					avgd[tracking] = 0
				avgd[tracking] += ((Decimal(there[keyT]) + Decimal(back[keyB])) / 2) / Decimal(1.15)
				numFound += 1
		if numFound > 0:
			avgd[tracking] /= numFound
		if found == 1:
			continue;
		numFound = 0
		tracking = 0
		for keyB in back:
			if abs(Decimal(keyT) - Decimal(keyB)) < 0.3:
				found = 1
				if tracking == 0:
					tracking = str((Decimal(keyT) + Decimal(keyB))/2)
				if tracking not in avgd:
					avgd[tracking] = 0
				avgd[tracking] += ((Decimal(there[keyT]) + Decimal(back[keyB])) / 2) / Decimal(1.15)
				numFound += 1
		if numFound > 0:
			avgd[tracking] /= numFound

	# Scaling range: 0.9-1.3
	# Complete average error checking with different scale values to find best fit scaling
	bestAvg = 5
	bestScale = 0
	bestMaxErr = -1;

	for z in range(0, 40):
		scaleFactor = Decimal(0.9) + Decimal(z / 100)

		# for every (gpsSpeed, avgWindSpeed) pair, calculate error
		# find the average and max of all these errors
		# if these errors are less than current best for given scaling factor, replace best scaling with this scaling 
		maxErr = 0	
		totErr = 0
		totCt = 0
		for k in avgd:
			if Decimal(scaleFactor)*Decimal(avgd[k]) > 20:
				continue
			totErr += abs(Decimal(k) - Decimal(scaleFactor)*Decimal(avgd[k]))
			totCt += 1
			if abs(Decimal(k) - Decimal(scaleFactor)*Decimal(avgd[k])) > maxErr:
				maxErr = abs(Decimal(k) - Decimal(scaleFactor)*Decimal(avgd[k]))

		if totCt != 0:
			if totErr / totCt < bestAvg:
				bestAvg = totErr / totCt
				bestScale = scaleFactor
				bestMaxErr = maxErr

	count = 0
	current = -1
	for x in range(1, len(lineDict)):
		TEMP = lineDict[x][9].split("*")
		if(current != TEMP[0]):
			current = TEMP[0]
			count += 1


	print("--Best ScaleFactor:", bestScale)
	print("--Avg Err w/ best ScaleFactor:", bestAvg)
	print("--MaxErr w/ best ScaleFactor:", bestMaxErr)
	print("--Avg Hz of packet:", len(lineDict)/count)

	f.close()