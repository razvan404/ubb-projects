function x0=init_newton_elem(n, a, b, alfa, beta)
    x=linspace(a, b, n+2);
    c=polyfit([a, b], [alfa, beta], 1);
    x0=polyval(c, x(2:end-1))';
end