function pol_test(n)
    if nargin < 1, n=15; end
    clf; hold on;
    a=poly(1:n);
    for i=1:100
        ap=a+normrnd(0,10^-5,1,n+1);
        r=roots(ap);
        plot(real(r),imag(r),'.k');
    end
    plot(1:n,zeros(1,n),'or');
    xlim([0 n+1]);
end