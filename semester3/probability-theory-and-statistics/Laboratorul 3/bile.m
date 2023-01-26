pkg load statistics;

function out=eventA()
	count = 0;
	for step=1:1:5000
		if length(strfind(randsample('RRRRRBBBGG', 3, replacement=false), 'R')) > 0
			count++;
		endif
	endfor
	out=count / 5000;
endfunction

function out=eventAintersB()
	count = 0;
	for step=1:1:5000
		if length(strfind(randsample('RRRRRBBBGG', 3, replacement=false), 'R')) == 3
			count++;
		endif
	endfor
	out=count / 5000;
endfunction

function out=eventBrestrA()
	count1=eventA();
	count2=eventAintersB();
	out=count2 / count1;
endfunction

function out=eventBrestrAsimulation()
	count = 0;
	for step=1:1:5000
		if length(strfind(randsample('RRRRRBBBGG', 3, replacement=false), 'R')) > 0
			if length(strfind(randsample('RRRRRBBBGG', 3, replacement=false), 'R')) == 3
				count++;
			endif
		endif
	endfor
	out=count / 5000;
endfunction
