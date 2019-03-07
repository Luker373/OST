import sys
from decimal import Decimal

for i in range(1,len(sys.argv)):
	f = open(sys.argv[i])
	print("Opened argv number", i, sys.argv[i])

	lineDict = {}
	there = {}
	back = {}

	t = 0
	for line in f:
		lineDict[t] = line.rstrip('\n').split(",")
		t+=1
	print("File size:", len(lineDict), "lines")

	midVal = "-1"
	for x in range(20, len(lineDict)-40):
		if midVal == "-1":
			midVal = lineDict[x][2]
			for y in range(x, x+20):
				if lineDict[x][2] != lineDict[y][2]:
					midVal = "-1"
					break;
		if lineDict[x][2] == midVal:
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
					tempT += Decimal(lineDict[x][2])
				else:
					tempC += 1
					tempT += Decimal(lineDict[x][2])
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
					tempT += Decimal(lineDict[x][2])
				else:
					tempC += 1
					tempT += Decimal(lineDict[x][2])
					back[lineDict[x][1]] = str(tempT / tempC)
					break
			continue

	bestAvg = 5
	bestScale = 0
	for z in range(0, 40):
		scaleFactor = Decimal(0.9) + Decimal(z / 100)
		avgd = {}
		found = 0
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
					avgd[tracking] += Decimal(scaleFactor*((Decimal(there[keyT]) + Decimal(back[keyB])) / 2) / Decimal(1.15))
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
					avgd[tracking] += Decimal(scaleFactor*((Decimal(there[keyT]) + Decimal(back[keyB])) / 2) / Decimal(1.15))
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
					avgd[tracking] += Decimal(scaleFactor*((Decimal(there[keyT]) + Decimal(back[keyB])) / 2) / Decimal(1.15))
					numFound += 1
			if numFound > 0:
				avgd[tracking] /= numFound
		maxErr = 0
		totErr = 0
		totCt = 0

		for k in avgd:
			if Decimal(avgd[k]) > 30:
				#print("OUTLIER: ", avgd[k])
				continue
			totErr += abs(Decimal(k) - Decimal(avgd[k]))
			totCt += 1
			if abs(Decimal(k) - Decimal(avgd[k])) > maxErr:
				maxErr = abs(Decimal(k) - Decimal(avgd[k])) 
			#print("--GPS:", k," ANEMOM:", avgd[k])

		if totCt != 0:
			if totErr / totCt < bestAvg:
				bestAvg = totErr / totCt
				bestScale = scaleFactor
				bestMaxErr = maxErr
			#print("--Error Avg:", totErr / totCt)
			#print("--Error Max:", maxErr)

	print("--Best ScaleFactor:", bestScale)
	print("--Avg Err w/ best ScaleFactor:", bestAvg)
	print("--MaxErr w/ best ScaleFactor:", bestMaxErr)

	#print("--There size", len(there))
	#print("--Back size", len(back))

	f.close()