function inaltimi(n)
  clf; grid on; hold on;
  miu = 165; #cm
  sigma = 10;
  heights = normrnd(miu, sigma, 1, n);
  norm_factor = 1.0 / ( (max(heights) - min(heights) ) / 10);
  hist(heights, 10, norm_factor);
  #bar(10, F1, 'hist', 'FaceColor', 'b');
  #bar(10, normpdf(120:200, miu, sigma), 'FaceColor', 'y');
  plot(120:200, normpdf(120:200, miu, sigma));
endfunction


