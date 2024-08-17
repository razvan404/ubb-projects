function pb1
    disp('Hilbert')
    for n=10:15
        cond(hilb(n))
    end
    disp('Vandermond_a')
    for n=10:15
        cond(vander(linspace(-1,1,n)),1)
    end
    disp('Vandermond_b')
    for n=10:15
        cond(vander(1./(1:n)),1)
    end
end
