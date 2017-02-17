program p1479;
var s,ss:ansistring;
    b:array[0..1000000]of boolean;
    i,j,ans,x,p:longint;
begin
  readln(s);
  x:=6;
  if length(s)<x then x:=length(s);
  fillchar(b,sizeof(b),false);
  for i:=1 to x do
  begin
    for j:=1 to length(s)-i+1 do
    begin
      ss:=copy(s,j,i);
      val(ss,p);
      b[p]:=true;
    end;
  end;
  for i:=1 to 100000 do
    if (not b[i]) then begin
      writeln(i);
      halt;
    end;
end.
