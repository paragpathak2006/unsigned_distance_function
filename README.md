# Unsigned distance function 
## Orignal Git repos
These repos cannot be updated due to git issues. <br/>
https://github.com/paragpathak2006/unsigned_distance_function <br/>
https://github.com/paragpathak2006/CudaRuntime1 <br/><br/>

## Updated Git repo
Lastest updates are in the following repo2 <br/>
https://github.com/paragpathak2006/CudaRuntime2 <br/>

## Mesh
Define a Mesh that has vertex Points Pi and Triangular faces Tj as <br/>
Mesh=Pi,Tj(Pa,Pb,Pc)

## Bounding box
If point is outside a bounding BoxPi  at β distance, them point is automatically a Beta distance. <br/>
BoxPi at β distance
## Convex hull method
If point is outside a bounding convex Hull Pi  at β distance, them point is automatically outside a Beta distance.  <br/>

## Pointwise distance
Q is query point. βis maximum truncated distance. <br/>
dmin=mind(Q,Pi),β <br/>
## Facewise distance
Q is query point. βis maximum truncated distance. <br/>
dmin=mindQ,Tj,β <br/>
Ref: Distance Between Point and Triangle in 3D (geometrictools.com) <br/>
(https://www.geometrictools.com/Documentation/DistancePoint3Triangle3.pdf) <br/>

Let Face Triangle be defined as <br/>
Tjs,t Tjs,t= B +sE0 +tE1 ,∀ s≥0,t≥0,s+t≤1 <br/>

Face Triangle to Point distance can be found using the formula<br/>
dQ,Tj=ds,t=as2 + 2bst + ct2 + 2ds + 2et + f <br/>
a = E0 · E0,b = E0 · E1,c = E1 · E1, <br/>
d = E0 · B - P,e = E1 · B - P,f = (B - P) · (B - P) <br/>
d0,t= ct2 + 2et + f→t=-ec <br/>
ds,0=as2 + 2ds + f→s=-da <br/>
ds,1-s=as2 + 2bs1-s+c1-s2 + 2ds+ 2e1-s+ f→ <br/>
s=b+d-c-eb-c-a,t=b+e-a-db-c-a <br/>
=as+b1-s-b+cs-1+d-e=a-b+cs+b-c+d-e-da <br/>

## Brute force approach
Go over all the points and faces to find the minimum possible distance dmin  between target point and mesh points.
## Spatial indexing approach
Recommended approach of indexing is using octree, but in our case were going to implement a simple space map to spatially Index the mesh points. After indexing, find all the points and faces in a β sphere to minimize list of candidate Points to search.
Spatial indexing using CUDA, requires us to implement unordered map using CUDA. 
A vectorized unordered map is implemented using an additional vector container for storing indexes. 
The program is supposed to handle each spatial index on an individual CUDA thread. 
CUDA streams can be used to further enhance the concurrency of the data transfer process.
![image](https://github.com/paragpathak2006/CudaRuntime1/assets/31978917/b0443065-ff67-4f37-af8e-55b95cbc5726)

## Parallel indexing of Points
The process of indexing is also parallized using thrust. 
This is done using sorting a point_indexes using as keys point_wise_bucket_index array.
Then counting differences in bucket indexes accross two consecutive elements to update correct buckets using cuda.

### See function [cuda_parallel_hashmap_generation()](https://github.com/paragpathak2006/cudaRuntime2/blob/994a9516142b90060ab2882f2fb2f626bfc77886/Thrust_lib/thrust_dist.h#L188)

## Parallel Hashmap
A parallelized version of Hashing was also implemented.

## Thrust library function

typedef thrust::host_vector<double> Hvec;   <br/>
typedef thrust::host_vector<Point> HPoint;<br/>
typedef thrust::device_vector<double> Dvec; <br/>
typedef thrust::device_vector<Point> DPoint;<br/>

double min_dist_calculation2(<br/>
const HPoint& Hpoints, <br/>
const Point& target, <br/>
const double& beta2<br/>
){
    DPoint points = Hpoints;
    Dvec distances(Hpoints.size());

    // apply the transformation <br/>
    thrust::transform(_ITER_(points), distances.begin(), dist2_point(target));<br/>
    return thrust::reduce(_ITER_(distances), beta2, min_dist());<br/>
}

## OUTPUT

- find materials in: /content/3DObjects/./cube.obj.mtl

Num of points : 3456<br/>
Num of faces : 1152<br/>
Bounding Box : Min(-1.000000,-1.000000,-1.000000) , Max(1.000000,1.000000,1.000001)<br/>
dist test : <br/>
0.72<br/>
0.04<br/>
Point_index(-50,-50,-50)<br/>
Point_index(50,50,50)<br/>

### INPUTS
Target point : Point(0,1,1.2)<br/>
Target point index : Point_index(0,50,60)<br/>
Beta : 0.3<br/>
Map size : 0.02<br/>

### Pointwise(brute force)
Unsigned distance for Points (brute force) => 

Unsigned distance : 0.2<br/>
Target point : Point(0,1,1.2)<br/>
Nearest point : Point(-5e-07,1,1)<br/>


### Facewise(brute force)
Unsigned distance for Faces (brute force) => <br/>

Unsigned distance : 0.2<br/>
Target point : Point(0,1,1.2)<br/>
Nearest Face : Face(870,871,872)<br/>


### Pointwise(local)
Unsigned distance for Points (space map) => 

Unsigned distance : 0.2<br/>
Target point : Point(0,1,1.2)<br/>
Nearest point : Point(-5e-07,1,1)<br/>


### Pointwise(Serial)
Unsigned distance for Points (Serial) => <br/>

DIMs : <br/>
max_size_index : 16 , Threads_dim : 4 , blocks_dim : 8 , Dim : 32<br/>
(i0,  j0, k0) : ( -16 , 34 , 44 )<br/>
(i1,  j1, k1) : ( 16 , 66 , 76 )<br/>

Unsigned distance : 0.2<br/>
Target point : Point(0,1,1.2)<br/>


### Facewise(Serial)
Unsigned distance for Faces (Serial) => <br/>

DIMs : <br/>
max_size_index : 16 , Threads_dim : 4 , blocks_dim : 8 , Dim : 32<br/>
(i0,  j0, k0) : ( -16 , 34 , 44 )<br/>
(i1,  j1, k1) : ( 16 , 66 , 76 )<br/>

Unsigned distance : 0.2<br/>
Target point : Point(0,1,1.2)<br/>
Nearest Face : Face(870,871,872)<br/>


### CUDA_TEST_BEGINS<br/>
{1,2,3,4,5} + {10,20,30,40,50} = {11,22,33,44,55}<br/>

### CUDA_TEST_SUCCESS<br/>

### Pointwise(cuda)
Unsigned_distance_cuda_hash_table with Points =><br/> 

DIMs : <br/>
max_size_index : 16 , Threads_dim : 4 , blocks_dim : 8 , Dim : 32<br/>
(i0,  j0, k0) : ( -16 , 34 , 44 )<br/>
(i1,  j1, k1) : ( 16 , 66 , 76 )<br/>
Kernel execution time: 0 ms<br/>

Unsigned distance : 0.2<br/>
Target point : Point(0,1,1.2)<br/>


### Facewise(cuda)
Unsigned_distance_cuda_hash_table with Faces => <br/>

DIMs : <br/>
max_size_index : 16 , Threads_dim : 4 , blocks_dim : 8 , Dim : 32<br/>
(i0,  j0, k0) : ( -16 , 34 , 44 )<br/>
(i1,  j1, k1) : ( 16 , 66 , 76 )<br/>
Kernel execution time: 0 ms<br/>

Unsigned distance : 0.2<br/>
Target point : Point(0,1,1.2)<br/>




