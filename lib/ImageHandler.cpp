#include "ImageHandler.h"

int ImageHandler::ALPHA = 16711935;

ImageHandler::ImageHandler(const char *filePath) {
    char aux, type;

    std::ifstream is(filePath);
    std::cout << filePath << std::endl;
    aux = is.get();
    if (aux != 'P') {
        // enviar erro
        std::cout << "Não é P\n";
    }

    aux = is.get();
    if (aux != '3' && aux != '6') {
        // enviar erro
        printf("Não é 3 nem 6 é %c \n",aux);
    }

    type = aux;
    aux = is.get();
    if (aux != '\n') {
        printf("Não é 'enter' é %c \n",aux);
    }

    aux = is.get();
    while (aux == '#') {
        while (aux != '\n') {
            aux = is.get();
        }

        aux = is.get();
    }

    char buff_w[5], buff_h[5], buff_max[3];
    int i = 1;
    buff_w[0] = aux;
    while (aux != ' ') {
        aux = is.get();
        buff_w[i++] = aux;
    }

    width = atoi(buff_w);

    aux = is.get();
    buff_h[0] = aux;
    i = 1;
    while (aux != '\n') {
        aux = is.get();
        buff_h[i++] = aux;
    }

    height = atoi(buff_h);

    aux = is.get();
    buff_max[0] = aux;
    i = 1;
    while (aux != '\n') {
        aux = is.get();
        buff_max[i++] = aux;
    }
    int max = atoi(buff_max);

    pixels = new int[width * height];

    int j = 0;
    if (type == '3') {
        for (j = width * height - 1; j >= 0; j--) {
            int r = 0, g = 0, b = 0;
            is >> r >> g >> b;
            pixels[j] =
                ( ( r * 255 / max ) << 16 ) |
                ( ( g * 255 / max ) << 8 ) |
                ( b * 255 / max );
        }
    } else {
        for (j = 0; j < width * height ;  j++) {
            unsigned char r, g, b;
            r = is.get();
            g = is.get();
            b = is.get();

            pixels[j] =
                ( ( b * 255 / max ) << 16 ) |
                ( ( g * 255 / max ) << 8 ) |
                ( r * 255 / max );

            if (pixels[j] != ImageHandler::ALPHA) {
                pixels[j] = pixels[j] | (255 << 24);
            }
        }
    }
}

int * ImageHandler::getPixels() {
    return pixels;
}

int ImageHandler::getWidth() {
    return width;
}

int ImageHandler::getHeight() {
    return height;
}
