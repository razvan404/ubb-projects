pkg load statistics;
clf; grid on; hold on;

N = 500;

X = [-2, -1, -1, -1, -1, 1, 1, 1, 2, 2];
# Y ~ Unif[-1, 4]

valuesX = X(randi(10, 1, N));
valuesY = unifrnd(-1, 4, 1, N);
valuesU = valuesX.^3 - valuesY.^3;

#a)
hist(valuesU, 20, 20 / (max(valuesU) - min(valuesU)))

#b)
disp("Aproximarea P(U < 0):")
disp(sum(valuesU < 0) / length(valuesU))
disp("Aproximarea valoarii medie al lui U:")
disp(mean(valuesU))
disp ("Aproximarea variantei lui U:")
disp(var(valuesU))

#c)
disp("Valoarea medie teoretica a lui X^3:")
disp(mean(X.^3))
