function ret=pointsInCircle(X, Y)
	if X.^2 + Y.^2 <= 1
		ret=1;
	else
		ret=0;
	endif
endfunction

function squareFrequency(N)
	clf
	hold on
	axis square
	title("Problema 2");
	rect=rectangle("Position", [-1, -1, 2, 2]);
	set(rect, "FaceColor", [0.9, 0.9, 0.9]);

	coords=randi(1001, 2, N);
	coords-=501;
	coords/=500;
	
	inCircle=0;
	closerToCenter=0;
	coolAngles=0;

	coordsInCircle=[];
	coordsCloserToCenter=[];
	coordsCoolAngles=[];

	for i=1:N
		if pointsInCircle(coords(1, i), coords(2, i)) == 1
			++inCircle;
			coordsInCircle(1, end + 1) = coords(1, i);
			coordsInCircle(2, end) = coords(2, i);
		endif
		
		if abs(coords(1, i)) + abs(coords(2, i)) <= 1
			++closerToCenter;
			coordsCloserToCenter(1, end + 1) = coords(1, i);
			coordsCloserToCenter(2, end) = coords(2, i);
		endif
		
		if pointsInCircle(coords(1, i) - 1, coords(2, i)) == 1 || pointsInCircle(coords(1, i) + 1, coords(2, i)) == 1
			if pointsInCircle(coords(1, i), coords(2, i) - 1) == 1 || pointsInCircle(coords(1, i), coords(2, i) + 1) == 1
				++coolAngles;
				coordsCoolAngles(1, end + 1) = coords(1, i);
				coordsCoolAngles(2, end) = coords(2, i);
			endif
		endif
	endfor

	disp("Probability in circle: "), disp(inCircle/N)
	scatter(coordsInCircle(1, :), coordsInCircle(2, :), "filled")

	disp("Probability to be closer to center: "), disp(closerToCenter/N)
	scatter(coordsCloserToCenter(1, :), coordsCloserToCenter(2, :), "filled")

	disp("Probability to make cool angles with the sides: "), disp(coolAngles/N)
	scatter(coordsCoolAngles(1, :), coordsCoolAngles(2, :), "filled")
endfunction