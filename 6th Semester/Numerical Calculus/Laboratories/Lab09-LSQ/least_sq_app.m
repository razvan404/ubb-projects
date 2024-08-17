function mcmmp_app_incomplet2(k)
    if nargin < 1, k=5; end
    clf; axis equal;axis([0 2 0 1]);
    xticks(0:0.2:2);yticks(0:0.2:1);
    grid on;hold on; set(gca,"fontsize", 15)
    
    i=1
    X = [];
    f = [];
    [x,y]=ginput(1)
    while ~isempty([x,y])
        X(end + 1) = x;
        f(end + 1) = y;
        plot(x,y,'*k','MarkerSize',10);
        text(x+0.02,y+0.02,num2str(i),'fontsize',13);
        i=i+1
        [x,y]=ginput(1)
    end
    coef = least_sq(X, f, k)
    div_interval = 0:0.01:2;
    plot(div_interval, polyval(coef, div_interval));
end