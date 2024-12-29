#include <SFML/Graphics.hpp>
#include "Model.hpp"
#include "View.hpp"
#include "Controller.hpp"

int main()
{
    const int GRID_WIDTH  = 30;
    const int GRID_HEIGHT = 20;
    const int CELL_SIZE   = 30;
    const double FILL_PROBABILITY = 0.1;

    Model model(GRID_WIDTH, GRID_HEIGHT);

    model.randomize(FILL_PROBABILITY);

    View view(model, CELL_SIZE);

    Controller controller(model, view);
    controller.run();

    return 0;
}
