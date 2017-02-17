 program P1314;
   var len,f:array[-10..1000000] of longint;
       n,i,min,max,st,fi:longint;

   procedure init;
     begin
       readln(n);
       min:=maxlongint;
       for i:=1 to n do
         begin
           readln(st,fi);
           if len[fi]<st then len[fi]:=st;
           if fi>max then max:=fi;
          if  fi<min then min:=fi;
         end;
     end;

   procedure main;
     begin
       for i:=min to max do
         begin
          f[i]:=f[i-1];
           if f[len[i]]+1>f[i] then f[i]:=f[len[i]]+1;
         end;
       writeln(f[max]);
     end;

   begin
     init;
     main;
   end.
