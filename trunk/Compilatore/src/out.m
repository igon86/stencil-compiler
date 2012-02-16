function b = compilato(a)

s00=a(3:4,3:4,);
o00=a(1:4,1:4,);
s01=a(3:4,3:13,);
o01=a(1:4,3:13,);
s02=a(3:4,12:13,);
o02=a(1:4,14:13,);
s10=a(3:13,3:4,);
o10=a(3:13,1:4,);
s11=a(5:15,5:15,);
o11=a(3:15,3:15,);
s12=a(3:13,12:13,);
o12=a(3:13,14:13,);
s20=a(12:13,3:4,);
o20=a(14:13,1:4,);
s21=a(12:13,3:13,);
o21=a(14:13,3:13,);
s22=a(12:13,12:13,);
o22=a(14:13,14:13,);
for i0 = 1 : 2
	for i1 = 1 : 2
		s00_1(i0,i1,) = funzione( s10(i0+2,i1+0),o01(i0+0,i1+1),);
	end
end
for i0 = 1 : 2
	for i1 = 1 : 2
		s01_1(i0,i1,) = funzione( s10(i0+2,i1+0),o01(i0+0,i1+1),);
	end
	for i1 = 3 : 9
		s01_1(i0,i1,) = funzione( s11(i0+0,i1-2),o01(i0+0,i1+1),);
	end
	for i1 = 10 : 10
		s01_1(i0,i1,) = funzione( s12(i0+2,i1-9),o01(i0+0,i1+1),);
	end
	for i1 = 11 : 11
		s01_1(i0,i1,) = funzione( s12(i0+2,i1-9),o02(i0+0,i1-10),);
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s02_1(i0,i1,) = funzione( s12(i0+2,i1+0),o01(i0+0,i1+10),);
	end
	for i1 = 2 : 2
		s02_1(i0,i1,) = funzione( s12(i0+2,i1+0),o02(i0+0,i1-1),);
	end
end
for i0 = 1 : 2
	for i1 = 1 : 2
		s10_1(i0,i1,) = funzione( s10(i0+2,i1+0),o01(i0+0,i1+1),);
	end
end
for i0 = 3 : 4
	for i1 = 1 : 1
		s10_1(i0,i1,) = funzione( s10(i0+2,i1+0),s10(i0-2,i1+1),);
	end
	for i1 = 2 : 2
		s10_1(i0,i1,) = funzione( s10(i0+2,i1+0),s01(i0-2,i1+1),);
	end
end
for i0 = 5 : 7
	for i1 = 1 : 1
		s10_1(i0,i1,) = funzione( s10(i0+2,i1+0),s10(i0-2,i1+1),);
	end
	for i1 = 2 : 2
		s10_1(i0,i1,) = funzione( s10(i0+2,i1+0),s11(i0-4,i1-1),);
	end
end
for i0 = 8 : 9
	for i1 = 1 : 1
		s10_1(i0,i1,) = funzione( s21(i0-7,i1+0),s10(i0-2,i1+1),);
	end
	for i1 = 2 : 2
		s10_1(i0,i1,) = funzione( s21(i0-7,i1+0),s11(i0-4,i1-1),);
	end
end
for i0 = 10 : 11
	for i1 = 1 : 1
		s10_1(i0,i1,) = funzione( o21(i0-9,i1+0),s10(i0-2,i1+1),);
	end
	for i1 = 2 : 2
		s10_1(i0,i1,) = funzione( o21(i0-9,i1+0),s11(i0-4,i1-1),);
	end
end
for i0 = 1 : 2
	for i1 = 1 : 6
		s11_1(i0,i1,) = funzione( s11(i0+2,i1+0),s01(i0+0,i1+3),);
	end
	for i1 = 7 : 7
		s11_1(i0,i1,) = funzione( s11(i0+2,i1+0),s12(i0+0,i1-6),);
	end
end
for i0 = 3 : 5
	for i1 = 1 : 6
		s11_1(i0,i1,) = funzione( s11(i0+2,i1+0),s11(i0-2,i1+1),);
	end
	for i1 = 7 : 7
		s11_1(i0,i1,) = funzione( s11(i0+2,i1+0),s12(i0+0,i1-6),);
	end
end
for i0 = 6 : 7
	for i1 = 1 : 6
		s11_1(i0,i1,) = funzione( s21(i0-5,i1+2),s11(i0-2,i1+1),);
	end
	for i1 = 7 : 7
		s11_1(i0,i1,) = funzione( s21(i0-5,i1+2),s12(i0+0,i1-6),);
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s12_1(i0,i1,) = funzione( s12(i0+2,i1+0),o01(i0+0,i1+10),);
	end
	for i1 = 2 : 2
		s12_1(i0,i1,) = funzione( s12(i0+2,i1+0),o02(i0+0,i1-1),);
	end
end
for i0 = 3 : 7
	for i1 = 1 : 1
		s12_1(i0,i1,) = funzione( s12(i0+2,i1+0),s12(i0-2,i1+1),);
	end
	for i1 = 2 : 2
		s12_1(i0,i1,) = funzione( s12(i0+2,i1+0),o12(i0-2,i1-1),);
	end
end
for i0 = 8 : 9
	for i1 = 1 : 1
		s12_1(i0,i1,) = funzione( s22(i0-7,i1+0),s12(i0-2,i1+1),);
	end
	for i1 = 2 : 2
		s12_1(i0,i1,) = funzione( s22(i0-7,i1+0),o12(i0-2,i1-1),);
	end
end
for i0 = 10 : 11
	for i1 = 1 : 1
		s12_1(i0,i1,) = funzione( o21(i0-9,i1+9),s12(i0-2,i1+1),);
	end
	for i1 = 2 : 2
		s12_1(i0,i1,) = funzione( o21(i0-9,i1+9),o12(i0-2,i1-1),);
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s20_1(i0,i1,) = funzione( o21(i0+0,i1+0),s10(i0+7,i1+1),);
	end
	for i1 = 2 : 2
		s20_1(i0,i1,) = funzione( o21(i0+0,i1+0),s11(i0+5,i1-1),);
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s21_1(i0,i1,) = funzione( o21(i0+0,i1+0),s10(i0+7,i1+1),);
	end
	for i1 = 2 : 8
		s21_1(i0,i1,) = funzione( o21(i0+0,i1+0),s11(i0+5,i1-1),);
	end
	for i1 = 9 : 10
		s21_1(i0,i1,) = funzione( o21(i0+0,i1+0),s12(i0+7,i1-8),);
	end
	for i1 = 11 : 11
		s21_1(i0,i1,) = funzione( o21(i0+0,i1+0),o12(i0+7,i1-10),);
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s22_1(i0,i1,) = funzione( o21(i0+0,i1+9),s12(i0+7,i1+1),);
	end
	for i1 = 2 : 2
		s22_1(i0,i1,) = funzione( o21(i0+0,i1+9),o12(i0+7,i1-1),);
	end
end
b(3:4,3:4,) = s00_1 ;
b(3:4,3:13,) = s01_1 ;
b(3:4,12:13,) = s02_1 ;
b(3:13,3:4,) = s10_1 ;
b(5:15,5:15,) = s11_1 ;
b(3:13,12:13,) = s12_1 ;
b(12:13,3:4,) = s20_1 ;
b(12:13,3:13,) = s21_1 ;
b(12:13,12:13,) = s22_1 ;
