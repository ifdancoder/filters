# Image Filters

Проект для обработки изображений с использованием различных фильтров, написанный на C++ с использованием OpenCV.

## Описание

Этот проект предоставляет набор фильтров для обработки изображений, включая:
- **Сверточные фильтры** (Convolution Filter)
- **Гауссов фильтр** (Gaussian Filter) (На основе Convolution Filter)
- **Медианный фильтр** (Median Filter)
- **Фильтр повышения резкости** (Sharpen Filter)
- **DoG фильтр** (Difference of Gaussians)
- **Пороговый фильтр** (Threshold Filter)

## Примеры

### Входное изображение:

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/input/input.jpg" height="350">
</p>

### Выходные изображения:

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/convolution.jpg" height="350">
</p>

#### **Сверточные фильтры** (Convolution Filter)

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/convolution.jpg" height="350">
</p>

#### **Гауссов фильтр** (Gaussian Filter)

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/gaussian.jpg" height="350">
</p>

#### **Медианный фильтр** (Median Filter)

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/median.jpg" height="350">
</p>

#### **Фильтр повышения резкости** (Sharpen Filter)

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/sharpen.jpg" height="350">
</p>

#### **DoG фильтр** (Difference of Gaussians)

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/dog.jpg" height="350">
</p>

#### **Пороговый фильтр** (Threshold Filter)

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/threshold.jpg" height="350">
</p>

## Архитектура

Проект использует паттерн **Decorator** для композиции фильтров и **Singleton** для управления изображениями.

### Основные компоненты:

- **Image** - базовый класс для работы с изображениями
- **Pixel** - класс для представления пикселя
- **ImageManager** - менеджер для загрузки, обработки и сохранения изображений
- **FilterDecorator** - базовый класс для всех фильтров
- **BaseImage** - базовый источник изображения

## Требования

- **CMake** 4.0+
- **C++20** компилятор
- **OpenCV** библиотека
- **HDF5** библиотека
- **dotenv** (автоматически загружается через FetchContent)

## Установка и сборка

1. Клонируйте репозиторий:
```bash
git clone <repository-url>
cd filters
```

2. Создайте директорию для сборки:
```bash
mkdir build
cd build
```

3. Соберите проект:
```bash
cmake ..
make
```

## Использование

### Настройка через переменные окружения

Создайте файл `.env` в корне проекта:
```env
INPUT_PATH=input/input.jpg
OUTPUT_PATH=output/output.jpg
```

### Программное использование

```cpp
#include "core/ImageManager.h"
#include "filters/GaussianFilter.h"
#include "filters/SharpenFilter.h"

int main() {
    ImageManager manager = ImageManager::getInstance();
    manager.loadByEnv();
    
    // Применение фильтра повышения резкости
    manager.applyFilter<SharpenFilter>(10, 1);
    
    // Применение гауссова фильтра
    manager.applyFilter<GaussianFilter>(1, 29, 0);
    
    // Сохранение результата
    manager.saveByEnv();
    
    return 0;
}
```

## Доступные фильтры

### 1. ConvolutionFilter
Базовый сверточный фильтр с пользовательским ядром.

```cpp
std::vector<std::vector<double>> kernel = {
    {1.0/9, 1.0/9, 1.0/9},
    {1.0/9, 1.0/9, 1.0/9},
    {1.0/9, 1.0/9, 1.0/9}
};
manager.applyFilter<ConvolutionFilter>(kernel, 1);
```

### 2. GaussianFilter
Гауссов фильтр для размытия изображения.

```cpp
manager.applyFilter<GaussianFilter>(sigma, kernelSize, padMode);
```

### 3. MedianFilter
Медианный фильтр для удаления шума.

```cpp
manager.applyFilter<MedianFilter>(radius);
```

### 4. SharpenFilter
Фильтр повышения резкости.

```cpp
manager.applyFilter<SharpenFilter>(strength, padMode);
```

### 5. DogFilter
Difference of Gaussians - фильтр для выделения границ.

```cpp
manager.applyFilter<DogFilter>(sigma1, sigma2);
```

### 6. ThresholdFilter
Пороговый фильтр для бинаризации.

```cpp
manager.applyFilter<ThresholdFilter>(threshold, invert);
```

## Структура проекта

```
filters/
├── include/
│   ├── core/
│   │   ├── Image.h
│   │   ├── Pixel.h
│   │   ├── ImageManager.h
│   │   └── IImageSource.h
│   └── filters/
│       ├── BaseImage.h
│       ├── FilterDecorator.h
│       ├── ConvolutionFilter.h
│       ├── GaussianFilter.h
│       ├── MedianFilter.h
│       ├── SharpenFilter.h
│       ├── DogFilter.h
│       └── ThresholdFilter.h
├── src/
│   ├── core/
│   └── filters/
├── main.cpp
├── CMakeLists.txt
└── README.md
```

## Примеры использования

### Обработка изображения с несколькими фильтрами

```cpp
ImageManager manager = ImageManager::getInstance();
manager.loadByEnv();

// Удаление шума
manager.applyFilter<MedianFilter>(1);

// Размытие
manager.applyFilter<GaussianFilter>(1, 15, 0);

// Повышение резкости
manager.applyFilter<SharpenFilter>(5, 1);

// Сохранение
manager.saveByEnv();
```

## Лицензия

Этот проект создан в образовательных целях.

## Автор

Создано IfDANCodeR в 2025 году.
