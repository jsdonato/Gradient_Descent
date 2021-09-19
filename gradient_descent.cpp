#include <stdio.h>
#include <getopt.h>
#include <memory>
#include "input.h"
#include "constants.h"
#include "gradient.h"
#include "routine.h"


class Gradient_Descent {
public:
    Gradient_Descent(int argc, char **argv) {
        get_options(argc, argv);
        if (problem_name == "linsys") {
            gradient = std::make_unique<LinSysGradient>(A, b);
        }
        if (routine_name == "simple") {
            routine = std::make_unique<SimpleRoutine>(gradient);
        }
        std::cout << routine->run() << std::endl;
    }
    
    
private:
    std::string problem_name;
    std::string routine_name;
    std::unique_ptr<Gradient> gradient = nullptr;
    std::unique_ptr<Routine> routine = nullptr;
    
    void get_options(int argc, char **argv){
        bool problem = false;
        bool rout = false;
        
        int option_index = 0, option = 0;
        struct option longOpts[] = {{"problem", required_argument, nullptr, 'p'},
                                    {"routine", required_argument, nullptr, 'r'},
                                    { nullptr, 0, nullptr, '\0'}};
        while ((option = getopt_long(argc, argv, "p:r:", longOpts, &option_index)) != -1){
            switch (option){
                case 'p': {
                    problem = true;
                    std::string str_p(optarg);
                    problem_name = str_p;
                    break;
                }
                case 'r': {
                    rout = true;
                    std::string str_r(optarg);
                    routine_name = str_r;
                    break;
                }
                default:
                    exit(1);
            }
        }
        if (!problem) {
            throw std::runtime_error("Did not select problem.  Use -p flag.");
        }
        if (!rout) {
            throw std::runtime_error("Did not select routine.  Use -r flag.");
        }
    }
    
};

int main(int argc, char **argv) {
    Gradient_Descent(argc, argv);
    return 0;
}
