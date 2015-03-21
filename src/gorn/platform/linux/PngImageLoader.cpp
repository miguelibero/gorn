

#include <gorn/platform/linux/PngImageLoader.hpp>
#include <gorn/asset/Image.hpp>
#include <gorn/base/Exception.hpp>
#include <buffer.hpp>
#include <buffer_reader.hpp>
#include <cstring>
#include <png.h>

/**
 * this png loader is based on this blog post
 * http://www.piko3d.com/tutorials/libpng-tutorial-loading-png-files-from-streams
 */

#define PNGSIGSIZE 8

namespace gorn {

    bool PngImageLoader::validate(const buffer& inputData) const NOEXCEPT
    {
        buffer_reader input(inputData);
        png_byte pngSig[PNGSIGSIZE];
        memset(pngSig, 0, PNGSIGSIZE);
        bool isPng = false;
        input.read(reinterpret_cast<uint8_t*>(pngSig), PNGSIGSIZE);
        isPng = png_sig_cmp(pngSig, 0, PNGSIGSIZE) == 0;
        return isPng;
    }

    void readPngImage
        (png_structp pngPtr, png_bytep data, png_size_t length)
    {
        png_voidp a = png_get_io_ptr(pngPtr);
        static_cast<buffer_reader*>(a)
            ->read(data, length);
    }

    Image PngImageLoader::load(const buffer& inputData) const
    {
        buffer_reader input(inputData);
        png_structp pngPtr = png_create_read_struct(
            PNG_LIBPNG_VER_STRING, nullptr, nullptr, nullptr);
        if (!pngPtr)
        {
            throw Exception("Could not create png read structure.");
        }
        png_infop infoPtr = png_create_info_struct(pngPtr);
        if (!infoPtr)
        {
            png_destroy_read_struct(&pngPtr, nullptr, nullptr);
            throw Exception("Could not create png info structure.");
        }
        png_bytep* rowPtrs = nullptr;

        if (setjmp(png_jmpbuf(pngPtr)))
        {
            png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
            if (rowPtrs != nullptr)
            {
                delete[] rowPtrs;
            }
            throw Exception("Could not create png jump buffer.");
        }
        png_set_read_fn(pngPtr, (png_voidp)&input, readPngImage);

        png_read_info(pngPtr, infoPtr);
        png_uint_32 imgWidth   = png_get_image_width(pngPtr, infoPtr);
        png_uint_32 imgHeight  = png_get_image_height(pngPtr, infoPtr);
        png_uint_32 bitDepth   = png_get_bit_depth(pngPtr, infoPtr);
        png_uint_32 colorType = png_get_color_type(pngPtr, infoPtr);
        bool hasAlpha = false;

        if (colorType == PNG_COLOR_TYPE_PALETTE)
        {
            png_set_palette_to_rgb(pngPtr);
        }
        if (colorType == PNG_COLOR_TYPE_GRAY && bitDepth < 8)
        {
            png_set_expand_gray_1_2_4_to_8(pngPtr);
        }
        if (png_get_valid(pngPtr, infoPtr, PNG_INFO_tRNS))
        {
            png_set_tRNS_to_alpha(pngPtr);
        }
        if (bitDepth == 16)
        {
            png_set_strip_16(pngPtr);            
        }
        if (colorType == PNG_COLOR_TYPE_GRAY ||
            colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
        {
            png_set_gray_to_rgb(pngPtr);
        }
        if (colorType == PNG_COLOR_TYPE_RGB_ALPHA ||
            colorType == PNG_COLOR_TYPE_GRAY_ALPHA)
        {        
            hasAlpha = true;
        }

        png_read_update_info(pngPtr, infoPtr);
        const png_size_t rowBytes = png_get_rowbytes(pngPtr, infoPtr);
        rowPtrs = new png_bytep[imgHeight];
        const size_t len = rowBytes * imgHeight;
        buffer data(len);

        for (size_t i = 0; i < imgHeight; i++)
        {
            png_size_t q = (imgHeight - i - 1) * rowBytes;
            rowPtrs[i] = data.data() + q;
        }
        png_read_image(pngPtr, rowPtrs);
        png_read_end(pngPtr, NULL);

        delete[] rowPtrs;
        png_destroy_read_struct(&pngPtr, &infoPtr, nullptr);
        return Image(std::move(data),
            glm::vec2(imgWidth, imgHeight), hasAlpha, BasicType::UnsignedByte);
    }
}
