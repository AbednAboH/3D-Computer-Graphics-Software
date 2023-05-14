## Assighnment 1 report
i changed the resolution to 1440p /2k 
Creating the code for a>1 and 0<a<1 was easy and didn’t require anything special ,
Yet I had a small problem with it ,above the middle point everything worked fine, 
but below it i.e. when dx,dy where negative so I realized that I had to create a condition to always pick
the left most point as a starting point ,there were other solutions but this one was easier to maintain throughout 
the rest of the code . the condition was  : if(dx<0) then switch the points , which inspired me to create two ivec2
vectors to allow some flexibility , then the condition became : 
<img width="145" alt="sol" src="https://user-images.githubusercontent.com/92520508/138558539-c330b6dc-72e1-4eda-bbef-1d9b6db4c2cb.png">
as i used 2 new points so that i can switch whenever i want between the 2 values
The condition of a>1 was pretty standard so I added a flag named Roles and gave it a false value that becomes true if I’m in the condition of if (a>1),so that when I try to print a pixel i just choose between PutPixel(x,t,color) and PutPixel(y,x,color) using “roles” flag as an indicator to what condition I’m currently in . 
in both conditions (a<-1 and -1<a<0) reflect only required reflecting the value of dy to -dy which was handeld by a flag named reflect.
in (a<-1) i used both reflect and roles flags and it worked perfectly .
the circle's code was pretty standard ,i used the equations given in the assighnment and wrote them in code .
## final result's:
#circle :

![image](https://user-images.githubusercontent.com/92520508/138558691-db4bfce2-9bce-44ac-8669-bd408a5e65fe.png)
#bird +circle in the same code:

![image](https://user-images.githubusercontent.com/92520508/138558913-73d15a9d-0501-4c8a-8b5e-6886e39d8193.png)



