## Assignment 1b 
## section 1 output :
v 0.00000 0.00000 0.00000
v 2.00000 0.00000 0.00000
v 2.00000 2.00000 0.00000
v 0.00000 2.00000 0.00000
v 0.00000 0.00000 -2.00000
v 2.00000 0.00000 -2.00000
v 2.00000 2.00000 -2.00000
v 0.00000 2.00000 -2.00000
v -0.60000 1.00000 -1.00000
v 1.00000 -0.60000 -1.00000
v 2.60000 1.00000 -1.00000
v 1.00000 2.60000 -1.00000
v 1.00000 1.00000 0.60000
v 1.00000 1.00000 -2.60000
f  1//1 13//2 4//1
f  4//3 13//4 3//3
f  3//5 13//6 2//5
f  2//7 13//8 1//7
f  4//1 9//9 1//1
f  8//10 9//11 4//10
f  5//12 9//13 8//12
f  1//14 9//15 5//14
f  5//16 14//17 6//16
f  8//12 14//18 5//12
f  7//19 14//20 8//19
f  6//21 14//22 7//21
f  3//23 11//24 7//23
f  2//5 11//25 3//5
f  6//26 11//27 2//26
f  7//21 11//28 6//21
f  3//3 12//29 4//3
f  4//10 12//30 8//10
f  8//19 12//31 7//19
f  7//23 12//32 3//23
f  1//7 10//33 2//7
f  2//26 10//34 6//26
f  6//16 10//35 5//16
f  5//14 10//36 1//14
## section 2 :
initialy ,i found the ratio between the height(half of it) of the screen and the longes point in the object(from 0) and then multiplied for each point,then i added half the screen width and height to every vertix. such that the x and y axis are exacly in the middle of the screen , then i calculated the greatest distance in the y axis from the positive and negative coardinates (greatest distance between 2 vertices on the y axis // i did  that for the x axis as well) ,calculated half of that distance and substracted it on every vertix so that it would be exactly in the middle (like the neer far approch ) . Basically i recentered the object.
in the rest of the report i used matrices to do these two operations.

## section 3 

![image](https://user-images.githubusercontent.com/92520508/140768339-b25a201c-d3f3-4244-90df-61d49f27d9ce.png)

## section 4
* let W denote the world transformation , O denotes the object transformations,and V each vertix in the Object , The matrices are calculated in the following order :
*  W=Wscale * Wrotate * Wtranslate 
*  O=Oscale * Orotate * Otranslate 
* final product is  W*O*v.
* in the code itself we use   V*O*W  because the product of a vertix and a victor in a class  is  victor * Matrix .

![image](https://user-images.githubusercontent.com/92520508/140769224-ec7afba1-0dda-4fdb-bfe4-a218db640cfa.png)
## Section 5 :
Translating in the model then rotating in the world frame :

![image](https://user-images.githubusercontent.com/92520508/140805661-43d4a6d2-c69c-41d3-bebc-0abf842acbf6.png)

Translating in the World frame then rotating in model frame (local frame ,i have only one model at a time):

![image](https://user-images.githubusercontent.com/92520508/140805467-3286f277-297e-4f65-bf94-5f08e86409ed.png)
* 

## Section6 :
i added an option to get new models into the scene ,on the top left click file->open-> "your object file" ,this option made checking so much easier 

## section 7 : 
* The functions added :
  *  ctrl+ w\a\s\d\q\e  rotates the picture , w/s rotate around x ,a/d around y ,q\e around z in local 
  *  ctrl+ double right click scales the picture down in local
  *  ctrl left click move's the picture in the world matrix 
  *  alt+ w\a\s\d\q\e  rotates the picture , w/s rotate around x ,a/d around y ,q\e around z in World
  *  alt + double right click scales the picture up  in local
  *  alt+ left click move's the picture in the world matrix 
 
