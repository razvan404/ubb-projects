function monteIntegral(g, a, b, M, n)
  hold on;

  interval_x = a:0.1:b;
  interval_y = 0:0.1:M;
  points_x = unifrnd(a, b, 1, n);
  points_y = unifrnd(0, M, 1, n);

  plot(interval_x, g(interval_x))
  plot(points_x, points_y, '*', 'MarkerSize', 2)

  approximate_integral = sum(points_y < g(points_x)) * (b - a) * M / n
  exact_integral = integral(g, a, b)
endfunction

