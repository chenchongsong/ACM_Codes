var i,j,k,l,m,n,sum:integer;
begin
  readln(n);
  for i:=1 to 5 do
   for j:=1 to 5 do
    for k:=1 to 5 do
     for l:=1 to 5 do
      for m:=1 to 5 do
    if (i<>j) and (j<>k) and (k<>l) and (l<>m) and (i<>k) and (i<>l)
    and (i<>m)and (j<>l)and (j<>m)and (k<>m)
    then
      if (m=1) or(m=3) or (m=5) then
        if ((i+j+k) mod i=0) and ((j+k+l) mod j=0) and ((k+l+m) mod k=0)
         then begin
            writeln(i,j,k,l,m);
            inc(sum);
            end;
   writeln(sum);
  end.
