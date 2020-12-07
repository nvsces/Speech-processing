clear all;
close all;

[x1,fs]=audioread('mifasol.wav');
x1=x1(:,1);

  x1=x1(100001:105001);



% f1 = pitch(x1,fs);figure; plot(f1);
% t
f2=main_pef(x1,fs);
figure; plot(f2);

% fileID = fopen('data.txt','w');
% fprintf(fileID,'%f\n',x1);
% fclose(fileID);