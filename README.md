ECSE 420 - Parallel Computing Project: perceptual-image-hash
=====================

A tool for finding similar images. The focus of the project is on measuring performance improvements of running the 2 algorithms in parallel on GPU using OpenCL vs when running them serial on CPU.

In order to simplify the details, we only process square grayscale images.

1st step) FFT
---
Convert the image into it's FFT representation, we only keep the magnitude as we won't have to revert the transformation.

2nd step) Run a "perceptual hash" on the FFT representation of the image
---
The goal of the perceptual hash is to hash in such a way that lower frequencies have a higher effect on the hash result. The reason behind the idea is that lower frequencies represent a bigger chunk of information of the image whereas higher frequencies represent more the small details of the image. By having the lower frequencies have more effect on the hash, we expect that images which have a higher similarity will hash to numbers close to each other. We are going to verify our hypothesis once the application is built.

Details on the perceptual hashing:
If we have an image that has NxN pixels and it was transformed into FFT so it represents NxN frequencies.
We are going to generate N prime number using sieving.
The frequencies matrix is going to be divided into N parts (going from low-to-high freq.). Each part is associated with one of the prime numbers (lower frequencies are associated with the larger prime numbers), all the values in that part are summed and multiplied with that prime number. The result of multiplication from each part is added together to get the final hash value.
