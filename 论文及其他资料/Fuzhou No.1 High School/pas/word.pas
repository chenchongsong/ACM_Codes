program word;
var s:ansistring;
    i,j,max,min:longint;
    c:char;
    a:array['a'..'z']of longint;
function pd(x:longint):boolean;
begin
  if (x=0) or (x=1) then exit(false);
  for i:=2 to trunc(sqrt(x)) do
    if x mod i=0 then exit(false);
  pd:=true;
end;
begin
  //assign(input,'word.in');
  //assign(output,'word.out');
  //reset(input);
  //rewrite(output);
  readln(s);
  for i:=1 to length(s) do
    inc(a[s[i]]);
  max:=0;
  min:=99999;
  for c:='a' to 'z' do
  begin
    if a[c]>max then max:=a[c];
    if (a[c]<min) and (a[c]>0) then min:=a[c];
  end;
  if pd(max-min) then
  begin
    writeln('Lucky Word');
    writeln(max-min);
  end
  else
  begin
    writeln('No Answer');
    writeln('0');
  end;
  //close(input);
  //close(output);
end.
