# SLAM  Visual Odometer 2: Optical Flow & Direct Method
The project implements the front end of the SLAM system, also known as the VO (Visual Odometer). The algorithm of VO are mainly divided into two categories: Feature-Based Method and Direct Method.

There are some problems with using Feature-Based Method. Is there any way to overcome these shortcomings? Here are some ideas:

• Keep the feature points, but only calculate the key points, not the descriptors. At the same time, using the **Optical Flow** method to track movement of feature points. So that we can avoid computing and match the descriptors, but it takes time to the calculation of optical flow itself;

• Calculate only key points, not descriptors. At the same time, using the **Direct Method** to calculate the position of the image feature point in the next moment. It also can skip descriptor computation process, and the calculation is more simple.

- **Optical Flow**
Optical flow is a way of describing how pixels move between images over time. The computation of partial pixel motion is called sparse optical flow, while the computation of all pixels is called dense optical flow.

The sparse optical flow is represented by the **Lucas-Kanade** Optical Flow and can be used to track the position of feature points in SLAM.

Optical Flow can also be seen as an optimization problem: minimizing Photometric Errors to estimate the optimal pixel offset. Therefore, this project manually implemented the Gauss-Newton based Optical Flow Method including specific implementation of **Forward-additive and Inverse Optical Flow**, and generalizing to **Pyramid Multi-Level Optical Flow**.

<div align=center>
<img src="https://latex.codecogs.com/gif.latex?\dpi{130}&space;\large&space;\min_{\Delta&space;x,\Delta&space;y}\big\|&space;I_1(x,y)-I_2(x&plus;\Delta&space;x,&space;y&plus;\Delta&space;y)&space;\big\|_2^2." />
</div>  

Where the residual is the part inside the bracket.

Forward-additive: Jacobian is the gradient of the second image at <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{130}&space;x&plus;\Delta&space;x,&space;y&plus;\Delta&space;y" />

Inverse: The gradient here can also be replaced by the gradient of the first image;

Pyramid Multi-Leve: The original image as the bottom of the pyramid, each layer up, the lower image is scaled to a certain degree, resulting in a pyramid. When computing optical flow, using Coarse-to-fine process, start from the top image first, and then put previous layer's result as the initial value of the next layer's optical flow.

- **Direct Method**

The Direct Method is an intuitive extension of Optical Flow. In the Optical Flow, we estimate the translation per pixel (in the case of additive). In the Direct method, we minimize the Optical flow error to estimate the rotation and translation of the camera (in lie algebra form)

The project uses Kitti Dataset which provides left.png and disparity.png to estimates camera pose from image 000001.png to 000005.png, where left.png is the reference image(ref), and any of the images from 000001.png to 000005.png is the current image(cur).

<div align=center>
<img src="https://latex.codecogs.com/gif.latex?\dpi{130}&space;\large&space;T_{cur,ref}=\frac{1}{N}\sum_{i=1}^N&space;\sum_{W_i}&space;\big\|I_{ref}(\pi(p_i))-I_{cur}(\pi(T_{cur,ref}&space;p_i))\big\|_2^2" />
</div> 

Where N is the number of points, the function <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{130}&space;\pi" /> is the projection function of the pinhole camera, and <img src="https://latex.codecogs.com/gif.latex?\inline&space;\dpi{130}&space;W_i" /> is the small window around the ith point. Same as Optical Flow method, the problem can be solved by Gauss-Newton function.

The project also put the Direct Method with coarse -to-fine process, expanding into multi-level pyramid, which can still track to all points in the case of a larger movement.