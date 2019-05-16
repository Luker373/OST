# Python code for wrapping anemometer value - to be converted to C
# Luke H - 5/15/2019

# arr is example input from anemometer
arr = [355, 350, 40, 180, 350, 20]
# res is the result of math to keep track of a wrapping anemom value
# *****res is also the value array that will have moving average performed on it*****
res = [0] * len(arr)
# resMod is an example showing that the input can be backed out still when needed
resMod = [0] * len(arr)

# meat and potatoes 
for x in range(0, len(arr)):
	if x == 0:
		res[x] = arr[x]
		continue
	if arr[x] < 50 and arr[x-1] > 300:
		res[x] = res[x-1] + (360 - arr[x-1]) + arr[x]
		continue
	if arr[x] > 300 and arr[x-1] < 50:
		res[x] = res[x-1] - (360 - arr[x] + arr[x-1])
		continue
	res[x] = (res[x-1] - (arr[x-1] - arr[x]))

for x in range(0, len(arr)):
	resMod[x] = res[x] % 360
print("arr: ", arr)
print("res: ", res)
print("resMod: ", resMod)
