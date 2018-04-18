% add check for units for frequancy and spacing

% Freq
% Settings
% Mag_log
% Phase_degrees
% AntennaXY

function [Freq, Settings, Mag_log, Phase_degrees, AntennaXY] =...
    ScanData(ScanFolder,NumOfAntennaPos)

addpath('C:\Users\Sivan\Dropbox\Spring18\SDII\Scan');
An = NumOfAntennaPos;
file_dir = ScanFolder;
cd (ScanFolder)

data_dirs = dir(file_dir);
file={};
for m=1:size(data_dirs,1)
    %     data_dirs(m)
    if data_dirs(m).bytes > 0%(data_dirs(m).isdir&&~strcmp( data_dirs(m).name,'..' ) && ~strcmp(data_dirs(m).name,'.'))
        file=[file;data_dirs(m).name];
    end
end

if length(file) > 9
    Rtotal = length(file);
    Rused = Rtotal-2;
    points = Rused/2;
    
    Usorted(:,1) = 1:points+2;
    Usorted(:,2) = [0 0 1 10:points 2:9]';
    
    x = 1:3;
    x2 = points+2-7 : points+2;
    x1 = 4:points+2-8;
    Sorted = [Usorted(x,:);Usorted(x2,:);Usorted(x1,:)];
    
    file2 = [file(x,:);file(x2,:);file(x1,:)];
    
    Usorted = [];
    Usorted(:,1) = 1:length(file);
    Usorted(:,2) = [0 0 1 10:points 2:9 1 10:points 2:9]';
    
    points = Rused/2;
    x = points+3;
    x2 = x2+points;
    x1 = x1+points;
    Sorted = [Sorted;Usorted(x,:);Usorted(x2,:);Usorted(x1,:)];
    
    n = Sorted(:,1);
else
    n = [0 0 1:9];
end

Mag_log = [];
Phase_degrees = [];
flag = 0;

for m = 1:length(n)
    if n(m) == 1
%         file (n(m))
        Freq = importFrequency(file{n(m)}, 1, An);
    elseif n(m) == 2
%         file (n(m))
        Settings = importSettings(file{n(m)}, 1, 25);
    elseif n(m) < x
%         file (n(m))
        [MLOG_ComponentA_Pos_1,~] = importTrace1(file{n(m)}, 2, An+1);
        while length(MLOG_ComponentA_Pos_1)<length(Mag_log)
%             n(m)
            MLOG_ComponentA_Pos_1 = [MLOG_ComponentA_Pos_1;0];
            flag = 1;
        end
        Mag_log = [Mag_log MLOG_ComponentA_Pos_1];
    else
%         file (n(m))
        [PHAS_ComponentA_Pos_1,~] = importPhase(file{n(m)}, 2, An+1);
        while length(PHAS_ComponentA_Pos_1)<length(Phase_degrees)
%             n(m)
            PHAS_ComponentA_Pos_1 = [PHAS_ComponentA_Pos_1;0];
            flag = 1;
        end
        Phase_degrees = [Phase_degrees PHAS_ComponentA_Pos_1];
    end
end
if flag == 1
    Mag_log(size(Mag_log,1)-1,:) = [];
    Phase_degrees(size(Mag_log,1)-1,:) = [];
%     Freq(size(Mag_log,1)-1,:) = [];
end

AntennaXY = Settings{20:25,2};%cm



% X_start_cm = Settings{20,2};%cm
% X_stop_cm  = Settings{21,2};%cm
% X_Points = Settings{22,2};
% Y_start_cm = Settings{23,2};%cm
% Y_stop_cm  = Settings{24,2};%cm
% Y_Points = Settings{25,2};
% Mag = 10.^(Mag_log/20);
% Phase_rad = Phase_degrees.*(pi/180);





end
