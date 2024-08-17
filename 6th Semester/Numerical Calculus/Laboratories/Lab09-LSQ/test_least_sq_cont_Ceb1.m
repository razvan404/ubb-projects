f=@(t) sin(exp(t));
clf; hold on;
t=linspace(-1,1,1000);
plot(t,f(t),'displayname','f','linewidth',1.5);
for n=1:4
    y=least_sq_cont_Ceb1(f,n);
    plot(t,y(t),'displayname',strcat('y',num2str(n)),'linewidth',1.5);
end
legend;
set(gca,'fontsize',20)
