import sys

val = 0
idx = 0
window_size = 100
window_arr = [0] * window_size
w_sum = 0
summation = window_size*(window_size+1) / 2

for x in range(0,10000):
	idx = idx % window_size;
	w_sum = w_sum + val*1000*window_size
	for i in range(0, window_size):
	  w_sum = w_sum - window_arr[i]
	
	window_arr[idx] = (val*1000)
	idx = idx + 1
	val = val + 1
	print("Avg: ", w_sum / (1000*summation))