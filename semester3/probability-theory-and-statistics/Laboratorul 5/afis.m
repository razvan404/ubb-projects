function afis(lambda, N)
  X = -1 / lambda * log(1 - rand(1, N));
  VAL_MED_RAND = mean(X)
  DEV_STD_RAND = std(X)

  E = exprnd(1/lambda, N, 1);
  VAL_MED_EXPRND = mean(E)
  DEV_STD_EXPRND = std(E)
endfunction
