#include "Controller.hpp"
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"
#include "Populator.hpp"

int main()
{
    Model model(25, 20);
    
    Populator populator;
    //populator.randomize(model, 0);
    populator.loadFromFile(model, "map.txt");

    View view(model, 30);

    Controller controller(model, view);
    controller.run();

    return 0;
}
