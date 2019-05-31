5/31/19
if running data_process_luke.m add 

%x = j:i:k 
timeStamp = [0:1:length(boatSpeed)-1]';
%timeSec = [0:1/12:length(boatSpeed)/12-1/12]';
timeMinutes = [0:12*60:length(boatSpeed)]';

to the raw data file for the timeStamp variable to exist. .py parsers do not add such

polar_speed_3.m used to make polar speed plots of raw data.

see SAMPLING VARS
plot all samples. change vars?
choose best sample for butterfly
calc average based on dTheta thresh
plot polar


