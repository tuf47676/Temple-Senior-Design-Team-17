M = Trace1Location6{:,1};
M = 10.^(M/20);
phase = Trace1Location6{:,1};
phase = phase.*(pi/180);

x = M.*exp(1i*phase);

X = fft(x);
L= length(X);

plot((0:L-1)*(pi/L),abs(X));

signal= [flipud(X(1:L/2-1));flipud(X(L/2:end))];
figure; clf;
plot((0:L-1)*(pi/L),abs(signal));
