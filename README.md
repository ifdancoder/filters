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
- **Фильтр мозаики** (Mosaic Filter)
- **Фильтр Кэнни** (Canny Edge Detection)
- **Морфологические фильтры** (Morphological Filters):
  - Бинарные: эрозия, дилатация, открытие, закрытие
  - Полутоновые: эрозия, дилатация, открытие, закрытие
  - Выделение контуров и многомасштабный градиент

## Примеры

### Входное изображение:

<p align="center">
    <img alt="MySQL" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/input/input.jpg" height="350">
</p>

### Выходные изображения:

#### **Сверточные фильтры** (Convolution Filter)

```cpp
std::vector<std::vector<double>> box3 = {
    {1.0/9, 1.0/9, 1.0/9},
    {1.0/9, 1.0/9, 1.0/9},
    {1.0/9, 1.0/9, 1.0/9}
};
manager.applyFilter<ConvolutionFilter>(/*kernel=*/box3, /*padding=*/1);
```

<p align="center">
    <img alt="Сверточные фильтры" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/convolution.jpg" height="350">
</p>

#### **Гауссов фильтр** (Gaussian Filter)

```cpp
manager.applyFilter<GaussianFilter>(/*sigma=*/1, /*kernel_size=*/29, /*padding=*/0);
```

<p align="center">
    <img alt="Гауссов фильтр" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/gaussian.jpg" height="350">
</p>

#### **Медианный фильтр** (Median Filter)

```cpp
manager.applyFilter<MedianFilter>(/*radius=*/1);
```

<p align="center">
    <img alt="Медианный фильтр" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/median.jpg" height="350">
</p>

#### **Фильтр повышения резкости** (Sharpen Filter)

```cpp
manager.applyFilter<SharpenFilter>(/*strength=*/10, /*padding=*/1);
```

<p align="center">
    <img alt="Фильтр повышения резкости" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/sharpen.jpg" height="350">
</p>

#### **DoG фильтр** (Difference of Gaussians)

```cpp
manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/10, /*kernel_size=*/1, /*padding=*/1);
```

<p align="center">
    <img alt="DoG фильтр" src="https://raw.githubusercontent.com/ifdancoder/filters/4320e36872a8ab7f7c5db7373dedda025bdb8ad1/output/dog.jpg" height="350">
</p>

#### **Пороговый фильтр** (Threshold Filter)

```cpp
manager.applyFilter<ThresholdFilter>(/*threshold=*/45, /*inversion=*/1);
```

<p align="center">
    <img alt="Пороговый фильтр" src="https://raw.githubusercontent.com/ifdancoder/filters/65738cdf54615145494f7daed0593ac86383a105/output/threshold.jpg" height="350">
</p>

#### **Mosaic фильтр**

```cpp
manager.applyFilter<MosaicFilter>(/*size=*/10);
```

<p align="center">
    <img alt="Mosaic фильтр" src="https://raw.githubusercontent.com/ifdancoder/filters/f85bd752ead6b9b3b1c7527b6fd76f58bbf6d104/output/mosaic.jpg" height="350">
</p>

#### **DoG + Вертикальный Sobel фильтры**

```cpp
manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/1, /*kernel_size=*/5, /*padding=*/2);
manager.applyFilter<SobelVerticalFilter>();
```

<p align="center">
    <img alt="DoG + Вертикальный Sobel фильтры" src="https://raw.githubusercontent.com/ifdancoder/filters/5a08fbba2d64c0fc571aa6ab5771835b44409696/output/dog_sobel_vertical.jpg" height="350">
</p>

#### **DoG + Горизонтальный Sobel фильтры**

```cpp
manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/1, /*kernel_size=*/5, /*padding=*/2);
manager.applyFilter<SobelHorizontalFilter>();
```

<p align="center">
    <img alt="DoG + Горизонтальный Sobel фильтры" src="https://raw.githubusercontent.com/ifdancoder/filters/5a08fbba2d64c0fc571aa6ab5771835b44409696/output/dog_sobel_horizontal.jpg" height="350">
</p>

#### **DoG + Диагональный Sobel фильтры**

```cpp
manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/1, /*kernel_size=*/5, /*padding=*/2);
manager.applyFilter<SobelDiagonalFilter>();
```

<p align="center">
    <img alt="DoG + Диагональный Sobel фильтры" src="https://raw.githubusercontent.com/ifdancoder/filters/5a08fbba2d64c0fc571aa6ab5771835b44409696/output/dog_sobel_diagonal.jpg" height="350">
</p>

#### **Canny фильтр**

```cpp
manager.applyFilter<CannyFilter>(/*low=*/ 5.0, /*high=*/ 60.0);
```

<p align="center">
    <img alt="Canny фильтр" src="https://raw.githubusercontent.com/ifdancoder/filters/5a08fbba2d64c0fc571aa6ab5771835b44409696/output/canny.jpg" height="350">
</p>

#### **DoG + Canny фильтры**

```cpp
manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/1, /*kernel_size=*/5, /*padding=*/2);
manager.applyFilter<CannyFilter>(/*low=*/ 5.0, /*high=*/ 60.0);
```

<p align="center">
    <img alt="DoG + Canny фильтры" src="https://raw.githubusercontent.com/ifdancoder/filters/5a08fbba2d64c0fc571aa6ab5771835b44409696/output/dog_canny.jpg" height="350">
</p>

#### **Фильтр бинарной эрозии**

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<BinaryErosionFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Фильтр бинарной эрозии" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/binary_erosion.jpg" height="350">
</p>

#### **Фильтр бинарной дилатации**

```cpp
auto se = StructuringElement::createCross(3);
manager.applyFilter<BinaryDilationFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Фильтр бинарной дилатации" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/binary_dilation.jpg" height="350">
</p>

#### **Оператор закрытия**

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<BinaryClosingFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Оператор закрытия" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/binary_closing.jpg" height="350">
</p>

#### **Оператор открытия**

```cpp
auto se = StructuringElement::createDisk(3);
manager.applyFilter<BinaryOpeningFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Оператор открытия" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/binary_opening.jpg" height="350">
</p>

#### **Фильтр полутоновой эрозии**

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<GrayscaleErosionFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Фильтр полутоновой эрозии" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/grayscale_erosion.jpg" height="350">
</p>

#### **Фильтр полутоновой дилатации**

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<GrayscaleDilationFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Фильтр полутоновой дилатации" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/grayscale_dilation.jpg" height="350">
</p>

#### **Оператор закрытия**

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<GrayscaleClosingFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Оператор закрытия" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/grayscale_closing.jpg" height="350">
</p>

#### **Оператор открытия**

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<GrayscaleOpeningFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Оператор открытия" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/grayscale_opening.jpg" height="350">
</p>

#### **Оператор выделения контуров**

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<EdgeDetectionFilter>(/*structuring_element=*/se);
```

<p align="center">
    <img alt="Оператор выделения контуров" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/grayscale_edge_detection.jpg" height="350">
</p>

#### **Многомасштабный морфологический градиент**

```cpp
manager.applyFilter<MorphologicalGradientFilter>(/*structuring_element=*/StructuringElement::SQUARE, /*iterations=*/3);
```

<p align="center">
    <img alt="Многомасштабный морфологический градиент" src="https://raw.githubusercontent.com/ifdancoder/filters/b17859005a9e4029036d5f1dfbaf54772f8a356b/output/grayscale_morphological_gradient.jpg" height="350">
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

Создайте файл `.env` в папке с исполняемым файлом:
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
manager.applyFilter<ConvolutionFilter>(/*kernel=*/kernel, /*padding=*/1);
```

**Параметры:**
- `kernel` - матрица ядра свертки
- `padding` - режим обработки границ (0 = нулевое заполнение, 1 = отражение)

### 2. GaussianFilter
Гауссов фильтр для размытия изображения.

```cpp
manager.applyFilter<GaussianFilter>(/*sigma=*/1, /*kernel_size=*/29, /*padding=*/0);
```

**Параметры:**
- `sigma` - стандартное отклонение гауссова распределения (сила размытия)
- `kernel_size` - размер ядра (если 0, вычисляется автоматически)
- `padding` - режим обработки границ

### 3. MedianFilter
Медианный фильтр для удаления шума.

```cpp
manager.applyFilter<MedianFilter>(/*radius=*/1);
```

**Параметры:**
- `radius` - радиус окна для медианной фильтрации

### 4. SharpenFilter
Фильтр повышения резкости.

```cpp
manager.applyFilter<SharpenFilter>(/*strength=*/10, /*padding=*/1);
```

**Параметры:**
- `strength` - сила повышения резкости
- `padding` - режим обработки границ

### 5. DogFilter
Difference of Gaussians - фильтр для выделения границ.

```cpp
manager.applyFilter<DogFilter>(/*sigma1=*/3, /*sigma2=*/10, /*kernel_size=*/1, /*padding=*/1);
```

**Параметры:**
- `sigma1` - стандартное отклонение первого гауссова ядра
- `sigma2` - стандартное отклонение второго гауссова ядра (должно быть больше sigma1)
- `kernel_size` - размер ядра (если 0, вычисляется автоматически)
- `padding` - режим обработки границ

### 6. ThresholdFilter
Пороговый фильтр для бинаризации.

```cpp
manager.applyFilter<ThresholdFilter>(/*threshold=*/45, /*inversion=*/1);
```

**Параметры:**
- `threshold` - пороговое значение (0-255)
- `inversion` - инверсия результата (0 = обычная бинаризация, 1 = инвертированная)

### 7. MosaicFilter
Фильтр мозаики - разбивает изображение на блоки и заполняет каждый блок средним цветом.

```cpp
manager.applyFilter<MosaicFilter>(/*size=*/10);
```

**Параметры:**
- `size` - размер блока мозаики в пикселях (по умолчанию 10)

### 8. CannyFilter
Детектор границ Кэнни - многоэтапный алгоритм для обнаружения границ на изображении.

```cpp
manager.applyFilter<CannyFilter>(/*low=*/40.0, /*high=*/200.0);
```

**Параметры:**
- `low` - нижний порог для двойной пороговой фильтрации (по умолчанию 40.0)
- `high` - верхний порог для двойной пороговой фильтрации (по умолчанию 200.0)
- `sigma` - параметр размытия по Гауссу для подавления шума (по умолчанию 1.4)

**Этапы алгоритма:**
1. Размытие по Гауссу для снижения шума
2. Вычисление градиентов с помощью оператора Собеля
3. Подавление немаксимумов
4. Двойная пороговая фильтрация (сильные/слабые границы)
5. Трассировка границ методом гистерезиса

## Морфологические фильтры

### 9. BinaryErosionFilter
Бинарная эрозия - сжимает объекты и удаляет мелкие детали.

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<BinaryErosionFilter>(/*structuring_element=*/se);
```

**Параметры:**
- `structuring_element` - структурный элемент (квадрат, крест, диск)

### 10. BinaryDilationFilter
Бинарная дилатация - расширяет объекты и заполняет пробелы.

```cpp
auto se = StructuringElement::createCross(3);
manager.applyFilter<BinaryDilationFilter>(/*structuring_element=*/se);
```

### 11. BinaryOpeningFilter
Бинарное открытие - эрозия + дилатация. Удаляет шум "соль".

```cpp
auto se = StructuringElement::createDisk(3);
manager.applyFilter<BinaryOpeningFilter>(/*structuring_element=*/se);
```

### 12. BinaryClosingFilter
Бинарное закрытие - дилатация + эрозия. Удаляет шум "перец".

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<BinaryClosingFilter>(/*structuring_element=*/se);
```

### 13. GrayscaleErosionFilter
Полутоновая эрозия - находит минимум в области структурного элемента.

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<GrayscaleErosionFilter>(/*structuring_element=*/se);
```

### 14. GrayscaleDilationFilter
Полутоновая дилатация - находит максимум в области структурного элемента.

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<GrayscaleDilationFilter>(/*structuring_element=*/se);
```

### 15. GrayscaleOpeningFilter
Полутоновое открытие - сглаживает контуры, удаляет пики.

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<GrayscaleOpeningFilter>(/*structuring_element=*/se);
```

### 16. GrayscaleClosingFilter
Полутоновое закрытие - заполняет впадины, сглаживает контуры.

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<GrayscaleClosingFilter>(/*structuring_element=*/se);
```

### 17. EdgeDetectionFilter
Выделение контуров - разность между дилатацией и эрозией.

```cpp
auto se = StructuringElement::createSquare(3);
manager.applyFilter<EdgeDetectionFilter>(/*structuring_element=*/se);
```

### 18. MorphologicalGradientFilter
Многомасштабный морфологический градиент - использует несколько размеров структурных элементов.

```cpp
manager.applyFilter<MorphologicalGradientFilter>(/*structuring_element=*/StructuringElement::SQUARE, /*iterations=*/3);
```

**Параметры:** Нет (использует встроенные структурные элементы 3x3, 5x5, 7x7)

## Структурные элементы

### Создание структурных элементов:

```cpp
// Квадратный элемент 3x3
auto square = StructuringElement::createSquare(3);

// Крестообразный элемент 3x3
auto cross = StructuringElement::createCross(3);

// Диск радиусом 3
auto disk = StructuringElement::createDisk(3);
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
│       ├── ThresholdFilter.h
│       ├── MosaicFilter.h
│       ├── CannyFilter.h
│       ├── StructuringElement.h
│       ├── BinaryErosionFilter.h
│       ├── BinaryDilationFilter.h
│       ├── BinaryOpeningFilter.h
│       ├── BinaryClosingFilter.h
│       ├── GrayscaleErosionFilter.h
│       ├── GrayscaleDilationFilter.h
│       ├── GrayscaleOpeningFilter.h
│       ├── GrayscaleClosingFilter.h
│       ├── EdgeDetectionFilter.h
│       └── MorphologicalGradientFilter.h
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
