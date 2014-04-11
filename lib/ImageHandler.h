#ifndef __ImageHandler
  #define __ImageHandler

  #include "includes.h"

  class ImageHandler {
      public:
          ImageHandler(int,int);
          ImageHandler(const char*);
          int* getPixels(void);
          int getWidth(void);
          int getHeight(void);
          static int ALPHA;
      private:
          int width, height, *pixels;
  };
#endif
