//
// Created by gascon_n on 3/28/16.
//

#include "../include/ArcadeOgre.hh"

extern "C" {
    arcade::IOInterface *getGraphic();
}

arcade::IOInterface *getGraphic()
{
    return (new Graphic::ArcadeOgre);
}