#include "Scene.hpp"
#include "object/Object.hpp"
#include <cstdlib>

Scene::Scene(Camera *camera) : _camera(camera) { _sceneId = std::rand(); }

Scene::~Scene() {}

void Scene::addObject(Object &obj) { _objects.push_back(obj); }

Camera *Scene::getCamera() const { return _camera; }

std::vector<Object> Scene::getObjects() const { return _objects; }
