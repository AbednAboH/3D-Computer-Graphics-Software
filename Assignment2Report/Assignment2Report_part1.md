## section 1 :
bounding rectangles :
 * i found the maximum and minimum x,y couardinates of every triangle and used drawline to draw them with colours given by a color victor that is meant also for the faces 
 
 
   ![image](https://user-images.githubusercontent.com/92520508/145678679-32816235-2aa5-481d-8861-c45190bd368e.png)

## section 2 : 
 
 * at first i used the approch given in this section but then i changed my mind and used edgwalking apporch because it was much more forgiving on the cpu .
 
 ## section 3 :
 
 i simply used the edge walking approch and this is the result without rotating :
    
   ![image](https://user-images.githubusercontent.com/92520508/145679648-ac507453-7697-429e-99fb-cc0a41cf90bc.png)

   this is the result when i move the camera's location :
    
    
   ![image](https://user-images.githubusercontent.com/92520508/145679671-ad4eb98e-7b09-4be7-8bb7-0d4e9e793dcf.png)

  ## section 4 :
   * in this section i used the same interpolation method to find the z values of each x ,just like the shading of a triangl's colors ,exactly the same method , previously i implemented 2 depth algorithem to find the depth but i noticed the Z-fighting problem on the model so i used interepolation to find z depth on each pixel ,moreover, on the area method it took the cpu a lot of time to calculate areas.
   * i should also note that the interpolation was at 1/z values not z itself because if we do it on z interpolation the z's that we get would be wrong values(it would print correct faces but it doesn't have the correct depth) , in other word's it wasn't linear , but on 1/z it becomes linear .
   * then i used z=1/z to get the correct value of z ,this step was to represent the Zbuffer in grayscale (thats how i realized that i have to interpolate on 1/z ). 
   *  here are a couple of model's on defferent angles from the camera (moving the camera around )
  
## Bunny:
![image](https://user-images.githubusercontent.com/92520508/145684351-087b85f4-0b98-48b1-bdf4-1facf3f1e684.png)  ![image](https://user-images.githubusercontent.com/92520508/145684362-f4479702-774a-4d52-8595-2800230d4e7f.png)




## Blob:

![image](https://user-images.githubusercontent.com/92520508/145684378-6c44bf26-ef50-4620-9dce-2ecf5c79925b.png)  ![image](https://user-images.githubusercontent.com/92520508/145684393-23137518-3ce1-4456-ba03-6ab12a9b4e17.png)

## Beethoven:

![image](https://user-images.githubusercontent.com/92520508/145684455-52cbd5a6-c173-4b19-9879-f0dc83376bd6.png)  ![image](https://user-images.githubusercontent.com/92520508/145684462-0aed3a86-bc21-4d8a-a952-afd1dad2f75c.png)


## Cow:


![image](https://user-images.githubusercontent.com/92520508/145684483-fbdb88ca-e4d2-4a06-b847-81e9be13bfe0.png)   ![image](https://user-images.githubusercontent.com/92520508/145684503-1a6ad9f8-be98-4f22-9db6-df6466b0898c.png)



## Cube:

![image](https://user-images.githubusercontent.com/92520508/145684551-de2de9df-5aae-404b-b361-db0c8cc3f44d.png)    ![image](https://user-images.githubusercontent.com/92520508/145684560-d8685c16-6da8-4ada-93d3-1665fc0ad318.png)

## cube zoomed out :


![image](https://user-images.githubusercontent.com/92520508/145684612-ae57b211-2d52-47b9-9817-e40700609822.png) ![image](https://user-images.githubusercontent.com/92520508/145684626-01701f80-0b54-4892-99e2-a4ea38b5fc0e.png)




# note's :
   * under main menu i added a gray scale option and am option for drawing only the triangles pointed to in the picture below :
 
   
   ![image](https://user-images.githubusercontent.com/92520508/145685465-0521bf60-eaf4-4cb6-bdf3-c0047607bfb2.png)


