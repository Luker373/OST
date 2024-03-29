% ctrl+r to add comments on highlighted section
% ctrl+t to remove comments on highlighted section

toggleFilter = 0;
deltaThresh = 2; % difference between two consecutive imu roll or pitch vals to trigger ignore
numIgnore = 2; % num seconds to ignore after deltaThresh occurs

% copying vars each time prevents having to re-run data files between tests
track2 = track;
windDeg2 = windDeg;
windSpeed2 = filloutliers(windSpeed, 'nearest');
boatSpeed2 = filloutliers(boatSpeed, 'nearest');
compass_deg2 = filloutliers(compass_deg, 'nearest');
compass_deg2 = movmean(compass_deg2, 20);

% windSpeed2 = movmean(windSpeed2, [99 0]);
% windDeg2 = movmean(windDeg2, [9 0]);

if toggleFilter == 1
    dataPtsPerSec = 4;
    coeff = ones(1, dataPtsPerSec)/dataPtsPerSec;
    %windSpeed2 = filter(coeff, 1, windSpeed2);
    %windSpeed2 = movmean(windSpeed2, 30);
    
    for c = 1:min([length(roll) length(pitch) length(ts_imu)] - numIgnore*8 + 1)
        if abs(roll(c)-roll(c+1))>deltaThresh || abs(pitch(c)-pitch(c+1))>deltaThresh
            A = find(ts_gnost >= ts_imu(c) & ts_gnost < ts_imu(c+1) + numIgnore);
            for r = 1:length(A)
                boatSpeed2(A(r)) = boatSpeed2(A(1));
                track2(A(r)) = track2(A(1));
                windSpeed2(A(r)) = windSpeed2(A(1));
                windDeg2(A(r)) = windDeg2(A(1));
            end
        end
    end
end

% timeStamp = 1:length(track);
% for c = 1:length(timeStamp)
%     timeStamp(c) = 60*(floor(ts_gnost(c)/100) - floor(ts_gnost(1)/100)) + mod(ts_gnost(c),60) - mod(ts_gnost(1),60);
% end

boatWindX = boatSpeed2 .* sin(track2 * 3.1415/180);
boatWindY = boatSpeed2 .* cos(track2 * 3.1415/180);

appWindHeading = mod((track2 + windDeg2), 360);

% noise reduction
% coeff = ones(1, 50)/50;
% appWindHeadingMvMean = filter(coeff, 1, appWindHeading);

appWindX = windSpeed2 .* sin(appWindHeading * 3.1415/180);
appWindY = windSpeed2 .* cos(appWindHeading * 3.1415/180);
appWind = [appWindX, appWindY];

appWindSpeed = zeros(length(boatSpeed2),1);
for c = 1:length(appWind)
    appWindSpeed(c) = sqrt(appWind(c,1)^2 + appWind(c,2)^2);
end

trueWindX = appWindX - boatWindX;
trueWindY = appWindY - boatWindY;
trueWind = [trueWindX, trueWindY];
trueWindSpeed = zeros(length(boatSpeed2),1);

for c = 1:length(boatSpeed2)
    trueWindSpeed(c) = sqrt(trueWind(c,1)^2 + trueWind(c,2)^2);
end

trueWindSpeed = filloutliers(trueWindSpeed, 'previous');
trueWindHeading = atan2(trueWindY, trueWindX)*180/3.1415;

if (trueWindX < 0)
    trueWindHeading = trueWindHeading + 180;
end

trueWindHeading = mod((360 - (trueWindHeading - 90)), 360); 

disp(mean(trueWindHeading));

%boat data
% figure(1)
% subplot(2,1,1)
% plot(timeStamp, boatSpeed2);
% xticks(0:12*60:length(boatSpeed2));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
% xlabel('Time [minutes]')
% ylabel('Speed [knots]')
% title('Boat Speed')
% grid on
% 
% subplot(2,1,2)
% plot(timeStamp, track2);
% xticks(0:12*60:length(track2));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
% xlabel('Time [minutes]')
% ylabel('Boat Heading[deg]')
% title('Boat Heading')
% grid on
% title('Boat(Wind) Speed and Heading (from GPS)')
% 
% %true wind data
% figure(2)
% subplot(2,1,1)
% plot(timeStamp, trueWindSpeed);
% xticks(0:12*60:length(trueWindSpeed));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
% xlabel('Time [minutes]')
% ylabel('TrueWind Speed[kn]')
% grid on
% title('True Wind Speed')
% 
% subplot(2,1,2)
% plot(timeStamp, trueWindHeading);
% grid on
% xticks(0:12*60:length(trueWindHeading));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
% xlabel('Time [minutes]')
% ylabel('TrueWind Heading[deg]')
% title('True Wind Heading')
% 
% title('True Wind Speed and Heading')
% 
% %app wind data
% figure(3)
% subplot(2,1,1)
% plot(timeStamp, appWindHeading);
% grid on
% xticks(0:12*60:length(appWindHeading));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
% xlabel('Time [minutes]')
% ylabel('AppWind Heading[deg]')
% title('App Wind Heading')
% 
% % subplot(2,1,2)
% % plot(timeStamp, appWindHeadingMvMean);
% % grid on
% % xticks(0:12*60:length(appWindHeadingMvMean));
% % xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
% % xlabel('Time [minutes]')
% % ylabel('[deg]')
% % title('App Wind Heading (Mv Mean)')
% 
% %raw anem wind data
% figure(4)
% subplot(2,1,1)
% plot(timeStamp, windSpeed2);
% grid on
% xticks(0:12*60:length(windSpeed2));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17'})
% xlabel('Time [minutes]')
% ylabel('Wind Speed[kn]')
% %ylim([0,15])
% title('Anemometer Wind Speed')
% 
% subplot(2,1,2)
% plot(timeStamp, windDeg2);
% grid on
% xticks(0:12*60:length(windDeg2));
% xticklabels({'1', '2', '3', '4', '5', '6', '7', '8', '9', '10', '11', '12', '13', '14', '15', '16', '17', '18' })
% xlabel('Time [minutes]')
% ylabel('[deg]')
% title('Anemometer Wind Heading')
% title('Anemometer Wind Speed and Heading')

%speed data
% figure(1)
% subplot(3,1,1)
% plot(timeStamp, boatSpeed2);
% grid on
% xticks(0:11*60*5:length(appWindHeading));
% xticklabels([0:5:length(appWindHeading)/11*60*5]);
% xlabel('Time [minutes]')
% ylabel('Speed [kn]')
% title('Boat Wind Speed')
% % 
% subplot(3,1,2)
% plot(timeStamp, trueWindSpeed);
% grid on
% xticks(0:11*60*5:length(appWindHeading));
% xticklabels([0:5:length(appWindHeading)/11*60*5]);
% xlabel('Time [minutes]')
% ylabel('Speed [kn]')
% title('True Wind Speed')
% % 
% subplot(3,1,3)
% plot(timeStamp, appWindSpeed);
% grid on
% xticks(0:11*60*5:length(appWindHeading));
% xticklabels([0:5:length(appWindHeading)/11*60*5]);
% xlabel('Time [minutes]')
% ylabel('Speed [kn]')
% title('App Wind Speed')

%Heading data
figure(2)
subplot(3,1,1)
plot(timeStamp(15000:40000), track2(15000:40000));
grid on
xticks(0:11*60*5:length(appWindHeading(15000:40000)));
xticklabels([0:5:length(appWindHeading(15000:40000))/11*60*5]);
xlabel('Time [minutes]')
ylabel('Heading [deg]')
title('Boat Wind Heading')

subplot(3,1,2)
plot(timeStamp(15000:40000), trueWindHeading(15000:40000));
grid on
xticks(0:11*60*5:length(appWindHeading(15000:40000)));
xticklabels([0:5:length(appWindHeading(15000:40000))/11*60*5]);
xlabel('Time [minutes]')
ylabel('Heading [deg]')
title('True Wind Heading')

subplot(3,1,3)
plot(timeStamp(15000:40000), appWindHeading(15000:40000));
grid on
xticks(0:11*60*5:length(appWindHeading(15000:40000)));
xticklabels([0:5:length(appWindHeading(15000:40000))/11*60*5]);
xlabel('Time [minutes]')
ylabel('Heading [deg]')
title('App Wind Heading')

figure(3)
subplot(2,1,1)
plot(timeStamp, track2);
hold on
plot(timeStamp, compass_deg2);
hold off
grid on
xticks(0:11*60*5:length(appWindHeading));
xticklabels([0:5:length(appWindHeading)/11*60*5]);
xlabel('Time [minutes]')
ylabel('GPS Heading [deg]')
title('GPS Heading v Time')

figure(3)
subplot(2,1,2)
plot(timeStamp, compass_deg2);
grid on
xticks(0:11*60*5:length(appWindHeading));
xticklabels([0:5:length(appWindHeading)/11*60*5]);
xlabel('Time [minutes]')
ylabel('Compass Heading [deg]')
title('Compass Heading v Time')


% figure(9)
% subplot(3,1,1)
% startMinute = 1;
% stopMinute = 3*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'0', '1', '2'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% subplot(3,1,2)
% startMinute = 3*12*60;
% stopMinute = 6*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'3', '4', '5'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% subplot(3,1,3)
% startMinute = 6*12*60;
% stopMinute = 9*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'6', '7', '8'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% xlabel('Time [minutes]')
% ylabel('[kn]')
% title('Wind Speeds')
% legend('True Wind Speed', 'Boat Wind Speed', 'Apparent Wind Speed')
% % 
% figure(10)
% subplot(3,1,1)
% startMinute = 9*12*60;
% stopMinute = 12*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'9', '10', '11'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% subplot(3,1,2)
% startMinute = 12*12*60;
% stopMinute = 15*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'12', '13', '14'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% subplot(3,1,3)
% startMinute = 15*12*60;
% stopMinute = 17.26*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindSpeed(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), boatSpeed(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindSpeed(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'15', '16', '17'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% xlabel('Time [minutes]')
% ylabel('[deg]')
% title('Wind Speeds')
% legend('True Wind Speed', 'Boat Wind Speed', 'Apparent Wind Speed')
% % 
% figure(11)
% subplot(3,1,1)
% startMinute = 1;
% stopMinute = 3*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'0', '1', '2'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% subplot(3,1,2)
% startMinute = 3*12*60;
% stopMinute = 6*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'3', '4', '5'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% subplot(3,1,3)
% startMinute = 6*12*60;
% stopMinute = 9*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'6', '7', '8'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% xlabel('Time [minutes]')
% ylabel('[kn]')
% title('Wind Headings')
% legend('True Wind Heading', 'Boat Wind Heading', 'Apparent Wind Heading')
% % 
% figure(12)
% subplot(3,1,1)
% startMinute = 9*12*60;
% stopMinute = 12*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'9', '10', '11'})
% xlim([startMinute,stopMinute])
% grid minor
% % 
% subplot(3,1,2)
% startMinute = 12*12*60;
% stopMinute = 15*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'12', '13', '14'})
% xlim([startMinute,stopMinute])
% grid minor
% 
% subplot(3,1,3)
% startMinute = 15*12*60;
% stopMinute = 17.26*12*60;
% plot(timeStamp(startMinute:stopMinute), trueWindHeading(startMinute:stopMinute));
% hold on
% plot(timeStamp(startMinute:stopMinute), track(startMinute:stopMinute));
% plot(timeStamp(startMinute:stopMinute), appWindHeading(startMinute:stopMinute));
% xticks(startMinute:12*60:stopMinute);
% xticklabels({'15', '16', '17'})
% xlim([startMinute,stopMinute])
% grid minor
% 
% xlabel('Time [minutes]')
% ylabel('[deg]')
% title('Wind Headings')
% legend('True Wind Heading', 'Boat Wind Heading', 'Apparent Wind Heading')
