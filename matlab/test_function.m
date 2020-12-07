% clear all;

Ypower=Ypower(:,1);
Xpow=Ypower;
Ylog   = interp1(linSpacedFrequency,Ypower,logSpacedFrequency);

in=my_interp(linSpacedFrequency,Ypower,logSpacedFrequency);

figure; plot(in);
hold on; plot(Ylog,'r--');
hold off;

a=Ylog./logSpacedFrequency;
% z=my_logspace(1,124,50);
% 
% r=logspace(1,124,50);

% z=my_linspace(2,96,43);
% r=linspace(2,96,43);
% 
% 
% figure ; plot(z);

% dz=my_diff(z);
% dr=diff(r);


% fq=find(q<1,1,'last');
% fm=my_find_last_less(q,1);

function in=my_interp(linear,Y,logspace)

n=length(logspace)
m=1;
for k=1:n

    while(linear(m)<logspace(k))
       m=m+1; 
    end
    
    in(k)=Y(m-1)+(Y(m)-Y(m-1))*(logspace(k)-linear(m-1))/(linear(m)-linear(m-1));
    
end


end



function out=my_find_last_less(x,m)

n=length(x);
temp=0;

for i=1:n
    if (x(i)<m)
       temp=i;  
    end
end

out=temp;

end


function out=my_diff(x)

n=length(x)-1;

for i=1:n
    out(i)=x(i+1)-x(i);
end

end

function out=my_logspace(x1,x2,n)

helpMas=my_linspace(x1,x2,n);

for i=1:n
    out(i)=10^helpMas(i);
end

end

function out=my_linspace(x1,x2,n)


n1=n-1;
step=(x2-x1)/n1;

   for i=0:n1
     out(i+1)=x1+step*i; 
   end   
end