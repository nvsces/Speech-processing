clear all;
close all;

[x,fs]=audioread('doremi.wav');
x=x(:,1);

[x1,fs]=audioread('do.wav');
x1=x1(:,1);
[x2,fs]=audioread('re.wav');
x2=x2(:,1);
[x3,fs]=audioread('mi.wav');
x3=x3(:,1);
[x4,fs]=audioread('fa.wav');
x4=x4(:,1);
[x5,fs]=audioread('so.wav');
x5=x5(:,1);
[x6,fs]=audioread('lya.wav');
x6=x6(:,1);
[x7,fs]=audioread('si.wav');
x7=x7(:,1);

x=[x1; x2; x3; x4 ;x5; x6 ;x7];
ym={x1 x2 x3 x4 x5 x6 x7};

Nx = length(x);
nsc = floor(Nx/4.5);
nov = floor(nsc/2);
nff = max(256,2^nextpow2(nsc));

spectrogram(x,'yaxis');


for i=1:length(ym) 
    x=ym{i};
% ��������� wav-����, ���������� ������� ������

% x - ������� �������� �������

% fs - ������� �������������

nfft=1024;% ���������� ����� ���

window='hamming';% ��� ���� ����������� ���

nlap=0.75;% ���������� ����� ���������� (75%)

nlap = round(nlap*nfft);

nx=length(x);

nwin=nfft;

w=feval(window,nwin,'periodic');

x = x(:);

window = window(:);

% ������ �������� �������� �������

ncol = fix((nx-nlap)/(nwin-nlap));% ncol - ���������� ����������� ���

colindex = 1 + (0:(ncol-1))*(nwin-nlap);

rowindex = (1:nwin)';

% ������������ �������� �������
y = zeros(nwin,ncol);

y(:)=x( rowindex(:,ones(1,ncol)) + colindex(ones(nwin,1),:) -1 );

y = w(:,ones(1,ncol)).*y;

y = fft(y,nfft);% ��� �������� �������� �������

y2 = y;

% ������� ������ ����� �������

select = [1:nfft/2+1];

y = y(select,:);

[lll,ll]=size(y2);% ������� ������� ���

ll=round(ll/2)

%sm=ll;

% ��������� ������

r= ifft ( log(abs(y2)) );% �������� ��� �� ��������� ���

r=r(:,ll);% �������� ������ �� ������� �������

r1=r;% ��������� ������� ������� ��� ���������� �������

r1(1)=0;

r1(2)=0;

r(1:0.002*fs)=0;% ���������� �� ������� ���������� � ������� ������

ll=size(r);

lll=round(ll(1)/2);

ss = [1 : lll];

r = r(ss,:);% ������� ������ ����� �������

r1=r1(ss,:);

[f0m,T0]=max(r);% ���������� ��������� ���������� ���� �������

f0=1/(T0/fs)% �������� ������� ��������� ���� � ������
masf0(i)=f0;

if f0m<0.05 % ���� ��������� ���� ������� <0.05, ������� ������ - �� �����������

%  else masf0(i)=f0;
f0='������� �������������';

end

end

 figure; plot(masf0);


% ����������� ����������� ������� �������

% time=[1:length(r1)]'/fs;% ������� �������
% 
% figure ; plot(time,abs(r1));
% 
% xlabel('Time');