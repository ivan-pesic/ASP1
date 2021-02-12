program dzp1; //strogo donja trougaona matrica
uses crt ;

const MAX = 1000 ;

type
  type_arr = array[1..MAX] of integer ;

var
  arr : type_arr ;
  menu_choice, n, p_flag, d, p, arr_flag : integer ;

function menu() : integer ;
         var
           choice : integer ;
  begin
       writeln();
       writeln('MENI') ;
       writeln();
       writeln('1. Stvaranje matrice');
       writeln('2. Postavljanje podrazumevane vrednosti');
       writeln('3. Dohvatanje zadatog elementa');
       writeln('4. Postavljanje vrednosti zadatom elementu');
       writeln('5. Broj nepodrazumevanih vrednosti');
       writeln('6. Ispis matrice');
       writeln('7. Usteda memorijskog prostora');
       writeln('8. Brisanje matrice');
       writeln('9. Kraj rada');
       writeln();
       write('Izabrati zeljeni podmeni: ');
       readln( choice ) ;
               while ( ( choice < 1 ) or ( choice > 9 ) ) do
               begin
               write( 'Nekorektan unos. Unesite zeljeni podmeni ponovo: ' );
               readln(choice) ;
               end;
       clrscr;

       menu := choice ;
  end;
procedure menu1( var arr : type_arr ; var dim , len: integer) ;
var i, x, y : integer ;
begin
    writeln('Podmeni 1. Uneti dimenziju matrice: ') ;
    readln(dim) ;
    len := (dim*(dim-1) )div 2;

    while ( len > MAX ) do begin
      write('Preveliki unos. Uneti manji broj: ') ;
      readln(dim) ;
      len := dim*(dim-1)div 2;
    end;
    if(len<>0) then begin
    clrscr;
    x := 2 ;
    y := 1;
    for i:= 1 to len do begin
    write('A[',x,',',y,'] = ');
    readln(arr[i]);
    inc(y) ;
    if(y=x) then
    begin
        inc(x) ;
        y := 1 ;
    end;
    end;
    writeln('Nepodrazumevani elementi matrice su uneti.');
    end
    else writeln('Nema nepodrazumevanih elemenata matrice jer je ona dimenzije 1x1.');
end;

procedure menu2(var p:integer) ;
begin
    clrscr;
    write('Podmeni 2. Uneti podrazumevanu vrednost matrice: ') ;
    readln(p);
end;

procedure menu3(var arr : type_arr; n, d, p : integer ) ;
var i,j, elem : integer ;
  begin
      clrscr;
      writeln('Podmeni 3. Dohvatanje zadatog elementa.');
      write('Uneti koordinate elementa u matrici (i,j): ');
      readln(i, j);
      while(i>n) or (j>n) or (i<1) or (j<1) do begin
      writeln();
      write('Nekorektan unos. Ponovo uneti koordinate elementa u matrici (i,j): ');
      readln(i, j);
      end;
      if (i>j) then
      begin
         elem := ((i-2)*(i-1)) div 2 + j ;   //adresna funkcija
         writeln('Trazeni element je: ', arr[elem]);
      end
      else
         writeln('Trazeni element je podrazumevana vrednost, tj. ', p);

  end;

procedure menu4(var arr: type_arr; n, d, p : integer) ;
var i,j, elem, new : integer ;
  begin
      clrscr;

      writeln('Podmeni 4. Postavljanje vrednosti zadatom elementu.');
      write('Uneti koordinate elementa u matrici (i,j): ');
      readln(i, j);
      while(i>n) or (j>n) or (i<1) or (j<1) do begin
      writeln();
      write('Nekorektan unos. Ponovo uneti koordinate elementa u matrici (i,j): ');
      readln(i, j);
      end;
      if (i>j) then
      begin
         write('Uneti novu vrednost elementa A[',i,',',j,']: ');
         readln(new);
         elem := ((i-2)*(i-1)) div 2 + j ;
         arr[elem]:=new;
      end
      else
         writeln('Greska! Trazeni element je podrazumevana vrednost i ne moze se menjati. Moze se promeniti u podmeniju 2.');

  end;

procedure menu5(var arr: type_arr; d: integer) ;
var i, s : integer ;
  begin
      clrscr;
      s := 0 ;
      for i := 1 to d do begin
          if ( arr[i] <> p ) then
          inc(s) ;
      end;
     writeln('Podmeni 5. Broj nepodrazumevanih elemenata.');
     writeln('Broj nepodrazumevanih elemenata je: ',s);
  end;

procedure menu6(var arr : type_arr; n, d, p: integer) ;
var
  i, j, id,elem : integer ;
  begin
     id:=1;
     clrscr;
     writeln('Podmeni 6. Ispis matrice.');
     for i := 1 to n do begin
         for j:= 1 to i-1 do
         begin
         write(arr[id]:5);
         inc(id);
         end;

         for j:=1 to n-i+1 do
         write(p:5);
     {for j:=1 to n do begin
         if(j>=i) then write(p:5)
         else begin
         elem := ((i-2)*(i-1)) div 2 + j ;
         write(arr[elem]:5);
         end;
     end;
     }
         writeln();
     end;
  end;

procedure menu7(n,d:integer);
var
  usteda:real;
begin

     clrscr;
     writeln('Podmeni 7. Racunanje ustede memorije.');
     usteda := (n*n-(d+1))/(n*n);
     usteda := usteda * 100;
     writeln('Usteda prostora je: ',usteda:2:2,'%.');
end;

procedure menu8(var n, d, p, arr_flag, p_flag : integer) ;
begin
   clrscr;
   writeln('Podmeni 8. Brisanje matrice.');
   writeln('Matrica je obrisana.');
   n:= 0;
   d:= 0;
   arr_flag := 0;
   p_flag := 0;

end;
procedure check(arr_flag, p_flag : integer) ;
begin
   if(arr_flag = 0) then
   writeln('Greska! Nije uneta matrica.');
   if (p_flag = 0) then
   writeln('Greska! Nije uneta podrazumevana vrednost.');
end;
begin
     writeln('Zadatak 1. Operacije sa strogo donje trougaonom matricom.');

     n := 0 ;
     d := 0 ;
     p_flag := 0 ;
     arr_flag := 0 ;
     menu_choice := menu() ;
     while ( menu_choice <> 9 ) do begin

       if menu_choice = 1 then begin
          menu1(arr, n, d) ;
          arr_flag := 1 ;
       end
       else if menu_choice = 2 then begin
          menu2(p);
          p_flag := 1 ;
       end

       else if menu_choice = 3 then begin
          if(p_flag <> 0) and (arr_flag <> 0) then
              menu3(arr, n, d, p)
          else check(arr_flag, p_flag) ;
       end

       else if menu_choice = 4 then begin
       if(p_flag <> 0) and (arr_flag <> 0) then
              menu4(arr, n, d, p)
          else
              check(arr_flag, p_flag) ;
       end

       else if menu_choice = 5 then begin
       if(p_flag <> 0) and (arr_flag <> 0) then
              menu5(arr,d)
          else
              check(arr_flag, p_flag) ;
       end

       else if menu_choice = 6 then begin
       if(p_flag <> 0) and (arr_flag <> 0) then
              menu6(arr, n, d, p)
          else
              check(arr_flag, p_flag) ;
       end

       else if menu_choice = 7 then begin
       if(p_flag <> 0) and (arr_flag <> 0) then
              menu7(n,d)
          else
              check(arr_flag, p_flag) ;
       end

       else if menu_choice = 8 then begin
       if(p_flag <> 0) and (arr_flag <> 0) then
              menu8(n,d,p,arr_flag,p_flag)
          else
              check(arr_flag, p_flag) ;
       end ;

     writeln();
     menu_choice:=menu();

     end;
end.
