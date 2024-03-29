#include "MRI.hpp"
  
MRI::MRI(string path)
{
  
  ifstream mriFile (path.c_str(), ios::in | ios::binary);

  //loop through MRI file and seperate each pixel into its x,y,z cordinate
  for (int z = 0; z < depth; z++)
    {
      for (int y = 0; y < height; y++)
	{
	  for (int x = 0; x < width; x++)
	    {
	      //place data into a char buffer and then reinterpret into an unsigned char
	      char pix[1];
	      mriFile.read(pix, 1);
	      data[x][y][z] = reinterpret_cast<unsigned char&>(pix[0]);
	    }
	}
    }

  //loop through the data and generate chunks
  for (int z = 0; z < chunkDepth; z++)
    {
      for (int y = 0; y < chunkHeight; y++)
	{
	  for (int x = 0; x < chunkWidth; x++)
	    {
	      //generate chunk if it doesn't exist and populate it with correct information
	      chunks[x][y][z] = Chunk();
	      chunks[x][y][z].chunkSizeX = chunkSize;
	      chunks[x][y][z].chunkSizeY = chunkSize;
	      chunks[x][y][z].chunkSizeZ = chunkSize;
	      chunks[x][y][z].chunkX = x * chunkSize;
	      chunks[x][y][z].chunkY = y * chunkSize;
	      chunks[x][y][z].chunkZ = z * chunkSize;
	      chunks[x][y][z].parent = this;
	      chunks[x][y][z].init();
	    }
	}
    } 
  
}

void MRI::update(Camera &camera)
{
  
  //loop through the data and generate chunks
  for (int z = 0; z < chunkDepth; z++)
    {
      for (int y = 0; y < chunkHeight; y++)
	{
	  for (int x = 0; x < chunkWidth; x++)
	    {
	      chunks[x][y][z].update(camera);
	    }
	}
    }
}
