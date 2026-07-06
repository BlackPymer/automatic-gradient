#pragma once

#include <memory>

struct float64
{
    double val;
    double grad = 0;
    bool calc_grad = true;
    std::shared_ptr<float64> parent1 = nullptr;
    std::shared_ptr<float64> parent2 = nullptr;
    char op = ' ';
};

class Float64
{
private:
    std::shared_ptr<float64> data = nullptr;

public:
    Float64(double value = 0, bool calculate_gradient = true,
            std::shared_ptr<float64> parent1 = nullptr,
            std::shared_ptr<float64> parent2 = nullptr,
            char operation = ' ');
    Float64 operator+(const Float64 &num2) const;
    Float64 operator*(const Float64 &num2) const;

    double value() const { return data->val; }
    double gradient() const { return data->grad; }

    void backward(double backward_grad);
};