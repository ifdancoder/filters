//
// Created by ifdancoder on 16.11.2025.
//

#include "filters/CannyFilter.h"
#include "filters/GaussianFilter.h"
#include "core/Pixel.h"
#include <cmath>
#include <algorithm>
#include <queue>

CannyFilter::CannyFilter(std::shared_ptr<IImageSource> src,
                         double low,
                         double high,
                         double sigma)
    : FilterDecorator(std::move(src)), lowThreshold(low), highThreshold(high), sigma(sigma) {
}

std::shared_ptr<Image> CannyFilter::applyFilter(std::shared_ptr<Image> in) const {
    int width = in->getWidth();
    int height = in->getHeight();

    int kernelSize = static_cast<int>(std::ceil(6 * sigma));
    if (kernelSize % 2 == 0) kernelSize++;
    auto gaussianKernel = GaussianFilter::createGaussianKernel(kernelSize, sigma);

    auto blurred = std::make_shared<Image>(width, height);
    int pad = kernelSize / 2;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            double sumR = 0.0, sumG = 0.0, sumB = 0.0;

            for (int ky = 0; ky < kernelSize; ++ky) {
                for (int kx = 0; kx < kernelSize; ++kx) {
                    int ix = std::clamp(x + kx - pad, 0, width - 1);
                    int iy = std::clamp(y + ky - pad, 0, height - 1);
                    const auto& pixel = in->at(ix, iy);

                    sumR += pixel.getR() * gaussianKernel[ky][kx];
                    sumG += pixel.getG() * gaussianKernel[ky][kx];
                    sumB += pixel.getB() * gaussianKernel[ky][kx];
                }
            }

            blurred->at(x, y) = Pixel(
                static_cast<int>(std::clamp(sumR, 0.0, 255.0)),
                static_cast<int>(std::clamp(sumG, 0.0, 255.0)),
                static_cast<int>(std::clamp(sumB, 0.0, 255.0))
            );
        }
    }

    std::vector<std::vector<double>> magnitude(height, std::vector<double>(width));
    std::vector<std::vector<double>> direction(height, std::vector<double>(width));
    computeGradients(blurred, magnitude, direction);

    std::vector<std::vector<double>> suppressed(height, std::vector<double>(width));
    nonMaximumSuppression(magnitude, direction, suppressed);

    std::vector<std::vector<int>> edges(height, std::vector<int>(width, 0));
    doubleThreshold(suppressed, edges);

    edgeTracking(edges);

    auto out = std::make_shared<Image>(width, height);
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int value = (edges[y][x] == 2) ? 255 : 0;
            out->at(x, y) = Pixel(value, value, value);
        }
    }

    return out;
}

void CannyFilter::computeGradients(const std::shared_ptr<Image>& image,
                                   std::vector<std::vector<double>>& magnitude,
                                   std::vector<std::vector<double>>& direction) {
    int width = image->getWidth();
    int height = image->getHeight();

    int sobelX[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int sobelY[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double gx = 0.0, gy = 0.0;

            for (int ky = -1; ky <= 1; ++ky) {
                for (int kx = -1; kx <= 1; ++kx) {
                    const auto& pixel = image->at(x + kx, y + ky);
                    double gray = 0.299 * pixel.getR() + 0.587 * pixel.getG() + 0.114 * pixel.getB();

                    gx += gray * sobelX[ky + 1][kx + 1];
                    gy += gray * sobelY[ky + 1][kx + 1];
                }
            }

            magnitude[y][x] = std::sqrt(gx * gx + gy * gy);
            direction[y][x] = std::atan2(gy, gx);
        }
    }
}

void CannyFilter::nonMaximumSuppression(const std::vector<std::vector<double>>& magnitude,
                                       const std::vector<std::vector<double>>& direction,
                                       std::vector<std::vector<double>>& suppressed) {
    int height = magnitude.size();
    int width = magnitude[0].size();

    for (int y = 1; y < height - 1; ++y) {
        for (int x = 1; x < width - 1; ++x) {
            double angle = direction[y][x] * 180.0 / M_PI;
            if (angle < 0) angle += 180.0;

            double q = 255.0, r = 255.0;

            if ((angle >= 0 && angle < 22.5) || (angle >= 157.5 && angle <= 180)) {
                q = magnitude[y][x + 1];
                r = magnitude[y][x - 1];
            } else if (angle >= 22.5 && angle < 67.5) {
                q = magnitude[y + 1][x - 1];
                r = magnitude[y - 1][x + 1];
            } else if (angle >= 67.5 && angle < 112.5) {
                q = magnitude[y + 1][x];
                r = magnitude[y - 1][x];
            } else if (angle >= 112.5 && angle < 157.5) {
                q = magnitude[y - 1][x - 1];
                r = magnitude[y + 1][x + 1];
            }

            if (magnitude[y][x] >= q && magnitude[y][x] >= r) {
                suppressed[y][x] = magnitude[y][x];
            } else {
                suppressed[y][x] = 0;
            }
        }
    }
}

void CannyFilter::doubleThreshold(const std::vector<std::vector<double>>& suppressed,
                                 std::vector<std::vector<int>>& edges) const {
    int height = suppressed.size();
    int width = suppressed[0].size();

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (suppressed[y][x] >= highThreshold) {
                edges[y][x] = 2; // Сильная граница
            } else if (suppressed[y][x] >= lowThreshold) {
                edges[y][x] = 1; // Слабая граница
            } else {
                edges[y][x] = 0;
            }
        }
    }
}

void CannyFilter::edgeTracking(std::vector<std::vector<int>>& edges) {
    int height = edges.size();
    int width = edges[0].size();

    std::queue<std::pair<int, int>> strongEdges;

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (edges[y][x] == 2) {
                strongEdges.push({x, y});
            }
        }
    }

    int dx[] = {-1, 0, 1, -1, 1, -1, 0, 1};
    int dy[] = {-1, -1, -1, 0, 0, 1, 1, 1};

    while (!strongEdges.empty()) {
        auto [x, y] = strongEdges.front();
        strongEdges.pop();

        for (int i = 0; i < 8; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height && edges[ny][nx] == 1) {
                edges[ny][nx] = 2;
                strongEdges.push({nx, ny});
            }
        }
    }

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            if (edges[y][x] == 1) {
                edges[y][x] = 0;
            }
        }
    }
}

