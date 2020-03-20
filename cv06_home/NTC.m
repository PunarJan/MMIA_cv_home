filename = 'ntc.csv';
M = csvread(filename)

ad=M(:, 2);
t=M(:, 1);

p = polyfit(ad, t, 10);

plot (ad, t)

ad2=0:1023;
t2 = round(polyval(p, ad2)); 
hold on, plot(ad2, t2, 'r'); 

dlmwrite('data.dlm', t2*10, ','); 
