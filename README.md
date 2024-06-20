# Unsigned distance function 
## Git repos
https://github.com/paragpathak2006/unsigned_distance_function 
https://github.com/paragpathak2006/CudaRuntime1 
## Mesh
Define a Mesh that has vertex Points Pi and Triangular faces Tj as
Mesh=Pi,Tj(Pa,Pb,Pc)
## Bounding box
If point is outside a bounding BoxPi  at β distance, them point is automatically a Beta distance.
BoxPi at β distance
## Convex hull method
If point is outside a bounding convex HullPi  at β distance, them point is automatically outside a Beta distance.  

## Pointwise distance
Q is query point. βis maximum truncated distance. 
dmin=mind(Q,Pi),β
## Facewise distance
Q is query point. βis maximum truncated distance.
dmin=mindQ,Tj,β
Ref: Distance Between Point and Triangle in 3D (geometrictools.com)
(https://www.geometrictools.com/Documentation/DistancePoint3Triangle3.pdf)
Let Face Triangle be defined as Tjs,t 
Tjs,t= B +sE0 +tE1 ,∀ s≥0,t≥0,s+t≤1
Face Triangle to Point distance can be found using the formula
dQ,Tj=ds,t=as2 + 2bst + ct2 + 2ds + 2et + f
a = E0 · E0,b = E0 · E1,c = E1 · E1, 
d = E0 · B - P,e = E1 · B - P,f = (B - P) · (B - P)
d0,t= ct2 + 2et + f→t=-ec 
ds,0=as2 + 2ds + f→s=-da
ds,1-s=as2 + 2bs1-s+c1-s2 + 2ds+ 2e1-s+ f→
s=b+d-c-eb-c-a,t=b+e-a-db-c-a
=as+b1-s-b+cs-1+d-e=a-b+cs+b-c+d-e-da

## Brute force approach
Go over all the points and faces to find the minimum possible distance dmin  between target point and mesh points.
## Spatial indexing approach
Recommended approach of indexing is using octree, but in our case were going to implement a simple space map to spatially Index the mesh points. After indexing, find all the points and faces in a β sphere to minimize list of candidate Points to search.
Spatial indexing using CUDA, requires us to implement unordered map using CUDA. A vectorized unordered map is implemented using an additional vector container for storing indexes. The program is supposed to handle each spatial index on an individual CUDA thread. However, the process of indexing is still serial, as we have assumed this will not be repeated and is not time-constrained.
CUDA streams can be used to further enhance the concurrency of the data transfer process.
## Parallel Hashmap
A parallelized version of Hashing was also implemented.

## Thrust library function

typedef thrust::host_vector<double> Hvec;   
typedef thrust::host_vector<Point> HPoint;
typedef thrust::device_vector<double> Dvec; 
typedef thrust::device_vector<Point> DPoint;

double min_dist_calculation2(
const HPoint& Hpoints, 
const Point& target, 
const double& beta2
){
    DPoint points = Hpoints;
    Dvec distances(Hpoints.size());

    // apply the transformation
    thrust::transform(_ITER_(points), distances.begin(), dist2_point(target));
    return thrust::reduce(_ITER_(distances), beta2, min_dist());
}

## OUTPUT


- find materials in: /content/3DObjects/./cube.obj.mtl

Num of points : 3456
Num of faces : 1152
Bounding Box : Min(-1.000000,-1.000000,-1.000000) , Max(1.000000,1.000000,1.000001)
dist test : 
0.72
0.04
Point_index(-50,-50,-50)
Point_index(50,50,50)

###
Target point : Point(0,1,1.2)
Target point index : Point_index(0,50,60)
Beta : 0.3
Map size : 0.02

### ---------------------Pointwise(brute force)-----------------
Unsigned distance for Points (brute force) => 

Unsigned distance : 0.2
Target point : Point(0,1,1.2)
Nearest point : Point(-5e-07,1,1)


### -----------------------Facewise(brute force)---------------------------
Unsigned distance for Faces (brute force) => 

Unsigned distance : 0.2
Target point : Point(0,1,1.2)
Nearest Face : Face(870,871,872)


### ---------------------Pointwise(local)---------------------------
Unsigned distance for Points (space map) => 

Unsigned distance : 0.2
Target point : Point(0,1,1.2)
Nearest point : Point(-5e-07,1,1)


### ---------------------Pointwise(Serial)-----------------
Unsigned distance for Points (Serial) => 

DIMs : 
max_size_index : 16 , Threads_dim : 4 , blocks_dim : 8 , Dim : 32
(i0,  j0, k0) : ( -16 , 34 , 44 )
(i1,  j1, k1) : ( 16 , 66 , 76 )

Unsigned distance : 0.2
Target point : Point(0,1,1.2)


### -----------------------Facewise(Serial)---------------------------
Unsigned distance for Faces (Serial) => 

DIMs : 
max_size_index : 16 , Threads_dim : 4 , blocks_dim : 8 , Dim : 32
(i0,  j0, k0) : ( -16 , 34 , 44 )
(i1,  j1, k1) : ( 16 , 66 , 76 )

Unsigned distance : 0.2
Target point : Point(0,1,1.2)
Nearest Face : Face(870,871,872)




### 
**************************CUDA_TEST_BEGINS********************************
**************************CUDA_TEST_BEGINS********************************

{1,2,3,4,5} + {10,20,30,40,50} = {11,22,33,44,55}

**************************CUDA_TEST_SUCCESS********************************
**************************CUDA_TEST_SUCCESS********************************

### ---------------------Pointwise(cuda)---------------------------
Unsigned_distance_cuda_hash_table with Points => 

DIMs : 
max_size_index : 16 , Threads_dim : 4 , blocks_dim : 8 , Dim : 32
(i0,  j0, k0) : ( -16 , 34 , 44 )
(i1,  j1, k1) : ( 16 , 66 , 76 )
Kernel execution time: 0 ms

Unsigned distance : 0.2
Target point : Point(0,1,1.2)




### -----------------------Facewise(cuda)---------------------------
Unsigned_distance_cuda_hash_table with Faces => 

DIMs : 
max_size_index : 16 , Threads_dim : 4 , blocks_dim : 8 , Dim : 32
(i0,  j0, k0) : ( -16 , 34 , 44 )
(i1,  j1, k1) : ( 16 , 66 , 76 )
Kernel execution time: 0 ms

Unsigned distance : 0.2
Target point : Point(0,1,1.2)





