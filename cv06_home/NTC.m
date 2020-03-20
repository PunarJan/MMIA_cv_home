clear all;
close all;

filename = 'ntc.csv';
M = csvread(filename);

rk=M(:, 2); %rezistivity kohm
t=M(:, 1); %temperature degrees C

Vref=3.3; 
rf=10000;
rohm=rk*1000;

Vout=Vref*(rohm./(rohm+rf)); %ADC voltage [V]


ad=(1023/Vref)*Vout;
plot (ad, t)

p = polyfit(ad, t, 10);

ad2=0:1023;
h=polyval(p, ad2)';
t2 = round(h) 
hold on, plot(ad2, t2, 'r'); 

dlmwrite('data.dlm', t2'*10, ','); 