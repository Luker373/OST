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



%%%%
num_wS = 25;
base_wS = 1;
range_wS = 0.7;
disc_wind_s = zeros(1,num_wS);
pos = zeros(1,num_wS);
cor_boat_s = zeros(1,num_wS);
sample_wS_mids = zeros(1,num_wS);
%%%%

avg_disc_wS = zeros(1, num_wS);

for k = 1:num_wS   
    low = base_wS - range_wS;
    high = base_wS + range_wS;
    sample_wS_mids(1,k) = base_wS;
%     low = 10;
%     high = 10.5;
    sum = 0;
    j = 1;
    for i = 1:length(trueWindSpeed)
        if (trueWindSpeed(i) > low && trueWindSpeed(i) < high)
            disc_wind_s(j, k) = i;
            sum = sum + trueWindSpeed(i);
            j = j+1;
        end
    end
    avg_disc_wS(1,k) = sum/(j-1);
    base_wS = base_wS + range_wS;
end
sample_wS_mids;

% sz = size(disc_wind_s, 1)
% nnz(disc_wind_s(:,1))


for k = 1:num_wS    
    for j = 1:nnz(disc_wind_s(:,k))
       pos(j,k) = deg2rad(mod(trueWindHeading(disc_wind_s(j,k)) - track(disc_wind_s(j,k)), 360));
%        if(rad2deg(pos(j,k)) >= 180)
%             pos(j,k)  = -pos(j,k) + deg2rad(360);
% %            pos(j,k) = mod(pos(j,k) + 180 ,360);
%        end
%        if(rad2deg(pos(j,k)) >= 180)
%            pos(j,k)
%        end
       corres_boat_s(j,k) = boatSpeed(disc_wind_s(j,k));       
    end
end

% figure(2)
% pax = polaraxes;
% theta = 0:0.01:2*pi;
% rho = sin(2*theta).*cos(2*theta);
% polarplot(theta,rho)% 
% POLAR AXES PACKAGE NOT WORKING
% pax.ThetaDir = 'clockwise';
% pax.ThetaZeroLocation = 'top';
% pax.FontSize = 12;
% 

% length(corres_boat_s(1,:))
for k = 1:length(corres_boat_s(1,:))
    figure(3)
    subplot(5,5,k)
    polar(pos(:,k), corres_boat_s(:,k), 'r.')
    view([90 -90])
end


%sample trim of half the data
sample = 12;
pos2 = pos(:,sample);
corres_boat_s_2 = corres_boat_s(:,sample);

corres_boat_s_2(pos2 >= deg2rad(180)) = [];
pos2(pos2 >= deg2rad(180)) = [];
% for i=1:length(corres_boat_s_2)
    
dTheta = 10;
k = 1;
avg_cor_bS = zeros(1,180);
avg_theta = zeros(1,180);

for theta = 1:179
    j = 0;
    sum = 0;
    theta_sum =  0;
    low = theta - dTheta;
    high = theta + dTheta;    
    for i = 1:length(pos2)
        cur_pos = rad2deg(pos2(i));
        if(cur_pos > low && cur_pos < high)
            sum = sum + corres_boat_s_2(i);
            theta_sum = theta_sum + cur_pos;
            j = j + 1;
        end                        
    end
    k = k+1;
    avg_cor_bS(1,k) = sum/j;
    avg_theta(1,k) = theta_sum/j;
end
    phi = 1:180;
    figure(5)    
%     polar(pos2, corres_boat_s_2, 'g.')
%     hold on
%     polar(deg2rad(phi), avg_cor_bS(1,:), 'k.')
    polar(deg2rad(avg_theta(1,:)), avg_cor_bS(1,:), 'c.')
    view([90 -90])
%     title('Point of Sail vs Boat Speed')
grid on
hold on

curr_polar_wS = avg_disc_wS(1,sample)
avg_TW_heading = mean(trueWindHeading)
avg_TW_speed = mean(trueWindSpeed)

clear corres_boat_s
