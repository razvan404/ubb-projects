nodes=[0 3 5 8 13];
values=[0  225  383  623  993];
der_values=[75  77   80   74   72];
t=linspace(0,13,1001);
[distance,speed]=Hermite_interp(nodes,values,der_values,t);
[distance2,speed2]=piecewise_cubic_hermite(nodes,values,der_values,t);

clf; 
subplot(1,2,1)
hold on;axis square;
plot(t,distance,'b','LineWidth',3)
plot(t,distance2,'r','LineWidth',3)
plot(nodes,values,'or','MarkerSize',8,'MarkerFaceColor','r')
xlabel("time",'fontweight','bold');
ylabel("distance",'fontweight','bold');
grid on;set(gca,"fontsize", 15)

subplot(1,2,2)
hold on;axis square;
plot(t,speed,'b','LineWidth',3)
plot(t,speed2,'r','LineWidth',3)
plot(nodes,der_values,'or','MarkerSize',8,'MarkerFaceColor','r')
xlabel("time",'fontweight','bold');
ylabel("speed",'fontweight','bold');
grid on;set(gca,"fontsize", 15)