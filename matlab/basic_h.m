clear all;
close all;

[x,fs]=audioread('fa.wav');
y=x(:,1);

WindowLength=2048;

NFFT = 2^nextpow2(2*WindowLength-1);
nCol = size(y,2);

logSpacedFrequency = logspace(1,log10(min(fs/2-1,4000)),NFFT)';
linSpacedFrequency = linspace(0,fs/2,round(NFFT/2)+1)';

[aFilt,numToPad] = createPitchEstimationFilter_(logSpacedFrequency');

% Power spectrum
Y      = fft(y,NFFT);
Yhalf  = Y(1:(NFFT/2)+1,1:nCol);
Ypower = real(Yhalf.*conj(Yhalf));

% Interpolate onto log-frequency grid
Ylog   = interp1(linSpacedFrequency,Ypower,logSpacedFrequency);

Z   = [zeros(numToPad(1),size(Ylog,2),'like',y);Ylog];

% Cross correlation
m   = max(size(Z,1),size(aFilt,1));
mxl = m - 1;
m2  = min(2^nextpow2(2*m - 1), NFFT*4);

figure; plot(logSpacedFrequency,Ylog);
figure; plot(Z);

function [PEFFilter,PEFNumToPad] = createPitchEstimationFilter_(freq)
K     = 10;
gamma = 1.8;
num   = round(numel(freq)/2);
q     = logspace(log10(0.5),log10(K+0.5),num);
h     = 1./(gamma - cos(2*pi*q));

delta = diff([q(1),(q(1:end-1)+q(2:end))./2,q(end)]);
beta  = sum(h.*delta)/sum(delta);

PEFFilter   = (h - beta)';
PEFNumToPad = find(q<1,1,'last');
end