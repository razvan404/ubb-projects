# Project 2 - CUDA Convolution

## Approach

For this one, we needed to do convolution using CUDA. The pipeline is simple, reading the matrix from the file, allocating the CUDA memory for the input matrix, the filter and the output matrix and moved the input matrix and the filter to the device (GPU) from the host (CPU), started at least N * M threads (N, M being the dimensions of the matrix) by using different 2D block sizes and 2D grid size, then each thread, if it has a valid position in the matrix, will perform the convolution operation with the filter, keeping in mind that for the border elements we took the closest element from the matrix, then, after all the convolution operations were done, we wrote the output matrix data to our initial matrix from the device to the host, and lastly, we printed the matrix in the output file. The matrices were saved in a flatten way, because our version of CUDA Toolkit (12.1) doesn't allow 2D matrices.

## Results comparing Sequential and CUDA with block size 16x16

| Type       |   Matrix Size |   Filter Size |       Time |
|:-----------|--------------:|--------------:|-----------:|
| Sequential |            24 |             3 |    0.00974 |
| CUDA       |            24 |             3 |  195.37    |
| Sequential |           120 |             5 |    0.44835 |
| CUDA       |           120 |             5 |   93.2909  |
| Sequential |           720 |             7 |   29.4128  |
| CUDA       |           720 |             7 |  103.853   |
| Sequential |          2500 |             9 |  585.057   |
| CUDA       |          2500 |             9 |  296.452   |
| Sequential |          6400 |            11 | 6832.96    |
| CUDA       |          6400 |            11 | 1513.88    |


## Interpretation at the Sequential vs CUDA with block size 16x16 results
We can observe that for the first 3 tests the sequential data is faster than the CUDA implementation, that's probably because it takes some time to allocate the memory and to send the data to the device, and it's not worth for the test size, but we can observe that for the last two tests, there is a clear improvement, so it's usually better to use CUDA when dealing with bigger chunks of data. I will also add the fact that we measured only the time of processing the data on the Sequential approach, the reading and writing to the file took the longest in all the tests, while on CUDA tests we also meassured the time of allocating and moving the data to the device.

# Results comparing Sequential and CUDA with different block sizes
| Type       | Block Dim   |   Matrix Size |   Filter Size |          Time |
|:-----------|:------------|--------------:|--------------:|--------------:|
| Sequential | -           |            24 |             3 |    0.00813333 |
| CUDA       | 16          |            24 |             3 |  159.001      |
| CUDA       | 64          |            24 |             3 |  116.596      |
| CUDA       | 256         |            24 |             3 |  108.121      |
| CUDA       | 1024        |            24 |             3 |  102.292      |
| Sequential | -           |           120 |             5 |    0.4459     |
| CUDA       | 16          |           120 |             5 |  104.505      |
| CUDA       | 64          |           120 |             5 |  101.728      |
| CUDA       | 256         |           120 |             5 |   96.7105     |
| CUDA       | 1024        |           120 |             5 |   98.9948     |
| Sequential | -           |           720 |             7 |   31.0266     |
| CUDA       | 16          |           720 |             7 |   95.8603     |
| CUDA       | 64          |           720 |             7 |   98.2653     |
| CUDA       | 256         |           720 |             7 |   98.1262     |
| CUDA       | 1024        |           720 |             7 |  102.705      |
| Sequential | -           |          2500 |             9 |  572.946      |
| CUDA       | 16          |          2500 |             9 |  195.22       |
| CUDA       | 64          |          2500 |             9 |  172.032      |
| CUDA       | 256         |          2500 |             9 |  165.174      |
| CUDA       | 1024        |          2500 |             9 |  187.693      |
| Sequential | -           |          6400 |            11 | 6207.42       |
| CUDA       | 16          |          6400 |            11 |  412.165      |
| CUDA       | 64          |          6400 |            11 |  350.212      |
| CUDA       | 256         |          6400 |            11 |  463.012      |
| CUDA       | 1024        |          6400 |            11 |  701.934      |

# Interpretation at the Sequential vs CUDA with different block sizes results
We can see that between Sequential and CUDA it's almost the same differences as before. We can also see that the 4x4 block size performed worse than the others in almost all cases, but it's a bit different for the other tests. For these test cases, we used 3 runs / test instead of 10 runs / test, because it was taking way longer than the other, and that's why it may be a bit more inconsistent, but otherwise, there is not a big difference between 8x8, 16x16 and 32x32 test cases.