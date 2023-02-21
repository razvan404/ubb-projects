function sangvin(X, P, N)
    clf; grid on; hold on;
    rand_values = rand(1, N);
    pseudo_population = zeros(1, N);
    for i=1:N
      crt_index = 1;
      crt_sum = 0;
      while crt_sum + P(crt_index) < rand_values(i)
        crt_sum += P(crt_index);
        crt_index++;
      endwhile
      pseudo_population(i) = X(crt_index);
    endfor
    n = length(X);
    random_population = randsample(X, N, replacement=true, P);

    PSEUDO_HIST=hist(pseudo_population, 1:n);
    RANDOM_HIST=hist(random_population, 1:n);

    bar(1:n,PSEUDO_HIST/N,'hist','FaceColor','b');
    bar(1:n,RANDOM_HIST/N,'hist','FaceColor','y');
    legend('populatia pseudo-aleatoare','populatia aleatoare');
    set(findobj('type','patch'),'facealpha',0.5);
    xlim([0 n+1]);
endfunction
