clear all;
close all;

[x1,fs]=audioread('do.wav');
x1=x1(:,1);

f1 = pitch(x1,fs);figure; plot(f1);

f2=main_pef(x1,fs);figure; plot(f2);
