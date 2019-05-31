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
    
% cant get this to work well.
%trueWindHeading = filloutliers(trueWindSpeed, 'next','movmean', 500);

disp(mean(trueWindHeading));

%boat data
figure(1)
subplot(2,1,1)
plot(timeStamp, boatSpeed);
xticks(0:12*60:length(boatSpeed));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
xlabel('Time [minutes]')
ylabel('Speed [knots]')
title('Boat Speed')
grid on

subplot(2,1,2)
plot(timeStamp, track);
xticks(0:12*60:length(track));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
xlabel('Time [minutes]')
ylabel('Boat Heading[deg]')
title('Boat Heading')
grid on
sgtitle('Boat(Wind) Speed and Heading (from GPS)')

%true wind data
figure(2)
subplot(2,1,1)
plot(timeStamp, trueWindSpeed);
xticks(0:12*60:length(trueWindSpeed));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
xlabel('Time [minutes]')
ylabel('TrueWind Speed[kn]')
grid on
title('True Wind Speed')

subplot(2,1,2)
plot(timeStamp, trueWindHeading);
grid on
xticks(0:12*60:length(trueWindHeading));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
xlabel('Time [minutes]')
ylabel('TrueWind Heading[deg]')
title('True Wind Heading')

sgtitle('True Wind Speed and Heading')

%app wind data
figure(3)
subplot(2,1,1)
plot(timeStamp, appWindSpeed);
grid on
xticks(0:12*60:length(appWindSpeed));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
xlabel('Time [minutes]')
ylabel('AppWind Speed[kn]')
title('App Wind Speed')

subplot(2,1,2)
plot(timeStamp, windSpeed);
grid on
xticks(0:12*60:length(windSpeed));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
xlabel('Time [minutes]')
ylabel('speeed')
title('Wind Speed')
sgtitle('Apparent Wind Speed and Heading')

%raw anem wind data
figure(4)
subplot(2,1,1)
plot(timeStamp, windSpeed);
grid on
xticks(0:12*60:length(windSpeed));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
xlabel('Time [minutes]')
ylabel('Wind Speed[kn]')
%ylim([0,15])
title('Anemometer Wind Speed')

subplot(2,1,2)
plot(timeStamp, windDeg);
grid on
xticks(0:12*60:length(windDeg));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
xlabel('Time [minutes]')
ylabel('[deg]')
title('Anemometer Wind Heading')
sgtitle('Anemometer Wind Speed and Heading')

%speed data
figure(5)
subplot(3,1,1)
plot(timeStamp, boatSpeed);
grid on
xticks(0:12*60:length(windSpeed));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
xlabel('Time [minutes]')
ylabel('Speed [kn]')
title('Boat Wind Speed')

subplot(3,1,2)
plot(timeStamp, trueWindSpeed);
grid on
xticks(0:12*60:length(windSpeed));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
xlabel('Time [minutes]')
ylabel('Speed [kn]')
title('True Wind Speed')

subplot(3,1,3)
plot(timeStamp, appWindSpeed);
grid on
xticks(0:12*60:length(windSpeed));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
xlabel('Time [minutes]')
ylabel('Speed [kn]')
title('App Wind Speed')

%Heading data
figure(6)
subplot(3,1,1)
plot(timeStamp, track);
grid on
xticks(0:12*60:length(appWindHeading));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
xlabel('Time [minutes]')
ylabel('Heading [deg]')
title('Boat Wind Heading')

subplot(3,1,2)
plot(timeStamp, trueWindHeading);
grid on
xticks(0:12*60:length(appWindHeading));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
xlabel('Time [minutes]')
ylabel('Heading [deg]')
title('True Wind Heading')

subplot(3,1,3)
plot(timeStamp, appWindHeading);
grid on
xticks(0:12*60:length(appWindHeading));
xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
xlabel('Time [minutes]')
ylabel('Heading [deg]')
title('App Wind Heading')

figure(9)
subplot(3,1,1)
startMinute = 1;
stopMinute = 3*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'0', '1', '2'})
xlim([startMinute,stopMinute])
grid minor

subplot(3,1,2)
startMinute = 3*12*60;
stopMinute = 6*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'3', '4', '5'})
xlim([startMinute,stopMinute])
grid minor

subplot(3,1,3)
startMinute = 6*12*60;
stopMinute = 9*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'6', '7', '8'})
xlim([startMinute,stopMinute])
grid minor

xlabel('Time [minutes]')
ylabel('[kn]')
sgtitle('Wind Speeds')
legend('True Wind Speed', 'Boat Wind Speed', 'Apparent Wind Speed')

figure(10)
subplot(3,1,1)
startMinute = 9*12*60;
stopMinute = 12*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'9', '10', '11'})
xlim([startMinute,stopMinute])
grid minor

subplot(3,1,2)
startMinute = 12*12*60;
stopMinute = 15*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'12', '13', '14'})
xlim([startMinute,stopMinute])
grid minor

subplot(3,1,3)
startMinute = 15*12*60;
stopMinute = 17.26*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'15', '16', '17'})
xlim([startMinute,stopMinute])
grid minor

xlabel('Time [minutes]')
ylabel('[deg]')
sgtitle('Wind Speeds')
legend('True Wind Speed', 'Boat Wind Speed', 'Apparent Wind Speed')

figure(11)
subplot(3,1,1)
startMinute = 1;
stopMinute = 3*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'0', '1', '2'})
xlim([startMinute,stopMinute])
grid minor

subplot(3,1,2)
startMinute = 3*12*60;
stopMinute = 6*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'3', '4', '5'})
xlim([startMinute,stopMinute])
grid minor

subplot(3,1,3)
startMinute = 6*12*60;
stopMinute = 9*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'6', '7', '8'})
xlim([startMinute,stopMinute])
grid minor

xlabel('Time [minutes]')
ylabel('[kn]')
sgtitle('Wind Headings')
legend('True Wind Heading', 'Boat Wind Heading', 'Apparent Wind Heading')

figure(12)
subplot(3,1,1)
startMinute = 9*12*60;
stopMinute = 12*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'9', '10', '11'})
xlim([startMinute,stopMinute])
grid minor

subplot(3,1,2)
startMinute = 12*12*60;
stopMinute = 15*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'12', '13', '14'})
xlim([startMinute,stopMinute])
grid minor

subplot(3,1,3)
startMinute = 15*12*60;
stopMinute = 17.26*12*60;
plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
hold on
plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
xticks(startMinute:12*60:stopMinute);
xticklabels({'15', '16', '17'})
xlim([startMinute,stopMinute])
grid minor

xlabel('Time [minutes]')
ylabel('[deg]')
sgtitle('Wind Headings')
legend('True Wind Heading', 'Boat Wind Heading', 'Apparent Wind Heading')
