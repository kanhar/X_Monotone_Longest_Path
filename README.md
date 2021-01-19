X_Monotone_Longest_Path
=======================

Find the x-monotone longest path given a set of points. X monotone longest path is a path that moves only in the x axis, increasing as it progresses. Similar to this: http://en.wikipedia.org/wiki/Longest_increasing_subsequence

Test Case
=======================
```
[0,600]x[0,400]
S (20,40) (100,50)
S (50,30) (100,200)
S (10,100) (200,70)
S (10,300) (300,370)
S (50,5) (70,290)
S (60,390) (80,100)
```

Output

```
Searching for Intersection Points
****************************************************************************************** 
P4(10,100)
P6(10,300)
P0(20,40)
P2(50,30)
P8(50,5)
P15(52,37)
P13(52,44)
P12(54,44)
P17(56,92)
P10(60,390)
P18(65,313)
P14(67,90)
P19(68,267)
P9(70,290)
P16(78,125)
P11(80,100)
P1(100,50)
P3(100,200)
P5(200,70)
P7(300,370)
Algorithm applied, all points maintain the length of the longest path ending at that point 
****************************************************************************************** 

Line 	Start 	End				Intersection Information
Line 0	P0(20,40)	P1(100,50)		 DIST: 80.6226	P12(54,44), P13(52,44), 
Line 1	P2(50,30)	P3(100,200)		 DIST: 177.2	P12(54,44), P14(67,90), P15(52,37), P16(78,125), 
Line 2	P4(10,100)	P5(200,70)		 DIST: 192.354	P14(67,90), P17(56,92), 
Line 3	P6(10,300)	P7(300,370)		 DIST: 298.329	P18(65,313), 
Line 4	P8(50,5)	P9(70,290)		 DIST: 285.701	P13(52,44), P15(52,37), P17(56,92), P19(68,267), 
Line 5	P10(60,390)	P11(80,100)		 DIST: 290.689	P16(78,125), P18(65,313), P19(68,267), 

#	Point 		Last	LongestPath
0	P4(10,100)		LastPath:-1	length:0
1	P6(10,300)		LastPath:-1	length:0
2	P0(20,40)		LastPath:-1	length:0
3	P2(50,30)		LastPath:-1	length:0
4	P8(50,5)		LastPath:-1	length:0
5	P15(52,37)		LastPath:2	length:177
6	P13(52,44)		LastPath:0	length:80
7	P12(54,44)		LastPath:13	length:82
8	P17(56,92)		LastPath:4	length:192
9	P10(60,390)		LastPath:-1	length:0
10	P18(65,313)		LastPath:6	length:298
11	P14(67,90)		LastPath:15	length:232
12	P19(68,267)		LastPath:15	length:407
13	P9(70,290)		LastPath:15	length:430
14	P16(78,125)		LastPath:14	length:268
15	P11(80,100)		LastPath:19	length:574
16	P1(100,50)		LastPath:12	length:128
17	P3(100,200)		LastPath:15	length:347
18	P5(200,70)		LastPath:14	length:366
19	P7(300,370)		LastPath:18	length:540

Highest Value is Ending with Path 11,19,15,2,
P11(80,100)		LastPath:19	length:574
P19(68,267)		LastPath:15	length:407
P15(52,37)		LastPath:2	length:177
P2(50,30)		LastPath:-1	length:0
Connected to X server  :0.0
Width 1280, Height 1024, Screen Number 0
```
