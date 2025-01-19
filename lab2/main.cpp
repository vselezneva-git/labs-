#include "Controller.hpp"
#include "Model.hpp"
#include "View.hpp"

int main()
{
    Model model(25, 20);
    model.randomize(0.2);

    View view(model, 30);

    Controller controller(model, view);
    controller.run();

    return 0;
}
