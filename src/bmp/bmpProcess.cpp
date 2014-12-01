#include "bmpProcess.hpp"

bmpProcessor::~bmpProcessor()
{
	if (this->GetBlue())
		free(this->GetBlue());
	if (this->GetGreen())
		free(this->GetGreen());
	if (this->GetRed())
		free(this->GetRed());
}

complex** allocateComplexMatrix(int n)
{
	complex** a = (complex**)malloc(sizeof(complex*)*n);
	for (int i = 0; i < n; i++)
		a[i] = (complex*)malloc(sizeof(complex)*n);
	return a;
}

bmpProcessor::bmpProcessor(char* filename)
{
	BMP bmpHandler;
	
	if (!bmpHandler.ReadFromFile(filename))
		return;

	if (bmpHandler.TellHeight()
		!= bmpHandler.TellWidth())
	{

		printf("%i\n", bmpHandler.TellHeight());
		printf("%i\n", bmpHandler.TellWidth());
		std::cout << "BMP file " << filename << " is not square sized.\n";
		this->bufferSize = -1;

		return;
	}

	int n = bmpHandler.TellHeight();

	this->bufferSize = n;

	this->red = allocateComplexMatrix(n);
	this->green = allocateComplexMatrix(n);
	this->blue = allocateComplexMatrix(n);

	for (int i = 0; i < this->bufferSize; i++)
	{
		for (int j = 0; j < this->bufferSize; j++)
		{
			RGBApixel px = bmpHandler.GetPixel(i, j);
			
			this->red[i][j] = { px.Red, 0 };
			this->green[i][j] = { px.Green, 0 };
			this->blue[i][j] = { px.Blue, 0 };
		}
	}
}