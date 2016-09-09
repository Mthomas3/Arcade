//
// Created by styvaether on 3/8/16.
//

#include "../include/ArcadeSFML.hh"

extern "C" {
    arcade::IOInterface *getGraphic();
}

arcade::IOInterface *getGraphic()
{
    return (new Graphic::ArcadeSFML);
}