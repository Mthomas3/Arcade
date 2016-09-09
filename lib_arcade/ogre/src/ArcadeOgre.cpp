//
// Created by mart_4 on 3/22/16.
//

#include "../../../include/Core/Exceptions.hh"
#include "../include/ArcadeOgre.hh"

Graphic::ArcadeOgre::ArcadeOgre() : _map(nullptr), _input(nullptr), _keyboard(nullptr)
{
}

void Graphic::ArcadeOgre::init(void)
{
    Ogre::LogManager * lm = new Ogre::LogManager();
    lm->createLog(".Ogre.log", true, false, false);
    _root = new Ogre::Root();
    Ogre::RenderSystem *rs;
    _root->loadPlugin("./lib/RenderSystem_GL");
    if (!(rs = _root->getRenderSystemByName("OpenGL Rendering Subsystem")))
        throw exception::ArcadeError("Failed to load RenderSystem", "OGRE");
    _root->setRenderSystem(rs);
    rs->setConfigOption("Full Screen", "No");
    rs->setConfigOption("Video Mode", "600 x 400 @ 32-bit colour");
    rs->setConfigOption("VSync", "No");
    _root->initialise(false);
}

void Graphic::ArcadeOgre::display(void)
{
    Ogre::WindowEventUtilities::messagePump();
    if (_keyboard)
        _keyboard->capture();
    _window->update();
    if (_window->isClosed())
        _events.push_back(arcade::Events::CLOSE);
    if (!_root->renderOneFrame())
        _events.push_back(arcade::Events::CLOSE);
}

void Graphic::ArcadeOgre::createWindow(size_t x, size_t y)
{
    _window = _root->createRenderWindow("Arcade", x, y, false);
    OIS::ParamList pl;
    size_t windowHnd = 0;
    std::ostringstream windowHndStr;
    _window->getCustomAttribute("WINDOW", &windowHnd);
    windowHndStr << windowHnd;
    pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));
    _input = OIS::InputManager::createInputSystem(pl);
    _keyboard = static_cast<OIS::Keyboard *>(_input->createInputObject(OIS::OISKeyboard, true));
    _keyboard->setEventCallback(this);
    _manager = _root->createSceneManager("DefaultSceneManager", "Arcade Scene Manager");
    _manager->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));
    _cam = _manager->createCamera("Main Camera");
    _cam->setNearClipDistance(5);
    _viewport = _window->addViewport(_cam);
    _cam->setAspectRatio(Ogre::Real(_viewport->getActualWidth()) / Ogre::Real(_viewport->getActualHeight()));
    _cam->setPosition(0, 0, 2000);
    _cam->lookAt(0, 0, 0);
    _cam->setProjectionType(Ogre::PT_ORTHOGRAPHIC);
}

void Graphic::ArcadeOgre::destroyWindow(void)
{
    for (Ogre::SceneNode *node : _entities)
    {
        DestroyAllAttachedMovableObjects(node);
        _manager->destroySceneNode(node);
    }
    _entities.clear();
    if (Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("Entities"))
        Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Entities");
    for (Ogre::SceneNode *node : _mapEntities)
    {
        DestroyAllAttachedMovableObjects(node);
        _manager->destroySceneNode(node);
    }
    _mapEntities.clear();
    if (Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("MEntities"))
        Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("MEntities");
    _input->destroyInputObject(_keyboard);
    OIS::InputManager::destroyInputSystem(_input);
    _input = nullptr;
    _root->destroySceneManager(_manager);
    _window->destroy();
    delete _root;
}

void Graphic::ArcadeOgre::setEntities(const std::vector<arcade::Entity *> &entities)
{
    size_t i = 0;
    for (Ogre::SceneNode *node : _entities)
    {
        DestroyAllAttachedMovableObjects(node);
        _manager->destroySceneNode(node);
    }
    _entities.clear();
    if (Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("Entities"))
        Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("Entities");
    Ogre::ResourceGroupManager::getSingleton().createResourceGroup("Entities");
    Ogre::MaterialManager::getSingleton().createResource("Entity", "Entities");
    for (arcade::Entity *entity : entities)
    {
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MaterialEnt" + std::to_string(i), "Entities");
        Ogre::Entity *ent;
        Ogre::SceneNode *node;
        node = _manager->getRootSceneNode()->createChildSceneNode("ent" + std::to_string(i));

        switch (entity->shape.type)
        {
            case arcade::Type::BBOX:
                ent = _manager->createEntity("ent" + std::to_string(i), Ogre::SceneManager::PT_CUBE);
                node->setScale(0.4, 0.4, 1);
                break;
            case arcade::Type::BCIRCLE:
                ent = _manager->createEntity("ent" + std::to_string(i), Ogre::SceneManager::PT_SPHERE);
                node->setScale(0.4, 0.4, 1);
                break;
            case arcade::Type::SBOX:
                ent = _manager->createEntity("ent" + std::to_string(i), Ogre::SceneManager::PT_CUBE);
                node->setScale(0.2, 0.2, 1);
                break;
            case arcade::Type::SCIRCLE:
                ent = _manager->createEntity("ent" + std::to_string(i), Ogre::SceneManager::PT_SPHERE);
                node->setScale(0.2, 0.2, 1);
                break;
            case arcade::Type::TRIANGLE:
                ent = _manager->createEntity("ent" + std::to_string(i), Ogre::SceneManager::PT_SPHERE);
                node->setScale(0.4, 0.4, 1);
                break;
            default:
                ent = _manager->createEntity("ent" + std::to_string(i), Ogre::SceneManager::PT_CUBE);
                node->setScale(0.2, 0.2, 1);
        }
        int color[] = { static_cast<uint8_t>(std::get<0>(entity->shape.color)), static_cast<uint8_t>(std::get<1>(entity->shape.color)),
                        static_cast<uint8_t>(std::get<2>(entity->shape.color)) };
        material->setAmbient(static_cast<float>(color[0]) / 255.0f, static_cast<float>(color[1]) / 255.0f,
                        static_cast<float>(color[2]) / 255.0f);
        ent->setMaterial(material);
        node->attachObject(ent);
        node->setPosition(entity->pos.first * 40 - 20, (_map->getLength() - entity->pos.second) * 40 + 20, 0);
        _entities.push_back(node);
        i++;
    }
}

std::list<arcade::Events > Graphic::ArcadeOgre::getEvents(void)
{
  std::list<arcade::Events> events = _events;
    _events.clear();
  return (events);
}

void Graphic::ArcadeOgre::sendMap(arcade::Map *map)
{
    _map = map;
    size_t i = 0;
    for (Ogre::SceneNode *node : _mapEntities)
    {
        DestroyAllAttachedMovableObjects(node);
        _manager->destroySceneNode(node);
    }
    _mapEntities.clear();
    if (Ogre::ResourceGroupManager::getSingleton().resourceGroupExists("MEntities"))
        Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup("MEntities");
    Ogre::ResourceGroupManager::getSingleton().createResourceGroup("MEntities");
    Ogre::MaterialManager::getSingleton().createResource("MEntity", "MEntities");
    for (size_t i = 0; i < map->getSize(); i++)
    {
        arcade::Entity *entity = (*map)[i];
        Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("MaterialMEnt" + std::to_string(i), "MEntities");
        Ogre::Entity *ent;
        Ogre::SceneNode *node;
        node = _manager->getRootSceneNode()->createChildSceneNode("ment" + std::to_string(i));

        switch (entity->shape.type)
        {
            case arcade::Type::BBOX:
                ent = _manager->createEntity("ment" + std::to_string(i), Ogre::SceneManager::PT_PLANE);
                node->setScale(0.4, 0.4, 1);
                break;
            case arcade::Type::BCIRCLE:
                ent = _manager->createEntity("ment" + std::to_string(i), Ogre::SceneManager::PT_SPHERE);
                node->setScale(0.4, 0.4, 1);
                break;
            case arcade::Type::SBOX:
                ent = _manager->createEntity("ment" + std::to_string(i), Ogre::SceneManager::PT_PLANE);
                node->setScale(0.2, 0.2, 1);
                break;
            case arcade::Type::SCIRCLE:
                ent = _manager->createEntity("ment" + std::to_string(i), Ogre::SceneManager::PT_SPHERE);
                node->setScale(0.2, 0.2, 1);
                break;
            case arcade::Type::TRIANGLE:
                ent = _manager->createEntity("ment" + std::to_string(i), Ogre::SceneManager::PT_SPHERE);
                node->setScale(0.4, 0.4, 1);
                break;
            default:
                ent = _manager->createEntity("ment" + std::to_string(i), Ogre::SceneManager::PT_CUBE);
                node->setScale(0.2, 0.2, 1);
        }
        int color[] = { static_cast<uint8_t>(std::get<0>(entity->shape.color)), static_cast<uint8_t>(std::get<1>(entity->shape.color)),
                        static_cast<uint8_t>(std::get<2>(entity->shape.color)) };
        material->setAmbient(static_cast<float>(color[0]) / 255.0f, static_cast<float>(color[1]) / 255.0f,
                             static_cast<float>(color[2]) / 255.0f);
        ent->setMaterial(material);
        node->attachObject(ent);
        node->setPosition((i % map->getWidth()) * 40, (_map->getLength() - i / map->getWidth()) * 40, 0);
        _mapEntities.push_back(node);
    }
    _cam->setPosition(map->getWidth() / 3 * 40, map->getLength() / 3 * 40, 2000);
    Ogre::Matrix4 mt = _cam->getViewMatrix();
    float z = 1.5f;
    mt[0][0] /= z;
    mt[1][1] /= z;
    _cam->setCustomViewMatrix(true, mt);
}

bool Graphic::ArcadeOgre::keyPressed(const OIS::KeyEvent &e) {
    switch (e.key)
    {
        case OIS::KC_ESCAPE:
            _events.push_back(arcade::Events::CLOSE);
            break;
        case OIS::KC_UP:
            _events.push_back(arcade::Events::UP);
            break;
        case OIS::KC_DOWN:
            _events.push_back(arcade::Events::DOWN);
            break;
        case OIS::KC_LEFT:
            _events.push_back(arcade::Events::LEFT);
            break;
        case OIS::KC_RIGHT:
            _events.push_back(arcade::Events::RIGHT);
            break;
        case OIS::KC_F2:
            _events.push_back(arcade::Events::LIB_DOWN);
            break;
        case OIS::KC_F3:
            _events.push_back(arcade::Events::LIB_UP);
            break;
        case OIS::KC_F4:
            _events.push_back(arcade::Events::GAME_DOWN);
            break;
        case OIS::KC_F5:
            _events.push_back(arcade::Events::GAME_UP);
            break;
        case OIS::KC_F8:
            _events.push_back(arcade::Events::RESTART_GAME);
            break;
        case OIS::KC_F9:
            _events.push_back(arcade::Events::MENU);
            break;
    }
    return false;
}

bool Graphic::ArcadeOgre::keyReleased(const OIS::KeyEvent &e) {
    return false;
}

void Graphic::ArcadeOgre::DestroyAllAttachedMovableObjects(Ogre::SceneNode *pSceneNode)
{
    Ogre::SceneNode::ObjectIterator itObject = pSceneNode->getAttachedObjectIterator();

    while (itObject.hasMoreElements())
    {
        Ogre::MovableObject *pObject = static_cast<Ogre::MovableObject *>(itObject.getNext());
        pSceneNode->getCreator()->destroyMovableObject( pObject );
    }
    Ogre::SceneNode::ChildNodeIterator itChild = pSceneNode->getChildIterator();
    while (itChild.hasMoreElements())
    {
        Ogre::SceneNode *pChildNode = static_cast<Ogre::SceneNode *>(itChild.getNext());
        DestroyAllAttachedMovableObjects(pChildNode);
    }
}