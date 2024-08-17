function b=num2float(x)
    if isa(x,'single')
        b=dec2bin(typecast(x,'uint32'),32);
        b=[b(1) ' ' b(2:9) ' ' b(10:end)];
    else
        b=dec2bin(typecast(x,'uint64'),64);
        b=[b(1) ' ' b(2:12) ' ' b(13:end)];
    end
end