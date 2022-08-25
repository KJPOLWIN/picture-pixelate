#include <bitset>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include <string>

int main(int argc, char* argv[])
{
  if(argc != 3)
  {
    std::cout << "Usage: pixelate <filename> <pixel minification>\n";
    std::cout << "<filename> \t- Name of image to pixelate\n";
    std::cout << "<pixel minification> \t- How many pixels will be transformed into one pixel in output image. For example, with pixel minification = 3 a square 3x3 pixels will be transformed into one pixel on output image.\n";
  }
  else
  {
    int pixelRatio{ std::stoi(std::string(argv[2])) };

    sf::Image inputImage{  };
    if(!inputImage.loadFromFile(argv[1]))
    { 
      std::cerr << "Error: file not found\n";
      return 1;
    }

    sf::Image outputImage{  };
    int w{ static_cast<int>(ceil(static_cast<double>(inputImage.getSize().x) 
                                 / static_cast<double>(pixelRatio))) };
    int h{ static_cast<int>(ceil(static_cast<double>(inputImage.getSize().y) 
                                 / static_cast<double>(pixelRatio))) };
    outputImage.create(w, h);

    for(int y{ 0 }; y < h; ++y)
    {
      for(int x{ 0 }; x < w; ++x)
      {
        int r{ 0 };
        int g{ 0 };
        int b{ 0 };

        for(int subY{ 0 }; subY < pixelRatio; ++subY)
        {
          for(int subX{ 0 }; subX < pixelRatio; ++subX)
          {
            r += inputImage.getPixel(x * pixelRatio + subX, 
                                              y * pixelRatio + subY).r;
            g += inputImage.getPixel(x * pixelRatio + subX, 
                                              y * pixelRatio + subY).g;
            b += inputImage.getPixel(x * pixelRatio + subX, 
                                              y * pixelRatio + subY).b;
          }
        }

        sf::Color pixelColor{ sf::Uint8(r / pow(pixelRatio, 2)),
                              sf::Uint8(g / pow(pixelRatio, 2)),
                              sf::Uint8(b / pow(pixelRatio, 2)), };
        outputImage.setPixel(x, y, pixelColor);
      }
    }

    if(!outputImage.saveToFile("pixelated.png"))
    {
      std::cerr << "Error: output file cannot be saved\n";
    }
  }

  return 0;
}
