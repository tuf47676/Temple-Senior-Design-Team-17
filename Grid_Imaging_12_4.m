
clear all
clc
%%%%%%%%%%%%%%%%% Frequency %%%%%%%%%%%%%%%%%

w_high = 2e9;
w_low = 1e9;
BW = w_high - w_low;
dw = BW/101;%frequency spacing
w = w_low:dw:w_high;%frequency array in Hz
w = 2*pi.*w;%frequency array in rad

%%%%%%%%%%%%%%%%% Grid %%%%%%%%%%%%%%%%%

max_y_range = physconst('LightSpeed')/(2*dw);%15.1395 meters
x_range = 2.5;%meters
y_range = 5;%meters
p = 0.05;%pixle 5X5cm
%%% Grid coordinates
[Qx,Qy] = meshgrid(-x_range/2 : p : x_range/2 , 0 : p : y_range);
grid = zeros(size(Qx));
%%% Introducing a target
grid(51,26) = 5;
grid_size = size(grid);
R = grid_size(1);
C = grid_size(2);

%%%%%%%%%%%%%%%%% Antena %%%%%%%%%%%%%%%%%

antena_length = 1.5;%meters
antena_spacing = physconst('LightSpeed')/(2*w_high);%meters
antena_Xcoordinate = -antena_length/2:antena_spacing:antena_length/2;%Txs
antena_Ycoordinate = 0;

cross_range = antena_spacing*2/1.5;
down_range = physconst('LightSpeed')/(2*(w_high-w_low));

N = length(antena_Xcoordinate);%number of "antenas"

% z = 5;
% a = abs(randi(Res)-z);
% for m = a:a+z
%     for p = a:a+z
%         T(m,p) = randi(Res);
%     end
% end
% T =  zeros(length(Qx),length(Qy));%target matrix
%Res = 50;%255;%resolution
% T(randi(Res),randi(Res)) = 1;

D = zeros(size(grid));%delays
Return = zeros(length(Qx),length(Qy));%returned signal
I = zeros(length(Qx),length(Qy));%intensity at each pixel q

T = 1;%sec
t = 0:.01:T;
fc = 2*BW*2*pi;
%S = @(t)[ones(1,5),zeros(1,6)].*exp(j*fc.*t);
for n=1:1:N%antena location
    for r=1:1:R
        for c = 1:1:C
            dx = Qx(r,c) - antena_Xcoordinate(n);
            dy = Qy(r,c) - antena_Ycoordinate;
            D(r,c) = sqrt(dx^2+dy^2);%delay
            
            for k = 1:1:length(w)
                for t = 0:.01:T
                    R_temp = exp(j*fc.*t).*grid(r,c).*exp(-j*w(k)*D(r,c));
                    Return(r,c) = Return(r,c) + R_temp;
                end
            end
            
            for k = 1:1:length(w)
                I_temp = Return(r,c).*exp(j*w(k)*D(r,c));
                I(r,c) = I(r,c) + I_temp;
            end
        end
    end
    n
end

figure(1)
image(D)
figure(2)
subplot(1,2,1)
imagesc(grid)
subplot(1,2,2)
imagesc(20*log10(abs(I)))





% Grid - Q
% N tranmitters
% M recievers
% Resolution
% t_nm - delay - time it takes the signal to come back from transmission
% Calculate delay for all transit-recieved pairs
% k frequencies
% Recieved signal: Rnm(t) = Anm*S(T-t_nm) - Anm is the power
% time shifting I(q) = sum(k=0 to k-1)sum(n=0 to N-1)[Rk,n*exp(jW_k*t_q,n)]
% t_q,n = 2*||x_tn,x_q||_2

% spacing between antenas, d=< wavelenght/2

