function E=sir
  m=1;
  while 1/factorial(m+1)>eps/2
    m=m+1;
  end
  E=0;
  while m>1
    E=1/m-1/m*E;
    m=m-1;
  end
  E=1/E;% trebuie returnat e, iar E1=1/e
end
