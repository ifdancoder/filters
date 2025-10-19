//
// Created by ifdancoder on 13.10.2025.
//

#include "core/Image.h"

#include <opencv2/imgproc.hpp>

#include "core/Pixel.h"

Image::Image(int width, int height) : w(width), h(height), data(w * h, Pixel()) {
}

Image::Image(const cv::Mat& image) {
    if (image.empty()) {
        w = 0;
        h = 0;
        data.clear();
        return;
    }

    cv::Mat rgbImage;
    if (image.channels() == 1) {
        cv::cvtColor(image, rgbImage, cv::COLOR_GRAY2RGB);
    } else if (image.channels() == 3) {
        cv::cvtColor(image, rgbImage, cv::COLOR_BGR2RGB);
    } else if (image.channels() == 4) {
        cv::cvtColor(image, rgbImage, cv::COLOR_BGRA2RGB);
    } else {
        w = 0;
        h = 0;
        data.clear();
        return;
    }

    w = rgbImage.cols;
    h = rgbImage.rows;

    data.resize(w * h);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            cv::Vec3b pixel = rgbImage.at<cv::Vec3b>(y, x);
            data[y * w + x] = Pixel(pixel[0], pixel[1], pixel[2]); // R, G, B
        }
    }
}

cv::Mat Image::toMat() const {
    if (data.empty() || w == 0 || h == 0) {
        return {};
    }

    cv::Mat mat(h, w, CV_8UC3);

    for (int y = 0; y < h; ++y) {
        for (int x = 0; x < w; ++x) {
            const Pixel& pixel = data[y * w + x];
            auto& matPixel = mat.at<cv::Vec3b>(y, x);
            matPixel[0] = pixel.getR();
            matPixel[1] = pixel.getG();
            matPixel[2] = pixel.getB();
        }
    }

    cv::Mat bgrMat;
    cv::cvtColor(mat, bgrMat, cv::COLOR_RGB2BGR);

    return bgrMat;
}

Pixel& Image::at(int i) {
    return data[i];
}

Pixel& Image::at(int x, int y) {
    return at(y * w + x);
}

const Pixel &Image::at(int i) const {
    return data[i];
}

const Pixel& Image::at(int x, int y) const {
    return at(y * w + x);
}

int Image::getWidth() const {
    return w;
}

int Image::getHeight() const {
    return h;
}
