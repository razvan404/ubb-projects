function A = ShortVander(x, n)
    x=x(:);
    A=ones(length(x), n);
    for i=2:n
        A(:,i)=x.*A(:, i-1);
    end
end