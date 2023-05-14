
# section 1 :
  * added light class to the project which contains light position , ambient ,specular,diffuse parameters 
  * added an option to add a point in gui (press the add light botton and then select a place on the screen ) adds x,y courdinats and leaves z as 0
  * a menu to control light parameter and object material i.e colors  (and i'll be adding positions)
  * in the menue above we can draw a circle in the x,y coardinates of the light (will add z into consideration but not yet as im only calculating ambient for section 1 )
  
## progress :
  ### 1.light's ambient is white and the object is red :

  ![image](https://user-images.githubusercontent.com/92520508/147089127-2eb60e6b-d76b-4390-96cf-5fced72e1acf.png)

   
   * this result shows that the basic's of light reflection ; object reflect's it's light when exposed to a white light 
  
  
  ### 2.light's ambient is red but has less luminuns (not the full spectrum of red )
  
  
  ![image](https://user-images.githubusercontent.com/92520508/147089449-d6e0c529-8cab-4a53-bf14-7233a4733cda.png)

  
  
  * this result is what we are looking for because the object now recieves a "dimmer light" and reflect a dimmer red 
  
  
  ### 3.here we send pure green light to a white object which in turn doesn't reflect it because it's red that's why we get black color 


 ![image](https://user-images.githubusercontent.com/92520508/147089565-ed91ffeb-b34f-4936-80cf-0db9d2a6a427.png)
 
 ## section 2 :
 
  * in this picture we see the light on the right of the object and that the light reflects according to the light's position with flat shading  :
  
  
 ![image](https://user-images.githubusercontent.com/92520508/147410542-b170a3de-7f97-4be3-84d8-c01d7a726266.png)

 * different angle :
 
 
 ![image](https://user-images.githubusercontent.com/92520508/147605499-9783668d-582c-40fe-923e-2116b2c28183.png)




![image](https://user-images.githubusercontent.com/92520508/147605546-07b54b58-a909-4092-acb2-3805b1ed3b1a.png)


 * flat shading using both ambient and diffuse :
 
 ![image](https://user-images.githubusercontent.com/92520508/147605921-a948d9f1-373c-4b78-8e82-e8d941d4fcb4.png)


## section 4 :
  * these are the results without filling the triangles so that we can see that the light on the down side of the triangls bumps on the face from the inside and reflects the same way to the inside :
  ![image](https://user-images.githubusercontent.com/92520508/147855473-41807317-5ac9-4ce9-92a2-e29f08fca778.png)

  * video: 
     
    *without coloring:

https://user-images.githubusercontent.com/92520508/147860915-80e33967-9743-495b-851f-602045507161.mp4

    
   *with coloring:
   



https://user-images.githubusercontent.com/92520508/147860932-530e3d93-d831-4f48-9036-73dcfd6620f8.mp4



  
  
## section 5:

* in this section i used the same interpolation that i used for the z buffer on the vertix normals to calculate the correct value for each element of the normal ,meaning x,y,z of the normal vector for every pixel.
* the vertix normals that i used are the ones i calculated for the previous assighnment ,i sent them in a stack and used them. 
* for each component of specular and diffuse i used the normals above on the same equations that were in the lecture .

### the result on demo with all three components used:
  


https://user-images.githubusercontent.com/92520508/147853381-6df94126-f36b-4b1d-8064-2b9dc6ab78e0.mp4


### the result on demo with specular alone:


https://user-images.githubusercontent.com/92520508/147853486-211958ef-f3d7-425c-8ff6-93b2eeeb7993.mp4


## section 7 :

### teepot: 

https://user-images.githubusercontent.com/92520508/147853696-60ba4876-45ca-4cfc-a550-fe652b33a436.mp4


the following pictures are a great example on how the lighting works when it's in an angle with the object:


![image](https://user-images.githubusercontent.com/92520508/147853752-c9b81767-e878-45c5-9812-5c4320ceeee8.png)


![image](https://user-images.githubusercontent.com/92520508/147853797-3fa7c844-6eef-462d-85b1-1084e1445d50.png)


the light is above the object and (behind it )deeper in the z couardintes :

![image](https://user-images.githubusercontent.com/92520508/147853902-69209d2f-63a1-45d4-bfaf-19671542f5f2.png)


### beethoven: 

* here we can see the lighting changing while rotating beethoven: 


https://user-images.githubusercontent.com/92520508/147854358-015d89b1-79ea-4d01-9ca5-7ac6e1ea4644.mp4


### bishob:

* when changing the camera location we can see the lighting and shadows change ! :



https://user-images.githubusercontent.com/92520508/147854411-99bc941b-95e9-4483-bd52-d62e5057ff6a.mp4


* here the light is behind the object and far away in an angle with y , we can see the light on sides and this is due to the intensity :

low intinsity :

![image](https://user-images.githubusercontent.com/92520508/147854478-107cee21-5bbb-46c2-8926-8b94ea890d8e.png)

high intensity :

![image](https://user-images.githubusercontent.com/92520508/147854482-1880d02c-39ea-4144-92d2-eb367f84eb7e.png)


### banana:
  flat shading :

![image](https://user-images.githubusercontent.com/92520508/147858446-0a13134f-f7b2-448e-997e-63083d723e2b.png)

![image](https://user-images.githubusercontent.com/92520508/147858555-4fa6920c-6300-44a5-9df0-68867be34bd0.png)


 phong:
 
 ![image](https://user-images.githubusercontent.com/92520508/147858476-bedae776-245c-414c-8165-47a91b9d38d6.png)
 
 ![image](https://user-images.githubusercontent.com/92520508/147858542-7792015a-28d1-42cc-a098-24140b756c3f.png)


Camera:
 flat shading :
 
![image](https://user-images.githubusercontent.com/92520508/147858585-c96228ec-2129-4142-b403-84f5efe9b5f7.png)

![image](https://user-images.githubusercontent.com/92520508/147858635-b26d0457-90f1-419d-bab7-449e32b3a3bb.png)


phong:

![image](https://user-images.githubusercontent.com/92520508/147858599-416a8e8f-21bc-4ae7-bb3c-b46cfc1b3672.png)

![image](https://user-images.githubusercontent.com/92520508/147858631-42e4cb9b-f2bd-4763-b233-264251870f60.png)
 
 flat shading :
 
![image](https://user-images.githubusercontent.com/92520508/147858709-5b65b090-bf53-48cf-99f2-1f55d49f56b7.png)



phong:

![image](https://user-images.githubusercontent.com/92520508/147858699-54a483f6-25b7-4364-9505-28863c11df0f.png) 


## more than one light :

## cow :
  phong:
   
   ![image](https://user-images.githubusercontent.com/92520508/147860422-7943e8f8-f835-4e38-9679-47de38d1df91.png)
  flat:
  
  ![image](https://user-images.githubusercontent.com/92520508/147860430-0c179343-b1b7-4236-9a9f-d99476ed193b.png)
  
 ## bunny:
 
 phong:
 
 ![image](https://user-images.githubusercontent.com/92520508/147860446-4238ece4-5573-4eee-840c-e4e0f08431ef.png)
 
 flat:
 
 ![image](https://user-images.githubusercontent.com/92520508/147860454-c27c01e2-e09e-4691-aae3-f60943fa76b6.png)

## Blob:
 
 phong:
 
 ![image](https://user-images.githubusercontent.com/92520508/147860601-7e57bb55-16c9-414b-bc49-717813450019.png)

flat:

![image](https://user-images.githubusercontent.com/92520508/147860609-d465adc6-deee-46a2-97c0-425689303eb5.png)


## section 8 :
* i implemented 3 filters : gausian blurr ,bloom,boxed blurr 
  1. gausian blurr : i created the kernel with 5x5 window and then called for a function to implement the kernel on the color buffer 
  2. bloom: i created another buffer and added a threshold with 3 colors ,using the thresh hold i put the higher(than the threshold ) colors from  the color buffer to the buffer i created and then used the gausian filter on the new buffer , added both of them onto the original buffer ,then deleted the temporary buffer that i created .
  3. boxed blurr : created a kernel that puts equal values to each element in the kernel ,such that when we add all of the elements we get 1 ,and then used the function that applies the kernel on the buffer .
 
 examples :
 original :
 
 ![image](https://user-images.githubusercontent.com/92520508/147854685-f66598df-ea5f-4290-8515-cd855311bdb0.png)

 1.gausian blurr:
 
 ![image](https://user-images.githubusercontent.com/92520508/147854693-7c8d72c6-aa6a-4e03-9b54-e959fdb0f3d7.png)


2. boxed blurr:

  ![image](https://user-images.githubusercontent.com/92520508/147854705-3625464b-8cd7-4de3-8398-1f5d233a91d3.png)

3.bloom:

![image](https://user-images.githubusercontent.com/92520508/147854721-37237d5c-f750-4713-b2c4-308e64533805.png)

4. bloom with boxed blurr:

![image](https://user-images.githubusercontent.com/92520508/147854740-3cffceb9-ec7a-45a4-b77e-5d09e58c6c52.png)


### new featurs :
![image](https://user-images.githubusercontent.com/92520508/147855118-ae83744a-c606-4aad-b7a8-67fd5c6275da.png)
1. the tabs now work and the current tab is highlighted ! 
3. when pressing on ,Camera and fov or Transformations blurr or light controles we get a new tab that has all the conrols .

![image](https://user-images.githubusercontent.com/92520508/147855175-29b4e411-2928-471c-8c78-3b38a83b0f97.png)

4. to add a point press the check box on main menu "Add a Point" that adds it as a mesh model 

![image](https://user-images.githubusercontent.com/92520508/147855139-1f15e20f-60d5-4e3b-a945-edc83b546b79.png)

5. pressing light controls opens a new tab only if there is at least one light ,and it contains :
  1.light and model colors to control 
  2. select a light if there is more than one 
  3. 3 parameters to move the selected light
  4. intensity 
  5. show reflected ray : shows the light direction and its reflection on the model 



![image](https://user-images.githubusercontent.com/92520508/147860852-aa1996a9-e74c-43f5-8ad0-eaa902900cda.png)


6. pressing blurr scene opens the filters tab which contains 2 parameters 
  1. sigma for the gausian filter
  2. threshhold that contains the colors for the threshold of bloom

![image](https://user-images.githubusercontent.com/92520508/147855131-e476ce27-5bb4-4aa1-ac20-91be891c9a24.png)

