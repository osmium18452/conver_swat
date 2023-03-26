#include <torch/torch.h>
#include <iostream>
#include <string>
#include "headers/ProgressBar.h"
#define ULL unsigned long long


using std::cout;
using std::endl;
using std::cin;

ULL sizeof_tensor(const torch::Tensor& tensor) {
    return tensor.numel() * torch::elementSize(torch::typeMetaToScalarType(tensor.dtype()));
}

int main() {
#ifdef _WIN32
    const std::string data_root=R"(E:\Pycharm Projects\causal.dataset\data\swat\)";
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
    int line_num = 0, column_num = 0;
    torch::Tensor train_set = torch::zeros({train_set_row, sensor_num});
    torch::Tensor test_set = torch::zeros({test_set_row, sensor_num});
    torch::Tensor label_set = torch::zeros({label_row, 1});
    std::ifstream train_file_stream;
    train_file_stream.open(data_root + train_set_file);
    ProgressBar pbar(train_set_row);
    return 0;
    for (auto i = 0; i < train_set_row; i++) {
        for (auto j = 0; j < sensor_num; j++) {
            float data;
            train_file_stream >> data;
            train_set[i][j] = data;
        }
    }
    cout << torch::max(train_set).item<float>() << endl << torch::min(train_set).item<float>() << endl;
    cout<<sizeof_tensor(train_set)<<endl;
    return 0;
}