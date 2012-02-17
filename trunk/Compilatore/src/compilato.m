function b = compilato(a)

s00=a(3:4,3:4);
o00=a(1:2,1:2);
s01=a(3:4,3:22);
o01=a(1:2,3:22);
s02=a(3:4,21:22);
o02=a(1:2,23:24);
s10=a(3:22,3:4);
o10=a(3:22,1:2);
s11=a(5:20,5:20);
o11=a(3:22,3:22);
s12=a(3:22,21:22);
o12=a(3:22,23:24);
s20=a(21:22,3:4);
o20=a(23:24,1:2);
s21=a(21:22,3:22);
o21=a(23:24,3:22);
s22=a(21:22,21:22);
o22=a(23:24,23:24);
for i0 = 1 : 2
	for i1 = 1 : 2
		s00_1(i0,i1) = funzione( s10(i0+2,i1+0),o01(i0+0,i1+1));
	end
end
for i0 = 1 : 2
	for i1 = 1 : 2
		s01_1(i0,i1) = funzione( s10(i0+2,i1+0),o01(i0+0,i1+1));
	end
	for i1 = 3 : 18
		s01_1(i0,i1) = funzione( s11(i0+0,i1-2),o01(i0+0,i1+1));
	end
	for i1 = 19 : 19
		s01_1(i0,i1) = funzione( s12(i0+2,i1-18),o01(i0+0,i1+1));
	end
	for i1 = 20 : 20
		s01_1(i0,i1) = funzione( s12(i0+2,i1-18),o02(i0+0,i1-19));
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s02_1(i0,i1) = funzione( s12(i0+2,i1+0),o01(i0+0,i1+19));
	end
	for i1 = 2 : 2
		s02_1(i0,i1) = funzione( s12(i0+2,i1+0),o02(i0+0,i1-1));
	end
end
for i0 = 1 : 2
	for i1 = 1 : 2
		s10_1(i0,i1) = funzione( s10(i0+2,i1+0),o01(i0+0,i1+1));
	end
end
for i0 = 3 : 4
	for i1 = 1 : 1
		s10_1(i0,i1) = funzione( s10(i0+2,i1+0),s10(i0-2,i1+1));
	end
	for i1 = 2 : 2
		s10_1(i0,i1) = funzione( s10(i0+2,i1+0),s01(i0-2,i1+1));
	end
end
for i0 = 5 : 16
	for i1 = 1 : 1
		s10_1(i0,i1) = funzione( s10(i0+2,i1+0),s10(i0-2,i1+1));
	end
	for i1 = 2 : 2
		s10_1(i0,i1) = funzione( s10(i0+2,i1+0),s11(i0-4,i1-1));
	end
end
for i0 = 17 : 18
	for i1 = 1 : 1
		s10_1(i0,i1) = funzione( s21(i0-16,i1+0),s10(i0-2,i1+1));
	end
	for i1 = 2 : 2
		s10_1(i0,i1) = funzione( s21(i0-16,i1+0),s11(i0-4,i1-1));
	end
end
for i0 = 19 : 20
	for i1 = 1 : 1
		s10_1(i0,i1) = funzione( o21(i0-18,i1+0),s10(i0-2,i1+1));
	end
	for i1 = 2 : 2
		s10_1(i0,i1) = funzione( o21(i0-18,i1+0),s11(i0-4,i1-1));
	end
end
for i0 = 1 : 2
	for i1 = 1 : 15
		s11_1(i0,i1) = funzione( s11(i0+2,i1+0),s01(i0+0,i1+3));
	end
	for i1 = 16 : 16
		s11_1(i0,i1) = funzione( s11(i0+2,i1+0),s12(i0+0,i1-15));
	end
end
for i0 = 3 : 14
	for i1 = 1 : 15
		s11_1(i0,i1) = funzione( s11(i0+2,i1+0),s11(i0-2,i1+1));
	end
	for i1 = 16 : 16
		s11_1(i0,i1) = funzione( s11(i0+2,i1+0),s12(i0+0,i1-15));
	end
end
for i0 = 15 : 16
	for i1 = 1 : 15
		s11_1(i0,i1) = funzione( s21(i0-14,i1+2),s11(i0-2,i1+1));
	end
	for i1 = 16 : 16
		s11_1(i0,i1) = funzione( s21(i0-14,i1+2),s12(i0+0,i1-15));
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s12_1(i0,i1) = funzione( s12(i0+2,i1+0),o01(i0+0,i1+19));
	end
	for i1 = 2 : 2
		s12_1(i0,i1) = funzione( s12(i0+2,i1+0),o02(i0+0,i1-1));
	end
end
for i0 = 3 : 16
	for i1 = 1 : 1
		s12_1(i0,i1) = funzione( s12(i0+2,i1+0),s12(i0-2,i1+1));
	end
	for i1 = 2 : 2
		s12_1(i0,i1) = funzione( s12(i0+2,i1+0),o12(i0-2,i1-1));
	end
end
for i0 = 17 : 18
	for i1 = 1 : 1
		s12_1(i0,i1) = funzione( s22(i0-16,i1+0),s12(i0-2,i1+1));
	end
	for i1 = 2 : 2
		s12_1(i0,i1) = funzione( s22(i0-16,i1+0),o12(i0-2,i1-1));
	end
end
for i0 = 19 : 20
	for i1 = 1 : 1
		s12_1(i0,i1) = funzione( o21(i0-18,i1+18),s12(i0-2,i1+1));
	end
	for i1 = 2 : 2
		s12_1(i0,i1) = funzione( o21(i0-18,i1+18),o12(i0-2,i1-1));
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s20_1(i0,i1) = funzione( o21(i0+0,i1+0),s10(i0+16,i1+1));
	end
	for i1 = 2 : 2
		s20_1(i0,i1) = funzione( o21(i0+0,i1+0),s11(i0+14,i1-1));
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s21_1(i0,i1) = funzione( o21(i0+0,i1+0),s10(i0+16,i1+1));
	end
	for i1 = 2 : 17
		s21_1(i0,i1) = funzione( o21(i0+0,i1+0),s11(i0+14,i1-1));
	end
	for i1 = 18 : 19
		s21_1(i0,i1) = funzione( o21(i0+0,i1+0),s12(i0+16,i1-17));
	end
	for i1 = 20 : 20
		s21_1(i0,i1) = funzione( o21(i0+0,i1+0),o12(i0+16,i1-19));
	end
end
for i0 = 1 : 2
	for i1 = 1 : 1
		s22_1(i0,i1) = funzione( o21(i0+0,i1+18),s12(i0+16,i1+1));
	end
	for i1 = 2 : 2
		s22_1(i0,i1) = funzione( o21(i0+0,i1+18),o12(i0+16,i1-1));
	end
end
b(1:2,1:2) = s00_1 ;
b(1:2,1:20) = s01_1 ;
b(1:2,19:20) = s02_1 ;
b(1:20,1:2) = s10_1 ;
b(3:18,3:18) = s11_1 ;
b(1:20,19:20) = s12_1 ;
b(19:20,1:2) = s20_1 ;
b(19:20,1:20) = s21_1 ;
b(19:20,19:20) = s22_1 ;
