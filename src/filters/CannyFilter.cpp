//
// Created by ifdancoder on 16.11.2025.
//

#include "filters/CannyFilter.h"
#include "filters/GaussianFilter.h"
#include <algorithm>
#include <queue>
#include <opencv2/imgproc.hpp>

CannyFilter::CannyFilter(std::shared_ptr<IImageSource> src,
                         double low,
                         double high)
    : FilterDecorator(std::move(src)), lowThreshold(low), highThreshold(high) {
}

std::shared_ptr<Image> CannyFilter::applyFilter(std::shared_ptr<Image> in) const {
    cv::Mat contour;

    cv::Canny(in->toMat(), contour, lowThreshold, highThreshold);

    return std::make_shared<Image>(contour);
}
