#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <fstream>
//#include <gui_sdl.h>

namespace po=boost::program_options;

#include <core.h>
#include "ui.h"
#include "uincurses.h"

int main(int argc, char *argv[])
{
    po::options_description desc("Allowed options");
    desc.add_options()
        ("help,h", "produce help message")
        ("debug,d", "set debug mode")
        ("step,s", "set one step mode")
        ("bios,b",po::value<std::string>(), "set bios image file (size:256 byte)")
//        ("show,s", "show all display mode")
//        ("mode,m", "set display mode")
    ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    //! @todo delete std::count
    if (vm.count("help")) {
        std::cout << desc << "\n";
        return 0;
    }

    if (vm.count("bios")) {
//        std::cout << vm["bios"].as<std::string>() << "\n";
        auto bios_filename = vm["bios"].as<std::string>();
        std::ifstream in(bios_filename, std::ios::binary);
        if(in.is_open()){
            memset(memory, 0, sizeof memory);
            in.read((char *)(memory),256);
            in.close();
        }else{
            std::cout << "file: " << bios_filename << " err\n";
            return 1;
        }
    }

    auto *ui = new UINcurses(vm.count("step"));
    reg[REG_PROGRAM_COUNTER]=START_PROGRAMM_MEMORY;
    ui->drawWindows();
    while(runOneStep(ui->uiKeybord()))
    {
        ui->drawWindows();
 //       usleep(300000);
    }
    ui->exit();
    delete ui;
}
