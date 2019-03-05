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
			there[lineDict[x][1]] = lineDict[x][2]
			hold = lineDict[x][2]
			while lineDict[x][2] == hold:
				if x+1 in lineDict:
					x+=1
				else:
					break
			continue
		else:
			back[lineDict[x][1]] = lineDict[x][2]
			hold = lineDict[x][2]
			while lineDict[x][2] == hold:
				if x+1 in lineDict:
					x+=1
				else:
					break
			continue

	avgd = {}

	for keyT in there:
		for keyB in back:
			if abs(Decimal(keyT) - Decimal(keyB)) < 0.5:
				#print("--THERE: ", Decimal(keyT), Decimal(there[keyT]))
				#print("--BACK: ", Decimal(keyB), Decimal(back[keyB]))
				avgd[str((Decimal(keyT) + Decimal(keyB))/2)] = str((Decimal(there[keyT]) + Decimal(back[keyB])) / 2)
				break;

	totErr = 0
	totCt = 0
	for k in avgd:
		if Decimal(avgd[k]) > 30:
			continue
		totErr += abs(Decimal(k) - Decimal(avgd[k]))
		totCt += 1
		#print("--GPS:", k," ANEMOM:", avgd[k])

	if totCt != 0:
		print("--Error Avg:", totErr / totCt)


	print("--There size", len(there))
	print("--Back size", len(back))

	f.close()