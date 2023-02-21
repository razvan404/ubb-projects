function aranjamente(v, k)
	combs=nchoosek(v, k);
	for i=combs.'
		disp(perms(i))
	endfor
endfunction
