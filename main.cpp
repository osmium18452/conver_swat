#include <torch/torch.h>
#include <iostream>
#include <string>
#include <fstream>
#include "headers/ProgressBar.h"

#define ULL unsigned long long

ULL sizeof_tensor(const torch::Tensor &tensor) {
    return tensor.numel() * torch::elementSize(torch::typeMetaToScalarType(tensor.dtype()));
}

ULL *load_csv_data() {
    double *train_set = nullptr;
    double *test_set = nullptr;
    double *label_set = nullptr;
    ULL *ret = (ULL *) malloc(3 * sizeof(ULL));
    memcpy(ret, &train_set, sizeof(ULL));
    memcpy(ret + 1, &test_set, sizeof(ULL));
    memcpy(ret + 2, &label_set, sizeof(ULL));
    return ret;
}

int main() {
#ifdef _WIN32
    const std::string data_root = R"(E:\Pycharm Projects\causal.dataset\data\swat\)";
#else
    const std::string data_root=R"(/remote-home/liuwenbo/pycproj/tsdata/data/swat/)";
#endif
    const std::string train_set_file = "train.tsv";
    const std::string test_set_file = "test.tsv";
    const std::string label_file = "label.tsv";
    const int sensor_num = 51;
    const int train_set_row = 496800;
    const int test_set_row = 449919;
    const int label_row = 449919;
    auto train_set = (double *) malloc(train_set_row * sensor_num * sizeof(double));
    auto test_set = (double *) malloc(test_set_row * sensor_num * sizeof(double));
    auto label_set = (double *) malloc(label_row * sizeof(double));
    std::cout << data_root + train_set_file << std::endl;
    std::ifstream train_file_stream;
    std::ifstream test_file_stream;
    std::ifstream label_file_stream;
    train_file_stream.open(data_root + train_set_file);
    test_file_stream.open(data_root + test_set_file);
    label_file_stream.open(data_root + label_file);
    ProgressBar pbar(train_set_row);
    pbar.set_prefix("Loading train set");
    for (auto i = 0; i < train_set_row; i++) {
        for (auto j = 0; j < sensor_num; j++) {
            train_file_stream >> *(train_set + i * sensor_num + j);
        }
        pbar.set_postfix(std::to_string(*(train_set + i * sensor_num)));
        pbar.update();
    }
    train_file_stream.close();
    ProgressBar pbar2(test_set_row);
    pbar2.set_prefix("Loading test set");
    for (auto i = 0; i < test_set_row; i++) {
        for (auto j = 0; j < sensor_num; j++) {
            test_file_stream >> *(test_set + i * sensor_num + j);
        }
        pbar2.set_postfix(std::to_string(*(test_set + i * sensor_num)));
        pbar2.update();
    }
    test_file_stream.close();
    ProgressBar pbar3(label_row);
    pbar3.set_prefix("Loading label set");
    for (auto i = 0; i < label_row; i++) {
        label_file_stream >> *(label_set + i);
        pbar3.set_postfix(std::to_string(*(label_set + i)));
        pbar3.update();
    }
    label_file_stream.close();
    torch::Tensor train_set_tensor = torch::from_blob(train_set, {train_set_row, sensor_num}, torch::kFloat64);
    torch::Tensor test_set_tensor = torch::from_blob(test_set, {test_set_row, sensor_num}, torch::kFloat64);
    torch::Tensor label_set_tensor = torch::from_blob(label_set, {label_row, 1}, torch::kFloat64);
    std::cout << "train set size: " << train_set_tensor.sizes() << std::endl;
    std::cout << "train set max and min: " << torch::max(train_set_tensor).item<double>() << " "
              << torch::min(train_set_tensor).item<double>() << std::endl;
    std::cout << "test set size: " << test_set_tensor.sizes() << std::endl;
    std::cout << "test set max and min: " << torch::max(test_set_tensor).item<double>() << " "
              << torch::min(test_set_tensor).item<double>() << std::endl;
    std::cout << "label set size: " << label_set_tensor.sizes() << std::endl;
    std::cout << "label set max and min: " << torch::max(label_set_tensor).item<double>() << " "
              << torch::min(label_set_tensor).item<double>() << std::endl;
    std::ofstream train_set_output_file(data_root + "swat_train_set.pt", std::ios::binary | std::ios::out);
    std::ofstream test_set_output_file(data_root + "swat_test_set.pt", std::ios::binary | std::ios::out);
    std::ofstream label_set_output_file(data_root + "swat_label_set.pt", std::ios::binary | std::ios::out);
    train_set_output_file.write((char *) train_set, train_set_row * sensor_num * sizeof(double));
    test_set_output_file.write((char *) test_set, test_set_row * sensor_num * sizeof(double));
    label_set_output_file.write((char *) label_set, label_row * sizeof(double));
    train_set_output_file.close();
    test_set_output_file.close();
    label_set_output_file.close();
    return 0;
}