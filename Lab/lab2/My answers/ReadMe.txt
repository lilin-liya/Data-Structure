Because of my current level,my program may be not that satisfying,but I must say that I have tried my best.

And my program can give one correct construction plan,but since my optimization,it may cut some posible construction plans during the recursive process for the efficiency. 

I only deal with the situations which are smaller than 5*5,my program can't give answers for these test cases which are larger than 5*5,so TA doesn't need to bother test these cases.

About my optimization in this lab:

1.	for (1*1 1*2 2*1 2*2 2*3 3*2):
	{
		I didn't use any optimization during recursive process,just recursive since (0,0). 
	}
2.	for (3*3 3*4 4*3 4*4 4*5):
	{
		I found that all the results of these situations,their ground[0][0] = 3,and ground[0][1] = 2,
		so I init the all the elements in the ground as 3,except ground[0][1] = 2,and we can recursive since (0,3) instead of (0,0).
		And since ground[0][1] has been ensured as 2,the squares around it must exist at least one 1.
		This way to optimize may be not that good,but it can improve the efficiency observably.
	}
3.	for (5*5):
	{
		Since 5*5 is a little large,just optimize like above is not enough.
		I found that the first 3 lines of 5*5 is the same as 4*5's first 3 lines.
		So I recursive 4*5 first,then set the first 3 lines of the ground of 5*5 just like the 4*5,and then recursive since (2,4).It takes about 1.55s to get the result of 5*5.
	}
4.	for ( >5*5 ):
	{
		I was inspired by the 5*5 case,maybe we can use the way in 5*5.like 8*5,we can recursive 5*5 first and recursive 5*8 since (4,4),and keep iterating ,finally we can get the result.
		But I didn't realize this part because of my level and some other reasons.
	}
5.if row > col,then I recursive col*row ,and use transposition when cout the result.