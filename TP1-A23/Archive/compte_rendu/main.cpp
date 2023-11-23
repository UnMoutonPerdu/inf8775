#include <iostream>
#include <fstream> 
#include <sstream> 
#include <vector> 
#include <span>
#include <chrono>
#include <ctime>

// Fonction permettant de recuperer les donnees depuis un fichier
std::vector<int> parser(std::string fileName) {
    std::string myText;

    std::vector<int> sample;    

    std::ifstream SamplesFile(fileName);

    while (getline (SamplesFile, myText, ' ')) {
        sample.push_back(std::stoi(myText));
    }

    SamplesFile.close();

    return sample;
}

// Tri a bulles
void bubble_sort(std::span<int> &samples) {
    int length = samples.size();
    bool sorted;
    for(int i = length-1; i > 0; i--) {
        sorted = true;
        for(int j = 0; j < i; j++) {
            if(samples[j+1] < samples[j]) {
                sorted = false;
                int temp = samples[j+1];
                samples[j+1] = samples[j];
                samples[j] = temp;
            }
        }
        if(sorted) {
            break;
        }
    }
}

// Tri comptage
void counting_sort(std::span<int> &samples, int maxValue) {
    std::vector<int> counter  = std::vector(maxValue + 1, 0);
    for (int i: samples) {
        counter[i] += 1;
    }
    int index = 0;
    for (int i = 0; i < counter.size(); i++) {
        for (int j = 0; j < counter[i]; j++) {
            samples[index] = i;
            index++;
        }
    }
}

// https://www.tutorialspoint.com/data_structures_algorithms/quick_sort_algorithm.htm
// Tri rapide 
void quick_sort(std::span<int> &samples, int maxLength, bool randomPivot = false) {
    if (samples.size() <= 1) return;
    if (randomPivot) {
        std::swap(samples[0], samples[rand() % samples.size()]);
    }
    int pivot = samples[0];
    int low = 0;
    int high = samples.size();
    while(true) {
        while(samples[++low] < pivot);
        while(high > 0 && samples[--high] > pivot);

        if(low >= high) {
            break;
        } else {
            std::swap(samples[low],samples[high]);
        }
    }
    std::swap(samples[high], samples[0]);
    std::span<int> left = samples.subspan(0, high);
    std::span<int> right = samples.subspan(high + 1, samples.size() - high - 1);

    if (left.size() <= maxLength) {
        bubble_sort(left);
    } 
    else {
        quick_sort(left, maxLength, randomPivot);
    }
    
    if (right.size() <= maxLength) {
        bubble_sort(right);
    } 
    else {
        quick_sort(right, maxLength, randomPivot);
    }
}   

int main(int argc, char *argv[]){
    if (argc < 2) {
        std::cout << "Missing args" << std::endl;
        return 1;
    }
    srand(time(0));
    auto samplesVec = parser(argv[2]);

    std::span<int> samples(samplesVec);

    std::chrono::milliseconds duration;

    if (std::string(argv[1]) == "cs"){
        if (argc < 3) {
            std::cout << "Missing args" << std::endl;
            return 1;
        }
        int maxValue = std::stoi(argv[3]);
        auto start = std::chrono::high_resolution_clock::now();
        counting_sort(samples, maxValue);
        auto end = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(end - start);
    }
    else if (std::string(argv[1]) == "qs"){
        if (argc < 4) {
            std::cout << "Missing args" << std::endl;
            return 1;
        }
        int maxLength = std::stoi(argv[3]);
        int randomPivot = std::string(argv[4]) == "true";
        auto start = std::chrono::high_resolution_clock::now();
        quick_sort(samples, maxLength, randomPivot);
        auto end = std::chrono::high_resolution_clock::now();
        duration = duration_cast<std::chrono::milliseconds>(end - start);
    }
    else {
        std::cout << "Wrong algorithm" << std::endl;
        return 1;
    }
 

    std::cout << duration.count() << std::endl;

    int prev = -1;
    for (int s: samplesVec) {
        if (s < prev) {
            std::cout << "Bad sorting: " << s << " is after " << prev << std::endl;
        }
        prev = s;
    }

 
    return 0;
}
