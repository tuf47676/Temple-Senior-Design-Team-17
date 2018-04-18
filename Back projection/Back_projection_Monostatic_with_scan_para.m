clear all;clc;
Antenna_width_cm = (148-64)/14
X_Stop_cm = 106-64
X_Start_cm = -X_Stop_cm
X_coordinate_cm = X_Start_cm:Antenna_width_cm:X_Stop_cm
X_coordinate_meters = X_coordinate_cm/100

clear all;clc;
cd 'C:\Users\Sivan\Dropbox\Spring18\SDII\Scan'
PC = 'Sivan';%'tug27939'; %

%% Number of antenna positions:
NumOfAntennaPos = 51;
for s = 1:2
    if s == 1
        scan_folder = 'SCAN_EMPTY5';
        ScanFolder = ['C:\Users\' PC '\Dropbox\Spring18\SDII\Scan\' scan_folder];
        [Freq, Settings, Mag_log, Phase_degrees, AntennaXY] = ...
            ScanData(ScanFolder,NumOfAntennaPos);
        
        Mag_empty = 10.^(Mag_log/20);
        Phase_rad_empty = Phase_degrees.*(pi/180);
        
    else
        scan_folder = 'SCAN_OBJECTs5';
        ScanFolder = ['C:\Users\' PC '\Dropbox\Spring18\SDII\Scan\' scan_folder];
        [Freq, Settings, Mag_log, Phase_degrees, AntennaXY] = ...
            ScanData(ScanFolder,NumOfAntennaPos);
        
        Mag_target = 10.^(Mag_log/20);
        Phase_rad_target = Phase_degrees.*(pi/180);
    end
end

if size(Phase_rad_empty,1) ~= size(Phase_rad_target,1)
    if size(Phase_rad_empty,1) > size(Phase_rad_target,1)
        Phase_rad_empty(size(Phase_rad_empty,1),:) = [];
        Mag_empty(size(Phase_rad_empty,1),:) = [];
        Freq(size(Phase_rad_empty,1),:) = [];
    elseif size(Phase_rad_empty,1) < size(Phase_rad_target,1)
        Phase_rad_target(size(Phase_rad_target,1),:) = [];
        Mag_target(size(Phase_rad_target,1),:) = [];
        Freq(size(Phase_rad_target,1),:) = [];
    end
end

R_empty = Mag_empty.*exp(-j*Phase_rad_empty);
R_target = Mag_target.*exp(-j*Phase_rad_target);

% R_scan = R_empty;
R_scan = R_target - R_empty;

%% Collecting Data From Scan
% X_start_cm = Settings{20,2};%cm
% X_stop_cm  = Settings{21,2};%cm
% X_Points = Settings{22,2};
% Y_start_cm = Settings{23,2};%cm
% Y_stop_cm  = Settings{24,2};%cm
% Y_Points = Settings{25,2};

X_start = (Settings{20,2}-106)/100;%meters
X_stop  = (Settings{21,2}-106)/100;%meters
X_Points = Settings{22,2};
Y_start = Settings{23,2}/100;%meters
Y_stop  = Settings{24,2}/100;%meters
Y_Points = Settings{25,2};

%%%%%%%%%%%%%%%%% Frequency %%%%%%%%%%%%%%%%%
c = 3e8; %physconst('LightSpeed');
w_high = Freq(length(Freq));%3e9;
w_low = Freq(1);%2e9;
BW = w_high - w_low;%Bandwidth
% dw = BW/(length(Freq));%BW/(length(Freq)-1);%frequency spacing
w = Freq;%w_low:dw:w_high;%frequency array in Hz
w = 2*pi.*w;%frequency array in rad
%%
%%%%%%%%%%%%%%%%%% Grid %%%%%%%%%%%%%%%%%%
% max_y_range = c/(2*dw);%15.1395 meters
x_range = 4.36;%meters
y_range = 3.16;%meters
p = 0.05;%pixle 5X5cm

%%% Grid coordinates %%%%%%%
[Qx,Qy] = meshgrid(-x_range/2 : p : x_range/2 , 0 : p : y_range);
grid = Qx;       % 1st layer - x-coord
grid(:,:,2) = Qy;% 2nd layer - y-coord
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%%%%%%%%%%%%%%%%% Antena %%%%%%%%%%%%%%%%%
antenna_width = X_stop-X_start;%1;%meters
antenna_Xspacing = 0.06;%antenna_width/X_Points;%c/(2*w_high);%meters
antenna_Xcoordinate = -antenna_width/2:antenna_Xspacing:antenna_width/2;%Txs
% antenna_Xcoordinate = linspace(-antenna_width/2,antenna_width/2,X_Points);
%antenna_length = Y_stop-Y_start;
%antenna_Yspacing = antenna_length/Y_Points;
antenna_Ycoordinate = 0;%-antenna_hight/2:antenna_Yspacing:antenna_hight/2;%Txs;
N = X_Points;%length(antenna_Xcoordinate);% Number of antenna positions


% cross_range = antenna_spacing*2/1.5;
% down_range = c/(2*(w_high-w_low));


%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%
%%%%%%%%%%%% Back Projection %%%%%%%%%%%%%
%% Obtaining delay for grid pixles as if there were targets there
for n=1:N % n = antenna location
    dx = Qx - antenna_Xcoordinate(n);
    dy = Qy;
    % D: Time it takes a signal to travel from the Nth antenna to each
    % pixle in the grid and come back
    D(:,:,n) = 2.*(sqrt(dx.^2+dy.^2)./c);%Unit: seconds
% end
%% Calculating reflection/reference signal
% for n = 1:1:N
    D_temp = D(:,:,n);
    D_temp = D_temp(:)';
    Rn(:,:,n) = exp(j*w*D_temp);
end
%% Constructing Image
for q = 1:numel(Qx)
    I(q) = 0;
    for k=1:length(w)
        for n = 1:N
            I(q) = I(q)+R_scan(k,n)*Rn(k,q,n);
        end
    end
end
I = reshape(I,size(Qx));
%%
figure(1)
Imag = abs(I);
Imax = max(max(Imag));
Inorm = Imag./Imax;
contour3(Qx,Qy,20*log10(Inorm),1000)
caxis([-35 0])
% hold on
% plot(antenna_Xcoordinate,0,'--rd','LineWidth',2,...
%     'MarkerEdgeColor','k',...
%     'MarkerFaceColor','r',...
%     'MarkerSize',10)

figure (2)
imagesc(Qx(1,:),Qy(:,1),20*log10(Inorm))
hold on
plot(antenna_Xcoordinate,0,'--rd','LineWidth',2,...
    'MarkerEdgeColor','k',...
    'MarkerFaceColor','r',...
    'MarkerSize',10)
caxis([-35 0])
toc