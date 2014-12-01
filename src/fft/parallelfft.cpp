#include "parallelfft.hpp"

float** ParallelFFT::GetAsFloatArrays(complex** A, int n)
{
	float* real = (float*)malloc(sizeof(float) * (n*n));
	float* img = (float*)malloc(sizeof(float) * (n*n));

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			real[i*n + j] = A[i][j].r;
			img[i*n + j] = A[i][j].i;
		}
	}
	float** result = (float**)malloc(sizeof(float*) * 2);
	result[0] = real; result[1] = img;

	return result;
}

complex** ParallelFFT::GetAsComplexMatrix(float* A[], int n)
{
	float* real = A[0];
	float* img = A[1];

	complex** result = (complex**)malloc(sizeof(complex) * (n*n));

	for (auto i = 0; i < n; i++)
	{
		for (auto j = 0; j < n; i++)
		{
			result[i][j].r = real[i + j];
			result[i][j].i = img[i + j];
		}
	}

	return result;
}

void ParallelFFT::FFT2D(complex** A, int n)
{
	float** clFFTInput = this->GetAsFloatArrays(A, n);

	// Perform computations on GPU:
	if (!this->PerformCalculations(clFFTInput, "forward", n, n))
	{
		std::cout << "The FFT could not be performed on the GPU, please debug :)\n";
		return;
	}

	A = this->GetAsComplexMatrix(clFFTInput, n);
}

int ParallelFFT::PerformCalculations(float** tab, const char* direction, int sizex, int sizey)
{
	int i;

	/* OpenCL variables. */
	cl_int err;
	cl_platform_id platform = 0;
	cl_device_id device = 0;
	cl_context_properties props[3] = { CL_CONTEXT_PLATFORM, 0, 0 };
	cl_context ctx = 0;
	cl_command_queue queue = 0;

	/* Input and Output buffer. */
	cl_mem buffersIn[2] = { 0, 0 };
	cl_mem buffersOut[2] = { 0, 0 };

	/* Temporary buffer. */
	cl_mem tmpBuffer = 0;

	/* Size of temp buffer. */
	size_t tmpBufferSize = 0;
	int status = 0;
	int ret = 0;

	/* Total size of FFT. */
	size_t N = sizex*sizey;

	/* FFT library realted declarations. */
	clfftPlanHandle planHandle;
	clfftDim dim = CLFFT_2D;
	size_t clLengths[2] = { sizex, sizey };

	/* Setup OpenCL environment. */
	err = clGetPlatformIDs(1, &platform, NULL);
	err = clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 1, &device, NULL);

	props[1] = (cl_context_properties)platform;
	ctx = clCreateContext(props, 1, &device, NULL, NULL, &err);
	queue = clCreateCommandQueue(ctx, device, 0, &err);

	/* Setup clFFT. */
	clfftSetupData fftSetup;
	err = clfftInitSetupData(&fftSetup);
	err = clfftSetup(&fftSetup);

	/* Create a default plan for a complex FFT. */
	err = clfftCreateDefaultPlan(&planHandle, ctx, dim, clLengths);

	/* Set plan parameters. */
	err = clfftSetPlanPrecision(planHandle, CLFFT_SINGLE);
	err = clfftSetLayout(planHandle, CLFFT_COMPLEX_PLANAR, CLFFT_COMPLEX_PLANAR);
	err = clfftSetResultLocation(planHandle, CLFFT_OUTOFPLACE);

	/* Bake the plan. */
	err = clfftBakePlan(planHandle, 1, &queue, NULL, NULL);

	/* Real and Imaginary arrays. */
	cl_float* inReal = (cl_float*)malloc(N * sizeof(cl_float));
	cl_float* inImag = (cl_float*)malloc(N * sizeof(cl_float));
	cl_float* outReal = (cl_float*)malloc(N * sizeof(cl_float));
	cl_float* outImag = (cl_float*)malloc(N * sizeof(cl_float));

	/* Initialization of inReal, inImag, outReal and outImag. */
	for (i = 0; i<N; i++)
	{
		inReal[i] = tab[0][i];
		inImag[i] = 0.0f;
		outReal[i] = 0.0f;
		outImag[i] = 0.0f;
	}

	/* Create temporary buffer. */
	status = clfftGetTmpBufSize(planHandle, &tmpBufferSize);

	if ((status == 0) && (tmpBufferSize > 0)) {
		tmpBuffer = clCreateBuffer(ctx, CL_MEM_READ_WRITE, tmpBufferSize, 0, &err);
		if (err != CL_SUCCESS)
			printf("Error with tmpBuffer clCreateBuffer\n");
	}

	/* Prepare OpenCL memory objects : create buffer for input. */
	buffersIn[0] = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		N * sizeof(cl_float), inReal, &err);
	if (err != CL_SUCCESS)
		printf("Error with buffersIn[0] clCreateBuffer\n");

	/* Enqueue write tab array into buffersIn[0]. */
	err = clEnqueueWriteBuffer(queue, buffersIn[0], CL_TRUE, 0, N *
		sizeof(float),
		inReal, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		printf("Error with buffersIn[0] clEnqueueWriteBuffer\n");

	/* Prepare OpenCL memory objects : create buffer for input. */
	buffersIn[1] = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR,
		N * sizeof(cl_float), inImag, &err);
	if (err != CL_SUCCESS)
		printf("Error with buffersIn[1] clCreateBuffer\n");

	/* Enqueue write tab array into buffersIn[1]. */
	err = clEnqueueWriteBuffer(queue, buffersIn[1], CL_TRUE, 0, N * sizeof(float),
		inImag, 0, NULL, NULL);
	if (err != CL_SUCCESS)
		printf("Error with buffersIn[1] clEnqueueWriteBuffer\n");

	/* Prepare OpenCL memory objects : create buffer for output. */
	buffersOut[0] = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, N *
		sizeof(cl_float), outReal, &err);
	if (err != CL_SUCCESS)
		printf("Error with buffersOut[0] clCreateBuffer\n");

	buffersOut[1] = clCreateBuffer(ctx, CL_MEM_READ_WRITE | CL_MEM_COPY_HOST_PTR, N *
		sizeof(cl_float), outImag, &err);
	if (err != CL_SUCCESS)
		printf("Error with buffersOut[1] clCreateBuffer\n");

	/* Execute Forward or Backward FFT. */
	if (strcmp(direction, "forward") == 0)
	{
		/* Execute the plan. */
		err = clfftEnqueueTransform(planHandle, CLFFT_FORWARD, 1, &queue, 0, NULL, NULL,
			buffersIn, buffersOut, tmpBuffer);
	}
	else if (strcmp(direction, "backward") == 0)
	{
		/* Execute the plan. */
		err = clfftEnqueueTransform(planHandle, CLFFT_BACKWARD, 1, &queue, 0, NULL, NULL,
			buffersIn, buffersOut, tmpBuffer);
	}

	/* Wait for calculations to be finished. */
	err = clFinish(queue);

	/* Fetch results of calculations : Real and Imaginary. */
	err = clEnqueueReadBuffer(queue, buffersOut[0], CL_TRUE, 0, N * sizeof(float), tab[0],
		0, NULL, NULL);

	err = clEnqueueReadBuffer(queue, buffersOut[1], CL_TRUE, 0, N * sizeof(float), tab[1],
		0, NULL, NULL);

	/* Release OpenCL memory objects. */
	clReleaseMemObject(buffersIn[0]);
	clReleaseMemObject(buffersIn[1]);
	clReleaseMemObject(buffersOut[0]);
	clReleaseMemObject(buffersOut[1]);
	clReleaseMemObject(tmpBuffer);

	/* Release the plan. */
	err = clfftDestroyPlan(&planHandle);

	/* Release clFFT library. */
	clfftTeardown();

	/* Release OpenCL working objects. */
	clReleaseCommandQueue(queue);
	clReleaseContext(ctx);

	return ret;
}