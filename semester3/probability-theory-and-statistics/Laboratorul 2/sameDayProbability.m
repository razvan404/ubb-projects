function sameDayProbability(n: int)
	count=0;
	for i=1:n
		days=randi(365, 23, 1);
		if length(unique(days)) != 23
			++count;
		endif
	endfor
	disp(count / n)
endfunction

sameDayProbability(50)
