
windSpeed = filloutliers(windSpeed, 'nearest');
windDeg = filloutliers(windDeg, 'nearest');

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

trueWindSpeed = filloutliers(trueWindSpeed, 'previous');
trueWindHeading = atan2(trueWindY, trueWindX)*180/3.1415;

if (trueWindX < 0)
    trueWindHeading = trueWindHeading + 180;
end

trueWindHeading = mod((360 - (trueWindHeading - 90)), 360);

%%%%
disc_wind_s = zeros(1,4);
pos = zeros(1,4);
corres_boat_s = zeros(1,4);
%%%%

j = 1;
for i = 1:length(trueWindSpeed)
    if (trueWindSpeed(i) > 5 && trueWindSpeed(i) <= 5.1)
        disc_wind_s(j, 4) = i;
        j = j+1;
    end        
end
%sz = size(disc_wind_s, 1)
%for i = 1:5
    for j = 1:size(disc_wind_s, 1)
       pos(j,4) = mod(trueWindHeading(disc_wind_s(j,4)) - track(disc_wind_s(j,4)), 360);
       corres_boat_s(j,4) = boatSpeed(disc_wind_s(j,4));       
    end    
%end

figure(100)
polarscatter(pos(:,4), corres_boat_s(:,4))
hold on

test = mod(-350, 360)
% cant get this to work well.
%trueWindHeading = filloutliers(trueWindSpeed, 'next','movmean', 500);

disp(mean(trueWindHeading));
mean(trueWindSpeed)

