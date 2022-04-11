#include <random>
#include <ctime>
#include <iostream>
#include <chrono>

// MEDIANO NAREDI

void menu() {
    std::cout << "1 ... GENERATE RANDOM ARRAY" << std::endl;
    std::cout << "2 ... GENERATE ASCENDING ARRAY" << std::endl;
    std::cout << "3 ... GENERATE DESCENDING ARRAY" << std::endl;
    std::cout << "4 ... PRINT ARRAY" << std::endl;
    std::cout << "5 ... CHECK, IF THE ARRAY IS SORTED" << std::endl;
    std::cout << "6 ... QUICKSORT WITHOUT MEDIAN" << std::endl;
    std::cout << "7 ... QUICKSORT WITH MEDIAN" << std::endl;
    std::cout << "8 ... SELECTION SORT" << std::endl;
    std::cout << "9 ... COUNTING SORT" << std::endl;
    std::cout << "10 ... ROMAN SORT" << std::endl;
    std::cout << "11 ... BUBBLE SORT" << std::endl;
    std::cout << "12 ... INSERTION SORT" << std::endl;
    std::cout << "13 ... MERGE SORT" << std::endl;
}

int inputNum(int& num) {
    std::cin >> num;
    return num;
}

void randomArray(int* arr, unsigned int size) {
    for(int i = 0; i < size; i++) {
        arr[i] = rand()% size;
    }
}

void randomAscendingArray(int* arr, unsigned int size) {
    int c = 0;
    for(int i = 0; i < size; i++) {
        arr[i] = rand()%10 + c;
        c++;
    }
}

void randomDescendingArray(int* arr, unsigned int size) {
    int c = size;
    for(int i = 0; i < size; i++) {
        arr[i] = rand()%10 + c;
        c--;
    }
}

void printArray(int* arr , unsigned int size) {
    for(int i = 0; i < size; i++) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

bool isSorted(int* arr, int bot, int top) {
    for(int i = bot; i < top-1; i++) {
        for(int j = i+1; j < top; j++) {
            if(arr[i] > arr[j]) {
                return false;
            }
        }
    }
    return true;
}

// namesto std::swap al pa da bi nardil "bubble" znotraj divide
int swap(int* x, int* y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

int getMax(int* arr, unsigned int size) {
    int MAX = arr[0];
    for(int i = 1; i < size; i++) {
        if(MAX < arr[i]) {
            MAX = arr[i];
        }
    }
    return MAX;
}

int divide(int* arr, int bot, int top) {
    int pivot = arr[bot];
    int i = bot; // levi indeks
    int j = top; // desni indeks
    do {
        while(arr[i] <= pivot && i < top) {
            i++;
        }
        while(arr[j] >= pivot && j > bot) {
            j--;
        }
        if(i < j) {
            swap(&arr[i], &arr[j]);
        }
        else {
            swap(&arr[j], &arr[bot]);
        }
    } while(i <= j);
    return j;
}

void quickSort(int* arr, int bot, int top) {
    if(bot < top) {
        int j = divide(arr, bot, top);
        quickSort(arr, bot, j-1);
        quickSort(arr, j+1, top);
    }
}

int divideWithMedian(int* arr, int bot, int top) {
    int pivot = arr[bot];
    int i = bot; // levi indeks
    int j = top; // desni indeks
    do {
        while(arr[i] <= pivot && i < top) {
            i++;
        }
        while(arr[j] >= pivot && j > bot) {
            j--;
        }
        if(i < j) {
            swap(&arr[i], &arr[j]);
        }
        else {
            swap(&arr[j], &arr[bot]);
        }
    } while(i <= j);
    return j;
}

void quickSortWithMedian(int* arr, int bot, int top) {
    if(bot < top) {
        int j = divideWithMedian(arr, bot, top);
        quickSortWithMedian(arr, bot, j-1);
        quickSortWithMedian(arr, j+1, top);
    }
}

void selectionSort(int* arr, unsigned int size) {
    for(int i = 0; i < size - 1; i++) {
        int k = i; // minimalni indeks
        for(int j = i + 1; j < size; j++) {
            if(arr[j] < arr[k]) {
                k = j;
            }
        }
        if(k != i) {
            swap(&arr[i], &arr[k]);
        }
    }
}

void countingSort(int* arr, unsigned int size) {
    int MAX = getMax(arr, size);
    auto* tempArr = new int[MAX + 1] {0};
    auto* outArr = new int[size] {0};
    for(int i = 0; i < size; i++) {
        tempArr[arr[i]]++;
    }
    for(int i = 1; i <= MAX; i++) {
        tempArr[i]+=tempArr[i-1];
    }
    for(int i = size - 1; i >= 0; i--) {
        outArr[tempArr[arr[i]] - 1] = arr[i];
        tempArr[arr[i]]--;
    }
    for(int i = 0; i < size; i++) {
        arr[i] = outArr[i];
    }
}

void romanSort(int* arr, unsigned int size) {
    int MAX = getMax(arr, size);
    auto* tempArr = new int[MAX + 1] {0};
    for(int i = 0; i < size; i++) {
        tempArr[arr[i]]++;
    }
    int index = 0;
    for(int i = 0; i <= MAX; i++) {
        if(tempArr[i] != 0) {
            for(int j = 0; j < tempArr[i]; j++) {
                arr[index++] = i;
            }
        }
    }
    delete[] tempArr;
}

void bubbleSort(int* arr, unsigned int size) {
    for(int i = 0; i < size; i++) {
        for(int j = i + 1; j < size; j++) {
            if(arr[i] > arr[j]) {
                swap(&arr[i], &arr[j]);
            }
        }
    }
}

void insertionSort(int* arr, unsigned int size) {
}

int main() {
    srand(time(nullptr));

    int selection = 0;
    bool running = true;

    int size = 100'000'000;
    auto* arr = new int[size] {0};

    clock_t start;
    clock_t end;
    double duration;

    do {
        menu();
        std::cin >> selection;
        switch(selection) {
            case 1:
                std::cout << "Enter a size of array:" << std::endl;
                inputNum(size);
                randomArray(arr, size);
                break;
            case 2:
                std::cout << "Enter a size of array:" << std::endl;
                inputNum(size);
                randomAscendingArray(arr, size);
                break;
            case 3:
                std::cout << "Enter a size of array:" << std::endl;
                inputNum(size);
                randomDescendingArray(arr, size);
                break;
            case 4:
                printArray(arr, size);
                break;
            case 5:
                if(isSorted(arr, 0, size - 1)) {
                    std::cout << "Array is sorted." << std::endl;
                }
                else {
                    std::cout << "Array is not sorted." << std::endl;
                }
                break;
            case 6:
                start = clock();
                quickSort(arr, 0, size - 1);
                duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
                std::cout << duration << std::endl;
                break;
            case 7:
                quickSortWithMedian(arr, 0, size - 1);
                break;
            case 8:
                start = clock();
                selectionSort(arr, size);
                duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
                std::cout << duration << std::endl;
                break;
            case 9:
                start = clock();
                countingSort(arr, size);
                duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
                std::cout << duration << std::endl;
                break;
            case 10:
                start = clock();
                romanSort(arr, size);
                duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
                std::cout << duration << std::endl;
                break;
            case 11:
                start = clock();
                bubbleSort(arr, size);
                duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
                std::cout << duration << std::endl;
                break;
            case 12:
                start = clock();
                insertionSort(arr, size);
                duration = (std::clock() - start) / (double)CLOCKS_PER_SEC;
                std::cout << duration << std::endl;
                break;
            case 13:
                break;
            case 0:
                running = false;
                break;
            default:
                std::cout << "Wrong selection." << std::endl;
                break;
        }
    } while(running);
    delete[] arr;
}