[top]
components : reception@Reception Barber
in : newcust next
out : cust finished 

Link : newcust newcust@reception
Link : out@Barber next@reception
Link : out@Barber finished
Link : cust@reception in@Barber

[reception]
numberofChairs : 8
preparationTime : 00:00:01:000
openingTime : 09:00:00:000
closingTime : 16:00:00:000

[Barber]
components : checkhair@Checkhair cuthair@Cuthair

in : in
out : out

Link : in cust@checkhair
Link : finished@checkhair out 
Link : cutcontinue@checkhair cutcontinue@cuthair 
Link : progress@cuthair progress@checkhair

[checkhair]
preparationTime : 00:00:09:000

[cuthair]
preparationTime : 00:00:11:000
 
