Note : everything done in the project was inspired by the book given in the Textures lecture .
link : https://learnopengl.com/ 
## section 1 :

 This function  basically takes the 4 vertices from vertices vtc[] and thier texture couardinates from tex[] and sends(copies) them to the gpu. 
 then uses the built in shaders to render the vertices with the texures .
 and then assignes the texture coardinates that it sent to the gpu as the current active texture.
 
in opengl ,we use homogeneous coordinate system ,i.e  the rectangle below fills the whole screen :

     / (-1, 1)____(1, 1)
      //	     |\  |
      //	     | \ | <--- The exture is drawn over two triangles that stretch over the screen.
      //	     |__\|
      // (-1,-1)    (1,-1)

the shaders fill the screen with a rectangle built from 2 triangles above that we sent earlier to the gpu .  
which makes the whole screen a model that has two faces ,thus we use the texture coardinates to paint over the two triangles : 
this proccess allowed us to put our buffer as the texture for the screen built as mentioned ubove 

* now to how the texture is displayed :
  * fragment shader :
                  
          #version 150
          in  vec2 texCoord;
          out vec4 fColor;

          uniform sampler2D texture;

          void main() 
          { 
             fColor = textureLod( texture, texCoord, 0 );
          } 
we see that in the fragment shader : 
  the fragment shader gets the values of texture coardinates and uses texturelod with the sampler 2d object and uses textureLod to caculate the color of the pixel  .
  Sampler2d texture: Specifies the sampler to which the texture from which texels will be retrieved.
  texCoards is the said texture coardinate . 
  0 is the explicit level-of-detail. 
  and thats how every pixel is calculated .
  those textures are displayed according to the gl_position that was calculated in the V-shader .
  
## section 2:
 
  ### a couple of steps :
   * added texture to the constructor and updated the function in utility to get said textures from the obj file 
   * changed the recalibration such that it accures in the constructor (centering and resizing of the object). 
   * i updated the mesh model class by adding a Vertix class and adding vbo(vertix buffer object ) and vao( vertix array object ) but on the recalibrated vertices ! .
## section 3:
  
  * i used the reference code and added to it the multiplication of the camera matrices i.e. if we want to make adjustments to the camera without using lookat function.
  
  ### the code :
   
   
   
     #version 330 core
     layout(location = 0) in vec3 pos;
     layout(location = 1) in vec3 normal;
     layout(location = 2) in vec2 texCoords;

     // The model/view/projection matrices
     uniform mat4 model;
     uniform mat4 camera;
     uniform mat4 view;
     uniform mat4 projection;
     // These outputs will be available in the fragment shader as inputs
     out vec3 orig_fragPos;
     out vec3 fragPos;
     out vec3 fragNormal;
     out vec2 fragTexCoords;


    void main()
    {
      fragPos = vec3(view  *camera* model *vec4(pos, 1.0f));
      fragNormal = mat3(view  *camera* model  ) * normal;
      fragTexCoords = texCoords;
      gl_Position = projection * view  *camera* model * vec4(pos, 1.0f);
     }

  
## section 4:
  * the code for the fragment shader , i just added one line that gives a static color for the time being:
   
 ### code:
 
           #version 330 core  
           in vec3 orig_fragPos;
           in vec3 fragPos;
           in vec3 fragNormal;
           in vec2 fragTexCoords;
           out vec4 frag_color;
           void main()
           {
             frag_color =vec4(1.0f,0.0f,0.0f,1);
           }
           

           
## section 5:

### changes on the code to send vao to the shaders in the gpu :


 ![image](https://user-images.githubusercontent.com/92520508/150781209-c372b813-3ab0-40a9-9c9f-369675ae9fc1.png)


 ![image](https://user-images.githubusercontent.com/92520508/150781248-543c5149-0ae5-40e9-9125-65568679d9a3.png)


### changes in main :


 * in function RenderFrame :


  ![image](https://user-images.githubusercontent.com/92520508/150781592-38250758-0d5d-498a-865f-8530138c3422.png)
  


 ### teapot was drawn successfully :



 ![image](https://user-images.githubusercontent.com/92520508/154778502-68716518-0888-4a97-8b47-404f65400415.png)



## section 6 :
  * I treat light as a mesh model ,so i added a boolian to the fshader so that when i send a light to be calculated in the gpu it outputs only a single color to draw the light 
  * in the f shader i added a light class so that when i figure out how to create multiple lights i will be able to do that in the shaders and also added a function in the fragment shader that calculates phong shading.
  * i was saved by the book referenced above as i was having a problem where the specular lighting does shine but it shined both from the closest couardinate to the light and from the other symetrical end ! as i was multiplying  the view volume with the rest of the matrices and then with the normals.


  ### a video of reflections for teapot :
 
 
 
https://user-images.githubusercontent.com/92520508/154778679-bd4218f1-0bd4-4ecf-881c-15727ae7d612.mp4




## homer sympson:


* a video of homer , shows how smooth the transitions is ! : 



https://user-images.githubusercontent.com/92520508/154778920-6d8c229b-7303-476c-9627-0720800ebbfd.mp4



* homer with different light angles :




https://user-images.githubusercontent.com/92520508/154779081-9ee5116e-1664-4d54-97b9-480a2c3e8fe5.mp4



* homer from the side :



![image](https://user-images.githubusercontent.com/92520508/154779265-ffce40c6-7178-4e0b-acff-5deeb861c35a.png)



* video of homer from the back + side  :



https://user-images.githubusercontent.com/92520508/154779363-b04b2284-5b52-48a5-9838-4400cec9a3da.mp4



* highlighting speculer lighting when the light is underneath homer 



![image](https://user-images.githubusercontent.com/92520508/154779481-2b4ccd80-a66e-45e4-94a3-f99b3a70c47b.png)



* another angle :



![image](https://user-images.githubusercontent.com/92520508/154779572-ed6e041e-aae6-4c06-b4ba-a8191bda6f3a.png)



* same angle but highlighting the diffuse component :




![image](https://user-images.githubusercontent.com/92520508/154779602-039f4237-9190-46c3-80aa-f50da4b4698a.png)



* a video for diffuse component :




https://user-images.githubusercontent.com/92520508/154779702-f4c21d5f-ceca-4b84-9100-e479557e95f9.mp4





 
## section 7 :

* the implementation was fairly easy as i used the demo as reference, and used the texture coardinates as a seperate option ,for model's that come with them and thier textures . 


### for spherical projection i calculated the  Phi and Theta from the vertices and created texture coardinates using those phi and theta the poles of the sphere are on the z axis :

### teapot: 



![image](https://user-images.githubusercontent.com/92520508/154780018-e672b3e4-8b37-484a-8382-cb5a3bb88eb4.png)



### backpack + the light is the sphere next to it :



![image](https://user-images.githubusercontent.com/92520508/154780116-dfc3db53-528a-475e-9b72-763cd3197bac.png)



### feline :



![image](https://user-images.githubusercontent.com/92520508/154780168-011a513d-203c-4396-8f53-1f74510fdda2.png)



### golf ball closest to a sphere :



![image](https://user-images.githubusercontent.com/92520508/154780239-af04f9de-3b61-478e-99e0-d996d4219dfb.png)



### golf ball with texures and lighting :



![image](https://user-images.githubusercontent.com/92520508/154780334-3aaa01c0-7748-4bb8-98c6-11489bc10793.png)



## the poles on the sphere are on the y axis:

  ### teapot:
 
 
 ![image](https://user-images.githubusercontent.com/92520508/154799261-370491c6-8acc-4ea6-a310-8f3a767cc01b.png)
 
 
 ### feline :


![image](https://user-images.githubusercontent.com/92520508/154799295-650068fe-16f2-4e2c-8abe-4bc306413aa0.png)



![image](https://user-images.githubusercontent.com/92520508/154799308-298eb41c-2ad2-4daa-8a16-5e2cc7845dee.png)



### golfball:



![image](https://user-images.githubusercontent.com/92520508/154799402-749439f1-c30f-4a89-acb2-b66ef48365be.png)



## the disorintation at the pols is caused by the mirroring of the texture so that it fits the object 



* fixed by transforming the theta and phi that we found to the range of [1,-1]  .
* that was done by deviding by 2*pi and pi and adding 0.5 to the value of arctan and arcsin :
* the result is as follows : 
 

![image](https://user-images.githubusercontent.com/92520508/154801386-ed7e8d8e-bd13-410d-889d-d579adc22376.png)
 
 
 
 ![image](https://user-images.githubusercontent.com/92520508/154801479-75c3b4dc-6940-4205-922a-93672f989c42.png)



### the best implementation was using repeating and a bigger texture  :



![image](https://user-images.githubusercontent.com/92520508/154801541-898f779f-4ac3-477d-981e-01e5465ed662.png)



![image](https://user-images.githubusercontent.com/92520508/154801544-0a66bff1-ae2e-491b-be3a-e13e79bf3cd8.png)


 


we can see the orientaions being less and less obvious .




### golfball with it's own texture coardinates on a texture that i found online :


![image](https://user-images.githubusercontent.com/92520508/154808177-52ac9e4e-9026-497b-b420-3cc8fadc2c31.png)



![image](https://user-images.githubusercontent.com/92520508/154808194-85c7cf17-6120-4558-aab7-1e2422770f73.png)



![image](https://user-images.githubusercontent.com/92520508/154808320-305155ff-1412-4828-ad6d-0c17d90fb06b.png)









## section 8 :

# Enviroment mapping :
 * I created a Box for the sky box and a box that i used to reflect the enviroment of the skybox 
 * basically those 2 are like mesh model's but the sky box doesnt move rotate or any of the transformations 
 
 # sky box :
 * for the sky box i created a Vshader and Fshader ,then used that shader to apply its textures  
 * but it uses cubemap shaders as it's 6 2d images labeled left,top,right,down,front,back, all 6 together make a scene .
 *Texture2D class: 
  * in the Texture 2d class i added a function that loads cubemaps ,as i am going to use it for the mesh model too .
  * added a bind and unbind for cube objects.
*Vshader for sky box :
  * quite simple ; it gets projection matrix and view matix and sends out the texcoords as a position .
  * i used a cube and skybox from the book given as a referance in the lecture . 
*fshader:
 * takes the texturecoords and uses sampler cube on it . 

# mesh model (uses Cube):
  * Vshader:
    1. gets the position and normal as was the case before 
    2. this time the frag normal is calculated as the transpose inverse of the model* normal (mesh model) so that we can create the illusion of a mirror when we get to calculate the reflection victore that is used to get our texture ! .
    3. then we simply use reflect to find the correct orientation of the reflected light 
    4. we get the texture using cube map with our texture ! 
    5. i also added a refract feature as opengl makes it as easy as eating a cake 
    
    
 # back pack :

![image](https://user-images.githubusercontent.com/92520508/154781334-66737818-13c3-41a2-b5af-be45df632427.png)

# teapot :

![image](https://user-images.githubusercontent.com/92520508/154781351-421aabe8-5f17-46d6-8955-7732f9dae0b8.png)

# beathoven :

![image](https://user-images.githubusercontent.com/92520508/154781370-39af7ae7-b002-41cd-b9a9-b094988e48d1.png)


# huge Field of view (should be added on console for warzone !):

![image](https://user-images.githubusercontent.com/92520508/154781404-7c1bbb22-429f-42c0-bac5-b4355ea1d0a5.png)

# a tour with that fov:




https://user-images.githubusercontent.com/92520508/154781527-114da24c-32b2-4a0b-bd21-9e0d1f45ede4.mp4




# Ball with nice effects after zooming in ! :

 

https://user-images.githubusercontent.com/92520508/154781547-4a461c80-7b36-4e03-a314-76c20e2153cb.mp4




# additions to the ui 
 ## imgui main menu:
   
   ![image](https://user-images.githubusercontent.com/92520508/154801765-2e6308a3-e62e-429b-b455-31fd81cd5be9.png)
   
   
   1. we can select the color of the model and the color of the world
   2. select the projection on the screen ; i.e Enviroment mapping ,fill triangles ,or just wireframe   
 * enviroment mode :

  ![image](https://user-images.githubusercontent.com/92520508/154802386-5cd86aa5-ea24-4570-9695-57fcfecb5653.png)

   * is selected by default and has an option to use refraction instead of reflection with a refraction factore under it 
   
   ![image](https://user-images.githubusercontent.com/92520508/154802401-8d4a5393-5f3c-4ed4-86ca-51d946d15f5a.png)

   
   ![image](https://user-images.githubusercontent.com/92520508/154802375-23a27151-ccb2-46c1-8c26-550e852cd43f.png)


   3. we can turn on textures by clicking on Textures on/off .
   4. if we want to use the spherical mapping textures instead of the texture coardinates that come with the object  we click on Spherical textures
     * this option opens up a tab containing controls for the modes of spherical mapping ; which axis is the pole , manipulation of theta and phi that makes an effect of moving the texture (cyclic)
 
   ![image](https://user-images.githubusercontent.com/92520508/154802299-a23fe3e4-c8b5-480e-9502-2e4ae1289e15.png)


  5. Transformations :
      * opens up a tab that contains all the models transformations + an option to select one of the added models as the current model .
      *   ![image](https://user-images.githubusercontent.com/92520508/154802509-29364fe6-5c2d-4435-89b5-7178e8db0c4a.png)

  6. Camera And Fov:
    * opens a tab to controle the camera just like previous versions . 
    * has an option to change the projection type , orthographic or perspective.
    * set to Perspective by default 
    *The added functionality to the camera is the option to move the camera around the scene with a fixed distance from the 0,0,0  coardinate : 
   
   ![image](https://user-images.githubusercontent.com/92520508/154802602-6ab19008-827f-4d3a-abfb-be7d2312310f.png)
   
   
 7. Add point :
   * adds a light object to the screen .
 8. let light affect scene :  
   * makes the light affect the scene .
 9. light controles:
   * opens up the tab that contains the light controles :
      1. position 
      2. color of the light material 
      3. color of the object material 
      4.  intensity of the light 
      5. an option to remove the light . 

![image](https://user-images.githubusercontent.com/92520508/154802721-a8ee2418-e63f-4f5f-b612-279a3fc59d91.png)


all tabs opened : 

![image](https://user-images.githubusercontent.com/92520508/154802744-e66caf73-951e-4905-85bb-be03f63a2c91.png)




