var t,u,j,w:int64;
 function prime(x:longint):boolean;
 var z,y:int64;
     i:longint;
  begin
      z:=0;
    if x=1 then prime:=false;
   for i:=2 to trunc(sqrt(x)) do
     begin
      y:=x mod i;
      if (y=0) then z:=z+1;
     end;
   if (z=0) then prime:=true
   else prime:=false;
  end;
begin
 readln(t);
  w:=0;
  j:=2;
while (w=0) and (j<t div 2) do
 begin
  if prime(j) and prime(t-j) then
   begin
   write(j,' ',t-j);
    inc(w);
   end;
   inc(j);
 end;
end.


