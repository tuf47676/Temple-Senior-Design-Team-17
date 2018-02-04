clear all; clc; tic
%%%%%%%%%%%%%%%%%%%%%%%%
%%%    MONOSTATIC    %%%
%%%%%%%%%%%%%%%%%%%%%%%%

%%%%%%%%%%%%%%%%% Frequency %%%%%%%%%%%%%%%%%
c = 3e8; %physconst('LightSpeed');
w_high = 2e9;
w_low = 1e9;
BW = w_high - w_low;
dw = BW/101;%frequency spacing
w = w_low:dw:w_high;%frequency array in Hz
w = 2*pi.*w;%frequency array in rad

%%%%%%%%%%%%%%%%%% Grid %%%%%%%%%%%%%%%%%%

% Grid size: 2.5m X 5m; 
% Pixel size: 5cm X 5cm
% max_y_range = c/(2*dw);%15.1395 meters
x_range = 2.5;%meters
y_range = 5;%meters
p = 0.05;%pixle 5X5cm

%%% Grid coordinates %%%%%%%
[Qx,Qy] = meshgrid(-x_range/2 : p : x_range/2 , 0 : p : y_range);

%%%%%%%%%% Introducing Target %%%%%%%%%%
% T[x-coordinate y-coordinate Reflectivity]
T = [51 26 1];
%T(2,:) = [80 35 1];

%%%%%%%%%%%%%%%%% Antena %%%%%%%%%%%%%%%%%
antenna_length = 1.5;%meters
antenna_spacing = c/(2*w_high);%meters
Ax = -antenna_length/2:antenna_spacing:antenna_length/2;%antenna_Xcoordinate
% antenna_Ycoordinate = 0;
% cross_range = antenna_spacing*2/1.5;
% down_range = c/(2*(w_high-w_low));
N = length(Ax);% Number of antennas

%%%%%%%%%%%% Back Projection %%%%%%%%%%%%%
%%% Obtaining delay for grid pixles as if there were targets there
dy = Qy;
for n = 1:N % n = Receivers
    dx = Qx - Ax(n);
    D(:,:,n) = sqrt(dx.^2+dy.^2)*(2/c);
end

%%% Calculating reflection
for n = 1:1:N
    temp = 0;
    for t = 1:size(T,1)
        temp = temp + T(t,3)*exp(-j*w'*D(T(t,1),T(t,2),n));
    end 
    Rt(:,n) = zeros(size(temp));
    Rt(:,n) = Rt(:,n) + temp;
    D_temp = D(:,:,n);
    D_temp = D_temp(:)';
    Rn(:,:,n) = exp(j*w'*D_temp);% w/o target
end

for q = 1:numel(Qx)
    I(q) = 0;
    for k=1:length(w)
        for n = 1:N
            I(q) = I(q)+Rt(k,n).*Rn(k,q,n);
        end
    end
end
I = reshape(I,size(Qx));

% Alining Delays and obtaining image array 
% for k=1:length(w)
%     for n=1:N
%         I(k,:,n) = Rt(k,n).*Rn(k,:,n);
%     end
% end
% 
% I = sum(I,3);% Summing over n
% I = sum(I);  % Summing over k
I = reshape(I,size(Qx));

% In = sum(In,3);
% In = sum(In);
% In = reshape(In,size(dx));

figure(1)
Imag = abs(I);
Imax = max(max(Imag));
Inorm = Imag./Imax;
contour3(Qx,Qy,20*log10(Inorm),1000)

figure (2)
imagesc(Qx(1,:),Qy(1,:),20*log10(Inorm))
% hold on
% plot(Ax,0,'--rs','LineWidth',2,...
%     'MarkerEdgeColor','k',...
%     'MarkerFaceColor','g',...
%     'MarkerSize',10)
toc