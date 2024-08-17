clf; axis equal;axis([0 2 0 1]); 
xticks(0:0.2:2);yticks(0:0.2:1); 
grid on;hold on; set(gca,"fontsize", 15)

i=1
[x,y]=ginput(1)
while ~isempty([x,y])
    plot(x,y,'*k','MarkerSize',10);
    text(x+0.02,y+0.02,num2str(i),'fontsize',13);
    i=i+1
    [x,y]=ginput(1)  
end