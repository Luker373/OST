%windSpeed = filloutliers(windSpeed, 'nearest');
%windDeg = filloutliers(windDeg, 'nearest');

boatWindX = boatSpeed .* sin(track * 3.1415/180);
boatWindY = boatSpeed .* cos(track * 3.1415/180);

appWindHeading = mod((track + windDeg), 360);
appWindX = windSpeed .* sin(appWindHeading * 3.1415/180);
appWindY = windSpeed .* cos(appWindHeading * 3.1415/180);
appWind = [appWindX, appWindY];
appWindSpeed = zeros(length(boatSpeed),1);
for c = 1:length(appWind)
    %appWindSpeed(c, 1) = norm(appWind(c)); %norm fcn doesnt work?
    appWindSpeed(c) = sqrt(appWind(c,1)^2 + appWind(c,2)^2);
end

trueWindX = appWindX - boatWindX;
trueWindY = appWindY - boatWindY;
trueWind = [trueWindX, trueWindY];
trueWindSpeed = zeros(length(boatSpeed),1);
for c = 1:length(boatSpeed)
    trueWindSpeed(c) = sqrt(trueWind(c,1)^2 + trueWind(c,2)^2);
    %trueWindSpeed(c, 1) = norm(trueWind(c)); %norm fcn doesnt work?
end

%trueWindSpeed = filloutliers(trueWindSpeed, 'previous');
trueWindHeading = atan2(trueWindY, trueWindX)*180/3.1415;

if (trueWindX < 0)
    trueWindHeading = trueWindHeading + 180;
end

trueWindHeading = mod((360 - (trueWindHeading - 90)), 360); 
    
% cant get this to work well.
%trueWindHeading = filloutliers(trueWindSpeed, 'next','movmean', 500);

track3 = deg2rad(track);
track4 = rad2deg(unwrap(track3));
track5 =  wrapTo360(track4);

avgTWH = mean(trueWindHeading)
avgTWS = mean(trueWindSpeed)

%boat data
figure(1)
subplot(2,1,1)
plot(timeStamp, track4);
% xticks(0:12*60:length(boatSpeed));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
ax = gca;
xlabel('Time [minutes]')
ylabel('Speed [knots]')
yticka = -1080:90:360

ax.YTick = yticka;
ax.YTickLabel = {'360','270','180','90','360','270','180','90','360','270','180','90'};
title('Boat Speed')
grid on

subplot(2,1,2)
plot(timeStamp, track5);
% xticks(0:12*60:length(track));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
xlabel('Time [minutes]')
ylabel('Boat Heading[deg]')
title('Boat Heading')
grid on
% sgtitle('Boat(Wind) Speed and Heading (from GPS)')
