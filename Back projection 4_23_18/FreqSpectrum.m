Freq = VarName1;
Freq (length(Freq))=[];
M = MLOG_ComponentA_Pos_1;
M(length(M))=[];
M = 10.^(M/20);
phase = PHAS_ComponentA_Pos_1;
phase(length(phase))=[];
phase = phase.*(pi/180);
c = 3e8;
x = M.*exp(1i*phase);

X = fft(x);
L = length(X);


% plot(Freq(1:L)/c,abs(X));
% plot((0:L-1)*(1/L),abs(X));
plot((0:L-1)*(pi/L),abs(X));

c = 3e8;
x = M.*exp(1i*phase);

X = fft(x);
L = length(X);


plot(Freq(1:L)/c,abs(X));
% plot((0:L-1)*(1/L),abs(X));
plot((0:L-1)*(pi/L),abs(X));

signal= [flipud(X(1:L/2-1));flipud(X(L/2:end))];
figure; clf;
plot((0:L-1)*(1/L),abs(signal));
