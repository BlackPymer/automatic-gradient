#include "float64.h"
#include <stack>

Float64::Float64(double value, bool calculate_gradient,
                 std::shared_ptr<float64> parent1,
                 std::shared_ptr<float64> parent2,
                 char operation)
{
    data = std::make_shared<float64>();
    data->val = value;
    data->calc_grad = calculate_gradient;
    data->parent1 = parent1;
    data->parent2 = parent2;
    data->op = operation;
}

Float64 Float64::operator+(const Float64 &num2) const
{
    return Float64(data->val + num2.data->val, data->calc_grad, data, num2.data, '+');
}
Float64 Float64::operator*(const Float64 &num2) const
{
    return Float64(data->val * num2.data->val, data->calc_grad, data, num2.data, '*');
}
void Float64::backward(double backward_grad)
{
    std::stack<std::shared_ptr<float64>> should_visit;
    if (backward_grad == 0)
        data->grad = 1;
    else
        data->grad += backward_grad;
    should_visit.push(data);
    while (!should_visit.empty())
    {
        std::shared_ptr<float64> data = should_visit.top();
        should_visit.pop();
        if (data->parent1 == nullptr)
            continue;

        if (data->op == '+')
        {
            data->parent1->grad += data->grad;
            data->parent2->grad += data->grad;
        }
        else if (data->op == '*')
        {
            data->parent1->grad += data->grad * data->parent2->val;
            data->parent2->grad += data->grad * data->parent1->val;
        }
        should_visit.push(data->parent1);
        should_visit.push(data->parent2);
    }
}