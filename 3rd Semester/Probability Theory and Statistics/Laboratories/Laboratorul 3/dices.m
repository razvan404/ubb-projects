pkg load statistics;

function test()
	clf; grid on; hold on;
	p=1/5; n=10; m=20;
	x=binornd(n,p,1,m);
	N=hist(x,0:n);
	bar(0:n,N/m,'hist','FaceColor','b');
	bar(0:n,binopdf(0:n,n,p),'FaceColor','y');
	legend('probabilitatile estimate','probabilitatile teroretice');
	set(findobj('type','patch'),'facealpha',0.7);xlim([-1 n+1]);
endfunction

function dices()
	disp("Probabilitate estimata: ");
	disp(sum(binornd(5,1/3,1,5000)==2)/5000);
	disp("Probabilitate teoretica: ");
	disp(binopdf(0:5,5,1/3)(2));
endfunction