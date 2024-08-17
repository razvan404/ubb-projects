x=1900:10:2010;
f=[75995 91972 105710 123200 131670 150700 ...
179320 203210 226510 249630 281420 308790];
clf; hold on; grid on; xticks(x);
plot(x,f,'*');
time=1900:2010;
plot(time,polyval(least_sq(x,f,3),time));
c=least_sq(x,log(f),1);
plot(time,exp(c(1)*time+c(2)));