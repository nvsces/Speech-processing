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
% Открываем wav-файл, содержащий речевой сигнал

% x - отсчеты речевого сигнала

% fs - частота дискретизации

nfft=1024;% количество точек ДПФ

window='hamming';% вид окна сглаживания ДПФ

nlap=0.75;% количество точек перекрытия (75%)

nlap = round(nlap*nfft);

nx=length(x);

nwin=nfft;

w=feval(window,nwin,'periodic');

x = x(:);

window = window(:);

% Расчет размеров выходной матрицы

ncol = fix((nx-nlap)/(nwin-nlap));% ncol - количество необходимых ДПФ

colindex = 1 + (0:(ncol-1))*(nwin-nlap);

rowindex = (1:nwin)';

% Формирование выходной матрицы
y = zeros(nwin,ncol);

y(:)=x( rowindex(:,ones(1,ncol)) + colindex(ones(nwin,1),:) -1 );

y = w(:,ones(1,ncol)).*y;

y = fft(y,nfft);% ДПФ входного речевого сигнала

y2 = y;

% Убираем мнимую часть спектра

select = [1:nfft/2+1];

y = y(select,:);

[lll,ll]=size(y2);% Размеры матрицы ДПФ

ll=round(ll/2)

%sm=ll;

% Вычисляем кепстр

r= ifft ( log(abs(y2)) );% Обратное ДПФ от логарифма ДПФ

r=r(:,ll);% Выделяем кепстр на отрезке сигнала

r1=r;% Сохраняем отсчеты кепстра для построения графика

r1(1)=0;

r1(2)=0;

r(1:0.002*fs)=0;% Устранение из кепстра информации о речевом тракте

ll=size(r);

lll=round(ll(1)/2);

ss = [1 : lll];

r = r(ss,:);% Убираем мнимую часть кепстра

r1=r1(ss,:);

[f0m,T0]=max(r);% Определяем временную координату пика кепстра

f0=1/(T0/fs)% Значение частоты основного тона в Герцах
masf0(i)=f0;

if f0m<0.05 % если амплитуда пика кепстра <0.05, речевой сигнал - не вокализован

%  else masf0(i)=f0;
f0='сегмент невокализован';

end

end

 figure; plot(masf0);


% Графическое отображение кепстра сигнала

% time=[1:length(r1)]'/fs;% Отсчеты времени
% 
% figure ; plot(time,abs(r1));
% 
% xlabel('Time');