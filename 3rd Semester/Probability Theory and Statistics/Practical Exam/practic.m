pkg load statistics;
clf; grid on; hold on;

# X ~ N(-1, 4)
# Y ~ N(1, 4)

miuX = -1;
miuY = 1;
sigma = sqrt(4);
count = 1000;

valuesX = normrnd(miuX, sigma, 1, count);
valuesY = normrnd(miuY, sigma, 1, count);

miuXY = 0;
sigmaXY = sqrt(8);

valuesXY = valuesX + valuesY;

length(valuesXY)

left = min(valuesXY);
right = max(valuesXY);

beans = 15;

hist(valuesXY, beans, beans / (right - left))
plot(left:right, normpdf(left:right, miuXY, sigmaXY))

disp("Valoarea medie a lui X + Y:")
disp(mean(valuesXY))

disp("Varianta lui X + Y:")
disp(var(valuesXY))

disp("Probabilitatea in urma testarii a evenimentului P(|X + Y| < 1)")
disp(sum(abs(valuesXY) < 1) / count)

disp("Probabilitatea teoretica a evenimentului P(|X + Y| < 1)")
disp(normcdf(1, miuXY, sigmaXY) - normcdf(-1, miuXY, sigmaXY))
